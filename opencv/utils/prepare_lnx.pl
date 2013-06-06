#
# The script prepares Linux distribution of OpenCV from current tree:
#   Copies Linux-related folders to the particular destination folder (..\..\opencv_lnx)
#   Converts all the files from dos to unix format (\x0d\x0a -> \0x0a)
#   Updates include_HEADERS, *_la_SOURCES and EXTRA_DIST lists.
#
use strict;
use File::Path;

my %dosunix_except_ext =
( "dsp" => 1,
  "dsw" => 1,
  "rc" => 1,
  "rc2" => 1,
  "pdf" => 1,
);

my %allsrc;

my @default_dist = qw( ChangeLog AUTHORS NEWS COPYING INSTALL README TODO
                       configure.in prepare.sh );

############################################################################
#
# Operations on sets: union, intersection, subtraction
#
sub set_union
{
    my $ref_a = shift;
    my $ref_b = shift;
    my @a = @$ref_a;
    my @b = @$ref_b;

    my %c = map { $_ => 1 } (@a,@b);

    sort keys %c;
}


sub set_intersect
{
    my $ref_a = shift;
    my $ref_b = shift;
    my @a = @$ref_a;
    my @b = @$ref_b;

    my %a = map { $_ => 1 } @a;
    my %b = map { $_ => 1 } @b;

    sort (grep {defined $a{$_}} (keys %b));
}


sub set_subtract
{
    my $ref_a = shift;
    my $ref_b = shift;
    my @a = @$ref_a;
    my @b = @$ref_b;

    my %a = map { $_ => 1 } @a;
    my %b = map { $_ => 1 } @b;

    sort (grep {!defined $b{$_}} (keys %a));
}


# copy a group of files between two specified folders.
# text files are transformed to UNIX format (0x0d0x0a -> 0x0a) 
sub copy_dos_unix
{
    my $in_folder = shift;
    my $out_folder = shift;
    my @list = @_;
    my $file;
    my $ext;
    my $data;

    foreach $file (@list)
    {
        my $from = "$in_folder/$file";
        my $to = "$out_folder/$file";
        my $folder;
        my $ok;

        open (DOS_IN, "$from") or die "could not open $from";
        open (UNIX_OUT, ">$to") or die "could not open $to";
        binmode(DOS_IN);
        binmode(UNIX_OUT);
        
        $data = join "", <DOS_IN>;

        $from =~ m#\.(\w*)$#;
        $ext = lc($1);

        # purge \r if the file is text and it is not Win32/DevStudio-related file
        eval "\$data =~ s/\r//g" if( -T $from && !defined($dosunix_except_ext{$ext}));

        if( $file eq "configure.in" ) # hook for configure.in
        {
            $data =~ s/AC_OUTPUT\([^\)]+\)//;
            chomp $data;
            $data .= "AC_OUTPUT(";
            foreach $folder (sort keys %allsrc)
            {
                eval "\$ok = (\$folder =~ m#^$in_folder#)";
                if( $ok )
                {
                    eval ("\$folder =~ s#^$in_folder"."[/\\\\]?##");
                    $data .= $folder ? " $folder/Makefile" : " Makefile";
                }
            }

            $data .= " )\n";
        }

        print UNIX_OUT $data;

        close DOS_IN;
        close UNIX_OUT;
    }
} 

# retrieve list of files from specified folder using a glob mask
sub file_list
{
    my $folder = shift;
    my @masks = @_;
    my @result;
    my $m;

    foreach $m (@masks)
    {
        while( <$folder/$m> )
        {
            m#([^\\/]+)$#;
            push @result, $1;
        }
    }

    #print "file_list: ", (join " ", @result), "\n";

    return @result;
}

#######################################################################################
#
# recursive procedure that extracts the Linux tree from the current general Win32/Linux
# tree. Makefile.am's are used to identify which folders to copy (SUBDIRS field)
#
sub process_folder
{
    my $in_folder = shift;
    my $out_folder = shift;
    my $line;
    my @inc = file_list($in_folder, "*.h","*.hpp","*.inc" );
    my @src = file_list($in_folder, "*.c","*.cpp","*.asm" );
    my %subdirs;
    my $subfolder;
    my $am_file;
    my $noinst_HEADERS_passed;
    my $file;
    my $folder;

    mkpath($out_folder) if !(-d $out_folder);

    print "$in_folder\n";

    $allsrc{$in_folder} = [@src];

    $in_folder =~ m#([^\\/]+)$#;
    $folder = $1;

    if( !(-d $out_folder) )
    {
        mkdir( $out_folder ) or die "could not create $out_folder folder";
    }

    open AM_FILE, "$in_folder/Makefile.am"
      or die "could not open $in_folder/Makefile.am";

    while( $line = <AM_FILE> )
    {
        # .+ in below expessions (except the first one, where .* is used) prevents empty lists processing,
        # i.e. in case of empty list (e.g. include_HEADERS = ) the line remains unchanged
        
        if( $line =~ m#^EXTRA_DIST = (.+)# )
        {
            #print "$1\n";
            my $extra_dist = $1;
            my $extra_dist_tmp = $extra_dist;
            
            $extra_dist_tmp =~ s/\w+\.(asm|c|cpp|h)\b *//g; 

            if( $extra_dist_tmp ne $extra_dist )
            {
                $extra_dist = $extra_dist_tmp . " " . join( " ", (@inc,@src));
            }

            # exclude special variables and copy files
            $extra_dist_tmp = $extra_dist;
            $extra_dist_tmp =~ s/\$\([^\)]+\) *//g;
            copy_dos_unix( $in_folder, $out_folder, split(" ",$extra_dist_tmp) );

            $line = "EXTRA_DIST = $extra_dist\n";
        }
        elsif( $line =~ m#^include_HEADERS = (.+)# )
        {
            die "external headers section should go before internal headers section" if $noinst_HEADERS_passed;
            my @ext_inc = split " ", $1;

            @inc = set_subtract( \@inc, \@ext_inc );
            copy_dos_unix( $in_folder, $out_folder, @ext_inc );
        }
        elsif( $line =~ m#^noinst_HEADERS = .+# )
        {
            $line = "noinst_HEADERS = " . (join " ", @inc) . "\n";
            copy_dos_unix( $in_folder, $out_folder, @inc );
        }
        elsif( $line =~ m#^(\w+?_SOURCES) = .+# )
        {
            $line = "$1 = ";
            
            if( !@src ) # case of makefiles in optimized libraries
            {
                my $root_folder = $in_folder;
                $root_folder =~ s#[\//]\w+[\//]\w+$##; # go up two levels
                $root_folder .= "/_src";

                # add all the files from ../../_src and its subfolders
                foreach my $tmpdir (keys %allsrc)
                {
                    my $ok;
                    eval( "\$ok = (\$tmpdir =~ m#$root_folder#)" );
                    push @src, @{$allsrc{$tmpdir}} if $ok;
                }

                $line .= (join " ",@src) . "\n";
            }
            else # normal C/C++ library case
            {
                $line .= (join " ",@src) . "\n";
                copy_dos_unix( $in_folder, $out_folder, @src );
            }
        }
        elsif( $line =~ m#^SUBDIRS = (.+)# ||
               $line =~ m#^DIST_SUBDIRS = (.+)# )
        {
            my @tmpsubdirs = split (" ", $1);
            foreach my $dir (@tmpsubdirs)
            {
                $subdirs{$dir}++ if ($dir !~ m#^@#); #exclude folders starting from @ or .
            }
        }
        elsif( $line =~ m#^[ \t]# ) # if line starts with ' ' or TAB, replace them
        {                           # with a single TAB
            $line =~ s#^[ \t]+##;
            $line = "\t" . $line;
        }
        $am_file .= $line;
    }

    close AM_FILE;

    # purge \r in Makefile.am
    eval "\$am_file =~ s/\r//g";

    # save modified Makefile.am
    open AM_FILE, ">$out_folder/Makefile.am"
        or die "could not open $out_folder/Makefile.am";
    binmode( AM_FILE );
    print AM_FILE $am_file;
    close AM_FILE;

    foreach $subfolder (reverse sort keys %subdirs) # make sure _make goes after _src
    {
        process_folder( "$in_folder/$subfolder", "$out_folder/$subfolder", 0 );
    }

    # copy standard GNU files if present
    copy_dos_unix( $in_folder, $out_folder, grep { -e "$in_folder/$_" } @default_dist );
}

############################################################
#
# main script
#
if( defined($ARGV[0]) && defined($ARGV[1]))
{
    my $in_root = $ARGV[0];
    my $out_root = $ARGV[1];

    $in_root =~ s#[\\/]$##;  # remove trailing / or \\
    $out_root =~ s#[\\/]$##; # ditto

    process_folder( $in_root, $out_root );
}
else
{
    print "Usage: prepare_lnx.pl source_root destination_root\n";
}


#
#   The script generates makefiles for the following Win32 compilers:
#       Microsoft Visual C++,
#       Borland C++,
#       Intel Compiler,
#       Mingw GNU C++
#

@folderlist = (
    "cv\\make",
    "cvaux\\make",
    "otherlibs\\highgui",
);

%compilers = (

    "vc" => {
       NAME => "Microsoft Visual C++",
       IF_PREFIX => "!",
       MAKEFILE_FLAG => "/f",
       MAKE => "nmake"
    },

    "icl" => {
       NAME => "Intel Compiler",
       IF_PREFIX => "!",
       MAKEFILE_FLAG => "/f",
       MAKE => "nmake"
    },

    "bcc" => {
       NAME => "Borland C++",
       IF_PREFIX => "!",
       MAKEFILE_FLAG => "-f",
       MAKE => "bcmake"
    },

    "gcc" => {
       NAME => "Mingw GNU C++",
       IF_PREFIX => "",
       MAKEFILE_FLAG => "-f ",
       MAKE => "make"
    }
);


foreach $cc (keys %compilers)
{
    %ccflags = %{$compilers{$cc}}; 

    open MAKEFILE, ">..\\makefile.$cc";

    $make = $ccflags{MAKE};
    $if = $ccflags{IF_PREFIX};
    $file_flag = $ccflags{MAKEFILE_FLAG};

    print MAKEFILE <<MAKEALL;
# Master make file for $ccflags{NAME}
${if}ifdef debug
OPT= debug=1
${if}else
OPT=
${if}endif

all:
MAKEALL

    foreach $folder (@folderlist)
    {
        $i = 0;
        @levels = $folder =~ m#[/\\]#g;
        $count = scalar(@levels)+1;

        while ($dsp = glob("..\\$folder\\*.dsp"))
        {
            # extract dsp file name
            $dsp =~ m#([^/\\]+)\.dsp$#;
            $name = $1;

            eval "\$ok = (\$folder =~ m#$name#i)";

            if( $ok )
            {
                #print "\$dsp = $dsp, \$name = $name\n"; 
 
                system("perl gen_make.pl $cc ..\\$folder\\$name.dsp $count > ..\\$folder\\makefile.$cc\n");
                if( $cc ne "gcc" )
                {
                    print MAKEFILE "\tcd $folder\n";
                    print MAKEFILE "\t$make ${file_flag}makefile.$cc \$(OPT)\n";
                    print MAKEFILE "\tcd ". ("..\\" x ($count - 1)) . "..\n";
                }
                else
                {
                    print MAKEFILE "\t$make -C $folder -f makefile.$cc\n";
                }
            }
        }
    }

    close MAKEFILE;
}







#
# The master script that creates Makefile for given compiler from DSP file
#   
#   Usage: [perl] gen_make.pl <compiler> <dsp_file_name> level
#   
#      Where compiler is one of:
#         vc  == Microsoft Visual C++ 6.0,
#         bcc == Borland C++ 5.5
#         icl == Intel Proton 5.0,
#         gcc == GCC 2.95.3 (Mingw variant). 
#      
#      libname - Name of the library. The list of files will be taken from
#                <libname>.dsp file. Currently, the files in the project may have
#                only .cpp, *.h and *.hpp extensions.
#      level - Number of "..\" to get to the bin,lib and temp folders.
#

sub long_list
{
    my ($str, $prefix, $suffix, @list) = ($_[0], $_[1], $_[2], @{$_[3]});

    $len = length($str);

    foreach $item (@list)
    {
        $s = "$prefix$item$suffix ";
        $len_delta = length($s);
        if( $len + $len_delta > 85 )
        {
            print "$str\\\n";
            $str = "";
            $len = 0;
        }
        $str .= $s;
        $len += $len_delta;
    }
    return $str;
}

$GCC_HACK="none"; # !!! replace "none" with "gcc" in order to make use of VPATH !!!

$level = $ARGV[2];
$dsppath = $ARGV[1];
$dsppath =~ m#([^/\\]+)\.dsp$#i;
$libname = $1;

$top="..\\" x $level;

%cchash = (
    "vc" => {
        NAME => "Microsoft Visual C++",
        CXX => "cl",
        LINK => "link",
        OBJ => ".obj",
        DEFINE_OPT => "/D",
        INCDIR_OPT => "/I",
        LIBDIR_OPT => "/libpath:",
        LIB_EXT => ".lib",
        LIB_LINK_EXT => ".lib",
        LIB_LINK => "",
        IF_PREFIX => "!",
        INLINE_START => "",
        INLINE_END => "",
        DEPENDENTS => "\$**",
        CXXFLAGS_ALL => "/nologo /GX /GB /W4 " .
                        "/I \"\$(VCHOME)/include\" /c /Fo",
        CXXFLAGS_RELEASE => "/O2 /Ob2",
        CXXFLAGS_DEBUG => "/Gm /Zi /Od /FD /GZ",
        LINKFLAGS_ALL => "/nologo ".
                         "/subsystem:windows /dll /pdb:none ".
                         "/machine:I386 /out:\$(OUTDLL) /implib:\$(OUTLIB) ".
                         "/libpath:\"\$(VCHOME)/lib\" ",
        LINKFLAGS_DEBUG => "/debug",
        LINKFLAGS_RELEASE => "",
        LINKPOSTSTEP => "" },

    "icl" => {
        NAME => "Intel Proton Compiler 5.0",
        CXX => "icl",
        LINK => "link",
        OBJ => ".obj",
        DEFINE_OPT => "/D",
        INCDIR_OPT => "/I",
        LIBDIR_OPT => "/libpath:",
        LIB_EXT => ".lib",
        LIB_LINK_EXT => ".lib",
        LIB_LINK => "",
        IF_PREFIX => "!",
        INLINE_START => "",
        INLINE_END => "",
        DEPENDENTS => "\$**",
        CXXFLAGS_ALL => "/nologo /GX /GB /W4 " .
                        "/I \"\$(VCHOME)/include\" " .
                        " \"/Qwd171,424,981\" /Qxi /Qaxi /c /Fo",
        CXXFLAGS_RELEASE => "/O2 /Ob2",
        CXXFLAGS_DEBUG => "/Gm /Zi /Od /FD /GZ",
        LINKFLAGS_ALL => "/nologo ".
                         "/subsystem:windows /dll /pdb:none ".
                         "/machine:I386 /out:\$(OUTDLL) /implib:\$(OUTLIB) ".
                         "/nodefaultlib:libm /nodefaultlib:libirc ".
                         "/libpath:\"\$(VCHOME)/lib\" ",
        LINKFLAGS_DEBUG => "/debug",
        LINKFLAGS_RELEASE => "",
        LINKPOSTSTEP => "" },

    "bcc" => {
        NAME => "Borland C++ 5.5",

        CXX => "bcc32",
        LINK => "bcc32",
        OBJ => ".obj",
        DEFINE_OPT => "-D",
        INCDIR_OPT => "-I",
        LIBDIR_OPT => "-L",
        LIB_EXT => ".lib",
        LIB_LINK_EXT => ".lib",
        LIB_LINK => "",
        IF_PREFIX => "!",
        INLINE_START => "@&&|\n",
        INLINE_END => "\n|",
        DEPENDENTS => "\$**",
        CXXFLAGS_ALL => "-3 -I\"\$(BCHOME)/include\" ".
                        "-a8 -b -c -d -RT- -tWM -w-inl -w-aus -j200 -o",
        CXXFLAGS_RELEASE => "-O2",
        CXXFLAGS_DEBUG => "-Od -v",
        LINKFLAGS_ALL => "-tWD -e\$(OUTDLL) -L\"\$(BCHOME)/lib\" ".
                         " -L\"\$(BCHOME)/lib/PSDK\" ",
        LINKFLAGS_DEBUG => "",
        LINKFLAGS_RELEASE => "",
        LINKPOSTSTEP => "implib \$(OUTLIB) \$(OUTDLL)"  },

    "gcc" => {
        NAME => "GNU C/C++ 2.95.3",
        CXX => "g++",
        LINK => "g++",
        OBJ => ".o",
        DEFINE_OPT => "-D",
        INCDIR_OPT => "-I",
        LIBDIR_OPT => "-L",
        LIB_PREFIX => "lib",
        LIB_EXT => ".a",
        LIB_LINK_EXT => "",
        LIB_LINK => "-l",
        IF_PREFIX => "",
        INLINE_START => "",
        INLINE_END => "",
        DEPENDENTS => "\$(OBJS)",
        CXXFLAGS_ALL => "-I\"\$(GCCHOME)/include\" -Wall -c -o",
        CXXFLAGS_RELEASE => "-O2",
        CXXFLAGS_DEBUG => "-O0 -ggdb3",
        LINKFLAGS_ALL => "-o\$(OUTDLL) -shared -Wl,-call_shared,--out-implib,\$(OUTLIB) ",
        LINKFLAGS_DEBUG => "",
        LINKFLAGS_RELEASE => "",
        LINKPOSTSTEP => "" },
);

# "/I \"\$(VCHOME)/include\" /D \"_DEBUG\" " .
# "/D \"WIN32\" /D \"_WINDOWS\" /D \"CV_DLL\" /c /Fo",

$compiler = "\L$ARGV[0]";

%ccflags = %{$cchash{$compiler}} or die "Wrong compiler name";

$temppath = "${top}_temp\\$libname\$(DR)";
$dllpath = "${top}bin\\$libname\$(SUFFIX).dll";
$libpath = "${top}lib\\$ccflags{LIB_PREFIX}$libname\$(SUFFIX)$ccflags{LIB_EXT}";
$if = $ccflags{IF_PREFIX};
$obj = $ccflags{OBJ};

# CXXFLAGS4 = $ccflags{INCDIR_OPT}"\$(DSHOME)\\include" $ccflags{INCDIR_OPT}"\$(DSHOME)\\samples\\Multimedia\\DirectShow\\BaseClasses"
# LINKFLAGS4 = $ccflags{LIBDIR_OPT}"\$(DSHOME)\\lib" $ccflags{LINKFLAGS_ALL}

print <<HEAD;
# Makefile for $ccflags{NAME}

CXX = $ccflags{CXX}
LINK = $ccflags{LINK}

${if}ifdef debug

SUFFIX = d
DR = _Dbg

${if}else

SUFFIX =
DR = _Rls

${if}endif    

OUTDLL = $dllpath
OUTLIB = $libpath
HEAD

print "vpath = $temppath\n\n" if $compiler eq $GCC_HACK;

open(dspfile,$dsppath) || die "Can not open $dsppath";

@filelist=();  # list of source files (full paths)
@barelist=();  # list of source files (names only (to build object file names))
@inclist=();   # list of include files
%incpaths=();  # hash of include paths
%debug_defines=();  # hash of defines in DEBUG configuration
%release_defines=();  # hash of defines in RELEASE configuration
$debug_libs="";
$release_lib="";

while($line = <dspfile>)
{
    if( $line =~ m#SOURCE=(.*?\.(c|cpp))\n$#i )
    {
        $name = $1;
        push @filelist, $name;
        $name =~ m#.*?(\w+)\.(c|cpp)$#i;
        push @barelist, $1;
    }
    elsif( $line =~ m#SOURCE=(.*?\.(h|hpp))\n$#i )
    {
        $name = $1;
        $name =~ s#\\#/#g;
        push @inclist, $name;
        $name =~ m#(.*?)/\w+\.(h|hpp)$#i;
        $incpaths{"\L$1"}++ if $1; # add the include path into the hash if it is not in yet
    }
    elsif( $line =~ m/^# ADD CPP/ )
    {
        # fetch a list of include directories
        while( $line =~ m#/I\s*"(\S+)\s+#g )
        {
            $name = "\L$1";
            $name =~ s#\\#/#g;
            chop $name;
            $incpaths{$name}++ if $name; #import include path from developer studio
        }

        if( $line !~ m#_STATIC# ) # hack only for CV
        {
            if( $line =~ m#_DEBUG# )
            {
                # fetch a list of preprocessor definitions
                while( $line =~ m#/D\s*"(\S+)\s+#g )
                {
                    $name = $1;
                    chop $name;
                    $debug_defines{$name}++ if $name; #import include path from developer studio
                }
            }
            else
            {
                # fetch a list of preprocessor definitions
                while( $line =~ m#/D\s*"(\S+)\s+#g )
                {
                    $name = $1;
                    chop $name;
                    $release_defines{$name}++ if $name; #import include path from developer studio
                }
            }
        }
    }
    elsif( $line =~ m/^# ADD LINK32/ && $line =~ m#/dll#i )
    {
        # fetch list of libraries
        if( $line =~ m#/debug#i )
        {
            while( $line =~ m#(\w+)\.lib #gi )
            {
                $name = "$ccflags{LIB_LINK}\L$1$ccflags{LIB_LINK_EXT} ";
                $debug_libs .= $name;
            }
        }
        else
        {
            while( $line =~ m#(\w+)\.lib #gi )
            {
                $name = "$ccflags{LIB_LINK}\L$1$ccflags{LIB_LINK_EXT} ";
                $release_libs .= $name;
            }
        }
    }
}

close(dspfile);

print long_list( "OBJS = ", $compiler eq $GCC_HACK ? "" : "$temppath\\", "$obj", \@barelist ) . "\n";
print long_list( "\n\nINC = ", "", "", \@inclist ) . "\n";

$ccopt = "";
$debug_ccopt = "";
$release_ccopt = "";

foreach $incpath (keys %incpaths)
{
    $ccopt .= "$ccflags{INCDIR_OPT}\"$incpath\" ";
}

foreach $define  (keys %debug_defines)
{
    $debug_ccopt .= "$ccflags{DEFINE_OPT}\"$define\" ";
}

foreach $define  (keys %release_defines)
{
    $release_ccopt .= "$ccflags{DEFINE_OPT}\"$define\" ";
}

print <<MIDDLE;

CXXFLAGS2 = $ccopt $ccflags{CXXFLAGS_ALL}
LINKFLAGS2 = $ccflags{LIBDIR_OPT}${top}lib $ccflags{LINKFLAGS_ALL} 

${if}ifdef debug

CXXFLAGS = $debug_ccopt $ccflags{CXXFLAGS_DEBUG} \$(CXXFLAGS2)
LIBS = $debug_libs
LINKFLAGS = \$(LINKFLAGS2) $ccflags{LINKFLAGS_DEBUG} 

${if}else

CXXFLAGS = $release_ccopt $ccflags{CXXFLAGS_RELEASE} \$(CXXFLAGS2)
LIBS = $release_libs
LINKFLAGS = \$(LINKFLAGS2) $ccflags{LINKFLAGS_RELEASE} 

${if}endif


\$(OUTDLL): \$(OBJS)
\t-mkdir ${top}bin 2>nul
\t-mkdir ${top}lib 2>nul
\t\$(LINK) $ccflags{INLINE_START} \$(LINKFLAGS) $ccflags{DEPENDENTS} \$(LIBS) $ccflags{INLINE_END}
\t$ccflags{LINKPOSTSTEP}

all: \$(OUTDLL)

MIDDLE

#\$(OUTDLL): INIT_BUILD \$(OBJS)
#\t-mkdir ${top2}bin
#\t-mkdir ${top2}lib
#\t\$(LINK) $ccflags{INLINE_START} \$(LINKFLAGS) \$(OBJS) $ccflags{INLINE_END}
#\t$ccflags{LINKPOSTSTEP}

$i = 0;
foreach $file (@barelist)
{
    $infile = $filelist[$i++];
    print (($compiler eq $GCC_HACK ? "" : "$temppath\\") . "$file$obj: $infile \$(INC)\n");
    if( $i == 1 )
    {
        print "\t@-mkdir $temppath 2>nul\n";
    }
    print "\t-\$(CXX) \$(CXXFLAGS)$temppath\\$file$obj $infile\n";
}


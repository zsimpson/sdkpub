clapack-3.2.1 was added to sdkpub for use with KinTek Explorer in Sept 2014.  It is considerably
newer than the clapack already in sdkpub, and I wanted to make some further configuration changes,
like causing the typedef'd integer type to be 32bit instead it's default of 64 -- this because I'm 
calling LAPACK functions from a library I didn't write, which assumes ints to be 32bit.

Since I develop in OSX, I took the easiest route forward in providing this library for win32, 
which was downloading prebuilt binaries for win32 from http://icl.cs.utk.edu/lapack-for-windows/clapack/
At the time of this writing that page says these binaries correspond to version 3.2.1 of clapack, and
were built with VS2008.

If you need to build from source, then explore the clapack package built around CMake.  With the CMake 
distribution, you can apparently create the .dsp files needed for Visual Studio.

I would create these and version control them, since we'd prefer to not require zlab users to install 
CMake to build any of the SDKs.

tfb sept 2014

####

I ended up downloading the clapack-3.2.1 with CMAKE, and using CMAKE on Win7 to generate the solution
files.  The CMAKE run generates quite a number of vcproj files for vs2008, so I'm just copying the
resulting libs into win32/prebuilt.  The reason I needed to build after all is that the prebuilt
versions available for download link against DLLs and so externally ref'd fns have the __imp_ prefix.

####

To build 64bit versions of these libs, I used the vcupdate.exe tool that comes with the free vs2013
and converted the specific projects for blas.lib, lapack.lib, and libf2c.lib to the newer .vcxproj
format.  I opened these in vs2013, created a new x64 build configuration, and build  them in that
tool.  I copied the libs into the vc12_64bit folder.  The sdkbuild.pl entry for clapack-3.2.1 will
copy either the 32bit or the 64bit libs in the the prebuilt folder so that the path to the lib
remains the same in the win32lib entry etc.

tfb may 2015
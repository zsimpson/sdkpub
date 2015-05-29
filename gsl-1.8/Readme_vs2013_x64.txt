To build 64bit windows code, I installed vs2013 community edition (free).  Used the vcupgrade.exe tool to
update the .vcproj files under VC8 folder for libgsl and libgslcblas from the vs2008 versions -- the updated versions get a new
name .vcxproj.  I opened those in vs2013 and added the x64 platform, and edited the gsl-1.8 entry in
sdkbuild to use the newer msbuild.exe (replaces vcbuild.exe) to build these new projects.  This results in
64bit libs that can be linked to a 64bit app.

You can still use vs2008 (vc9) to build the 32bit versions - I did not update that yet, though it would
be easy to just use msbuld.exe to build the 32bit versions also using those updated vcxproj files.

tfb
27 may 2015



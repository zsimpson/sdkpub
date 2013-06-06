The VC6 project was created by TFB to build GSL 1.8 code for zlab projects on win32.  This GSL code was obtained
here: http://gnuwin32.sourceforge.net/packages/gsl.htm

This is modified from the standard GSL releases to compile with MS compilers on win32 - that particular distro 
comes with project files etc... for msvc v8 (vs2005 Express etc).  I created the ones for v6 which we use for zlab.
See other readme files in root folder for gsl-1.8

WARNING: the current project file does not include ALL of the sources for gsl 1.8.  I only added the folders that
were necessary for numerical integration and nonlinear fitting.

Mods to gsl-1.8 source package:

1.  eliminate deep folder structure & make gsl-1.8 the root for this sdk
2.  all source files in gsl #include with either no path prefix, or <gsl/...>, but there is no such
    common include folder in the distribution.  So I create an "include" folder and place the config.h
    header there, and create a folder "gsl" under this and copy all headers for the sdk there.
3.  See svn for a couple options in config.h modified to compile under VC6.


thomas blom
june 18, 2007
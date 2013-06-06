Hawk is the application designed for interactive development and testing
of Computer Vision algorithms. It represents all features of IPL library and
a part of IPPI library (full support of IPPI to come soon). Also it can 
support ANY library that has a proper "wrapper plugin" to Hawk.


Hawk consists of the following parts and modules:

== CVEiCL (lib): the interpreter based on EiC interpreter of ISO C

== HighGUI (lib): the library that provides high-level interface to UI
   features like windows creation, images visualization, user input, etc.

== IplWrap (dll): the module that wraps IPL library for it to be used 
   in Hawk. It should be disposed in plugins directory.

== IppiWrap (dll): the same for IPPI library

== ProxyTrans (DS filter): the filter for working with camera (up to now 
   supports only Intel USB Camera). Before working with the camera, you 
   should register the filter, like this:

   regsvr32 ProxyTrans.ax

== Hawk itself: getting all the parts together and providing a friendly
   UI. Also it contains the block of converters (to be a separate module 
   soon) to and from IPPI, IPL image structures and Win32 bitmap.


There are two samples of using Hawk in the scripts directory. 
Hough.c demonstrates the text rotation angle recognition based on 
Hough transform;
Ds.c shows how to work with DirectShow.
This is a stereo demo.
It is a console-based application that uses cvcam for video capture and
highgui for visualization.

Below are the application requirements and instructions on using the application:

To run the demo you will need two USB cameras that are compatible with DirectShow
and can work in pair. Creative WebCam is an example of such a camera, 3Com is not
(currently). Two different cameras might be also OK.

Also, you will need to register ProxyTrans.ax and SyncFilter.ax DirectShow filters
from opencv\bin folder using regsvr32.exe utility or
opencv\bin\RegisterAll.bat batch command file.

When the application starts, three windows displaying cameras, appear,
"camera 1" shows left camera's view, "camera 2" shows right camera's view.
If they are swapped, press 't' to swap them back.

First, you need to calibrate cameras. Use checkerboard etalon.
Default size of checker board (7x10 squares) is hard-coded into the demo code -
change it in main.cpp, line 26 if you have different board size, or
pass the size in command line, e.g. if you have 10x15 board, run the demo
as "StereoDemo 10 15".
To start calibration (and to interrupt calibration), press 'g'.
When camera is calibrated, disparity map starts displaying automatically.
Press 'r' to toggle disparity map  displaying.
Press 's' to save camera parameters.
Press 'l' to load previously stored camera parameters.
Press ESC to quit the program.

For other options see online help that is displayed using 'h' command.

!!!CAUTION!!! Although Creative WebCams work well together, their driverts
may cause the system hangup upon the system exit. So, it is recommented
to close all the running applications and save the currently open documents
before the application execution.


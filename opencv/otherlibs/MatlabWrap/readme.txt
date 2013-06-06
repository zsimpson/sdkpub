This is a source code and executables for MATLAB wrappers for OpenCV.
To install wrappers, set path in the MATLAB to the "toolbox/opencv"
subfolder of this folder and, optionally, to "toolbox/opencv/demos" subfolder.
Wrappers for OpenCV functions can be run in two ways:
cvwrap('<FunctionName>', parameters) where FunctionName is opencv function without
cv prefix,
or
just cvFunctionName( parameters).

To build matlab wrappers you need to add <matlab_folder>/extern/include folder
to include path (within Developer Studio) and
<matlab_folder>/extern/lib/win32;<matlab_folder>/extern/lib/win32/microsoft/msvc60
folders to lib path.

Below is the list of OpenCV functions for which wrappers are written,
[x] mark the functions for which more convenient .m files (that provide
second way of funcitons use) have been created
    cvErode                        [x]
    cvDilate                       [x]
    cvPyrUp                        [x]
    cvPyrDown                      [x]
    cvLaplace                      [ ]
    cvSobel                        [ ]
    cvDistTransform                [ ]
    cvCanny                        [ ]
    cvPreCornerDetect              [ ]
    cvMatchTemplate                [x]
    cvUpdateMotionHistory          [ ]
    cvMinMaxLoc                    [ ]
    cvThreshold                    [x]
    cvFindContours                 [x]
    cvDrawContours                 [x]
    cvApproxPoly                   [x]
    cvContourPerimeter             [x]
    cvContourArea                  [x]
    cvContourBoundingRect          [x]
    cvFloodFill                    [x]
    cvCalcOpticalFlowPyrLK         [x]
    cvGoodFeaturesToTrack          [x]

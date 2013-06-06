# Makefile for Intel Proton Compiler 5.0

CXX = icl
LINK = link

!ifdef debug

SUFFIX = d
DR = _Dbg

!else

SUFFIX =
DR = _Rls

!endif    

OUTDLL = ..\..\bin\CV$(SUFFIX).dll
OUTLIB = ..\..\lib\CV$(SUFFIX).lib
OBJS = ..\..\_temp\CV$(DR)\cvConvHull.obj ..\..\_temp\CV$(DR)\cvEllipseFit.obj \
..\..\_temp\CV$(DR)\cvGeometry.obj ..\..\_temp\CV$(DR)\cvGeometryWrap.obj \
..\..\_temp\CV$(DR)\CvLineFit.obj ..\..\_temp\CV$(DR)\CvProject.obj \
..\..\_temp\CV$(DR)\cvRotCalipers.obj ..\..\_temp\CV$(DR)\cvSubdivision2D.obj \
..\..\_temp\CV$(DR)\cvImage.obj ..\..\_temp\CV$(DR)\camshift.obj \
..\..\_temp\CV$(DR)\cvConDens.obj ..\..\_temp\CV$(DR)\cvKalman.obj \
..\..\_temp\CV$(DR)\cvAdapThresh.obj ..\..\_temp\CV$(DR)\cvThresh.obj \
..\..\_temp\CV$(DR)\cvCalcCovarMatrix.obj ..\..\_temp\CV$(DR)\cvJacobiEigens.obj \
..\..\_temp\CV$(DR)\cvmathfuncs.obj ..\..\_temp\CV$(DR)\cvmatmul.obj \
..\..\_temp\CV$(DR)\cvMatrix.obj ..\..\_temp\CV$(DR)\cvMatrix64d.obj \
..\..\_temp\CV$(DR)\cvSvd.obj ..\..\_temp\CV$(DR)\cvMean.obj \
..\..\_temp\CV$(DR)\cvMeanSdv.obj ..\..\_temp\CV$(DR)\cvMinMaxLoc.obj \
..\..\_temp\CV$(DR)\cvMoments.obj ..\..\_temp\CV$(DR)\cvNorm.obj \
..\..\_temp\CV$(DR)\cvSumPixels.obj ..\..\_temp\CV$(DR)\cvCamShift.obj \
..\..\_temp\CV$(DR)\cvCalcContrastHistogram.obj ..\..\_temp\CV$(DR)\cvEMD.obj \
..\..\_temp\CV$(DR)\cvHistogram.obj ..\..\_temp\CV$(DR)\cvApprox.obj \
..\..\_temp\CV$(DR)\cvContourArea.obj ..\..\_temp\CV$(DR)\cvContours.obj \
..\..\_temp\CV$(DR)\cvContoursMoments.obj ..\..\_temp\CV$(DR)\cvContourTree.obj \
..\..\_temp\CV$(DR)\cvDominants.obj ..\..\_temp\CV$(DR)\cvMatchContours.obj \
..\..\_temp\CV$(DR)\cvPGH.obj ..\..\_temp\CV$(DR)\cvShapeDescr.obj \
..\..\_temp\CV$(DR)\cvMoTempl.obj ..\..\_temp\CV$(DR)\cvMotSeg.obj \
..\..\_temp\CV$(DR)\cvDrawing.obj ..\..\_temp\CV$(DR)\cvOutText.obj \
..\..\_temp\CV$(DR)\cvAlloc.obj ..\..\_temp\CV$(DR)\cverror.obj \
..\..\_temp\CV$(DR)\cvprecomp.obj ..\..\_temp\CV$(DR)\cvSamplers.obj \
..\..\_temp\CV$(DR)\cvtables.obj ..\..\_temp\CV$(DR)\cvTemplMatch.obj \
..\..\_temp\CV$(DR)\cvUtilitiesWrap.obj ..\..\_temp\CV$(DR)\cvutils.obj \
..\..\_temp\CV$(DR)\cvDisTransform.obj ..\..\_temp\CV$(DR)\cvHough.obj \
..\..\_temp\CV$(DR)\cvHoughDiv.obj ..\..\_temp\CV$(DR)\cvHoughP.obj \
..\..\_temp\CV$(DR)\cvHoughWrap.obj ..\..\_temp\CV$(DR)\cvPOSIT.obj \
..\..\_temp\CV$(DR)\cvSnakes.obj ..\..\_temp\CV$(DR)\cvLkPyramid.obj \
..\..\_temp\CV$(DR)\cvOptFlowBM.obj ..\..\_temp\CV$(DR)\cvOptFlowHS.obj \
..\..\_temp\CV$(DR)\cvOptFlowLK.obj ..\..\_temp\CV$(DR)\cvDataStructs.obj \
..\..\_temp\CV$(DR)\cvCalcCovarMatrixEx.obj \
..\..\_temp\CV$(DR)\cvCalcEigenObjects.obj \
..\..\_temp\CV$(DR)\cvEigenDecomposite.obj \
..\..\_temp\CV$(DR)\cvEigenObjectsWrap.obj ..\..\_temp\CV$(DR)\cvEigenProjection.obj \
..\..\_temp\CV$(DR)\cvMorph.obj ..\..\_temp\CV$(DR)\cvMorphWrap.obj \
..\..\_temp\CV$(DR)\cvpyramids.obj ..\..\_temp\CV$(DR)\cvPyrSegmentation.obj \
..\..\_temp\CV$(DR)\cvFloodFill.obj ..\..\_temp\CV$(DR)\cvCalcImageHomography.obj \
..\..\_temp\CV$(DR)\cvCalcProbDensity.obj ..\..\_temp\CV$(DR)\cvCreateHandMask.obj \
..\..\_temp\CV$(DR)\cvFindHandRegion.obj \
..\..\_temp\CV$(DR)\cvGestureRecognition.obj ..\..\_temp\CV$(DR)\cvMaxRect.obj \
..\..\_temp\CV$(DR)\cvCorrespond.obj ..\..\_temp\CV$(DR)\cvFundam.obj \
..\..\_temp\CV$(DR)\cvLines.obj ..\..\_temp\CV$(DR)\cvLMedS.obj \
..\..\_temp\CV$(DR)\cvMorphing.obj ..\..\_temp\CV$(DR)\cvPrewarp.obj \
..\..\_temp\CV$(DR)\cvScanlines.obj ..\..\_temp\CV$(DR)\cvBlur.obj \
..\..\_temp\CV$(DR)\cvConvGen.obj ..\..\_temp\CV$(DR)\cvFilterWr.obj \
..\..\_temp\CV$(DR)\cvInitConvol.obj ..\..\_temp\CV$(DR)\cvLaplace.obj \
..\..\_temp\CV$(DR)\cvScharr.obj ..\..\_temp\CV$(DR)\cvAbsDiff.obj \
..\..\_temp\CV$(DR)\cvAccum.obj ..\..\_temp\CV$(DR)\cvCanny.obj \
..\..\_temp\CV$(DR)\cvCorner.obj ..\..\_temp\CV$(DR)\cvCornerSubPix.obj \
..\..\_temp\CV$(DR)\cvDetectWr.obj ..\..\_temp\CV$(DR)\cvfeatureselect.obj \
..\..\_temp\CV$(DR)\cvMinEVal.obj ..\..\_temp\CV$(DR)\cvPreCorner.obj \
..\..\_temp\CV$(DR)\cvCalibInit.obj ..\..\_temp\CV$(DR)\cvCalibration.obj \
..\..\_temp\CV$(DR)\cvUnDistort.obj ..\..\_temp\CV$(DR)\cvHMM.obj \
..\..\_temp\CV$(DR)\cvHMMObs.obj ..\..\_temp\CV$(DR)\cvHMMWrap.obj \
..\..\_temp\CV$(DR)\cvSwitcher.obj ..\..\_temp\CV$(DR)\cvaffine.obj \
..\..\_temp\CV$(DR)\cvarithm.obj ..\..\_temp\CV$(DR)\cvarray.obj \
..\..\_temp\CV$(DR)\cvcolor.obj ..\..\_temp\CV$(DR)\cvconvert.obj \
..\..\_temp\CV$(DR)\cvcopy.obj ..\..\_temp\CV$(DR)\cvlogic.obj \
..\..\_temp\CV$(DR)\cvrand.obj 


INC = ../Include/CV.h ../Include/CV.hpp ../include/cvcompat.h ../include/Cverror.h \
../Include/CvPixelAccess.h ../Include/CvStorage.hpp ../Include/CVTypes.h \
../include/ipl.h ../include/iplerror.h ../include/iplmisc.h ../src/_CV.h \
../src/_cvarr.h ../src/_cvDataStructs.h ../src/_CvError.h ../src/_cvfuncn.h \
../src/_cvGeom.h ../src/_cvList.h ../src/_cvmatrix.h ../src/_cvMorphology.h \
../src/_cvoptions.h ../src/_cvtables.h ../src/_cvUtils.h ../src/_cvVM.h \
../src/_cvWrap.h ../src/_ipcv.h ../src/_optcv.h 

CXXFLAGS2 = /I"../include" /I"../src"  /nologo /GX /GB /W4 /I "$(VCHOME)/include"  "/Qwd171,424,981" /Qxi /Qaxi /c /Fo
LINKFLAGS2 = /libpath:..\..\lib /nologo /subsystem:windows /dll /pdb:none /machine:I386 /out:$(OUTDLL) /implib:$(OUTLIB) /nodefaultlib:libm /nodefaultlib:libirc /libpath:"$(VCHOME)/lib"  

!ifdef debug

CXXFLAGS = /D"CV_DLL" /D"WIN32" /D"_WINDOWS" /D"_DEBUG"  /Gm /Zi /Od /FD /GZ $(CXXFLAGS2)
LIBS = kernel32.lib user32.lib gdi32.lib 
LINKFLAGS = $(LINKFLAGS2) /debug 

!else

CXXFLAGS = /D"NDEBUG" /D"CV_DLL" /D"WIN32" /D"_WINDOWS"  /O2 /Ob2 $(CXXFLAGS2)
LIBS = kernel32.lib user32.lib gdi32.lib 
LINKFLAGS = $(LINKFLAGS2)  

!endif


$(OUTDLL): $(OBJS)
	-mkdir ..\..\bin 2>nul
	-mkdir ..\..\lib 2>nul
	$(LINK)  $(LINKFLAGS) $** $(LIBS) 
	

all: $(OUTDLL)

..\..\_temp\CV$(DR)\cvConvHull.obj: ..\src\cvConvHull.cpp $(INC)
	@-mkdir ..\..\_temp\CV$(DR) 2>nul
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvConvHull.obj ..\src\cvConvHull.cpp
..\..\_temp\CV$(DR)\cvEllipseFit.obj: ..\src\cvEllipseFit.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvEllipseFit.obj ..\src\cvEllipseFit.cpp
..\..\_temp\CV$(DR)\cvGeometry.obj: ..\src\cvGeometry.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvGeometry.obj ..\src\cvGeometry.cpp
..\..\_temp\CV$(DR)\cvGeometryWrap.obj: ..\src\cvGeometryWrap.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvGeometryWrap.obj ..\src\cvGeometryWrap.cpp
..\..\_temp\CV$(DR)\CvLineFit.obj: ..\src\CvLineFit.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\CvLineFit.obj ..\src\CvLineFit.cpp
..\..\_temp\CV$(DR)\CvProject.obj: ..\src\CvProject.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\CvProject.obj ..\src\CvProject.cpp
..\..\_temp\CV$(DR)\cvRotCalipers.obj: ..\src\cvRotCalipers.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvRotCalipers.obj ..\src\cvRotCalipers.cpp
..\..\_temp\CV$(DR)\cvSubdivision2D.obj: ..\src\cvSubdivision2D.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvSubdivision2D.obj ..\src\cvSubdivision2D.cpp
..\..\_temp\CV$(DR)\cvImage.obj: ..\src\cvImage.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvImage.obj ..\src\cvImage.cpp
..\..\_temp\CV$(DR)\camshift.obj: ..\src\camshift.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\camshift.obj ..\src\camshift.cpp
..\..\_temp\CV$(DR)\cvConDens.obj: ..\src\cvConDens.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvConDens.obj ..\src\cvConDens.cpp
..\..\_temp\CV$(DR)\cvKalman.obj: ..\src\cvKalman.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvKalman.obj ..\src\cvKalman.cpp
..\..\_temp\CV$(DR)\cvAdapThresh.obj: ..\src\cvAdapThresh.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvAdapThresh.obj ..\src\cvAdapThresh.cpp
..\..\_temp\CV$(DR)\cvThresh.obj: ..\src\cvThresh.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvThresh.obj ..\src\cvThresh.cpp
..\..\_temp\CV$(DR)\cvCalcCovarMatrix.obj: ..\src\cvCalcCovarMatrix.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvCalcCovarMatrix.obj ..\src\cvCalcCovarMatrix.cpp
..\..\_temp\CV$(DR)\cvJacobiEigens.obj: ..\src\cvJacobiEigens.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvJacobiEigens.obj ..\src\cvJacobiEigens.cpp
..\..\_temp\CV$(DR)\cvmathfuncs.obj: ..\src\cvmathfuncs.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvmathfuncs.obj ..\src\cvmathfuncs.cpp
..\..\_temp\CV$(DR)\cvmatmul.obj: ..\src\cvmatmul.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvmatmul.obj ..\src\cvmatmul.cpp
..\..\_temp\CV$(DR)\cvMatrix.obj: ..\src\cvMatrix.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvMatrix.obj ..\src\cvMatrix.cpp
..\..\_temp\CV$(DR)\cvMatrix64d.obj: ..\src\cvMatrix64d.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvMatrix64d.obj ..\src\cvMatrix64d.cpp
..\..\_temp\CV$(DR)\cvSvd.obj: ..\src\cvSvd.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvSvd.obj ..\src\cvSvd.cpp
..\..\_temp\CV$(DR)\cvMean.obj: ..\src\cvMean.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvMean.obj ..\src\cvMean.cpp
..\..\_temp\CV$(DR)\cvMeanSdv.obj: ..\src\cvMeanSdv.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvMeanSdv.obj ..\src\cvMeanSdv.cpp
..\..\_temp\CV$(DR)\cvMinMaxLoc.obj: ..\src\cvMinMaxLoc.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvMinMaxLoc.obj ..\src\cvMinMaxLoc.cpp
..\..\_temp\CV$(DR)\cvMoments.obj: ..\src\cvMoments.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvMoments.obj ..\src\cvMoments.cpp
..\..\_temp\CV$(DR)\cvNorm.obj: ..\src\cvNorm.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvNorm.obj ..\src\cvNorm.cpp
..\..\_temp\CV$(DR)\cvSumPixels.obj: ..\src\cvSumPixels.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvSumPixels.obj ..\src\cvSumPixels.cpp
..\..\_temp\CV$(DR)\cvCamShift.obj: ..\src\cvCamShift.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvCamShift.obj ..\src\cvCamShift.cpp
..\..\_temp\CV$(DR)\cvCalcContrastHistogram.obj: ..\src\cvCalcContrastHistogram.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvCalcContrastHistogram.obj ..\src\cvCalcContrastHistogram.cpp
..\..\_temp\CV$(DR)\cvEMD.obj: ..\src\cvEMD.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvEMD.obj ..\src\cvEMD.cpp
..\..\_temp\CV$(DR)\cvHistogram.obj: ..\src\cvHistogram.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvHistogram.obj ..\src\cvHistogram.cpp
..\..\_temp\CV$(DR)\cvApprox.obj: ..\src\cvApprox.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvApprox.obj ..\src\cvApprox.cpp
..\..\_temp\CV$(DR)\cvContourArea.obj: ..\src\cvContourArea.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvContourArea.obj ..\src\cvContourArea.cpp
..\..\_temp\CV$(DR)\cvContours.obj: ..\src\cvContours.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvContours.obj ..\src\cvContours.cpp
..\..\_temp\CV$(DR)\cvContoursMoments.obj: ..\src\cvContoursMoments.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvContoursMoments.obj ..\src\cvContoursMoments.cpp
..\..\_temp\CV$(DR)\cvContourTree.obj: ..\src\cvContourTree.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvContourTree.obj ..\src\cvContourTree.cpp
..\..\_temp\CV$(DR)\cvDominants.obj: ..\src\cvDominants.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvDominants.obj ..\src\cvDominants.cpp
..\..\_temp\CV$(DR)\cvMatchContours.obj: ..\src\cvMatchContours.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvMatchContours.obj ..\src\cvMatchContours.cpp
..\..\_temp\CV$(DR)\cvPGH.obj: ..\src\cvPGH.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvPGH.obj ..\src\cvPGH.cpp
..\..\_temp\CV$(DR)\cvShapeDescr.obj: ..\src\cvShapeDescr.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvShapeDescr.obj ..\src\cvShapeDescr.cpp
..\..\_temp\CV$(DR)\cvMoTempl.obj: ..\src\cvMoTempl.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvMoTempl.obj ..\src\cvMoTempl.cpp
..\..\_temp\CV$(DR)\cvMotSeg.obj: ..\src\cvMotSeg.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvMotSeg.obj ..\src\cvMotSeg.cpp
..\..\_temp\CV$(DR)\cvDrawing.obj: ..\src\cvDrawing.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvDrawing.obj ..\src\cvDrawing.cpp
..\..\_temp\CV$(DR)\cvOutText.obj: ..\src\cvOutText.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvOutText.obj ..\src\cvOutText.cpp
..\..\_temp\CV$(DR)\cvAlloc.obj: ..\src\cvAlloc.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvAlloc.obj ..\src\cvAlloc.cpp
..\..\_temp\CV$(DR)\cverror.obj: ..\src\cverror.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cverror.obj ..\src\cverror.cpp
..\..\_temp\CV$(DR)\cvprecomp.obj: ..\src\cvprecomp.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvprecomp.obj ..\src\cvprecomp.cpp
..\..\_temp\CV$(DR)\cvSamplers.obj: ..\src\cvSamplers.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvSamplers.obj ..\src\cvSamplers.cpp
..\..\_temp\CV$(DR)\cvtables.obj: ..\src\cvtables.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvtables.obj ..\src\cvtables.cpp
..\..\_temp\CV$(DR)\cvTemplMatch.obj: ..\src\cvTemplMatch.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvTemplMatch.obj ..\src\cvTemplMatch.cpp
..\..\_temp\CV$(DR)\cvUtilitiesWrap.obj: ..\src\cvUtilitiesWrap.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvUtilitiesWrap.obj ..\src\cvUtilitiesWrap.cpp
..\..\_temp\CV$(DR)\cvutils.obj: ..\src\cvutils.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvutils.obj ..\src\cvutils.cpp
..\..\_temp\CV$(DR)\cvDisTransform.obj: ..\src\cvDisTransform.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvDisTransform.obj ..\src\cvDisTransform.cpp
..\..\_temp\CV$(DR)\cvHough.obj: ..\src\cvHough.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvHough.obj ..\src\cvHough.cpp
..\..\_temp\CV$(DR)\cvHoughDiv.obj: ..\src\cvHoughDiv.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvHoughDiv.obj ..\src\cvHoughDiv.cpp
..\..\_temp\CV$(DR)\cvHoughP.obj: ..\src\cvHoughP.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvHoughP.obj ..\src\cvHoughP.cpp
..\..\_temp\CV$(DR)\cvHoughWrap.obj: ..\src\cvHoughWrap.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvHoughWrap.obj ..\src\cvHoughWrap.cpp
..\..\_temp\CV$(DR)\cvPOSIT.obj: ..\src\cvPOSIT.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvPOSIT.obj ..\src\cvPOSIT.cpp
..\..\_temp\CV$(DR)\cvSnakes.obj: ..\src\cvSnakes.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvSnakes.obj ..\src\cvSnakes.cpp
..\..\_temp\CV$(DR)\cvLkPyramid.obj: ..\src\cvLkPyramid.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvLkPyramid.obj ..\src\cvLkPyramid.cpp
..\..\_temp\CV$(DR)\cvOptFlowBM.obj: ..\src\cvOptFlowBM.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvOptFlowBM.obj ..\src\cvOptFlowBM.cpp
..\..\_temp\CV$(DR)\cvOptFlowHS.obj: ..\src\cvOptFlowHS.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvOptFlowHS.obj ..\src\cvOptFlowHS.cpp
..\..\_temp\CV$(DR)\cvOptFlowLK.obj: ..\src\cvOptFlowLK.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvOptFlowLK.obj ..\src\cvOptFlowLK.cpp
..\..\_temp\CV$(DR)\cvDataStructs.obj: ..\src\cvDataStructs.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvDataStructs.obj ..\src\cvDataStructs.cpp
..\..\_temp\CV$(DR)\cvCalcCovarMatrixEx.obj: ..\src\cvCalcCovarMatrixEx.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvCalcCovarMatrixEx.obj ..\src\cvCalcCovarMatrixEx.cpp
..\..\_temp\CV$(DR)\cvCalcEigenObjects.obj: ..\src\cvCalcEigenObjects.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvCalcEigenObjects.obj ..\src\cvCalcEigenObjects.cpp
..\..\_temp\CV$(DR)\cvEigenDecomposite.obj: ..\src\cvEigenDecomposite.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvEigenDecomposite.obj ..\src\cvEigenDecomposite.cpp
..\..\_temp\CV$(DR)\cvEigenObjectsWrap.obj: ..\src\cvEigenObjectsWrap.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvEigenObjectsWrap.obj ..\src\cvEigenObjectsWrap.cpp
..\..\_temp\CV$(DR)\cvEigenProjection.obj: ..\src\cvEigenProjection.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvEigenProjection.obj ..\src\cvEigenProjection.cpp
..\..\_temp\CV$(DR)\cvMorph.obj: ..\src\cvMorph.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvMorph.obj ..\src\cvMorph.cpp
..\..\_temp\CV$(DR)\cvMorphWrap.obj: ..\src\cvMorphWrap.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvMorphWrap.obj ..\src\cvMorphWrap.cpp
..\..\_temp\CV$(DR)\cvpyramids.obj: ..\src\cvpyramids.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvpyramids.obj ..\src\cvpyramids.cpp
..\..\_temp\CV$(DR)\cvPyrSegmentation.obj: ..\src\cvPyrSegmentation.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvPyrSegmentation.obj ..\src\cvPyrSegmentation.cpp
..\..\_temp\CV$(DR)\cvFloodFill.obj: ..\src\cvFloodFill.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvFloodFill.obj ..\src\cvFloodFill.cpp
..\..\_temp\CV$(DR)\cvCalcImageHomography.obj: ..\src\cvCalcImageHomography.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvCalcImageHomography.obj ..\src\cvCalcImageHomography.cpp
..\..\_temp\CV$(DR)\cvCalcProbDensity.obj: ..\src\cvCalcProbDensity.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvCalcProbDensity.obj ..\src\cvCalcProbDensity.cpp
..\..\_temp\CV$(DR)\cvCreateHandMask.obj: ..\src\cvCreateHandMask.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvCreateHandMask.obj ..\src\cvCreateHandMask.cpp
..\..\_temp\CV$(DR)\cvFindHandRegion.obj: ..\src\cvFindHandRegion.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvFindHandRegion.obj ..\src\cvFindHandRegion.cpp
..\..\_temp\CV$(DR)\cvGestureRecognition.obj: ..\src\cvGestureRecognition.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvGestureRecognition.obj ..\src\cvGestureRecognition.cpp
..\..\_temp\CV$(DR)\cvMaxRect.obj: ..\src\cvMaxRect.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvMaxRect.obj ..\src\cvMaxRect.cpp
..\..\_temp\CV$(DR)\cvCorrespond.obj: ..\src\cvCorrespond.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvCorrespond.obj ..\src\cvCorrespond.cpp
..\..\_temp\CV$(DR)\cvFundam.obj: ..\src\cvFundam.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvFundam.obj ..\src\cvFundam.cpp
..\..\_temp\CV$(DR)\cvLines.obj: ..\src\cvLines.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvLines.obj ..\src\cvLines.cpp
..\..\_temp\CV$(DR)\cvLMedS.obj: ..\src\cvLMedS.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvLMedS.obj ..\src\cvLMedS.cpp
..\..\_temp\CV$(DR)\cvMorphing.obj: ..\src\cvMorphing.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvMorphing.obj ..\src\cvMorphing.cpp
..\..\_temp\CV$(DR)\cvPrewarp.obj: ..\src\cvPrewarp.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvPrewarp.obj ..\src\cvPrewarp.cpp
..\..\_temp\CV$(DR)\cvScanlines.obj: ..\src\cvScanlines.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvScanlines.obj ..\src\cvScanlines.cpp
..\..\_temp\CV$(DR)\cvBlur.obj: ..\src\cvBlur.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvBlur.obj ..\src\cvBlur.cpp
..\..\_temp\CV$(DR)\cvConvGen.obj: ..\src\cvConvGen.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvConvGen.obj ..\src\cvConvGen.cpp
..\..\_temp\CV$(DR)\cvFilterWr.obj: ..\src\cvFilterWr.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvFilterWr.obj ..\src\cvFilterWr.cpp
..\..\_temp\CV$(DR)\cvInitConvol.obj: ..\src\cvInitConvol.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvInitConvol.obj ..\src\cvInitConvol.cpp
..\..\_temp\CV$(DR)\cvLaplace.obj: ..\src\cvLaplace.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvLaplace.obj ..\src\cvLaplace.cpp
..\..\_temp\CV$(DR)\cvScharr.obj: ..\src\cvScharr.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvScharr.obj ..\src\cvScharr.cpp
..\..\_temp\CV$(DR)\cvAbsDiff.obj: ..\src\cvAbsDiff.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvAbsDiff.obj ..\src\cvAbsDiff.cpp
..\..\_temp\CV$(DR)\cvAccum.obj: ..\src\cvAccum.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvAccum.obj ..\src\cvAccum.cpp
..\..\_temp\CV$(DR)\cvCanny.obj: ..\src\cvCanny.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvCanny.obj ..\src\cvCanny.cpp
..\..\_temp\CV$(DR)\cvCorner.obj: ..\src\cvCorner.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvCorner.obj ..\src\cvCorner.cpp
..\..\_temp\CV$(DR)\cvCornerSubPix.obj: ..\src\cvCornerSubPix.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvCornerSubPix.obj ..\src\cvCornerSubPix.cpp
..\..\_temp\CV$(DR)\cvDetectWr.obj: ..\src\cvDetectWr.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvDetectWr.obj ..\src\cvDetectWr.cpp
..\..\_temp\CV$(DR)\cvfeatureselect.obj: ..\src\cvfeatureselect.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvfeatureselect.obj ..\src\cvfeatureselect.cpp
..\..\_temp\CV$(DR)\cvMinEVal.obj: ..\src\cvMinEVal.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvMinEVal.obj ..\src\cvMinEVal.cpp
..\..\_temp\CV$(DR)\cvPreCorner.obj: ..\src\cvPreCorner.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvPreCorner.obj ..\src\cvPreCorner.cpp
..\..\_temp\CV$(DR)\cvCalibInit.obj: ..\src\cvCalibInit.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvCalibInit.obj ..\src\cvCalibInit.cpp
..\..\_temp\CV$(DR)\cvCalibration.obj: ..\src\cvCalibration.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvCalibration.obj ..\src\cvCalibration.cpp
..\..\_temp\CV$(DR)\cvUnDistort.obj: ..\src\cvUnDistort.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvUnDistort.obj ..\src\cvUnDistort.cpp
..\..\_temp\CV$(DR)\cvHMM.obj: ..\src\cvHMM.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvHMM.obj ..\src\cvHMM.cpp
..\..\_temp\CV$(DR)\cvHMMObs.obj: ..\src\cvHMMObs.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvHMMObs.obj ..\src\cvHMMObs.cpp
..\..\_temp\CV$(DR)\cvHMMWrap.obj: ..\src\cvHMMWrap.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvHMMWrap.obj ..\src\cvHMMWrap.cpp
..\..\_temp\CV$(DR)\cvSwitcher.obj: ..\src\cvSwitcher.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvSwitcher.obj ..\src\cvSwitcher.cpp
..\..\_temp\CV$(DR)\cvaffine.obj: ..\src\cvaffine.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvaffine.obj ..\src\cvaffine.cpp
..\..\_temp\CV$(DR)\cvarithm.obj: ..\src\cvarithm.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvarithm.obj ..\src\cvarithm.cpp
..\..\_temp\CV$(DR)\cvarray.obj: ..\src\cvarray.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvarray.obj ..\src\cvarray.cpp
..\..\_temp\CV$(DR)\cvcolor.obj: ..\src\cvcolor.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvcolor.obj ..\src\cvcolor.cpp
..\..\_temp\CV$(DR)\cvconvert.obj: ..\src\cvconvert.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvconvert.obj ..\src\cvconvert.cpp
..\..\_temp\CV$(DR)\cvcopy.obj: ..\src\cvcopy.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvcopy.obj ..\src\cvcopy.cpp
..\..\_temp\CV$(DR)\cvlogic.obj: ..\src\cvlogic.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvlogic.obj ..\src\cvlogic.cpp
..\..\_temp\CV$(DR)\cvrand.obj: ..\src\cvrand.cpp $(INC)
	-$(CXX) $(CXXFLAGS)..\..\_temp\CV$(DR)\cvrand.obj ..\src\cvrand.cpp

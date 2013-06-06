/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                        Intel License Agreement
//                For Open Source Computer Vision Library
//
// Copyright (C) 2000, Intel Corporation, all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of Intel Corporation may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Intel Corporation or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/#if !defined(_GESTURE_RECOGNIZER_H_)
#define _GESTURE_RECOGNIZER_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable:4786)


#if defined(GESTREC_EXPORTS)
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

// FindHandCtl.h : Declaration of the CFindHandCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CFindHandCtrl : See FindHandCtl.cpp for implementation.

#define GR_NOTHING 0
#define GR_TRAIN 1
#define GR_RECOGNIZE 2
#define GR_RESEACH 1
#define GR_LINE
//#define GR_CONTOUR
//#define GR_IMPROVING     // improving of the initial hand mask by the using previous result hand mask

#include "cv.h"

#include <vector>
using namespace std;

typedef vector<CvHuMoments> feature_vector;
typedef vector<float> fvector;
typedef struct _gr_pose : public fvector
{
    __int64 time;
    CvHuMoments pose;
} gr_pose;

class DLL_EXPORT CFindHandCtrl
{
// Constructor
public:
	CFindHandCtrl();
	~CFindHandCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindHandCtrl)
	public:
/*	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);*/
	//}}AFX_VIRTUAL

// Implementation
public:

	/* Some user stuff*/
	vector<feature_vector> m_features;
	feature_vector m_avgs;
    vector<string> m_gestureNames;
	vector<fvector> m_covMatrices;
    vector<bool> m_isCovMatCalculated;
	long m_gestureCode;

    vector<IplImage*> m_dgMasks;
    vector<gr_pose> m_geomParams;

	long m_minPointCount;
	CvPoint3D32f* m_pointCloudBuffer;
	long m_pointCount;
	long m_handImage;
	long m_errNo;
	string m_errString;
	long m_rawImage;
	long m_task;
	string m_path;
	BOOL m_dynamicGesture;
	string m_dGestureName;
    string GetGestureName();
    void SetGestureName(std::string name);
    BOOL m_dynGestureFixed;
    BOOL m_saveDynGest;
        	
	long GetGestureCode();
	void SetGestureCode(long nNewValue);
	long GetRecognizedCode();
	void SetRecognizedCode(long nNewValue);
	BOOL FitLine();
	BOOL FindHand(_int64 _time, BOOL ForCenterOnly);
	BOOL LoadGestures(LPCTSTR FileName);
	BOOL SaveGestures(LPCTSTR FileName);
	void UpdateDynGest();

public:
	CvMemStorage* m_storage;
	void StoreDynGesture(IplImage* mask_rez, __int64 _time);
	string GetRecognizedName();
	string m_recognizedGesture;
	int m_segThresh;
	int m_trainFrameCount;
	IplImage* m_mask;
	void ClearGesture(string name);
    BOOL IsGestureFixed() {return m_dynGestureFixed; }
    void ReleaseFixedGesture() { m_dynGestureFixed = FALSE; ClearDynGest(); }
    	
	void SetTask(long task);
	BOOL m_staticGesture;
	float m_center[3];
	IplImage* m_disparityImage;
	IplImage* m_outputImage;
	IplImage* m_inputImage;
	float m_line[6];
	void SetPointBuffer(CvPoint3D32f* buffer);
	//int m_dgFrameCount;
    BOOL m_dgFrameFound;
	BOOL _FindHand(_int64 _time, BOOL ForCenterOnly);
	BOOL _RectifyInputMask(BOOL ForCenterOnly);
	void CalculateCovarianceMatrix();

	int m_maskImprovigFlag;   // flag for the initial mask improving (0 for default) 
	int m_convexDefCount;     // counter of the convexity defects  
	vector<float> m_DefectsDepth; 

private:
	long m_time;
	void ClearDynGest();
	int m_dgFrameThreshold;
	string m_num;
    BOOL InitModulePath();
	FILE* m_dgHandle;
	void SaveDynGestures();

	float* m_linePre;
	IplImage* m_maskPre;  // pointer to the previous initial hand mask 
	IplImage* m_resPre;   // pointer to the previous result hand mask 
	
	int m_gestureIndex;
	string Recognize(IplImage* image);

	string LogClassification();  //  logical classification of the static gestures

	long m_recognizedCode;
	CvHuMoments CalculateHuMoments(IplImage* image);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_GESTURE_RECOGNIZER_H_)

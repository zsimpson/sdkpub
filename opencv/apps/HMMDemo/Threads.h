#ifndef __THREADS_H__
#define __THREADS_H__

//#include "stdafx.h"
#include "FaceBase.h"
#include "HMMDemoDoc.h"
#include "MainFrm.h"

//#ifndef _WINDOWS_
    //#include <windows.h>
//#endif

struct StartTrainParams {
    CHMMDemoDoc* doc;
    int flag;
    CMainFrame* frame;
};

extern HANDLE g_hevtWakeUpControlThread;
extern CRITICAL_SECTION g_critSect;

extern DWORD dwCtrlTrainThread;
extern HANDLE hCtrlTrainThread;

bool startTrain( CHMMDemoDoc* doc, CMainFrame* frame, int flag );
DWORD ctrlTrainThreadFunc( LPVOID param );

bool recognizeThread(CImage& image, CRect rect, /*HWND hwnd,*/
                            CFaceBase& base, CImageBaseView* baseview);

#endif // if !defined __THREADS_H__
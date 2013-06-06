#include "stdafx.h"
#include "Threads.h"
#include "facebase.h"
#include <afxtempl.h>
#include <float.h>

#include "image.h"

//#include "cv.h"

//#include "HMMDemo.h"
//#include "FaceBase.h"
//#include "direct.h"

#include "multiprocdiv.h"

#define NONE_FINISH_WORK -1
#define BRAKE_WORK -2

//#define PRIOR //
#define PRIOR

#define CHECK_TRAIN_FOR_BREAK(mac_thrArr,mac_thrParams,mac_numProc) \
    if( thrFinishWork == BRAKE_WORK ) { \
        int mac_i; \
        POSITION pos; \
        for( mac_i = 0; mac_i < mac_numProc; mac_i ++ ) { \
            if( mac_thrParams[mac_i].working == true ) { \
                mac_thrParams[mac_i].doNext = false; \
                ResumeThread( mac_thrArr[mac_i] ); \
                Sleep(50); \
            } \
        } \
        for( pos = base.GetPersonList().GetHeadPosition(); pos;  ) \
        { \
            CPerson* person = base.GetPersonList().GetNext( pos ); \
            person->SetTrainFlag( false ); \
        } \
        Sleep( 5000 ); \
        for( mac_i = 0; mac_i < mac_numProc; mac_i ++ ) { \
            if( mac_thrParams[mac_i].working == true ) { \
                char buf[256]; \
                _RPT1( _CRT_WARN, "Terminating thread #%d\n", mac_i ); \
                if( !TerminateThread( mac_thrArr[mac_i], 1 ) ) { \
                    FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM, 0, GetLastError(), 0, buf, 256, 0 ); \
                    _RPT1( _CRT_WARN, "TerminateThread returned: %s\n", buf ); \
                } \
                else { \
                    FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM, 0, GetLastError(), 0, buf, 256, 0 ); \
                    _RPT1( _CRT_WARN, "TerminateThread returned: %s\n", buf ); \
                } \
                WaitForSingleObject( mac_thrArr[mac_i], 3000 ); \
            } \
        } \
        base.DeleteHMMInfo(); \
        CloseHandle( g_hevtWakeUpControlThread ); \
        DeleteCriticalSection( &g_critSect ); \
        hCtrlTrainThread = 0; \
        trainParam.frame->EnableItemsAfterTrain(); \
        ExitThread(0); \
    }

#define CHECK_TRAIN_FOR_BREAK1(mac_thrArr,mac_thrParams,mac_numProc) \
    if( thrFinishWork == BRAKE_WORK ) { \
        int mac_i; \
        for( mac_i = 0; mac_i < mac_numProc; mac_i ++ ) { \
            if( mac_thrParams[mac_i].working == true ) { \
                mac_thrParams[mac_i].doNext = false; \
                ResumeThread( mac_thrArr[mac_i] ); \
            } \
        } \
        Sleep( 5000 ); \
        for( mac_i = 0; mac_i < mac_numProc; mac_i ++ ) { \
            if( mac_thrParams[mac_i].working == true ) { \
                char buf[256]; \
                _RPT1( _CRT_WARN, "Terminating thread #%d\n", mac_i ); \
                if( !TerminateThread( mac_thrArr[mac_i], 1 ) ) { \
                    FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM, 0, GetLastError(), 0, buf, 256, 0 ); \
                    _RPT1( _CRT_WARN, "TerminateThread returned: %s\n", buf ); \
                } \
                else { \
                    FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM, 0, GetLastError(), 0, buf, 256, 0 ); \
                    _RPT1( _CRT_WARN, "TerminateThread returned: %s\n", buf ); \
                } \
                WaitForSingleObject( mac_thrArr[mac_i], 30 ); \
            } \
        } \
        CloseHandle( g_hevtWakeUpControlThread ); \
        DeleteCriticalSection( &g_critSect ); \
        hCtrlTrainThread = 0; \
        ExitThread(0); \
    }

struct TrainThreadParams {
    int threadNum;
    CPerson* person;
    int doNext;
    HANDLE hThread;
    bool working;
};

HANDLE g_hevtWakeUpControlThread;
CRITICAL_SECTION g_critSect;

DWORD dwCtrlTrainThread;
HANDLE hCtrlTrainThread;

volatile int thrFinishWork;

StartTrainParams trainParam;

//DWORD WINAPI ThreadProc(
//  LPVOID lpParameter   // thread data
//);
 
DWORD trainFunc( LPVOID param )
{
    TrainThreadParams* thrParams = (TrainThreadParams*)param;
    int threadNum = thrParams->threadNum;
    HANDLE hThread = thrParams->hThread;
    CPerson* person;
    int anotherThrBlocksVar;

    InterlockedExchange( (long*)&(thrParams->working), (int)true );

    while( thrParams->doNext )
    {
        person = thrParams->person;

        _RPT1( _CRT_WARN, "Thread #%d begins\n", threadNum );

        EnterCriticalSection( &g_critSect );
            person->LoadRest();
        LeaveCriticalSection( &g_critSect );

        person->TrainHMM();
        person->UnloadRest();

        if( !thrParams->doNext ) {
            break;
        }


        _RPT1( _CRT_WARN, "Thread #%d ends\n", threadNum );

        EnterCriticalSection( &g_critSect );
            thrParams->doNext = false;
            anotherThrBlocksVar = true;
            while( anotherThrBlocksVar )
            {
                if( thrFinishWork == NONE_FINISH_WORK ) {
                    thrFinishWork = threadNum;
                    anotherThrBlocksVar = false;
                }
                else {
                    LeaveCriticalSection( &g_critSect );
                        Sleep(0);
                    EnterCriticalSection( &g_critSect );
                }
            }

            _RPT1( _CRT_WARN, "Thread #%d sets event\n", threadNum );

            SetEvent( g_hevtWakeUpControlThread );
        LeaveCriticalSection( &g_critSect );

        _RPT1( _CRT_WARN, "Thread #%d suspends\n", threadNum );

        SuspendThread( hThread );

        Sleep(0);

        _RPT1( _CRT_WARN, "Thread #%d resumes\n", threadNum );
    } // while( thrParams->doNext )

    _RPT1( _CRT_WARN, "Thread #%d finishes\n", threadNum );

    InterlockedExchange( (long*)&(thrParams->working), (int)false );
    return 0;
} // trainFunc

DWORD ctrlTrainThreadFunc( LPVOID param )
{
    SYSTEM_INFO sysInfo;
    int numProc;
    int i;
    DWORD dwTrainThread[32];
    HANDLE hTrainThread[32];
    TrainThreadParams thrParams[32];
    DWORD affMask = 0;
    POSITION pos;
    CPerson* person;
    
    InitializeCriticalSection( &g_critSect );
    g_hevtWakeUpControlThread = CreateEvent( 0, true, false, "WakeUpCtrlTrainThread" );

    GetSystemInfo( &sysInfo );
    numProc = sysInfo.dwNumberOfProcessors;

    numProc = 32;

    if( numProc > 32 ) {
        CloseHandle( g_hevtWakeUpControlThread );
        DeleteCriticalSection( &g_critSect );
        hCtrlTrainThread = 0;
        return 0;
    }

    trainParam.frame->DisableItemsForTrain();


    if( numProc == 1 )
    {
        // Single processor code
        CHMMDemoDoc* doc = ( (StartTrainParams*)param )->doc;
        if( !doc )
            return 0;
        CFaceBase& base = doc->GetFaceBase();
        base.TrainAll( ( (StartTrainParams*)param )->flag );
    }
    else {
        // Multiple processor code
        CHMMDemoDoc* doc = ( (StartTrainParams*)param )->doc;
        if( !doc )
            ExitThread(0);
        CFaceBase& base = doc->GetFaceBase();

        affMask = 0;
        for( i = 0; i < numProc; i ++ )
        {
            affMask |= ( 1 << i );
        }
        for( i = 0; i < numProc; i ++ )
        {
            thrParams[i].threadNum = i;
            thrParams[i].working = true;
            hTrainThread[i] = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)trainFunc, &(thrParams[i]), CREATE_SUSPENDED, &(dwTrainThread[i]) );
            thrParams[i].hThread = hTrainThread[i];
            thrParams[i].doNext = false;
            PRIOR SetThreadPriority( hTrainThread[i], THREAD_PRIORITY_BELOW_NORMAL );
            //SetThreadAffinityMask( hTrainThread[i], affMask );
            //SetThreadIdealProcessor( hTrainThread[i], (DWORD)i );
        }

        thrFinishWork = NONE_FINISH_WORK;
        ResetEvent( g_hevtWakeUpControlThread );
        for( i = 0, pos = base.GetPersonList().GetHeadPosition(); pos; )
        {
            person = base.GetPersonList().GetNext(pos);

            _RPT2( _CRT_WARN, "%s %d\n", "pos = ", (int)pos );

            if( (( (StartTrainParams*)param )->flag == TRAIN_UNTRAINED) && person->IsTrained() ) continue;
        
            EnterCriticalSection( &g_critSect );

                _RPT1( _CRT_WARN, "Giving execute to thread #%d\n", i );

                thrParams[i].person = person;
                thrParams[i].doNext = true;
            LeaveCriticalSection( &g_critSect );

            _RPT1( _CRT_WARN, "Resuming thread #%d\n", i );

            ResumeThread( hTrainThread[i] );
            i ++;
            if( i == numProc ) {
                break;
            }
        }
        if( i != numProc ) {
            while( i > 0 ) {
                WaitForSingleObject( g_hevtWakeUpControlThread, INFINITE );
                CHECK_TRAIN_FOR_BREAK( hTrainThread, thrParams, numProc );

                _RPT1( _CRT_WARN, "Main thread gets last event from thread #%d\n", thrFinishWork );

                EnterCriticalSection( &g_critSect );
                    ResetEvent( g_hevtWakeUpControlThread );
                    thrParams[ thrFinishWork ].doNext = false;

                    _RPT1( _CRT_WARN, "Resuming thread #%d\n", thrFinishWork );

                    ResumeThread( hTrainThread[ thrFinishWork ] );
                    thrFinishWork = NONE_FINISH_WORK;
                    i --;
                LeaveCriticalSection( &g_critSect );
            }
        } // if( i == numProc )
        else {
            i = base.GetPersonList().GetCount() - numProc;
            while( i > 0 ) {
                WaitForSingleObject( g_hevtWakeUpControlThread, INFINITE );
                CHECK_TRAIN_FOR_BREAK( hTrainThread, thrParams, numProc );

                _RPT0( _CRT_WARN, "Main thread gets event\n" );

                EnterCriticalSection( &g_critSect );
                    ResetEvent( g_hevtWakeUpControlThread );
                    person = base.GetPersonList().GetNext(pos);

                    _RPT1( _CRT_WARN, "pos = %d\n", (int)pos );

                    while( pos && person->IsTrained() ) {
                        if( (( (StartTrainParams*)param )->flag != TRAIN_UNTRAINED) ) {
                            person = base.GetPersonList().GetNext(pos);
                            i --;
                        }
                    }
        
                    if( person ) {

                        _RPT1( _CRT_WARN, "Giving execute to thread #%d\n", thrFinishWork );

                        thrParams[ thrFinishWork ].person = person;
                        thrParams[ thrFinishWork ].doNext = true;

                        _RPT1( _CRT_WARN, "Resuming thread #%d\n", thrFinishWork );

                        ResumeThread( hTrainThread[ thrFinishWork ] );
                        thrFinishWork = NONE_FINISH_WORK;
                        i --;
                    }
                LeaveCriticalSection( &g_critSect );

                _RPT1( _CRT_WARN, "i = %d\n", i );

                //WaitForSingleObject( g_hevtWakeUpControlThread, INFINITE );
            } // while( i > 0 )

            for( i = 0; i < numProc; i ++ ) {

                int thrNum;
                DWORD resumeRes;

                WaitForSingleObject( g_hevtWakeUpControlThread, INFINITE );
                CHECK_TRAIN_FOR_BREAK( hTrainThread, thrParams, numProc );

                _RPT1( _CRT_WARN, "Main thread gets last event from thread #%d\n", thrFinishWork );
            
                EnterCriticalSection( &g_critSect );
                    ResetEvent( g_hevtWakeUpControlThread );
                    thrNum = thrFinishWork;
                    thrParams[thrNum].doNext = false;

                    _RPT1( _CRT_WARN, "Resuming thread #%d\n", thrFinishWork );

                    resumeRes = ResumeThread( hTrainThread[thrNum] );
                    thrFinishWork = NONE_FINISH_WORK;
                LeaveCriticalSection( &g_critSect );

                _RPT1( _CRT_WARN, "Waiting for finishing thread #%d\n", thrNum );

                while( !resumeRes ) {
                    resumeRes = ResumeThread( hTrainThread[thrNum] );
                }
                WaitForSingleObject( hTrainThread[thrNum], INFINITE );
            }

        } // if( i == numProc ) else
        for( i = 0; i < numProc; i ++ )
        {
            thrParams[i].doNext = false;
            if( thrParams[i].working == true ) {

                _RPT1( _CRT_WARN, "Resuming thread #%d\n", i );

                while( !ResumeThread( hTrainThread[i] ) && thrParams[i].working == true ) {
                    Sleep(0);
                }

                _RPT1( _CRT_WARN, "Waiting for finishing thread #%d\n", i );

                WaitForSingleObject( hTrainThread[i], INFINITE );
            }
        }
        base.Save();
    } // if( numProc == 1 )


    _RPT0( _CRT_WARN, "Main thread: All is Ok!\n" );

    CloseHandle( g_hevtWakeUpControlThread );
    DeleteCriticalSection( &g_critSect );
    hCtrlTrainThread = 0;
    trainParam.frame->EnableItemsAfterTrain();
    return 0;
} // ctrlTrainThreadFunc

bool startTrain( CHMMDemoDoc* doc, CMainFrame* frame, int flag )
{
    static bool trainingStartsFirstTime = true;
    bool anotherThrBlocksVar;

    if( trainingStartsFirstTime ) {
        trainingStartsFirstTime = false;
        hCtrlTrainThread = 0;
    }

    if( hCtrlTrainThread ) {
        EnterCriticalSection( &g_critSect );
            anotherThrBlocksVar = true;
            while( anotherThrBlocksVar )
            {
                if( thrFinishWork == NONE_FINISH_WORK ) {
                    thrFinishWork = BRAKE_WORK;
                    anotherThrBlocksVar = false;
                }
                else {
                    LeaveCriticalSection( &g_critSect );
                        Sleep(0);
                    EnterCriticalSection( &g_critSect );
                }
            }

            _RPT0( _CRT_WARN, "Main thread sets break event\n" );

            SetEvent( g_hevtWakeUpControlThread );
        LeaveCriticalSection( &g_critSect );
    }
    else {
        trainParam.doc = doc;
        trainParam.frame = frame;
        trainParam.flag = flag;

        hCtrlTrainThread = CreateThread( NULL, 0,
            (LPTHREAD_START_ROUTINE)ctrlTrainThreadFunc, &trainParam, 0, &dwCtrlTrainThread );
        PRIOR SetThreadPriority( hCtrlTrainThread, THREAD_PRIORITY_BELOW_NORMAL );
    }

    return true;
}





struct InputRecogChildThread {
    INPUT_STRUCT_COMMON_PARAMS();
    CvEHMM* hmm;
    CvImgObsInfo* info;
    float* like_array;
};

struct InputCtrlChildThread {
    CFaceBase* faceBase;
    CImage* image;
    CRect rect;
    //HWND hwnd;
    CFaceBase* base;
    CImageBaseView* baseview;
};

COMMON_GLOBAL_VARS(recognizeThread,InputCtrlChildThread);


/*struct InputRecogChildThread {
    int threadNum; bool doNext; HANDLE hThread; bool working;
    CvEHMM* hmm;
    CvImgObsInfo* info;
    float* like_array;
};

struct InputCtrlChildThread {
    CFaceBase* faceBase;
    CImage* image;
    CRect rect;
    //HWND hwnd;
    CFaceBase* base;
    CImageBaseView* baseview;
};

CRITICAL_SECTION recognizeThreadCritSect; HANDLE recognizeThreadEvent; volatile int recognizeThreadMessage; HANDLE recognizeThreadThreadHandle; InputCtrlChildThread recognizeThreadInputStruct;
*/

// recognize child thread function
BEGIN_CHILD_THREAD_FUNCTION(recognizeThread,InputRecogChildThread);
    BEGIN_CHILD_THREAD_CORE();
        cvEstimateObsProb( params->info, params->hmm );
        *(params->like_array) = cvEViterbi( params->info, params->hmm );
    END_CHILD_THREAD_CORE();
END_CHILD_THREAD_FUNCTION();


// recognize control thread function
BEGIN_CTRL_THREAD_FUNCTION(recognizeThread,InputCtrlChildThread,InputRecogChildThread,0,0,0);
    int ranged[3];

    if ( params->rect == CRect( 0,0,0,0 ) )
    {
        params->rect.bottom = params->image->Height();
        params->rect.right = params->image->Width();
    }

    float like_array[1000]; ASSERT( params->faceBase->GetPersonList().GetCount() < 1000 );
    
    CImage gray_img;
    gray_img.CopyOf( *(params->image), 0 );
             
    IplImage* ipl = gray_img.GetImage();
    IplROI ipl_roi;
    ipl_roi.coi = 0;
    ipl_roi.xOffset = params->rect.left;
    ipl_roi.yOffset = params->rect.top;
    ipl_roi.height = params->rect.Height();
    ipl_roi.width = params->rect.Width();
    ipl->roi = &ipl_roi;
           
    int code = 1;

      bool doRescale = false;
        
        int new_height = 0;
        int new_width = 0; 
 
        if ( params->faceBase->m_useWidth )
        {
            doRescale = true;
            new_width = params->faceBase->m_scaleWidth;
        }
        if ( params->faceBase->m_useHeight )
        {
            doRescale = true;
            new_height = params->faceBase->m_scaleHeight;
        }
        //recompute width or height if any is absent
        IplImage* ipl_scaled;
        if ( doRescale )
        {
            if ( !new_width )
            {
                new_width  = new_height * ipl->roi->width / ipl->roi->height;
            }
            else if ( !new_height ) 
            {
                new_height  = new_width * ipl->roi->height / ipl->roi->width;
            }

            //rescale
            ipl_scaled = cvCreateImage( cvSize( new_width, new_height ), IPL_DEPTH_8U, 1 );
                
            iplResizeFit(ipl, ipl_scaled, /*ipl_scaled->width, ipl->width, 
                      ipl_scaled->height, ipl->height,*/ IPL_INTER_NN);
                
        }
        else
            ipl_scaled = ipl;

    
        CvSize cvroi = cvSize( ipl_scaled->roi ? ipl_scaled->roi->width : ipl_scaled->width,
                               ipl_scaled->roi ? ipl_scaled->roi->height : ipl_scaled->height);
    
    CvSize num_obs;
    CvImgObsInfo* info;
    
    CV_COUNT_OBS( &cvroi, &(params->faceBase->m_dctSize), &(params->faceBase->m_delta), &num_obs ); 

    int vect_len = (params->faceBase->m_obsSize.height)*(params->faceBase->m_obsSize.width);

    if( params->faceBase->m_suppress_intensity )
    {
        vect_len--;
    }

    info = cvCreateObsInfo( num_obs, vect_len );

    
    if( params->faceBase->m_suppress_intensity )
    {
        float* observations = (float*)malloc( num_obs.height * num_obs.width * (vect_len+1) * sizeof(float) );
        cvImgToObs_DCT( /*normalized_image*/ipl_scaled, observations, params->faceBase->m_dctSize, params->faceBase->m_obsSize, params->faceBase->m_delta );
        ExtractDCT( observations, info->obs, num_obs.height * num_obs.width, vect_len );
        free( observations);
    }
    else
    {
    
        //IplImage* normalized_image = cvCreateImage( cvroi, IPL_DEPTH_8U, 1 );
        //NormalizeImageForHMM( ipl_scaled, normalized_image );
    
        cvImgToObs_DCT( /*normalized_image*/ipl_scaled, info->obs, params->faceBase->m_dctSize, params->faceBase->m_obsSize, params->faceBase->m_delta );

	//cvReleaseImage(&normalized_image);
    }

    if ( doRescale )
    {
        cvReleaseImage( &ipl_scaled );
    }
    
    float max_like = -100000000; 
    //int recognized = -1;

    BEGIN_CTRL_THREAD_CORE(params->faceBase->GetPersonList().GetCount());

        CPerson* person = params->faceBase->GetPersonList().GetAt( params->faceBase->GetPersonList().FindIndex(i) );
        //CvEHMM* hmm = 0;
        childParams.hmm = 0;

        if( !person->IsTrained() )
        {
            code = 0;
            break;
        }

        childParams.hmm = person->GetHMM().GetIppiEHMM();

        if (!childParams.hmm) //person not trained
        {
            code = 0;
            break;
        }

        //cvEstimateObsProb( info, hmm );
        //like_array[i] = cvEViterbi( info, hmm );
        childParams.like_array = &(like_array[i]);
        childParams.info = info;

    END_CTRL_THREAD_CORE();

    for( i = 0; i < MIN(3,params->faceBase->GetPersonList().GetCount()); i ++ )
    {
        float maxl = -FLT_MAX;
        int maxind = -1;

        for( int j = 0; j < params->faceBase->GetPersonList().GetCount(); j++ )
        {
            if (like_array[j] > maxl) { maxl = like_array[j]; maxind = j; }
        }
        //params->three_first[i] = maxind;
        ranged[i] = maxind;
        like_array[maxind] = -FLT_MAX;
    }
    cvReleaseObsInfo( &info ); 
    gray_img.Destroy();

    int result;
    if( !code ) return result = code;

    //return MIN(3,params->faceBase->GetPersonList().GetCount());

    //int ranged[3];
    //int result = base.RecognizePerson( camera.GetFrame(), view->GetSelection(), 
    //                                   ranged );
    result = MIN(3,params->faceBase->GetPersonList().GetCount());

    if( result == 0 ) 
    {
         //MessageBox( params->hwnd, "Not all persons are trained", NULL, MB_ICONERROR );
         MessageBox( 0, "Not all persons are trained", NULL, MB_ICONERROR );
    }
    else
    {   
        CString message = "";
        for( int i = 0 ; i < result; i++ )
        {
            CPerson* person = params->base->GetPerson( ranged[i]);
            message += person->GetName() + "\n";
        }

        params->baseview->SwitchMode(ranged[0], false);
        //MessageBox( params->hwnd, (LPCTSTR)message, NULL, MB_ICONEXCLAMATION  );
        MessageBox( 0, (LPCTSTR)message, "Result of recognition", MB_ICONEXCLAMATION  );
    }

END_CTRL_THREAD_FUNCTION();

BEGIN_START_THREAD_FUNCTION(recognizeThread,
                            (CImage& image, CRect rect, /*HWND hwnd,*/
                            CFaceBase& base, CImageBaseView* baseview),InputCtrlChildThread);
    params->image = &image;
    params->rect = rect;
    params->base = &base;
    params->faceBase = &base;
    params->baseview = baseview;
END_START_THREAD_FUNCTION();



#ifndef __MULTYPROCDIV_H__
#define __MULTYPROCDIV_H__

#include <winbase.h>
#include <crtdbg.h>

#ifdef _DEBUG
    #define thrWriteToTrace0(mac_param0,mac_param1)                                               \
            _RPT0(mac_param0,mac_param1)
    #define thrWriteToTrace1(mac_param0,mac_param1,mac_param2)                                    \
            _RPT1(mac_param0,mac_param1,mac_param2)
    #define thrWriteToTrace2(mac_param0,mac_param1,mac_param2,mac_param3)                         \
            _RPT2(mac_param0,mac_param1,mac_param2,mac_param3)
    #define thrWriteToTrace3(mac_param0,mac_param1,mac_param2,mac_param3,mac_param4)              \
            _RPT3(mac_param0,mac_param1,mac_param2,mac_param3,mac_param4)
    #define thrWriteToTrace4(mac_param0,mac_param1,mac_param2,mac_param3,mac_param4,mac_param5)   \
            _RPT4(mac_param0,mac_param1,mac_param2,mac_param3,mac_param4,mac_param5)
#else
    #define thrWriteToTrace0(mac_param0,mac_param1)
    #define thrWriteToTrace1(mac_param0,mac_param1,mac_param2)
    #define thrWriteToTrace2(mac_param0,mac_param1,mac_param2,mac_param3)
    #define thrWriteToTrace3(mac_param0,mac_param1,mac_param2,mac_param3,mac_param4)
    #define thrWriteToTrace4(mac_param0,mac_param1,mac_param2,mac_param3,mac_param4,mac_param5)
#endif

#define NONE_FINISH_WORK -1
#define BRAKE_WORK -2

#define SET_CHILD_THREAD_PRIORITY(mac_handle)                                      \
    SetThreadPriority( mac_handle, THREAD_PRIORITY_BELOW_NORMAL )

#if(_WIN32_WINNT >= 0x0400)
    #define SET_CHILD_THREAD_AFFINITY_MASK(mac_handle,mac_mask)                    \
        SetThreadAffinityMask( mac_handle, mac_mask )
    #define SET_CHILD_THREAD_IDEAL_PROCESSOR(mac_handle,mac_number)                \
        SetThreadIdealProcessor( mac_handle, (DWORD)mac_number )
#else
    #define SET_CHILD_THREAD_AFFINITY_MASK(mac_handle,mac_mask)
    #define SET_CHILD_THREAD_IDEAL_PROCESSOR(mac_handle,mac_number)
#endif

#define COMMON_GLOBAL_VARS(mac_functionName,mac_inputStructType)                   \
CRITICAL_SECTION mac_functionName##CritSect;                                       \
HANDLE mac_functionName##Event;                                                    \
volatile int mac_functionName##Message;                                            \
HANDLE mac_functionName##ThreadHandle;                                             \
mac_inputStructType mac_functionName##InputStruct


#define IS_THREAD_STILL_WORKING(mac_functionName)                                  \
    ( mac_functionName##ThreadHandle ? true : false )

#define INPUT_STRUCT_COMMON_PARAMS()                                               \
    int threadNum;                                                                 \
    bool doNext;                                                                   \
    HANDLE hThread;                                                                \
    bool working

#define ENTER_THREAD_CRITICAL_SECTION()                                            \
    EnterCriticalSection( criticalSection )

#define LEAVE_THREAD_CRITICAL_SECTION()                                            \
    LeaveCriticalSection( criticalSection )

#define childParams (thrParams[thrTaskNum])

#define INIT_CHILD_THREAD_PARAMS(mac_inputStructType,mac_threadMessage)            \
    mac_inputStructType* params = (mac_inputStructType*)param;                     \
    int threadNum = params->threadNum;                                             \
    CRITICAL_SECTION* criticalSect;                                                \
    HANDLE event;                                                                  \
    int* thrMessage = (int*)&mac_threadMessage;                                    \
    bool anotherThreadBlocksVar

#define BEGIN_CHILD_THREAD_FUNCTION(mac_functionName,mac_inputStructTypeForChild)  \
DWORD mac_functionName##_child( LPVOID param )                                     \
{                                                                                  \
    INIT_CHILD_THREAD_PARAMS( mac_inputStructTypeForChild,                         \
        mac_functionName##Message );                                               \
    criticalSect = &mac_functionName##CritSect;                                    \
    event = mac_functionName##Event;                                               \
    thrWriteToTrace1( _CRT_WARN, "Thread #%d begins\n", threadNum )

#define BEGIN_CHILD_THREAD_CORE()                                                  \
    InterlockedExchange( (long*)&(params->working), (long)true );                  \
    while( params->doNext )                                                        \
    {                                                                              \
        thrWriteToTrace1( _CRT_WARN, "Thread #%d core begins\n", threadNum )

#define END_CHILD_THREAD_CORE()                                                    \
        if( !params->doNext ) {                                                    \
            break;                                                                 \
        }                                                                          \
        thrWriteToTrace1( _CRT_WARN, "Thread #%d core ends\n", threadNum );        \
        EnterCriticalSection( criticalSect );                                      \
            params->doNext = false;                                                \
            anotherThreadBlocksVar = true;                                         \
            while( anotherThreadBlocksVar )                                        \
            {                                                                      \
                if( *thrMessage == NONE_FINISH_WORK ) {                            \
                    *thrMessage = threadNum;                                       \
                    anotherThreadBlocksVar = false;                                \
                }                                                                  \
                else {                                                             \
                    LeaveCriticalSection( criticalSect );                          \
                        Sleep(0);                                                  \
                    EnterCriticalSection( criticalSect );                          \
                }                                                                  \
            }                                                                      \
            thrWriteToTrace1( _CRT_WARN, "Thread #%d sends message\n", threadNum );\
            SetEvent( event );                                                     \
        LeaveCriticalSection( criticalSect );                                      \
        thrWriteToTrace1( _CRT_WARN, "Thread #%d suspends\n", threadNum );         \
        SuspendThread( params->hThread );                                          \
        Sleep(0);                                                                  \
        thrWriteToTrace1( _CRT_WARN, "Thread #%d resumes\n", threadNum );          \
    }

#define END_CHILD_THREAD_FUNCTION()                                                \
    thrWriteToTrace1( _CRT_WARN, "Thread #%d finishes\n", threadNum );             \
    InterlockedExchange( (long*)&(params->working), (long)false );                 \
    return 0;                                                                      \
}                                                                                  
                                                                                   
#define EXIT_CTRL_THREAD(mac_threadHandle)                                         \
    thrWriteToTrace0( _CRT_WARN, "Control thread exits\n" );                       \
    if( eraseFunction ) {                                                          \
        eraseFunction(params);                                                     \
    }                                                                              \
    CloseHandle( *event );                                                         \
    DeleteCriticalSection( criticalSect );                                         \
    mac_threadHandle = 0;                                                          \
    return 0;                                                                      
                                                                                   
#define WAIT_SINGLE_OBJECT_CTRL()                                                  \
WaitForSingleObject( *event, INFINITE );                                           \
if( *thrMessage == BRAKE_WORK ) {                                                  \
    int j;                                                                         \
    thrWriteToTrace0( _CRT_WARN, "Control thread got exit message" );              \
    for( j = 0; j < numProc; j ++ )                                                \
    {                                                                              \
        if( thrParams[j].working == true ) {                                       \
            thrParams[j].doNext = false;                                           \
            ResumeThread( hThread[j] );                                            \
        }                                                                          \
    }                                                                              \
    Sleep( 5000 );                                                                 \
    for( j = 0; j < numProc; j ++ )                                                \
    {                                                                              \
        int termRes;                                                               \
        if( thrParams[j].working == true )                                         \
        {                                                                          \
            char buf[256];                                                         \
            if( termRes = TerminateThread( hThread[j], 1 ) )                       \
            {                                                                      \
                FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM, 0, GetLastError(), 0,   \
                    buf, 256, 0 );                                                 \
                thrWriteToTrace1( _CRT_WARN, "TerminateThread returned: %s\n",     \
                    buf );                                                         \
            }                                                                      \
            else {                                                                 \
                FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM, 0, GetLastError(), 0,   \
                    buf, 256, 0 );                                                 \
                thrWriteToTrace1( _CRT_WARN, "TerminateThread returned: %s\n",     \
                    buf );                                                         \
            }                                                                      \
            WaitForSingleObject( hThread[j], 1000 );                               \
        }                                                                          \
    }                                                                              \
    EXIT_CTRL_THREAD(*thisThreadHandle);                                           \
}                                                                                  

#define BEGIN_CTRL_THREAD_FUNCTION(mac_functionName,mac_inputStructType,mac_inputStructTypeForChild,\
                mac_eraseFunction,mac_beginFunction,mac_endFunction)                                \
DWORD mac_functionName##_ctrl( LPVOID param )                                                       \
{                                                                                                   \
    mac_inputStructType* params = (mac_inputStructType*)param;                                      \
    SYSTEM_INFO sysInfo;                                                                            \
    int numProc;                                                                                    \
    DWORD dwThread[32];                                                                             \
    HANDLE hThread[32];                                                                             \
    mac_inputStructTypeForChild thrParams[32];                                                      \
    DWORD affMask = 0;                                                                              \
    CRITICAL_SECTION* criticalSect = &mac_functionName##CritSect;                                   \
    HANDLE* event = &mac_functionName##Event;                                                       \
    HANDLE* thisThreadHandle = &mac_functionName##ThreadHandle;                                     \
    int tasksNum;                                                                                   \
    LPTHREAD_START_ROUTINE childFunction = (LPTHREAD_START_ROUTINE)mac_functionName##_child;        \
    int thrTaskNum;                                                                                 \
    int* thrMessage = (int*)&mac_functionName##Message;                                             \
    bool (*eraseFunction)( void* ) = ( bool (*)( void* ) )mac_eraseFunction;                        \
    bool (*beginFunction)( void* ) = ( bool (*)( void* ) )mac_beginFunction;                        \
    bool (*endFunction)( void* ) = ( bool (*)( void* ) )mac_endFunction;                            \
    int i;                                                                                          \
    thrWriteToTrace0( _CRT_WARN, "Control thread begins\n" )

#define BEGIN_CTRL_THREAD_CORE(mac_tasksNum)                                       \
    tasksNum = mac_tasksNum;                                                       \
    InitializeCriticalSection( criticalSect );                                     \
    *event = CreateEvent( 0, true, false, NULL );                                  \
    GetSystemInfo( &sysInfo );                                                     \
    numProc = sysInfo.dwNumberOfProcessors;                                        \
    if( numProc > 32 ) {                                                           \
        EXIT_CTRL_THREAD( *thisThreadHandle );                                     \
    }                                                                              \
    if( beginFunction ) {                                                          \
        beginFunction( params );                                                   \
    }                                                                              \
    *thrMessage = NONE_FINISH_WORK;                                                \
    for( i = 0; i <= tasksNum; i ++ )                                              \
    {                                                                              \
        if( i > 0 ) {                                                              \
            i --;                                                                  \
            thrWriteToTrace2( _CRT_WARN, "Control thread gives task #%d to"        \
                " thread #%d\n", i, thrTaskNum )

// givingTask

#define END_CTRL_THREAD_CORE()                                                     \
            thrParams[thrTaskNum].doNext = true;                                   \
            thrWriteToTrace1( _CRT_WARN, "Control thread resumes thread #%d\n",    \
                thrTaskNum );                                                      \
            while( !ResumeThread( hThread[thrTaskNum] ) ) Sleep(0);                \
            i ++;                                                                  \
        }                                                                          \
        if( i < tasksNum ) {                                                       \
            if( i < numProc ) {                                                    \
                thrParams[i].threadNum = i;                                        \
                thrParams[i].working = true;                                       \
                thrWriteToTrace0( _CRT_WARN, "Control thread creates child"        \
                    " thread\n" );                                                 \
                hThread[i] = CreateThread( NULL, 0, childFunction,                 \
                    &(thrParams[i]), CREATE_SUSPENDED, &(dwThread[i]) );           \
                thrParams[i].hThread = hThread[i];                                 \
                thrParams[i].doNext = false;                                       \
                SET_CHILD_THREAD_PRIORITY( hThread[i] );                           \
                SET_CHILD_THREAD_AFFINITY_MASK( hThread[i], affMask );             \
                SET_CHILD_THREAD_IDEAL_PROCESSOR( hThread[i], (DWORD)i );          \
                thrTaskNum = i;                                                    \
            }                                                                      \
            else {                                                                 \
            thrWriteToTrace0( _CRT_WARN, "Control thread waits for a message\n" ); \
                WAIT_SINGLE_OBJECT_CTRL();                                         \
                EnterCriticalSection( criticalSect );                              \
                    ResetEvent( *event );                                          \
                    thrTaskNum = *thrMessage;                                      \
                    thrWriteToTrace1( _CRT_WARN, "Control thread got a message"    \
                        " from thread #%d\n", thrTaskNum );                        \
                    thrParams[thrTaskNum].doNext = true;                           \
                    *thrMessage = NONE_FINISH_WORK;                                \
                LeaveCriticalSection( criticalSect );                              \
            }                                                                      \
        }                                                                          \
    }                                                                              \
    thrWriteToTrace0( _CRT_WARN, "Control thread waits for finishing all"          \
        " threads\n" );                                                            \
    for( i = tasksNum; i < numProc; i ++ ) {                                       \
        thrParams[i].doNext = false;                                               \
        ResumeThread( hThread[i] );                                                \
        WaitForSingleObject( hThread[i], INFINITE );                               \
    }                                                                              \
    for( i = 0; i < numProc; i ++ )                                                \
    {                                                                              \
        thrWriteToTrace0( _CRT_WARN, "Control thread waits for message\n" );       \
        WAIT_SINGLE_OBJECT_CTRL();                                                 \
        EnterCriticalSection( criticalSect );                                      \
            ResetEvent( *event );                                                  \
            thrTaskNum = *thrMessage;                                              \
            thrWriteToTrace1( _CRT_WARN, "Control thread got last message from"    \
                " thread #%d\n", thrTaskNum );                                     \
            thrParams[thrTaskNum].doNext = false;                                  \
            *thrMessage = NONE_FINISH_WORK;                                        \
            while( !ResumeThread( hThread[thrTaskNum] ) ) Sleep(0);                \
        LeaveCriticalSection( criticalSect );                                      \
        WaitForSingleObject( hThread[thrTaskNum], INFINITE );                      \
    }

#define END_CTRL_THREAD_FUNCTION()                                                 \
    thrWriteToTrace0( _CRT_WARN, "Control thread is getting normal finishing\n" ); \
    if( endFunction ) {                                                            \
        endFunction( params );                                                     \
    }                                                                              \
    CloseHandle( *event );                                                         \
    DeleteCriticalSection( criticalSect );                                         \
    *thisThreadHandle = 0;                                                         \
    return 0;                                                                      \
}

#define DEFINE_START_THREAD_FUNCTION(mac_functionName,mac_inputParams)             \
extern HANDLE mac_functionName##ThreadHandle;                                      \
bool mac_functionName##mac_inputParams

#define BEGIN_START_THREAD_FUNCTION(mac_functionName,mac_inputParams,              \
        mac_inputStructType)                                                       \
bool mac_functionName##mac_inputParams                                             \
{                                                                                  \
    static bool mac_functionName##StartsFirstTime = true;                          \
    bool anotherThreadBlocksVar;                                                   \
    mac_inputStructType* params = &mac_functionName##InputStruct;                  \
    HANDLE* thrHandle = &mac_functionName##ThreadHandle;                           \
    LPTHREAD_START_ROUTINE threadCtrlFunction =                                    \
        (LPTHREAD_START_ROUTINE)mac_functionName##_ctrl;                           \
    thrWriteToTrace0( _CRT_WARN, "Start function begins\n" );                      \
    if( mac_functionName##StartsFirstTime ) {                                      \
        mac_functionName##StartsFirstTime = false;                                 \
        mac_functionName##ThreadHandle = 0;                                        \
    }                                                                              \
    if( mac_functionName##ThreadHandle ) {                                         \
        EnterCriticalSection( &mac_functionName##CritSect );                       \
            anotherThreadBlocksVar = true;                                         \
            while( anotherThreadBlocksVar )                                        \
            {                                                                      \
                if( mac_functionName##Message == NONE_FINISH_WORK ) {              \
                    mac_functionName##Message = BRAKE_WORK;                        \
                    anotherThreadBlocksVar = false;                                \
                }                                                                  \
                else {                                                             \
                    LeaveCriticalSection( &mac_functionName##CritSect );           \
                        Sleep(0);                                                  \
                    EnterCriticalSection( &mac_functionName##CritSect );           \
                }                                                                  \
            }                                                                      \
            thrWriteToTrace0( _CRT_WARN, "Main thread sets break event\n" );       \
            SetEvent( mac_functionName##Event );                                   \
        LeaveCriticalSection( &mac_functionName##CritSect );                       \
    }                                                                              \
    else {
        
#define END_START_THREAD_FUNCTION()                                                \
        *thrHandle = CreateThread( NULL, 0,                                        \
            (LPTHREAD_START_ROUTINE)threadCtrlFunction, params, 0, 0 );            \
        SET_CHILD_THREAD_PRIORITY( *thrHandle );                                   \
    }                                                                              \
    thrWriteToTrace0( _CRT_WARN, "Start function ends\n" );                        \
    return true;                                                                   \
}


#endif // if !defined __MULTYPROCDIV_H__
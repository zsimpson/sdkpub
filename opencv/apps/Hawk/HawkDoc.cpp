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
//M*/// HawkDoc.cpp : implementation of the CHawkDoc class
//

#include "stdafx.h"
#include "Hawk.h"

#include "MainFrm.h"
#include "HawkDoc.h"
#include "HawkView.h"
#include "LogView.h"
#include "DSWnd.h"
#include "HawkOptions.h"
#include "QuickWatch.h"
#include "wordcolors.h"

#include "convert.h"

#include <io.h>
#include <fcntl.h>
#include <process.h>
#include <setjmp.h>


extern "C"
{
/*#include "eic.h"
#ifdef malloc
#undef malloc
#endif
#ifdef realloc
#undef realloc
#endif
#ifdef free
#undef free
#endif*/
#include "CVEiCL\EiC\src\error.h"
#include "CVEiCL\EiC\src\preproc.h"
#include "HighGUI.h"
void set_highgui_mark(jmp_buf* mark);
}

void init_signal_handlers();

int __cdecl DS_ON_SIZE(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, int* ret);
unsigned long __stdcall ProcessEicErr(void* hawkDoc, int show = 1);
unsigned long __stdcall ProcessEicOut(void* hawkDoc);
unsigned long __stdcall RunScript(void*);
unsigned long _stdcall ReadPipeStream(void* data);
void __cdecl ImageTransform(void* in);

typedef struct
{
    stream_pipe pipe;
    char* text;
} data_pipe;

#define EIC_OUT ((CHawkApp*)AfxGetApp())->m_eicOut
#define EIC_ERR ((CHawkApp*)AfxGetApp())->m_eicErr

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHawkDoc

IMPLEMENT_DYNCREATE(CHawkDoc, CDocument)

BEGIN_MESSAGE_MAP(CHawkDoc, CDocument)
    //{{AFX_MSG_MAP(CHawkDoc)
    ON_COMMAND(ID_RUN, OnRun)
    ON_UPDATE_COMMAND_UI(ID_RUN, OnUpdateRun)
    ON_COMMAND(ID_RUNDS, OnRunds)
    ON_UPDATE_COMMAND_UI(ID_RUNDS, OnUpdateRunds)
    ON_COMMAND(ID_STOPDS, OnStopds)
    ON_UPDATE_COMMAND_UI(ID_STOPDS, OnUpdateStopds)
    ON_COMMAND(ID_OPTIONS_CONFIGURATION, OnOptionsConfiguration)
    ON_COMMAND(ID_OPTIONS_COLORS, OnOptionsColors)
    ON_UPDATE_COMMAND_UI(ID_OPTIONS_COLORS, OnUpdateOptionsColors)
	ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
	ON_UPDATE_COMMAND_UI(ID_FILE_CLOSE, OnUpdateFileClose)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_EIC_QWATCH, OnEicQwatch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHawkDoc construction/destruction

CHawkDoc::CHawkDoc() /*: m_DSWnd(new CDSWnd)*/
{
    m_pHawkView = NULL;
    m_pLogView = NULL;
    m_pScript = NULL;
    m_hThread = NULL;
    m_hScriptMutex = NULL;
    m_hScriptExec = NULL;
    SetModifiedFlag(FALSE);
}

CHawkDoc::~CHawkDoc()
{
    /* Close the therad... */
    CHawkApp* app = (CHawkApp*)AfxGetApp();
//    app->CloseEiCHandles();
    if(WaitForSingleObject(m_hScriptExec, 0) == WAIT_TIMEOUT)
    {
        TerminateThread(m_hScriptExec, 0);
    }
    if(WaitForSingleObject( m_hThread, 0) == WAIT_TIMEOUT)
    {
        TerminateThread(m_hThread, 0);
    }
    CMainFrame* frame = (CMainFrame*)AfxGetMainWnd();
    frame->SetIntRun(FALSE);
    frame->SetDocRun();
    delete m_pScript;
    if(m_hScriptExec) CloseHandle(m_hScriptExec);
    if(m_hScriptMutex) CloseHandle(m_hScriptMutex);
}

BOOL CHawkDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

    // TODO: add reinitialization code here
	// (SDI documents will reuse this document)

    return Initialize();
}



/////////////////////////////////////////////////////////////////////////////
// CHawkDoc serialization

void CHawkDoc::Serialize(CArchive& ar)
{
    CEditView* pView = GetHawkView();
    pView->SerializeRaw(ar);

    if(ar.IsLoading())
    {
        Initialize();
    }
    else
    {
        pView->GetEditCtrl().SetModify(FALSE);
    }
}

/////////////////////////////////////////////////////////////////////////////
// CHawkDoc diagnostics

#ifdef _DEBUG
void CHawkDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHawkDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHawkDoc commands

void CHawkDoc::OnRun() 
{
    if(IsRunning())
    {
        return;
    }

    CHawkApp* app = (CHawkApp*)AfxGetApp();
    CMainFrame* frame = (CMainFrame*)AfxGetMainWnd();

    if(app->GetSBRun() && IsModified())
    {
        OnFileSave();
        SetModifiedFlag(FALSE);
        if(IsModified())
        {
            return;
        }
    }

    frame->SetIntRun(TRUE);
    frame->m_pRunDoc = this;

    DWORD threadID;

    if(!m_hScriptMutex)
    {
        CString mname;
        mname.Format("Script semaphore,doc=0x%p", this);
        m_hScriptMutex = CreateMutex(0, TRUE, LPCTSTR(mname));
    }
    m_execState = TRUE;

    if(!m_hScriptExec)
    {
        m_hScriptExec = CreateThread(0, 0, RunScript, this, 0, &threadID);
    }
//    m_hThread = CreateThread(0, 0, ProcessEicOut, this, 0, &threadID);

    // Let the script execution start...
    ReleaseMutex(m_hScriptMutex);
    while(m_execState  == TRUE);

    WaitForSingleObject(m_hScriptMutex, INFINITE);
    m_execState = TRUE;
}

void CHawkDoc::OnUpdateRun(CCmdUI* pCmdUI) 
{
    CHawkView* pHawkView = GetHawkView();
    if(!::IsWindow(pHawkView->m_hWnd) || IsRunning())
    {
        pCmdUI->Enable(FALSE);
    }
    else
    {
        pCmdUI->Enable(pHawkView->GetBufferLength());
    }
}

CHawkView* CHawkDoc::GetHawkView()
{
    if(m_pHawkView)
    {
        return m_pHawkView;
    }

    POSITION pos = GetFirstViewPosition();
    CView* pView;
    while(pos)
    {
        pView = GetNextView(pos);
        if(pView->IsKindOf(RUNTIME_CLASS(CHawkView)))
        {
            m_pHawkView = static_cast<CHawkView*>(pView);
            return m_pHawkView;
        }
    }

    ASSERT(0);

    return NULL;
}

void GenerateExceptionString(DWORD code, char* buffer)
{
    switch(code)
    {
    case EXCEPTION_ACCESS_VIOLATION:
         strcpy(buffer, "The thread attempted to read from or write to a virtual address \
for which it does not have the appropriate access.");

    case EXCEPTION_BREAKPOINT: strcpy(buffer, "A breakpoint was encountered.");
    case EXCEPTION_FLT_DIVIDE_BY_ZERO: strcpy(buffer, "The thread attempted to divide a floating-point \
value by a floating-point divisor of zero.");
    case EXCEPTION_FLT_INVALID_OPERATION: strcpy(buffer, "This exception represents any floating-point \
exception not included in this list.");
    case EXCEPTION_FLT_OVERFLOW: strcpy(buffer, "The exponent of a floating-point operation is greater \
than the magnitude allowed by the corresponding type.");
    case EXCEPTION_FLT_UNDERFLOW: strcpy(buffer, "The exponent of a floating-point operation is less \
than the magnitude allowed by the corresponding type.");
    case EXCEPTION_INT_DIVIDE_BY_ZERO: strcpy(buffer, "The thread attempted to divide an integer value \
by an integer divisor of zero.");
    case EXCEPTION_INT_OVERFLOW: strcpy(buffer, "The result of an integer operation caused a carry out \
of the most significant bit of the result.");

    default:
        {
            sprintf(buffer, "Code 0x%08x.", code);
        }
    }
}

extern "C"
{
extern char* EiC_CurrentFile;
extern int EiC_CurrentLine;
}
int _Hawk_EiC_parseString(char* str, void* hawkDoc)
{
#ifndef HAWK_TEST
    __try
    {
        EiC_parseString(str);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        char info[18256];
        char ex_info[9128];
        CMainFrame* frame = (CMainFrame*)AfxGetMainWnd();
        CHawkDoc* pDoc = (CHawkDoc*)hawkDoc;
        frame->SetIntRun(FALSE);
        frame->SetDocRun();
        pDoc->m_hScriptExec = 0;
        GenerateExceptionString(GetExceptionCode(), ex_info);
        sprintf(info, "Exception in file %s, line %d: \n%s", EiC_CurrentFile, EiC_CurrentLine, 
            ex_info);
        AfxMessageBox(info);
        EiC_parseString(":reset");
        return FALSE;
    }
#else
    EiC_parseString(str);
#endif /* HAWK_TEST */

	return TRUE;
}
unsigned long __stdcall RunScript(void* hawkDoc)
{
	int retval = TRUE;
	CHawkApp* app = (CHawkApp*)AfxGetApp();
    CHawkDoc* pDoc = (CHawkDoc*)hawkDoc;
    CMainFrame* frame = (CMainFrame*)AfxGetMainWnd();
    CString fileName = pDoc->GetPathName();
    char drive[_MAX_DRIVE], path[_MAX_PATH], file[_MAX_PATH], ext[_MAX_PATH];
    _splitpath(LPCTSTR(fileName), drive, path, file, ext);
    CString spath = CString(drive) + path;
    fileName = CString(file) + ext;

    char curDir[_MAX_PATH];
    GetCurrentDirectory(_MAX_PATH, curDir);
    init_signal_handlers();

//    pDoc->m_readMutex = CreateMutex(NULL, TRUE, "EiC read mutex(for threads)");
    while(retval)
    {
        frame->SetIntRun(FALSE);
        frame->SetDocRun();
        while(pDoc->m_execState == FALSE);
        while(WaitForSingleObject(pDoc->m_hScriptMutex, 10) != WAIT_OBJECT_0)
        {
            MSG message;
            if(PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&message);
                DispatchMessage(&message);
            }
        }
        pDoc->m_execState = FALSE;
        ReleaseMutex(pDoc->m_hScriptMutex);

        /* Starting the execution... */
        frame->SetIntRun(TRUE);
        frame->SetDocRun(pDoc);

        /* Clean the error stream */
        ProcessEicErr(pDoc, 0);

        EiC_parseString("#pragma push_unsafeptr");
        CString inString = CString("#include \"") + fileName + CString("\"");

        int ret = setjmp(app->m_mark);
        if(!ret)
        {
            // Execute the script
            LPTSTR pstr = const_cast<char*>(LPCTSTR(inString));
            SetCurrentDirectory(spath);
            retval = _Hawk_EiC_parseString(pstr, hawkDoc);
            SetCurrentDirectory(curDir);
        }
        else
        {
            SetCurrentDirectory(curDir);
            // Catched long jump:
            wrapexcept_t* err = (wrapexcept_t*)ret;
            switch(err->result_code)
            {
            case result_string:
                AfxMessageBox(err->message);
                free(err->message);
                free(err);
                break;

            case result_empty:
                break;

            default:
                ASSERT(0);
            }
            destroy_all();
        }
        
        
        // Clean the space
        if(!EiC_ParseError)
        {
            detach_all_controls();
            inString = CString(":clear ") + fileName;//pDoc->GetPathName();
            EiC_parseString(const_cast<char*>(LPCTSTR(inString)));
            EiC_parseString("#pragma pop_ptr");
//            EiC_parseString(":reset");
        }
        else
        {
            if(ProcessEicErr(pDoc))
            {
                // An error has been detected
        //        return;
            }
            // Return to the initial state of EiC
//            EiC_parseString(":reset");// Commented because of possible EiC reset bug
        }
    }
    
    return 0;
}

/* This function should not be called... */
unsigned long __stdcall ProcessEicOut(void* hawkDoc)
{
    CHawkDoc* pDoc = (CHawkDoc*)hawkDoc;
    CHawkApp* app = (CHawkApp*)AfxGetApp();
    HANDLE mutices[2]; /* Great spelling! */
    mutices[0] = app->m_printfMutex;
    mutices[1] = pDoc->m_readMutex;
//    long pos = tell(EIC_OUT.read);

//    fputc(0, EIC_OUT.write);
//    fflush(EIC_OUT.write);

    long buffer_size = 2048;
//    char* textBuffer = (char*)malloc(buffer_size + 2);
//    char* temp = textBuffer;
//    int out;
    while(1)
    {

        DWORD ret = WaitForMultipleObjects(2, mutices, FALSE, INFINITE);
        if(ret != WAIT_OBJECT_0)
        {
            break;
        }

        CString buf = app->m_EiCOut;
        app->m_EiCOut.Empty();
        ReleaseMutex(app->m_printfMutex);
        pDoc->GetLogView()->AddString(LPCTSTR(buf));

/*        if(textBuffer[out - 1] == 0)
        {
            break;
        }*/
    }

//    free(textBuffer);

    // Now it is safe to close the application
    ((CMainFrame*)AfxGetMainWnd())->SetIntRun(FALSE);

    return 1;
}

unsigned long __stdcall ProcessEicErr(void* hawkDoc, int show)
{
    CHawkDoc* pDoc = (CHawkDoc*)hawkDoc;
    int ret = 0;

    rewind(EIC_ERR.read);

    long buffer_size = 2048;
    char* textBuffer = (char*)malloc(buffer_size);
    char* temp = textBuffer;
    int err, err_total = 0;
    while(1)
    {
        err = _read(_fileno(EIC_ERR.read), temp, buffer_size);
        err_total += err;
        if(err < buffer_size)
        {
            break;
        }
        buffer_size *= 2;
        temp = (char*)malloc(buffer_size + err_total);
        memcpy(temp, textBuffer, err_total);
        free(textBuffer);
        textBuffer = temp;
        temp = &textBuffer[err_total];
    }

    if(err_total > 0)
    {
        if(textBuffer[err_total-1] == 26 || textBuffer[err_total-1] == 0)
        {
            textBuffer[--err_total] = 0;
        }
        if(err_total > 0)
        {
            textBuffer[err_total] = 0;
            if(show)
                AfxMessageBox(textBuffer);
            ret = err_total - 1;
        }
    }

    free(textBuffer);
    /* Clear the file... */
    _chsize(_fileno(EIC_ERR.read), 0);
    rewind(EIC_ERR.read);
    return ret;
}

unsigned long _stdcall ReadPipeStream(void* pdata)
{
    data_pipe* data = static_cast<data_pipe*>(pdata);
    CString OutText;

    do
    {
        OutText += fgetc(data->pipe.read);
    }
    while(OutText.GetAt(OutText.GetLength()) != 26);

    data->text = _strdup(LPCTSTR(OutText));

    return 0;
}

CLogView* CHawkDoc::GetLogView()
{
    if(m_pLogView)
    {
        return m_pLogView;
    }

    POSITION pos = GetFirstViewPosition();
    CView* pView;
    while(pos)
    {
        pView = GetNextView(pos);
        if(pView->IsKindOf(RUNTIME_CLASS(CLogView)))
        {
            m_pLogView = static_cast<CLogView*>(pView);
            return m_pLogView;
        }
    }

    ASSERT(0);

    return NULL;
}

BOOL CHawkDoc::Initialize()
{
    GetHawkView()->UpdateCursorPos();
    return TRUE;
}

// An example of a bad idea. I tried to divide a C source into parts 
// that can be accepted by EiC, for instance, single lines finished by a semicolon
// Put off to be on the safe side. Hope I'll never return to this idea.
void CHawkDoc::ParseString()
{
    unsigned int i;
    int braceCount = 0;
    int bracketCount = 0;
    int start = 0;
    char* text = new char[strlen(m_pScript)];
    CString str;

    m_parsedStrings.RemoveAll();
    for(i = 0; i < strlen(m_pScript); i++)
    {
        switch(m_pScript[i])
        {
        case '{':
            braceCount++;
            break;
        case '(':
            bracketCount++;
            break;

        case '}':
            braceCount--;
            if(!braceCount && !bracketCount)
            {
                memcpy(text, m_pScript + start, i - start + 1);
                text[i - start + 1] = 0;
                str = CString(text);
                str.Remove(10);
                str.Remove(13);
                m_parsedStrings.Add(str);
                start = i + 1;
            }
            break;

        case ')':
            bracketCount--;
            break;

        case ';':
            if(!braceCount && !bracketCount)
            {
                memcpy(text, m_pScript + start, i - start + 1);
                text[i - start + 1] = 0;
                str = CString(text);
                str.Remove(10);
                str.Remove(13);
                if(str.GetLength())
                    m_parsedStrings.Add(str);
                start = i + 1;
            }
            break;

        case '#':
            if(i == 0 || text[i - 1] == 10 || text[i - 1] == 13)
            {
                
            }
        }
    }

    delete text;
}

void CHawkDoc::OnRunds() 
{
    if(IsRunning())
    {
        // We're already running
        return;
    }

    CHawkApp* app = (CHawkApp*)AfxGetApp();
    if(app->GetSBRun() && IsModified())
    {
        OnFileSave();
        if(IsModified())
        {
            return;
        }
    }

	if(ParseTransformFunction())
	{
        m_dsSimpleMode = TRUE;
        CMainFrame* frame = (CMainFrame*)AfxGetMainWnd();
        frame->SetIntRun(TRUE);
        frame->m_pRunDoc = this;
        frame->RunDS(ImageTransform);
	}
}

void CHawkDoc::OnUpdateRunds(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(0/*((CMainFrame*)AfxGetMainWnd())->IsDirectShowOn()*/);
}

static void __cdecl ImageTransform(void* in)
{
    CHawkApp* app = (CHawkApp*)AfxGetApp();

    WaitForSingleObject(app->m_printfMutex, INFINITE);
    TRACE0("\nCaptured printf mutex...");
	IplImage* image = static_cast<IplImage*>(in);

	CString inString;
	inString.Format("__HAWK_IMAGE_TRANSFORM((IPLIMAGE)0x%x);", (int)in);
	EiC_parseString(const_cast<char*>(LPCTSTR(inString)));
    TRACE0("Preparing to release printf mutex...");
    ReleaseMutex(app->m_printfMutex);
    TRACE0("\nReleased printf mutex...");
}

BOOL CHawkDoc::ParseTransformFunction()
{
	const char* dir = ((CHawkApp*)AfxGetApp())->GetModulePath();
	char* tmpname = _strdup(_tempnam(dir, ""));
	if(tmpname == NULL)
	{
		AfxMessageBox("Could not create a temporary file name");
		return FALSE;
	}

	m_tempName = CString(tmpname);
	FILE* fp = fopen(tmpname, "wt");
	if(fp == NULL)
	{
		AfxMessageBox("Could not open a temporary file");
		return FALSE;
	}

	fprintf(fp, "void __HAWK_IMAGE_TRANSFORM(IPPIIMAGE ds_image)\n");
	fprintf(fp, "{\n");
	fprintf(fp, "#include \"%s\"\n", GetPathName());
	fprintf(fp, "}");
	fclose(fp);

    EiC_parseString("#pragma push_unsafeptr");
	CString str;
	str.Format("#include \"%s\"", tmpname);
	free(tmpname);
	EiC_parseString(const_cast<char*>(LPCTSTR(str)));
    EiC_parseString("#pragma pop_ptr");

	return !ProcessEicErr(this);
}

void CHawkDoc::ClearTransformFunction()
{
	CString inString;
	inString.Format(":clear %s", LPCTSTR(m_tempName));
	EiC_parseString(const_cast<char*>(LPCTSTR(inString)));
	remove(const_cast<char*>(LPCTSTR(m_tempName)));
	m_tempName.Empty();
}

unsigned long __stdcall _StopDS(void* doc)
{
    CMainFrame* frame = (CMainFrame*)AfxGetMainWnd();
    CHawkApp* app = (CHawkApp*)AfxGetApp();
    CHawkDoc* pDoc = (CHawkDoc*)doc;
    WaitForSingleObject(app->m_printfMutex, INFINITE);
	frame->StopGraph();
//	VERIFY(m_DSWnd->DestroyWindow());
	VERIFY(destroy_window("DirectShow") == 0);
	// Clear the CVEiCL scope
    if(pDoc->m_dsSimpleMode)
	    pDoc->ClearTransformFunction();
    ReleaseMutex(app->m_printfMutex);
/*	FILE* out = ((CHawkApp*)AfxGetApp())->m_eicOut.write;
	fputc(0, out);
	fflush(out);*/
    if(pDoc->m_dsSimpleMode)
    {
        frame->SetIntRun(FALSE);
        frame->SetDocRun();
    }

    return 0;
}

void CHawkDoc::OnStopds() 
{
    DWORD tID;
    CreateThread(NULL, 0, _StopDS, this, 0, &tID);
}

void CHawkDoc::OnUpdateStopds(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(((CMainFrame*)AfxGetMainWnd())->IsDSRunning());	
}

BOOL CHawkDoc::IsRunning()
{
    CMainFrame* frame = (CMainFrame*)AfxGetMainWnd();
    if(frame->IsIntRun() || frame->IsDSRunning())
    {
        // We're already running
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL CHawkDoc::CanCloseFrame(CFrameWnd* pFrame) 
{
	return !IsRunning() && !((CMainFrame*)AfxGetMainWnd())->IsDSRunning();
}

void CHawkDoc::OnOptionsConfiguration() 
{
    CHawkApp* app = (CHawkApp*)AfxGetApp();
    CHawkOptions dlg(app->GetErrLevel(), app->GetSBRun());
    if(dlg.DoModal() == IDOK)
    {
        app->SetErrLevel(dlg.m_errLevel ? safe : unsafe);
        app->SetSBRun(dlg.m_sbRun);
    }
}

BOOL CHawkDoc::IsModified()
{
//    return GetHawkView()->m_edit.GetModify();
    return CDocument::IsModified();
}


void CHawkDoc::OnOptionsColors() 
{
    CWordColors wc;
    GetHawkView()->Scheme = wc.DoModal(GetHawkView()->Scheme);
}

void CHawkDoc::OnUpdateOptionsColors(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
}

BOOL CHawkDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

    char drive[_MAX_DRIVE];
    char path[_MAX_DIR];
    char fname[_MAX_FNAME];
    char fext[_MAX_EXT];
    _splitpath(lpszPathName, drive, path, fname, fext);
    
    VERIFY(::SetCurrentDirectory(LPCTSTR(CString(drive) + CString(path))));	
	return TRUE;
}

/* Currently this function should not be called! */
void CHawkDoc::OnFileClose() 
{
    /* Close the therad... */
    CHawkApp* app = (CHawkApp*)AfxGetApp();
    app->CloseEiCHandles();
    if(WaitForSingleObject(m_hScriptExec, 0) == WAIT_TIMEOUT)
    {
        TerminateThread(m_hScriptExec, 0);
    }
    if(WaitForSingleObject( m_hThread, 0) == WAIT_TIMEOUT)
    {
        TerminateThread(m_hThread, 0);
    }
    app->InitEiCHandles();
    
    CMainFrame* frame = (CMainFrame*)AfxGetMainWnd();
    frame->SetIntRun(FALSE);
    frame->SetDocRun();
    
    CDocument::OnFileClose();	
}

void CHawkDoc::OnUpdateFileClose(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(!IsRunning());
}

int play_ds(void (*transform_image)(IPLIMAGE))
{
    CMainFrame* frame = (CMainFrame*)AfxGetMainWnd();
    if(!frame->IsDirectShowOn())
    {
        return -1;
    }
    frame->m_pRunDoc->m_dsSimpleMode = FALSE;
    frame->RunDS((void(*)(void*))transform_image, FALSE);
    return 0;
}

void CHawkDoc::OnFileSave() 
{
    CDocument::OnFileSave();
    SetModifiedFlag(FALSE);
}

void CHawkDoc::OnFileSaveAs() 
{
    CDocument::OnFileSaveAs();	
    SetModifiedFlag(FALSE);
}

void CHawkDoc::OnEicQwatch() 
{
    CQuickWatch dlg;
    dlg.DoModal();
}

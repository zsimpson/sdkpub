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
//M*/// Hawk.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Hawk.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "HawkDoc.h"
#include "HawkView.h"
#include "LogView.h"

#include <io.h>
#include <fcntl.h>
#include <process.h>
#include <signal.h>
extern "C"
{
#include "wrap.h"
}

#include <fstream>
//#include "eicdllwrap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char* cline = "-D_EiC";
char* std_inc[] = {"assert", "ctype", "errno", /*"float", "limits",*/ "math",
            "stdarg", "stddef", "stdio", "stdlib", "string", "time"};

extern "C"
{
#include "CVEiCL\EiC\src\eic.h"
#include "CVEiCL\EiC\src\typemod.h"
#include "CVEiCL\EiC\src\global.h"
#include "CVEiCL\EiC\src\func.h"
#include "CVEiCL\EiC\src\error.h"
#include "CVEiCL\EiC\src\symbol.h"
#include "eicio.h"
#include "HighGUI.h"
}
extern "C" {
    void EiC_init_EiC(void);
    void stdClib(void);
    void module_ippiwrap(void);
    void module_ipl();
    void EiC_switches(char*);
    void module_highguiwrap();
    void set_highgui_errlevel(errlevel_t level);
    void set_highgui_mark(jmp_buf* mark);
    symentry_t * EiC_lookup(char nspace, char *id);
    void EiC_xalloc_CleanUp(size_t, size_t);

    extern void (*EiC_messageDisplay)(char*);
};
void set_hawk_errlevel(errlevel_t level);
void set_hawk_mark(jmp_buf* mark);
void module_convertwrap();
void set_eic_errlevel(errlevel_t level);
void set_eic_mark(jmp_buf* mark);

int FindStringInArray(const CStringArray& array, const CString& string)
{
    for(int i = 0; i < array.GetSize(); i++)
    {
        if(strcmp(LPCTSTR(array.GetData()[i]), LPCTSTR(string)) == 0)
        {
            return i;
        }
    }

    return -1;
}

template<> void AFXAPI DestructElements<CMenu*> (CMenu** pElements, int nCount)
{
    for(int i = 0; i < nCount; i++)
        delete pElements[i];
}

template<> void AFXAPI DestructElements<plugin_t> (plugin_t* pElements, int nCount)
{
    for(int i = 0; i < nCount; i++)
        delete pElements[i].m_functions;
}


/////////////////////////////////////////////////////////////////////////////
// CHawkApp

BEGIN_MESSAGE_MAP(CHawkApp, CWinApp)
        //{{AFX_MSG_MAP(CHawkApp)
        ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
                // NOTE - the ClassWizard will add and remove mapping macros here.
                //    DO NOT EDIT what you see in these blocks of generated code!
        //}}AFX_MSG_MAP
        // Standard file based document commands
        ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
        ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
        // Standard print setup command
        ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHawkApp construction

CHawkApp::CHawkApp()
{
    m_eicOut.write = m_eicOut.read = NULL;
    m_eicErr.write = m_eicErr.read = NULL;
    m_mainMenu.m_hMenu = NULL;
    m_errlevel = unsafe;
    m_sbRun = TRUE;
    m_dsMutex = NULL;

    m_pipeDataSize = 0;
}

CHawkApp::~CHawkApp()
{
    for(int i = 0; i < m_funcDialogs.GetSize(); i++)
    {
        delete (CFuncDialog*)m_funcDialogs.GetData()[i];
    }
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CHawkApp object

CHawkApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CHawkApp initialization

BOOL CHawkApp::InitInstance()
{
        AfxEnableControlContainer();

        // Standard initialization
        // If you are not using these features and wish to reduce the size
        //  of your final executable, you should remove from the following
        //  the specific initialization routines you do not need.

#ifdef _AFXDLL
        Enable3dControls();                     // Call this when using MFC in a shared DLL
#else
        Enable3dControlsStatic();       // Call this when linking to MFC statically
#endif

        // Change the registry key under which our settings are stored.
        // TODO: You should modify this string to be something appropriate
        // such as the name of your company or organization.
        SetRegistryKey(_T("Intel"));

        LoadStdProfileSettings();  // Load standard INI file options (including MRU)

        // Register the application's document templates.  Document templates
        //  serve as the connection between documents, frame windows and views.

        CMultiDocTemplate* pDocTemplate;
        pDocTemplate = new CMultiDocTemplate(
                IDR_HAWTYPE,
                RUNTIME_CLASS(CHawkDoc),
                RUNTIME_CLASS(CChildFrame), // custom MDI child frame
                RUNTIME_CLASS(CHawkView));
        AddDocTemplate(pDocTemplate);

        pDocTemplate = new CMultiDocTemplate(
                IDR_LOGTYPE,
                RUNTIME_CLASS(CDocument),
                RUNTIME_CLASS(CChildFrame), // custom MDI child frame
                RUNTIME_CLASS(CLogView));
        AddDocTemplate(pDocTemplate);


        // create main MDI Frame window
        CMainFrame* pMainFrame = new CMainFrame;
        if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
                return FALSE;
        m_pMainWnd = pMainFrame;

        // Parse command line for standard shell commands, DDE, file open
        CCommandLineInfo cmdInfo;
        ParseCommandLine(cmdInfo);

        // Dispatch commands specified on the command line
        if (!ProcessShellCommand(cmdInfo))
                return FALSE;

        // The main window has been initialized, so show and update it.
        pMainFrame->ShowWindow(m_nCmdShow);
        pMainFrame->UpdateWindow();

    // Creating a headband
    m_headband.Create(IDD_HEADBAND, AfxGetMainWnd());

    // Centering a headband
    CRect rect, drect, nrect;
    AfxGetMainWnd()->GetWindowRect(&rect);
    m_headband.GetWindowRect(&drect);
    CPoint DUpLeft = CPoint((rect.Width() - drect.Width())/2, (rect.Height() - drect.Height())/2);
    drect.OffsetRect(DUpLeft);
    m_headband.MoveWindow(&drect);
    m_headband.ShowWindow(SW_SHOW);
    m_headband.UpdateWindow();

    InitCommonControls();
    
        BOOL ret = InitEiC();
    m_headband.DestroyWindow();
    
    return ret;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
        CAboutDlg();

// Dialog Data
        //{{AFX_DATA(CAboutDlg)
        enum { IDD = IDD_ABOUTBOX };
        //}}AFX_DATA

        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CAboutDlg)
        protected:
        virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
        //}}AFX_VIRTUAL

// Implementation
protected:
        //{{AFX_MSG(CAboutDlg)
                // No message handlers
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
        //{{AFX_DATA_INIT(CAboutDlg)
        //}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
        CDialog::DoDataExchange(pDX);
        //{{AFX_DATA_MAP(CAboutDlg)
        //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
        //{{AFX_MSG_MAP(CAboutDlg)
                // No message handlers
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CHawkApp::OnAppAbout()
{
        CAboutDlg aboutDlg;
        aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CHawkApp message handlers

/* My version of printf function... */
int eic_hawk_charout(int c, void* buf)
{
    CHawkApp* app = (CHawkApp*)AfxGetApp();
//    if(app->m_pipeDataSize > )
    CString& str = *(CString*)buf;
    char text = (char)c;
    str += CString(text);

/*    if(WaitForSingleObject(app->m_printfMutex, INFINITE) != WAIT_OBJECT_0)
    {
        ASSERT(0);
        v.ival = 0;
        return v;
    };*/
    return 1;
}

extern "C"
{
int _eicUprintf(int (*output)(int, void*), void *arg, char *fmt, arg_list ap);
}

static val_t eic_hawk_printf()
{
    CHawkApp* app = (CHawkApp*)AfxGetApp();
    CMainFrame* frame = (CMainFrame*)AfxGetMainWnd();

    val_t v;
    arg_list ag = getargs();
    char *fmt = (char*)nextarg(ag,ptr_t).p;
    CString buf;
    v.ival = _eicUprintf(eic_hawk_charout, (void*)&buf, fmt, ag);

    frame->m_pRunDoc->GetLogView()->AddString(LPCTSTR(buf));
//    ReleaseMutex(app->m_printfMutex);
    
    return v;
}

static void _Hawk_MessageDisplay(char* str)
{
    AfxMessageBox(str);
}

/*static val_t eic_Hawk_uni_wrap()
{
    val_t v;

    uni_wrap(stub_f(arg(0, getargs(), ptr_t).p), 
        (int*)arg(1, getargs(), ptr_t).p,
        (char*)arg(2, getargs(), ptr_t).p,
        (char*)&v);

    return v;
}*/

BOOL CHawkApp::InitEiC()
{
    InitEiCHandles();    

    // Initialize the module's path string
    InitModulePath();

    SetStatusString("Initializing EiC...");
    EiC_init_EiC();
    char _argv[] = "";
    char *_pargv[2] = {_argv, 0};
    EiC_startEiC(1, _pargv);
    SetStatusString("Initializing standard C library...");
    stdClib();
    EiC_add_builtinfunc("printf", eic_hawk_printf);
/*
    // Setup the signals messaging
    EiC_messageDisplay = _Hawk_MessageDisplay;*/

    // Initializing EiC plugin functions
    SetStatusString("Initializing HighGUI library...");
    module_highguiwrap();
    SetStatusString("Initializing converters library...");
    module_convertwrap();
    LoadPlugins();
/*
    EiC_parseString("typedef struct _a {double v;int w;char t;} a;");
    EiC_parseString("int f(a b) {return b.w;};");
    EiC_parseString("struct a b;f(b);\\int e");
    EiC_parseString("struct a c;");

    EiC_parseString("struct _b {char t;};");
    EiC_parseString("struct _a b;");
    symentry_t* sym = EiC_lookup(1, "a");
    struct_t* s = (struct_t*)sym->type->nxt->u.inf;
    func_t* funcDesc = (func_t*)sym->type->u.inf;
    parm_t* parmDesc = funcDesc->parm;
    s = (struct_t*)parmDesc->type->u.inf;*/

    // Initializing HighGUI
    SetInstance(AfxGetApp()->m_hInstance);
    add_search_path(LPCTSTR(m_modulePath + CString("bitmaps")));
    add_search_path(LPCTSTR(m_modulePath + CString("..\\..\\..\\apps\\Hawk\\bitmaps")));
    AddVideoPath(m_modulePath + CString("Video"));
    AddVideoPath(m_modulePath + CString("..\\..\\..\\apps\\Hawk\\Video"));

    // Initializing EiC
    EiC_switches(cline);

    // Define the universal wrapper function
    EiC_parseString("void _Hawk_uniwrap(void*,int*,char*,int*, void*);");

    // First lets find the wrappers directory
    m_wrappersPath = m_modulePath + CString("wrappers");
    CString inc = CString(":-I ") + m_wrappersPath;
//    EiC_parseString(const_cast<char*>(LPCTSTR(inc)));
    inc += CString("\\std");
//    EiC_parseString(const_cast<char*>(LPCTSTR(inc)));

    EiC_parseString("#pragma push_unsafeptr");

    /* Make the source compatible with C standard */
    EiC_parseString("#define __stdcall");
    EiC_parseString("#define __cdecl");
    EiC_parseString("#define __declspec(a)");
    EiC_parseString("typedef struct{int l,h;} __int64;");

    /* Definitions for IPL */
    EiC_parseString("#define IPL_WINDOWS");
    EiC_parseString("#define IPLAPI(type, name, arg) type name arg;");

    /* Definitions for OpenCV */
    EiC_parseString("#define CV_INLINE");
    EiC_parseString("#define CVL_TYPES");
    /* Temporary! Inserted because of EiC bug. */
    EiC_parseString("struct CvSubdiv2DPoint;");

    /* Enum all include dirs and headers */
    char curDir[_MAX_PATH];
    GetCurrentDirectory(_MAX_PATH, curDir);
    SetCurrentDirectory(m_wrappersPath);
    EnumHeaders(m_wrappersPath);

    // Set include directories
    for(int i = 0; i < m_includeDirs.size(); i++)
    {
        EiC_parseString(":-I %s", m_includeDirs[i].c_str());
    }

    // Include headers
    for(i = 0; i < m_includeFiles.size(); i++)
    {
        string str;
        str = string("Parsing header ") + m_includeFiles[i] + "...";
        SetStatusString(str.c_str());
        Attach(m_includeFiles[i]);
    }
    SetCurrentDirectory(curDir);

    char textBuffer[2048];
    rewind(m_eicErr.read);
    int err = _read(_fileno(m_eicErr.read), textBuffer, 2047);
    if(err > 1)
    {
        textBuffer[err] = 0;
        AfxMessageBox(textBuffer);
    }
    _chsize(_fileno(m_eicErr.read), 0);
#ifdef NDEBUG
    const char* libName = "cv.dll";
#else
    const char* libName = "cvd.dll";
#endif
    
    LoadModuleFunctions(libName, "OpenCV");

#ifdef NDEBUG
    const char* auxlibName = "cvaux.dll";
#else
    const char* auxlibName = "cvauxd.dll";
#endif
    
    LoadModuleFunctions(auxlibName, "OpenCVAux");

/*
#ifdef NDEBUG
        const char* libName1 = "3Dface.dll";
#else
        const char* libName1 = "3Dfaced.dll";
#endif
    
    LoadModuleFunctions(libName1, "3Dface");*/

    LoadModules();

    EiC_parseString("#pragma pop_ptr");

    SetStatusString("Almost done...");
    // Initialize context menus
    InitPopupMenu();
    InitPopupDialogs();
    // Update error marks
    UpdateMark();
    // Loading Hawk configuration
    m_errlevel = (errlevel_t)GetProfileInt("Configuration", "Error level", (int)unsafe);
    SetErrLevel(m_errlevel);
    m_sbRun = GetProfileInt("Configuration", "Autosave before run", TRUE);

    // Remember EiC's state
    EiC_parseString(":reset here");

    return TRUE;
}

BOOL CHawkApp::InitModulePath()
{
    // Find the full path for this executable
    HMODULE hnd = GetModuleHandle(LPCTSTR(m_pszExeName));
    char buff[128];
    GetModuleFileName(hnd, buff, 128);

    char drive[_MAX_DRIVE], dir[_MAX_DIR], fName[_MAX_FNAME], ext[_MAX_EXT];
    _splitpath(buff, drive, dir, fName, ext);

    m_modulePath.Format("%s%s",drive,dir);

    return TRUE;
}

BOOL CHawkApp::FindAndAttach(LPCTSTR path, LPCTSTR fileName)
{
    char buffer[2048];
    char* pFinal;

    int length = SearchPath(path, fileName, ".h", 2048, buffer, &pFinal);
    if(length > 0)
    {
        return Attach(buffer);
    }
    else
    {
        CString str = CString("Wrapper file ") + CString(fileName) + 
                CString(".h has not been found!\n") + 
                CString("Functions declared in the file will not be ") + 
                CString("available during current session.");
        AfxMessageBox(str);
        return FALSE;
    }
}


LPCTSTR CHawkApp::GetModulePath()
{
        return LPCTSTR(m_modulePath);
}

void CHawkApp::LoadPlugins()
{
    long searchHandle;
    BOOL isAnother = TRUE;
    _finddata_t data;
    CString dir, str;
    dir = m_modulePath + CString("\\plugins\\");
    str = dir + CString("*.dll");

    searchHandle = _findfirst(LPCTSTR(str), &data);
    if(searchHandle == -1)
    {
        return;
    }

    while(isAnother)
    {
        CString str;
        str.Format("Loading %s plugin...", data.name);
        SetStatusString(LPCTSTR(str));
        HMODULE module;
        module = LoadLibrary(LPCTSTR(dir + CString(data.name)));
        if(module && LoadPluginFunctions(module))
        {
            CString str(data.name);
            m_plugins.GetData()[m_plugins.GetSize() - 1].m_path = str.Left(str.GetLength() - 4);
        }
        else
        {
            CString str;
            str.Format("Failed to load %s plugin!", data.name);
            AfxMessageBox(str);

            if(module)
            {
                FreeLibrary(module);
            }
        }

        isAnother = !_findnext(searchHandle, &data);
    }
}

BOOL CHawkApp::LoadPluginFunctions(HMODULE module)
{
    plugin_t plugin;

    // Check if this is Hawk dll
    plugin.m_GetInfo = (void (*)(plugin_info*))GetProcAddress(module, "PluginGetInfo");
    plugin.m_SetEiCStack = (void (*)(AR_t**))GetProcAddress(module, "SetEiCStack");
    plugin.m_SetEiCCallback = (void (*)(void(*)(void*)))GetProcAddress(module, "SetEiCCallback");
    plugin.m_GetFunctions = (void (*)(char***, val_t (***)(void), int*))
        GetProcAddress(module, "GetFunctions");
    plugin.m_SetErrLevel = (void(*)(errlevel_t))GetProcAddress(module, "SetErrLevel");
    plugin.m_SetErrMark = (void(*)(jmp_buf*))GetProcAddress(module, "SetErrMark");
    if(!plugin.m_SetEiCStack || !plugin.m_GetFunctions || !plugin.m_SetEiCCallback ||
        !plugin.m_SetErrLevel || !plugin.m_SetErrMark)
    {
        return FALSE;
    }

    // Get the plugin info
    plugin.m_GetInfo(&plugin.m_info);
    
    // Set eic's stack
    plugin.m_SetEiCStack(AR);
    plugin.m_SetEiCCallback(EiC_callBack);
    plugin.m_SetErrMark(&m_mark);

    // Get all functions wrappers
    char** func_names;
    val_t(**funcs)(void);
    int funcs_count;
    plugin.m_GetFunctions(&func_names, &funcs, &funcs_count);

    // Register functions in EiC and update names array
    CStringArray* names = new CStringArray;
    for(int i = 0; i < funcs_count; i++)
    {
        if(funcs[i])
        {
            EiC_add_builtinfunc(func_names[i], funcs[i]);
            for(int j = 0;; j++)
            {
                if(j < names->GetSize())
                {
                    if(strcmp(func_names[i], LPCTSTR(names->GetData()[j])) < 0)
                    {
                        names->InsertAt(j, CString(func_names[i]));
                        break;
                    }
                }
                else
                {
                    names->Add(CString(func_names[i]));
                    break;
                }
            }
        }
    }
    plugin.m_functions = names;
    plugin.m_handle = module;
    m_plugins.Add(plugin);

    return TRUE;
}

void CHawkApp::InitPopupMenu()
{
    m_mainMenu.CreatePopupMenu();
    for(int i = 0; i < m_plugins.GetSize(); i++)
    {
        m_mainMenu.AppendMenu(MF_STRING | (i%30 || !i ? 0 : MF_MENUBARBREAK), 
            (i + 1)<<16, LPCTSTR(m_plugins.GetData()[i].m_info.name));
    }
}

CMenu* CHawkApp::GetContextMenu()
{
    return &m_mainMenu;
}

CStringArray* CHawkApp::GetFunctions(int i)
{
    return m_plugins.GetData()[i].m_functions;
}

void CHawkApp::ExitEiC()
{
    for(int i = 0; i < m_eicFiles.GetSize(); i++)
    {
        char str[8192];
        sprintf(str, ":clear %s", LPCTSTR(m_eicFiles[i]));
        EiC_parseString(str);
    }

    EiC_parseString(":clear ::EiC::");

    EiC_xalloc_CleanUp(0, UINT_MAX);
}

int CHawkApp::ExitInstance() 
{
    OleUninitialize();
    ExitEiC();  
    HGExit();

    // Save Hawk configuration
    WriteProfileInt("Configuration", "Error level", m_errlevel);
        return CWinApp::ExitInstance();
}

void CHawkApp::SetErrLevel(errlevel_t level)
{
    m_errlevel = level;
    set_highgui_errlevel(level);
    set_hawk_errlevel(level);
    set_eic_errlevel(level);
    for(int i = 0; i < m_plugins.GetSize(); i++)
    {
        if(m_plugins.GetData()[i].m_SetErrLevel)
            m_plugins.GetData()[i].m_SetErrLevel(level);
    }
}

errlevel_t CHawkApp::GetErrLevel()
{
    return m_errlevel;
}

void CHawkApp::UpdateMark(jmp_buf *mark)
{
    jmp_buf* realmark = mark ? mark : &m_mark;

    set_highgui_mark(realmark);
    set_hawk_mark(realmark);
    set_eic_mark(realmark);
    for(int i = 0; i < m_plugins.GetSize(); i++)
    {
        if(m_plugins.GetData()[i].m_SetErrMark)
            m_plugins.GetData()[i].m_SetErrMark(realmark);
    }
}

BOOL CHawkApp::GetSBRun()
{
    return m_sbRun;
}

void CHawkApp::SetSBRun(BOOL sbRun)
{
    m_sbRun = sbRun;
}

void CHawkApp::SetStatusString(LPCTSTR str)
{
    m_headband.SetDlgItemText(IDC_STATUS, str);
}

void CHawkApp::AddVideoPath(const CString& path)
{
    m_videoPath.Add(path);
}

const CStringArray& CHawkApp::GetVideoPath()
{
    return m_videoPath;
}

BOOL CHawkApp::InitEiCHandles()
{/*
    // Open a pipe to read EiC's stdout
    int handles[2];

    // Creating a pipe for eicout:
    int error = _pipe(handles, 9128, _O_TEXT);
    if(error)
    {
        AfxMessageBox("Failed to create an output buffer for EiC...");
        return FALSE;
    }

    m_eicOut.read = fdopen(handles[0], "r");
    m_eicOut.write = fdopen(handles[1], "w");

    // Creating a pipe for eicerr:
    error = _pipe(handles, 9128, _O_BINARY);
    if(error)
    {
        AfxMessageBox("Failed to create an output buffer for EiC...");
        return FALSE;
    }

    m_eicErr.read = fdopen(handles[0], "r");
    m_eicErr.write = fdopen(handles[1], "w");*/

    m_printfMutex = CreateMutex(NULL, FALSE, "EiC stdout");
//    m_eicOut.read = m_eicOut.write = freopen("__stdout.temp", "w+", stdout);
    _fmode = _O_BINARY;
    char* tn = tempnam(GetModulePath(), "__eiCErrTemp.");
    m_EiCErrFile = CString(tn);
    free(tn);
    m_eicErr.read = freopen(LPCTSTR(m_EiCErrFile), "w+", stderr);
    m_eicErr.write = m_eicErr.read;
    rewind(m_eicErr.read);

    return TRUE;
}

void CHawkApp::CloseEiCHandles()
{
    CloseHandle(m_printfMutex);
//    fclose(m_eicOut.write);
    fclose(m_eicErr.write);
    remove(LPCTSTR(m_EiCErrFile));
}


int get_uweic_type(type_expr* type) 
{
    struct_t* s;
#define _TYPE_CASE(x)   case t_##x: return sizeof(x)
#define _TYPE_UCASE(x)   case t_##x: case t_u##x: return sizeof(x)

    switch(type->obj)
    {
        _TYPE_UCASE(char);
        _TYPE_UCASE(short);
        _TYPE_UCASE(int);
        _TYPE_UCASE(long);
        _TYPE_CASE(enum);
        _TYPE_CASE(float);
        _TYPE_CASE(double);

    case t_pointer:
        return sizeof(void*);

    case t_struct:
    case t_union:
        s = (struct_t*)(type->u.inf);
        return s->tsize;

    case t_void:
    case t_var:
        return 0;
        
    default:
        ASSERT(0);
        return -1;
    }

#undef _TYPE_UCASE
#undef _TYPE_CASE
}

BOOL CHawkApp::GenAutoWrapper(void* func, LPCTSTR func_name)
{
    // Find EiC description for the function 
    symentry_t* sym = (symentry_t*)EiC_lookup(1, const_cast<char*>(func_name));
    if(!sym)
    {
//        ASSERT(0);
        /* Function not found */
        return -1;
    }

    // Get the function return type string
    CString ret = GetTypeString(sym->type->nxt);

    // Generate the argument list: (type0 x0, type1 x1, etc..., typen xn)
    CString argstr("(");
    func_t* funcDesc = (func_t*)sym->type->u.inf;
    parm_t* parmDesc = funcDesc->parm;
    CString _argstr;
    CString _argfstr;
    for(int p = 0; p < funcDesc->Num - 1; p++)
    {
        type_expr* type = parmDesc[p].type;
        if(type->obj == t_pointer && type->nxt->obj == t_funcdec)
        {
            /* Function contains callbacks */
            return -2;
        }
         _argstr.Format("x%d", p);
        argstr += GetTypeString(parmDesc[p].type, _argstr) /*+ " " + _argstr */ + ",";
    }
    if(funcDesc->Num == 1 && parmDesc[p].type->obj == t_var)
    {
        argstr += ")";
    }
    else
    {
        _argstr.Format("x%d", p);
        argstr += GetTypeString(parmDesc[p].type, _argstr) /*+ " " + _argstr*/ + ")";
    }

    // Define auxiliary EiC function
        // First, the return type and function name
    CString str =  ret + " " + CString(func_name);

        // Then, the function parameters
    str += argstr;

    // Now, the function body:
        // First of all, generate the argi array of arguments types
    CString argistr;
    argistr.Format("int argi[%d] = ", funcDesc->Num + 3);
    CString arginitstr;
            // argi initializer
    int* argi = new int[funcDesc->Num + 3];

    argi[1] = funcDesc->Num;
    arginitstr.Format("%d,", funcDesc->Num);

    CString temp;
    if(sym->type->nxt->obj == t_float)
    {
        argi[2] = EICEX_TYPE_FLOAT;
        temp.Format("%d,", EICEX_TYPE_FLOAT);
    }
    else if(sym->type->nxt->obj == t_double)
    {
        argi[2] = EICEX_TYPE_DOUBLE;
        temp.Format("%d,", EICEX_TYPE_DOUBLE);
    }
    else
    {
        argi[2] = get_uweic_type(sym->type->nxt);
        temp.Format("%d,", argi[2]);
    }
    arginitstr += temp;

    for(p = 0; p < funcDesc->Num - 1; p++)
    {
        argi[3 + p] = get_uweic_type(parmDesc[p].type);
        temp.Format("%d,",argi[3 + p]);
        arginitstr += temp;
    }
    argi[3 + p] = get_uweic_type(parmDesc[p].type);
    temp.Format("%d", argi[3 + p]);
    arginitstr += temp;

    argi[0] = stack_size(argi + 1);
    temp.Format("%d,", argi[0]);
    arginitstr  = temp + arginitstr;
    argistr += CString("{") + arginitstr + "};";
    str += CString("{") + argistr;

    // argi is not needed any more...
    delete argi;
    argi = 0;
            // Generate the nonscalar arguments list

    argistr.Format("int nslist[] = {%d", 0/*funcDesc->Num - 1*/);
    for(p = 0; p < funcDesc->Num; p++)
    {
        if(parmDesc[p].type->obj == t_struct || parmDesc[p].type->obj == t_union)
            argistr += CString(",1");
        else
            argistr += CString(",0");
    }
    argistr += CString("};");
    str += argistr;

            // Generate the function address
    CString addrstr;
    addrstr.Format("%d", (int)func);
    str += "void* xr=" + addrstr + ";";
            // Now generate the return buffer
    if(sym->type->nxt->obj != t_void)
    {
        argistr.Format("(char*)%d", 1);
        str += GetTypeString(sym->type->nxt) + " ret;";
        str += CString("_Hawk_uniwrap(xr, argi, " + argistr + ", nslist, (void*)&ret);return ret;};");
    }
    else
    {
        argistr.Format("(char*)%d", 0);
        str += CString("_Hawk_uniwrap(xr, argi, " + argistr + ", nslist, 0);};");
    }
    EiC_parseString(const_cast<char*>(LPCTSTR(str)));
    if(EiC_ParseError)
    {
        ASSERT(0);
        return FALSE;      
    }
#ifndef NDEBUG
    m_wrapperStrings.Add(str);
#endif
    return TRUE;
}

CString CHawkApp::GetTypeString(void* _type, const char* name)
{
    if(!_type)
    {
        ASSERT(0);
        return CString("");
    }
        
    
    type_expr* type = (type_expr*)_type;

    // Check typedef
    if(type->sym)
    {
        symentry_t* sym = (symentry_t*)type->sym;
        if(sym->sclass == c_typedef)
            return CString(sym->id) + " " + name;
    }

#define _TYPE_CASE(x) case t_##x: return CString(#x) + " " + name
#define _TYPE_UCASE(x) case t_u##x: return CString("unsigned " #x) + " " + name;
    switch(type->obj)
    {
        _TYPE_CASE(void);
        _TYPE_CASE(char);
        _TYPE_UCASE(char);
        _TYPE_CASE(short);
        _TYPE_UCASE(short);
        _TYPE_CASE(int);
        _TYPE_CASE(enum);
        _TYPE_UCASE(int);
        _TYPE_CASE(long);
        _TYPE_UCASE(long);
        _TYPE_CASE(float);
        _TYPE_CASE(double);
    case t_pointer:
        {
            CString _name;
            int flag = 0;
            type_expr* t = type;
            while(t && t->obj != t_array) t = t->nxt;
            if(t)
            {
                CString size;
                size.Format("[%d]", type->u.sz);
                _name = name + size;
                flag = 1;
            }
            else
            {
                _name = CString("*") + name;
                if(type->nxt->obj == t_func || type->nxt->obj == t_funcdec)
                    _name = CString("(") + _name + ")";
            }
            return GetTypeString(type->nxt, _name) /*+ 
                (type->nxt->obj == t_funcdec || flag ? CString() : CString("*"))*/;
        }

    case t_struct:
    case t_union:
        {
            CString str = type->obj == t_struct ? CString("struct ") : CString("union ");
            if(type->sym)
            {
                symentry_t* sym = (symentry_t*)type->sym;
                if(sym->sclass & c_typedef)
                    str = CString(sym->id);
                else
                    str += CString(sym->id);
                return str + " " + name;
            }
            else
            {
                CString ptr;
                ptr.Format("struct_%d", (unsigned int)type);

                if(AddStructType(type))
                {
                    str += ptr + "{";
                    struct_t* s = (struct_t*)type->u.inf;
                    for(int i = 0; i < s->n; i++)
                    {
                        str += GetTypeString(s->type[i]) + CString(";");
                    }
                    str += CString("}");
                    return str + " " + name;
                }
                else
                {
                    str += ptr;
                    return str + " " + name;
                }
            }
        }

    case t_func:
    case t_funcdec:
    case t_builtin:
        {
            if(!type->nxt && !type->u.inf)
                return CString("");
            CString str = GetTypeString(type->nxt);
            CString str1;
            str1.Format("%s ( ", name);
            str += str1;
            func_t* funcDesc = (func_t*)type->u.inf;
            parm_t* parmDesc = funcDesc->parm;
            for(int i = 0; i < funcDesc->Num - 1; i++)
            {
                str += GetTypeString(parmDesc[i].type) + " ,";
            }
            str += GetTypeString(parmDesc[i].type) + " )";
            return str;
            
        }        
        break;
    case t_array:
        {
            CString str;
            CString ptr;
            ptr.Format("_%d", (int)type);
            CString _name = CString(name).IsEmpty() ? CString("array") + ptr : CString(name);
            ptr.Format("%d", type->u.sz);
            str = GetTypeString(type->nxt) + " " + name + "[" + ptr + "]";
            return str;
        }

    case t_var:
        {
            return "...";
        }
    default:
        ASSERT(0);
        return CString("");
    }
}

void CHawkApp::LoadModuleFunctions(LPCTSTR filename, LPCTSTR modulename)
{
    CString str;
    str.Format("Attaching module %s...", filename);
    SetStatusString(str);
    
    CStringArray* names = new CStringArray;
    EnumModuleFunctions(filename, *names);

    /* Now load all functions... */
    HMODULE module = LoadLibrary(filename);
    for(int j = 0; j < names->GetSize(); j++)
    {
        LoadModuleFunction(module, (*names)[j], TRUE);
    }

    plugin_t plugin;
    plugin.m_handle = module;
    char buffer[_MAX_PATH];
    GetModuleFileName(module, buffer, _MAX_PATH);
    plugin.m_path = CString(buffer);
    strcpy(plugin.m_info.name, modulename);
    plugin.m_functions = names;
    plugin.m_GetFunctions = 0;
    plugin.m_GetInfo = 0;
    plugin.m_SetEiCCallback = 0;
    plugin.m_SetEiCStack = 0;
    plugin.m_SetErrLevel = 0;
    plugin.m_SetErrMark = 0;
    m_plugins.Add(plugin);
}

BOOL CHawkApp::AddStructType(const type_expr *type)
{
    for(int i = 0; i < m_structTypes.GetSize(); i++)
        if(m_structTypes.GetData()[i] == (void*)type)
            return FALSE;

    m_structTypes.Add((void*)type);
    return TRUE;
}

BOOL CHawkApp::Attach(string filename)
{
    string str;
    str = string("#include \"") + filename + "\"";
    EiC_parseString(const_cast<char*>(str.c_str()));
    m_eicFiles.Add(CString(filename.c_str()));
    return TRUE;
}

BOOL CHawkApp::EnumHeaders(LPCTSTR path)
{
    string data = string(path) + "\\wrappers.in";
    ifstream headers(data.c_str());
    string _path(path);
    while(!headers.eof())
    {
        string str, full;
        headers >> str;
        full = _path + "\\" + str;

        char _filename[_MAX_FNAME], _ext[_MAX_EXT];
        _splitpath(str.c_str(), 0, 0, _filename, _ext);
        string filename = string(_filename) + _ext;
        /* Found a header file or a folder. Remember it! */
        CFileFind finder;
        if(!finder.FindFile(full.c_str()))
        {
            CString str;
            str.Format("Cannot find %s", full.c_str());
            AfxMessageBox(str);
            continue;
        }
        finder.FindNextFile();
        if(finder.IsDirectory())
        {
            m_includeDirs.push_back(str);
        }
        else
        {
            m_includeFiles.push_back(filename);
            m_includeFilePath.push_back(full);
        }
    }

    return TRUE;
}

BOOL CHawkApp::EnumModuleFunctions(LPCTSTR filename, CStringArray &names)
{
        HANDLE hFile;
        HANDLE hFileMapping;
        LPVOID lpFileBase;

    CString errorMessage;
    errorMessage.Format("Failed to load the library %s", filename);

    char buffer[_MAX_PATH];
    LPSTR filePart;
    int ret = SearchPath(0, filename, 0, _MAX_PATH, buffer, &filePart);
        if(!ret)
        {
        AfxMessageBox(errorMessage);
                return FALSE;
        }

    hFile = CreateFile(buffer, GENERIC_READ, FILE_SHARE_READ, NULL,
                                                OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
                                        
        if ( hFile == INVALID_HANDLE_VALUE )
        {
        AfxMessageBox(errorMessage);
                return FALSE;
        }

        hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
        if ( hFileMapping == 0 )
        {
                CloseHandle(hFile);
        AfxMessageBox(errorMessage);
                return FALSE;
        }

        lpFileBase = MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, 0);
        if ( lpFileBase == 0 )
        {
                CloseHandle(hFileMapping);
                CloseHandle(hFile);
        AfxMessageBox(errorMessage);
                return FALSE;
        }

        PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER)lpFileBase;
        if(dosHeader->e_magic != IMAGE_DOS_SIGNATURE)
    {
        CString errorMessage;
        errorMessage.Format("The file %s does not appear to be a valid dynamic link library.", buffer);
        AfxMessageBox(errorMessage);
        return FALSE;
    }

#define MakePtr( cast, ptr, addValue ) (cast)( (DWORD)(ptr) + (addValue) )
    
        PIMAGE_NT_HEADERS pNTHeader;
        DWORD base = (DWORD)dosHeader;
        PIMAGE_EXPORT_DIRECTORY exportDir;


        pNTHeader = MakePtr( PIMAGE_NT_HEADERS, dosHeader,
                                                                dosHeader->e_lfanew );
    PIMAGE_OPTIONAL_HEADER optionalHeader = &pNTHeader->OptionalHeader;
        exportDir = MakePtr(PIMAGE_EXPORT_DIRECTORY, base,
                                                 optionalHeader->DataDirectory[0].VirtualAddress);
    char** name = MakePtr(char**, base, exportDir->AddressOfNames);

        for (UINT i = 0; i < exportDir->NumberOfNames; i++)
        {
        const char* str = *(name + i) + base;
        int isCfunc = 1;
        for(const char* p = str; *p != 0; p++)
        {
            char c = *p;
            if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_' || (c >= '0' && c <= '9'))
                continue;
            else
            {
                isCfunc = 0;
                break;
            }
        }

        if(isCfunc)
            names.Add(str);
        }
    
        UnmapViewOfFile(lpFileBase);
        CloseHandle(hFileMapping);
        CloseHandle(hFile);

    return TRUE;
}

BOOL CHawkApp::LoadModuleFunction(HMODULE handle, LPCTSTR name, BOOL isOpenCV)
{
    FARPROC addr = GetProcAddress(handle, name);
    if(isOpenCV && (CString(name) == "cvFitLine2D" || CString(name) == "cvFitLine3D"))
    {
        // The wrappers for these functions are already ok
        return TRUE;
    }

    if(GenAutoWrapper(addr, name) == -2)
    {
        if(!isOpenCV)
        {
            CString str;
            str.Format("Function %s takes a function pointer as input.\n\
This function will not be available in the current Hawk session.\nRefer fo the documentation for further details",
                name);
            AfxMessageBox(str);
        }
    }
    return TRUE;
}

BOOL CHawkApp::LoadModules()
{
    /* First of all, look for plugins that have a PLUG_ALL option */
    for(int i = 0; i < m_plugins.GetSize(); i++)
    {
        plugin_t& plugin = m_plugins[i];
        if(plugin.m_info.type == PLUG_ALL)
        {
            /* Initialize the rest of functions with universal wrappers */
            CStringArray all;
            EnumModuleFunctions(plugin.m_info.library_path, all);
            HMODULE module = LoadLibrary(plugin.m_info.library_path);
            for(int i = 0; i < all.GetSize(); i++)
            {
                CString buf;
                if(!FindStringInArray(*plugin.m_functions, all[i]))
                {
                    LoadModuleFunction(module, all[i], TRUE);
                }
            }
        }
    }

    return TRUE;
}

extern "C"
{
extern keyword_t cwords[];
}
CString CHawkApp::GenDecl(const char *name)
{
    symentry_t* sym = EiC_lookup(1, const_cast<char*>(name));
    if(!sym)
        return CString(""); // Name not found

    // Make sure this is not a simple keyword or typedef 
    if(EiC_iskeyword(cwords, const_cast<char*>(name), 36) || 
        (sym->sclass & c_typedef))
        return CString("");


    return GetTypeString(sym->type, name);
}

CFuncDialog* CHawkApp::GetFuncDialog(int index)
{
    return (CFuncDialog*)m_funcDialogs[index];
}

void CHawkApp::InitPopupDialogs()
{
    for(int i = 0; i < m_plugins.GetSize(); i++)
    {
        /* Initialize the context dialog */
        CFuncDialog* dlg = new CFuncDialog;
        dlg->SetModuleName(m_plugins.GetData()[i].m_info.name);
        m_funcDialogs.Add(dlg);
    }
}

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
//M*/// Hawk.h : main header file for the HAWK application
//

#if !defined(AFX_HAWK_H__6FFD53A7_939A_11D3_AE7E_00A0C9989BC6__INCLUDED_)
#define AFX_HAWK_H__6FFD53A7_939A_11D3_AE7E_00A0C9989BC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
        #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#include "HeadBand.h"
#include "FuncDialog.h"
#include "eicdllwrap.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
#include "hawkwrap.h"
#include <eic.h>
#ifdef malloc
#undef malloc
#endif
#ifdef realloc
#undef realloc
#endif
#ifdef free
#undef free
#endif
#ifdef __cplusplus
}
#endif // __cplusplus

#pragma warning(disable:4786)
#include <vector>
#include <string>
//#include <xstring>
using namespace std;


typedef struct
{
    FILE* read;
    FILE* write;
} stream_pipe;

/////////////////////////////////////////////////////////////////////////////
// CHawkApp:
// See Hawk.cpp for the implementation of this class
//

typedef struct
{
    CString m_path;
    HMODULE m_handle;
    CStringArray* m_functions;
    plugin_info m_info;
    void (*m_GetInfo)(plugin_info*);
    void (*m_SetErrLevel)(errlevel_t);
    void (*m_SetErrMark)(jmp_buf*);
    void (*m_SetEiCStack)(AR_t**);
    void (*m_SetEiCCallback)(void(*)(void*));
    void (*m_GetFunctions)(char***, val_t (***)(void), int*);
} plugin_t;

template<> void AFXAPI DestructElements<CMenu*> (CMenu** pElements, int nCount);
typedef CArray<CMenu*, CMenu*> CMenuArray;

template<> void AFXAPI DestructElements<plugin_t> (plugin_t* pElements, int nCount);
typedef CArray<plugin_t, plugin_t&> CPluginArray;

struct type_expr;

typedef void(__cdecl *HAWK_SIGFUNC)(int);

//typedef basic_string<char> string;

class CHawkApp : public CWinApp
{
private:
    CArray<void*, void*> m_funcDialogs;
    CMenu m_mainMenu;
    CMenuArray m_childMenus;
    CHeadBand m_headband;
    
public:
        CFuncDialog* GetFuncDialog(int index);
        CString GenDecl(const char* name);
        BOOL LoadModuleFunction(HMODULE handle, LPCTSTR name, BOOL isOpenCV);
        BOOL EnumModuleFunctions(LPCTSTR filename, CStringArray& names);
        BOOL EnumHeaders(LPCTSTR path);
        BOOL Attach(string filename);
        int m_pipeDataSize;
#ifndef NDEBUG
    CStringArray m_wrapperStrings;
#endif
        void LoadModuleFunctions(LPCTSTR filename, LPCTSTR modulename);
        CString GetTypeString(void* _type, const char* name = "");
        CString m_EiCOut;
        HANDLE m_printfMutex;
    HANDLE m_dsMutex;
        void CloseEiCHandles();
        BOOL InitEiCHandles();
        const CStringArray& GetVideoPath();
        void AddVideoPath(const CString& path);
        void SetStatusString(LPCTSTR str);
        void SetSBRun(BOOL sbRun);
        BOOL GetSBRun();
        void UpdateMark(jmp_buf* mark = 0);
    CPluginArray m_plugins;
        jmp_buf m_mark;
        errlevel_t GetErrLevel();
        void SetErrLevel(errlevel_t level);
        void ExitEiC();
        CStringArray* GetFunctions(int i);
        CMenu* GetContextMenu();
        void InitPopupMenu();
        LPCTSTR GetModulePath();
        BOOL FindAndAttach(LPCTSTR path, LPCTSTR fileName);
        stream_pipe m_eicOut;
    stream_pipe m_eicErr;

    CMap<int, int, HAWK_SIGFUNC, HAWK_SIGFUNC> m_eicSigFuncs;

    BOOL InitEiC();
        CHawkApp();
    ~CHawkApp();

// Overrides
        // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CHawkApp)
        public:
        virtual BOOL InitInstance();
        virtual int ExitInstance();
        //}}AFX_VIRTUAL

// Implementation
        //{{AFX_MSG(CHawkApp)
        afx_msg void OnAppAbout();
                // NOTE - the ClassWizard will add and remove member functions here.
                //    DO NOT EDIT what you see in these blocks of generated code !
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
private:
        void InitPopupDialogs();
        BOOL LoadModules();
    vector<string> m_includeDirs;
    vector<string> m_includeFiles;
        vector<string> m_includeFilePath;
        BOOL AddStructType(const type_expr* type);
        CPtrArray m_structTypes;
        BOOL GenAutoWrapper(void* func, LPCTSTR func_name);
        CString m_EiCErrFile;
        CStringArray m_videoPath;
        BOOL m_sbRun;
        errlevel_t m_errlevel;
        CStringArray m_eicFiles;
        BOOL LoadPluginFunctions(HMODULE module);
        void LoadPlugins();
        CString m_wrappersPath;
        CString m_modulePath;
        BOOL InitModulePath();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HAWK_H__6FFD53A7_939A_11D3_AE7E_00A0C9989BC6__INCLUDED_)

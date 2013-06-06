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
//M*/#ifndef __EIC_DLL_WRAP_H__
#define __EIC_DLL_WRAP_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API static
#endif

#include <stdlib.h>
#include <setjmp.h>
#include "eic.h"
#include "hawkwrap.h"

#ifdef DLL_EXPORTS
static errlevel_t errlevel = unsafe;
static jmp_buf* errmark = NULL;

static AR_t** eicAR;
static void (*eicCallBack)(void*);

#ifdef getargs
#undef getargs
#define getargs() eicAR[2]
#endif
#endif /* DLL_EXPORTS */

typedef enum
{
    PLUG_WRAPPERS,
    PLUG_ALL
} plugin_type;

typedef struct _plugin_info
{
    int reserved; /* Reserved for internal use */
    char name[1024]; /* name of plugin */
    char library_path[_MAX_PATH];
    plugin_type type; /* type of plugin */
} plugin_info;

DLL_API void PluginGetInfo(plugin_info* info);

#ifdef DLL_EXPORTS
DLL_API void SetErrLevel(errlevel_t level)
{
    errlevel = level;
}

DLL_API void SetErrMark(jmp_buf* mark)
{
    errmark = mark;
}


DLL_API void SetEiCStack(AR_t** ar)
{
    eicAR = ar;
}

DLL_API void SetEiCCallback(void(*call)(void*))
{
    eicCallBack = call;
}

static void EiC_callBack(void* code)
{
    eicCallBack(code);
}
#else
DLL_API void SetErrLevel(errlevel_t level);
DLL_API void SetErrMark(jmp_buf* mark);
DLL_API void SetEiCStack(AR_t** ar);
DLL_API void SetEiCCallback(void(*call)(void*));
#endif /* DLL_EXPORTS */

DLL_API void GetFunctions(char*** func_names, val_t (***funcs)(void), int* funcs_count);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif /* __EIC_DLL_WRAP_H__ */
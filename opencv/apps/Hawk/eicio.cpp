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
//M*/#include "stdafx.h"

#include "Hawk.h"
#include <stdarg.h>
#include "eicio.h"
#include <stdio.h>

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>
#include <signal.h>

//#include "..\..\..\src\eicio.h"

#pragma warning(disable:4273)

#include "..\module\stdClib\src\stdliblocal.h"
#include "hawkwrap.h"

static errlevel_t errlevel = unsafe;
static jmp_buf* errmark = NULL;

void set_eic_errlevel(errlevel_t level)
{
    errlevel = level;
}

void set_eic_mark(jmp_buf* mark)
{
    errmark = mark;
}

extern "C"
{
extern unsigned int EiC_CurrentLine;
extern char *EiC_CurrentFile;
}

void raiseio(int sig)
{
    char buf[1024];
    sprintf(buf, "Signal with code %d has been raised by EiC in %s, line %d.\nAborting script execution...", 
        sig, EiC_CurrentFile, EiC_CurrentLine);
    init_signal_handlers();
#ifdef HAWK_TEST
    WRAP_THROW_MESSAGE(errmark, buf);
#else
    // Redirect the signal to EiC
    switch(sig)
    {
    case SIGABRT:
    case SIGFPE:
    case SIGSEGV:
    case SIGINT:
        {
            CHawkApp* app = (CHawkApp*)AfxGetApp();
            HAWK_SIGFUNC func;
            if(app->m_eicSigFuncs.Lookup(sig, func))
            {
                func(sig);
            }
        }

    default:
        WRAP_THROW_MESSAGE(errmark, buf);
    }
#endif /* HAWK_TEST */
}

void init_signal_handlers()
{
    CHawkApp* app = (CHawkApp*)AfxGetApp();
    app->m_eicSigFuncs.SetAt(SIGABRT, signal(SIGABRT, raiseio));
    app->m_eicSigFuncs.SetAt(SIGFPE, signal(SIGFPE, raiseio));
    app->m_eicSigFuncs.SetAt(SIGILL, signal(SIGILL, raiseio));
    app->m_eicSigFuncs.SetAt(SIGINT, signal(SIGINT, raiseio));
    app->m_eicSigFuncs.SetAt(SIGSEGV, signal(SIGSEGV, raiseio));
    app->m_eicSigFuncs.SetAt(SIGTERM, signal(SIGTERM, raiseio));
}
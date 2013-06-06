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
//M*/#define EICEX_TYPE_BYTE         1
#define EICEX_TYPE_WORD         2
#define EICEX_TYPE_DWORD        4
#define EICEX_TYPE_QWORD        8
#define EICEX_TYPE_FP           (1 << 20)
#define EICEX_TYPE_FLOAT        (EICEX_TYPE_DWORD + EICEX_TYPE_FP)
#define EICEX_TYPE_DOUBLE       (EICEX_TYPE_QWORD + EICEX_TYPE_FP)

#define EICEX_TYPE_STRUCT       (1 << 21)
#define EICEX_TYPE_SIZEMASK     (EICEX_TYPE_FP - 1)
#define EICEX_RETADDR           (1 << 20)

typedef __int64 int64;
typedef int64 (*stub_f)(void);

static char* get_arg( char* args, int argtype, int argsize, int* nsparams );
static char* next_arg( char* args, int argtype, int argsize, int* nsparams );
int  stack_size( int* argi );
void uni_wrap( stub_f f, int* argi, char* args, int* nsparams, void* retbuf );
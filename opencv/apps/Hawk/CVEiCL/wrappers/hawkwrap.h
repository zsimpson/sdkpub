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
//M*/#ifndef __HAWK_WRAP__
#define __HAWK_WRAP__

#include<setjmp.h>
#include <string.h>

typedef enum
{
    unsafe = 0,
    safe = 1,
} errlevel_t;

typedef enum
{
    result_empty = 0,
    result_string = 1,
} result_code_t;

typedef struct _wrapexcept_t
{
    result_code_t result_code;
    char* message;
} wrapexcept_t;

#ifndef WRAP_THROW_MESSAGE
#define WRAP_THROW_MESSAGE(jmp, msg)\
    {wrapexcept_t* temp_res = (wrapexcept_t*)malloc(sizeof(wrapexcept_t));\
    if(temp_res) {temp_res->result_code = result_string;temp_res->message = strdup(msg);\
    if(jmp){longjmp(*jmp, (int)temp_res);}}}
#endif /* WRAP_THROW_MESSAGE */

#endif /* __HAWK_WRAP__ */

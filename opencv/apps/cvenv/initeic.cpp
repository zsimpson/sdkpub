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
//M*/

#include "stdlib.h"
#include "eic.h"
#include "initeic.h"

int InitEiC()
{
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

    return 0;
}

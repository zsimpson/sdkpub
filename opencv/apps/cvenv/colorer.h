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
#ifndef __COLORER__
#define __COLORER__

#include "cvenv.h"

//#pragma once

#define MAX_TOKNS 1000

#ifndef max
#define max(a,b) a > b ? a : b
#endif

#ifndef min
#define min(a,b) a < b ? a : b
#endif

#ifndef swap
#define swap(a,b) {a -= b; b += a; a = b - a;}
#endif

typedef enum _TokenType
{
    TOKEN_NORMAL  = 0,
    TOKEN_COMMENT = 1,
    TOKEN_STRING  = 2,
    TOKEN_KEYWORD = 3,
    TOKEN_NUMBER  = 4,
    TOKEN_END     = 5
}
MyTokenType;

typedef struct _Token
{
    MyTokenType  type;
    int  start;
}
Token;


typedef struct _Lexer
{
    const  char* text;
    int    pos;
}
Lexer;

//void  InitLexer( Lexer* lexer, const char* text );
//void  GetToken( Lexer* lexer, Token* token );
int ParseTextBegin(ClientData, Tcl_Interp *pinterp, int, char**);
int ParseTextEnd(ClientData, Tcl_Interp *pinterp, int, char**);

bool LoadColors(Tcl_Interp *pinterp,const char* colorsfile);
bool SaveColors(Tcl_Interp *pinterp,const char* colorsfile);


#endif

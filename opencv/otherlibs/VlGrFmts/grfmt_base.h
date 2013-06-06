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

#ifndef _RW_BASE_H_
#define _RW_BASE_H_

#if _MSC_VER >= 1200
    #pragma warning( disable: 4514 )
    #pragma warning( disable: 4711 )
#endif

#include "utils.h"

#define  RBS_BAD_HEADER   -125  /* invalid image header */
#define  BAD_HEADER_ERR()     throw RBS_BAD_HEADER

// GrFmtReader interface
class  GrFmtReader
{
public:
    
    GrFmtReader();

    int           GetSignatureLength() { return m_sign_len; };
    const char*   GetDescription() { return m_description; };
    int           GetWidth()  { return m_width; };
    int           GetHeight() { return m_height; };
    
    virtual bool  CheckFormat( const char* signature );
    void          SetFile( const char* filename );

    virtual int   GetColor() = 0;
    virtual bool  ReadHeader() = 0;
    virtual bool  ReadData( uchar* data, int step, int color ) = 0;
    virtual void  Close() = 0;

protected:
    int          m_width;       // width  of an image ( filled by ReadHeader )
    int          m_height;      // height of an image ( filled by ReadHeader )
    int          m_sign_len;    // length of the signature of the format
    const char*  m_signature;   // signature of the format
    const char*  m_description; // e.g: Graphics interchange format (*.GIF)
    char         m_filename[1000];
};


typedef struct { int stub; } ListPosition;

// list of <GrFmtReader>s
class  GrFmtReadersList
{
public:

    GrFmtReadersList();
    ~GrFmtReadersList();
    void                    RemoveAllReaders();
    void                    AddReader( GrFmtReader* reader );
    int                     ReadersCount() { return m_curReaders; };
    ListPosition*           GetFirstReaderPos();
    GrFmtReader* GetNextReader( ListPosition*& pos );
    GrFmtReader* FindReader( const char* filename );
    int                     GetFiltersString( char* buffer, int maxlen );

protected:

    GrFmtReader** m_readers;
    int  m_maxReaders;
    int  m_curReaders;
};

#endif/*_RW_BASE_H_*/

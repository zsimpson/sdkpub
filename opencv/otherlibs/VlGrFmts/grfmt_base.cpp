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

#include <assert.h>
#include <string.h>

#include "grfmt_base.h"
#include "bitstrm.h"

///////////////////// GrFmtReader //////////////////////////

GrFmtReader::GrFmtReader()
{
    m_width = m_height = -1;
    m_sign_len    = 0;
    m_signature   = 0;
    m_description = 0;
    m_filename[0] ='\0';
}


void  GrFmtReader::SetFile( const char* filename )
{
    assert( filename != 0 && strlen(filename) < sizeof(m_filename) );
    strcpy( m_filename, filename );
}


bool  GrFmtReader::CheckFormat( const char* signature )
{
    assert( signature != 0 );
    return memcmp( m_signature, signature, m_sign_len ) == 0;
}


///////////////////// GrFmtReader_list //////////////////////////

GrFmtReadersList::GrFmtReadersList()
{
    m_readers = 0;
    RemoveAllReaders();
}


GrFmtReadersList::~GrFmtReadersList()
{
    RemoveAllReaders();
}


void  GrFmtReadersList::RemoveAllReaders()
{
    if( m_readers )
    {
        for( int i = 0; i < m_curReaders; i++ ) delete m_readers[i];
        delete m_readers;
    }
    m_readers = 0;
    m_maxReaders = m_curReaders = 0;
}


void  GrFmtReadersList::AddReader( GrFmtReader* reader )
{
    assert( reader != 0 );
    if( m_curReaders == m_maxReaders )
    {
        // reallocate the readers pointers storage
        int new_maxReaders = 2*m_maxReaders;
        if( new_maxReaders < 16 ) new_maxReaders = 16;

        GrFmtReader** newReaders = 
            new GrFmtReader*[new_maxReaders];

        for( int i = 0; i < m_curReaders; i++ ) newReaders[i] = m_readers[i];

        delete m_readers;
        m_readers = newReaders;
        m_maxReaders = new_maxReaders;
    }

    m_readers[m_curReaders++] = reader;
}


ListPosition*  GrFmtReadersList::GetFirstReaderPos()
{
    return (ListPosition*)m_readers;
}


GrFmtReader* GrFmtReadersList::
    GetNextReader( ListPosition*& pos )
{
    GrFmtReader* reader = 0;
    GrFmtReader** temp = (GrFmtReader**)pos;

    assert( temp == 0 || (m_readers <= temp && temp < m_readers + m_curReaders));
    if( temp )
    {
        reader = *temp++;
        pos = (ListPosition*)(temp < m_readers + m_curReaders ? temp : 0);
    }
    return reader;
}


GrFmtReader* GrFmtReadersList::
    FindReader( const char* filename )
{
    int    i;
    FILE*  f = fopen( filename, "rb" );
    char   signature[4096];
    int    sign_len = 0;
    GrFmtReader* reader = 0;

    if( f )
    {
        for( i = 0; i < m_curReaders; i++ )
        {
            int temp = m_readers[i]->GetSignatureLength();
            if( temp > sign_len ) sign_len = temp;
        }

        assert( sign_len <= sizeof(signature) );

        sign_len = fread( signature, 1, sign_len, f );
        fclose(f);

        for( i = 0; i < m_curReaders; i++ )
        {
            int temp = m_readers[i]->GetSignatureLength();
            if( temp <= sign_len && m_readers[i]->CheckFormat(signature))
            {
                reader = m_readers[i];
                break;
            }
        }
    }

    return reader;
}

int  GrFmtReadersList::GetFiltersString( char* buffer, int maxlen )
{
    buffer, maxlen;
    return 0;
}



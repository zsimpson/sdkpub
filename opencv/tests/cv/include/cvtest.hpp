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

#ifndef _CVTEST_HPP_
#define _CVTEST_HPP_

#include "cv.hpp"
#include "ats.h"

#pragma warning( disable : 4786 )
#pragma warning( disable: 4100 )


#include <map>
#include <vector>

typedef struct 
{
    const char* file;
    int   line;
} atsCallRecord;
    
using namespace std;

class AtsCallStack
{
protected:
    vector< CvStackRecord > m_stack;
public:
    void Push( const char* file, int line );
    void Push( CvStackRecord record );

    void Pop( const char* file = 0, int line = 0 );

    void Print();
};

class AtsMemAllocRecord:public atsCallRecord
{     
public:
    
    AtsCallStack call_stack;
    char* m_context; //stores stack text

public:

    AtsMemAllocRecord();
    AtsMemAllocRecord(const char* file, int line, CvStackRecord* current_stack, int stack_size);
    
};

//extern AtsCallStack gAtsCallStack;

class AtsMemoryManager 
{  
    typedef map<int, AtsMemAllocRecord> MemMap;
    typedef MemMap::iterator iterator;



protected:
    //members
    MemMap m_blockList; 
    

public:
    //functions
    int AddBlock( const char* file, int line, void* address );
    int DeleteBlock( void* address );
    int CheckMemoryLeaks();      
};

extern AtsMemoryManager gAtsMemoryManager;


//below two functions serve to start and finish memory management
void StartMemoryManagement();
void ReportMemoryManagement();

void StartProfiler();

#endif /* _CVTEST_HPP_ */

/* End of file. */

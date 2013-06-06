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

#include "ats.h"

/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:      atsTimerStart
//    Purpose:   Setting privileges level for task highest
//    Context:   
//    Parameters:
//    Returns:   
//    Notes:     
//F*/
void atsTimerStart( int param )
{
    trsTimerStart( param );
    return;
}


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:      atsTimerStop
//    Purpose:   Setting privileges level for task highest
//    Context:   
//    Parameters:
//    Returns:   
//    Notes:     
//F*/
void atsTimerStop( int param )
{
    trsTimerStop(param);
    return;
}


/* static void vf();

double atsGetTime(int (*func_ptr)())
{
	int i,j;
	double time_min=0,delay=0;
    __asm   int 0f0h
    __asm   cli
	for(j=0;j<100;j++){
		start_count(&time);
		for(i=0;i<10;i++) vf();
		stop_count(&time);
		if(!delay) delay=time.value;
		else if(time.value<delay) delay=time.value;
	}
	for(j=0;j<100;j++){
		start_count(&time);
		for(i=0;i<10;i++) (*func_ptr)();
		stop_count(&time);
		if(!time_min) time_min=time.value;
		else if(time.value<time_min) time_min=time.value;
	}
    __asm   sti
	time_min-=delay;
	time_min/=10;
	return time_min;
}

static void vf()
{
	__asm	nop
	return;
} */


/* End of file. */

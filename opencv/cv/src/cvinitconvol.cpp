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

#include "_cv.h"

#define BUFFER_OFFSET 592
/* This function calculates the convolution with (1, 1) kernels */
void
icvCalcKer( char *Kernel, int order, int Size, int depth,int origin )
{
    int i,j;
    int oldsafe, newsafe;
    float oldval, newval;
    float* KerF = (float*)Kernel;
    

    if(depth!=cv32f)
    {
        int* KerI = (int*)Kernel;
        KerI[0] = 1;
        for(i = 1; i <= Size; i++)KerI[i] = 0;

        for(i = 0; i < Size-order-1; i++)
        {
            oldsafe = KerI[0];
            for(j = 1; j <= Size; j++)
            {
                newsafe = KerI[j]+KerI[j-1];
                KerI[j-1] = oldsafe;
                oldsafe = newsafe;
            }
        }
        for(i = 0; i < order; i++)
        {
            oldsafe = -KerI[0];
            for(j = 1; j <= Size; j++)
            {
                newsafe = KerI[j-1]-KerI[j];
                KerI[j-1] = oldsafe;
                oldsafe = newsafe;
            }
        }
        if(Size==CV_SCHARR)
        {
            if(order==1)
            {
                KerI[0]=-1;
                KerI[1]=0;
                KerI[2]=1;
            }
            else if(order==0)
            {
                KerI[0]=KerI[2]=3;
                KerI[1]=10;
            }

        }
        if((order&1)&&(origin==CV_ORIGIN_BL))
        {
            for(j = 0; j < Size; j++)
            {
                KerI[j] *= -1;
            }
        }
    }
    else
    {
        KerF[0] = 1;
        for(i = 1; i <= Size; i++)KerF[i] = 0;

        for(i = 0; i < Size-order-1; i++)
        {
            oldval = KerF[0];
            for(j = 1; j <= Size; j++)
            {
                newval = KerF[j]+KerF[j-1];
                KerF[j-1] = oldval;
                oldval = newval;
            }
        }
        for(i = 0; i < order; i++)
        {
            oldval = -KerF[0];
            for(j = 1; j <= Size; j++)
            {
                newval = KerF[j-1]-KerF[j];
                KerF[j-1] = oldval;
                oldval = newval;
            }
        }
        if(Size==CV_SCHARR)
        {
            if(order==1)
            {
                KerF[0]=-1;
                KerF[1]=0;
                KerF[2]=1;
            }
            else if(order==0)
            {
                KerF[0]=KerF[2]=3;
                KerF[1]=10;
            }

        }
        if((order&1)&&(origin==CV_ORIGIN_BL))
        {
            for(j = 0; j < Size; j++)
            {
                KerF[j] *= -1;
            }
        }

    }
    return;
}


/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    icvCalcConvBufSize
//    Purpose:
//      Calculate size of cyclic buffer needed for convolution
//
//    Context:
//    Parameters:
//      datatype    - image data type (cv8u, cv8s,CVL_16S,cv32f)
//      width       - width of source image in pixels
//      height      - number of rows in the buffer
//    Returns:
//      size of buffer in bytes (aligned to 32)
//    Notes:
//F*/
int
icvCalcConvBufSize( int datatype, int width, int height )
{
    if( datatype == cv32f )
    {
        return height * icvAlign( width * 4, 32 );
    }
    else if( datatype == cv16s )
    {
        return height * icvAlign( width * 2, 16 );
    }
    else
    {
        return height * icvAlign( width * 4, 32 );
    }
}

IPCVAPI_IMPL( CvStatus, icvScharrInitAlloc, (int roiwidth,
                                             int depth,
                                             int origin,
                                             int dx, int dy, _CvConvState ** state) )
{
    int i;
    _CvConvState* st;
    int BufStep;
    BufStep=icvCalcConvBufSize(depth,roiwidth,1);
    st =(_CvConvState*)icvAlloc(icvCalcConvBufSize(depth,
                                                   roiwidth,
                                                   3) + BUFFER_OFFSET );
    st->kerType = (origin<<1)+dx;
    st->initialized = 3;
    
        st->buffer = (char*)st + BUFFER_OFFSET;
        for(i = 0; i < 3 ; i++)
        {            
            st->lines[i]=st->buffer+BufStep * i;
        }
    icvCalcKer(st->KerX,dx,CV_SCHARR,depth,CV_ORIGIN_TL);
    icvCalcKer(st->KerY,dy,CV_SCHARR,depth,origin);
    (*state)=st;
    return CV_NO_ERR;
}

IPCVAPI_IMPL( CvStatus, icvSobelInitAlloc, (int roiwidth,
                                            int depth,
                                            int Size,
                                            int origin,
                                            int dx, int dy, _CvConvState ** state) )
{
    int i;
    _CvConvState* st;
    int BufStep;
        
    BufStep=icvCalcConvBufSize(depth,roiwidth,1);
    st =(_CvConvState*)icvAlloc(icvCalcConvBufSize(depth,
                                                        roiwidth,
                                                        Size) + BUFFER_OFFSET );
    st->kerType = (Size<<3)+(origin<<2)+((dy%2)<<1)+(dx%2);
    st->initialized = Size;
    
        st->buffer = (char*)st + BUFFER_OFFSET;
        for(i = 0; i < Size ; i++)
        {            
            st->lines[i]=st->buffer+BufStep * i;
        }

        icvCalcKer(st->KerX,dx,Size,depth,CV_ORIGIN_TL);
        icvCalcKer(st->KerY,dy,Size,depth,origin);
        
   
    (*state)=st;
    return CV_NO_ERR;
}

IPCVAPI_IMPL( CvStatus, icvBlurInitAlloc, (int roiwidth,
                                           int depth, int kerSize, _CvConvState ** state) )
{
    int i;
    _CvConvState* st;
    int BufStep; 
    BufStep=icvCalcConvBufSize(depth,roiwidth,1);
    st =(_CvConvState*)icvAlloc(icvCalcConvBufSize(depth,
                                                        roiwidth,
                                                        kerSize+1) + BUFFER_OFFSET);
    st->buffer = (char*)st + BUFFER_OFFSET;
    st->kerType = kerSize<<3;
    st->initialized = kerSize;
    
        for(i = 0; i <= kerSize ; i++)
        {            
            st->lines[i]=st->buffer+BufStep * i;
        }

    (*state)=st; 
    
    return CV_NO_ERR;
}


IPCVAPI_IMPL( CvStatus, icvLaplaceInitAlloc, (int roiwidth,
                                              int depth, int kerSize, _CvConvState ** state) )
{
    int i;
    _CvConvState* st;
    int BufStep; 
    BufStep=icvCalcConvBufSize(depth,roiwidth,1);
    st =(_CvConvState*)icvAlloc(2*icvCalcConvBufSize(depth,
                                                        roiwidth,
                                                        kerSize) + BUFFER_OFFSET );
    st->buffer = (char*)st + BUFFER_OFFSET;
    st->kerType = kerSize<<3;
    st->initialized = kerSize;
    for(i = 0; i < 2 * kerSize; i++)
    {            
        st->lines[i]=st->buffer+BufStep * i;
    }

    icvCalcKer(st->KerX,2,kerSize,depth,CV_ORIGIN_TL);
    icvCalcKer(st->KerY,0,kerSize,depth,CV_ORIGIN_TL);
    (*state)=st;
    return CV_NO_ERR;
}

IPCVAPI_IMPL( CvStatus, icvConvolFree, (_CvConvState ** state) )
{
    icvFree(state);
    return CV_NO_ERR;
}

IPCVAPI_IMPL( CvStatus, icvScharrFree, (_CvConvState ** state) )
{
    icvFree(state);
    return CV_NO_ERR;
}

/* End of file. */


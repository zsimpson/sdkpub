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
#include "_cvwrap.h"

IPCVAPI(CvStatus, icvSegmentMotion_32f_C1R, (float *mhiIm,
                                             int mhiStep,
                                             CvSize size,
                                             float timestamp,
                                             float SegThresh,
                                             float *SegMask,
                                             int SMStep,
                                             CvMemStorage * storage,
                                             CvSeq ** components ))

/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:    icvSegmentMotion_32f_C1R
//    Purpose: The function updates motion history image.
//    Context:
//    Parameters:
//        mhiIm         - motion history image
//        mhiStep       - its step
//        size          - size of both images (in pixels)
//        SegMask       - Segmentation Mask Image
//        SMStep        - its step
//        SegThresh     - Segmentation Threshold
//    Returns:
//        CV_OK or error code:
//           CV_NULLPTR_ERR - silIm or mhiIm pointer are null
//           CV_BADSIZE_ERR   - width or height is negative or steps less than width
//           CV_BADFACTOR_ERR - SegThresh is non positive
//    Notes:
//F*/
IPCVAPI_IMPL( CvStatus, icvSegmentMotion_32f_C1R, (float *mhiIm,
                                                   int mhiStep,
                                                   CvSize size,
                                                   float timestamp,
                                                   float SegThresh,
                                                   float *SegMask,
                                                   int SMStep,
                                                   CvMemStorage * storage,
                                                   CvSeq ** components) )
{
    CvPoint InitPoint;
    CvConnectedComp ConComp;
    CvSeqWriter writer;
    int ownstep = mhiStep / 4;
    int ownstepm = SMStep / 4;
    float CurRegNum = 1;
    int BufSize;
    void *Buffer;
    float *Temp;
    int i, j;
	
    if( !mhiIm )
        return CV_NULLPTR_ERR;
    if( size.height <= 0 || size.width <= 0 || mhiStep < size.width * 4 ||
        SMStep < size.width * 4 )
        return CV_BADSIZE_ERR;
    if( SegThresh <= 0 )
        return CV_BADFACTOR_ERR;

    cvStartWriteSeq( 0, sizeof( CvSeq ), sizeof( CvConnectedComp ), storage, &writer );
    icvFloodFillGetSize_Grad( size, &BufSize );
    Buffer = icvAlloc( BufSize );
    for( i = 0; i < size.height; i++ )
    {
        for( j = 0; j < size.width; j++ )
        {
            SegMask[i * ownstepm + j] = mhiIm[i * ownstep + j];
        }
    }
    for( i = 1; i < size.height-1; i++ )
    {
        for( j = 1; j < size.width-1; j++ )
        {
            if( SegMask[i * ownstepm + j] == timestamp )
            {
                float ffillVal = timestamp + CurRegNum;
                float ffillLoDelta = 2*SegThresh;
                float ffillUpDelta = 0;

                /*up */
                if( (SegMask[(i - 1) * ownstepm + j] < timestamp) &&
                    ((timestamp - SegMask[(i - 1) * ownstepm + j]) <= SegThresh) )
                {
                    InitPoint.x = j;
                    InitPoint.y = i - 1;
                    icvFloodFill_Grad4Con_32f_C1IR( SegMask,
                                                     mhiStep,
                                                     size,
                                                     InitPoint,
                                                     &ffillVal,
                                                     &ffillLoDelta, &ffillUpDelta,
                                                     &ConComp, Buffer );
                    ConComp.value = CurRegNum;
                    CV_WRITE_SEQ_ELEM( ConComp, writer );
                    CurRegNum += 1;
                }
                /* left */
                if( (SegMask[i * ownstepm + j - 1] < timestamp) &&
                    ((timestamp - SegMask[i * ownstepm + j - 1]) <= SegThresh) )
                {
                    InitPoint.x = j - 1;
                    InitPoint.y = i;
                    icvFloodFill_Grad4Con_32f_C1IR( SegMask,
                                                     mhiStep,
                                                     size,
                                                     InitPoint,
                                                     &ffillVal,
                                                     &ffillLoDelta, &ffillUpDelta,
                                                     &ConComp, Buffer );
                    ConComp.value = CurRegNum;
                    CV_WRITE_SEQ_ELEM( ConComp, writer );
                    CurRegNum += 1;
                }
                /* right */
                if( (SegMask[i * ownstepm + j + 1] < timestamp) &&
                    ((timestamp - SegMask[i * ownstepm + j + 1]) <= SegThresh) )
                {
                    InitPoint.x = j + 1;
                    InitPoint.y = i;
                    icvFloodFill_Grad4Con_32f_C1IR( SegMask,
                                                     mhiStep,
                                                     size,
                                                     InitPoint,
                                                     &ffillVal,
                                                     &ffillLoDelta, &ffillUpDelta,
                                                     &ConComp, Buffer );
                    ConComp.value = CurRegNum;
                    CV_WRITE_SEQ_ELEM( ConComp, writer );
                    CurRegNum += 1;
                }
                /* low */
                if( (SegMask[(i + 1) * ownstepm + j] < timestamp) &&
                    ((timestamp - SegMask[(i + 1) * ownstepm + j]) <= SegThresh) )
                {
                    InitPoint.x = j;
                    InitPoint.y = i + 1;
                    icvFloodFill_Grad4Con_32f_C1IR( SegMask,
                                                     mhiStep,
                                                     size,
                                                     InitPoint,
                                                     &ffillVal,
                                                     &ffillLoDelta, &ffillUpDelta,
                                                     &ConComp, Buffer );
                    ConComp.value = CurRegNum;
                    CV_WRITE_SEQ_ELEM( ConComp, writer );
                    CurRegNum += 1;
                }
            }
        }
    }
    *components = cvEndWriteSeq( &writer );
    for( i = 0; i < size.height; i++ )
    {
        Temp = SegMask + i * ownstepm;
        for( j = 0; j < size.width; j++ )
        {
            Temp[j] = MAX( Temp[j] - timestamp, 0 );
        }
    }
    icvFree( &Buffer );
    return CV_NO_ERR;
}


CV_IMPL CvSeq* cvSegmentMotion( void* mhiimg, void* seg_mask,
                                CvMemStorage* storage,
                                double timestamp, double seg_thresh )
{
    CvSize size;
    CvMat  mhistub, *mhi = (CvMat*)mhiimg;
    CvMat  maskstub, *mask = (CvMat*)seg_mask;
    CvSeq* components = 0;

    CV_FUNCNAME( "cvMotionSegmentation" );

    __BEGIN__;

    if( !storage )
        CV_ERROR( CV_StsNullPtr, "" );

    CV_CALL( mhi = cvGetMat( mhi, &mhistub ));
    CV_CALL( mask = cvGetMat( mask, &maskstub ));

    if( CV_ARR_CN( mhi->type ) != 1 || CV_ARR_CN( mask->type ) != 1 )
        CV_ERROR( CV_BadNumChannels, "" );

    if( CV_ARR_DEPTH( mhi->type ) != CV_32F ||
        CV_ARR_DEPTH( mask->type ) != CV_32F )
        CV_ERROR( CV_BadDepth, "" );

    if( !CV_ARE_SIZES_EQ( mhi, mask ))
        CV_ERROR( CV_StsUnmatchedSizes, "" );

    size = icvGetMatSize( mhi );

    IPPI_CALL( icvSegmentMotion_32f_C1R( mhi->data.fl, mhi->step, size,
                                         (float) timestamp, (float) seg_thresh,
                                         mask->data.fl, mask->step,
                                         storage, &components ));
    __END__;

    return components;
}

/* End of file. */

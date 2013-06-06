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

/* ////////////////////////////////////////////////////////////////////
//
//  CvMat implementation file: utilities
//
// */

#include "_cv.h"

static struct
{
    Cv_iplCreateImageHeader  createHeader;
    Cv_iplAllocateImageData  allocateData;
    Cv_iplDeallocate  deallocate;
    Cv_iplCreateROI  createROI;
    Cv_iplCloneImage  cloneImage;
}
CvIPL;


CV_IMPL void
cvSetIPLAllocators( Cv_iplCreateImageHeader createHeader,
                    Cv_iplAllocateImageData allocateData,
                    Cv_iplDeallocate deallocate,
                    Cv_iplCreateROI createROI,
                    Cv_iplCloneImage cloneImage )
{
    CV_FUNCNAME( "cvSetIPLAllocators" );

    __BEGIN__;

    if( !createHeader || !allocateData || !deallocate || !createROI || !cloneImage )
    {
        if( createHeader || allocateData || deallocate || createROI || cloneImage )
            CV_ERROR( CV_StsBadArg, "Either all the pointers should be null or "
                                    "they all should be non-null" );
    }

    CvIPL.createHeader = createHeader;
    CvIPL.allocateData = allocateData;
    CvIPL.deallocate = deallocate;
    CvIPL.createROI = createROI;
    CvIPL.cloneImage = cloneImage;

    __END__;
}


/****************************************************************************************\
*                               CvMat creation and basic operations                      *
\****************************************************************************************/

// create CvMat and underlying date
CV_IMPL CvMat*
cvCreateMat( int height, int width, int type )
{
    CvMat* arr = 0;

    CV_FUNCNAME( "cvCreateMat" );
    
    __BEGIN__;

    CV_CALL( arr = cvCreateMatHeader( height, width, type ));
    CV_CALL( cvCreateData( arr ));

    __END__;

    if( cvGetErrStatus() < 0 )
        cvReleaseMat( &arr );

    return arr;
}


// Create CvMat header only
CV_IMPL CvMat*
cvCreateMatHeader( int height, int width, int type )
{
    CvMat* arr = 0;
    
    CV_FUNCNAME( "cvCreateMatHeader" );

    __BEGIN__;

    CV_CALL( arr = (CvMat*)cvAlloc( sizeof(*arr)));
    CV_CALL( cvInitMatHeader( arr, height, width, type, 0,
                              icvAlign(width*cvPixSize(type),4) ));

    __END__;

    if( cvGetErrStatus() < 0 )
        cvReleaseMatHeader( &arr );

    return arr;
}


// initialize CvMat header, allocated by the user
CV_IMPL CvMat*
cvInitMatHeader( CvMat* arr, int height, int width,
                 int type, void* data, int step )
{
    CV_FUNCNAME( "cvInitMatHeader" );
    
    __BEGIN__;

    if( !arr )
        CV_ERROR_FROM_CODE( CV_StsNullPtr );

    if( (unsigned)(CV_ARR_CN(type) - 1) >= CV_CN_MAX )
        CV_ERROR_FROM_CODE( CV_BadDepth );

    if( (unsigned)CV_ARR_DEPTH(type) > CV_DEPTH_MAX )
        CV_ERROR_FROM_CODE( CV_BadNumChannels );

    if( height <= 0 || width <= 0 )
        CV_ERROR_FROM_CODE( CV_StsBadSize );
 
    arr->type = (type & CV_ARR_TYPE_MASK) | CV_ARR_MAGIC_VAL;
    arr->height = height;
    arr->width = width;

    CV_CALL( cvSetData( arr, data, step ));

    __END__;

    return arr;
}

// deallocate the CvMat structure and underlying date
CV_IMPL void
cvReleaseMat( CvMat** array )
{
    CV_FUNCNAME( "cvReleaseMat" );
    
    __BEGIN__;

    if( !array )
        CV_ERROR_FROM_CODE( CV_HeaderIsNull );

    if( *array )
    {
        CvMat* arr = *array;
        
        if( !_CV_IS_ARR( arr ))
            CV_ERROR_FROM_CODE( !arr ? CV_StsNullPtr : CV_StsBadFlag );

        *array = 0;
        CV_CALL( cvReleaseData( arr ));
        CV_CALL( cvReleaseMatHeader( &arr ));
    }

    __END__;
}


// set CvMat flags
void
cvSetMatShapeFlags( CvMat* arr )
{
    CV_FUNCNAME( "cvSetMatShapeFlags" );
    
    __BEGIN__;

    int type, cont_flag;

    if( !_CV_IS_ARR( arr ))
        CV_ERROR_FROM_CODE( !arr ? CV_StsNullPtr : CV_StsBadFlag );

    type = CV_ARR_TYPE( arr->type );
    cont_flag = arr->step == 0 || arr->step == arr->width*icvPixSize[type];

    arr->type = type | (cont_flag << CV_ARR_CONT_FLAG_SHIFT) | CV_ARR_MAGIC_VAL;

    __END__;
}


// deallocate CvMat header
CV_IMPL void
cvReleaseMatHeader( CvMat** array )
{
    CV_FUNCNAME( "cvReleaseMatHeader" );
    
    __BEGIN__;

    if( !array )
        CV_ERROR_FROM_CODE( CV_HeaderIsNull );

    if( *array )
    {
        CvMat* arr = *array;
        if( !_CV_IS_ARR( arr ))
            CV_ERROR_FROM_CODE( !arr ? CV_StsNullPtr : CV_StsBadFlag );

        *array = 0;
        cvFree( (void**)&arr );
    }

    __END__;
}


CV_IMPL CvMat*
cvCloneMat( const CvMat* src )
{
    CvMat* dst = 0;
    CV_FUNCNAME( "cvCloneMat" );

    __BEGIN__;

    if( !_CV_IS_ARR( src ))
        CV_ERROR( CV_StsBadArg, "Bad CvMat header" );

    CV_CALL( dst = cvCreateMatHeader( src->height, src->width, src->type ));

    if( src->data.ptr )
    {
        CV_CALL( cvCreateData( dst ));
        CV_CALL( cvCopy( src, dst ));
    }

    __END__;

    return dst;
}


/****************************************************************************************\
*                           Common for CvMat and IplImage operations                     *
\****************************************************************************************/

// allocate underlying CvMat or IplImage data
CV_IMPL void
cvCreateData( CvArr* arr )
{
    CV_FUNCNAME( "cvCreateData" );
    
    __BEGIN__;

    if( _CV_IS_ARR( arr ))
    {
        int step, total_size;
        CvMat* mat = (CvMat*)arr;
        step = mat->step;

        if( step == 0 )
            step = icvPixSize[CV_ARR_TYPE(mat->type)]*mat->width;

        total_size = step*mat->height;

        assert( total_size >= 0 );
        CV_CALL( mat->data.ptr = (uchar*)cvAlloc( total_size ));
    }
    else if( _CV_IS_IMAGE(arr))
    {
        IplImage* img = (IplImage*)arr;

        if( !CvIPL.allocateData )
        {
            CV_CALL( img->imageData = img->imageDataOrigin = 
                        (char*)cvAlloc( img->imageSize ));
        }
        else
        {
            int depth = img->depth;
            int width = img->width;

            if( img->depth == IPL_DEPTH_32F || img->nChannels == 64 )
            {
                img->width *= img->depth == IPL_DEPTH_32F ? sizeof(float) : sizeof(double);
                img->depth = IPL_DEPTH_8U;
            }

            CvIPL.allocateData( img, 0, 0 );

            img->width = width;
            img->depth = depth;
        }
    }
    else
    {
        CV_ERROR( CV_StsBadArg, "" );
    }

    __END__;
}


// set underlying CvMat or IplImage data
CV_IMPL void
cvSetData( CvArr* arr, void* data, int step )
{
    CV_FUNCNAME( "cvSetData" );

    __BEGIN__;

    int pix_size, min_step;

    if( _CV_IS_ARR( arr ))
    {
        CvMat* mat = (CvMat*)arr;

        pix_size = icvPixSize[CV_ARR_TYPE(mat->type)];
        min_step = mat->width*pix_size & ((mat->height <= 1) - 1);

        if( step != CV_AUTOSTEP )
        {
            if( step < min_step && data != 0 )
                CV_ERROR_FROM_CODE( CV_BadStep );
            mat->step = step & ((mat->height <= 1) - 1);
        }
        else
        {
            mat->step = min_step;
        }

        mat->data.ptr = (uchar*)data;

        CV_CALL( cvSetMatShapeFlags( mat ));
    }
    else if( _CV_IS_IMAGE( arr ))
    {
        IplImage* img = (IplImage*)arr;
        
        pix_size = icvGetBtPix( img );
        min_step = img->width*pix_size;

        if( step != CV_AUTOSTEP && img->height > 1 )
        {
            if( step < min_step && data != 0 )
                CV_ERROR_FROM_CODE( CV_BadStep );
            img->widthStep = step;
        }
        else
        {
            img->widthStep = min_step;
        }

        img->imageSize = img->widthStep * img->height;
        img->imageData = img->imageDataOrigin = (char*)data;

        if( (((int)(long)data | step) & 7) == 0 &&
            icvAlign(img->width * pix_size, 7) == step )
        {
            img->align = 8;
        }
        else
        {
            img->align = 4;
        }
    }
    else
    {
        CV_ERROR( CV_StsBadArg, "" );
    }

    __END__;
}


// deallocate underlying CvMat or IplImage data
CV_IMPL void
cvReleaseData( CvArr* arr )
{
    CV_FUNCNAME( "cvReleaseData" );
    
    __BEGIN__;

    if( _CV_IS_ARR( arr ))
    {
        CvMat* mat = (CvMat*)arr;
        uchar* data = mat->data.ptr;
        mat->data.ptr = 0;
        cvFree( (void**)&data );
    }
    else if( _CV_IS_IMAGE( arr ))
    {
        IplImage* img = (IplImage*)arr;

        if( !CvIPL.deallocate )
        {
            char* ptr = img->imageData;
            img->imageData = img->imageDataOrigin = 0;
            cvFree( (void**)&ptr );
        }
        else
        {
            CvIPL.deallocate( img, IPL_IMAGE_DATA );
        }
    }
    else
    {
        CV_ERROR( CV_StsBadArg, "" );
    }

    __END__;
}


// get essential information about image ROI or CvMat data
CV_IMPL void
cvGetRawData( const CvArr* arr, uchar** data, int* step, CvSize* roi_size )
{
    CV_FUNCNAME( "cvGetRawData" );

    __BEGIN__;

    if( CV_IS_ARR( arr ))
    {
        CvMat *mat = (CvMat*)arr;

        if( step )
            *step = mat->step;

        if( data )
            *data = mat->data.ptr;

        if( roi_size )
            *roi_size = icvGetMatSize( mat );
    }
    else if( CV_IS_IMAGE( arr ))
    {
        IplImage* img = (IplImage*)arr;

        if( step )
            *step = img->widthStep;

        if( data )
            CV_CALL( *data = cvGetPtrAt( img, 0, 0 ));

        if( roi_size )
        {
            if( img->roi )
            {
                *roi_size = cvSize( img->roi->width, img->roi->height );
            }
            else
            {
                *roi_size = cvSize( img->width, img->height );
            }
        }
    }
    else
    {
        CV_ERROR( CV_StsBadArg, "" );
    }

    __END__;
}


OPENCVAPI CvSize
cvGetSize( const CvArr* arr )
{
    CvSize size = { 0, 0 };

    CV_FUNCNAME( "cvGetSize" );

    __BEGIN__;

    if( _CV_IS_ARR( arr ))
    {
        CvMat *mat = (CvMat*)arr;

        size.width = mat->width;
        size.height = mat->height;
    }
    else if( _CV_IS_IMAGE( arr ))
    {
        IplImage* img = (IplImage*)arr;

        if( img->roi )
        {
            size.width = img->roi->width;
            size.height = img->roi->height;
        }
        else
        {
            size.width = img->width;
            size.height = img->height;
        }
    }
    else
    {
        CV_ERROR( CV_StsBadArg, "Parameter of cvGetSize is neither CvMat nor IplImage" );
    }

    __END__;

    return size;
}



// get ROI (or minor) of input array
CV_IMPL  CvMat*
cvGetSubArr( const CvArr* arr, CvMat* submat, CvRect rect )
{
    CvMat* res = 0;
    
    CV_FUNCNAME( "cvGetSubArr" );

    __BEGIN__;

    CvMat stub, *mat = (CvMat*)arr;

    if( !CV_IS_ARR( mat ))
        CV_CALL( mat = cvGetMat( mat, &stub ));

    if( !submat )
        CV_ERROR( CV_StsNullPtr, "" );

    if( (rect.x|rect.y|rect.width|rect.height) < 0 )
        CV_ERROR( CV_StsBadSize, "" );

    if( rect.x + rect.width > mat->width ||
        rect.y + rect.height > mat->height )
        CV_ERROR( CV_StsBadSize, "" );

    CV_CALL( cvInitMatHeader( submat, rect.height, rect.width, mat->type,
                             mat->data.ptr + rect.y*mat->step +
                             rect.x*icvPixSize[CV_ARR_TYPE(mat->type)],
                             mat->step ));
    res = submat;
    
    __END__;

    return res;
}


// get row of input array
CV_IMPL  CvMat*
cvGetRow( const CvArr* arr, CvMat* submat, int row )
{
    CvMat* res = 0;
    
    CV_FUNCNAME( "cvGetRow" );

    __BEGIN__;

    CvMat stub, *mat = (CvMat*)arr;

    if( !CV_IS_ARR( mat ))
        CV_CALL( mat = cvGetMat( mat, &stub ));

    if( !submat )
        CV_ERROR( CV_StsNullPtr, "" );

    if( (unsigned)row >= (unsigned)mat->height )
        CV_ERROR( CV_StsOutOfRange, "" );

    CV_CALL( cvInitMatHeader( submat, 1, mat->width, mat->type,
                             mat->data.ptr + row*mat->step,
                             CV_AUTOSTEP ));
    res = submat;
    
    __END__;

    return res;
}


// get column of input array
CV_IMPL  CvMat*
cvGetCol( const CvArr* arr, CvMat* submat, int col )
{
    CvMat* res = 0;
    
    CV_FUNCNAME( "cvGetCol" );

    __BEGIN__;

    CvMat stub, *mat = (CvMat*)arr;

    if( !CV_IS_ARR( mat ))
        CV_CALL( mat = cvGetMat( mat, &stub ));

    if( !submat )
        CV_ERROR( CV_StsNullPtr, "" );

    if( (unsigned)col >= (unsigned)mat->width )
        CV_ERROR( CV_StsOutOfRange, "" );

    CV_CALL( cvInitMatHeader( submat, mat->height, 1, mat->type,
                              mat->data.ptr + col*icvPixSize[CV_ARR_TYPE(mat->type)],
                              mat->step ));
    res = submat;
    
    __END__;

    return res;
}


// get column of input array
CV_IMPL  CvMat*
cvGetDiag( const CvArr* arr, CvMat* submat, int diag )
{
    CvMat* res = 0;
    
    CV_FUNCNAME( "cvGetDiag" );

    __BEGIN__;

    CvMat stub, *mat = (CvMat*)arr;
    int pix_size; 

    if( !CV_IS_ARR( mat ))
        CV_CALL( mat = cvGetMat( mat, &stub ));

    if( !submat )
        CV_ERROR( CV_StsNullPtr, "" );

    pix_size = icvPixSize[CV_ARR_TYPE(mat->type)];

    if( diag >= 0 )
    {
        int len = mat->width - diag;
        
        if( len <= 0 )
            CV_ERROR( CV_StsOutOfRange, "" );

        len = CV_IMIN( len, mat->height );

        CV_CALL( cvInitMatHeader( submat, len, 1, mat->type,
                                  mat->data.ptr + diag*pix_size,
                                  mat->step + pix_size ));
    }
    else
    {
        int len = mat->height + diag;
        diag = -diag;
        
        if( len <= 0 )
            CV_ERROR( CV_StsOutOfRange, "" );

        len = CV_IMIN( len, mat->width );

        CV_CALL( cvInitMatHeader( submat, len, 1, mat->type,
                                  mat->data.ptr + diag*mat->step,
                                  mat->step + pix_size ));
    }

    res = submat;
    
    __END__;

    return res;
}


/****************************************************************************************\
*                      Operations on CvScalar and accessing array elements               *
\****************************************************************************************/

// convert CvScalar to specified type
void
cvScalarToRawData( CvScalar* scalar, int flags, void* data, int extend_to_12 )
{
    CV_FUNCNAME( "cvScalarToRawData" );
    
    __BEGIN__;

    int type = CV_ARR_TYPE( flags );
    int cn = CV_ARR_CN( type );
    int depth = type & CV_ARR_DEPTH_MASK;

    assert( scalar && data );
    assert( (unsigned)(cn - 1) < 4 );

    switch( depth )
    {
    case CV_8UC1:
        while( cn-- )
        {
            int t = cvRound( scalar->val[cn] );
            ((uchar*)data)[cn] = CV_CAST_8U(t);
        }
        break;
    case CV_8SC1:
        while( cn-- )
        {
            int t = cvRound( scalar->val[cn] );
            ((char*)data)[cn] = CV_CAST_8S(t);
        }
        break;
    case CV_16SC1:
        while( cn-- )
        {
            int t = cvRound( scalar->val[cn] );
            ((short*)data)[cn] = CV_CAST_16S(t);
        }
        break;
    case CV_32SC1:
        while( cn-- )
            ((int*)data)[cn] = cvRound( scalar->val[cn] );
        break;
    case CV_32FC1:
        while( cn-- )
            ((float*)data)[cn] = (float)(scalar->val[cn]);
        break;
    case CV_64FC1:
        while( cn-- )
            ((double*)data)[cn] = (double)(scalar->val[cn]);
        break;
    default:
        assert(0);
        CV_ERROR_FROM_CODE( CV_BadDepth );
    }

    if( extend_to_12 )
    {
        int pix_size = icvPixSize[type];
        int offset = icvPixSize[depth]*12;

        do
        {
            offset -= pix_size;
            memcpy( (char*)data + offset, data, pix_size );
        }
        while( offset > pix_size );
    }

    __END__;
}


// convert data of specified type to CvScalar
void
cvRawDataToScalar( void* data, int flags, CvScalar* scalar )
{
    CV_FUNCNAME( "cvRawDataToScalar" );
    
    __BEGIN__;

    int cn = CV_ARR_CN( flags );

    assert( scalar && data );
    assert( (unsigned)(cn - 1) < 4 );

    memset( scalar->val, 0, sizeof(scalar->val));

    switch( CV_ARR_DEPTH( flags ))
    {
    case CV_8U:
        while( cn-- )
            scalar->val[cn] = CV_8TO32F(((uchar*)data)[cn]);
        break;
    case CV_8S:
        while( cn-- )
            scalar->val[cn] = CV_8TO32F(((char*)data)[cn]);
        break;
    case CV_16S:
        while( cn-- )
            scalar->val[cn] = ((short*)data)[cn];
        break;
    case CV_32S:
        while( cn-- )
            scalar->val[cn] = ((int*)data)[cn];
        break;
    case CV_32F:
        while( cn-- )
            scalar->val[cn] = ((float*)data)[cn];
        break;
    case CV_64F:
        while( cn-- )
            scalar->val[cn] = ((double*)data)[cn];
        break;
    default:
        assert(0);
        CV_ERROR_FROM_CODE( CV_BadDepth );
    }

    __END__;
}


// get pointer to specified array element
CV_IMPL  uchar*
cvGetPtrAt( const CvArr* arr, int y, int x )
{
    uchar* ptr = 0;
    
    CV_FUNCNAME( "cvGetPtrAt" );

    __BEGIN__;

    if( CV_IS_ARR( arr ))
    {
        CvMat* mat = (CvMat*)arr;

        if( (unsigned)y >= (unsigned)(mat->height) ||
            (unsigned)x >= (unsigned)(mat->width) )
            CV_ERROR_FROM_CODE( CV_StsBadArg );

        ptr = mat->data.ptr + y*mat->step + x*icvPixSize[CV_ARR_TYPE(mat->type)];
    }
    else if( CV_IS_IMAGE( arr ))
    {
        IplImage* img = (IplImage*)arr;
        int pix_size = (img->depth & 255) >> 3;
        int width, height;
        ptr = (uchar*)img->imageData;

        if( img->dataOrder == 0 )
            pix_size *= img->nChannels;

        if( img->roi )
        {
            width = img->roi->width;
            height = img->roi->height;

            ptr += img->roi->yOffset*img->widthStep +
                   img->roi->xOffset*pix_size;

            if( img->dataOrder && img->roi->coi )
                ptr += (img->roi->coi - 1)*img->imageSize;
        }
        else
        {
            width = img->width;
            height = img->height;
        }

        if( (unsigned)y >= (unsigned)height ||
            (unsigned)x >= (unsigned)width )
            CV_ERROR_FROM_CODE( CV_StsBadArg );

        ptr += y*img->widthStep + x*pix_size;
    }

    __END__;

    return ptr;
}


static int icvIplToCvDepth( int ipl_depth )
{
    int depth;
    
    switch( ipl_depth )
    {
    case IPL_DEPTH_8U:  depth = CV_8U; break;
    case IPL_DEPTH_8S:  depth = CV_8S; break;
    case IPL_DEPTH_16S: depth = CV_16S; break;
    case IPL_DEPTH_32S: depth = CV_32S; break;
    case IPL_DEPTH_32F: depth = CV_32F; break;
    case 64: depth = CV_64F; break;
    default: depth = -1;
    }
    
    return depth;
}


static int icvCvToIplDepth( int ipl_depth )
{
    int depth;
    
    switch( ipl_depth )
    {
    case CV_8U:  depth = IPL_DEPTH_8U; break;
    case CV_8S:  depth = IPL_DEPTH_8S; break;
    case CV_16S: depth = IPL_DEPTH_16S; break;
    case CV_32S: depth = IPL_DEPTH_32S; break;
    case CV_32F: depth = IPL_DEPTH_32F; break;
    case CV_64F: depth = IPL_DEPTH_64F; break;
    default: depth = -1;
    }
    
    return depth;
}


// get specifed element of array
CV_IMPL  CvScalar
cvGetAt( const CvArr* arr, int y, int x )
{
    CvScalar scalar = {{ 0, 0, 0, 0 }};

    CV_FUNCNAME( "cvGetAt" );

    __BEGIN__;

    uchar* ptr;
    int type;

    CV_CALL( ptr = cvGetPtrAt( arr, y, x ));

    if( CV_IS_ARR( arr ))
    {
        type = CV_ARR_TYPE( ((CvMat*)arr)->type );
    }
    else
    {
        IplImage* img = (IplImage*)arr;
        
        type = icvIplToCvDepth( img->depth );
        if( type < 0 || (unsigned)(img->nChannels - 1) > 3 )
            CV_ERROR( CV_StsUnsupportedFormat, "" );

        type = type*4 + img->nChannels - 1;
    }

    CV_CALL( cvRawDataToScalar( ptr, type, &scalar ));

    __END__;

    return scalar;
}


// Set array element to given value
CV_IMPL  void
cvSetAt( CvArr* arr, CvScalar value, int y, int x )
{
    CV_FUNCNAME( "cvSetAt" );
    
    __BEGIN__;

    uchar* ptr;
    int type;

    CV_CALL( ptr = cvGetPtrAt( arr, y, x ));

    if( CV_IS_ARR( arr ))
    {
        type = CV_ARR_TYPE( ((CvMat*)arr)->type );
    }
    else
    {
        IplImage* img = (IplImage*)arr;
        
        type = icvIplToCvDepth( img->depth );
        if( type < 0 || (unsigned)(img->nChannels - 1) > 3 )
            CV_ERROR( CV_StsUnsupportedFormat, "" );

        type = type*4 + img->nChannels - 1;
    }

    CV_CALL( cvScalarToRawData( &value, type, ptr ));

    __END__;
}



/****************************************************************************************\
*                               Conversion  CvMat <-> IplImage                           *
\****************************************************************************************/

// convert array (CvMat or IplImage) to CvMat
CV_IMPL CvMat*
cvGetMat( const CvArr* array, CvMat* mat, int* pCOI )
{
    CvMat* result = 0;
    CvMat* src = (CvMat*)array;
    int coi = 0;
    
    CV_FUNCNAME( "cvGetMat" );

    __BEGIN__;

    if( !mat || !src )
        CV_ERROR_FROM_CODE( CV_StsNullPtr );

    if( !_CV_IS_ARR(src) )
    {
        const IplImage* img = (const IplImage*)src;
        int depth, order;

        if( img->nSize != sizeof(IplImage))
            CV_ERROR_FROM_CODE( CV_StsBadFlag );

        if( img->imageData == 0 )
            CV_ERROR_FROM_CODE( CV_StsNullPtr );

        if( img->nChannels > 4 )
            CV_ERROR_FROM_CODE( CV_BadNumChannels );

        depth = icvIplToCvDepth( img->depth );
        if( depth < 0 )
            CV_ERROR_FROM_CODE( CV_BadDepth );

        order = img->dataOrder & (img->nChannels > 1 ? -1 : 0);

        if( img->roi )
        {
            if( order == IPL_DATA_ORDER_PLANE )
            {
                int type = depth;

                if( img->roi->coi == 0 )
                    CV_ERROR( CV_StsBadFlag, "Planar order should be used with coi != 0" );

                CV_CALL( cvInitMatHeader( mat, img->roi->height,
                                   img->roi->width, type,
                                   img->imageData + (img->roi->coi-1)*img->imageSize +
                                   img->roi->yOffset*img->widthStep +
                                   img->roi->xOffset*icvPixSize[type],
                                   img->widthStep ));
            }
            else /* pixel order */
            {
                int type = depth + (img->nChannels - 1)*8;

                coi = img->roi->coi;

                CV_CALL( cvInitMatHeader( mat, img->roi->height,
                                   img->roi->width, type,
                                   img->imageData +
                                   img->roi->yOffset*img->widthStep +
                                   img->roi->xOffset*icvPixSize[type],
                                   img->widthStep ));
            }
        }
        else
        {
            int type = depth + (img->nChannels - 1)*8;

            if( order != IPL_DATA_ORDER_PIXEL )
                CV_ERROR( CV_StsBadFlag, "Pixel order should be used with coi == 0" );

            CV_CALL( cvInitMatHeader( mat, img->height,
                                      img->width, type,
                                      img->imageData, img->widthStep ));
        }

        result = mat;
    }
    else
    {
        if( !src->data.ptr )
            CV_ERROR_FROM_CODE( CV_StsNullPtr );
        
        result = (CvMat*)src;
    }

    __END__;

    if( pCOI )
        *pCOI = coi;

    return result;
}



CV_IMPL CvMat*
cvReshape( const CvArr* array, CvMat* header,
           int new_cn, int new_rows )
{
    CvMat* result = 0;
    CV_FUNCNAME( "cvReshape" );

    __BEGIN__;

    CvMat *mat = (CvMat*)array;
    int total_width, new_width;

    if( !header )
        CV_ERROR( CV_StsNullPtr, "" );

    if( (unsigned)(new_cn - 1) > 3 )
        CV_ERROR( CV_BadNumChannels, "" );

    if( !CV_IS_ARR( mat ))
        CV_CALL( mat = cvGetMat( mat, header ));

    if( mat != header )
        *header = *mat;

    total_width = mat->width * CV_ARR_CN( mat->type );

    if( new_cn > total_width )
        new_rows = mat->height * total_width / new_cn;

    if( new_rows != 0 )
    {
        int total_size = total_width * mat->height;

        if( !CV_IS_ARR_CONT( mat->type ))
            CV_ERROR( CV_BadStep,
            "The matrix is not continuous, thus its number of rows can not be changed" );

        if( (unsigned)new_rows > (unsigned)total_size )
            CV_ERROR( CV_StsOutOfRange, "Bad new number of rows" );

        total_width = total_size / new_rows;

        if( total_width * new_rows != total_size )
            CV_ERROR( CV_StsBadArg, "The total number of matrix elements "
                                    "is not divisible by the new number of rows" );

        header->height = new_rows;
        header->step = total_width * icvPixSize[mat->type & CV_ARR_DEPTH_MASK];
    }

    new_width = total_width / new_cn;

    if( new_width * new_cn != total_width )
        CV_ERROR( CV_BadNumChannels,
        "The total width is not divisible by the new number of channels" );

    header->width = new_width;
    header->type = (mat->type & ~CV_ARR_CN_MASK) + ((new_cn - 1)*8);

    __END__;

    return  result;
}


// convert array (CvMat or IplImage) to IplImage
CV_IMPL IplImage*
cvGetImage( const CvArr* array, IplImage* img )
{
    IplImage* result = 0;
    const IplImage* src = (const IplImage*)array;
    
    CV_FUNCNAME( "cvGetImage" );

    __BEGIN__;

    if( !img )
        CV_ERROR_FROM_CODE( CV_StsNullPtr );

    if( !_CV_IS_IMAGE(src) )
    {
        const CvMat* mat = (const CvMat*)src;
        
        if( !_CV_IS_ARR(mat))
            CV_ERROR_FROM_CODE( CV_StsBadFlag );

        if( mat->data.ptr == 0 )
            CV_ERROR_FROM_CODE( CV_StsNullPtr );

        cvInitImageHeader( img, cvSize(mat->width, mat->height),
                           icvCvToIplDepth(CV_ARR_DEPTH(mat->type)),
                           CV_ARR_CN(mat->type) );
        cvSetData( img, mat->data.ptr, mat->step );

        result = img;
    }
    else
    {
        result = (IplImage*)src;
    }

    __END__;

    return result;
}


/****************************************************************************************\
*                               IplImage-specific functions                              *
\****************************************************************************************/

static IplROI* icvCreateROI( int coi, int xOffset, int yOffset, int width, int height )
{
    IplROI *roi = 0;

    CV_FUNCNAME( "icvCreateROI" );

    __BEGIN__;

    if( !CvIPL.createROI )
    {
        CV_CALL( roi = (IplROI*)cvAlloc( sizeof(*roi)));

        roi->coi = coi;
        roi->xOffset = xOffset;
        roi->yOffset = yOffset;
        roi->width = width;
        roi->height = height;
    }
    else
    {
        roi = CvIPL.createROI( coi, xOffset, yOffset, width, height );
    }

    __END__;

    return roi;
}

static  void
icvGetColorModel( int nchannels, char** colorModel, char** channelSeq )
{
    static char* tab[][2] =
    {
        {"GRAY", "GRAY"},
        {"",""},
        {"RGB","BGR"},
        {"RGB","BGRA"}
    };

    nchannels--;
    *colorModel = *channelSeq = "";

    if( (unsigned)nchannels <= 3 )
    {
        *colorModel = tab[nchannels][0];
        *channelSeq = tab[nchannels][1];
    }
}


// create IplImage header
CV_IMPL IplImage *
cvCreateImageHeader( CvSize size, int depth, int channels )
{
    IplImage *img = 0;

    CV_FUNCNAME( "cvCreateImageHeader" );

    __BEGIN__;

    if( !CvIPL.createHeader )
    {
        CV_CALL( img = (IplImage *)cvAlloc( sizeof( *img )));
        CV_CALL( cvInitImageHeader( img, size, depth, channels, IPL_ORIGIN_TL, 4, 1 ));
    }
    else
    {
        char *colorModel;
        char *channelSeq;

        icvGetColorModel( channels, &colorModel, &channelSeq );

        img = CvIPL.createHeader( channels, 0, depth, colorModel, channelSeq,
                                  IPL_DATA_ORDER_PIXEL, IPL_ORIGIN_TL, 4,
                                  size.width, size.height, 0, 0, 0, 0 );
    }

    __END__;

    if( cvGetErrStatus() < 0 && img )
        cvReleaseImageHeader( &img );

    return img;
}


// create IplImage header and allocate underlying data
CV_IMPL IplImage *
cvCreateImage( CvSize size, int depth, int channels )
{
    IplImage *img = 0;

    CV_FUNCNAME( "cvCreateImage" );

    __BEGIN__;

    CV_CALL( img = cvCreateImageHeader( size, depth, channels ));
    assert( img );
    CV_CALL( cvCreateData( img ));

    __END__;

    if( cvGetErrStatus() < 0 )
        cvReleaseImage( &img );

    return img;
}


// initalize IplImage header, allocated by the user
CV_IMPL IplImage*
cvInitImageHeader( IplImage * image, CvSize size, int depth,
                   int channels, int origin, int align, int clear )
{
    IplImage* result = 0;

    CV_FUNCNAME( "cvInitImageHeader" );

    __BEGIN__;

    if( !image )
        CV_ERROR( IPL_HeaderIsNull, "null pointer to header" );

    if( clear )
    {
        char *colorModel, *channelSeq;

        memset( image, 0, sizeof( *image ));
        image->nSize = sizeof( *image );

        CV_CALL( icvGetColorModel( channels, &colorModel, &channelSeq ));
        strncpy( image->colorModel, colorModel, 4 );
        strncpy( image->channelSeq, channelSeq, 4 );
    }

    if( size.width < 0 || size.height < 0 )
        CV_ERROR( CV_BadROISize, "Bad input roi" );

    if( (depth != (int)IPL_DEPTH_1U && depth != (int)IPL_DEPTH_8U &&
         depth != (int)IPL_DEPTH_8S && depth != (int)IPL_DEPTH_16U &&
         depth != (int)IPL_DEPTH_16S && depth != (int)IPL_DEPTH_32S &&
         depth != (int)IPL_DEPTH_32F && depth != (int)IPL_DEPTH_64F) ||
         channels < 0 )
        CV_ERROR( IPL_BadDepth, "Unsupported format" );
    if( origin != CV_ORIGIN_BL && origin != CV_ORIGIN_TL )
        CV_ERROR( IPL_BadOrigin, "Bad input origin" );

    if( align != 4 && align != 8 )
        CV_ERROR( IPL_BadAlign, "Bad input align" );

    image->width = size.width;
    image->height = size.height;

    if( image->roi )
    {
        image->roi->coi = 0;
        image->roi->xOffset = image->roi->yOffset = 0;
        image->roi->width = size.width;
        image->roi->height = size.height;
    }

    image->nChannels = MAX( channels, 1 );
    image->depth = depth;
    image->align = align;
    image->widthStep = (((image->width * image->nChannels *
         (image->depth & ~IPL_DEPTH_SIGN) + 7)/8)+ align - 1) & (~(align - 1));
    image->origin = origin;
    image->imageSize = image->widthStep * image->height;

    result = image;

    __END__;

    return result;
}


CV_IMPL void
cvReleaseImageHeader( IplImage** image )
{
    CV_FUNCNAME( "cvReleaseImageHeader" );

    __BEGIN__;

    if( !image )
        CV_ERROR( CV_StsNullPtr, "" );

    if( *image )
    {
        IplImage* img = *image;
        *image = 0;
        
        if( !CvIPL.deallocate )
        {
            cvFree( (void**)&(img->roi) );
            cvFree( (void**)&img );
        }
        else
        {
            CvIPL.deallocate( img, IPL_IMAGE_HEADER | IPL_IMAGE_ROI );
        }
    }
    __END__;
}


CV_IMPL void
cvReleaseImage( IplImage ** image )
{
    CV_FUNCNAME( "cvReleaseImage" );

    __BEGIN__

    if( !image )
        CV_ERROR( CV_StsNullPtr, "" );

    if( *image )
    {
        IplImage* img = *image;
        *image = 0;
        
        cvReleaseData( img );
        cvReleaseImageHeader( &img );
    }

    __END__;
}


void
icvCheckImageHeader( const IplImage * img, const char *image_name )
{
    CV_FUNCNAME( "icvCheckImageHeader" );

    __BEGIN__;

    if( !img )
        CV_ERROR( IPL_HeaderIsNull, image_name );

    if( img->dataOrder != IPL_DATA_ORDER_PIXEL && img->nChannels > 1 )
        CV_ERROR( IPL_BadOrder, image_name );

    if( img->maskROI != 0 || img->tileInfo != 0 )
        CV_ERROR( IPL_StsBadArg, image_name );

    if( img->imageData == 0 )
        CV_ERROR( IPL_BadDataPtr, image_name );

    if( img->roi &&
        ((img->roi->xOffset | img->roi->yOffset | img->roi->width | img->roi->height) < 0 ||
         img->roi->xOffset + img->roi->width > img->width ||
         img->roi->yOffset + img->roi->height > img->height ||
         (unsigned) (img->roi->coi) > (unsigned) (img->nChannels)))
        CV_ERROR( IPL_BadROISize, image_name );

    __END__;
}


void
icvCheckMaskImageHeader( const IplImage * img, const char *image_name )
{
    CV_FUNCNAME( "cvCheckMaskImageHeader" );

    __BEGIN__;

    CV_CALL( icvCheckImageHeader( img, image_name ));

    if( img->depth != (int)IPL_DEPTH_8U && img->depth != (int)IPL_DEPTH_8S )
        CV_ERROR( IPL_BadDepth, image_name );

    if( img->nChannels != 1 )
        CV_ERROR( IPL_BadNumChannels, image_name );

    __END__;
}



CV_IMPL void
cvSetImageROI( IplImage* image, CvRect rect )
{
    CV_FUNCNAME( "cvSetImageROI" );

    __BEGIN__;

    if( !image )
        CV_ERROR( IPL_HeaderIsNull, 0 );

    if( rect.x > image->width || rect.y > image->height )
        CV_ERROR( IPL_BadROISize, 0 );

    if( rect.x + rect.width < 0 || rect.y + rect.height < 0 )
        CV_ERROR( IPL_BadROISize, 0 );

    if( rect.x < 0 )
    {
        rect.width += rect.x;
        rect.x = 0;
    }

    if( rect.y < 0 )
    {
        rect.height += rect.y;
        rect.y = 0;
    }

    if( rect.x + rect.width > image->width )
        rect.width = image->width - rect.x;

    if( rect.y + rect.height > image->height )
        rect.height = image->height - rect.y;

    if( image->roi )
    {
        image->roi->xOffset = rect.x;
        image->roi->yOffset = rect.y;
        image->roi->width = rect.width;
        image->roi->height = rect.height;
    }
    else
    {
        CV_CALL( image->roi = icvCreateROI( 0, rect.x, rect.y, rect.width, rect.height ));
    }

    __END__;
}


CV_IMPL void
cvResetImageROI( IplImage* image )
{
    CV_FUNCNAME( "cvResetImageROI" );

    __BEGIN__;

    if( !image )
        CV_ERROR( IPL_HeaderIsNull, 0 );

    if( image->roi )
    {
        if( !CvIPL.deallocate )
        {
            CV_CALL( cvFree( (void**)&(image->roi) ));
        }
        else
        {
            CvIPL.deallocate( image, IPL_IMAGE_ROI );
            image->roi = 0;
        }
    }

    __END__;
}


CV_IMPL CvRect
cvGetImageROI( const IplImage* img )
{
    CvRect rect = { 0, 0, 0, 0 };
    
    CV_FUNCNAME( "cvGetImageROI" );

    __BEGIN__;

    if( !img )
        CV_ERROR( IPL_StsNullPtr, "Null pointer to image" );

    if( img->roi )
        rect = cvRect( img->roi->xOffset, img->roi->yOffset,
                       img->roi->width, img->roi->height );
    else
        rect = cvRect( 0, 0, img->width, img->height );

    __END__;
    
    return rect;
}


CV_IMPL void
cvSetImageCOI( IplImage* image, int coi )
{
    CV_FUNCNAME( "cvSetImageCOI" );

    __BEGIN__;

    if( !image )
        CV_ERROR( IPL_HeaderIsNull, 0 );

    if( (unsigned)coi > (unsigned)(image->nChannels) )
        CV_ERROR( IPL_BadCOI, 0 );

    if( image->roi || coi != 0 )
    {
        if( image->roi )
        {
            image->roi->coi = coi;
        }
        else
        {
            CV_CALL( image->roi = icvCreateROI( coi, 0, 0, image->width, image->height ));
        }
    }

    __END__;
}


CV_IMPL int
cvGetImageCOI( IplImage* image )
{
    int coi = -1;
    CV_FUNCNAME( "cvGetImageCOI" );

    __BEGIN__;

    if( !image )
        CV_ERROR( IPL_HeaderIsNull, 0 );

    coi = image->roi ? image->roi->coi : 0;

    __END__;

    return coi;
}


CV_IMPL IplImage*
cvCloneImage( const IplImage* src )
{
    IplImage* dst = 0;
    CV_FUNCNAME( "cvCloneImage" );

    __BEGIN__;

    if( !_CV_IS_IMAGE( src ))
        CV_ERROR( CV_StsBadArg, "Bad image header" );

    if( !CvIPL.cloneImage )
    {
        CV_CALL( dst = (IplImage*)cvAlloc( sizeof(*dst)));

        memcpy( dst, src, sizeof(*src));
        dst->roi = 0;

        if( src->roi )
        {
            dst->roi = icvCreateROI( src->roi->coi, src->roi->xOffset,
                          src->roi->yOffset, src->roi->width, src->roi->height );
        }

        if( src->imageData )
        {
            int size = src->imageSize;
            cvCreateData( dst );
            memcpy( dst->imageData, src->imageData, size );
        }
    }
    else
    {
        dst = CvIPL.cloneImage( src );
    }

    __END__;

    return dst;
}


/****************************************************************************************\
*                            Additional operations on CvTermCriteria                     *
\****************************************************************************************/

CvTermCriteria
icvCheckTermCriteria( CvTermCriteria criteria, double default_eps,
                      int default_max_iters )
{
    CV_FUNCNAME( "icvCheckTermCriteria" );

    CvTermCriteria crit;

    crit.type = CV_TERMCRIT_ITER|CV_TERMCRIT_EPS;
    crit.maxIter = default_max_iters;
    crit.epsilon = (float)default_eps;
    
    __BEGIN__;

    if( (criteria.type & ~(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER)) != 0 )
        CV_ERROR( CV_StsBadArg,
                  "Unknown type of term criteria" );

    if( (criteria.type & CV_TERMCRIT_ITER) != 0 )
    {
        if( criteria.maxIter <= 0 )
            CV_ERROR( CV_StsBadArg,
                  "Iterations flag is set and maximum number of iterations is <= 0" );
        crit.maxIter = criteria.maxIter;
    }
    
    if( (criteria.type & CV_TERMCRIT_EPS) != 0 )
    {
        if( criteria.epsilon < 0 )
            CV_ERROR( CV_StsBadArg, "Accuracy flag is set and epsilon is < 0" );

        crit.epsilon = criteria.epsilon;
    }

    if( (criteria.type & (CV_TERMCRIT_EPS | CV_TERMCRIT_ITER)) == 0 )
        CV_ERROR( CV_StsBadArg,
                  "Neither accuracy nor maximum iterations "
                  "number flags are set in criteria type" );

    __END__;

    crit.epsilon = (float)MAX( 0, crit.epsilon );
    crit.maxIter = MAX( 1, crit.maxIter );

    return crit;
}


/* End of file. */

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
/*--------------------------------------------------------------------------------------*/

/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name: cvCalcCovarMatrixEx
//    Purpose: The function calculates a covariance matrix for a group of input objects
//             (images, vectors, etc.).
//    Context:
//    Parameters:  nObjects    - number of source objects
//                 input       - pointer either to array of input objects
//                               or to read callback function (depending on ioFlags)
//                 ioFlags     - input/output flags (see Notes to
//                               cvCalcEigenObjects function)
//                 ioBufSize   - input/output buffer size
//                 userData    - pointer to the structure which contains all necessary
//                               data for the callback functions
//                 avg         - averaged object
//                 covarMatrix - covariance matrix (output parameter; must be allocated
//                               before call)
//
//    Notes:  See Notes to cvCalcEigenObjects function
//F*/

CV_IMPL void
cvCalcCovarMatrixEx( int       nObjects,
                     void*     input,
                     int       ioFlags,
                     int       ioBufSize,
                     uchar*    buffer,
                     void*     userData,
                     IplImage* avg,
                     float*    covarMatrix )
{
    float *avg_data;
    int avg_step = 0;
    CvSize avg_size;
    int i;

    CV_FUNCNAME( "cvCalcCovarMatrixEx" );

    __BEGIN__;

    CV_CALL( CV_CHECK_IMAGE( avg ));
    cvGetImageRawData( avg, (uchar **) & avg_data, &avg_step, &avg_size );
    if( avg->depth != IPL_DEPTH_32F )
        CV_ERROR( IPL_BadDepth, icvUnsupportedFormat );
    if( avg->nChannels != 1 )
        CV_ERROR( IPL_BadNumChannels, icvUnsupportedFormat );

    if( ioFlags == CV_EIGOBJ_NO_CALLBACK )
    {
        IplImage **images = (IplImage **) (((CvInput *) & input)->data);
        uchar **objects = (uchar **) icvAlloc( sizeof( uchar * ) * nObjects );
        int img_step = 0, old_step = 0;
        CvSize img_size = avg_size, old_size = avg_size;

        if( objects == NULL )
            CV_ERROR( IPL_StsBadArg, "Insufficient memory" );

        for( i = 0; i < nObjects; i++ )
        {
            IplImage *img = images[i];
            uchar *img_data;

            CV_CALL( CV_CHECK_IMAGE( img ));
            cvGetImageRawData( img, &img_data, &img_step, &img_size );
            if( img->depth != IPL_DEPTH_8U )
                CV_ERROR( IPL_BadDepth, icvUnsupportedFormat );
            if( img_size != avg_size || img_size != old_size )
                CV_ERROR( IPL_StsBadArg, "Different sizes of objects" );
            if( img->nChannels != 1 )
                CV_ERROR( IPL_BadNumChannels, icvUnsupportedFormat );
            if( i > 0 && img_step != old_step )
                CV_ERROR( IPL_StsBadArg, "Different steps of objects" );

            old_step = img_step;
            old_size = img_size;
            objects[i] = img_data;
        }

        CV_CALL( icvCalcCovarMatrixEx_8u32fR( nObjects,
                                              (void*) objects,
                                              img_step,
                                              CV_EIGOBJ_NO_CALLBACK,
                                              0,
                                              NULL,
                                              NULL,
                                              avg_data,
                                              avg_step,
                                              avg_size,
                                              covarMatrix ));
        icvFree( (void**) &objects );
    }

    else

    {
        CV_CALL( icvCalcCovarMatrixEx_8u32fR( nObjects,
                                              input,
                                              avg_step / 4,
                                              ioFlags,
                                              ioBufSize,
                                              buffer,
                                              userData,
                                              avg_data,
                                              avg_step,
                                              avg_size,
                                              covarMatrix ));
    }

    __CLEANUP__;
    __END__;
}

/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name: cvCalcEigenObjects
//    Purpose: The function calculates an orthonormal eigen basis and a mean (averaged)
//             object for a group of input objects (images, vectors, etc.).
//    Context:
//    Parameters: nObjects  - number of source objects
//                input     - pointer either to array of input objects
//                            or to read callback function (depending on ioFlags)
//                output    - pointer either to output eigen objects
//                            or to write callback function (depending on ioFlags)
//                ioFlags   - input/output flags (see Notes)
//                ioBufSize - input/output buffer size
//                userData  - pointer to the structure which contains all necessary
//                            data for the callback functions
//                calcLimit - determines the calculation finish conditions
//                avg       - averaged object (has the same size as ROI)
//                eigVals   - pointer to corresponding eigen values (array of <nObjects>
//                            elements in descending order)
//
//    Notes: 1. input/output data (that is, input objects and eigen ones) may either
//              be allocated in the RAM or be read from/written to the HDD (or any
//              other device) by read/write callback functions. It depends on the
//              value of ioFlags paramater, which may be the following:
//                  CV_EIGOBJ_NO_CALLBACK, or 0;
//                  CV_EIGOBJ_INPUT_CALLBACK;
//                  CV_EIGOBJ_OUTPUT_CALLBACK;
//                  CV_EIGOBJ_BOTH_CALLBACK, or
//                            CV_EIGOBJ_INPUT_CALLBACK | CV_EIGOBJ_OUTPUT_CALLBACK.
//              The callback functions as well as the user data structure must be
//              developed by the user.
//
//           2. If ioBufSize = 0, or it's too large, the function dermines buffer size
//              itself.
//
//           3. Depending on calcLimit parameter, calculations are finished either if
//              eigenfaces number comes up to certain value or the relation of the
//              current eigenvalue and the largest one comes down to certain value
//              (or any of the above conditions takes place). The calcLimit->type value
//              must be CV_TERMCRIT_NUMB, CV_TERMCRIT_EPS or
//              CV_TERMCRIT_NUMB | CV_TERMCRIT_EPS. The function returns the real
//              values calcLimit->maxIter and calcLimit->epsilon.
//
//           4. eigVals may be equal to NULL (if you don't need eigen values in further).
//
//F*/
CV_IMPL void
cvCalcEigenObjects( int       nObjects,
                    void*     input,
                    void*     output,
                    int       ioFlags,
                    int       ioBufSize,
                    void*     userData,
                    CvTermCriteria* calcLimit,
                    IplImage* avg, 
                    float*    eigVals )
{
    float *avg_data;
    int avg_step = 0;
    CvSize avg_size;
    int i;
    int nEigens = nObjects - 1;

    CV_FUNCNAME( "cvCalcEigenObjects" );

    __BEGIN__;

    CV_CALL( CV_CHECK_IMAGE( avg ));
    cvGetImageRawData( avg, (uchar **) & avg_data, &avg_step, &avg_size );
    if( avg->depth != IPL_DEPTH_32F )
        CV_ERROR( IPL_BadDepth, icvUnsupportedFormat );
    if( avg->nChannels != 1 )
        CV_ERROR( IPL_BadNumChannels, icvUnsupportedFormat );

    if( nEigens > calcLimit->maxIter && calcLimit->type != CV_TERMCRIT_EPS )
        nEigens = calcLimit->maxIter;

    switch (ioFlags)
    {
    case CV_EIGOBJ_NO_CALLBACK:
        {
            IplImage **objects = (IplImage **) (((CvInput *) & input)->data);
            IplImage **eigens = (IplImage **) (((CvInput *) & output)->data);
            uchar **objs = (uchar **) icvAlloc( sizeof( uchar * ) * nObjects );
            float **eigs = (float **) icvAlloc( sizeof( float * ) * nEigens );
            int obj_step = 0, old_step = 0;
            int eig_step = 0, oldeig_step = 0;
            CvSize obj_size = avg_size, old_size = avg_size,

                eig_size = avg_size, oldeig_size = avg_size;

            if( objects == NULL || eigens == NULL )
                CV_ERROR( IPL_StsBadArg, "Insufficient memory" );

            for( i = 0; i < nObjects; i++ )
            {
                IplImage *img = objects[i];
                uchar *obj_data;

                CV_CALL( CV_CHECK_IMAGE( img ));
                cvGetImageRawData( img, &obj_data, &obj_step, &obj_size );
                if( img->depth != IPL_DEPTH_8U )
                    CV_ERROR( IPL_BadDepth, icvUnsupportedFormat );
                if( obj_size != avg_size || obj_size != old_size )
                    CV_ERROR( IPL_StsBadArg, "Different sizes of objects" );
                if( img->nChannels != 1 )
                    CV_ERROR( IPL_BadNumChannels, icvUnsupportedFormat );
                if( i > 0 && obj_step != old_step )
                    CV_ERROR( IPL_StsBadArg, "Different steps of objects" );

                old_step = obj_step;
                old_size = obj_size;
                objs[i] = obj_data;
            }
            for( i = 0; i < nEigens; i++ )
            {
                IplImage *eig = eigens[i];
                float *eig_data;

                CV_CALL( CV_CHECK_IMAGE( eig ));
                cvGetImageRawData( eig, (uchar **) & eig_data, &eig_step, &eig_size );
                if( eig->depth != IPL_DEPTH_32F )
                    CV_ERROR( IPL_BadDepth, icvUnsupportedFormat );
                if( eig_size != avg_size || eig_size != oldeig_size )
                    CV_ERROR( IPL_StsBadArg, "Different sizes of objects" );
                if( eig->nChannels != 1 )
                    CV_ERROR( IPL_BadNumChannels, icvUnsupportedFormat );
                if( i > 0 && eig_step != oldeig_step )
                    CV_ERROR( IPL_StsBadArg, "Different steps of objects" );

                oldeig_step = eig_step;
                oldeig_size = eig_size;
                eigs[i] = eig_data;
            }
            CV_CALL( icvCalcEigenObjects_8u32fR( nObjects,
                                                 (void*) objs,
                                                 obj_step,
                                                 (void*) eigs,
                                                 eig_step,
                                                 obj_size,
                                                 ioFlags,
                                                 ioBufSize,
                                                 userData,
                                                 calcLimit,
                                                 avg_data,
                                                 avg_step,
                                                 eigVals   ));
            icvFree( (void**) &objs );
            icvFree( (void**) &eigs );
            break;
        }

    case CV_EIGOBJ_OUTPUT_CALLBACK:
        {
            IplImage **objects = (IplImage **) (((CvInput *) & input)->data);
            uchar **objs = (uchar **) icvAlloc( sizeof( uchar * ) * nObjects );
            int obj_step = 0, old_step = 0;
            CvSize obj_size = avg_size, old_size = avg_size;

            if( objects == NULL )
                CV_ERROR( IPL_StsBadArg, "Insufficient memory" );

            for( i = 0; i < nObjects; i++ )
            {
                IplImage *img = objects[i];
                uchar *obj_data;

                CV_CALL( CV_CHECK_IMAGE( img ));
                cvGetImageRawData( img, &obj_data, &obj_step, &obj_size );
                if( img->depth != IPL_DEPTH_8U )
                    CV_ERROR( IPL_BadDepth, icvUnsupportedFormat );
                if( obj_size != avg_size || obj_size != old_size )
                    CV_ERROR( IPL_StsBadArg, "Different sizes of objects" );
                if( img->nChannels != 1 )
                    CV_ERROR( IPL_BadNumChannels, icvUnsupportedFormat );
                if( i > 0 && obj_step != old_step )
                    CV_ERROR( IPL_StsBadArg, "Different steps of objects" );

                old_step = obj_step;
                old_size = obj_size;
                objs[i] = obj_data;
            }
            CV_CALL( icvCalcEigenObjects_8u32fR( nObjects,
                                                 (void*) objs,
                                                 obj_step,
                                                 output,
                                                 avg_step,
                                                 obj_size,
                                                 ioFlags,
                                                 ioBufSize,
                                                 userData,
                                                 calcLimit,
                                                 avg_data,
                                                 avg_step,
                                                 eigVals   ));
            icvFree( (void **) &objs );
            break;
        }

    case CV_EIGOBJ_INPUT_CALLBACK:
        {
            IplImage **eigens = (IplImage **) (((CvInput *) & output)->data);
            float **eigs = (float**) icvAlloc( sizeof( float* ) * nEigens );
            int eig_step = 0, oldeig_step = 0;
            CvSize eig_size = avg_size, oldeig_size = avg_size;

            if( eigens == NULL )
                CV_ERROR( IPL_StsBadArg, "Insufficient memory" );

            for( i = 0; i < nEigens; i++ )
            {
                IplImage *eig = eigens[i];
                float *eig_data;

                CV_CALL( CV_CHECK_IMAGE( eig ));
                cvGetImageRawData( eig, (uchar **) & eig_data, &eig_step, &eig_size );
                if( eig->depth != IPL_DEPTH_32F )
                    CV_ERROR( IPL_BadDepth, icvUnsupportedFormat );
                if( eig_size != avg_size || eig_size != oldeig_size )
                    CV_ERROR( IPL_StsBadArg, "Different sizes of objects" );
                if( eig->nChannels != 1 )
                    CV_ERROR( IPL_BadNumChannels, icvUnsupportedFormat );
                if( i > 0 && eig_step != oldeig_step )
                    CV_ERROR( IPL_StsBadArg, "Different steps of objects" );

                oldeig_step = eig_step;
                oldeig_size = eig_size;
                eigs[i] = eig_data;
            }
            CV_CALL( icvCalcEigenObjects_8u32fR( nObjects,
                                                 input,
                                                 avg_step / 4,
                                                 (void*) eigs,
                                                 eig_step,
                                                 eig_size,
                                                 ioFlags,
                                                 ioBufSize,
                                                 userData,
                                                 calcLimit,
                                                 avg_data,
                                                 avg_step,
                                                 eigVals   ));
            icvFree( (void **) &eigs );
            break;
        }
    case CV_EIGOBJ_INPUT_CALLBACK | CV_EIGOBJ_OUTPUT_CALLBACK:

        CV_CALL( icvCalcEigenObjects_8u32fR( nObjects,
                                             input,
                                             avg_step / 4,
                                             output,
                                             avg_step,
                                             avg_size,
                                             ioFlags,
                                             ioBufSize,
                                             userData,
                                             calcLimit,
                                             avg_data,
                                             avg_step,
                                             eigVals   ));
        break;

    default:
        CV_ERROR( IPL_StsBadArg, "Unsupported i/o flag" );
    }

    __CLEANUP__;
    __END__;
}

/*--------------------------------------------------------------------------------------*/
/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name: cvCalcDecompCoeff
//    Purpose: The function calculates one decomposition coefficient of input object
//             using previously calculated eigen object and the mean (averaged) object
//    Context:
//    Parameters:  obj     - input object
//                 eigObj  - eigen object
//                 avg     - averaged object
//
//    Returns: decomposition coefficient value or large negative value (if error)
//
//    Notes:
//F*/

CV_IMPL double
cvCalcDecompCoeff( IplImage * obj, IplImage * eigObj, IplImage * avg )
{
    double coeff = DBL_MAX;

    uchar *obj_data;
    float *eig_data;
    float *avg_data;
    int obj_step = 0, eig_step = 0, avg_step = 0;
    CvSize obj_size, eig_size, avg_size;

    CV_FUNCNAME( "cvCalcDecompCoeff" );

    __BEGIN__;

    CV_CALL( CV_CHECK_IMAGE( obj ));
    CV_CALL( CV_CHECK_IMAGE( eigObj ));
    CV_CALL( CV_CHECK_IMAGE( avg ));

    cvGetImageRawData( obj, &obj_data, &obj_step, &obj_size );
    if( obj->depth != IPL_DEPTH_8U )
        CV_ERROR( IPL_BadDepth, icvUnsupportedFormat );
    if( obj->nChannels != 1 )
        CV_ERROR( IPL_BadNumChannels, icvUnsupportedFormat );

    cvGetImageRawData( eigObj, (uchar **) & eig_data, &eig_step, &eig_size );
    if( eigObj->depth != IPL_DEPTH_32F )
        CV_ERROR( IPL_BadDepth, icvUnsupportedFormat );
    if( eigObj->nChannels != 1 )
        CV_ERROR( IPL_BadNumChannels, icvUnsupportedFormat );

    cvGetImageRawData( avg, (uchar **) & avg_data, &avg_step, &avg_size );
    if( avg->depth != IPL_DEPTH_32F )
        CV_ERROR( IPL_BadDepth, icvUnsupportedFormat );
    if( avg->nChannels != 1 )
        CV_ERROR( IPL_BadNumChannels, icvUnsupportedFormat );

    if( obj_size != eig_size || obj_size != avg_size )
        CV_ERROR( IPL_StsBadArg, "different sizes of images" );

    coeff = icvCalcDecompCoeff_8u32fR( obj_data, obj_step,
                                       eig_data, eig_step,
                                       avg_data, avg_step, obj_size );

    __END__;
    
    return coeff;
}

/*--------------------------------------------------------------------------------------*/
/*F///////////////////////////////////////////////////////////////////////////////////////
//    Names: cvEigenDecomposite
//    Purpose: The function calculates all decomposition coefficients for input object
//             using previously calculated eigen objects basis and the mean (averaged)
//             object
//
//    Parameters:  obj         - input object
//                 nEigObjs    - number of eigen objects
//                 eigInput    - pointer either to array of pointers to eigen objects
//                               or to read callback function (depending on ioFlags)
//                 ioFlags     - input/output flags
//                 userData    - pointer to the structure which contains all necessary
//                               data for the callback function
//                 avg         - averaged object
//                 coeffs      - calculated coefficients (output data)
//
//    Notes:   see notes for cvCalcEigenObjects function
//F*/

CV_IMPL void
cvEigenDecomposite( IplImage* obj,
                    int       nEigObjs,
                    void*     eigInput,
                    int       ioFlags, 
                    void*     userData, 
                    IplImage* avg, 
                    float*    coeffs )
{
    float *avg_data;
    uchar *obj_data;
    int avg_step = 0, obj_step = 0;
    CvSize avg_size, obj_size;
    int i;

    CV_FUNCNAME( "cvEigenDecomposite" );

    __BEGIN__;

    CV_CALL( CV_CHECK_IMAGE( avg ));
    cvGetImageRawData( avg, (uchar **) & avg_data, &avg_step, &avg_size );
    if( avg->depth != IPL_DEPTH_32F )
        CV_ERROR( IPL_BadDepth, icvUnsupportedFormat );
    if( avg->nChannels != 1 )
        CV_ERROR( IPL_BadNumChannels, icvUnsupportedFormat );

    CV_CALL( CV_CHECK_IMAGE( obj ));
    cvGetImageRawData( obj, &obj_data, &obj_step, &obj_size );
    if( obj->depth != IPL_DEPTH_8U )
        CV_ERROR( IPL_BadDepth, icvUnsupportedFormat );
    if( obj->nChannels != 1 )
        CV_ERROR( IPL_BadNumChannels, icvUnsupportedFormat );

    if( obj_size != avg_size )
        CV_ERROR( IPL_StsBadArg, "Different sizes of objects" );

    if( ioFlags == CV_EIGOBJ_NO_CALLBACK )
    {
        IplImage **eigens = (IplImage **) (((CvInput *) & eigInput)->data);
        float **eigs = (float **) icvAlloc( sizeof( float * ) * nEigObjs );
        int eig_step = 0, old_step = 0;
        CvSize eig_size = avg_size, old_size = avg_size;

        if( eigs == NULL )
            CV_ERROR( IPL_StsBadArg, "Insufficient memory" );

        for( i = 0; i < nEigObjs; i++ )
        {
            IplImage *eig = eigens[i];
            float *eig_data;

            CV_CALL( CV_CHECK_IMAGE( eig ));
            cvGetImageRawData( eig, (uchar **) & eig_data, &eig_step, &eig_size );
            if( eig->depth != IPL_DEPTH_32F )
                CV_ERROR( IPL_BadDepth, icvUnsupportedFormat );
            if( eig_size != avg_size || eig_size != old_size )
                CV_ERROR( IPL_StsBadArg, "Different sizes of objects" );
            if( eig->nChannels != 1 )
                CV_ERROR( IPL_BadNumChannels, icvUnsupportedFormat );
            if( i > 0 && eig_step != old_step )
                CV_ERROR( IPL_StsBadArg, "Different steps of objects" );

            old_step = eig_step;
            old_size = eig_size;
            eigs[i] = eig_data;
        }

        CV_CALL( icvEigenDecomposite_8u32fR( obj_data,
                                             obj_step,
                                             nEigObjs,
                                             (void*) eigs,
                                             eig_step,
                                             ioFlags,
                                             userData,
                                             avg_data,
                                             avg_step,
                                             obj_size,
                                             coeffs   ));
        icvFree( (void **) &eigs );
    }

    else

    {
        CV_CALL( icvEigenDecomposite_8u32fR( obj_data,
                                             obj_step,
                                             nEigObjs,
                                             eigInput,
                                             avg_step,
                                             ioFlags,
                                             userData,
                                             avg_data,
                                             avg_step,
                                             obj_size,
                                             coeffs   ));
    }

    __CLEANUP__;
    __END__;
}

/*--------------------------------------------------------------------------------------*/
/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name: cvEigenProjection
//    Purpose: The function calculates object projection to the eigen sub-space (restores
//             an object) using previously calculated eigen objects basis, mean (averaged)
//             object and decomposition coefficients of the restored object
//    Context:
//    Parameters:  nEigObjs    - number of eigen objects
//                 eigInput    - pointer either to array of pointers to eigen objects
//                               or to read callback function (depending on ioFlags)
//                 ioFlags     - input/output flags
//                 userData    - pointer to the structure which contains all necessary
//                               data for the callback function
//                 coeffs      - array of decomposition coefficients
//                 avg         - averaged object
//                 proj        - object projection (output data)
//
//    Notes:   see notes for cvCalcEigenObjects function
//F*/

CV_IMPL void
cvEigenProjection( void*     eigInput,
                   int       nEigObjs,
                   int       ioFlags,
                   void*     userData,
                   float*    coeffs, 
                   IplImage* avg,
                   IplImage* proj )
{
    float *avg_data;
    uchar *proj_data;
    int avg_step = 0, proj_step = 0;
    CvSize avg_size, proj_size;
    int i;

    CV_FUNCNAME( "cvEigenProjection" );

    __BEGIN__;

    CV_CALL( CV_CHECK_IMAGE( avg ));
    cvGetImageRawData( avg, (uchar **) & avg_data, &avg_step, &avg_size );
    if( avg->depth != IPL_DEPTH_32F )
        CV_ERROR( IPL_BadDepth, icvUnsupportedFormat );
    if( avg->nChannels != 1 )
        CV_ERROR( IPL_BadNumChannels, icvUnsupportedFormat );

    CV_CALL( CV_CHECK_IMAGE( proj ));
    cvGetImageRawData( proj, &proj_data, &proj_step, &proj_size );
    if( proj->depth != IPL_DEPTH_8U )
        CV_ERROR( IPL_BadDepth, icvUnsupportedFormat );
    if( proj->nChannels != 1 )
        CV_ERROR( IPL_BadNumChannels, icvUnsupportedFormat );

    if( proj_size != avg_size )
        CV_ERROR( IPL_StsBadArg, "Different sizes of projects" );

    if( ioFlags == CV_EIGOBJ_NO_CALLBACK )
    {
        IplImage **eigens = (IplImage**) (((CvInput *) & eigInput)->data);
        float **eigs = (float**) icvAlloc( sizeof( float * ) * nEigObjs );
        int eig_step = 0, old_step = 0;
        CvSize eig_size = avg_size, old_size = avg_size;

        if( eigs == NULL )
            CV_ERROR( IPL_StsBadArg, "Insufficient memory" );

        for( i = 0; i < nEigObjs; i++ )
        {
            IplImage *eig = eigens[i];
            float *eig_data;

            CV_CALL( CV_CHECK_IMAGE( eig ));
            cvGetImageRawData( eig, (uchar **) & eig_data, &eig_step, &eig_size );
            if( eig->depth != IPL_DEPTH_32F )
                CV_ERROR( IPL_BadDepth, icvUnsupportedFormat );
            if( eig_size != avg_size || eig_size != old_size )
                CV_ERROR( IPL_StsBadArg, "Different sizes of objects" );
            if( eig->nChannels != 1 )
                CV_ERROR( IPL_BadNumChannels, icvUnsupportedFormat );
            if( i > 0 && eig_step != old_step )
                CV_ERROR( IPL_StsBadArg, "Different steps of objects" );

            old_step = eig_step;
            old_size = eig_size;
            eigs[i] = eig_data;
        }

        CV_CALL( icvEigenProjection_8u32fR( nEigObjs,
                                            (void*) eigs,
                                            eig_step,
                                            ioFlags,
                                            userData,
                                            coeffs,
                                            avg_data,
                                            avg_step,
                                            proj_data,
                                            proj_step,
                                            avg_size   ));
        icvFree( (void **) &eigs );
    }

    else

    {
        CV_CALL( icvEigenProjection_8u32fR( nEigObjs,
                                            eigInput,
                                            avg_step,
                                            ioFlags,
                                            userData,
                                            coeffs,
                                            avg_data,
                                            avg_step,
                                            proj_data,
                                            proj_step,
                                            avg_size   ));
    }

    __CLEANUP__;
    __END__;
}

/*  END  OF   FILE  */

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

CV_IMPL CvEHMM*
cvCreate2DHMM( int *state_number, int *num_mix, int obs_size )
{
    CvEHMM* hmm = 0;

    CV_FUNCNAME( "cvCreate2DHMM" );

    __BEGIN__;

    IPPI_CALL( icvCreate2DHMM( &hmm, state_number, num_mix, obs_size ));

    __END__;

    return hmm;
}

CV_IMPL void
cvRelease2DHMM( CvEHMM ** hmm )
{
    CV_FUNCNAME( "cvRelease2DHMM" );

    __BEGIN__;

    IPPI_CALL( icvRelease2DHMM( hmm ));
    __END__;
}

CV_IMPL CvImgObsInfo*
cvCreateObsInfo( CvSize num_obs, int obs_size )
{
    CvImgObsInfo *obs_info = 0;
    
    CV_FUNCNAME( "cvCreateObsInfo" );

    __BEGIN__;

    IPPI_CALL( icvCreateObsInfo( &obs_info, num_obs, obs_size ));

    __END__;

    return obs_info;
}

CV_IMPL void
cvReleaseObsInfo( CvImgObsInfo ** obs_info )
{
    CV_FUNCNAME( "cvReleaseObsInfo" );

    __BEGIN__;

    IPPI_CALL( icvReleaseObsInfo( obs_info ));

    __END__;
}

CV_IMPL void
cvImgToObs_DCT( const void* arr, float *obs, CvSize dctSize,
                CvSize obsSize, CvSize delta )
{
    CV_FUNCNAME( "cvImgToObs_DCT" );

    __BEGIN__;

    CvMat stub, *mat = (CvMat*)arr;

    CV_CALL( mat = cvGetMat( arr, &stub ));

    if( CV_ARR_TYPE( mat->type ) != CV_8UC1 )
        CV_ERROR( CV_StsUnsupportedFormat, "" );

    IPPI_CALL( icvImgToObs_DCT_8u32f_C1R( (uchar*)mat->data.ptr, mat->step,
                                           icvGetMatSize(mat), obs,
                                           dctSize, obsSize, delta ));

    __END__;

}

CV_IMPL void
cvUniformImgSegm( CvImgObsInfo * obs_info, CvEHMM * hmm )
{
    CV_FUNCNAME( "cvUniformImgSegm" );

    __BEGIN__;

    IPPI_CALL( icvUniformImgSegm( obs_info, hmm ));
    __CLEANUP__;
    __END__;
}

CV_IMPL void
cvInitMixSegm( CvImgObsInfo ** obs_info_array, int num_img, CvEHMM * hmm )
{
    CV_FUNCNAME( "cvInitMixSegm" );

    __BEGIN__;

    IPPI_CALL( icvInitMixSegm( obs_info_array, num_img, hmm ));

    __END__;
}

CV_IMPL void
cvEstimateHMMStateParams( CvImgObsInfo ** obs_info_array, int num_img, CvEHMM * hmm )
{
    CV_FUNCNAME( "cvEstimateHMMStateParams" );

    __BEGIN__;

    IPPI_CALL( icvEstimateHMMStateParams( obs_info_array, num_img, hmm ));

    __END__;
}

CV_IMPL void
cvEstimateTransProb( CvImgObsInfo ** obs_info_array, int num_img, CvEHMM * hmm )
{
    CV_FUNCNAME( "cvEstimateTransProb" );

    __BEGIN__;

    IPPI_CALL( icvEstimateTransProb( obs_info_array, num_img, hmm ));

    __END__;

}

CV_IMPL void
cvEstimateObsProb( CvImgObsInfo * obs_info, CvEHMM * hmm )
{
    CV_FUNCNAME( "cvEstimateObsProb" );

    __BEGIN__;

    IPPI_CALL( icvEstimateObsProb( obs_info, hmm ));

    __END__;
}

CV_IMPL float
cvEViterbi( CvImgObsInfo * obs_info, CvEHMM * hmm )
{
    float result = FLT_MAX;

    CV_FUNCNAME( "cvEViterbi" );

    __BEGIN__;

    if( (obs_info == NULL) || (hmm == NULL) )
        CV_ERROR( IPL_BadDataPtr, "Null pointer." );

    result = icvEViterbi( obs_info, hmm );
    
    __END__;
    
    return result;
}

CV_IMPL void
cvMixSegmL2( CvImgObsInfo ** obs_info_array, int num_img, CvEHMM * hmm )
{
    CV_FUNCNAME( "cvMixSegmL2" );

    __BEGIN__;

    IPPI_CALL( icvMixSegmL2( obs_info_array, num_img, hmm ));

    __END__;
}

CV_IMPL void
cvKMeans( int num_clusters, CvVect32f * samples, int num_samples,
          int vec_size, CvTermCriteria termcrit, int *cluster )
{
    CV_FUNCNAME( "cvKMeans" );

    __BEGIN__;

    IPPI_CALL( icvKMeans( num_clusters, samples, num_samples, vec_size, termcrit, cluster ));

    __END__;
}

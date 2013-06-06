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

/****************************************************************************************\
*                                Mathematical functions                                  *
\****************************************************************************************/

CV_IMPL void
cvbFastArctan( const float *y, const float *x, float *angle, int len )
{
    CV_FUNCNAME( "cvbFastArctan" );

    __BEGIN__;

    IPPI_CALL( icvbFastArctan_32f( y, x, angle, len ));

    __END__;
}


CV_IMPL void
cvbCartToPolar( const float *y, const float *x, float *mag, float *angle, int len )
{
    CV_FUNCNAME( "cvbCartToPolar" );

    __BEGIN__;

    IPPI_CALL( icvbCartToPolar32f( (float *) y, (float *) x, mag, angle, len ));

    __END__;
}

CV_IMPL void
cvbSqrt( const float *x, float *sqrt_x, int len )
{
    CV_FUNCNAME( "cvbSqrt" );

    __BEGIN__;

    IPPI_CALL( icvbSqrt_32f( x, sqrt_x, len ));

    __END__;
}


CV_IMPL void
cvbInvSqrt( const float *x, float *inv_sqrt_x, int len )
{
    CV_FUNCNAME( "cvbInvSqrt" );

    __BEGIN__;

    IPPI_CALL( icvbInvSqrt_32f( x, inv_sqrt_x, len ));

    __END__;
}


CV_IMPL void
cvbReciprocal( const float *x, float *inv_x, int len )
{
    CV_FUNCNAME( "cvbReciprocal" );

    __BEGIN__;

    IPPI_CALL( icvbRecip_32f( x, inv_x, len ));

    __END__;
}


CV_IMPL void
cvbFastExp( const float *x, double *exp_x, int len )
{
    CV_FUNCNAME( "cvbFastExp" );

    __BEGIN__;

    IPPI_CALL( icvbExp_32f64f( x, exp_x, len ));

    __END__;
}


CV_IMPL void
cvbFastLog( const double *x, float *log_x, int len )
{
    CV_FUNCNAME( "cvbFastLog" );

    __BEGIN__;

    IPPI_CALL( icvbLog_64f32f( x, log_x, len ));

    __END__;
}

/* End of file. */

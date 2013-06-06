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


IPCVAPI_IMPL( CvStatus, icvCalcProbDensity, (CvHistogram * hist,
                                             CvHistogram * hist_mask,
                                             CvHistogram * hist_dens) )
{
    int i, j, height, width;
    float *cur_hist, *cur_hist_mask, *cur_hist_dens;
    float eps = (float) 1e-4;
    float fgist, fgistm;

    if( hist == NULL || hist_mask == NULL || hist_dens == NULL )
        return CV_NULLPTR_ERR;

    if( hist->type != hist_mask->type )
        return CV_BADFLAG_ERR;
    if( hist->c_dims != hist_mask->c_dims ||
        hist->c_dims != hist_dens->c_dims && hist->c_dims != 2 )
        return CV_BADSIZE_ERR;

    for( i = 0; i < hist->c_dims; i++ )
    {
        if( hist->dims[i] != hist_mask->dims[i] || hist->dims[i] != hist_dens->dims[i] )
            return CV_BADSIZE_ERR;
    }

    cur_hist = hist->array;
    cur_hist_mask = hist_mask->array;
    cur_hist_dens = hist_dens->array;

    width = hist->dims[1];
    height = hist->dims[0];

    for( i = 0; i < height;
         i++, cur_hist += width, cur_hist_mask += width, cur_hist_dens += width )
    {
        for( j = 0; j < width; j++ )
        {
            fgist = cur_hist[j];
            fgistm = cur_hist_mask[j];
            if( fgist > eps )
                if( fgistm <= fgist )
                    cur_hist_dens[j] = fgistm / fgist * 255;
                else
                    cur_hist_dens[j] = 255;
            else
                cur_hist_dens[j] = (float) 0;
        }
    }

    return CV_OK;
}

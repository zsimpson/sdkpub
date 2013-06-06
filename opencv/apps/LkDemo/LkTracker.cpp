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
//M*/#include "stdafx.h"

#include "LkTracker.h"


CLkTracker::CLkTracker()
{
    m_tracked = m_count = 0;
}


CLkTracker::~CLkTracker()
{
}


void CLkTracker::Initialize( CImage& image, int max_features, double quality,
                             double min_distance )
{
    IplImage* img = image.GetImage();

    if( img )
    {
        IplImage* img0 = 0;
        IplImage* img1 = 0; 
        
        for( int i = 0; i < 2; i++ )
        {
            m_features[i].SetSize( max_features, 10 );
            m_frame[i].Create( image.Width(), image.Height(), 8 );
            m_pyr[i].Create( image.Width(), image.Height(), 8 );
            m_temp[i].Create( image.Width(), image.Height(), 32 );
            {
                IplImage* tmp_img = m_temp[i].GetImage();
                tmp_img->depth = IPL_DEPTH_32F;
                tmp_img->nChannels = 1;
            }
        }
        m_status.SetSize( max_features, 10 );
        m_matrices.SetSize( max_features*2, 20 );

        img0 = m_frame[0].GetImage();
        img1 = m_frame[1].GetImage();

        m_frame[0].CopyOf( image, 0 );

        int count = max_features;
        cvGoodFeaturesToTrack( img0, m_temp[0].GetImage(), m_temp[1].GetImage(),
                               &m_features[0][0], &count, quality, min_distance );

        if( count > 0 )
        {
            cvFindCornerSubPix( img0, &m_features[0][0], count, 
                                cvSize(5,5), cvSize(-1,-1),
                                cvTermCriteria( CV_TERMCRIT_ITER, 10, 0.1f ));
            for( int i = 0; i < m_count; i++ )
            {
                m_status[i] = 1;
            }
            m_tracked = 0;
            m_idx = 0;
            m_count = count;
        }
    }
}


void CLkTracker::PushFrame( CImage& image )
{
    static int frame_idx = 0;
    
    IplImage* img = image.GetImage();

    if( m_count > 0 && img )
    {
        int I = m_idx, J = m_idx ^ 1;
        int pyr0_ready = m_tracked != 0;

        int i, k, count;

        assert( m_idx == 0 || m_idx == 1 );

        m_frame[I].Create( image.Width(), image.Height(), 8 );
        m_frame[J].Create( image.Width(), image.Height(), 8 );
        m_pyr[I].Create( image.Width(), image.Height(), 8 );
        m_pyr[J].Create( image.Width(), image.Height(), 8 );

        m_frame[J].CopyOf( image, 0 );

        IplImage* img0 = m_frame[I].GetImage();
        IplImage* img1 = m_frame[J].GetImage();
        IplImage* pyr0 = m_pyr[I].GetImage();
        IplImage* pyr1 = m_pyr[J].GetImage();

        cvCalcOpticalFlowPyrLK( img0, img1, pyr0, pyr1,
                                &m_features[I][0], &m_features[J][0],
                                m_count, cvSize(10,10), 3,
                                &m_status[0], 0, 
                                cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.03),
                                pyr0_ready ? CV_LKFLOW_PYR_A_READY : 0 );

        frame_idx++;

        /*cvCalcAffineFlowPyrLK( img0, img1, pyr0, pyr1,
                               &m_features[I][0], &m_features[J][0],
                               &(m_matrices[0].x),
                               m_count, cvSize(5,5), 3,
                               &m_status[0], 0, 
                               cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,5,0.3),
                               pyr0_ready ? CV_LKFLOW_PYR_A_READY : 0 );*/

        count = m_count;
        for( i = 0, k = 0; i < count; i++ )
        {
            if( m_status[i] )
            {
                m_features[J][k++] = m_features[J][i];
            }
            else
            {
                m_count--;
            }
        }

        m_tracked++;
        m_idx = J;
    }
    /*
    if( img.GetImage() )
    {
        cvGoodFeaturesToTrack( img.GetImage(), m_temp[0].GetImage(),
                               m_temp[1].GetImage(),
                               &m_features[0][0], &m_count, 0.1, 10 );
    }*/
}



void  CLkTracker::RemovePoint( int index )
{
    if( (unsigned)index < (unsigned)m_count )
    {
        m_features[m_idx].RemoveAt( index );
        m_features[m_idx^1].RemoveAt( index );
        m_matrices.RemoveAt( m_count*2 - 1 );
        m_matrices.RemoveAt( m_count*2 - 2 );
        m_count--;
    }
}


void  CLkTracker::AddPoint( CPoint p, CImage& image )
{
    CvPoint2D32f pt = AdjustPoint( p, image );
    
    if( m_count < m_features[m_idx].GetSize() )
    {
        m_features[m_idx][m_count] = pt;
    }
    else
    {
        m_features[m_idx].Add(pt);
        m_features[m_idx^1].Add(pt);
        m_matrices.Add(pt);
        m_matrices.Add(pt);
        m_status.Add(0);
    }
    m_count++;
}


void  CLkTracker::MovePoint( int index, CPoint p, CImage& image )
{
    if((unsigned)index < (unsigned)m_count )
    {
        CvPoint2D32f pt = AdjustPoint( p, image );
        m_features[m_idx][index] = pt;
    }
}


CvPoint2D32f  CLkTracker::AdjustPoint( CPoint p, CImage& image )
{
    CvPoint2D32f pt;
    pt.x = (float)p.x;
    pt.y = (float)p.y;
    cvFindCornerSubPix( image.GetImage(), &pt, 1, cvSize(5,5), cvSize(-1,-1),
                        cvTermCriteria( CV_TERMCRIT_ITER, 10, 0.1f ));
    return pt;
}

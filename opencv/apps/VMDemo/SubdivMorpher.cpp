#include "stdafx.h"
#include "SubdivMorpher.h"

typedef struct
{
    CV_SUBDIV2D_POINT_FIELDS()
    CvPoint2D32f* another;
}
StereoSubdivPoint;

CCvSubdivMorpher::CCvSubdivMorpher()
{
    m_subdiv = cvCreateSubdiv2D( 0, sizeof(*m_subdiv),
                                 sizeof(StereoSubdivPoint),
                                 sizeof(CvQuadEdge2D),
                                 cvCreateMemStorage(0));
    Clear();
    SetPointCount(100);

    m_win_size = cvSize(20,20);
    m_pyr_level = 3;
    m_criteria = cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,20,0.1);
}    


bool CCvSubdivMorpher::GeneratePoints()
{
#if 1
    int x, y;
    int count = m_count - 4;

    CvSize size = GetImageSize( m_left_gray_img );

    int ny = cvRound( cvSqrt( ((float)count)*size.height/size.width ));
    int nx = cvFloor( ((float)count)/MAX(ny,1) );

    float x_scale = ((float)size.width)/(nx + 1);
    float y_scale = ((float)size.height)/(ny + 1);

    if( nx < 2 || ny < 2 ) return false;

    m_realcount = nx*ny;

    for( y = 0; y < ny; y++ )
    {
        for( x = 0; x < nx; x++ )
        {
            m_left_points[y*nx + x] =
                cvPoint2D32f( (x + 0.5f)*x_scale, (y + 0.5f)*y_scale );
        }
    }

#else
    m_realcount = m_count;

    cvGoodFeaturesToTrack( m_left_gray_img, m_left_pyr, m_right_pyr, m_left_points,
                           &m_realcount, 0.01, 5 );
#endif

    cvFindCornerSubPix( m_left_gray_img, m_left_points, m_realcount,
                        m_win_size, cvSize(-1,-1), m_criteria );
    return true;


}

bool CCvSubdivMorpher::OnCalculateStereo()
{
    CvSize size = GetImageSize( m_left_img );
    int i, k;
    bool result = false;
    char* status = new char[m_count];
    
    m_left_gray_img = CreateIsometricImage( m_left_img, m_left_gray_img,
                                            m_left_img->depth, 1 );
    m_right_gray_img = CreateIsometricImage( m_right_img, m_right_gray_img,
                                             m_right_img->depth, 1 );

    m_left_pyr = CreateIsometricImage( m_left_img, m_left_pyr,
                                       IPL_DEPTH_32F, 1 );
    m_right_pyr = CreateIsometricImage( m_right_img, m_right_pyr,
                                        IPL_DEPTH_32F, 1 );

    cvCvtColor( m_left_img, m_left_gray_img, CV_BGR2GRAY );
    cvCvtColor( m_right_img, m_right_gray_img, CV_BGR2GRAY );

    m_left_gray_img->roi->width &= -(1 << m_pyr_level);
    m_left_gray_img->roi->height &= -(1 << m_pyr_level);
    m_right_gray_img->roi = m_left_gray_img->roi;

    result = GeneratePoints();
    if( !result ) return result;

    cvCalcOpticalFlowPyrLK( m_left_gray_img, m_right_gray_img,
                            m_left_pyr, m_right_pyr, m_left_points, m_right_points,
                            m_realcount, m_win_size, m_pyr_level, status, 0,
                            m_criteria,0);

    m_right_gray_img->roi = m_left_gray_img->roi = m_left_img->roi;

    for( i = 0, k = 0; i < m_realcount; i++ )
    {
        if( status[i] &&
            m_left_points[i].x > 1 && m_left_points[i].x < size.width - 2 &&
            m_left_points[i].y > 1 && m_left_points[i].y < size.height - 2  &&
            m_right_points[i].x > 1 && m_right_points[i].x < size.width - 2 &&
            m_right_points[i].y > 1 && m_right_points[i].y < size.height - 2 )
        {
            if( k < i )
            {
                m_left_points[k] = m_left_points[i];
                m_right_points[k] = m_right_points[i];
            }
            k++;
        }
    }

    delete status;

    m_realcount = k + 4;

    m_right_points[k]   = m_left_points[k] = cvPoint2D32f( 1.f, 1.f );
    m_right_points[k+1] = m_left_points[k+1] = cvPoint2D32f( size.width - 2.f, 1.f );
    m_right_points[k+2] = m_left_points[k+2] = cvPoint2D32f( size.width - 2.f, size.height - 2.f );
    m_right_points[k+3] = m_left_points[k+3] = cvPoint2D32f( 1.f, size.height - 2.f );

    cvInitSubdivDelaunay2D( m_subdiv, cvRect(0,0,size.width,size.height));

    for( i = 0; i < m_realcount; i++ )
    {
        if( i == 77 )
        {
            printf("%d",i);
        }
        StereoSubdivPoint* point = (StereoSubdivPoint*)
            cvSubdivDelaunay2DInsert( m_subdiv, m_left_points[i] );
        point->another = m_right_points + i;
    }

    return result;
}


bool CCvSubdivMorpher::OnCalculateVirtualImage()
{
    CvSeqReader reader;
    int i, total = m_subdiv->edges->total;

    cvZero( m_virtual_img );

    cvStartReadSeq( (CvSeq*)(m_subdiv->edges), &reader, 0 );

    for( i = 0; i < total; i++ )
    {
        CvQuadEdge2D* quadedge = (CvQuadEdge2D*)reader.ptr;
        CvSubdiv2DEdge edge = (CvSubdiv2DEdge)quadedge;

        if( CV_IS_SET_ELEM_EXISTS( quadedge ))
        {
            if( !quadedge->pt[3] ) // left facet was not considered
            {
                MorphFacet( edge );            
            }

            if( !quadedge->pt[1] ) // right facet was not considered
            {
                MorphFacet( cvSubdiv2DSymEdge(edge));
            }
        }

        CV_NEXT_SEQ_ELEM( sizeof(*quadedge), reader );
    }

    cvSetSeqReaderPos( 0, 0, &reader );

    // clear "facet visited" flags
    for( i = 0; i < total; i++ )
    {
        CvQuadEdge2D* quadedge = (CvQuadEdge2D*)reader.ptr;
        quadedge->pt[1] = quadedge->pt[3] = 0;
        CV_NEXT_SEQ_ELEM( sizeof(*quadedge), reader );
    }
    //iplCopy( m_left_img, m_virtual_img );

    cvDeleteMoire( m_virtual_img );

    return true;
}


void CCvSubdivMorpher::MorphFacet( CvSubdiv2DEdge edge )
{
#define SHIFT      10
#define DELTA      (1 << (SHIFT - 1))
#define ASHIFT     8
#define ADELTA     (1 << (ASHIFT - 1))

    CvPoint2D32f left_points[3];
    CvPoint2D32f right_points[3];
    CvPoint2D32f middle_points[3];
    CvPoint left_c, right_c, middle_c;

    CvSize size;
    int left_step = 0, right_step = 0, middle_step = 0;
    uchar* left_data = 0;
    uchar* right_data = 0;
    uchar* middle_data = 0;
    int min_len, max_len;
    int i, j, v;
    CvPoint2D32f left_pt_step, right_pt_step, middle_pt_step;
    float t;
    int alpha = cvRound(m_pan*(1 << ASHIFT));
    int flag = 0;

    cvGetImageRawData( m_left_img, &left_data, &left_step, &size );
    cvGetImageRawData( m_right_img, &right_data, &right_step, 0 );
    cvGetImageRawData( m_virtual_img, &middle_data, &middle_step, 0 );

    for( i = 0; i < 3; i++ )
    {
        StereoSubdivPoint* subdiv_pt = (StereoSubdivPoint*)cvSubdiv2DEdgeOrg( edge );
        
        left_points[i] = subdiv_pt->pt;
        right_points[i] = subdiv_pt->another ? *subdiv_pt->another : left_points[i];
        
        ((CvQuadEdge2D*)(edge & ~3))->pt[(edge + 3) & 3] = (CvSubdiv2DPoint*)1;
        edge = cvSubdiv2DGetEdge( edge, CV_NEXT_AROUND_LEFT );

        middle_points[i].x = left_points[i].x + m_pan*(right_points[i].x - left_points[i].x);
        middle_points[i].y = left_points[i].y + m_pan*(right_points[i].y - left_points[i].y);

        flag |= (unsigned)left_points[i].x >= (unsigned)size.width ||
                (unsigned)left_points[i].y >= (unsigned)size.height;
    }

    if( flag ) return;

    // calculate min and max side length in the middle triangle
    v = cvRound(fabs(middle_points[0].x - middle_points[1].x) + 
                fabs(middle_points[0].y - middle_points[1].y));

    min_len = max_len = v;
    i = 0;

    v = cvRound(fabs(middle_points[1].x - middle_points[2].x) + 
                fabs(middle_points[1].y - middle_points[2].y));

    if( v < min_len ) min_len = v, i = 1;
    if( v > max_len ) max_len = v;

    v = cvRound(fabs(middle_points[0].x - middle_points[2].x) + 
                fabs(middle_points[0].y - middle_points[2].y));

    if( v < min_len ) min_len = v, i = 2;
    if( v > max_len ) max_len = v;

    if( i != 0 )
    {
        CvPoint2D32f t;
        CV_SWAP( left_points[2], left_points[i-1], t );
        CV_SWAP( right_points[2], right_points[i-1], t );
        CV_SWAP( middle_points[2], middle_points[i-1], t );
    }

    left_c = cvPoint( cvRound(left_points[2].x*(1 << SHIFT)),
                      cvRound(left_points[2].y*(1 << SHIFT)));
    right_c = cvPoint( cvRound(right_points[2].x*(1 << SHIFT)),
                       cvRound(right_points[2].y*(1 << SHIFT)));
    middle_c = cvPoint( cvRound(middle_points[2].x*(1 << SHIFT)),
                        cvRound(middle_points[2].y*(1 << SHIFT)));

    t = 1.f/min_len;

    left_pt_step = cvPoint2D32f( (left_points[1].x - left_points[0].x)*t,
                                 (left_points[1].y - left_points[0].y)*t );

    right_pt_step = cvPoint2D32f( (right_points[1].x - right_points[0].x)*t,
                                  (right_points[1].y - right_points[0].y)*t );

    middle_pt_step = cvPoint2D32f( (middle_points[1].x - middle_points[0].x)*t,
                                   (middle_points[1].y - middle_points[0].y)*t );

    t = 1.f/max_len;

    for( i = 0; i < min_len; i++ )
    {
        CvPoint left_pt = cvPoint( cvRound(left_points[0].x*(1 << SHIFT)) + DELTA,
                                   cvRound(left_points[0].y*(1 << SHIFT)) + DELTA),
                right_pt = cvPoint( cvRound(right_points[0].x*(1 << SHIFT)) + DELTA,
                                    cvRound(right_points[0].y*(1 << SHIFT)) + DELTA),
                middle_pt = cvPoint( cvRound(middle_points[0].x*(1 << SHIFT)) + DELTA,
                                     cvRound(middle_points[0].y*(1 << SHIFT)) + DELTA);

        CvPoint left_pt_step2 = cvPoint( cvRound((left_c.x - left_pt.x)*t),
                                         cvRound((left_c.y - left_pt.y)*t)),
                right_pt_step2 = cvPoint( cvRound((right_c.x - right_pt.x)*t),
                                          cvRound((right_c.y - right_pt.y)*t)),
                middle_pt_step2 = cvPoint( cvRound((middle_c.x - middle_pt.x)*t),
                                           cvRound((middle_c.y - middle_pt.y)*t));

        for( j = 0; j < max_len; j++ )
        {
            uchar* left_ptr = left_data + (left_pt.y >> SHIFT)*left_step
                              + (left_pt.x >> SHIFT)*3;
            uchar* right_ptr = right_data + (right_pt.y >> SHIFT)*right_step
                               + (right_pt.x >> SHIFT)*3;
            uchar* middle_ptr = middle_data + (middle_pt.y >> SHIFT)*middle_step
                                + (middle_pt.x >> SHIFT)*3;
            
            int t0, t1, t2;

            t0 = ((left_ptr[0] << ASHIFT) + alpha*(right_ptr[0] - left_ptr[0]) + ADELTA) >> ASHIFT;
            t1 = ((left_ptr[1] << ASHIFT) + alpha*(right_ptr[1] - left_ptr[1]) + ADELTA) >> ASHIFT;
            t2 = ((left_ptr[2] << ASHIFT) + alpha*(right_ptr[2] - left_ptr[2]) + ADELTA) >> ASHIFT;

            middle_ptr[0] = (uchar)t0;
            middle_ptr[1] = (uchar)t1;
            middle_ptr[2] = (uchar)t2;

            left_pt.x += left_pt_step2.x;
            left_pt.y += left_pt_step2.y;
            right_pt.x += right_pt_step2.x;
            right_pt.y += right_pt_step2.y;
            middle_pt.x += middle_pt_step2.x;
            middle_pt.y += middle_pt_step2.y;
        }

        left_points[0].x += left_pt_step.x;
        left_points[0].y += left_pt_step.y;

        right_points[0].x += right_pt_step.x;
        right_points[0].y += right_pt_step.y;

        middle_points[0].x += middle_pt_step.x;
        middle_points[0].y += middle_pt_step.y;
    }
}

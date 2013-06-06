#pragma once

#include "CV.hpp"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

inline CvSize GetImageSize( IplImage* img )
{
    CvSize size = { 0, 0 };
    if( img ) cvGetImageRawData( img, 0, 0, &size );
    return size;
}


inline IplImage* CreateIsometricImage( IplImage* src, IplImage* dst,
                                       int desired_depth, int desired_num_channels )
{
    CvSize src_size = GetImageSize( src ),
           dst_size = src_size;

    if( dst ) dst_size = GetImageSize( dst );

    if( !dst || dst->depth != desired_depth ||
        dst->nChannels != desired_num_channels ||
        dst_size.width != src_size.width ||
        dst_size.height != dst_size.height )
    {
        cvReleaseImage( &dst );
        dst = cvCreateImage( src_size, desired_depth, desired_num_channels );
    }

    return dst;
}

// Basic class for ViewMorphing
class CCvMorpher
{
protected:

    IplImage* m_left_img;
    IplImage* m_right_img;
    IplImage* m_virtual_img;
    IplImage* m_disparity_img;

    float     m_pan;
    bool      m_isVirtualImageReady;
    bool      m_isStereoReady;
    bool      m_isDisparityReady;

    void  Clear()
    {
        m_left_img = m_right_img = m_virtual_img = m_disparity_img = 0;
        m_pan = 0.5f;
        m_isVirtualImageReady = m_isStereoReady =
            m_isDisparityReady = false;
    }

    virtual void  ResetStereo()
    {
        m_isVirtualImageReady = m_isStereoReady =
            m_isDisparityReady = false;
    }

    virtual void  Release()
    {
        cvReleaseImage( &m_left_img );
        cvReleaseImage( &m_right_img );
        cvReleaseImage( &m_virtual_img );
        cvReleaseImage( &m_disparity_img );
        Clear();
    }

    virtual bool  OnCalculateStereo()
    {
        return false;
    }

    virtual bool  OnCalculateVirtualImage()
    {
        return false;
    }

    virtual bool  CalculateStereo()
    {
        CvSize left_size = GetImageSize(m_left_img),
               right_size = GetImageSize(m_right_img);
        
        if( !m_left_img || !m_right_img ||
            m_left_img->depth != m_right_img->depth ||
            m_left_img->depth != IPL_DEPTH_8U ||
            m_left_img->nChannels != m_right_img->nChannels ||
            m_left_img->nChannels != 3 ||
            left_size.width != right_size.width ||
            left_size.height != right_size.height ) return false;

        return OnCalculateStereo();
    }

    virtual bool  CalculateVirtualImage()
    {
        m_virtual_img = CreateIsometricImage( m_left_img,
                                              m_virtual_img,
                                              m_left_img -> depth,
                                              m_left_img -> nChannels
                                            );
        return OnCalculateVirtualImage();
    }

    virtual bool OnCalculateDisparity()
    {
        return false;
    }

    virtual bool CalculateDisparity()
    {
        if( !m_isStereoReady )
        {
            m_isStereoReady = CalculateStereo();
        }
        m_isDisparityReady = m_isStereoReady && OnCalculateDisparity();

        return m_isDisparityReady;
    }

    virtual bool OnCalculateDisparityImage()
    {
        return false;
    }
    
    virtual bool CalculateDisparityImage()
    {
        m_disparity_img = CreateIsometricImage( m_left_img,
                                                m_disparity_img,
                                                m_left_img -> depth,
                                                m_left_img -> nChannels
                                              );
        if( !m_isDisparityReady ) {
            m_isDisparityReady = CalculateDisparity();
        }
        OnCalculateDisparityImage();

        return true;
    }

    virtual void  SetImage( IplImage* src, IplImage*& dst,
                            bool substitute_pointer = false )
    {
        if( dst != src )
        {
            if( substitute_pointer )
            {
                cvReleaseImage( &dst );
                dst = src;
            }
            else
            {
                dst = CreateIsometricImage( src, dst, src->depth, src->nChannels );
                cvCopy( src, dst );
            }
        }
        ResetStereo();
    }

public:

    CCvMorpher()
    {
        Clear();
    }

    virtual ~CCvMorpher()
    {
        Release();
    }

    virtual void SetLeftImage( IplImage* img, bool substitute_pointer = false )
    {
        SetImage( img, m_left_img, substitute_pointer );
    }

    virtual void SetRightImage( IplImage* img, bool substitute_pointer = false )
    {
        SetImage( img, m_right_img, substitute_pointer );
    }

    virtual IplImage* GetLeftImage() { return m_left_img; }
    virtual IplImage* GetRightImage() { return m_right_img; }

    virtual IplImage* GetVirtualImage()
    {
        if( !m_isVirtualImageReady )
        {
            if( !m_isStereoReady )
            {
                m_isStereoReady = CalculateStereo();
            }
            m_isVirtualImageReady = m_isStereoReady && CalculateVirtualImage();
        }
        return m_virtual_img;
    }

    virtual IplImage* GetDisparityImage()
    {
        if( !m_isStereoReady ) {
            m_isStereoReady = CalculateStereo();
        }
        CalculateDisparityImage();

        return m_disparity_img;
    }

    virtual void SetPan( float pan )
    {
        assert( 0.f <= pan && pan <= 1.f );
        m_pan = pan;
        
        m_isVirtualImageReady = false;
    }

    float GetPan() { return m_pan; };
};


// Subdivision + LK - based viewmorphing
class CCvSubdivMorpher : public CCvMorpher
{
protected:

    int  m_count;
    int  m_realcount;
    int  m_maxcount;
    CvSubdiv2D* m_subdiv;
    CvPoint2D32f* m_left_points;
    CvPoint2D32f* m_right_points;
    IplImage* m_left_gray_img;
    IplImage* m_right_gray_img;
    IplImage* m_left_pyr;
    IplImage* m_right_pyr;
    CvSize m_win_size;
    int  m_pyr_level;
    CvTermCriteria m_criteria;

    void ClearPoints()
    {
        m_left_points = m_right_points = 0;
        m_count = m_maxcount = 0;
    }

    virtual void ReleasePoints()
    {
        cvClearGraph( (CvGraph*)m_subdiv );
        delete m_left_points;
        delete m_right_points;
        ClearPoints();
    }

    void Clear()
    {
        CCvMorpher::Clear();
        ClearPoints();
        m_left_gray_img = m_right_gray_img = 0;
        m_left_pyr = m_right_pyr = 0;
        m_realcount = 0;
    }

    virtual void Release()
    {
        CCvMorpher::Release();
        ReleasePoints();
        cvReleaseImage( &m_left_gray_img );
        cvReleaseImage( &m_right_gray_img );
        cvReleaseImage( &m_left_pyr );
        cvReleaseImage( &m_right_pyr );
        Clear();
    }

    virtual bool  OnCalculateStereo();
    virtual bool  OnCalculateVirtualImage();
    virtual bool  GeneratePoints();
    virtual void  MorphFacet( CvSubdiv2DEdge edge );

public:

    CCvSubdivMorpher();

    int GetPointCount() { return m_count; }
    void SetPointCount( int count )
    {
        if( count > m_maxcount )
        {
            ReleasePoints();
            m_left_points = new CvPoint2D32f[count];
            m_right_points = new CvPoint2D32f[count];
            m_maxcount = count;
        }
        m_count = count;
        ResetStereo();
    }
};

// Pixel to pixel morphing
class CCvPixelToPixelMorpher : public CCvMorpher
{
protected:
    int     m_maxPixelDifference;
    int*    m_corr;
    int*    m_corrNum;

protected:
    struct _Color
    {
        unsigned char red;
        unsigned char green;
        unsigned char blue;
    };
    
    typedef enum {
        CORR_ARRAY      = 0,
        NUM_CORR_ARRAY  = 1,
        CORR_EDGES      = 2,
        CORR_TEMP       = 3
    } corrArrayType;
    
    typedef enum {
        morphNormalImage    = 0,
        morphDepthMap       = 1
    } morphImageType;

protected:
    int* corrAlloc( int width, int height, corrArrayType type, int maxPixelDifference = 0 );
    void FindFullCorr( unsigned char* _leftImage,
                       int _leftLineStep,
                       unsigned char* _rightImage,
                       int _rightLineStep,
                       int* _corrArray,
                       int* _numCorrArray,
                       int width,
                       int height,
                       int maxPixelDifference
                     );
    void FindCorr( unsigned char* _leftLine,
                   unsigned char* _rightLine,
                   int* _corrArray,
                   int* numCorrArray,
                   int width,
                   int* edges,
                   int* tempArray
                 );
    
    void Morph( unsigned char* _leftImage,
                int _leftLineStep,
                unsigned char* _rightImage,
                int _rightLineStep,
                unsigned char* _resultImage,
                int _resultLineStep,
                int* _corrArray,
                int* _numCorrArray,
                int width,
                int height,
                float alpha,
                morphImageType imageNeed    = morphNormalImage,
                int maxDifference           = 0
              );
    
    int distance( unsigned char* _leftLine,
                  unsigned char* _rightLine,
                  int lineSize,
                  int x,
                  int y
                );

    void Clear()
    {
        CCvMorpher::Clear();
        m_maxPixelDifference = 10;
        m_corr = m_corrNum = 0;
    }

    virtual void Release()
    {
        CCvMorpher::Release();
        if( m_corr ) {
            free( m_corr );
        }
        if( m_corrNum ) {
            free( m_corrNum );
        }
        Clear();
    }

    virtual bool  OnCalculateStereo();
    virtual bool  OnCalculateVirtualImage();
    virtual bool  OnCalculateDisparity();
    virtual bool  OnCalculateDisparityImage();

public:

    CCvPixelToPixelMorpher();
};

/* End of file. */

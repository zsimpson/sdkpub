// CamAvi.h: interface for the CCamAvi class 
//
//////////////////////////////////////////////////////////////////////

#ifndef __CAMAVI__
#define __CAMAVI__


#include "image.h"
#include <ipl.h>
#include <vfw.h>

class CCamAvi  
{
protected:
    CImage m_frame;
	bool m_init;
	PAVIFILE m_paf;
	PAVISTREAM m_pas;
	HIC m_hic;
	BYTE *m_data;
	long m_length;
public:
	BITMAPINFO m_bi, m_bi_out;
	long m_pos;
    double m_FrameRate;

    CImage& GetFrame();
    CCamAvi();
    ~CCamAvi();

    bool  IsInitialized() { return m_init;};

    bool  Initialize(char* filename);
    void  Uninitialize();
};

#endif 

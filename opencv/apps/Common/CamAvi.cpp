#include "CamAvi.h"

bool CCamAvi::Initialize (char* filename)
{
	long hr;
	AVISTREAMINFO info;
	
	m_init=false;
	m_pos=0;
	
	AVIFileInit ();
	
	hr=AVIFileOpen (&m_paf, filename, OF_READ, NULL);
	if (hr!=0) return false;

	hr=AVIFileGetStream (m_paf, &m_pas, streamtypeVIDEO, 0);
	if (hr!=0) return false;

	hr= AVIStreamInfo (m_pas, &info, sizeof (info));	
	if (hr!=0) return false;

	hr=sizeof (m_bi);
	hr= AVIStreamReadFormat (m_pas, 0, &m_bi, &hr);
	if (hr!=0) return false;	
	
	if (m_bi.bmiHeader.biCompression!=0)
	{
		// find decompressor
		m_hic=ICOpen (ICTYPE_VIDEO, info.fccHandler ,ICMODE_DECOMPRESS);
		if (m_hic==0) return false;
	}
 	m_data=new unsigned char[m_bi.bmiHeader.biSizeImage];
	AVISTREAMINFO a;
	AVIStreamInfo (m_pas, &a, sizeof (a));
	m_length=a.dwLength;
	hr=AVIStreamBeginStreaming (m_pas, 0, 100, 1000);	
	m_init=true;

    m_FrameRate = (double)a.dwRate / a.dwScale;
	
	m_pos=AVIStreamStart (m_pas);
	m_data=new BYTE[m_bi.bmiHeader.biSizeImage];
	if (m_bi.bmiHeader.biCompression!=0) 
	{
		hr=ICDecompressGetFormat (m_hic, &m_bi, &m_bi_out);
	}
	else m_bi_out=m_bi;
	m_frame.Create (m_bi_out.bmiHeader.biWidth, m_bi_out.bmiHeader.biHeight, m_bi_out.bmiHeader.biBitCount);
	return true;
}

void CCamAvi::Uninitialize ()
{
	AVIFileRelease (m_paf);
	delete m_data;
	return;
}

CCamAvi::CCamAvi()
{
    m_FrameRate = 25;
}

CCamAvi::~CCamAvi ()
{
//	if (m_data) delete m_data;
}

CImage& CCamAvi::GetFrame ()
{
	m_frame.Create (m_bi_out.bmiHeader.biWidth, m_bi_out.bmiHeader.biHeight, m_bi_out.bmiHeader.biBitCount);

	HANDLE h = 0;
	IplImage* img=m_frame.GetImage();
	BITMAPINFOHEADER *b;
	long written, s_written;
	long err=AVIStreamRead (m_pas, m_pos, 1, m_data, m_bi.bmiHeader.biSizeImage, &written, &s_written);
	m_pos=(m_pos+1)%m_length;
	if (m_bi.bmiHeader.biCompression!=0) 
	{
		// decompress data
		h=ICImageDecompress (m_hic, 0, &m_bi, m_data, &m_bi_out);
        if( h )
        {
		    b=(BITMAPINFOHEADER*)GlobalLock(h);
		    iplConvertFromDIB (b, img);	
		    GlobalUnlock(h);
            GlobalFree(h);
        }
	}
	else
	{
		
		iplConvertFromDIBSep (&m_bi.bmiHeader, (const char*) m_data, img);	
	}
	
	return m_frame;
}

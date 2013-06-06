#include "splitwin.h"

/**************************************************
*
*	Purpose: Alter the Display Data
*
**************************************************/
int Window::CreateDeviceIndependentBitmap(HWND hwnd)
{
	HDC    hDC;	
	long k,j;
	LPBITMAPINFO info;
	unsigned char *dat;
	int W = ImageWidth;
	int H = ImageHeight;

    /* Handle 4-Byte Boundary For BitBlt */
    while ( W%4 != 0 )
      W++;
    
	hDC = GetDC (hwnd) ;		                  
    
	// Intialize BITMAPINFOHEADER data.
    //.................................
    bi.biSize			= sizeof (BITMAPINFOHEADER) ;
    bi.biWidth			= W;     
    bi.biHeight			= H;
    bi.biPlanes			= 1;
    bi.biBitCount		= COLORBITS;
    bi.biCompression	= BI_RGB;
    bi.biSizeImage		= ( ALIGNLONG( (W * COLORBITS)/8 ) * H);
    bi.biXPelsPerMeter	= 0;
    bi.biYPelsPerMeter	= 0;
    bi.biClrUsed		= 256;
    bi.biClrImportant	= 256;
    
	// Allocate memory for BITMAPINFO structure.
    //..........................................
    lpbi = (BITMAPINFOHEADER*)GlobalAlloc( GPTR, 
                                           sizeof(BITMAPINFOHEADER) +
                                           256 * sizeof (RGBQUAD) + 
                                           (ALIGNLONG((W * COLORBITS)/8)
                                           * H) );
                  
    // Copy BITMAPINFOHEADER information.
    //...................................
    *lpbi = bi;
				  
	// Create The Palette
	info = (LPBITMAPINFO) lpbi;	
	CreatePalette( info );
	
    // Set pointer to bitmap’s bit data.
    //..................................
    lpstBitmap = (LPSTR)lpbi + (WORD)sizeof(BITMAPINFOHEADER) +
					   (256 * sizeof(RGBQUAD));
					
	dat = (unsigned char*)lpstBitmap;
		  
	for ( k=0; k< H; k++ )
		for ( j = 0; j < W; j++ )
		    *dat++ = (unsigned char)k;
				
	hBitmap = CreateDIBitmap( hDC, 
							  &bi, 
							  0, 
							  lpstBitmap, 
                              (LPBITMAPINFO) lpbi, 
							  DIB_RGB_COLORS);

				
    ReleaseDC( hwnd, hDC);

	return ( TRUE );
}


/**************************************************
*
*	Purpose:Set DIB Palette Up
**************************************************/
Window::CreatePalette( LPBITMAPINFO info)
{
	int i;

		for ( i=0; i<256; i++ )
		{
			info->bmiColors[i].rgbRed   = i;
			info->bmiColors[i].rgbBlue  = i;
			info->bmiColors[i].rgbGreen = i;
			info->bmiColors[i].rgbReserved = 0;					
		}
	

	
	return (TRUE);
}


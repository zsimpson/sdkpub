#include "splitwin.h"
#define PIXCM 1
#include "platform.h"
extern "C"
{
#include "pigenfcn.h"
}

/**************************************************
*
*	Purpose: Update the window
*
**************************************************/
Window::OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
    HDC         hMemDC;
	int			scan;
	DWORD		lasterror;
	
	if ( hBitmap == NULL )
		CreateDeviceIndependentBitmap(hwnd);

    BeginPaint( hwnd, &ps );
    hMemDC = CreateCompatibleDC( ps.hdc );

	scan =  SetDIBits(
		    hMemDC,						// handle of device context 
			hBitmap,					// handle of bitmap 
			0,							// starting scan line 
			ImageHeight,				// number of scan lines 
			lpstBitmap,					// array of bitmap bits 
			(LPBITMAPINFO) lpbi,		// address of structure with bitmap data 
			DIB_RGB_COLORS );			// type of color indices to use 
				

	if ( !scan )
		lasterror = GetLastError();

    SelectObject( hMemDC, hBitmap );

	
	scan = StretchBlt(	ps.hdc,	// handle of destination device context 
							0,	// x-coordinate of upper-left corner of dest. rect. 
							0,	// y-coordinate of upper-left corner of dest. rect. 
							ClientWidth,	// width of destination rectangle 
							ClientHeight,	// height of destination rectangle 
							hMemDC,	// handle of source device context 
							0,	// x-coordinate of upper-left corner of source rectangle 
							0,	// y-coordinate of upper-left corner of source rectangle 
							ImageWidth,	// width of source rectangle 
							ImageHeight,	// height of source rectangle 
							SRCCOPY	 ); 



    DeleteDC( hMemDC );
    EndPaint( hwnd, &ps );
				 
	return (TRUE);
}

/**************************************************
*
*	Purpose: Alter the Display Data
*
**************************************************/
Window::UpdateDeviceIndependentBitmap(unsigned short *data )
{
	// Alter The Bits via the pointer
	int i,j;	
	unsigned short *head = data;
	unsigned char *dbits = (unsigned char*)lpstBitmap;
    int x,y;
    int temp;

    /* Get Overrall Buffer Width And Height */
    x = PICM_Get_pixeldimension_x();
    y = PICM_Get_pixeldimension_y();

    /* NX1,NX2,NY1,NY2 are the postions of the region */
    /* inside the buffer size x by y at address data  */

    /* Go To First Point in our region */
    data += (NY1-1)*x + NX1;
    
    /* Find Region Height and Width */
    ImageHeight = NY2 - NY1 + 1;
    ImageWidth  = NX2 - NX1 + 1;

	for (i=0; i<ImageHeight; i++)
	{
        temp = ImageWidth;
       
		for ( j=0;j<ImageWidth;j++)
		{		
			*dbits = (unsigned char)((float) *data / 16.0);				
			dbits++;
			data++;
		}	
     
        /* Handle 4-Byte Boundary For BitBlt */
        while ( temp%4 != 0 )
        {
            dbits++;
            temp++;
        }
        data += x - (NX2 - NX1 + 1);
	}

	// force repaint
	InvalidateRect( handle, NULL, FALSE );

	return (TRUE);
}
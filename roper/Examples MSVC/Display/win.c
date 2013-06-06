/* Window.C */
#include "windows.h"
#include "wingdi.h"
#include "win.h"

#define ALIGNLONG(i) ((i+3)/4*4)
#define COLORBITS 8


void Draw_Strip( HWND hWnd );
HBRUSH ghbrWhite, ghbrBlack;
void Create_DIB( HWND wnd );
void Draw_DIB( HWND wnd );

/*
 * Some handy globals.
 */
int W, H;
static HBITMAP            hBitmap;
static LPBITMAPINFOHEADER lpbi;
static BITMAPINFOHEADER   bi;
char  *lpstBitmap;
HPALETTE palette;


/**************************************************
*
*	Register this type of window...
*
*
**************************************************/
BOOL RegisterWindow(char *lpClass, HANDLE instance)
{
	WNDCLASS wc;
   
    ghbrWhite = CreateSolidBrush(0x00FFFFFF);
    ghbrBlack = CreateSolidBrush(0x00000000);

    wc.style            = CS_OWNDC;
    wc.lpfnWndProc      = (WNDPROC) ImageWndProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = sizeof(LONG);
    wc.hInstance        = instance;
    wc.hIcon            = LoadIcon(NULL,IDC_ARROW);
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground    = ghbrWhite;
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = lpClass;

    if (!RegisterClass(&wc))
        return FALSE;

	else 
		return TRUE;

}

/**************************************************
*
*	Create and show the window....
*
*
**************************************************/
HWND CreateWin(		  int x, 
					  int y, 
					  int width, 
					  int height, 
					  char *lpClass, 
					  char *name,
					  HANDLE instance)
{
	HWND handle;
	W = width;
	H = height;
	handle = CreateWindow(
					lpClass,										// pointer to registered class name
				    name,											// pointer to window name
					WS_VISIBLE | WS_OVERLAPPEDWINDOW, //| WS_VSCROLL | WS_HSCROLL,	// window style
				    x,												// horizontal position of window
				    y+20,												// vertical position of window
					width,											// window width
					height,											// window height
					NULL,											// handle to parent or owner window
					NULL,											// handle to menu or child-window identifier
					instance,										// handle to application instance
					NULL 											// pointer to window-creation data
				);

	return (handle);

}

/**************************************************
*
*	Handles the messages for this window
*
*
**************************************************/
int WINAPI ImageWndProc(
    HWND hwnd,
    UINT message,
    DWORD wParam,
    LONG lParam)
{
    switch (message) 
	{
		case WM_PAINT:
			
			Draw_DIB( hwnd );
			
			return 0L;
		break;
        case WM_SIZE:
				return DefMDIChildProc(hwnd, message, wParam, lParam);
		break;
        case WM_CREATE:		
			Create_DIB( hwnd );
		break;
        case WM_CLOSE:
				return DefMDIChildProc(hwnd, message, wParam, lParam);
		break;
        case WM_DESTROY:
				return DefMDIChildProc(hwnd, message, wParam, lParam);
		break;
        default:
                return DefMDIChildProc(hwnd, message, wParam, lParam);
		break;
    }

}

/**************************************************
*
*	Create a Device Independent Bitmap...
*
*
**************************************************/
void Create_DIB( HWND hWnd )
{
   
       HDC    hDC;	
	   unsigned char i;
	   long k,j;
	   LPBITMAPINFO info;
	   unsigned char *dat;
	   
	   hDC = GetDC (hWnd) ;		                  
       // Intialize BITMAPINFOHEADER data.
       //.................................
                  bi.biSize			 = sizeof (BITMAPINFOHEADER) ;
                  bi.biWidth		 = W;     
                  bi.biHeight		 = H;
                  bi.biPlanes		 = 1;
                  bi.biBitCount		 = COLORBITS;
                  bi.biCompression	 = BI_RGB;
                  bi.biSizeImage	 = ( ALIGNLONG( (W * COLORBITS)/8 ) * H);
                  bi.biXPelsPerMeter = 0;
                  bi.biYPelsPerMeter = 0;
                  bi.biClrUsed       = 256;
                  bi.biClrImportant  = 256;

                  

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


		for ( i=0; i<255; i++ )
		{
			info->bmiColors[i].rgbRed   = i;
			info->bmiColors[i].rgbBlue  = i;
			info->bmiColors[i].rgbGreen = i;
			info->bmiColors[i].rgbReserved = 0;	
		}
	                                		                  
          // Set pointer to bitmap’s bit data.
          //..................................
          lpstBitmap = (LPSTR)lpbi + (WORD)sizeof(BITMAPINFOHEADER) +
					   (256 * sizeof(RGBQUAD));
					
		  dat = lpstBitmap;
		  
		  for ( k=0; k< H; k++ )
			  for ( j = 0; j < W; j++ )
			    *dat++ = k;

		  // Create uninitialized DIB bitmap.
          //.................................
          hBitmap = CreateDIBitmap( hDC, 
									&bi, 
									0, 
									lpstBitmap, 
                                    (LPBITMAPINFO) lpbi, 
									DIB_RGB_COLORS);

				
          ReleaseDC( hWnd, hDC);

               
}



/**************************************************
*
*		Force repaint and update the display...
*
*
**************************************************/
void Draw_DIB( HWND hWnd )
{
    PAINTSTRUCT ps;
    HDC         hMemDC;
	int scan;
	DWORD lasterror;
					
    BeginPaint( hWnd, &ps );
    hMemDC = CreateCompatibleDC( ps.hdc );

	SelectPalette(hMemDC, palette, TRUE);
	RealizePalette(hMemDC);
	SelectPalette(ps.hdc, palette, TRUE);
	RealizePalette(ps.hdc);

	scan =  SetDIBits(
			hMemDC,						// handle of device context 
			hBitmap,					// handle of bitmap 
			0,							// starting scan line 
			H,							// number of scan lines 
			lpstBitmap,					// array of bitmap bits 
			(LPBITMAPINFO) lpbi,		// address of structure with bitmap data 
			DIB_RGB_COLORS );			// type of color indices to use 
				

	if ( !scan )
		lasterror = GetLastError();
    SelectObject( hMemDC, hBitmap );
				 
    BitBlt( ps.hdc, 0, 0, W, H, 
            hMemDC, 0, 0, SRCCOPY );
    DeleteDC( hMemDC );
    EndPaint( hWnd, &ps );
				 
}


/**************************************************
*
*	Set the bits to the bitmap to be displayed...
*
*
**************************************************/
void Update_Bitmap( HWND hwnd, unsigned short *data, int AutoStop )
{	
	// Alter The Bits via the pointer
	int i,j;	
	unsigned char *dbits = lpstBitmap;
	unsigned short *head;
	float mp;
	unsigned int max, min;

	max = 0;
	min = 65535;
	head = data;

	/* Calculate Scaling Factor */
	for (i=0; i<H; i++)
		for (j=0;j<W; j++)
		{
				if ( min >= *head ) min = *head;
				if ( max <= *head ) max = *head;
				head++;
		}

	mp = (float)256 / ( (float)max-(float)min ); 

	/* Transfer Data to 8 bits */
	for (i=0; i<H; i++)
	{
		data += W;
		for ( j=0;j<W;j++)
		{		
			*dbits = (unsigned char)(((float)*data - (float)min)*mp);	
			dbits++;
			data--;
		}
		data+=W;
	
	}
	
	// force repaint
	InvalidateRect( hwnd, NULL, FALSE );
	
}      

	




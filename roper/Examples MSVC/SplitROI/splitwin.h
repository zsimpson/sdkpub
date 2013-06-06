#include "windows.h"

#define ALIGNLONG(i) ((i+3)/4*4)
#define COLORBITS 8


long WINAPI Procedure(		HWND hwnd,
							UINT message,
							DWORD wParam,
							LONG lParam);

class Window
{
public:
	 Window( int ImageSizeX, int ImageSizeY, char *name, int number );
	 ~Window();

	 UpdateDeviceIndependentBitmap(unsigned short *bits );
	 /* Windows Messages */
	 OnPaint(HWND wnd);
	 OnResize(LONG lp);
	 OnClose();
	 OnDestroy();
	

protected:
	/* Helper Routines */
	CreateDeviceIndependentBitmap(HWND wnd);
	Register(char *lpClass );
	Create( int ImageSizeX, int ImageSizeY, char *name );
	CreatePalette( LPBITMAPINFO info );

	HWND handle;	 

	HBRUSH ghbrWhite;
	HBRUSH ghbrBlack;

	int ImageWidth;
	int ImageHeight;
	
	HBITMAP            hBitmap;
	LPBITMAPINFOHEADER lpbi;
	BITMAPINFOHEADER   bi;
	char  *lpstBitmap;

	int ClientWidth;
	int ClientHeight;

	/* Data Scaling */
	int MaxI;
	int MinI;
	int NewMaxI;
	int NewMinI;
	int ScaleMode;

    int RoiNumber;
    int NX1;
    int NY1;
    int NX2;
    int NY2;

};

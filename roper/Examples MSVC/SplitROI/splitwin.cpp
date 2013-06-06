#include "splitwin.h"
#include "math.h"
#define PIXCM 1
#include "platform.h"

extern "C"
{
#include "pistpdef.h"
#include "pistpfcn.h"
}

static int RegisteredAlready;
/**************************************************
*
*	Purpose:  Register if not registered
*			  then create the window
**************************************************/
Window::Window( int xdimension, 
				int ydimension,
				char *name,
                int region)
{
    IRCT rect;
    int xb,yb;

	hBitmap		= NULL;
	handle		= NULL;
	MinI		= 65535;
	MaxI		= 0;
	NewMinI		= 0;
	NewMaxI     = 0;

    /* Store The Region Of Interest Number */
    RoiNumber   = region;

    /* Get The Normalized Region Data */
    PICM_Get_normal_rois( &rect, &xb, &yb, region );

    /* Calculate the Window Size */
    xdimension = rect.right - rect.left + 1;
    ydimension = rect.bottom- rect.top  + 1;

    /* Store The Region of Interest Normalized Info */
    NX1 = rect.left;
    NX2 = rect.right;
    NY1 = rect.top;
    NY2 = rect.bottom;

	if ( Register( "ImageTypeMult" ) || RegisteredAlready )
	{
		Create( xdimension, ydimension, name );
		RegisteredAlready = TRUE;
	}
}

/**************************************************
*
*	Purpose:  Clean up on destroy
*
**************************************************/
Window::~Window()
{
	/* If Bitmap, free it and all associated resources */
	if ( hBitmap )	
	{
		DeleteObject( hBitmap );
		hBitmap = NULL;
	}

}

/**************************************************
*
*	Purpose:  Register My Kind of window
*
**************************************************/
Window::Register(char *lpClass)
{	
	WNDCLASS wc;
   
    ghbrWhite = CreateSolidBrush(0x00FFFFFF);
    ghbrBlack = CreateSolidBrush(0x00000000);

    wc.style            = CS_OWNDC;
    wc.lpfnWndProc      = (WNDPROC) Procedure;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = sizeof(LONG);
    wc.hInstance        = NULL;
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
*	Purpose:  Create the window and set image size
*
**************************************************/
Window::Create( int x, int y, char *name )
{	
	ImageWidth  = x;
	ImageHeight = y;
	ClientWidth = x;
	ClientHeight= y;


	handle = CreateWindow(  "ImageTypeMult",										// pointer to registered class name								
							name,											// pointer to window name
							WS_VISIBLE | WS_OVERLAPPEDWINDOW | CS_DBLCLKS, //| WS_VSCROLL | WS_HSCROLL,	// window style
						    CW_USEDEFAULT,												// horizontal position of window
						    CW_USEDEFAULT,												// vertical position of window
							x,											// window width
							y,											// window height
							NULL,											// handle to parent or owner window
							NULL,											// handle to menu or child-window identifier
							NULL,										// handle to application instance
							NULL ); 	
	
	SetWindowLong( handle, 0, (LONG)this);

	if ( handle )
		return (TRUE);
	else
		return (FALSE);
}

/**************************************************
*
*	Purpose:  Resize Window
*
**************************************************/
Window::OnResize(LONG lParam)
{
	ClientWidth  = LOWORD(lParam);  // width of client area 
	ClientHeight = HIWORD(lParam);  // height of client area 

	/* Force Repaint */
	InvalidateRect( handle, NULL, FALSE );

	return(TRUE);
}

/**************************************************
*
*	Purpose:  Destroy Bitmap if window is closing
*
**************************************************/
Window::OnClose()
{
	/* If Bitmap, free it and all associated resources */
	if ( hBitmap )	
	{
		DeleteObject( hBitmap );
		hBitmap = NULL;
	}

	return(TRUE);
}

/**************************************************
*
*	Purpose:  destroy bitmap is somehow close was 
*			  avoided
*
**************************************************/
Window::OnDestroy()
{
	/* If Bitmap, free it and all associated resources */
	if ( hBitmap )	
	{
		DeleteObject( hBitmap );
		hBitmap = NULL;
	}

	return(TRUE);
}



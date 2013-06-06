#include "splitwin.h"
/**************************************************
*
*	Purpose: Handle Windows Messages and Pass them
*			 to the right class functions...
*
*
**************************************************/
long WINAPI Procedure(		HWND hwnd,
							UINT message,
							DWORD wParam,
							LONG lParam)
{
	long classinfo;

	/* Get the this pointer to the class that was stuffed in */
	/* at creation time	*/
	classinfo = GetWindowLong( hwnd, 0);

	switch (message)
	{
		/* If need to paint */
		case WM_PAINT:
			if ( classinfo != NULL )
			((Window*)classinfo)->OnPaint(hwnd);			
		break;
		
		/* Window is changing size */
		case WM_SIZE:
			if ( classinfo != NULL )
				((Window*)classinfo)->OnResize(lParam);
		break;
		
		/* Window is closing */
		case WM_CLOSE:
			if ( classinfo != NULL )
			{
				((Window*)classinfo)->OnClose();		
				delete ( (Window*)classinfo);
				SetWindowLong( hwnd, 0, 0);
			}
		break;
		
		/* Window is being destroyed */
	    case WM_DESTROY:
			if ( classinfo != NULL )
			{
				((Window*)classinfo)->OnDestroy();
				delete ( (Window*)classinfo);
			}
		break;
		default:
	        return DefMDIChildProc(hwnd, message, wParam, lParam);
		break;
	}

	return DefMDIChildProc(hwnd, message, wParam, lParam);
}
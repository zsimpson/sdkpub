/*************************************************************************
 *
 * WINCAIO - Measurement Computing Universal Library Demo Program
 *
 * (c) Copyright 2000-2002, Measurement Computing
 * All rights reserved.
 *
 * File:   WINCAIO.C
 *
 * This is an example Windows program that uses the Universal Library to demonestrate 
 * Simultaneous input/output functions using the same board.
 * 
 *
 * The WM_CREATE event handler allocates 2 buffers (A/D buffer and D/A buffer) 
 * via cbWinBufAlloc(). The Windows SDK function GlobalLock() twice for each buffer.  
 * cbAInScan() is called with the Options argument set to BACKGROUND | CONTINUOUS.  
 * cbAoutScan is called with the options BACKGROUND |CONTINUOUS.
 *
 * A Windows timer is set up that fires every 1/2 second.  The event handler for the
 * timer calls cbGetStatus() to get information on the background of each subsystem and then
 * forces a screen update.  The WM_PAINT handler displays the information that was 
 * returned by cbGetStatus.
 *
 *
 * Functions:  WinMain
 *             MainMessageHandler
 *             CleanUp
 *
 *
 **********************************************************************/

/* Include files */

#include <windows.h>                    /* Compiler's include files's */
#include <string.h>                   
#include <stdio.h>
#include "..\cbw.h"                        /* Universal Library's include file */

#define BOARD_NUM      0                /* Number of A/D board as defined with InstaCal */
#define BUF_SIZE       10000            /* Size of buffer */
#define NUM_SECS       10                /* Number of secs to collect data */
#define ADRANGE        BIP5VOLTS        /* A/D voltage range */
#define TIMER_NUM      1                /* Windows timer used by this program */

HWND hWndMain;                          /* handle for main window */

LONG FAR PASCAL MainMessageHandler (HWND, UINT, WPARAM, LPARAM);
void CreateSawTooth (unsigned short *buf);



/************************************************************************
*
* Name:      WinMain
*
* Arguments: hInstance - the instance handle for the program
*            hPrevInstance - the class name of the application (not used)
*            CmndLine - command line was called with (not used)
*            CmndShow - indicates how to display window
*                                                                      
* This is the entry point to the program. It gets called by Windows
* to start the program up.  This routine creates the main window,
* initializes a timer, and then falls into the main Windows Get
* message/Dispatch message loop.
*                                                                      
************************************************************************/

int PASCAL
WinMain(HANDLE hInstance, HANDLE hPrevInstance, LPSTR CmdLine, int nCmdShow)
{
    MSG       msg;                      /* MSG structure to pass to windows proc */
    WNDCLASS  wndclass;
    char      *AppName;                 /* Name for the window */

    cbErrHandling (PRINTALL, STOPALL);  /* Set library's error handling */

    CmdLine = NULL;                     /* Not used */
    AppName = "WINCDEMO";               /* The name of this application */
    if(!hPrevInstance)
        {
        wndclass.style      = CS_HREDRAW | CS_VREDRAW;
        wndclass.lpfnWndProc= MainMessageHandler;
        wndclass.cbClsExtra = 0;
        wndclass.cbWndExtra = 0;
        wndclass.hInstance  = hInstance;
        wndclass.hIcon      = LoadIcon (hInstance, AppName);
        wndclass.hCursor    = LoadCursor (NULL, IDC_ARROW);
        wndclass.hbrBackground  = GetStockObject (WHITE_BRUSH);
        wndclass.lpszMenuName   = AppName;
        wndclass.lpszClassName  = AppName;
        RegisterClass (&wndclass);
        }

    /* create application's Main window                                    */
    hWndMain = CreateWindow (AppName,                  /* Window class name          */
                             "AInScan Background",
                             WS_OVERLAPPEDWINDOW,
                             CW_USEDEFAULT,           /* Use default X, Y            */
                             CW_USEDEFAULT,           /* Use default X, Y            */
                             GetSystemMetrics(SM_CXSIZE) * 12,   /* x - fit text      */
                             GetSystemMetrics(SM_CYSIZE) * 12,  /* y - fit text      */
                             NULL,                    /* Parent window's handle      */
                             NULL,                    /* Default to Class Menu       */
                             hInstance,               /* Instance of window          */
                             NULL);                   /* Create struct for WM_CREATE */


    if (hWndMain == NULL)
        {
        MessageBox(NULL, "Could not create window in WinMain", NULL, MB_ICONEXCLAMATION);
        return (1);
        }

    ShowWindow(hWndMain, nCmdShow);     /* Display main window      */
    UpdateWindow(hWndMain);

    /* Start a 500ms timer to update display */
    if(!SetTimer(hWndMain, TIMER_NUM, 500, NULL))
        {
        MessageBox(NULL, "Error starting Windows timer", NULL, MB_OK |
                   MB_ICONEXCLAMATION);
        return (1);
        }                          
        
    while(GetMessage(&msg, NULL, 0, 0)) /* Main message loop */
        {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        }

    UnregisterClass (AppName, hInstance);
    return (msg.wParam);
} 
                                                                        
                                                                        

/************************************************************************
*
* Name:      MainMessageHandler
*
* Arguments: hWnd - handle to the window
*            Message - message that needs to be handled
*            hParam - message parameter
*            lParam - message parameter
*                                                                      
* This is the message dispatcher that gets called whenever Windows
* sends a message to this window.  WinMain started up a timer that
* sends a message every 1/2 sec.  When the message (WM_TIMER)is received
* by this routine, it reads the A/D and stores the values in ADValues[].
* It also causes a screen update which eill automatically generate a 
* WM_PAINT message.  The WM_PAINT handler takes care of converting the
* raw A/D values to voltages and printing them in the Window.
*                                                                      
************************************************************************/

LONG FAR PASCAL
MainMessageHandler(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    HDC        hDC;                     /* handle for the display device  */
    PAINTSTRUCT ps;                     /* holds PAINT information        */
    TEXTMETRIC tm;                      /* holds TEXT information         */

    static HRGN hRgn;                   /* Rectangle region Handles       */
    static int  CharWidth, CharHeight;
    
    
    static HGLOBAL  MemHandle32;        
    
    /* Variables for AinScan */
    static unsigned short *ADValues;    /* Win32 pointer to A/D buffer */
    static HGLOBAL   ADMemHandle; 
    static short     ADCurStatus;       /* Current status for D/A scan */
    static long      ADCurCount;        /* Current count for A/D scan  */
    static long      ADCurIndex;        /* Current index for A/D scan  */
    int              ADOptions;
    
    /* Variables for AoutScan */
    static unsigned short *DAValues;    /* Win32 pointer to D/A buffer */
    static HGLOBAL   DAMemHandle; 
    static long      DACurCount;        /* Current count for D/A scan  */
    static long      DACurIndex;        /* Current index for D/A scan  */
    static short     DACurStatus;       /* Current status for D/A scan */
    int              DAOptions;


    int        x, y;
    long       Count, Rate;
    char       OutString[80], *str, *StatusStr;
    float      Voltage;
    unsigned short CurValue;
    
    
    switch (Message)                    /* Windows Message Loop           */
        {
        case WM_CREATE:
            ADCurStatus = RUNNING;
            ADCurIndex = 0l;
            ADCurCount = 0l;

            hDC = GetDC(hWndMain);      /* Get the device context for window */
            GetTextMetrics(hDC, &tm);   /* From context, get size of font */
            CharWidth = tm.tmAveCharWidth;
            CharHeight = tm.tmHeight + tm.tmExternalLeading;
            ReleaseDC(hWndMain, hDC);
            hRgn = CreateRectRgn(0,0, CharWidth*30, CharHeight*30);    

            /* Allocate A/D Windows buffer */
            ADMemHandle = cbWinBufAlloc ((long)BUF_SIZE);
            
            /* Allocate D/A Windows buffer */
            DAMemHandle = cbWinBufAlloc ((long)BUF_SIZE);
            
            /* Allocate a local WIN32 buffer to hold A/D Data */
            MemHandle32 = GlobalAlloc(GMEM_FIXED | GMEM_DDESHARE, BUF_SIZE *sizeof(short));
				
            /* Get a 32-bit pointer to the A/D WIN32 buffer */
            ADValues = (unsigned short *)GlobalLock(MemHandle32);

            /* Get a 32-bit pointer to the D/A WIN32 buffer */
            DAValues = (unsigned short *)GlobalLock(DAMemHandle);

            /* Fill the D/A buffer with SawTooth values */
            CreateSawTooth (DAValues);


            /* Start up background A/D scan */
            Count = BUF_SIZE;
            Rate = BUF_SIZE / NUM_SECS;
            ADOptions = BACKGROUND | CONTINUOUS;
            cbAInScan (BOARD_NUM, 0, 0, Count, &Rate, ADRANGE, ADMemHandle,
                       ADOptions);
            
            DAOptions = BACKGROUND | CONTINUOUS;
            cbAOutScan (BOARD_NUM, 0, 0, Count, &Rate, ADRANGE, DAMemHandle,
                       DAOptions);
            break;

        case WM_TIMER:                  /* All Timer Events Processed Here */
            /* Get status of background A/D scan */
            cbGetStatus (BOARD_NUM, &ADCurStatus, &ADCurCount, &ADCurIndex, AIFUNCTION);
            
            /* Get status of background D/A scan */
            cbGetStatus (BOARD_NUM,&DACurStatus, &DACurCount, &DACurIndex, AOFUNCTION);

            InvalidateRgn(hWndMain, hRgn, FALSE);  /* Force screen update  */
            break;

        case WM_PAINT:                  /* Repaint client area of window */
            hDC = BeginPaint(hWndMain, &ps);     
            
            x = CharWidth * 2;          /* Position cursor within window */     
            y = CharHeight;             /* One line down and 2 chars in */
            str = "         A/D Info";  /* Print title */
            TextOut(hDC, x, y, str, strlen (str));

            if (ADCurStatus == RUNNING)   /* Print status of background scan */
                StatusStr = "RUNNING";
            else
                StatusStr = "COMPLETE";
            y += CharHeight;
            sprintf (OutString,"A/D Status = %s    ", StatusStr);
            TextOut(hDC, x, y, OutString, strlen (OutString));
                                              
            y += CharHeight;            /* Print current count */
            sprintf (OutString,"A/D Count = %ld    ", ADCurCount);
            TextOut(hDC, x, y, OutString, strlen (OutString));

            y += CharHeight;            /* Print current index */
            sprintf (OutString,"A/D Index = %ld    ", ADCurIndex);
            TextOut(hDC, x, y, OutString, strlen (OutString));

            if (ADCurIndex >= 0)
               {
               /* Copy Data from memory to 32 bit memory buffer */
               cbWinBufToArray(ADMemHandle, &ADValues[ADCurIndex], ADCurIndex ,1);
               
               CurValue = ADValues[ADCurIndex];
               }
            else
                CurValue = 0;                
                                    
            y += CharHeight*2;            /* Print raw data value */
            sprintf (OutString,"Raw A/D value = %u    ", CurValue);
            TextOut(hDC, x, y, OutString, strlen (OutString));
                                
            y += CharHeight;    /* Convert raw A/D to volts and print */
            cbToEngUnits(BOARD_NUM,ADRANGE,CurValue,&Voltage);
            sprintf (OutString,"Voltage = %.2f    ", Voltage);
            TextOut(hDC, x, y, OutString, strlen (OutString));

            /* print the D/A Info */
            y += CharHeight*2;            /* Print raw data value */
            str = "         D/A Info";  /* Print title */
            TextOut(hDC, x, y, str, strlen (str));

            if (DACurStatus == RUNNING)   /* Print status of background scan */
                StatusStr = "RUNNING";
            else
               {
               StatusStr = "COMPLETE";
               }
            y += CharHeight;
            sprintf (OutString,"D/A Status = %s    ", StatusStr);
            TextOut(hDC, x, y, OutString, strlen (OutString));
            
            
            y += CharHeight;            /* Print current count */
            sprintf (OutString,"D/A Count = %ld    ", DACurCount);
            TextOut(hDC, x, y, OutString, strlen (OutString));

            y += CharHeight;            /* Print current index */
            sprintf (OutString,"D/A Index = %ld ", DACurIndex);
            TextOut(hDC, x, y, OutString, strlen (OutString));


            SetTextAlign(hDC, TA_LEFT | TA_TOP);
            
            EndPaint(hWndMain, &ps);break;

        case WM_CLOSE:                      /* Close the window */
            KillTimer (hWnd, TIMER_NUM);    /* Stop the timer */
            cbStopBackground(BOARD_NUM, AIFUNCTION);  /* Stop A/D subsystem background scan */
            cbStopBackground(BOARD_NUM, AOFUNCTION); /* Stop A/D subsystem background scan */

            DestroyWindow(hWnd);                          
            if (hWnd == hWndMain)
                PostQuitMessage(0);         /* Send message to Quit application */
            if (ADMemHandle)                  
                cbWinBufFree (ADMemHandle);   /* Free allocated memory */

            if (DAMemHandle)                  
                cbWinBufFree (DAMemHandle);   /* Free allocated memory */

            if (MemHandle32)
               GlobalFree (MemHandle32);

            break;

        default:
            return (DefWindowProc(hWnd, Message, wParam, lParam));
        }
    return (0l);
}
                                                                        
void CreateSawTooth (unsigned short *buf)
{
	int MaxVal = 65535;
   int numSamples = BUF_SIZE;

   int i, j;
	unsigned int high =  (unsigned int)(MaxVal * 3.0/4.0);
	unsigned int low = (unsigned int)(MaxVal / 4.0);
	int dir = -1;	
	unsigned int offset = high;
	int freq = numSamples / 16;

	for (i = 0, j = 0; i < numSamples; i++, j++)
	{
		// toggle the sample value every freq samples
		if ( (i % freq) == 0 )
		{
			dir = -dir;
			offset = (offset == low) ? high : low;
			j = 0;
		}

		*(buf+i) = offset + (unsigned short) (j * dir * (float)MaxVal/(2.0*freq));
	} 
}
                                                                        

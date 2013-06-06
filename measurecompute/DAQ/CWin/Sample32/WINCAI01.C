/*************************************************************************
 *
 * WINCAI01 - Measurement Computing Universal Library Demo Program
 *
 * (c) Copyright 1995-2002, Measurement Computing
 * All rights reserved.
 *
 * File:   WINCAI01.C
 *
 * This is an example Windows program that uses the Universal Library to 
 * display data on channel 0. Double click the top left corner to halt 
 * the program. 
 *
 * Requirements:
 *     Board #0 (as installed with InstaCal) must have an A/D converter.      
 *
 *     The A/D board must support a -5 to +5 volt range.  If the voltage range for 
 *     the A/D is set via switches on the board then the board should be set for
 *     that range.  If the range for your board is software selectable then the 
 *     program will automatically set that range.
 *
 *     To use a different voltgae range, change the ADRANGE definitions below.
 *
 * Functions:  WinMain
 *             MainMessageHandler
 *
 **********************************************************************/

/* Include files */

#include <windows.h>                    /* Compiler's include files's */
#include <string.h>
#include <stdio.h>
#include "..\cbw.h"                        /* Universal Library's include file */

#define BOARD_NUM      0                /* Number of A/D board as defined with InstaCal */
#define ADRANGE        BIP5VOLTS        /* A/D voltage range */
#define TIMER_NUM      1                /* Windows timer used by this program */

HWND hWndMain;                          /* handle for main window */

LONG FAR PASCAL MainMessageHandler (HWND, UINT, WPARAM, LPARAM);

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
                             "AIn Demo",
                             WS_OVERLAPPEDWINDOW,
                             CW_USEDEFAULT,           /* Use default X, Y            */
                             CW_USEDEFAULT,           /* Use default X, Y            */
                             GetSystemMetrics(SM_CXSIZE) * 12,   /* x - fit text     */
                             GetSystemMetrics(SM_CYSIZE) * 10,  /* y - fit text      */
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

//    /* Start a 500ms timer to update display */
    if(!SetTimer(hWndMain, TIMER_NUM, 50, NULL))
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
* by this routine, it reads the A/D.
* It also causes a screen update which will automatically generate a 
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
    static unsigned short DataVal;
    int        x, y;
    char       OutString[80], *str;
    float      Voltage;

    switch (Message)                    /* Windows Message Loop           */
        {
        case WM_CREATE:
            hDC = GetDC(hWndMain);      /* Get the device context for window */
            GetTextMetrics(hDC, &tm);   /* From context, get size of font */
            CharWidth = tm.tmAveCharWidth;
            CharHeight = tm.tmHeight + tm.tmExternalLeading;
            ReleaseDC(hWndMain, hDC);
            hRgn = CreateRectRgn(0,0, CharWidth*30, CharHeight*12);    
            break;

        case WM_TIMER:                  /* All Timer Events Processed Here */
            InvalidateRgn(hWndMain, hRgn, FALSE);  /* Force screen update  */
            break;

        case WM_PAINT:                  /* Repaint client area of window */
            hDC = BeginPaint(hWndMain, &ps);     
            x = CharWidth * 2;          /* Position cursor within window */     
            y = CharHeight;             /* One line down and 2 chars in */
            str = "         A/D Info";  /* Print title */
            TextOut(hDC, x, y, str, strlen (str));
                                              
            y += CharHeight;            /* Print current index */
            cbAIn (BOARD_NUM, 0, ADRANGE, &DataVal);

            y += CharHeight*2;            /* Print raw data value */
            sprintf (OutString,"Raw A/D value = %u    ", DataVal);           
            TextOut(hDC, x, y, OutString, strlen (OutString));
                                
            y += CharHeight;    /* Convert raw A/D to volts and print */
            cbToEngUnits (BOARD_NUM,ADRANGE,DataVal,&Voltage);
            sprintf (OutString,"Voltage = %.2f    ", Voltage);
            TextOut(hDC, x, y, OutString, strlen (OutString));

            SetTextAlign(hDC, TA_LEFT | TA_TOP);
            EndPaint(hWndMain, &ps);
            break;

        case WM_CLOSE:                      /* Close the window */
            DestroyWindow(hWnd);                          
            if (hWnd == hWndMain)
                PostQuitMessage(0);         /* Send message to Quit application */
            break;

        default:
            return (DefWindowProc(hWnd, Message, wParam, lParam));
        }
    return (0l);
}
                                                                        
                                                                        

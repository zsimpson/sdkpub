/*ULGT02.C****************************************************************

File:                         ULGT02.C

Library Call Demonstrated:    cbGetStatus()

Purpose:                      Returns the status of a background
                              operation currently running.

Demonstration:                Uses an analog input scan for a background
                              operation. Updates the status of the data
                              collection until <ESC> is pressed.

Other Library Calls:          cbAInScan()
                              cbStopBackground()
                              cbErrHandling()

Special Requirements:         Board 0 must have an A/D converter.
                              Analog signal on an input channel.


Copyright (c) 1995-2002, Measurement Computing Corp.
All Rights Reserved.
***************************************************************************/


/* Include files */
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "..\cbw.h"

#define ESC_KEY 27


/* Prototypes */
void ClearScreen (void);
void GetTextCursor (int *x, int *y);
void MoveCursor (int x, int y);


void main ()
    {
    /* Variable Declarations */
    int Row, Col, j, NumLines, ExitFlag;
    int BoardNum = 0;
    int ULStat = 0;
    int LowChan = 0;
    int HighChan = 0;
    int Gain = 0;
    short Status = 0;
    long CurCount;
    long CurIndex;
    long Count = 100;
    long Rate = 4;
    char *StatusText;
    int PressedKey;
    WORD ADData[100];
    unsigned Options;
    float    RevLevel = (float)CURRENTREVNUM;

  /* Declare UL Revision Level */
   ULStat = cbDeclareRevision(&RevLevel);

    /* Initiate error handling
    Parameters:
        PRINTALL :all warnings and errors encountered will be printed
        DONTSTOP :program will continue even if error occurs.
                     Note that STOPALL and STOPFATAL are only effective in 
                     Windows applications, not Console applications. 
   */
    cbErrHandling (PRINTALL, DONTSTOP);

    /* set up the display screen */
    ClearScreen();
    printf ("Demonstration of cbGetStatus()\n\n");
    printf ("Press <ESC> to quit. <Spacebar> to stop/restart data collection.\n\n");
    printf ("%ld data points are being collected in the background with cbAInScan().\n", Count);
    printf ("\nData Points Collected:\n\n");
    printf ("Point #   Value     Status:\n");
    printf ("-------   ------\n");
    GetTextCursor (&Col, &Row);

    /* Collect the values with cbAInScan() in BACKGROUND mode
        Parameters:
             BoardNum    :the number used by CB.CFG to describe this board
             LowChan     :low channel of the scan
             HighChan    :high channel of the scan
             Count       :the total number of A/D samples to collect
             Rate        :sample rate in samples per second
             Gain        :the gain for the board
             ADData[]    :the array for the collected data values
             Options     :data collection options */

    Options = CONVERTDATA + BACKGROUND;

CollectData:
    ULStat = cbAInScan (BoardNum, LowChan, HighChan, Count, &Rate,
                        Gain, ADData, Options);

    StatusText = "Running";
    MoveCursor (Col + 27, Row - 2);
    printf (StatusText);

    /* During the BACKGROUND operation, check the status, print every ten values */
    ExitFlag = FALSE;
    while (!ExitFlag)
        {
        /* check the status of the current background operation
        Parameters:
            BoardNum  :the number used by CB.CFG to describe this board
            Status    :current status of the operation (IDLE or RUNNING)
            CurCount  :current number of samples collected
            CurIndex  :index to the last data value transferred 
            FunctionType: A/D operation (AIFUNCTIOM)*/
         ULStat = cbGetStatus (BoardNum, &Status, &CurCount, &CurIndex,AIFUNCTION);
        if (CurCount > 0)
            {
            MoveCursor (Col + 25, Row - 4);
            printf (" %lu  ", CurCount);
            if (!(CurIndex % 10))       /* display every tenth data point */
                {
                if (CurIndex > 0)
                    {
                    MoveCursor (Col, Row - 1 + (int) CurIndex / 10);
                    printf ("   %3u     %4u ",  (int) CurIndex, ADData[ (int) CurIndex - 1]);
                    }
                }
            }

        PressedKey = 0;
        if (kbhit())
            PressedKey = getch();

        /* check to see if <ESC> was pressed */
        if (PressedKey == ESC_KEY)
            {
            MoveCursor (Col + 30, Row - 4);
            printf ("Data collection interrupted by user.");
            ExitFlag = TRUE;
            }

        /* check to see if <Spacebar> was pressed */
        if (PressedKey == ' ')
            {
            if (Status == RUNNING)
                {
                ULStat = cbStopBackground (BoardNum,AIFUNCTION);
                 StatusText = "Idle   ";
                MoveCursor (Col + 27, Row - 2);
                printf (StatusText);
                NumLines = (int) CurIndex/10;
                }

            if (Status == IDLE)
                {
                /* clear any old numbers */
                for (j = 0; j < NumLines + 1; j++)
                    {
                    MoveCursor (Col, Row + j);
                    printf ("                ");
                    }
                MoveCursor (Col + 25, Row - 4);
                printf ("      ");

                goto CollectData;
                }
            }
        }

    /* the BACKGROUND operation must be explicitly stopped
       Parameters:
          BoardNum    :the number used by CB.CFG to describe this board 
          FunctionType:A/D operation (AIFUNCTIOM)*/  
    ULStat = cbStopBackground (BoardNum,AIFUNCTION);

    MoveCursor (1, 20);
    printf ("\n");

}



/***************************************************************************
*
* Name:      ClearScreen
* Arguments: ---
* Returns:   ---
*
* Clears the screen.
*
***************************************************************************/

#define BIOS_VIDEO   0x10

void
ClearScreen (void)
{
	COORD coordOrg = {0, 0};
	DWORD dwWritten = 0;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (INVALID_HANDLE_VALUE != hConsole)
		FillConsoleOutputCharacter(hConsole, ' ', 80 * 50, coordOrg, &dwWritten);

	MoveCursor(0, 0);

    return;
}


/***************************************************************************
*
* Name:      MoveCursor
* Arguments: x,y - screen coordinates of new cursor position
* Returns:   ---
*
* Positions the cursor on screen.
*
***************************************************************************/


void
MoveCursor (int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (INVALID_HANDLE_VALUE != hConsole)
	{
		COORD coordCursor;
		coordCursor.X = (short)x;
		coordCursor.Y = (short)y;
		SetConsoleCursorPosition(hConsole, coordCursor);
	}

    return;
}


/***************************************************************************
*
* Name:      GetTextCursor
* Arguments: x,y - screen coordinates of new cursor position
* Returns:   *x and *y
*
* Returns the current (text) cursor position.
*
***************************************************************************/

void
GetTextCursor (int *x, int *y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	*x = -1;
	*y = -1;
	if (INVALID_HANDLE_VALUE != hConsole)
	{
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		*x = csbi.dwCursorPosition.X;
		*y = csbi.dwCursorPosition.Y;
	}

    return;
}






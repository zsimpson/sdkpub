/*CInScan01.C****************************************************************

File:                         CInScan01.C

Library Call Demonstrated:    cbCInScan(), FOREGROUND mode

Purpose:                      Scans a range of Counter Input Channels and stores
                                the sample data in an array.

Demonstration:                Displays the counter input on two channels.
                              Continuously updates the display
                              until a key is pressed.

Other Library Calls:          cbErrHandling()

Special Requirements:         Board 0 must support counter scan function.
                              TTL signals on selected counter inputs.

Copyright (c) 1995-2006, Measurement Computing Corp.
All Rights Reserved.
***************************************************************************/


/* Include files */
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "..\cbw.h"

/* Prototypes */
void ClearScreen (void);
void GetTextCursor (int *x, int *y);
void MoveCursor (int x, int y);


void main ()
   {
   /* Variable Declarations */
   int Row, Col, I, J;
   int BoardNum = 0;
   int ULStat = 0;
   int FirstCtr = 0;
   int LastCtr = 1;
   long Count = 20;
   long Rate = 10;
   DWORD CounterData[20];
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
    printf ("Demonstration of cbCInScan() in FOREGROUND mode\n\n");

    /* Collect the values with cbCInScan()
        Parameters:
            BoardNum    :the number used by CB.CFG to describe this board
            FirstCtr    :first counter of the scan
            LastCtr     :last of the scan
            Count       :the total number of counter samples to collect
            Rate        :sample rate in samples per second
            DataBuffer[]:the array for the collected data values
            Options     :data collection options */

    Options = DEFAULTIO | CTR32BIT;
    ULStat = cbCInScan (BoardNum, FirstCtr, LastCtr, Count, &Rate,
                                            CounterData, Options);

    ClearScreen();
    printf ("Demonstration of cbCInScan() in FOREGROUND mode\n\n");

    /* display the data */
    for (J = 0; J < 2; J++)       /* loop through the channels */
        {
        printf ("\nThe first 5 values on Channel %u are ", J);
        GetTextCursor (&Col, &Row);

        for (I = 0; I < 5; I++)   /* loop through the values & print */
            {
            MoveCursor (Col, Row + I);
            printf ("%4u", CounterData[ I * 2 + J]);
            }
        printf ("\n");
        }
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


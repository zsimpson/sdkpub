/*ULAI02.C****************************************************************

File:                         ULAI02.C

Library Call Demonstrated:    cbAInScan(), FOREGROUND mode

Purpose:                      Scans a range of A/D Input Channels and
                              stores the sample data in an array.

Demonstration:                Displays the analog input on two channels.
                              Continuously updates the display
                              until a key is pressed.

Other Library Calls:          cbErrHandling()

Special Requirements:         Board 0 must have an A/D converter.
                              Analog signals on two input channels.

Copyright (c) 1995-2002, Measurement Computing Corp.
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
   int LowChan = 0;
   int HighChan = 1;
   int Gain = BIP5VOLTS;
   long Count = 20;
   long Rate = 3125;
   WORD ADData[20];
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
    printf ("Demonstration of cbAInScan() in FOREGROUND mode\n\n");

    /* Collect the values with cbAInScan()
        Parameters:
            BoardNum    :the number used by CB.CFG to describe this board
            LowChan     :low channel of the scan
            HighChan    :high channel of the scan
            Count       :the total number of A/D samples to collect
            Rate        :sample rate in samples per second
            Gain        :the gain for the board
            DataBuffer[]:the array for the collected data values
            Options     :data collection options */

    Options = CONVERTDATA;
    ULStat = cbAInScan (BoardNum, LowChan, HighChan, Count, &Rate,
                                            Gain, ADData, Options);

    ClearScreen();
    printf ("Demonstration of cbAInScan() in FOREGROUND mode\n\n");

    /* display the data */
    for (J = 0; J < 2; J++)       /* loop through the channels */
        {
        printf ("\nThe first 5 values on Channel %u are ", J);
        GetTextCursor (&Col, &Row);

        for (I = 0; I < 5; I++)   /* loop through the values & print */
            {
            MoveCursor (Col, Row + I);
            printf ("%4u", ADData[ I * 2 + J]);
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


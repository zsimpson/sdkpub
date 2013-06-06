/*ULDI03.C****************************************************************

File:                         ULDI03.C

Library Call Demonstrated:    cbDInScan()

Purpose:                      Multiple reads of digital input ports.

Demonstration:                FIRSTPORTA and B are configured for digital
                              inputs and are read using the WORDXFER
                              option. FIRSTPORTA is then read 15 times.

Other Library Calls:          cbDConfigPort()
                              cbErrHandling()

Special Requirements:         Board 0 must be a PDMA16.

Copyright (c) 1995-2002, Measurement Computing Corp.
All Rights Reserved.
***************************************************************************/


/* Include files */
#include <windows.h>
#include <stdio.h>
#include "..\cbw.h"

/* Prototypes */
void ClearScreen (void);
void GetTextCursor (int *x, int *y);
void MoveCursor (int x, int y);


void main ()
    {
    /* Variable Declarations */
    int Row, Col, I;
    int BoardNum = 0;
    int ULStat = 0;
    int PortNum, Direction;
    int Options;
    long Rate, Count;
    WORD DataBuffer[15];
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
    printf ("Demonstration of cbDInScan()\n\n");

    /* configure FIRSTPORTA and FIRSTPORTB for digital input
        Parameters:
            BoardNum    :the number used by CB.CFG to describe this board.
            PortNum     :the input port
            Direction   :sets the port for input or output */
    PortNum = FIRSTPORTB;
    Direction = DIGITALIN;
    ULStat = cbDConfigPort (BoardNum, PortNum, Direction);

    PortNum = FIRSTPORTA;
    ULStat = cbDConfigPort (BoardNum, PortNum, Direction);


    GetTextCursor (&Col, &Row);
    Count = 15;
    Rate = 15;
    printf ("Reading %ld input values at  ", Count);
    printf ("%ld samples/second...", Rate);

    /* read the digital input and display
        Parameters:
            BoardNum    :the number used by CB.CFG to describe this board
            PortNum     :the input port
            Count       :number of times to read digital input
            Rate        :sample rate in samples/second
            DataBuffer[]:the array for the digital input values read from the port
            Options     :data collection options */
    Options = WORDXFER;
    ULStat = cbDInScan (BoardNum, PortNum, Count, &Rate, DataBuffer, Options);

    /* display the value collected from the port(s) */
    MoveCursor (Col, Row + 1);
    printf ("The value of the port(s) is (in hex): (FIRSTPORTA & B combined)\n\n");
    for (I = 0; I < (int)Count; I++)
        {
        MoveCursor (Col + 10, Row + 2 + I);
        printf ("Read No:  %2u   Value: %X", I+1, DataBuffer[I]);
        }
    printf ("\n");

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






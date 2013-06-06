/*ULDO03.C****************************************************************

File:                         ULDO03.C

Library Call Demonstrated:    cbDOutScan()

Purpose:                      Multiple writes to a digital output port.

Demonstration:                FIRSTPORTA and B are configured for digital
                              output and values are sent to the port at
                              a specified rate.

Other Library Calls:          cbDConfigPort()
                              cbErrHandling()

Special Requirements:         Board 0 must be a PDMA16.


Copyright (c) 1995-2002, Measurement Computing Corp.
All Rights Reserved.
***************************************************************************/


/* Include files */
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include "..\cbw.h"


/* Prototypes */
void ClearScreen (void);
void GetTextCursor (int *x, int *y);
void MoveCursor (int x, int y);


void main ()
    {
    /* Variable Declarations */
    int I;
    int BoardNum = 0;
    int ULStat = 0;
    int PortNum, Direction;
    int Options;
    long Rate, Count;
    unsigned DataBuffer[10];
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
    printf ("Demonstration of cbDOutScan()\n\n");

    /* configure FIRSTPORTA and FIRSTPORTB for digital output
        Parameters:
            BoardNum    :the number used by CB.CFG to describe this board.
            PortNum     :the input port
            Direction   :sets the port for input or output */
    PortNum = FIRSTPORTB;
    Direction = DIGITALOUT;
    ULStat = cbDConfigPort (BoardNum, PortNum, Direction);

    PortNum = FIRSTPORTA;
    ULStat = cbDConfigPort (BoardNum, PortNum, Direction);

    /* place values into the output array */
    Count = 10;
    printf ("%ld data values are being placed in the output array...\n\n", Count);
    for (I = 0; I < (int)Count; I++)
        {
        DataBuffer[I] = 1 << I;
        printf ("Value %2u: %4u\n", I, DataBuffer[I]);
        }
    printf ("\nThe data values are being written to the port...\n\n");

    /* write to the digital output ports
        Parameters:
            BoardNum    :the number used by CB.CFG to describe this board
            PortNum     :the output port
            Count       :number of times to write to the digital output
            Rate        :sample rate in samples/second
            DataBuffer[]:the array for the digital output values sent to the port
            Options     :options for data operation*/
    Rate = 100;
    Options = WORDXFER;
    ULStat = cbDOutScan (BoardNum, PortNum, Count, &Rate, DataBuffer, Options);

    printf ("The values in the output array were successfully written to the port.");
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






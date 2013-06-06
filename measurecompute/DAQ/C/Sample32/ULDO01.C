/*ULDO01.C****************************************************************

File:                         ULDO01.C

Library Call Demonstrated:    cbDOut()

Purpose:                      Writes a bit to a digital output port.

Demonstration:                Configures FIRSTPORTA for output and
                              writes a value to the port.

Other Library Calls:          cbDConfigPort()
                              cbErrHandling()

Special Requirements:         Board 0 must have a digital output port.


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
    int Row, Col;
    int BoardNum = 0;
    int ULStat = 0;
    int PortNum, Direction;
    WORD DataValue;
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
    printf ("Demonstration of cbDOut()\n\n");
    printf ("Press any key to quit.\n\n");

    GetTextCursor (&Col, &Row);

    /* configure FIRSTPORTA for digital output
        Parameters:
            BoardNum    :the number used by CB.CFG to describe this board.
            PortNum     :the output port
            Direction   :sets the port for input or output */

    PortNum = FIRSTPORTA;
    Direction = DIGITALOUT;
    ULStat = cbDConfigPort (BoardNum, PortNum, Direction);

    /* get a user value to write to the port */
    do
        {
        MoveCursor (Col, Row);
        printf ("Enter a value to send to FIRSTPORTA (0-255):     ");
        scanf ("%i", &DataValue);
        } while  ((DataValue < 0) || (DataValue > 255));

    /* write the value to FIRSTPORTA
        Parameters:
            BoardNum    :the number used by CB.CFG to describe this board
            PortNum     :the output port
            DataValue   :the value written to the port   */
    ULStat = cbDOut(BoardNum, PortNum, DataValue);

    MoveCursor (Col, Row + 2);
    printf ("The value %u was written to FIRSTPORTA. ", DataValue);

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






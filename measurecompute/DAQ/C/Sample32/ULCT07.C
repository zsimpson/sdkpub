/*ULCT07.C****************************************************************

File:                         ULCT07.C

Library Call Demonstrated:    Event Counter Functions
                              cbCLoad32()
                              cbCIn32()

Purpose:                      Operate the counter.

Demonstration:                Reset and reads the counter.

Other Library Calls:          cbErrHandling()

Special Requirements:         Board 0 must have an Event Counter,
                              such as a miniLAB 1008 or PMD-1208LS.

Copyright (c) 2003, Measurement Computing Corp.
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
    int CounterNum = 1;
    int RegName;
    int LoadValue;
    int Count;

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
    printf ("Demonstration of Event Counter Functions.\n\n");
    printf ("NOTE: There must be a TTL freq. at cntr. 1 input.\n\n");
    printf ("Press any key to quit.\n\n\n");


    /* Reset the starting value to the counter with cbCLoad32()
        Parameters:
            BoardNum    :the number used by CB.CFG to describe this board
            RegName     :the counter to be loading with the starting value
            LoadValue   :the starting value to place in the counter */
    LoadValue = 0;   /* Event Counters can only be reset to 0 */
    RegName = LOADREG1;
    ULStat = cbCLoad32 (BoardNum, RegName, LoadValue);

    /* use a loop to keep checking the counter value with cbCIn() */
    GetTextCursor (&Col, &Row);

    while (!kbhit() && ULStat==NOERRORS)
        {
        /* Parameters:
            BoardNum    :the number used by CB.CFG to describe this board
            CounterNum  :the counter to be setup
            Count       :the count value in the counter */
        ULStat = cbCIn32 (BoardNum, CounterNum, &Count);

        MoveCursor (Col, Row + 1);
        printf ("The value of Counter %u is %u     ", CounterNum, Count);
        }

    MoveCursor (1, 22);
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





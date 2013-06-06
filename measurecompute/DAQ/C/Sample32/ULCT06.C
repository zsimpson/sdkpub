/*ULCT06.C****************************************************************

File:                         ULCT06.C

Library Call Demonstrated:    7266 (Quadrature encoder) Counter Functions
                                  cbC7266Config()
                                  cbCLoad32()
                                  cbCIn32()
                                  cbCStatus

Purpose:                      Operate the counter.

Demonstration:                Configures, loads, and
                              reads the counter and the counter status.

Other Library Calls:          cbErrHandling()

Special Requirements:         Board 0 must have a 7266 Counter (Quadrature
                              Encoder boards).

                              These functions are only supported in the 32
                              bit version of the Universal Library.  They
                              are not available in the DOS ow Windows 16
                              bit libraries.


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


void main()
    {
    /* Variable Declarations */
    int Row, Col;
    int ULStat = 0;
    int BoardNum = 0;
    int CounterNum, Quadrature, CountingMode, DataEncoding, IndexMode;
    int InvertIndex, FlagPins, GateEnable;
    long LoadValue;
    unsigned long Count, StatusBits;
    int  RegName;
    float RevLevel = (float)CURRENTREVNUM;
    char *DirectionStr;

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
    printf ("Demonstration of 7266 Counter Functions.\n\n");
    printf ("Press any key to quit.\n\n");

    /* set the configurable operations of the counter
        Parameters:
            BoardNum       :the number used by CB.CFG to describe this board
            CounterNum     :the counter to be configured (0-5)
            Quadrature     :Select type of counter input
            CountingMode   :Slects how counter will operate
            IndexMode      :Selects what index signal will control
            InvertIndex    :Set to ENABLED id index signal is inverted
            FlagPins       :Select which signals will drive Flag pins
            GateEnable     :Set to ENABLED to use external gating signal */
    CounterNum = 1;
    Quadrature = X1_QUAD;
    CountingMode = MODULO_N;
    DataEncoding = BINARY_ENCODING;
    IndexMode = INDEX_DISABLED;
    InvertIndex = DISABLED;
    FlagPins = CARRY_BORROW;
    GateEnable = DISABLED;
    ULStat = cbC7266Config (BoardNum, CounterNum , Quadrature, CountingMode,
                            DataEncoding, IndexMode, InvertIndex, FlagPins,
                            GateEnable);

    /* send a starting value to the counter with cbCLoad()
        Parameters:
            BoardNum    :the number used by CB.CFG to describe this board
            RegName     :the counter to be loading with the starting value
            LoadValue   :the starting value to place in the counter */

    LoadValue = 1000;
    RegName = COUNT1 + CounterNum - 1;
    printf ("Loading counter #%u with an initial count of %u using cbCLoad()\n", CounterNum, LoadValue);
    ULStat = cbCLoad32 (BoardNum, RegName, LoadValue);

    LoadValue = 2000;
    RegName = PRESET1 + CounterNum - 1;
    printf ("Setting counter #%u maximum count to %u by loading PRESET register", CounterNum, LoadValue);
    ULStat = cbCLoad32 (BoardNum, RegName, LoadValue);

    /* use a loop to keep checking the counter value with cbCIn() */
    GetTextCursor (&Col, &Row);
    while (!kbhit())
        {
        /* Parameters:
            BoardNum    :the number used by CB.CFG to describe this board
            CounterNum  :the counter to be setup
            Count       :the count value in the counter */
        ULStat = cbCIn32 (BoardNum, CounterNum, &Count);

        /* Parameters:
            BoardNum    :the number used by CB.CFG to describe this board
            CounterNum  :the counter to be setup
            StatusBits  :counter's status returned here */
        ULStat = cbCStatus (BoardNum, CounterNum, &StatusBits);
        if (StatusBits & C_UP_DOWN)
            DirectionStr = "UP  ";
        else
            DirectionStr = "DOWN";

        MoveCursor (Col, Row + 1);
        printf ("\nThe value of Counter %u is %u     \n", CounterNum, Count);
        printf ("The counter is now counting %s", DirectionStr);
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






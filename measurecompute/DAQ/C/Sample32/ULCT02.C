/*ULCT02.C****************************************************************

File:                         ULCT02.C

Library Call Demonstrated:    9513 Counter Functions
                                  cbC9513Init()
                                  cbC9513Config()
                                  cbCLoad()
                                  cbCIn()

Purpose:                      Operate the counter.

Demonstration:                Initializes, configures, loads, and
                              reads the counter.

Other Library Calls:          cbErrHandling()

Special Requirements:         Board 0 must have a 9513 Counter.
                              Program uses the internal clock to count.

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
    int ChipNum, FOutDivider, FOutSource, Compare1, Compare2, TimeOfDay;
    int CounterNum, GateControl, CounterEdge, CountSource, SpecialGate;
    int ReLoad, RecycleMode, BCDMode, CountDirection, OutputControl;
    int LoadValue;
    int RegName;
    WORD Count;
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
    printf ("Demonstration of 9513 Counter Functions.\n\n");
    printf ("Press any key to quit.\n\n");

    /* initialize the board level features
        Parameters:
            BoardNum    :the number used by CB.CFG to describe this board
            ChipNum     :chip being initialized (1 for CTR5, 1 or 2 for CTR10
            FOutDivider :the F-Out divider (0-15)
            FOutSource  :the signal source for F-Out
            Compare1    :status of comparator 1
            Compare2    :status of comparator 2
            TimeOfDay   :time of day control mode */
    ChipNum = 1;
    FOutDivider = 0;
    FOutSource = FREQ4;
    Compare1 = DISABLED;
    Compare2 = DISABLED;
    TimeOfDay = DISABLED;
    ULStat = cbC9513Init (BoardNum, ChipNum, FOutDivider, FOutSource, Compare1,
                          Compare2, TimeOfDay);

    /* set the configurable operations of the counter
        Parameters:
            BoardNum       :the number used by CB.CFG to describe this board
            CounterNum     :the counter to be configured (0-5)
            GateControl    :gate control value
            CounterEdge    :which edge to count
            CountSource    :signal source
            SpecialGate    :status of special gate
            ReLoad         :method of reloading the counter
            RecycleMode    :recycle mode
            BCDMode        :counting mode, BCD or binary
            CountDirection :direction for the counting (COUNTUP or COUNTDOWN)
            OutputControl  :output signal type and level */
    CounterNum = 1;
    GateControl = NOGATE;
    CounterEdge = POSITIVEEDGE;
    CountSource = FREQ4;
    SpecialGate = DISABLED;
    ReLoad = LOADREG;
    RecycleMode = RECYCLE;
    BCDMode = DISABLED;
    CountDirection = COUNTUP;
    OutputControl = ALWAYSLOW;
    ULStat = cbC9513Config (BoardNum, CounterNum , GateControl, CounterEdge,
                            CountSource, SpecialGate, ReLoad, RecycleMode,
                            BCDMode, CountDirection, OutputControl);

    /* send a starting value to the counter with cbCLoad()
        Parameters:
            BoardNum    :the number used by CB.CFG to describe this board
            RegName     :the counter to be loading with the starting value
            LoadValue   :the starting value to place in the counter */

    LoadValue = 1000;
    RegName = LOADREG1;
    printf ("Loading Counter %u with a value of %u using cbCLoad() ...", RegName, LoadValue);
    ULStat = cbCLoad (BoardNum, RegName, LoadValue);

    /* use a loop to keep checking the counter value with cbCIn() */
    GetTextCursor (&Col, &Row);
    while (!kbhit())
        {
        /* Parameters:
            BoardNum    :the number used by CB.CFG to describe this board
            CounterNum  :the counter to be setup
            Count       :the count value in the counter */
        ULStat = cbCIn (BoardNum, CounterNum, &Count);

        MoveCursor (Col, Row + 1);
        printf ("\nThe value of Counter %u is %u     ", CounterNum, Count);
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






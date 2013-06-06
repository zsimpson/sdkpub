/*ULCT05.C****************************************************************

File:                         ULCT05.C

Library Call Demonstrated:    8536 Counter Functions
                                  cbC8536Config()
                                  cbCLoad()
                                  cbCIn()

Purpose:                      Operate the counter.

Demonstration:                Configures, loads and reads the counter.

Other Library Calls:          cbErrHandling()

Special Requirements:         Board 0 must have an 8536 Counter.
                              There must be a TTL freq. at cntr. 1 input.
                              The gate line must be tied high.

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
    int CounterNum;
    int ChipNum;
    int RegName;
    int Ctr1Output;
    int OutputControl;
    int RecycleMode;
    int TrigType;
    int LoadValue;
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
    printf ("Demonstration of 8536 Counter Functions.\n\n");
    printf ("NOTE: There must be a TTL freq. at cntr. 1 input. The\n");
    printf ("      gate line must be tied high. Counters 1-3 are shown\n");
    printf ("      on the top of the connector,4-6 on the bottom.\n\n");
    printf ("Press any key to quit.\n\n\n");

    /* init the counter for desired operation
       Parameters:
           BoardNum    :the number used by CB.CFG to describe this board
           ChipNum     :the chip to be set up
           Ctr1Output  :how the counter output is used */
     ChipNum = 1;
     Ctr1Output = NOTLINKED;
     ULStat = cbC8536Init(BoardNum, ChipNum, Ctr1Output);

     /* configure the counter for desired operation
        Parameters:
            BoardNum    :the number used by CB.CFG to describe this board
            CounterNum  :the counter to be setup
            OutputControl  :which counter output is used
            RecycleMode :reload at 0
            TrigType    :trigger type */
    CounterNum = 1;
    OutputControl = TOGGLEONTC;
    RecycleMode = RECYCLE;
    TrigType = HW_START_TRIG;
    ULStat = cbC8536Config (BoardNum, CounterNum, OutputControl, RecycleMode, TrigType);
    printf ("\n\n");

    /* Send a starting value to the counter with cbCLoad()
        Parameters:
            BoardNum    :the number used by CB.CFG to describe this board
            RegName     :the counter to be loading with the starting value
            LoadValue   :the starting value to place in the counter */
    LoadValue = 1000;
    RegName = LOADREG1;
    printf ("Sending a starting value of %u to Counter %u ...", LoadValue, RegName);
    ULStat = cbCLoad (BoardNum, RegName, LoadValue);

    printf ("Done\n\n");

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


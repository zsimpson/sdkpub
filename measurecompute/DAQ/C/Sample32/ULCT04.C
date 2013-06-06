/*ULCT04.C*****************************************************************

File:                         ULCT04.C

Library Call Demonstrated:    cbCFreqIn()

Purpose:                      Measure the frequency of a signal.

Demonstration:                Initializes the counter and measures a frequency.

Other Library Calls:          cbErrHandling()

Special Requirements:         Board 0 must have a 9513 Counter.
                              Ext. freq at counter 1 input.
                              (100Hz < freq < 330kHz)
                              Ctr 4 out (pin 32) wired to Ctr 5 gate (pin12)

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
void MoveCursor (int x, int y);


void main()
    {
    /* Variable Declarations */
    int ULStat = 0;
    int BoardNum = 0;
    int SigSource;
    int ChipNum, FOutDivider, FOutSource, Compare1, Compare2, TimeOfDay;
    int GateInterval;
    long Freq;
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
    printf ("Demonstration of cbCFreqIn()\n");
    printf ("Must have an external freq. at cntr 1 input(100Hz < freq < 330kHz).");
    printf ("Cntr 4's output (pin 32) must be connected to Cntr 5's gate (pin12)");

    /* initialize the board level features
        Parameters:
            BoardNum    :the number used by CB.CFG to describe this board
            ChipNum     :chip being inititialized (1 for CTR5, 1 or 2 for CTR10)
            FOutDivider :the F-Out divider (0-15)
            FOutSource  :the signal source for F-Out
            Compare1    :status of comparator 1
            Compare2    :status of comparator 2
            TimeOfDay   :time of day control mode */
    ChipNum = 1;
    FOutDivider = 1;
    FOutSource = FREQ3;       /* sets up OSC OUT for 10kHz (may be used for */
    Compare1 = DISABLED;  /* input freq... connect pin 30 to 36 */
    Compare2 = DISABLED;
    TimeOfDay = DISABLED;
    ULStat = cbC9513Init (BoardNum, ChipNum, FOutDivider, FOutSource, Compare1,
                                                   Compare2, TimeOfDay);
    /* measure the frequency of the input signal
        Parameters:
            BoardNum    :the number used by CB.CFG to describe this board
            SigSource   :the signal to be measured
            GateInterval:gating interval in milliseconds
            Count       :the raw count during GateInterval is returned here
            Freq        :the calculated frequency (Hz) is returned here */

    GateInterval = 100;
    printf ("Measuring the frequency...\n\n");
    SigSource=CTRINPUT1;

    while(!kbhit())
        {
        ULStat = cbCFreqIn (BoardNum,  SigSource, GateInterval, &Count, &Freq);
        MoveCursor (5, 10);
        printf ("cbCFreqIn() returned the following values:\n");
        printf ("     Count     = %u     \n", Count);
        printf ("     Frequency = %ld Hz       ", Freq);
        printf ("\n\nPress any key to quit.");
        MoveCursor (1, 18);
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


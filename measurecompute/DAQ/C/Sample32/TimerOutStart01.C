/*TimerOutStart01.C****************************************************************

File:                         TimerOutStart01.C

Library Call Demonstrated:    cbTimerOutStart()
															cbTimerOutStop()

Purpose:                      Controls an Output Timer Channel.

Demonstration:                Sends a frequency output to Timer 0.

Other Library Calls:          cbErrHandling()

Special Requirements:         Board 0 must have a Timer output.

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
	int Row, Col;
	int BoardNum = 0;
	int ULStat = 0;
	int Chan;
	double frequency;
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
	printf ("Demonstration of cbTimerStart() and cbTimerStop()\n\n");
	GetTextCursor (&Col, &Row);

	Chan = 0;
	MoveCursor (0, 7);
	printf ("Enter a frequency between 16 and 1000000 Hz: ");
	MoveCursor (50, 7);
	scanf ("%lf", &frequency);
	ULStat = cbTimerOutStart (BoardNum, Chan, &frequency);
	if(ULStat == NOERRORS)
	{
		printf ("\n  Timer 0 was set to output %.2lf Hz.\n\n", frequency);
		printf ("Press any key to stop the timer:\n ");
		while (!kbhit()){}
		cbTimerOutStop(BoardNum, Chan);
	}
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


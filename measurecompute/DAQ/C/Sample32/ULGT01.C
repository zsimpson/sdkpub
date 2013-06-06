/*ULGT01.C****************************************************************

File:                         ULGT01.C

Library Call Demonstrated:    cbGetErrMsg()

Purpose:                      Returns the error message associated
                              with an error code.

Demonstration:                An invalid board# is generated and the
                              associated message is retrieved.

Other Library Calls:          cbErrHandling()

Special Requirements:         ---

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

void main ()
    {
    /* Variable Declarations */
    int ULStat, ECode, Chan, BoardNum, Gain;
    WORD DataValue;
    char c;
    char ErrMessage[80];
    float    RevLevel = (float)CURRENTREVNUM;

  /* Declare UL Revision Level */
   ULStat = cbDeclareRevision(&RevLevel);

    /* Parameters:
        DONTPRINT :no warnings or errors will be printed
        DONTSTOP  :if any error is encountered, the program will not stop */
    cbErrHandling (DONTPRINT, DONTSTOP);

    /* set up the display screen */
    ClearScreen();
    printf ("Demonstration of cbGetErrMsg()\n\n");
    printf ("Press any key to start.\n\n");
    c = (char)getch();

    /* generate an error by passing an invalid variable to a routine */
    printf ("Generating an error...\n");
    BoardNum = 99;
    Chan = 0;
    Gain = BIP5VOLTS;
    ULStat = cbAIn (BoardNum, Chan, Gain, &DataValue);

    /* trap the error and determine the message to print
    Parameters:
        ULStat     :the error code returned by the invalid call statement
        ErrMessage :the text of the error message associated with ULStat
                    must be dimensioned to at least the length of the
                    longest message */
    ECode = cbGetErrMsg (ULStat, ErrMessage);

    printf ("\a\n");
    printf ("The following error was detected:\n");
    printf ("\nError Code: %u\n", ULStat);
    printf ("Message:  %s", ErrMessage);

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






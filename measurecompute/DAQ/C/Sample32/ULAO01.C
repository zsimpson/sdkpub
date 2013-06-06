/*ULAO01.C****************************************************************

File:                         ULAO01.C

Library Call Demonstrated:    cbAOut()

Purpose:                      Writes to a D/A Output Channel.

Demonstration:                Sends a digital output to D/A 0
                              until a key is pressed.

Other Library Calls:          cbErrHandling()
                              cbFromEngUnits()

Special Requirements:         Board 0 must have a D/A output port.

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
        int ch;
    int Row, Col;
    int BoardNum = 0;
    int ULStat = 0;
    int Gain = BIP5VOLTS;
    int Chan, ExitFlag;
        WORD DataValue;
    float EngUnits;
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
    printf ("Demonstration of cbAOut()\n\n");
    GetTextCursor (&Col, &Row);

    ExitFlag = FALSE;
        Chan = 0;
    while (!ExitFlag)
        {
                MoveCursor (0, 7);
        printf ("Enter a voltage between -5.0 and +5.0: ");
                MoveCursor (39, 7);
        scanf ("%f", &EngUnits);
        ULStat = cbFromEngUnits(BoardNum, Gain, EngUnits, &DataValue);
        ULStat = cbAOut (BoardNum, Chan, Gain, DataValue);
                printf ("\n  %.2f volts has been sent to D/A 0.\n\n", EngUnits);
        printf ("Press Q to quit , any other key to continue:\n ");
                while (!kbhit()){}
                ch=getch();
        if (ch=='q' || ch=='Q')
            ExitFlag=TRUE;
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


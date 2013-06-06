/*ULAI01.C****************************************************************

File:                         ULAI01.C

Library Call Demonstrated:    cbAIn()

Purpose:                      Reads an A/D Input Channel.

Demonstration:                Displays the analog input on a
                              user-specified channel until a
                              key is pressed.

Other Library Calls:          cbErrHandling()

Special Requirements:         Board 0 must have an A/D converter.
                              Analog signal on an input channel.
                              CB.CFG must be in the current directory.

Copyright (c) 1993-2002, Measurement Computing Corp.
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
    int Row,Col;
        int Row2,Col2;
    int BoardNum = 0;
    int UDStat = 0;
    int Chan;
    int Gain = BIP5VOLTS;
    WORD DataValue = 0;
        float    EngUnits;
        float    RevLevel = (float)CURRENTREVNUM;

  /* Declare UL Revision Level */
   UDStat = cbDeclareRevision(&RevLevel);


    /* Initiate error handling
       Parameters:
           PRINTALL :all warnings and errors encountered will be printed
           DONTSTOP :program will continue even if error occurs.
                     Note that STOPALL and STOPFATAL are only effective in 
                     Windows applications, not Console applications. 
   */
    cbErrHandling (PRINTALL, DONTSTOP);

    /* set up the screen */
    ClearScreen();
    printf ("Demonstration of cbAIn()\n");
    printf ("Press any key to quit.\n\n");

    /* get the A/D channel to sample */
    printf ("Enter the channel to display: ");
    scanf("%i", &Chan);

        printf ("\n\nThe raw data value on Channel %u is: ", Chan);
    GetTextCursor (&Col, &Row);

        printf ("\nThe voltage on Channel %u is:......... ", Chan);
        GetTextCursor (&Col2, &Row2);

    /* collect the sample from the channel until a key is pressed */
    while (!kbhit())
        {
        /*Parameters:
            BoardNum    :number used by CB.CFG to describe this board
            Chan        :input channel number
            Gain        :gain for the board in BoardNum
            DataValue   :value collected from Chan */

        UDStat = cbAIn (BoardNum, Chan, Gain, &DataValue);
        UDStat = cbToEngUnits (BoardNum, Gain, DataValue, &EngUnits);

        MoveCursor(Col, Row);
                printf ("%6u ", DataValue);
                MoveCursor(Col2, Row2);
                printf ("%.2f ", EngUnits);
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


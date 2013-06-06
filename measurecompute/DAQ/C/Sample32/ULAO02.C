/*ULAO02.C****************************************************************

File:                         ULAO02.C

Library Call Demonstrated:    cbAOutScan()

Purpose:                      Writes to a range of D/A Output Channels.

Demonstration:                Sends a digital output to the D/A channels
                              until a key is pressed.

Other Library Calls:          cbErrHandling()

Special Requirements:         Board 0 must have D/A output ports.

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
    int Row, Col, I;
    int BoardNum = 0;
    int NumChan = 2;
    int ULStat = 0;
    int LowChan, HighChan;
    int Options;
    int Gain = BIP5VOLTS;
    WORD ADData[2];
    long Count, Rate;
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
    printf ("Demonstration of cbAOutScan()\n\n");
    printf ("Press any key to quit.\n\n\n");
    printf ("Channel  Value Sent\n-------  ----------\n");
    GetTextCursor (&Col, &Row);

    /* load the output array with values */
    LowChan = 0;
    HighChan = 1;
    for (I = LowChan; I <= HighChan; I++)
        {
        ADData[I] = (WORD)((4095 / (I + 1) + (4095 % (I+1))));
        MoveCursor (Col, Row + I);
        printf ("  %i        %u", I, ADData[I]);
        if (I == 0)
            printf(" (Full Scale)");
        if (I == 1)
            printf(" (Half Scale)");
        }
    printf ("\n\n");
    GetTextCursor (&Col, &Row);

    /* send the output values to the D/A range using cbAOutScan() */
    /* Parameters:
            BoardNum    :the number used by CB.CFG to describe this board
            LowChan     :the lower channel of the scan
            HighChan    :the upper channel of the scan
            Count       :the number of D/A values to send
            Rate        :send rate in values/second
            Gain        :the gain of the D/A
            ADData[]    :array of values to send to the scanned channels
            Options     :data send options  */
    Count = HighChan - LowChan + 1;  /* for all boards other than SBX-DD04,
                                        Count = the number of channels */
    Rate = NOTUSED;
    Options = 0;
    ULStat = cbAOutScan (BoardNum, LowChan, HighChan, Count, &Rate, Gain, ADData,
                         Options);

    MoveCursor (Col, Row);
        printf ("These values have been sent to the D/A's...\n\n");

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






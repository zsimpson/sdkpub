/*ULAI09.C****************************************************************

File:                         ULAI09.C

Library Call Demonstrated:    cbAConvertPretrigData()

Purpose:                      Waits for a trigger with cbAPretrig(), then
                              uses cbAConvertPretrigData() to convert
                              the data.

Demonstration:                Displays the analog input on one channel and
                              waits for the trigger.

Other Library Calls:          cbAPretrig()
                              cbErrHandling()

Special Requirements:         Board 0 must support cbAPretrig.

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
void WaitKey (void);

WORD ADData[1112];   /* array must be dimensioned TotalCount + 512 */

void main ()
    {
    /* Variable Declarations */
    int K;
    int BoardNum = 0;
    int ULStat = 0;
    int LowChan = 0;
    int HighChan = 0;
    int Gain = BIP5VOLTS;
    long PretrigCount = 10;
    long TotalCount = 700;
    long Rate = 2000;
    int Options;
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
    printf ("Demonstration of cbAConvertPretrigData()\n\n");
    printf ("The trigger input line (D0) must be held low before this demo is started.\n\n");
    WaitKey();

    printf ("\n\nWaiting for trigger:");
    /* Collect the values after the trigger
        Parameters:
            BoardNum    :the number used by CB.CFG to describe this board
            LowChan     :first A/D channel of the scan
            HighChan    :last A/D channel of the scan
            PretrigCount:number of pre-trigger A/D samples to collect
            TotalCount  :the total number of A/D samples to collect
            Rate        :sample rate in samples per second
            Gain        :the gain for the board
            ADData[]    :the array for the collected data values
            Options     :data collection options */
    Options = NOCONVERTDATA;
    ULStat = cbAPretrig (BoardNum, LowChan, HighChan, &PretrigCount,
                         &TotalCount, &Rate, Gain, ADData, Options);

    /* convert the data using cbAConvertPretrigData() and print
        Parameters:
            PretrigCount:number of pre-trigger A/D samples collected
                         actual value is returned by cbAPretrig()
            TotalCount  :total number of A/D samples collected
                         actual value is returned by cbAPretrig()
            ADData      :the array containing the raw data values
            NULL        :no channel tags returned  */
    printf ("Converting data with cbAConvertPretrigData()...\n\n");
    ULStat = cbAConvertPretrigData (BoardNum, PretrigCount, TotalCount, ADData, NULL);

   /* print the data after conversion */
    printf ("The Pre-trigger data were: \n");
    for (K = 1; K < (int)PretrigCount; K++)
        printf (" %u ", ADData[K]);
    printf ("\n\n");

    printf ("The first 10 values after the trigger were: \n");
    for (K = 1; K < 11; K++)
        printf (" %u ", ADData[PretrigCount + K]);

}


/***************************************************************************
*
* Name:      WaitKey
* Arguments:
* Returns:
*
* Waits for a key press
*
***************************************************************************/

void
WaitKey (void)
{
     printf ("--- Press Enter to continue ---\n");
     getch();
     return;
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






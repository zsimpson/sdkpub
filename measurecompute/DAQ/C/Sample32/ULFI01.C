/* ULFI01.C=================================================================

File:                         ULFI01.C

Library Call Demonstrated:    cbFileAInScan()

Purpose:                      Scan a range of A/D channels and store the
                              data in a disk file.

Demonstration:                Collects data points from one analog input
                              channel and saves them in a file.

Other Library Calls:          cbErrHandling()

Special Requirements:         Board 0 must an A/D converter.

Copyright (c) 1995-2002, Measurement Computing Corp.
All Rights Reserved.
=========================================================================*/


/* Include files */
#include <windows.h>
#include <stdio.h>
#include "..\cbw.h"


/* Prototypes */
void ClearScreen (void);
void GetTextCursor (int *x, int *y);
void MoveCursor (int x, int y);


void main ()
    {
    /* Variable Declarations */
    int BoardNum = 0;
    int ULStat = 0;
    short LowChan = 0;
    short HighChan = 0;
    int Gain = BIP5VOLTS;
    long Count,TotalCount;
    long PreTrigCount;
    long NumPoints = 128000;
    long Rate;
    int Options;
    char *FileName;
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
    printf ("Demonstration of cbFileAInScan()\n");

    /* set up the collection parameters */
    Count = NumPoints;
    FileName = "DEMO.DAT";
    Rate = 50000;                     /* sampling rate (samples per second) */
    LowChan = 0;
    HighChan = 1;
    Options = TIMED + NODTCONNECT;
    Gain = BIP5VOLTS;

    printf ("Collecting %4ld data points...\n\n", NumPoints);
    printf ("Rate     = %ld Hz\n", Rate);
    printf ("LowChan  = %u\n", LowChan);
    printf ("HighChan = %u\n", HighChan);
    printf ("Options  = %u\n", Options);
    printf ("Gain     = %u\n", Gain);
    printf ("FileName = %s\n", FileName);
    printf ("Count    = %ld\n", Count);

    /* Collect the values with cbFileAInScan()
      Parameters:
        BoardNum   :the number used by CB.CFG to describe this board
          LowChan    :first A/D channel of the scan
          HighChan   :last A/D channel of the scan
          Count      :the total number of A/D samples to collect
          Rate       :sample rate in samples per second
          Gain       :the gain for the board
          FileName   :the filename for the collected data values
          Options    :data collection options  */
    ULStat = cbFileAInScan (BoardNum, LowChan, HighChan, Count, &Rate, Gain, FileName, Options);

    printf ("\n%4ld data points were placed in the file: %s.\n\n", Count, FileName);
    ULStat = cbFileGetInfo (FileName, &LowChan, &HighChan, &PreTrigCount, &TotalCount, &Rate, &Gain);

    printf ("Rate     = %ld Hz\n", Rate);
    printf ("LowChan  = %u\n", LowChan);
    printf ("HighChan = %u\n", HighChan);
    printf ("Options  = %u\n", Options);
    printf ("Gain     = %u\n", Gain);
    printf ("FileName = %s\n", FileName);
    printf ("Count    = %ld\n", TotalCount);
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







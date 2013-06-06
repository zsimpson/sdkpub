/*ULFI02.C=================================================================

File:                         ULFI02.C

Library Call Demonstrated:    File Operations:
                              cbFileRead()
                              cbFileGetInfo()

Purpose:                      Read information & data from a streamer file.

Demonstration:                Creates a file and scans analog data to the
                              file. Displays the data in the file and the
                              information in the file header.

Other Library Calls:          cbFileAInScan()
                              cbErrHandling()

Special Requirements:         Board 0 must have an A/D converter.

Copyright (c) 1995-2002, Measurement Computing Corp.
All Rights Reserved.
========================================================================== */


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
    int I;
    int ULStat;
    int BoardNum = 0;
    long TestPoints = 128000;
    long FirstPoint, NumPoints;
    short HighChan, LowChan;
    int Options, Gain;
    long PreTrigCount, Count, TotalCount, Rate;
    char *FileName;
    WORD DataBuffer[10];
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
    printf ("Demonstration of File Operations \n");
    printf ("     using cbFileRead() and cbFileGetInfo().\n\n");

    Count = TestPoints;
    FileName = "DEMO.DAT";
    Rate = 50000;                      /* sampling rate (samples per second) */
    LowChan = 0;
    HighChan = 1;
    Options = TIMED + NODTCONNECT;
    Gain = BIP5VOLTS;

    printf ("Collecting %4ld data points...", Count);

    /* Collect the values with cbFileAInScan()
    Parameters:
          BoardNum   :the number used by CB.CFG to describe this board
          LowChan    :first A/D channel of the scan
          HighChan   :last A/D channel of the scan
          Count      :the total number of A/D samples to collect
          Rate       :sample rate in samples per second
          Gain       :the gain for the board
          FileName   :the filename for the collected data values
          Options    :data collection options */

    ULStat = cbFileAInScan (BoardNum, LowChan, HighChan, Count, &Rate, Gain, FileName, Options);

    printf ("which were placed in the file: %s.\n", FileName);

    /* show the information in the file header with cbFileGetInfo()
       Parameters:
          FileName      :the filename containing the data
          LowChan       :first A/D channel of the scan
          HighChan      :last A/D channel of the scan
          PreTrigCount  :the number of pretrigger samples in the file
          TotalCount    :the total number of A/D samples in the file
          Rate          :sample rate in samples per second
          Gain          :the gain at which the samples were collected */
    ULStat = cbFileGetInfo (FileName, &LowChan, &HighChan, &PreTrigCount, &TotalCount, &Rate, &Gain);

    printf ("\nThe information in the file header is:\n");
    printf ("     Streamer File Name        =  %s\n", FileName);
    printf ("     Low Channel               =     %1u\n", LowChan);
    printf ("     High Channel              =     %1u\n", HighChan);
    printf ("     No. of Pretrigger samples =  %4ld\n", PreTrigCount);
    printf ("     No. of Samples            =  %4ld\n", TotalCount);
    printf ("     Collection Rate (Hz)      =  %4ld\n", Rate);
    printf ("     Gain                      =   %3u\n", Gain);

  /* Show the data using cbFileRead()
  Parameters:
      FileName      :the filename containing the data
      NumPoints     :the number of data values to read from the file
      FirstPoint    :index of the first data value to read
      DataBuffer[]   :array to read data into  */

     NumPoints = 5;     /* read the first five points of the file */
     FirstPoint = 0;     /* start at the first point after the trigger*/
     ULStat = cbFileRead (FileName, FirstPoint, &NumPoints, DataBuffer);

    /* display the data values read from the file */
    printf ("\nThe first 5 data values in the file are:\n");
    for (I = (int)FirstPoint; I < (int)NumPoints ; I++)
        printf ("     %2u) %4u  \n", I, DataBuffer[I]);
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






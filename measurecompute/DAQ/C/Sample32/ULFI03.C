/*ULFI03.C=================================================================

File:                         ULFI03.C

Library Call Demonstrated:    File Operations:
                              cbFilePretrig%()
                              cbFileRead()
                              cbFileGetInfo()

Purpose:                      Stream data continuously to a streamer file
                              until a trigger is received, continue data
                              streaming until total number of samples minus
                              the number of pretrigger samples is reached.

Demonstration:                Creates a file and scans analog data to the
                              file continuously, overwriting previous data.
                              When a trigger is received, acquisition stops
                              after (TotalCount& - PreTrigCount&) samples
                              are stored. Displays the data in the file and
                              the information in the file header. Prints
                              data from Pretrigger-4 to Pretrigger+6.

Other Library Calls:          cbErrHandling()

Special Requirements:         Board 0 must have an A/D converter.

Copyright (c) 1995-2002, Measurement Computing Corp.
All Rights Reserved.
========================================================================== */


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
    int I;
    int ULStat;
    int BoardNum = 0;
    long TotalCount = 128000;
    long PreTrigCount = 2000;
    long Rate=50000;
    long FirstPoint, NumPoints;
    short HighChan, LowChan;
    int Options, Gain;
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
    printf ("using cbFilePretrig%() and cbFileGetInfo%().\n\n");

    printf ("The trigger input line (D0) must be held low before this demo is started.\n\n");
    while (!kbhit())
        {;}

    printf ("\n\nRelease D0 when ready:\n\n");

    FileName = "DEMO.DAT";
    LowChan = 0;
    HighChan = 1;
    Options = 0;
    Gain = BIP5VOLTS;

    printf ("Collecting %4ld data points...", TotalCount);

    /* Collect the values with cbFileAInScan()
       Parameters:
            BoardNum     :the number used by CB.CFG to describe this board
            LowChan      :first A/D channel of the scan
            HighChan     :last A/D channel of the scan
            PreTrigCount :the total number of A/D samples to collect
            TotalCount   :the total number of samples to store to file
            Rate         :sample rate in samples per second
            Gain         :the gain for the board
            FileName   :the filename for the collected data values
            Options    :data collection options */

    ULStat = cbFilePretrig(BoardNum, LowChan, HighChan, &PreTrigCount, &TotalCount, &Rate, Gain, FileName, Options);

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


    /* show the data using cbFileRead()
       Parameters:
          FileName      :the filename containing the data
          NumPoints     :the number of data values to read from the file
          FirstPoint    :index of the first data value to read
          DataBuffer[]   :array to read data into  */

    NumPoints = 10;     /* read 10 points in the file */
    FirstPoint = PreTrigCount-4;     /* start at the trigger - 4 */
    ULStat = cbFileRead (FileName, FirstPoint, &NumPoints, DataBuffer);

    /* display the data values read from the file */
    printf ("\nThe five points before and after the trigger are:\n");
    for (I = 0; I < (int)NumPoints; I++)
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






/*ULMM01.C*****************************************************************

File:                         ULMM01.C

Library Call Demonstrated:    cbAPretrig() with EXTMEMORY option and
                              cbReadPretrigData()

Purpose:                      Collect pre-trig data from A/D to memory board

Demonstrates:                 How to use the collect pre-trigger data
                              to memory board and then retreive the data.

Other Library Calls:          cbErrHandling()

Special Requirements:         Board 0 must be an A/D board(DAS16/330i/330M1).
                              Board 5 must be a memory board.
                              A/D and memory boards must be connected together
                              via a DT-Connect cable.

Copyright (c) 1995-2002, Measurement Computing Corp.
All Rights Reserved.
**************************************************************************/


/* Include files */
#include <windows.h>
#include <stdio.h>
#include "..\cbw.h"

/* Prototypes */
void ClearScreen (void);
void GetTextCursor (int *x, int *y);
void MoveCursor (int x, int y);

#define ADBOARD  0                      /* Board number of A/D board */
#define MEMBOARD 5                      /* Board number of memory board */
#define BUFSIZE  100                    /* Size of buffer used with cbMemReadPretrig() */

void main (void)
{
    int  BoardNum, LowChan, HighChan, Range, Options, DataPoint;
    int  i, FirstPoint, ErrCode;
    long PretrigCount, Count, TotalCount, Rate;
    WORD ADData[BUFSIZE];
    WORD DataBuffer[BUFSIZE];
    int      ULStat = 0;
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


    /* Set up the display screen */
    ClearScreen();
    printf ("Demonstration of cbAPretrig() with EXTMEMORY and cbMemReadPretrig()\n");
    printf ("\n");
    printf ("This program collects 1000 points including 10 pre-trigger points\n");
    printf ("and stores them in the memory board\n");
    printf ("\n");
    printf ("It then reads the data in from the memory board and displays it.\n");
    printf ("\n");
    printf ("Waiting for trigger signal on trigger input line ...\n");

    /* Collect data to memory with cbAPretrig() and the EXTMEMORY option
        Parameters:
            BoardNum     :the number used by CB.CFG to describe this board
            LowChan      :the first channel of the scan
            HighChan     :the last channel of the scan
            PretrigCount :Number of pre-trigger points to collect
            TotalCount   :the total number of A/D samples to collect
            Rate         :sample rate in samples per second
            Range        :the gain for the board
            ADData[]     :the array for the collected data values
            Options      :data collection options  */

    BoardNum = ADBOARD;
    LowChan = 0;
    HighChan = 0;
    PretrigCount = 10;
    TotalCount = 10000;
    Rate = 10000;
    Range = BIP5VOLTS;
    Options = EXTMEMORY;
    do                  /* Keep retrying while trigger line is in wrong state */
        {
        ErrCode = cbAPretrig (BoardNum, LowChan, HighChan, &PretrigCount,
                              &TotalCount, &Rate, Range, ADData, Options);
        } while (ErrCode == TRIGSTATE);

    if (ErrCode)       /* For any other error print message and exit */
        {
        printf ("ERROR #%d occurred when calling cbAPretrig()\n", ErrCode);
        exit (1);
        }

    /* Turn automatic error handling back on again
      Parameters:
         PRINTALL    :all warnings and errors encountered will be printed
         DONTSTOP    :if any error is encountered, the program will continue */
    cbErrHandling (PRINTALL, DONTSTOP);

    /* Read the first block of data from the memory board.
       Read a block of data from  the memory board
           BoardNum - Board number of the memory board
           DataBuffer - Array of data to read data into
           FirstPoint - Address to read first point (or FROMHERE)
           NUMPOINTS - Number of points to read  */
     FirstPoint = 0;                     /* Set address of first point to read */
     BoardNum = MEMBOARD;
     Count = BUFSIZE;
     cbMemReadPretrig (BoardNum, DataBuffer, FirstPoint, Count);

     for (i=0; i<20; i++)
        {
        /* Raw data from memory board contains a 4 bit channel number (LSB's)
           and a 12 bit A/D value (MSB's).  Convert to just a 12 bit A/D value. */
        DataPoint = DataBuffer[i] >> 4;

        printf ("%3d. %4d\n", i, DataPoint);
        }
    printf ("\n");
    printf ("Trigger occurred between points #9 and #10\n");
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




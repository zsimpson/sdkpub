/*ULMM03.C*****************************************************************

File:                         ULMM03.C

Library Call Demonstrated:    cbAInScan() with EXTMEMORY option

Purpose:                      Collect data from A/D to memory board

Demonstrates:                 How to use the EXTMEMORY option to
                              send data to a memory board and how to
                              read the data back again.

Other Library Calls:          cbMemRead(), cbErrHandling()

Special Requirements:         Board 0 must be an A/D board.
                              Board 5 must be a memory board.
                              A/D and memory boards must be connected together
                              via a DT-Connect cable.


Copyright (c) 1995-2002, Measurement Computing Corp.
All Rights Reserved.
**************************************************************************/


/* Include files */
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "..\cbw.h"

/* Prototypes */
void ClearScreen (void);
void GetTextCursor (int *x, int *y);
void MoveCursor (int x, int y);

#define ADBOARD   0                     /* Board number of A/D board */
#define MEMBOARD  5                     /* Board number of memory board */
#define NUMPOINTS 1000                  /* Number of points to collect from A/D */
#define BUFSIZE   100                   /* Size of buffer used with cbMemRead() */
#define NUMBLOCKS 5                     /* Number of blocks to read/write */


void main (void)
{
    int  BoardNum, LowChan, HighChan, Gain, Options, DataPoint;
    int  i, x, y, FirstPoint, PointNum, StartY;
    long Count, Rate;
    WORD DataBuffer[BUFSIZE];
    int      ULStat = 0;
    float    RevLevel = (float)CURRENTREVNUM;

  /* Declare UL Revision Level */
   ULStat = cbDeclareRevision(&RevLevel);


    /* Initiate error handling
       Activating error handling will trap errors like bad channel numbers
       and non-configured conditions.
       Parameters:
         PRINTALL    :all warnings and errors encountered will be printed
         DONTSTOP :program will continue even if error occurs.
                     Note that STOPALL and STOPFATAL are only effective in 
                     Windows applications, not Console applications. 
   */
    cbErrHandling (PRINTALL, DONTSTOP);

    /* Set up the display screen */
    ClearScreen();
    printf ("Demonstration of cbAInScan() with EXTMEMORY option\n");
    printf ("\n");
    printf ("This program collects 1000 points from an A/D directly to an attached\n");
    printf ("memory board.\n");
    printf ("\n");
    printf ("It then reads the data in blocks from the memory board and displays it\n");
    printf ("on the screen.\n");
    printf ("\n");

    /* Reset memory board to the start of memory */
    BoardNum = MEMBOARD;
    cbMemReset(BoardNum);

    /*  Collect data to memory with cbAInScan() and the EXTMEMORY option
        Parameters:
            BoardNum    :the number used by CB.CFG to describe this board
            LowChan     :the first channel of the scan
            HighChan    :the last channel of the scan
            Count       :the total number of A/D samples to collect
            Rate        :sample rate in samples per second
            Gain        :the A/D range code for the board
            DataBuffer[]:the array for the collected data values
            Options     :data collection options  */
    BoardNum = ADBOARD;
    LowChan = 0;
    HighChan = 0;
    Count = NUMPOINTS;
    Rate = 5000;
    Gain = BIP5VOLTS;
    Options = EXTMEMORY;
    cbAInScan (BoardNum, LowChan, HighChan, Count, &Rate, Gain, DataBuffer, Options);

    /* Read the data back from the memory board in blocks.  Print each block
       of data on the screen. */
    FirstPoint = 0;                     /* Set address of first point to read */
    for (PointNum=0; PointNum<NUMPOINTS-1; PointNum+=BUFSIZE)
        {
        /* Read a block of data from  the memory board
             BoardNum - Board number of the memory board
             DataBuffer - Array of data to read data into
             FirstPoint - Address to read first point (or FROMHERE)
             NUMPOINTS - Number of points to read */
             BoardNum = MEMBOARD;
             Count = BUFSIZE;
        cbMemRead (BoardNum, DataBuffer, FirstPoint, Count);
        FirstPoint = FROMHERE;

        GetTextCursor (&x, &StartY);        /* Get cursor's vertical position */
        y = StartY;
        x = 1;
        for (i=0; i<BUFSIZE; i++)     /* Print one screen of data */
            {
            printf ("\n");
            MoveCursor (x, y);

            /* Raw data from memory board contains a 4 bit channel number (LSB's)
               and a 12 bit A/D value (MSB's).  Convert to just a 12 bit A/D value. */
            DataPoint = DataBuffer[i] >> 4;

            printf ("%3d. %4d", PointNum+i, DataPoint);
            y++;
            if (y == 24)                /* If at the bottom, reset to top */
                {
                y = StartY;             /* and move to next column. */
                x += 11;
                }
            }

        getch();
        ClearScreen();
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




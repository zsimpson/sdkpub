/*ULMM02.C*****************************************************************

File:                         ULMM02.C

Library Call Demonstrated:    cbMemRead() and cbMemWrite()

Purpose:                      Write data to a memory board and then read
                              it back again

Demonstrates:                 How to read and write to memory in blocks

Other Library Calls:          cbErrHandling()

Special Requirements:         Board 5 must be a memory borad

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

#define MEMBOARD 5              /* Board number of memory board */
#define NUMPOINTS 100           /* Number of points per chan */
#define NUMBLOCKS 5             /* Number of blocks to read/write */


void main ()
{
    int i, x, StartY, ULStat, FirstPoint, BlockNum, BoardNum;
    long Count;
    WORD DataBuffer1[NUMPOINTS];
    WORD DataBuffer2[NUMPOINTS];
    float    RevLevel = (float)CURRENTREVNUM;

  /* Declare UL Revision Level */
   ULStat = cbDeclareRevision(&RevLevel);

    /*  Initiate error handling to automatically trap and report errors
        Parameters:
          PRINTALL    :all warnings and errors encountered will be printed
          DONTSTOP :program will continue even if error occurs.
                     Note that STOPALL and STOPFATAL are only effective in 
                     Windows applications, not Console applications. 
   */
    cbErrHandling (PRINTALL, DONTSTOP);


    /* Set up the display screen */
    ClearScreen();
    printf ("Demonstration of cbMemRead() and cbMemWrite()\n");
    printf ("\n");
    printf ("This program writes 500 values to the memory board by writing\n");
    printf ("5 blocks of 100 values to consecutive locations in the memory board.\n");
    printf ("\n");
    printf ("The values that are written correspond to the memory board address that\n");
    printf ("they are stored at.  So for example the value 203 is stored at address 203\n");
    printf ("in memory.\n");
    printf ("\n");
    printf ("It then reads the data back and displays it.\n");

    Count = NUMPOINTS;
    FirstPoint = 0;                     /* Set address of first point to write */
    for (BlockNum=0; BlockNum<NUMBLOCKS; BlockNum++)
        {
        /* Fill up the array with ascending data */
        for (i=0; i<NUMPOINTS; i++)
            {
            DataBuffer1[i] = (WORD)(BlockNum * NUMPOINTS + i);
            DataBuffer2[i] = 0;
            }

        /* Write the block to the memory board
              MEMBOARD - Board number of the memory board
              DataBuffer1 - Array of data to be written
              FirstPoint - Address to write first point (or NEXTONE)
              NUMPOINTS - Number of points to write */
              BoardNum = MEMBOARD;
        ULStat = cbMemWrite (BoardNum, DataBuffer1, FirstPoint, Count);
        FirstPoint = FROMHERE;
        }

    printf ("\n");
    printf ("Address=   0        100       200       300       400\n");
    printf ("         ------    ------    ------    ------    ------\n");
    GetTextCursor (&x, &StartY);
    FirstPoint = 0;                     /* Set address of first point to read */
    for (BlockNum=0; BlockNum<NUMBLOCKS; BlockNum++)
        {
        /* Read a block of data from  the memory board
              MEMBOARD - Board number of the memory board
              DataBuffer2 - Array of data to read data into
              FirstPoint - Address to read first point (or FROMHERE)
              NUMPOINTS - Number of points to read */
        ULStat = cbMemRead (BoardNum, DataBuffer2, FirstPoint, Count);
        FirstPoint = FROMHERE;

        /* Print the data */
        for (i=0; i<5; i++)
            {
            MoveCursor (BlockNum*10+10, StartY+i);
            printf ("%u\n", DataBuffer2[i]);
            }
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




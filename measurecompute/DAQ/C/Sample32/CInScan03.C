/*CInScan03.C****************************************************************

File:                         CInScan03.C

Library Call Demonstrated:    cbCInScan(), FOREGROUND mode and cbCConfigScan() 

Purpose:                      Scans a Counter Input in encoder mode and stores
                              the sample data in an array.

Demonstration:                Displays counts from encoder as phase A, phase B,
                              and totalizes the index on Z.
                              

Other Library Calls:          cbErrHandling()

Special Requirements:         Board 0 must support counter scans in encoder mode.
                              Phase A from encode connected to counter 0 input.
                              Phase B from encode connected to counter 1 input.
                              Index Z from encode connected to counter 2 input.
							  

Copyright (c) 1995-2007, Measurement Computing Corp.
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
   int I;
   int BoardNum = 0;
   int ULStat = 0;
   int FirstCtr = 0;
   int LastCtr = 0;
   int CounterNum, MapChannel;
   int Mode,DebounceTime, DebounceMode, EdgeDetection, TickSize;

   long Count = 50;
   long Rate = 10;
   DWORD CounterData[50];
   unsigned Options;

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
    printf ("Demonstration of cbCInScan() in FOREGROUND mode\n\n");

	/*Setup Counters
		 Parameters:
         BoardNum       :the number used by CB.CFG to describe this board
			CounterNum     :counter to set up
			Mode           :counter mode
			DebounceTime   :debounce time
			DebounceMode   :debounce mode
			EdgeDetection  :determines whether the rising edge or falling edge is to be detected
			TickSize       :reserved.
			MapChannel     :mapped channel*/


	//Setup Counter 0 (Phase A signal)

	CounterNum = 0;
	Mode = ENCODER | ENCODER_MODE_X1 | CLEAR_ON_Z_ON;
	DebounceTime = CTR_DEBOUNCE_NONE;
	DebounceMode = 0;
	EdgeDetection = CTR_RISING_EDGE;
	TickSize = 0;
	MapChannel = 2;

	ULStat = cbCConfigScan(BoardNum, CounterNum, Mode, DebounceTime, DebounceMode, EdgeDetection, TickSize, MapChannel);


    /* Collect the values with cbCInScan()
        Parameters:
            BoardNum    :the number used by CB.CFG to describe this board
            FirstCtr    :first counter of the scan
            LastCtr     :last counter of the scan
            Count       :the total number of counter samples to collect
            Rate        :sample rate in samples per second
            DataBuffer[]:the array for the collected data values
            Options     :data collection options */

    Options = CTR32BIT;
    ULStat = cbCInScan (BoardNum, FirstCtr, LastCtr, Count, &Rate,
                                            CounterData, Options);

	ClearScreen();
    printf ("Demonstration of cbCInScan() in FOREGROUND mode\n\n");
	 printf (" Counter Data\n\n");
    /* display the data */
    for (I = 0; I < Count; I++)       /* loop through the channels */
        {
        printf("%8u\n", CounterData[I]);
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


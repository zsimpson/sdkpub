/*ULAO04.C****************************************************************

File:                         ULAO04.C

Library Call Demonstrated:    cbAOutScan() with scan option set to SCALEDATA

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

#define NUMCHANS  2
#define NUMPOINTS 2

void main ()
    {
    /* Variable Declarations */
    int Row, Col;
    int BoardNum = 0;
    int NumChan = 2;
    int ULStat = 0;
    int LowChan, HighChan;
    int Options;
    int Gain = BIP5VOLTS;
    double DAData[NUMCHANS * NUMPOINTS];
    long Count, Rate;
	long CurCount, CurIndex;
	short Status = IDLE;
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
    printf ("Demonstration of cbAOutScan() with SCALEDATA option\n\n");
    printf ("Press any key to quit.\n\n\n");
    GetTextCursor (&Col, &Row);

	/* load the output array with values */

	// output (low)
	DAData[0] = 0.0;        
	DAData[1] = 0.0;

	// output (high))
	DAData[2] = 5.0;
	DAData[3] = 5.0;

	LowChan = 0;
    HighChan = 1;

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
    Count = NUMPOINTS * NUMCHANS;
    Rate = 1000;
    Options = BACKGROUND | CONTINUOUS | SCALEDATA;
    ULStat = cbAOutScan (BoardNum, LowChan, HighChan, Count, &Rate, Gain, DAData,
                         Options);

    /* show the results */
    printf ("Here are the output values \n\n");

	printf ("Output(low):   %.8f       %.8f   \n",DAData[0],DAData[1]);
	printf ("Output(high):  %.8f       %.8f   \n\n",DAData[2],DAData[3]);

	GetTextCursor (&Col, &Row);

	if(ULStat == NOERRORS)
		Status = RUNNING;

	/* During the BACKGROUND operation, check the status */
    while (!kbhit() && Status==RUNNING)
        {
        /* Check the status of the current background operation
        Parameters:
            BoardNum  :the number used by CB.CFG to describe this board
            Status    :current status of the operation (IDLE or RUNNING)
            CurCount  :current number of samples collected
            CurIndex  :index to the last data value transferred 
            FunctionType: A/D operation (AOFUNCTION)*/
        ULStat = cbGetStatus (BoardNum, &Status, &CurCount, &CurIndex,AOFUNCTION);
		printf ("Current Count: %u \n", CurCount);
		printf ("Current Index: %d \n", CurIndex);
		printf ("\nPress any key to quit.\n");
		MoveCursor (Col, Row);
		}
	MoveCursor (Col, Row + 4);
	printf ("\nData output terminated.");

	/* The BACKGROUND operation must be explicitly stopped
        Parameters:
             BoardNum    :the number used by CB.CFG to describe this board 
             FunctionType: A/D operation (AOFUNCTION)*/  
    ULStat = cbStopBackground (BoardNum,AOFUNCTION);;

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






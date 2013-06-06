/*DaqOutScan01.C****************************************************************

File:                         DaqOutScan01.C

Library Call Demonstrated:    cbDaqOutScan(), BACKGROUND mode

Purpose:                      Synchronously writes to an  Analog channel and a Digital port in the background.

Demonstration:                Sends output to the D/A channels
                              until a key is pressed.

Other Library Calls:          cbDConfigPort()
                              cbErrHandling()

Special Requirements:         Board 0 must support cbDaqInScan.


Copyright (c) 1995-2006, Measurement Computing Corp.
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
    int ULStat = 0;
    int BoardNum = 0;
	int Options, ChanCount;
    long Count, Rate;
    WORD DAData[NUMPOINTS*NUMCHANS];
    short ChanArray[NUMCHANS];
	short ChanTypeArray[NUMCHANS];
    short GainArray[NUMCHANS];
	short Status = IDLE;
	long CurCount, CurIndex;
	int PortNum, Direction;
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
    printf ("Demonstration of cbDaqOutScan()\n\n");

    /* load the arrays with values */
    ChanArray[0] = 0;
	ChanTypeArray[0] = ANALOG;
    GainArray[0] = BIP10VOLTS;

    ChanArray[1] = FIRSTPORTA;
	ChanTypeArray[1] = DIGITAL16;
    GainArray[1] = NOTUSED;

    /* FIRSTPORTA is treated as a 16-bit port; therefore FIRSTPORTA and FIRSTPORTB must be configured for digital output */
	PortNum = FIRSTPORTA;
    Direction = DIGITALOUT;
    ULStat = cbDConfigPort (BoardNum, PortNum, Direction);

	PortNum = FIRSTPORTB;
    Direction = DIGITALOUT;
    ULStat = cbDConfigPort (BoardNum, PortNum, Direction);

	/* load the output array with values */

	// output (low)
	DAData[0] = 0;        
	DAData[1] = 0;

	// output (high))
	DAData[2] = 65535;
	DAData[3] = 65535;

	ChanCount = NUMCHANS;
    Count = NUMPOINTS * NUMCHANS;
    Rate = 1000;												/* sampling rate (samples per second) */
    Options = BACKGROUND | CONTINUOUS | NONSTREAMEDIO;          /* data collection options */

    ULStat = cbDaqOutScan(BoardNum, ChanArray, ChanTypeArray, GainArray, ChanCount, &Rate, Count, DAData, Options);

    /* show the results */
    printf ("Here are the output values \n\n");

    printf ("    Channel:     0       FIRSTPORTA\n");
    printf ("ChannelType:   ANALOG    DIGITAL16\n");
    printf ("       Gain:   +-10V         -    \n");
    printf ("               -----       -----  \n");
	printf ("Output(low):   %5d       %5d   \n",DAData[0],DAData[1]);
	printf ("Output(high):  %5d       %5d   \n\n",DAData[2],DAData[3]);

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
            FunctionType: A/D operation (DAQOFUNCTION)*/
        ULStat = cbGetStatus (BoardNum, &Status, &CurCount, &CurIndex,DAQOFUNCTION);
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
             FunctionType: A/D operation (DAQOFUNCTION)*/  
    ULStat = cbStopBackground (BoardNum,DAQOFUNCTION);

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






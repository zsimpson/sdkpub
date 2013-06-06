/*DaqInScan01.C****************************************************************

File:                         DaqInScan01.C

Library Call Demonstrated:    cbDaqInScan(), FOREGROUND mode

Purpose:                      Synchronously scans Analog channels, Digital ports and Counters
                              in the foreground.

Demonstration:                Collects data on Analog Channels 0 and 1,
							  FirstPortA and Counter 0.

Other Library Calls:          cbDConfigPort()
                              cbErrHandling()
							  cbCConfigScan()

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


#define NUMCHANS   4
#define NUMPOINTS 10

void main ()
    {
    /* Variable Declarations */
    int ULStat = 0;
	int BoardNum = 0;
    int  i, Options, SampleNum, Chan, ChanCount;
    long PreTrigCount, TotalCount, Rate;
    WORD ADData[NUMPOINTS*NUMCHANS];
    short ChanArray[NUMCHANS];
	short ChanTypeArray[NUMCHANS];
    short GainArray[NUMCHANS];
	int PortNum, Direction, CounterNum;
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
    printf ("Demonstration of cbDaqInScan()\n\n");

    /* load the arrays with values */
    ChanArray[0] = 0;
	ChanTypeArray[0] = ANALOG;
    GainArray[0] = BIP10VOLTS;

    ChanArray[1] = FIRSTPORTA;
	ChanTypeArray[1] = DIGITAL8;
    GainArray[1] = NOTUSED;

    ChanArray[2] = 0;
	ChanTypeArray[2] = CTR16;
    GainArray[2] = NOTUSED;

    ChanArray[3] = 5;
    ChanTypeArray[3] = ANALOG;
    GainArray[3] = BIP5VOLTS;


    /* configure FIRSTPORTA  for digital input */
	PortNum = ChanArray[1];
    Direction = DIGITALIN;
    ULStat = cbDConfigPort (BoardNum, PortNum, Direction);

	// configure counter 0
	CounterNum = ChanArray[2];
    ULStat = cbCConfigScan(BoardNum, CounterNum, STOP_AT_MAX, CTR_DEBOUNCE_NONE, 0, CTR_RISING_EDGE, 0, CounterNum);

    /* Collect the values with cbDaqInScan()
        Parameters:
            BoardNum    :the number used by CB.CFG to describe this board
            ChanArray[] :array of channel values
			ChanTypeArray[] : array of channel types
            GainArray[] :array of gain values
            ChanCount    :the number of channels
            Rate        :sample rate in samples per second
			PretrigCount:number of pre-trigger A/D samples to collect
            TotalCount  :the total number of A/D samples to collect
            ADData[]    :the array for the collected data values
            Options     :data collection options  */

	ChanCount = NUMCHANS;
	PreTrigCount =0;
    TotalCount = NUMPOINTS * NUMCHANS;
    Rate = 100;                    /* sampling rate (samples per second) */
    Options = CONVERTDATA;          /* data collection options */

    ULStat = cbDaqInScan(BoardNum, ChanArray, ChanTypeArray, GainArray, ChanCount, &Rate, &PreTrigCount, &TotalCount, ADData, Options);

    /* show the results */
    printf ("Here are the values returned \n\n");

    printf ("    Channel:   0    FIRSTPORTA     0	   5\n");
    printf ("ChannelType: ANALOG  DIGITAL8    CTR16  ANALOG\n");
    printf ("       Gain:+-10V        -         -     +-5V\n");
    printf ("             -----     -----     -----  ----- \n");

    i = 0;
    for (SampleNum=0; SampleNum<NUMPOINTS; SampleNum++)
        {
		printf ("             ");
        for (Chan=0; Chan<ChanCount; Chan++)
			printf ("%5d    ",ADData[i++]);
        printf ("\n");
        }
    printf ("\n");
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






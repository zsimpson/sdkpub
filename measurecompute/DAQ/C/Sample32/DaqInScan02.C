/*DaqInScan02.C****************************************************************

File:                         DaqInScan02.C

Library Call Demonstrated:    cbDaqInScan(), continuous BACKGROUND mode

Purpose:                      Synchronously scans Analog channels, Digital ports and Counters
                              in the background.

Demonstration:                Displays the input channels data.
                              Calls cbGetStatus to determine the status
                              of the background operation. Updates the
                              display until a key is pressed.

Other Library Calls:          cbGetStatus()
                              cbStopBackground()
							  cbCConfigScan()
							  cbDConfigPort()
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

#define NUMCHANS  4
#define NUMPOINTS 10000

void main ()
    {
    /* Variable Declarations */
    int Row, Col;
	int  BoardNum = 0;
	int Options;
    long PreTrigCount, TotalCount, Rate, ChanCount;
	short ChanArray[NUMCHANS];
	short ChanTypeArray[NUMCHANS];
    short GainArray[NUMCHANS];
    int ULStat = 0;
    short Status = IDLE;
    long CurCount;
    long CurIndex, DataIndex;
	int PortNum, Direction, CounterNum;
    WORD *ADData;
    float    RevLevel = (float)CURRENTREVNUM;

  /* Declare UL Revision Level */
   ULStat = cbDeclareRevision(&RevLevel);

    ADData = (WORD*)cbWinBufAlloc(NUMPOINTS * NUMCHANS);
    if (!ADData)    /* Make sure it is a valid pointer */
        {
        printf("\nout of memory\n");
        exit(1);
        }

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
    printf ("Data are being collected in the BACKGROUND, CONTINUOUSLY\n");


	/* load the arrays with values */
    ChanArray[0] = 0;
	ChanTypeArray[0] = ANALOG;
    GainArray[0] = BIP10VOLTS;

    ChanArray[1] = FIRSTPORTA;
	ChanTypeArray[1] = DIGITAL16;
    GainArray[1] = NOTUSED;

	ChanArray[2] = 0;
	ChanTypeArray[2] = CTR32LOW;
    GainArray[2] = NOTUSED;

	ChanArray[3] = 0;
	ChanTypeArray[3] = CTR32HIGH;
    GainArray[3] = NOTUSED;

	/* configure FIRSTPORTA and FIRSTPORTB for digital input */
	
	PortNum = FIRSTPORTA;
    Direction = DIGITALIN;
    ULStat = cbDConfigPort (BoardNum, PortNum, Direction);

	PortNum = FIRSTPORTB;
	ULStat = cbDConfigPort (BoardNum, PortNum, Direction);

	// configure counter 0
	CounterNum = ChanArray[2];
    ULStat = cbCConfigScan(BoardNum, CounterNum, ROLLOVER, CTR_DEBOUNCE_NONE, 0, CTR_RISING_EDGE, 0, CounterNum);

    /* Collect the values with cbDaqInScan() in BACKGROUND mode, CONTINUOUSLY
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
	Rate = 1000;								             /* sampling rate (samples per second) */
	Options = CONVERTDATA + BACKGROUND + CONTINUOUS;         /* data collection options */

	ULStat = cbDaqInScan(BoardNum, ChanArray, ChanTypeArray, GainArray, ChanCount, &Rate, &PreTrigCount, &TotalCount, ADData, Options);

    printf ("--------------------------------------------------------------------------------");
    printf ("| Your program could be doing something useful here while data are collected...|");
    printf ("--------------------------------------------------------------------------------");
    printf ("\nCollecting data...\n\n");
    printf ("Press any key to quit.\n\n");

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
            FunctionType: A/D operation (DAQIFUNCTION)*/
        ULStat = cbGetStatus (BoardNum, &Status, &CurCount, &CurIndex,DAQIFUNCTION);

        /* check the current status of the background operation */
        if (Status == RUNNING)
            {
			DataIndex = CurIndex -  CurIndex % NUMCHANS - NUMCHANS;
			if(DataIndex>0)
				{
					MoveCursor (Col, Row);
					printf ("Channel 0   Data point: %3ld   ", DataIndex);
					printf ("  Value: %d  \n",ADData[DataIndex]);
					DataIndex++;
					printf ("FIRSTPORTA  Data point: %3ld   ", DataIndex);
					printf ("  Value: %d  \n",ADData[DataIndex]);
					DataIndex++;
					printf ("Counter 0   Data point: %3ld   ", DataIndex);
					printf ("  Value: %u  ",ADData[DataIndex] + (ADData[DataIndex+1]<<16));   // 32-bit counter
				}
            }
        }
    printf ("\n");
    MoveCursor (Col, Row + 4);
    printf ("Data collection terminated.");

    /* The BACKGROUND operation must be explicitly stopped
        Parameters:
             BoardNum    :the number used by CB.CFG to describe this board 
             FunctionType: A/D operation (DAQIFUNCTION)*/  
    ULStat = cbStopBackground (BoardNum,DAQIFUNCTION);

    cbWinBufFree((int)ADData);
    MoveCursor (1, 22);
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







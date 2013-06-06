/*DaqSetTrigger01.C****************************************************************

File:                         DaqSetTrigger01.C

Library Call Demonstrated:    cbDaqSetTrigger()

Purpose:                      Sets start and stop triggers. These triggers are
                              used to initiate and terminate A/D conversion using cbDaqInScan,
										with EXTTRIGGER selected.

Demonstration:                Sets start and stop triggers.
							  Displays the input channels data when start
							  trigger occurs.
                              Calls cbGetStatus to determine the status
                              of the background operation. Continuously updates
							  the display until stop trigger occurs or 
							  a key is pressed.

Other Library Calls:          cbDaqInScan()
							  cbGetStatus()
                              cbStopBackground()
                              cbErrHandling()

Special Requirements:         Board 0 must support DaqSetTrigger.


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

#define NUMCHANS  3
#define NUMPOINTS 10000

void main ()
    {
    /* Variable Declarations */
    int Row, Col;
	int BoardNum = 0;
	int Options;
    long PreTrigCount, TotalCount, Rate, ChanCount;
	short ChanArray[NUMCHANS];
	short ChanTypeArray[NUMCHANS];
    short GainArray[NUMCHANS];
    int ULStat = 0;
    short Status = RUNNING;
    int TrigSource, TrigSense, TrigChan, ChanType, Gain, TrigEvent;
	float Level, Variance;
	
    long CurCount;
    long CurIndex, DataIndex;
	int PortNum, Direction;
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

    printf ("Demonstration of cbDaqSetTrigger()\n\n");


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


	/* configure FIRSTPORTA for digital input */
	
	PortNum = FIRSTPORTA;
    Direction = DIGITALIN;
    ULStat = cbDConfigPort (BoardNum, PortNum, Direction);

	/* Set Triggers 
		Parameters:
			BoardNum    :the number used by CB.CFG to describe this board
			TrigSource	:trigger source
			TrigSense	:trigger sensitivity
			TrigChan	:trigger channel
			ChanType	:trigger channel type
			Gain		:trigger channel gain
			Level		:trigger level
			Variance	:trigger variance
			TrigEvent	:trigger event type */

	/* Start trigger settings.
	   AD conversions are enabled when analog channel 0 makes a transition from below 2 V to above.*/
	TrigSource = TRIG_ANALOG_SW;
	TrigSense = RISING_EDGE;
	TrigChan = ChanArray[0];
	ChanType = ChanTypeArray[0];
	Gain = GainArray[0];
	Level = 2.0;
	Variance = 0;
	TrigEvent = START_EVENT;

	/* Set start trigger */
	ULStat = cbDaqSetTrigger(BoardNum, TrigSource, TrigSense, TrigChan, ChanType , Gain, Level, Variance, TrigEvent);

	/* Stop trigger settings. 
	   AD conversions are terminated when counter 0 reaches 100 counts.*/
	TrigSource = TRIG_COUNTER;
	TrigSense = ABOVE_LEVEL;
	TrigChan = ChanArray[2];
	ChanType = ChanTypeArray[2];
	Gain = GainArray[2];
	Level = 100;
	Variance = 0;
	TrigEvent = STOP_EVENT;

	/* Set stop trigger */
	ULStat = cbDaqSetTrigger(BoardNum, TrigSource, TrigSense, TrigChan, ChanType , Gain, Level, Variance, TrigEvent);


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
	PreTrigCount = 0;
	TotalCount = NUMPOINTS * NUMCHANS;
	Rate = 1000;								             /* sampling rate (samples per second) */
	Options = CONVERTDATA + BACKGROUND + CONTINUOUS + EXTTRIGGER;         /* data collection options */

	ULStat = cbDaqInScan(BoardNum, ChanArray, ChanTypeArray, GainArray, ChanCount, &Rate, &PreTrigCount, &TotalCount, ADData, Options);

	if (ULStat==NOERRORS)
		{

		printf ("\nTrigger signals are needed for this sample.\nSignals required: ACH0 - signal that transitions from below 2V to above.\nCNT0 should have a TTL signal applied.");
	    
		printf ("\n\nStart Trigger Source: Channel 0\n");
		printf ("Waiting for start trigger....\n\n");
		
		printf ("Press any key to quit.\n\n");
   
		GetTextCursor (&Col, &Row);

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
		
			DataIndex = CurIndex;
			if(DataIndex>=0)
				{
					MoveCursor (Col, Row);
					printf ("Triggered!\n\n");
					printf ("\nCollecting data...\n\n");
					printf ("Channel 0   Data point: %3ld   ", DataIndex);
					printf ("  Value: %d  \n",ADData[DataIndex]);
					DataIndex++;
					printf ("FIRSTPORTA  Data point: %3ld   ", DataIndex);
					printf ("  Value: %d  \n",ADData[DataIndex]);
					DataIndex++;
					printf ("Counter 0   Data point: %3ld   ", DataIndex);
					printf ("  Value: %d  ",ADData[DataIndex]);
					
					printf ("\n\nStop Trigger Source: Counter 0 \n");
					if (Status==RUNNING)
						printf ("Waiting for stop trigger...\n");
					else
						printf ("\n\nTriggered!");
				}
			
/*			else
				{
					MoveCursor (Col, Row + 11);
					printf ("\nTriggered!");
				}*/
			
			}

		printf ("\n");
		MoveCursor (Col, Row + 13);
		printf ("Data collection terminated.");
		}

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







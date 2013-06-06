/*DaqInScan02.C****************************************************************

File:                         DaqSetSetpoints01.C

Library Call Demonstrated:    cbDaqSetSetpoints()

Purpose:                      Demonstrate the configuration and usage of setpoints
							  Including Adding the setpoint status to the scanlist and 
							  asynchronous reads of the setpoint status


Demonstration:                Displays the input channels data.
                              Calls cbGetStatus to determine the status
                              of the background operation. Updates the
                              display until a key is pressed.

Other Library Calls:          cbDaqInScan()
							  cbGetStatus()
                              cbStopBackground()
							  cbDConfigPort()
                              cbErrHandling()

Special Requirements:         Board 0 must support cbDaqInScan.


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

#define NUMCHANS  4
#define NUMPOINTS 10000
#define NUMSETPOINTS 3

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
	int PortNum, Direction;
	WORD *ADData;

	int SetpointCount;
	float LimitAArray[NUMSETPOINTS];
	float LimitBArray[NUMSETPOINTS];
	float *Reserved =NULL;
	int SetpointFlagsArray[NUMSETPOINTS];	
	int SetpointOutputArray[NUMSETPOINTS];	
	float Output1Array[NUMSETPOINTS];
	float Output2Array[NUMSETPOINTS];
	float OutputMask1Array[NUMSETPOINTS];
	float OutputMask2Array[NUMSETPOINTS];

	float *EngUnits;

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

	printf ("Demonstration of cbDaqSetSetpoint()\n\n");
	printf ("Data are being collected in the BACKGROUND, CONTINUOUSLY\n");


	/* load the arrays with values */
	ChanArray[0] = 0;	//CH0
	ChanTypeArray[0] = ANALOG | SETPOINT_ENABLE;    // Enable setpoint
	GainArray[0] = BIP10VOLTS;

	ChanArray[1] = 1;  //CH1
	ChanTypeArray[1] = ANALOG | SETPOINT_ENABLE;    // Enable setpoint
	GainArray[1] = BIP10VOLTS;

	ChanArray[2] = FIRSTPORTA;
	ChanTypeArray[2] = DIGITAL8 | SETPOINT_ENABLE;  // Enable setpoint
	GainArray[2] = NOTUSED;

	ChanArray[3] = 0;
	ChanTypeArray[3] = SETPOINTSTATUS;
	GainArray[3] = NOTUSED;

	/* load the setpoint configuration array with values 
	   For each channel that has the SETPOINT_ENABLE flag 
	   included, a setpoint entry must exist*/

	SetpointCount = NUMSETPOINTS;

	/* setpoint configurations for ChanArray[0]  (CH0)*/
	SetpointFlagsArray[0] = SF_LESSTHAN_LIMITA | SF_UPDATEON_TRUEANDFALSE;	
	SetpointOutputArray[0] = SO_DAC0;   // setpoint result outputs a value to Analog Out 0
	LimitAArray[0] = 3;					// if CH0 less than 3.0 volts apply output1, else apply output2
	LimitBArray[0] = 0;					// ignored when SF_LESSTHAN_LIMITA flag is used
	Output1Array[0] = 5;				// output 5.0 volts on Analog Out 0
	Output2Array[0] = -5;				// output -5.0 volts on Analog Out 0
	OutputMask1Array[0] = 0;			// ignored for 'SO_DAC0' output type 
	OutputMask2Array[0] = 0;			// ignored for 'SO_DAC0' output type 

	/* setpoint configurations for ChanArray[1] (CH1)*/
	SetpointFlagsArray[1] = SF_GREATERTHAN_LIMITB | SF_UPDATEON_TRUEANDFALSE;	
	SetpointOutputArray[1] = SO_FIRSTPORTC;	// setpoint result outputs a value to digital port C	
	LimitAArray[1] = 0;						// ignored when SF_GREATERTHAN_LIMITB flag is used				
	LimitBArray[1] = 2;						// if CH1 greater than 2.0 volts apply output1
	Output1Array[1] = 0x55;              	// output a bit pattern of 01010101 to digital port C
	Output2Array[1] = 0xAA;	                // output a bit pattern of 10101010 to digital port C
	OutputMask1Array[1] = 0x0F;            	// output the value of 'out1' on low nibble only
	OutputMask2Array[1] = 0x0F;           	// output the value of 'out2' on low nibble only 

	/* setpoint configurations for ChanArray[2] (FIRSTPORTA)*/
	SetpointFlagsArray[2] = SF_EQUAL_LIMITA | SF_UPDATEON_TRUEONLY;	
	SetpointOutputArray[2] = SO_TMR0;	// setpoint result outputs a value to Timer 0	
	LimitAArray[2] = 0x0F;				// if FIRSTPORTA equal 00001111 bit pattern apply output1				
	LimitBArray[2] = 2;					// ignored when SF_EQUAL_LIMITA flag is used
	Output1Array[2] = 100;				// output a 100Hz square wave on Timer 0
	Output2Array[2] = 0;				// ignored when SF_UPDATEON_TRUEONLY flag is used
	OutputMask1Array[2] = 0;			// ignored for 'SO_TMR0' output type 
	OutputMask2Array[2] = 0;			// ignored for 'SO_TMR0' output type 

	/* configure setpoints with cbDaqSetSetpoints()
		Parameters:
			BoardNum				:the number used by CB.CFG to describe this board
			LimitAArray[]			:array of LimitA values
			LimitBArray[]			:array of LimitB values
			SetpointFlagsArray[]	:array of Setpoint flags
			SetpointOutputArray[]   :array of output channels
			Output1Array[]			:array of output1 values
			Output2Array[]			:array of output2 values
			OutputMask1Array[]		:array of output masks for output1
			OutputMask2Array[]      :array of output masks for output2 
			SetpointCount           :Number of setpoints  */

	ULStat =cbDaqSetSetpoints (BoardNum, LimitAArray, LimitBArray, Reserved, SetpointFlagsArray, SetpointOutputArray,
							   Output1Array, Output2Array, OutputMask1Array, OutputMask2Array, SetpointCount);



	/* configure FIRSTPORTA and FIRSTPORTB for digital input */

	PortNum = FIRSTPORTA;
	Direction = DIGITALIN;
	ULStat = cbDConfigPort (BoardNum, PortNum, Direction);


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
	Rate = 1000;                                                /* sampling rate (samples per second) */
	Options = CONVERTDATA + BACKGROUND + CONTINUOUS;            /* data collection options */

	ULStat = cbDaqInScan(BoardNum, ChanArray, ChanTypeArray, GainArray, ChanCount, &Rate, &PreTrigCount, &TotalCount, ADData, Options);

	printf ("--------------------------------------------------------------------------------");
	printf ("| Your program could be doing something useful here while data are collected...|");
	printf ("--------------------------------------------------------------------------------");
	printf ("\nCollecting data...\n\n");
	printf ("Press any key to quit.\n\n");

	GetTextCursor (&Col, &Row);

	if(ULStat == NOERRORS)
		Status = RUNNING;

	EngUnits = malloc(sizeof(float));

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
					cbToEngUnits(BoardNum, GainArray[0] , ADData[DataIndex], EngUnits); 
					printf ("Channel 0   Data point: %3ld   ", DataIndex);
					printf ("  Value: %d   Voltage: %f \n",ADData[DataIndex], *EngUnits);
					DataIndex++;
					cbToEngUnits(BoardNum, GainArray[1] , ADData[DataIndex], EngUnits); 
					printf ("Channel 1   Data point: %3ld   ", DataIndex);
					printf ("  Value: %d   Voltage: %f \n",ADData[DataIndex], *EngUnits);
					DataIndex++;
					printf ("FIRSTPORTA  Data point: %3ld   ", DataIndex);
					printf ("  Value: 0x%X  \n",ADData[DataIndex]);
					DataIndex++;
					printf ("Setpoint status register: %3ld   ", DataIndex);
					printf ("  Value: 0x%X  ",ADData[DataIndex]);   // 32-bit counter
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

	cbWinBufFree(ADData);
	free(EngUnits);

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







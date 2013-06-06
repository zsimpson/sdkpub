/*DaqInScan03.C****************************************************************

File:                         DaqInScan03.C

Library Call Demonstrated:    cbDaqInScan(), FOREGROUND mode and cbGetTCValues()

Purpose:                      Synchronously scans Analog channels, Digital ports, and Thermocouple channels
                              in the foreground.

Demonstration:                Collects data on Analog Channels 4
							  FirstPortA, CJCs 0, 1  and Thermocouple channels 0, 1.

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


#define NUMCHANS    6
#define NUMTCCHANS  2
#define NUMPOINTS   10

void main ()
    {
    /* Variable Declarations */
    int ULStat = 0;
	int BoardNum = 0;
    int i, Options, SampleNum, ChanCount;
    long PreTrigCount, TotalCount, Rate;
    WORD ADData[NUMPOINTS*NUMCHANS];
    short ChanArray[NUMCHANS];
	short ChanTypeArray[NUMCHANS];
    short GainArray[NUMCHANS];
	int PortNum, Direction;
	int Scale, FirstPoint;
	long Count;
	float TempValArray[NUMTCCHANS * NUMPOINTS];
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

	//For accurate thermocouple readings, the CJC channels and TC channels must be associated
    //properly. The TC channels must immediately follow their associated CJCs in the channel array.
    //Other channel types may be placed in the channel array as long as they do not fall between a CJC channel and
    //its associated thermocouple channel.


    /* load the arrays with values */
    ChanArray[0] = 4;
	ChanTypeArray[0] = ANALOG;
    GainArray[0] = BIP10VOLTS;

    ChanArray[1] = FIRSTPORTA;
	ChanTypeArray[1] = DIGITAL8;
    GainArray[1] = NOTUSED;

    ChanArray[2] = 0;				// first bank CJC
	ChanTypeArray[2] = CJC;
    GainArray[2] = NOTUSED;

    ChanArray[3] = 0;
    ChanTypeArray[3] = TC;
    GainArray[3] = NOTUSED;

	ChanArray[4] = 1;				// second bank CJC
	ChanTypeArray[4] = CJC;
    GainArray[4] = NOTUSED;

    ChanArray[5] = 1;
    ChanTypeArray[5] = TC;
    GainArray[5] = NOTUSED;

    /* configure FIRSTPORTA  for digital input */
	PortNum = ChanArray[1];
    Direction = DIGITALIN;
    ULStat = cbDConfigPort (BoardNum, PortNum, Direction);


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



	/* Convert CJC  and TC reading to temperature
	Parameters:
            BoardNum    :the number used by CB.CFG to describe this board
            ChanArray[] :array of channel values
			ChanTypeArray[] : array of channel types
            ChanCount   :the number of channels
            ADData[]    :the collected raw data values
			FirstPoint  :the scan index that holds the first sample of the first channel to be converted.
            Count		:the number of samples per channel to be converted.
            Scale       :temperature scale (Celsius, Fahrenheit, Kelvin)
            TempValArray[]  :the array for the temperature data values */

	Count = NUMPOINTS ;
    FirstPoint = 0;
	Scale = CELSIUS;

	cbGetTCValues(BoardNum, ChanArray, ChanTypeArray, ChanCount, ADData, FirstPoint, Count , Scale, TempValArray);

    /* show the results */
    printf ("Here are the values returned \n\n");

    printf ("    Channel:   4    FIRSTPORTA    0	    1\n");
    printf ("ChannelType: ANALOG  DIGITAL8    TC        TC\n");
    printf ("       Gain:+-10V        -       -         -\n");
    printf ("             -----     -----   -----     ----- \n");

    i = 0;
    for (SampleNum=0; SampleNum<NUMPOINTS; SampleNum++)
        {
		printf ("             ");
        //for (Chan=0; Chan<NUMCHANS; Chan++)
		printf ("%5d    ",ADData[NUMCHANS*SampleNum]);
		printf ("%5d    ",ADData[NUMCHANS*SampleNum+1]);
		printf ("%.3f    ",TempValArray[NUMTCCHANS*SampleNum]);
		printf ("%.3f    ",TempValArray[NUMTCCHANS*SampleNum+1]);

		//i+=NUMCHANS;

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






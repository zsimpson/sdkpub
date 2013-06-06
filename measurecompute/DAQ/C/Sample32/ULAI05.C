/*ULAI05.C****************************************************************

File:                         ULAI05.C

Library Call Demonstrated:    cbAInScan() with Manual data conversion

Purpose:                      Demonstrate the manual conversion of data
                              values after they have been collected.

Demonstration:                Collects 10 data points from one analog input.
                              Data are collected as 16-bit values and
                              are converted to channel numbers and
                              12-bit data values using BASIC code.

Other Library Calls:          cbGetStatus()
                              cbStopBackground()
                              cbErrHandling()

Special Requirements:         Board 0 must have an A/D converter.
                              Analog signal on an input channel.

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


void main ()
    {
    /* Variable Declarations */
    int Row, Col, K;
    int BoardNum = 0;
    int ULStat = 0;
    int LowChan = 0;
    int HighChan = 0;
    int Gain = BIP5VOLTS;
    short Status = 0;
    int Channel;
    long CurCount, LastCount;
    long CurIndex;
    long Count = 10;
    long Rate = 3125;
    WORD ADData[10], ConvData[10];
    unsigned Options;
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
    printf ("Demonstration of cbAInScan() in BACKGROUND mode with manual data conversion\n\n");
    printf ("Collecting %ld data points.   Press any key to quit.\n\n", Count);
    printf ("Value: the 16-bit integer read from the board.\n");
    printf ("Converted value: the 12-bit value after the 4 channel bits have been removed.\n\n");
    GetTextCursor (&Col, &Row);
    printf ("Collecting data ");

    /* Collect the values with cbAInScan() in BACKGROUND mode
        Parameters:
             BoardNum    :the number used by CB.CFG to describe this board
             LowChan     :low channel of the scan
             HighChan    :high channel of the scan
             Count       :the total number of A/D samples to collect
             Rate        :sample rate in samples per second
             Gain        :the gain for the board
             ADData[] :the array for the collected data values
             Options     :data collection options */
    Options = NOCONVERTDATA + BACKGROUND;
    ULStat = cbAInScan (BoardNum, LowChan, HighChan, Count, &Rate,
                                            Gain, ADData, Options);

    /* During the BACKGROUND operation, check status */
    Status = RUNNING;
    while (!kbhit() && Status==RUNNING)
        {
        /* Check the status of the current background operation
        Parameters:
            BoardNum  :the number used by CB.CFG to describe this board
            Status    :current status of the operation (IDLE or RUNNING)
            CurCount  :current number of samples collected
            CurIndex  :index to the last data value transferred 
            FunctionType: A/D operation (AIFUNCTIOM)*/
        ULStat = cbGetStatus (BoardNum, &Status, &CurCount, &CurIndex,AIFUNCTION);
        
         /* check if there are data in the buffer */
        if (CurCount != LastCount)
            {
            printf ("*");
            LastCount = CurCount;
            }
        }

    /* check if the background operation has finished */
    if (Status == IDLE)
        printf (" Data Collection finished.");
    else
        printf (" Data collection terminated by the user.");

    /* show the collected data, manually convert the data to 12-bit and
       channel values */
    MoveCursor (Col, Row + 2);
    printf ("Point#    Value \n");
    printf ("-------   -------");

    /* show the 16-bit values that were collected */
    for (K = 0; K < (int)Count; K++)
        {
        MoveCursor (Col, Row + 4 + K);
        printf ("  %3u     %5u", K, ADData[K]);
        }

    /* manually convert the 16-bit values to 12-bit values */
    MoveCursor (Col + 20, Row + 2);
    printf ("Converted Value (manual)");
    MoveCursor (Col + 20, Row + 3);
    printf ("---------------");

    for (K = 0; K < (int)Count; K++)
        {
        /* find the channel number in the first 4 bits */
        Channel = ADData[K] & 15;

        /* retrieve the data value by shifting 4 places */
        ConvData[K] = (WORD)(ADData[K] >> 4);
        MoveCursor (Col + 25, Row + 4 + K);
        printf ("%u", ConvData[K]);
        }

    MoveCursor (Col, Row + 15);
    printf ("Data conversion completed manually.");


    /* the BACKGROUND operation must be explicitly stopped
        Parameters:
             BoardNum    :the number used by CB.CFG to describe this board 
             FunctionType: A/D operation (AIFUNCTIOM)*/  
    ULStat = cbStopBackground (BoardNum,AIFUNCTION);

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


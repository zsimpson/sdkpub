/*ULAI03.C****************************************************************

File:                         ULAI03.C

Library Call Demonstrated:    cbAInScan(), BACKGROUND mode

Purpose:                      Scans a range of A/D Input Channels
                              in the background.

Demonstration:                Displays the analog input on one channel.
                              Calls cbGetStatus to determine the status
                              of the background operation. Updates the
                              display until a key is pressed.

Other Library Calls:          cbGetStatus()
                              cbStopBackground()
                              cbErrHandling()

Special Requirements:         Board 0 must have an A/D converter.
                              Analog signals on an input channel.


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
    int Row, Col;
    int PrnNum=1000;
    int BoardNum = 0;
    int ULStat = 0;
    int LowChan = 0;
    int HighChan = 0;
    int Gain = BIP5VOLTS;
    short Status = 0;
    long CurCount;
    long CurIndex;
    int Count = 10000;
    long Rate = 3125;
    unsigned Options;
    WORD *ADData;
   float    RevLevel = (float)CURRENTREVNUM;

  /* Declare UL Revision Level */
   ULStat = cbDeclareRevision(&RevLevel);

    ADData = (WORD*)cbWinBufAlloc(10000);
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
    printf ("Demonstration of cbAInScan() in BACKGROUND mode\n\n");
    printf ("%d data points are being collected in the background. This program\n", Count);
    printf ("could be doing many other things right now, but it will display every\n");
    printf ("1000th data value collected.\n\n");
    printf ("10000 Points Being Collected:\n\n");
    printf ("Press any key to quit.\n\n");
    printf ("Point #   Value\n");
    printf ("-------   ------\n");
    GetTextCursor (&Col, &Row);

    /* Collect the values with cbAInScan() in BACKGROUND mode
        Parameters:
             BoardNum    :the number used by CB.CFG to describe this board
             LowChan     :low channel of the scan
             HighChan    :high channel of the scan
             Count       :the total number of A/D samples to collect
             Rate        :sample rate in samples per second
             Gain        :the gain for the board
             ADData[]    :the array for the collected data values
             Options     :data collection options */
    Options = CONVERTDATA + BACKGROUND + SINGLEIO;
    ULStat = cbAInScan (BoardNum, LowChan, HighChan, Count, &Rate,
                                            Gain, ADData, Options);

    /* During the BACKGROUND operation, check the status, print every ten values */
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
        
        /* Check if there are data in the buffer */
        if (CurCount > 0)
            {
            MoveCursor (Col + 25, Row - 4);
            printf ("%ld", CurCount);
            if (CurCount > PrnNum)    /* display every 100th data point */
                {
                if (CurCount > 0)
                    {
                    MoveCursor (Col, Row - 1 + (PrnNum/ 1000));
                    printf ("  %4d    %5u",  PrnNum, ADData[PrnNum]);
                    }
                PrnNum = PrnNum+1000;
                }
            }
        }
    MoveCursor (Col + 30, Row - 4);
    if (Status == IDLE)
        printf ("  Data Collection finished.");
    else
        printf ("Data collection interrupted by user.");

    /* the BACKGROUND operation must be explicitly stopped
        Parameters:
             BoardNum    :the number used by CB.CFG to describe this board 
             FunctionType: A/D operation (AIFUNCTIOM)*/  
    ULStat = cbStopBackground (BoardNum,AIFUNCTION);

    MoveCursor (1, 22);
    printf ("\n");

    GetTextCursor (&Col, &Row);
    cbWinBufFree((int)ADData);
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







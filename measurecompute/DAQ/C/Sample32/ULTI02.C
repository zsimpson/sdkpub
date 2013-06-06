/* ULTI02.C****************************************************************

File:                         ULTI02.C

Library Call Demonstrated:    cbTInScan()

Purpose:                      Scans multiplexer input channels.

Demonstration:                Displays the temperature inputs on a range of
                              channels until a key is pressed.

Other Library Calls:          cbErrHandling()

Special Requirements:         Board 0 must have an A/D converter with an
                              attached EXP board. Thermocouples must be
                              wired to mux channels 0 and 1.

Copyright (c) 1995-2002, Measurement Computing Corp.
All Rights Reserved.
**************************************************************************/


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
    int Row, Col, I;
    int ULStat;
    int BoardNum = 0;
    int HighMUX, LowMUX, NumChans, ADChan, LowChan, HighChan;
    int Scale, Options;
    float DataBuffer[3];
    float    RevLevel = (float)CURRENTREVNUM;
	short InfoType, DevNum, ConfigItem;
	int UsesEXPs = 0;

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

	/* 
	   Determine if board uses expansiong boards for temperature measurements
	   Some boards, such as the CIO-DAS-TC, cannot use EXP expansion boards
	*/
	InfoType = BOARDINFO;
	DevNum = 0;
	ConfigItem = BIUSESEXPS;
	ULStat = cbGetConfig(InfoType, BoardNum, DevNum, ConfigItem, &UsesEXPs);
	if (ULStat) UsesEXPs = 0;

    /* set up the display screen */
    ClearScreen();
    printf ("Demonstration of cbTInScan()\n\n");
    printf ("Press any key to quit.\n\n");

    /* collect the data with cbTInScan()
       Input values will be collected from a thermocouple into DataBuffer
       The data value will be updated and displayed until a key is pressed.
       Parameters:
          BoardNum    :the number used by CB.CFG to describe this board
          LowMUX      :the starting channel of the scan
          HighMUX     :the ending channel of the scan
          Scale       :temperature scale (Celsius, Fahrenheit, Kelvin)
          DataBuffer[]:the array where the temperature values are collected
          Options     :      */
    Scale = FAHRENHEIT;
    ADChan = 0;    /* channel on the A/D */
    LowMUX = 0;
    HighMUX = 1;
	if (UsesEXPs>0)
		{
		LowChan=(ADChan + 1)* 16 + LowMUX;
		HighChan=(ADChan + 1)* 16 + HighMUX;
		}
	else /* is a DAS-TC or DAS-TEMP */
		{
		LowChan=LowMUX;
		HighChan=HighMUX;
		}

    NumChans = HighMUX - LowMUX + 1;
    Options = 0;
    printf ("Scanning from channel %1u to channel %1u\n\n", LowMUX, HighMUX);
    printf ("The temperatures at the thermocouples:\n\n");
    GetTextCursor (&Col, &Row);

    while (!kbhit())
        {
        MoveCursor (Col, Row);

        ULStat = cbTInScan (BoardNum, LowChan, HighChan, Scale,
                            &DataBuffer[1], Options);

        for (I = 1; I < NumChans + 1; I++)
            {
            if (I == 1)
                printf ("Low Channel  (%1u):  %6f degrees F\n", LowMUX, DataBuffer[I]);
            else if (I == NumChans)
                printf ("High Channel (%1u):  %6f degrees F\n", HighMUX, DataBuffer[I]);
            else
                printf ("                   %6f degrees F\n", DataBuffer[I]);
            }
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


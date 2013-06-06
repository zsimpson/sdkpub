/* ULTI01.C****************************************************************

File:                         ULTI01.C

Library Call Demonstrated:    cbTIn()

Purpose:                      Reads a multiplexer input channel.

Demonstration:                Displays the temperature input on a MUX
                              channel until a key is pressed.

Other Library Calls:          cbErrHandling()

Special Requirements:         Board 0 must have an A/D converter with an
                              attached EXP board. A thermocouple must be
                              attached to mux channel 0.

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
    int Row, Col;
    int ULStat;
    int BoardNum = 0;
    int Scale, Options, ADChan, MUXChan, Chan;
    float TempValue;
    char TUnits[11];
    float    RevLevel = (float)CURRENTREVNUM;
	int UsesEXPs=0;
	short InfoType, ConfigItem, DevNum;
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
    printf ("Demonstration of cbTIn()\n\n");
    printf ("Press any key to quit.\n\n");
    printf ("The temperature at the thermocouple is:\n\n");
    GetTextCursor (&Col, &Row);

    /* collect the data with cbTIn()
        Input values will be collected from a thermocouple into TempValue
        The data value will be updated and displayed until a key is pressed. */

    while (!kbhit())
        {
        MoveCursor (Col, Row);
        for (Scale = 0; Scale < 3; Scale++)
            {
            /* Parameters:
                 BoardNum    :the number used by CB.CFG to describe this board
                 Chan        :the input channel
                 Scale       :temperature scale (Celsius, Fahrenheit, Kelvin)
                 TempValue   :the temperature value collected
                 Options              */

            ADChan=0;
            MUXChan = 0;
			if (UsesEXPs>0)
				Chan= (ADChan + 1) * 16 + MUXChan;
			else /* is a DAS-TC or DAS-TEMP */
				Chan= MUXChan;

            Options = 0;
            ULStat = cbTIn (BoardNum, Chan, Scale, &TempValue, Options);

            if (Scale == 0)
                strcpy (TUnits, "Celsius");
            else if (Scale == 1)
                strcpy (TUnits, "Fahrenheit");
            else if (Scale == 2)
                strcpy (TUnits, "Kelvin");

            printf (" %6f  degrees", TempValue);
            printf (" %s \n", TUnits);
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


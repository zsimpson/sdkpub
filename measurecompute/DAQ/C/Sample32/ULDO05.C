/*ULDO05.C****************************************************************

File:                         ULDO05.C

Library Call Demonstrated:    cbDBitOut()

Purpose:                      Sets the state of a single digital output bit.

Demonstration:                Writes a specified bit value to AUXPORT.

Other Library Calls:          cbErrHandling()
                              cbGetConfig() using DIGITALINFO
                              cbDConfigPort()

Special Requirements:         Board 0 must have a digital output port.


Copyright (c) 1995-2003, Measurement Computing Corp.
All Rights Reserved.
***************************************************************************/


/* Include files */

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <assert.h>
#include "..\cbw.h"


/* Prototypes */
void ClearScreen (void);
void GetTextCursor (int *x, int *y);
void MoveCursor (int x, int y);


void main ()
    {
    /* Variable Declarations */
    int Row, Col;
    int BoardNum = 0;
    int ULStat = 0;
    int PortType;
    int DataValue;
    int BitLevel;
    int BitNum;
    WORD BitValue;
    int hilo;
    int devNum=0;
    int inmask=0, outmask=0;

    /* Initiate error handling
        Parameters:
            PRINTALL :all warnings and errors encountered will be printed
            DONTSTOP :continue operatioin even after error. */
   cbErrHandling (PRINTALL, DONTSTOP);

    /* Determine if board has AUXPORT */
    /* Parameters:
         DIGITALINFO : information about digital devices on the board 
         BoardNum    : the number used by CB.CFG to describe this board
         devNum      : 0-based digital device index
         DIDEVTYPE   : retrieve type of digital device - AUXPORT, FIRSTPORTA, ...
         PortType    : return value for type of device
     */
     PortType = 0;
     devNum = 0;    /*AUXPORT, if present, will have device index 0 */
     ULStat = cbGetConfig(DIGITALINFO, BoardNum, 0, DIDEVTYPE, &PortType);
     assert(PortType==AUXPORT);
     if (PortType != AUXPORT)
         {
         printf( "ERROR: This board does NOT have an AUXPORT.");
         exit(1);
         }

     /* Check if AUXPORT needs configuring */
     /* Parameters:
         DIGITALINFO : information about digital devices on the board 
         BoardNum    : the number used by CB.CFG to describe this board
         devNum      : 0-based digital device index
         DIINMASK/DIOUTMASK   : get input/output bitmask configuration for port
         mask    : bitmask indicating corresponding bit is in direction of ConfigItem(DIINMASk or DIOUTMASK)
     */
     inmask=0; 
     outmask=0;
     ULStat = cbGetConfig(DIGITALINFO, BoardNum, devNum, DIINMASK, &inmask);
     assert(ULStat==NOERRORS);

     ULStat = cbGetConfig(DIGITALINFO, BoardNum, devNum, DIOUTMASK, &outmask);
     assert(ULStat==NOERRORS);

     /* Only non-configurable AUXPORT's have overlapping input and output bitmasks */
     if (0 == (inmask & outmask))  
         cbDConfigPort(BoardNum, AUXPORT, DIGITALOUT);


    /* set up the display screen */
    ClearScreen();
    printf ("Demonstration of cbDBitOut() and AUXPORT.\n\n");

    GetTextCursor (&Col, &Row);


    /* get a user value to write to the port */
    DataValue = 4;
    while (DataValue > 3)
        {
        MoveCursor (Col, Row);
        printf ("Which bit would you like to set(0 to 3)? --> ");
        scanf ("%i", &DataValue);
        }

    BitLevel = 2;
    while (BitLevel > 1)
        {
        MoveCursor (Col, Row+2);
        printf ("Set high(1) or low(0)? --> ");
        scanf ("%i", &BitLevel);
        }

    MoveCursor (Col, Row + 4);
    printf ("Bit %u on AUXPORT was set to a %u.\n\n",DataValue,BitLevel);

    printf ("Bit   Value (X = Don't Care)\n");

    /* write the value to AUXPORT as single bits */
    for (BitNum = 0; BitNum < 4; BitNum++) /* loop through the bits */
        {
        /* parse data value into individual bits */
        hilo = 'X';
        if ((BitNum == DataValue) && (BitLevel == 1))
            {
            BitValue = 1;
            hilo = '1';
            }
        else if ((BitNum == DataValue) && (BitLevel == 0))
            {
            BitValue = 0;
            hilo = '0';
            }

        printf (" %u      %c\n", BitNum, hilo);

        /* write BitValue to BitNum of AUXPORT
            Parameters:
                BoardNum    :the number used by CB.CFG to describe this board
                PortType    :AUXPORT
                BitNum      :the number of the bit to be set to BitValue
                BitValue    :the value written to the port   */

        PortType=AUXPORT;
        if (BitNum == DataValue)
            ULStat = cbDBitOut (BoardNum, PortType, BitNum, BitValue);
        }

    MoveCursor (1, 20);
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






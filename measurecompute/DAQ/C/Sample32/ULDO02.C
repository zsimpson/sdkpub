/*ULDO02.C****************************************************************

File:                         ULDO02.C

Library Call Demonstrated:    cbDBitOut()

Purpose:                      Sets the state of a single digital output bit.

Demonstration:                Configures the first and second 8255 compatible
                              ports (usually FIRSTPORTA and B) for output and
                              writes a bit value to the port.

Other Library Calls:          cbDConfigPort()
                              cbGetConfig() using DIGITALINFO and BOARDINFO
                              cbErrHandling()

Special Requirements:         Board 0 must have a digital output port.


Copyright (c) 1995-2002, Measurement Computing Corp.
All Rights Reserved.
***************************************************************************/


/* Include files */
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include "..\cbw.h"


/* Prototypes */
void ClearScreen (void);
void GetTextCursor (int *x, int *y);
void MoveCursor (int x, int y);


void main ()
    {
    /* Variable Declarations */
    int Row, Col;
    int BoardNum=0, DevNum=0;
    int ULStat = 0;
    int PortNum, PortType, Direction, FirstPort;
    int DataValue;
    int BitLevel;
    int BitNum, FirstBit;
    WORD BitValue;
    int hilo;
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
    printf ("Demonstration of cbDBitOut()\n\n");

    GetTextCursor (&Col, &Row);

    /* get the first port on the device - some devices (such as the
       USB-ERB08 and USB-SSR08) don't have FIRSTPORTA, but do have
       FIRSTPORTCL and FIRSTPORTCH.
    
      Parameters:
         DIGITALINFO : information about digital devices on the board 
         BoardNum    : the number used by CB.CFG to describe this board
         devNum      : 0-based digital device index
         DIDEVTYPE   : retrieve type of digital device - AUXPORT, FIRSTPORTA, ...
         FirstType    : return value for type of device
     */  
    DevNum = 0;
    FirstPort = 0;
    ULStat = cbGetConfig(DIGITALINFO, BoardNum, DevNum, DIDEVTYPE, &FirstPort);
    if (ULStat!=NOERRORS)
       exit(ULStat);

    switch (FirstPort)
        {
        case FIRSTPORTA:
            FirstBit = 0;
            break;
            
        case FIRSTPORTB:
            FirstBit = 8;
            break;

        case FIRSTPORTCL:
            FirstBit = 16;
            break;
            
        case FIRSTPORTCH:
            FirstBit = 20;
            break;

        default:
            FirstBit = 0;
            break;
        }


    /* configure the first port for digital output
        Parameters:
            BoardNum    :the number used by CB.CFG to describe this board.
            PortNum     :the output port
            Direction   :sets the port for input or output */

	PortNum = FirstPort;
    Direction = DIGITALOUT;
    ULStat = cbDConfigPort (BoardNum, FirstPort, Direction);

    /* if the first port is FIRSTPORTCL, configure FIRSTPORTCH, too */
    if (FirstPort==FIRSTPORTCL)
        ULStat = cbDConfigPort (BoardNum, FirstPort+1, Direction);

    /* get a user value to write to the port */
    DataValue = 8;
    while (DataValue > 7)
        {
        MoveCursor (Col, Row);
        printf ("Which bit would you like to set(0 to 7)? --> ");
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
    printf ("Bit %u of the first port was set to a %u.\n\n",DataValue,BitLevel);

    printf ("Bit   Value (X = Don't Care)\n");


	if(PortNum == AUXPORT)
		PortType = AUXPORT;
	else
		PortType = FIRSTPORTA;

    /* write the value to the first port as single bits */
    for (BitNum = 0; BitNum < 8; BitNum++) /* loop through the bits */
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

        /* write BitValue to BitNum of the first port
            Parameters:
                BoardNum    :the number used by CB.CFG to describe this board
                PortType    :must be FIRSTPORTA or AUXPORT
                BitNum      :the number of the bit to be set to BitValue
                BitValue    :the value written to the port   
        
        For boards whose first port is not FIRSTPORTA (such as the USB-ERB08
        and the USB-SSR08) offset the BitNum by FirstBit */

        if (BitNum == DataValue)
            ULStat = cbDBitOut (BoardNum, PortType, FirstBit+BitNum, BitValue);
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






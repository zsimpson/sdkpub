/*ULDI04.C****************************************************************

File:                         ULDI04.C

Library Call Demonstrated:    cbDIn()

Purpose:                      Reads a digital input port.

Demonstration:                Configures AUXPORT for input and
                              reads the value on the port.

Other Library Calls:          cbErrHandling()
                              cbGetConfig() using DIGITALINFO
                              cbDConfigPort()

Special Requirements:         Board 0 must have a digital input port.

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
    int Row, Col, I;
    int BoardNum = 0;
    int ULStat = 0;
    int PortNum;
    int PowerVal, BitValue;
    int Zero = 0;
    int One = 1;
    WORD DataValue;
    int devNum=0, PortType=0;
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
     devNum = 0;
     PortType = 0;
     cbGetConfig(DIGITALINFO, BoardNum, devNum, DIDEVTYPE, &PortType);
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

     assert(inmask!=0 || outmask!=0);

     /* Only non-configurable AUXPORT's have overlapping input and output bitmasks */
     if (0 == (inmask & outmask))  
      cbDConfigPort(BoardNum, AUXPORT, DIGITALIN); 
      

    /* set up the display screen */
    ClearScreen();
    printf ("Demonstration of cbDIn()\n\n");
    printf ("\nYou may change a bit by applying a TTL high or");
    printf ("\na TTL low to the corresponding pin# on AUXPORT.\n\n");
    printf ("The 4 bits on AUXPORT are: \n");
    printf ("                         BIT#:  0  1  2  3 \n");
    GetTextCursor (&Col, &Row);

    PortNum = AUXPORT;
     while (!kbhit())
        {
         /* read the 4 bits digital input and display
            Parameters:
                BoardNum    :the number used by CB.CFG to describe this board
                PortNum     :the input port
                DataValue   :the value read from the port   */
        ULStat = cbDIn(BoardNum, PortNum, &DataValue);

        /* display the value collected from the port */
        MoveCursor (Col +46,Row);
        printf ("Port Value: %u ", DataValue);

        /* parse DataValue into bit values to indicate on/off status */
        MoveCursor (Col + 24, Row);
        for (I = 0; I < 4; I++)
            {
            BitValue = Zero;
            PowerVal = 1 << I;
            if (I == 0)
                printf("Value: ");
            if (DataValue & PowerVal)
                BitValue = One;
            printf (" %u ", BitValue);
            }

        printf ("\n\n\nPress any key to quit.\n\n");
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






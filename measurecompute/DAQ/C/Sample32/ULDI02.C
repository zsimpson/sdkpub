/*ULDI02.C****************************************************************

File:                         ULDI02.C

Library Call Demonstrated:    cbDBitIn()

Purpose:                      Reads a digital input port.

Demonstration:                Configures the first configurable
                              port (usually FIRSTPORTA) for input and
                              reads the bit value on the port. Unstable bit
                              values are due to the nature of
                              the input ports when left floating.

Other Library Calls:          cbDConfigPort()
                              cbGetConfig() using DIGITALINFO and BOARDINFO
                              cbErrHandling()

Special Requirements:         Board 0 must have a digital input port.


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
    int BoardNum=0, DevNum=0;
    int ULStat=0;
    int PortNum, PortType, Direction, FirstPort;
    int BitNum, FirstBit, MaxBits;
    WORD BitValue;
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

    

    /* get the first port on the device - some devices (such as the
       USB-ERB08 and USB-SSR08) don't have FIRSTPORTA, but do have
       FIRSTPORTCL.
    
      Parameters:
         DIGITALINFO : information about digital devices on the board 
         BoardNum    : the number used by CB.CFG to describe this board
         devNum      : 0-based digital device index
         DIDEVTYPE   : retrieve type of digital device - AUXPORT, FIRSTPORTA, ...
         FirstPort   : return value for type of device
     */  
    DevNum = 0;
    PortType = 0;
    ULStat = cbGetConfig(DIGITALINFO, BoardNum, DevNum, DIDEVTYPE, &FirstPort);
    

    switch (FirstPort)
        {
        case FIRSTPORTA:
            FirstBit = 0;
            MaxBits = 8;
            break;
            
        case FIRSTPORTB:
            FirstBit = 8;
            MaxBits=8;
            break;

        case FIRSTPORTCL:
            FirstBit = 16;
            MaxBits = 8;
            break;
            
        case FIRSTPORTCH:
            FirstBit = 20;
            MaxBits = 4;
            break;

        default:
            FirstBit = 0;
            MaxBits = 8;
            break;
        }

    /* set up the display screen */
    ClearScreen();
    printf ("Demonstration of cbDBitIn()\n\n");
    printf ("Press any key to quit.\n\n");
    printf ("You may change a bit by applying a TTL high or\n");
    printf ("a TTL low to the corresponding pin on port A.\n\n");

    
    printf ("The first 8 bit values are: ");
    printf ("0  1  2  3  4  5  6  7 \n");
        
    GetTextCursor (&Col, &Row);


    /* configure the first port(usually FIRSTPORTA) for input
        Parameters:
            BoardNum    :the number used by CB.CFG to describe this board.
            PortNum     :the input port
            Direction   :sets the port for input or output */
    
    PortNum = FirstPort;
    Direction = DIGITALIN;
    ULStat = cbDConfigPort (BoardNum, PortNum, Direction);
      
	if(PortNum == AUXPORT)
		PortType = AUXPORT;
	else
		PortType = FIRSTPORTA;

    while (!kbhit() && ULStat==NOERRORS)
        {
        MoveCursor (Col + 27, Row);

        for (BitNum = 0; BitNum < MaxBits; BitNum++)
            {
            /* read the input bits from the ports and display
               Parameters:
                    BoardNum    :the number used by CB.CFG to describe this board
                    PortType    :must be FIRSTPORTA or AUXPORT
                    BitNum      :the input port
                    BitValue    :the value read from the port 
                    
            For boards whose first port is not FIRSTPORTA (such as the USB-ERB08
            and the USB-SSR08) offset the BitNum by FirstBit*/
            ULStat = cbDBitIn (BoardNum, PortType, FirstBit + BitNum, &BitValue);

            printf (" %u ", BitValue);
            }
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



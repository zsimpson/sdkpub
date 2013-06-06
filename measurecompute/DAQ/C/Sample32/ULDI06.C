/*ULDIO_01.C*******************************************************************

File:                         ULDI06.C

Library Call Demonstrated:    cbDConfigBit()

Purpose:                      Reads the status of a single bit within a digital
                              port. 

Demonstration:                configures a single bit (within a digital port) 
                              for input and reads the bit status
                              
Other Library Calls:          cbErrHandling()
                              cbDBitIn()
                              cbGetConfig() using DIGITALINFO
                 

Special Requirements:         Board 0 must have a digital port that supports
                              cbDConfigBit function.


Copyright (c) 1995-2003, Measurement Computing Corp.
All Rights Reserved.
******************************************************************************/


/* Include files */
#include <windows.h>
#include <stdio.h>
#include <conio.h>
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
   int PortType, Direction;
   int BitNum= 0;
   WORD BitValue;
   int devNum=0;
   int inmask=0, outmask=0;

   /* Initiate error handling
        Parameters:
            PRINTALL :all warnings and errors encountered will be printed
            DONTSTOP :continue operatioin even after error. */
   cbErrHandling (PRINTALL, DONTSTOP);

   /* set up the display screen */
   ClearScreen();
   printf ("Demonstration of cbDConfigBit()\n\n");
   printf ("Press any key to quit.\n\n");
   printf ("You may change the bit state by applying a TTL high or\n");
   printf ("a TTL low to the corresponding pin on the port .\n\n");

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
     ULStat = cbGetConfig(DIGITALINFO, BoardNum, devNum, DIDEVTYPE, &PortType);
     assert(PortType==AUXPORT);
     if (PortType != AUXPORT)
         {
         printf( "ERROR: This board does NOT have an AUXPORT.");
         exit(1);
         }

    /* Check if AUXPORT needs configuring */
     inmask=0;
     outmask=0;
     ULStat = cbGetConfig(DIGITALINFO, BoardNum, devNum, DIINMASK, &inmask);
     assert(ULStat==NOERRORS);

     ULStat = cbGetConfig(DIGITALINFO, BoardNum, devNum, DIOUTMASK, &outmask);
     assert(ULStat==NOERRORS);

     assert(inmask!=0 || outmask!=0);

     /* Only non-configurable AUXPORT's have overlapping input and output bitmasks */
     if (inmask & outmask)  
     {
        printf("ERROR: AUXPORT is non-configurable.");
        exit(1);
     }
   
   /* configure a single bit for input or output
        Parameters:
            BoardNum    :the number used by CB.CFG to describe this board.
            PortType    :the port for which to configure the bit
            BitNum      :the bit to configure
            Direction   :sets the bit for input or output*/
   
   /* NOTE: Some boards don't support cbDConfigBit function. See your hardware
            manual or board specific information*/
     
   PortType = AUXPORT;
   BitNum = 0;
   Direction = DIGITALIN;
   ULStat = cbDConfigBit (BoardNum, PortType, BitNum,Direction);
   printf ("Bit %d state is: ", BitNum);
   GetTextCursor (&Col, &Row);

   while (!kbhit())
      {
      MoveCursor (Col + 1, Row);
        
      /* read a single bit status from the digital port
         Parameters:
                    BoardNum    :the number used by CB.CFG to describe this board
                    PortType    :the digital I/O port type
                    BitNum      :the bit to read
                    BitValue    :the value read from the port   */
      ULStat = cbDBitIn (BoardNum, PortType, BitNum, &BitValue);
   
      printf (" %d ", BitValue);
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



/*ULAI07.C****************************************************************

File:                         ULAI07.C

Library Call Demonstrated:    cbATrig()

Purpose:                      Waits for a specified analog input channel
                              go above or below a specified value.

Demonstration:                Reads the analog input on a user-specified
                              channel until the user-specified trigger
                              value is detected.

Other Library Calls:          cbErrHandling()

Special Requirements:         Board 0 must have an A/D converter.

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
WORD GetTrigCounts(int bd, int gain, float val);


void main ()
    {
    /* Variable Declarations */
    char TrigKind;
    int Row, Col;
    int BoardNum = 0;
    int ULStat = 0;
    int Chan, Gain;
    WORD DataValue;
    int TrigType;
    WORD TrigValue;
    float EngUnits;
    float RevLevel = (float)CURRENTREVNUM;

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
    printf ("Demonstration of cbATrig()\n\n");
    GetTextCursor (&Col, &Row);

    MoveCursor (Col, Row + 1);
    printf ("Enter the channel to display:      ");
    MoveCursor (Col + 31, Row + 1);
    scanf ("%i", &Chan);
    MoveCursor (Col, Row + 3);
    printf ("Enter the threshold value (-5 to +5V):     ");
    MoveCursor (Col + 39, Row + 3);
    scanf ("%f", &EngUnits);

   /* convert voltage to counts */
   Gain = BIP5VOLTS;
   

   TrigValue = GetTrigCounts(BoardNum, Gain, EngUnits);

    /* if the value is not at the extremes, ask which side to trigger */
    MoveCursor (Col, Row + 5);
    printf ("Should the data value be ABOVE or BELOW this threshold (A/B): ");
    TrigKind = (char)getch();
    MoveCursor (Col + 62, Row + 5);
    printf ("%c", TrigKind);

    switch (TrigKind)
        {
        case 'A':
        case 'a':
            TrigType = TRIGABOVE;
            break;
        case 'B':
        case 'b':
            TrigType = TRIGBELOW;
            break;
        default:
            break;
        }

    /* monitor the channel with cbATrig()
        Parameters:
            BoardNum    :the number used by CB.CFG to describe this board
            Chan        :the input channel number
            TrigType    :specifies whether the trigger is to be above or
                         below TrigValue
            TrigValue   :the threshold value that will cause the trigger
            Gain        :the gain value
            DataValue   :the input value read from Chan */

    MoveCursor (Col , Row + 7);
    printf ("Waiting for the trigger value...");

    ULStat = cbATrig (BoardNum, Chan, TrigType, TrigValue, Gain, &DataValue);

    MoveCursor (Col, Row + 9);
    printf ("The value that caused the trigger was %u ", DataValue);

    MoveCursor (1, 20);
    printf ("\n");
}


/***************************************************************************
*
* Name:     GetTrigCount   
* Arguments: bd - board or device number
*            val - trigger value in engineering units
*            gain - range 
* Returns:   ---
*
* Converts the trigger value in engineerin units to binary counts
*
***************************************************************************/
WORD GetTrigCounts(int bd, int gain, float val)
{
   WORD counts=0;
   float fcounts = 0.0f;
   int FSCounts=0;
   float FSEngUnits=0.0f;
   int ulstat = NOERRORS;

   //test if gain is bipolar or unipolar
   ulstat = cbToEngUnits(bd, gain, FSCounts, &FSEngUnits);
   if (FSEngUnits < 0.0f)
      {
      //'gain' is bipolar
      //now, test bitness
      FSCounts = 0x0fff;  //max 12-bit value
      ulstat = cbToEngUnits(bd, gain, FSCounts, &FSEngUnits);
      if (FSEngUnits<0.0f)
         {
         //must be 16-bit A/D...
         FSCounts = 0xffff;
         ulstat = cbToEngUnits(bd, gain, FSCounts, &FSEngUnits);
         }

      fcounts = (FSCounts/2.0f)*(1.0 + val/FSEngUnits);
      counts = fcounts;
      }
   else
      {
      //'gain' is unipolar
      // now, test bitness...
      FSCounts = 0x0fff; //max 12-bit value
      ulstat = cbToEngUnits(bd, gain, FSCounts, &FSEngUnits);
      ulstat = cbToEngUnits(bd, gain, FSCounts+0x1000, &fcounts);
      if (fcounts >= 2.0f*FSEngUnits)
         {
         //must be 16-bit A/D...
         FSCounts = 0xffff; //max 16-bit value
         ulstat = cbToEngUnits(bd, gain, FSCounts,&FSEngUnits);
         }

      fcounts = FSCounts*val/FSEngUnits;
      counts = fcounts;
      }

   if (counts > FSCounts)
      counts = FSCounts;

   return counts;
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



/*ULGT03.C****************************************************************

File:                         ULGT03.C

Library Call Demonstrated:    cbGetConfig()

Purpose:                      Prints a list of all boards installed in
                              the system and their base addresses.  Also
                              prints the addresses of each digital and
                              counter device on each board and any EXP
                              boards that are connected to A/D channels.

Other Library Calls:          cbErrHandling(), cbGetBoardName()

Special Requirements:         ---

Copyright (c) 1995-2002, Measurement Computing Corp.
All Rights Reserved.
***************************************************************************/


/* Include files */
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "..\cbw.h"


/* Prototypes */
void PrintADInfo (int BoardNum);
void PrintDAInfo (int BoardNum);
void PrintDigInfo (int BoardNum);
void PrintCtrInfo (int BoardNum);
void PrintExpInfo (int BoardNum);


void ClearScreen (void);
void MoveCursor (int x, int y);
void GetTextCursor (int *x, int *y);

int NumADChans[10];

void main ()
    {
    /* Variable Declarations */
    int  ULStat = 0;
    int  BoardType, NumBoards, BaseAdr, i;
    char BoardNameStr[BOARDNAMELEN];
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
    printf ("Demonstration of cbGetConfig()\n\n");

    printf ("List of Installed Boards:\n\n");

    /* Get the number of boards installed in system */
    cbGetConfig (GLOBALINFO, 0, 0, GINUMBOARDS, &NumBoards);

    for (i=0; i<NumBoards; i++)
        {
         /* Get board type of each board */
        cbGetConfig (BOARDINFO, i, 0, BIBOARDTYPE, &BoardType);

        /* If a board is installed */
        if (BoardType > 0)
            {
             /* Get the board's name */
            cbGetBoardName (i, BoardNameStr);
            printf ("    Board #%d = %s\n", i, BoardNameStr);

            /* Get the board's base address */
            cbGetConfig (BOARDINFO, i, 0, BIBASEADR, &BaseAdr);
            printf ("        Base Address = 0x%x\n",BaseAdr);

			   PrintADInfo (i);
			   PrintDAInfo (i);
            PrintDigInfo (i);
            PrintCtrInfo (i);
            PrintExpInfo (i);
            printf ("\n");
            }
        }
    printf ("\n\n");
    return;
}

void
PrintADInfo (int BoardNum)
{
	int NumDevs;

	cbGetConfig (BOARDINFO, BoardNum, 0, BINUMADCHANS, &NumDevs);

	NumADChans[BoardNum]=NumDevs;
	printf ("        Number of A/D channels: %d \n", NumDevs);
	return;
}

void
PrintDAInfo (int BoardNum)
{
	int NumDevs;

	cbGetConfig (BOARDINFO, BoardNum, 0, BINUMDACHANS, &NumDevs);

	printf ("        Number of D/A channels: %d \n", NumDevs);
	return;
}

void
PrintDigInfo (int BoardNum)
{
    int NumDevs, i, NumBits;

    /* get the number of digital devices for this board */
    cbGetConfig (BOARDINFO, BoardNum, 0, BIDINUMDEVS, &NumDevs);

    for (i=0; i<NumDevs; i++)
        {
        /* For each digital device, get the number of bits */
        cbGetConfig (DIGITALINFO, BoardNum, i, DINUMBITS, &NumBits);
        printf ("        Digital Device #%d : %d bits)\n", i, NumBits);
        }
    return;
}



void
PrintCtrInfo (int BoardNum)
{
    int NumDevs;

    /* Get the number of counter devices for this board */
    cbGetConfig (BOARDINFO, BoardNum, 0, BICINUMDEVS, &NumDevs);
    printf ("        Counter Devices : %d\n", NumDevs);
    
    return;
}



void
PrintExpInfo (int BoardNum)
{
   int NumDevs, DevNum;
   int BoardType, ADChan1, ADChan2;

   cbGetConfig (BOARDINFO, BoardNum, 0, BINUMEXPS, &NumDevs);
	for (DevNum=0; DevNum<NumDevs; ++DevNum)
      {
      cbGetConfig (EXPANSIONINFO, BoardNum, DevNum, XIBOARDTYPE, &BoardType);
      cbGetConfig (EXPANSIONINFO, BoardNum, DevNum, XIMUX_AD_CHAN1, &ADChan1);
      
      if (BoardType==770)
         {
         /* it's a CIO-EXP32 occupying 2 A/D channels*/
         cbGetConfig (EXPANSIONINFO, BoardNum, DevNum, XIMUX_AD_CHAN2, &ADChan2);
         printf ("        A/D channels #%d and #%d connected to EXP(devID=%d)\n", ADChan1, ADChan2, BoardType);
         }
      else
         printf ("        A/D chan #%d connected to EXP(devID=%d)\n", ADChan1, BoardType);
      }
      
    return;
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






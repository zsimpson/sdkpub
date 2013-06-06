/*ULGT04.C****************************************************************

File:                         ULGT04.C

Library Call Demonstrated:    cbGetBoardName()

Purpose:                      Prints a list of all boards installed in
                              the system.  Prints a list of all supported
                              boards.

Other Library Calls:          cbErrHandling(), cbGetConfig()

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
void PrintDigInfo (int BoardNum);
void PrintCtrInfo (int BoardNum);
void PrintExpInfo (int BoardNum);


void ClearScreen (void);
void MoveCursor (int x, int y);
void GetTextCursor (int *x, int *y);

void main ()
    {
    /* Variable Declarations */
    int  ULStat = 0;
    int  NumBoards, StartY, x, y, BoardNum;
    char BoardNameStr[BOARDNAMELEN];
    float    RevLevel = (float)CURRENTREVNUM;
    int  BoardType;
                             
  /* Declare UL Revision Level */                             
   ULStat = cbDeclareRevision(&RevLevel);

    cbErrHandling (PRINTALL, DONTSTOP);

    /* set up the display screen */
    ClearScreen();
    printf ("Demonstration of cbGetBoardName()\n\n");
    printf ("List of Installed Boards:\n");

    /* Get the number of boards installed in system */
    cbGetConfig (GLOBALINFO, 0, 0, GINUMBOARDS, &NumBoards);

    /* Print out board type name of each installed board */
    for (BoardNum=0; BoardNum<NumBoards; BoardNum++)
        {
        /* Get board type of each board */
        cbGetConfig (BOARDINFO, BoardNum, 0, BIBOARDTYPE, &BoardType);
        
        /* If a board is installed */
        if (BoardType > 0)
           {
            cbGetBoardName (BoardNum, BoardNameStr);
            printf ("    Board #%d = %s\n", BoardNum, BoardNameStr);
           }
        }
    printf ("\n\n");
    printf ("                 --- Press any key to continue ---\n");

    getch();
    ClearScreen();
    printf ("List of supported boards:\n");
    GetTextCursor (&x, &y);
    StartY = y;

    /* Get the fisrt board type in list of supported boards */
    cbGetBoardName (GETFIRST, BoardNameStr);
    printf ("  %s",BoardNameStr);
    y++;

    do
        {
        /* Get each consecutive board type in list */
        cbGetBoardName (GETNEXT, BoardNameStr);
        MoveCursor (x, y);
        printf ("  %s",BoardNameStr);
        y++;
        if (y > 21)
            {
            y = StartY;
            x += 20;
            }
        } while (BoardNameStr[0] != '\0');
    MoveCursor (0, 23);
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





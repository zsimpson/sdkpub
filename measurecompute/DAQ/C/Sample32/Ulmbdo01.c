/*ULMBDO01.C****************************************************************

File:                         ULMBDO01.C

Library Call Demonstrated:		cbDOut() for MetraBus Cards

Purpose:						Writes a bit to a digital output port.

Demonstration:					Writes a value to FIRSTPORTA 

Other Library Calls:			cbErrHandling()

Special Requirements:			MetraBus digital output card must be installed


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
BOOL ask();
int getNewBoardNumber(int col, int row);
void reportCurrentBoardNumber(int boardNum);


void main ()
    {
    /* Variable Declarations */
    int Row, Col;
    int BoardNum = 1;
    int ULStat = 0;
    int PortNum; //, Direction;
    WORD DataValue;
    float    RevLevel = (float)CURRENTREVNUM;
	char s[32];  // string for user input
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
    printf ("Demonstration of cbDOut()\n\n\n\n");
    GetTextCursor (&Col, &Row);

	/* change the board number from the console */
	reportCurrentBoardNumber(BoardNum);
    if (ask("Change board number (y/n)?"))
    {
        BoardNum = getNewBoardNumber(Col,Row);
		reportCurrentBoardNumber(BoardNum);
    }

	/* specify the port number */
    PortNum = FIRSTPORTA;

    /* get a user value to write to the port */
    do
    {
        MoveCursor (Col, Row);
        printf ("Enter a value to send to FIRSTPORTA (0-255):       ");
        MoveCursor (Col+45, Row);
		gets(s);
        sscanf(s,"%i", &DataValue);
     } while  ((DataValue < 0) || (DataValue > 255));

    /* write the value to FIRSTPORTA
        Parameters:
            BoardNum    :the number used by CB.CFG to describe this board
            PortNum     :the output port
            DataValue   :the value written to the port   */

	ULStat = cbDOut(BoardNum, PortNum, DataValue);

    MoveCursor (Col, Row + 2);
    printf ("The value %u was written to FIRSTPORTA. ", DataValue);

    MoveCursor (1, 20);
    printf ("\n");
    }

/***************************************************************************
*
* Name:      reportCurrentBoardNumber(int boardNum)
* Arguments: boardNum - boardNumber
* Returns:   nothing
*
* Queries user and returns the selected board number
*
***************************************************************************/
void reportCurrentBoardNumber(int boardNum)
{
    int c,r;
	GetTextCursor(&c,&r);
	MoveCursor(0,2);
	printf("Currently selected board number is %i.   ",boardNum);
	MoveCursor(c,r);
}

/***************************************************************************
*
* Name:      getNewBoardNumber(int col, int row)
* Arguments: screen position: col = column, row
* Returns:   number from 0 to 63
*
* Queries user and returns the selected board number
*
***************************************************************************/
int getNewBoardNumber(int col, int row)
{
	int bdNum = -1;
	char s[32];
	do
	{
        MoveCursor (col, row);
		printf("Enter new board number -->                        ");
        MoveCursor (col+32, row);
		gets(s);
		sscanf(s,"%i",&bdNum);
	}
	while ((bdNum<0) || (bdNum>64));
	return bdNum;
}

/***************************************************************************
*
* Name:      ask(char *question)
* Arguments: char *question
* Returns:   TRUE if user responds y, FALSE otherwise
*
* Queries user for yes or no response
*
***************************************************************************/

BOOL ask(char *question)
{
   BOOL retval = FALSE;
   char response;
   printf(question);
   response = (char)getchar();
   switch (response)
   {
     case 'y' :
     case 'Y' : retval = TRUE;
   }
   printf("\n\n");
   return retval;
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






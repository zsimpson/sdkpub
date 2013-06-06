/*ULMBDI01.C****************************************************************

File:                         ULMBDI01.C

Library Call Demonstrated:    cbDIn()  for MetraBus cards

Purpose:                      Reads a digital input port.

Demonstration:                Configures FIRSTPORTA for input and
                              reads the value on the port.

Other Library Calls:          cbDConfigPort()
                              cbErrHandling()

Special Requirements:         Board 0 must have a digital input port.

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
BOOL ask();
int getNewBoardNumber(int col, int row);
void reportCurrentBoardNumber(int boardNum);


void main ()
    {
    /* Variable Declarations */
    int Row, Col, I;
    int BoardNum = 1;
    int ULStat = 0;
    int PortNum;
    int PowerVal, BitValue;
    int Zero = 0;
    int One = 1;
    WORD DataValue;
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
    printf ("Demonstration of cbDIn()\n\n\n\n\n");
    GetTextCursor (&Col, &Row);

	/* change the board number from the console */
	reportCurrentBoardNumber(BoardNum);
    if (ask("Change board number (y/n)?"))
    {
        BoardNum = getNewBoardNumber(Col,Row);
		reportCurrentBoardNumber(BoardNum);
    }

    printf ("Press any key to quit.\n\n");
    printf ("\nYou may change a bit by applying a TTL high or");
    printf ("\na TTL low to the corresponding pin# on port A.\n\n");

    printf ("The first 7 bits are: ");
    printf ("0  1  2  3  4  5  6  7 \n");
    GetTextCursor (&Col, &Row);

    PortNum = FIRSTPORTA;

    while (!kbhit())
        {
        /* Read the 7 bits digital input and display
           Parameters:
                BoardNum    :the number used by CB.CFG to describe this board
                PortNum     :the input port
                DataValue   :the value read from the port   */
        ULStat = cbDIn(BoardNum, PortNum, &DataValue);

        /* display the value collected from the port */
        MoveCursor (Col, Row);
        printf ("Port Value: %u         ", DataValue);

        /* parse DataValue into bit values to indicate on/off status */
        MoveCursor (Col + 21, Row);
        for (I = 0; I < 8; I++)
            {
            BitValue = Zero;
            PowerVal = (int)pow(2, I);
            if (DataValue & PowerVal)
                {
                BitValue = One;
                }
            printf (" %u ", BitValue);
            }
        }

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






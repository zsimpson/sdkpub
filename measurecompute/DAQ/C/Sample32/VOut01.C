/*VOut01.C****************************************************************

File:                         VOut01.C

Library Call Demonstrated:    cbVOut()

Purpose:                      Writes to a D/A Output Channel.

Demonstration:                Sends a digital output to D/A 0
                              until a key is pressed.

Other Library Calls:          cbErrHandling()
                              cbFromEngUnits()

Special Requirements:         Board 0 must have a D/A output port.

Copyright (c) 1995-2007, Measurement Computing Corp.
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
        int ch;
    int Row, Col;
    int BoardNum = 0;
    int ULStat = 0;
    int Gain = BIP10VOLTS;
	int Options = DEFAULTOPTION;
    int Chan;
    float DataValue;
	int UDStat = 0;
	float min, max;
    
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
    printf ("Demonstration of cbVOut()\n\n");

	/* get the D/A channel to sample */
    printf ("Enter the channel to display: ");
    scanf("%i", &Chan);
    

	printf ("\n\nNote: Please make certain that the board you are using supports\n");
    printf ("      the gain you are choosing and if it is not a programmable\n");
    printf ("      gain that the switches on the board are set correctly.\n\n");
    GetTextCursor (&Col, &Row);

	while (Gain > 0 && !kbhit())
        {   
		do
			{ /* select gain */
			MoveCursor(Col,Row);
			printf("Please select one of the following ranges(1 to 4):\n\n");
			printf("                           10 VOLTS UNIPOLAR --> 1\n");
			printf("                           10 VOLTS BIPOLAR ---> 2\n");
			printf("                            5 VOLTS UNIPOLAR --> 3\n");
			printf("                            5 VOLTS BIPOLAR ---> 4\n");
			printf("                                       Quit ---> 0\n\n");
						printf("                                Your Choice ---> ");
			scanf ("%i",&Gain);
			} while ((Gain < 0) || (Gain > 4));

			/* Set Gain, MaxVal, and MinVal */
			switch (Gain)
				{
				case 0:
					exit(1);
				case 1:
					Gain = UNI10VOLTS;
					min=0.0;
					max=10.0;
					break;
				case 2:
					Gain = BIP10VOLTS;
					min=-10.0;
					max=10.0;
					break;
				case 3:
					Gain = UNI5VOLTS;
					min=0.0;
					max=5.0;
					break;
				case 4:
					Gain = BIP5VOLTS;
					min=-5.0;
					max=5.0;
					break;
				default:
					break;
				}

		UDStat = NOERRORS;

		while (UDStat == NOERRORS)
			{
			printf ("\n\nEnter a voltage between %.1f and +%.1f: ", min, max);
			scanf ("%f", &DataValue);
        
			ULStat = cbVOut (BoardNum, Chan, Gain, DataValue, Options);
			if(UDStat == NOERRORS)
				{
					printf ("\n  %.2f volts has been sent to D/A %d.\n\n", DataValue, Chan);
					printf ("Press Q to quit , any other key to continue:\n ");
					while (!kbhit()){}
					ch=getch();
					if (ch=='q' || ch=='Q')
						exit(1);
				}
			}
		}
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


/*VIn01.C****************************************************************

File:                         VIn01.C

Library Call Demonstrated:    cbVIn()

Purpose:                      Reads an A/D Input Channel.

Demonstration:                Displays the voltage input on a
                              user-specified channel until a
                              key is pressed.

Other Library Calls:          cbErrHandling()

Special Requirements:         Board 0 must have an A/D converter and support cbVIn().
                              Analog signal on an input channel.
                              CB.CFG must be in the current directory.

Copyright (c) 1993-2007, Measurement Computing Corp.
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
    int Row,Col,Row1,Col1;
    int BoardNum = 0;
    int UDStat = 0;
    int Chan;
    int Gain = BIP10VOLTS;
    float DataValue = 0;
	int Options = DEFAULTOPTION;
        
    float    RevLevel = (float)CURRENTREVNUM;

  /* Declare UL Revision Level */
   UDStat = cbDeclareRevision(&RevLevel);


    /* Initiate error handling
       Parameters:
           PRINTALL :all warnings and errors encountered will be printed
           DONTSTOP :program will continue even if error occurs.
                     Note that STOPALL and STOPFATAL are only effective in 
                     Windows applications, not Console applications. 
   */
    cbErrHandling (PRINTALL, DONTSTOP);

    /* set up the screen */
    ClearScreen();
    printf ("Demonstration of cbVIn()\n");

    /* get the A/D channel to sample */
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
			MoveCursor(12,10);
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
					break;
				case 2:
					Gain = BIP10VOLTS;
					break;
				case 3:
					Gain = UNI5VOLTS;
					break;
				case 4:
					Gain = BIP5VOLTS;
					break;
				default:
					break;
				}

		GetTextCursor (&Col1, &Row1);
		UDStat = NOERRORS;
		/* collect the sample from the channel until a key is pressed */
		while (!kbhit() && UDStat == NOERRORS)
			{
			/*Parameters:
				BoardNum    :number used by CB.CFG to describe this board
				Chan        :input channel number
				Gain        :gain for the board in BoardNum
				DataValue   :value collected from Chan */

			UDStat = cbVIn (BoardNum, Chan, Gain, &DataValue, Options);

			if(UDStat == NOERRORS)
				{
					MoveCursor(Col1, Row1);
					printf ("\nThe voltage on Channel %u is:  ", Chan);
					GetTextCursor (&Col, &Row);

					//MoveCursor(Col, Row);
					printf ("%.5f ", DataValue);
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


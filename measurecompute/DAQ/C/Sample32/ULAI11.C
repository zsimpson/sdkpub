/*ULAI11.C****************************************************************

File:                         ULAI11.C

Library Call Demonstrated:    cbToEngUnits()

Purpose:                      Convert a raw data value to a voltage.

Demonstration:                Displays a voltage on a user-specified
                              channel.

Other Library Calls:          cbErrHandling()
                              cbAIn()

Special Requirements:         Board 0 must have an A/D converter.
                              Analog signal on an input channel.
                              If the board is a 16 bit board, see the
                              CONVERT RAW DATA VALUE section for the
                              correct value to use.

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
    int Row,Col;
    int BoardNum = 0;
    int ULStat = 0;
    int Chan;
    int Gain = BIPPT625VOLTS;
    WORD DataValue = 0;
        float EngUnits;
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

    /* set up the screen */
    ClearScreen();
    printf ("Demonstration of voltage conversions.\n\n");

    /* get the A/D channel to sample */
    printf ("Enter the channel to display: ");
    scanf("%d", &Chan);

    printf ("\n\nNote: Please make certain that the board you are using supports\n");
    printf ("      the gain you are choosing and if it is not a programmable\n");
    printf ("      gain that the switches on the board are set correctly.\n\n");
    GetTextCursor (&Col, &Row);

    /* collect the sample with cbAIn() */
    while (Gain > 0)
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

        /*Parameters:
            BoardNum    :number used by CB.CFG to describe this board
            Chan        :input channel number
            Gain        :gain for the board in BoardNum
            DataValue   :value collected from Chan */

        if (Gain >= 0)
            {
            ULStat = cbAIn (BoardNum, Chan, Gain, &DataValue);
            ULStat = cbToEngUnits(BoardNum, Gain, DataValue, &EngUnits);

            printf ("\nThe voltage on channel %d is %.2f ", Chan, EngUnits);
            }
        Gain = BIPPT625VOLTS;
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



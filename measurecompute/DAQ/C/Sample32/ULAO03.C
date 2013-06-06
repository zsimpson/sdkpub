/*ULAO03.C****************************************************************

File:                         ULAO03.C

Library Call Demonstrated:    cbAOut()
                              cbSetConfig() using BIDACUPDATEMODE and
'                                   BIDACUPDATECMD

Purpose:                      Delays updating D/A's until BIDACUPDATECMD issued

Other Library Calls:          cbErrHandling()
                              cbFromEngUnits()

Special Requirements:         Board 0 must have a D/A output port that supports
                              UPDATEONCOMMAND update mode.

Copyright (c) 2003, Measurement Computing Corp.
All Rights Reserved.
***************************************************************************/


/* Include files */
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "..\cbw.h"

#define ALLDEVICES   -1
#define NOT_USED      0

/* Prototypes */
void ClearScreen (void);
void GetTextCursor (int *x, int *y);
void MoveCursor (int x, int y);


void main ()
    {
    /* Variable Declarations */
    int ch;
    int Row, Col;
    int BdNum = 0;
    int DevNum = 0;
    int ConfigVal = 0;
    int ULStat = 0;
    int Gain = BIP10VOLTS;
    int chan, ExitFlag;
    WORD DataValue;
    float volts;

    /* Initiate error handling
        Parameters:
            PRINTALL :all warnings and errors encountered will be printed
            DONTSTOP :program will continue even if error occurs.
                     Note that STOPALL and STOPFATAL are only effective in 
                     Windows applications, not Console applications. 
   */
    cbErrHandling (PRINTALL, DONTSTOP);

    

    // Initialize output to ground.
    // Note that the default behavior is to update D/A's immediately
    //  upon cbAOut or cbAOutScan.
    volts = 0.0;
    chan = 0;
    ULStat = cbFromEngUnits(BdNum, Gain, volts, &DataValue);
    ULStat = cbAOut (BdNum, chan, Gain, DataValue);

     
   // Set DAC Update mode to hold off updating D/A's until issued Update Command
   // Parameters
   //   BOARDINFO    : General information about the board
   //   BdNum        : Number used by CB.CFG to describe this board
   //   DevNum       : Selects device; in this case, selects D/A channel to configure
   //                  Note that -1 selects all D/A channels
   //   BIDACUPDATEMODE : Selects update mode for D/A, whether immediately (via cbAOut
   //                    or cbAOutScan) or upon issuing BIDACUPDATECMD
   //   UPDATEONCOMMAND : Delay D/A output updates from cbAOut or cbAOutScan until
   //                     BIDACUPDATECMD is issued.
    DevNum = ALLDEVICES;
    ULStat = cbSetConfig(BOARDINFO, BdNum, DevNum, BIDACUPDATEMODE, UPDATEONCOMMAND);

    ExitFlag = FALSE;
   
   while (!ExitFlag)
      {
      // Set up the display screen 
      ClearScreen();
      printf ("Demonstration of DAC Update Modes with cbAOut()\n\n");
      GetTextCursor (&Col, &Row);
      MoveCursor (0, 3);

      printf ("Enter a voltage between -10.0 and +10.0: ");
      MoveCursor (41, 3);

      if (0==scanf ("%f", &volts))
      {
         printf("Error : Invalid entry.");
         break;
      }
        
      ULStat = cbFromEngUnits(BdNum, Gain, volts, &DataValue);
      ULStat = cbAOut (BdNum, chan, Gain, DataValue);
     
      printf ("\n  %.2f volts has been sent to D/A 0.\n\n", volts);
       

      printf ("Press U to update D/A output, Q to quit, \n or any other key to continue:\n ");
      while (!kbhit()){}
   
      ch=getch();
      if (ch=='q' || ch=='Q')
         ExitFlag=TRUE;
      else if (ch=='u' || ch=='U')
         {
         // Issue command to update all the D/A's with the last value written
         //   to them via cbAOut or cbAOutScan
         //
         // Parameters
         //   BOARDINFO   : General information about the board
         //   BdNum       : Number used by CB.CFG to describe this board
         //   DevNum      : Not used for BIDACUPDATECMD
         //   BIDACUPDATECMD : Update D/A outputs with last value written
         //   ConfigVal   : Note used for BIDACUPDATECMD 
         DevNum = NOT_USED;
         ConfigVal = NOT_USED;
         ULStat = cbSetConfig(BOARDINFO, BdNum, DevNum, BIDACUPDATECMD, ConfigVal);
         printf("\nD/A output 0 has been updated.    ");
         }
      else
         printf("\nD/A output 0 has not been updated!");
      }

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


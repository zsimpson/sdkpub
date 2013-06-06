/*ULCT03.C*****************************************************************

File:                         ULCT03.C

Library Call Demonstrated:    9513 Counter Functions
                                 cbC9513Config()
                                 cbCStoreOnInt()

Purpose:                      Operate the counter.

Demonstration:                Sets up 2 counters to store values in
                              response to an interrupt.

Other Library Calls:          cbC9513Init()
                              cbCLoad()
                              cbCStopBackground()
                              cbErrHandling()

Special Requirements:         Board 0 must have a 9513 Counter.
                              IR enable must be tied low.
                              User must generate an interrrupt(Pin1).


Copyright (c) 1995-2002, Measurement Computing Corp.
All Rights Reserved.
***************************************************************************/


/* Include files */
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "..\cbw.h"

#define MAXNUMCNTRS 20

/* Prototypes */
void ClearScreen (void);
void MoveCursor (int x, int y);


void main()
    {
    /* Variable Declarations */
    int I, J, ULStat, BoardNum;
    int ChipNum, CounterNum;
    int FOutDivider, FOutSource, Compare1, Compare2, TimeOfDay;
    int GateControl, CounterEdge, CountSource, SpecialGate;
    int ReLoad, RecycleMode, BCDMode, CountDirection, OutputControl;
    int LoadValue;
    int RegName;
    int IntCount, NumCntrs;
    short Status;
    long CurCount, CurIndex, FirstPoint;
    short  CntrControl[MAXNUMCNTRS];
    char *StatusStr;
    WORD *DataBuffer;
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
    printf ("Demonstration of 9513 Counter Functions.\n\n");
    printf ("Press any key to quit.\n\n");

    /* Initialize the board level features  */
    BoardNum = 0;           /* Number used by CB.CFG to describe this board */
    ChipNum = 1;            /* chip being init'ed (1 for CTR5, 1 or 2 for CTR10) */
    FOutDivider = 10;       /* sets up OSC OUT for 10Hz signal which can be */
    FOutSource = FREQ5;     /* used as an interrrupt source for this example */
    Compare1 = DISABLED;    /* Status of comparator 1 */
    Compare2 = DISABLED;    /* Status of comparator 2 */
    TimeOfDay = DISABLED;   /* Time of day control mode */
    ULStat = cbC9513Init (BoardNum, ChipNum, FOutDivider, FOutSource, Compare1,
                          Compare2, TimeOfDay);

    /* Set the configurable operations of counters 1 and 2 */
    CounterNum = 1;         /* Counter to be configured (0-5) */
    GateControl = NOGATE;   /* Gate control value */
    CounterEdge = POSITIVEEDGE;    /* Which edge to count */
    CountSource = FREQ3;    /* Signal source for counter */
    SpecialGate = DISABLED; /* Status of special gate */
    ReLoad = LOADREG;       /* Method of reloading the counter */
    RecycleMode = RECYCLE;  /* Recycle mode */
    BCDMode = DISABLED;     /* Counting mode, BCD or binary */
    CountDirection = COUNTUP;  /* Counting direction (up or down) */
    OutputControl = ALWAYSLOW; /* Output signal type and level */
    ULStat = cbC9513Config (BoardNum, CounterNum , GateControl, CounterEdge,
                            CountSource, SpecialGate, ReLoad, RecycleMode,
                            BCDMode, CountDirection, OutputControl);
    CounterNum = 2;
    CountSource = FREQ5;
    ULStat = cbC9513Config (BoardNum, CounterNum , GateControl, CounterEdge,
                            CountSource, SpecialGate, ReLoad, RecycleMode,
                            BCDMode, CountDirection, OutputControl);

    /* Load the 2 counters with starting values of zero with cbCLoad()
        Parameters:
            BoardNum    :the number used by CB.CFG to describe this board
            RegName     :the counter to be loading with the starting value
            LoadValue   :the starting value to place in the counter */
    LoadValue = 0;
    for (RegName=LOADREG1; RegName<=LOADREG2; RegName++)
        ULStat = cbCLoad (BoardNum, RegName, LoadValue);

    /* set the counters to store their values upon an interrupt
        Parameters:
            BoardNum    :the number used by CB.CFG to describe this board
            IntCount    :maximum number of interrupts
            CntrControl[]:array which indicates the channels to be used
            DataBuffer[] :array that receives the count values for enabled
                          channels each time an interrupt occurs */
    IntCount = 100;

   
	/*
		DataBuffer must be able to hold  NumCntrs*IntCount  values, even if
		we're only enabling a few counters. We'll allocate enough space for
		MAXNUMCNTRS in case NumCntrs has not been updated.
	*/
	DataBuffer = (WORD *)cbWinBufAlloc( MAXNUMCNTRS*IntCount );

	/* 	
		The actual number of counters onboard.  
		UPDATE THIS	VALUE TO REFLECT THE NUMBER OF COUNTERS FOR THE INSTALLED MODEL.
	*/	
	NumCntrs = 10;			
    for (I = 0; I < NumCntrs; I++)
        CntrControl[I] = DISABLED;

	for (J = 0; J< IntCount; J++)
		for (I = 0; I<NumCntrs; I++)
			DataBuffer[J*NumCntrs + I] = 0;
        

    /* enable the channels to be monitored */
    CntrControl[0] = ENABLED;
    CntrControl[1] = ENABLED;

    ULStat = cbCStoreOnInt (BoardNum, IntCount, CntrControl, DataBuffer);

    MoveCursor (1, 14);
    printf ("When an interrupt is generated, the table below will be updated.");

    MoveCursor (5, 15);
    printf ("Counter   Status      Value ");

    Status = RUNNING;
    while (!kbhit() && Status==RUNNING)
        {
		/* We'll display the latest counts retrieved and the current INT count*/
		/* Check the status of the current background operation
        Parameters:
            BoardNum  :the number used by CB.CFG to describe this board
            Status    :current status of the operation (IDLE or RUNNING)
            CurCount  :current number of samples collected
            CurIndex  :index to the last data value transferred 
            FunctionType: A/D operation (CTRFUNCTION)*/
        cbGetStatus (BoardNum, &Status, &CurCount, &CurIndex,CTRFUNCTION);

        for (I = 0; I < 5; I++)
            {
            if (CntrControl[I] == DISABLED)
                StatusStr = "DISABLED";
            else
                StatusStr = "ENABLED";

            MoveCursor (5, 16 + I);
			
			FirstPoint=0;

			/* 
				The latest set of data in the data buffer is starts at
					FirstPoint = NumCntrs*CurIndex;
			*/
			if (CurIndex>0)
				{
				FirstPoint = NumCntrs*CurIndex;
				}	

			printf (" %2u       %8s    %5u\n", I, StatusStr, DataBuffer[FirstPoint + I]);
            }

        
        printf ("Number of interrupts so far=%-ld\n", CurCount);
        }

        /* the BACKGROUND operation must be explicitly stopped
        Parameters:
             BoardNum    :the number used by CB.CFG to describe this board 
             FunctionType: counter operation (CTRFUNCTION)*/  
    ULStat = cbStopBackground (BoardNum,CTRFUNCTION);

	cbWinBufFree((int)DataBuffer);

    MoveCursor (1, 22);
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


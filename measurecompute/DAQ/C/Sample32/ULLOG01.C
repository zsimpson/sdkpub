/*ULLOG01.C****************************************************************

File:                         ULLOG01.C

Library Call Demonstrated:    cbLogGetFilename()

Purpose:                      Retrieves the name of a binary log file.

Demonstration:                Displays all of the binary files in a 
                              specified directory.

Other Library Calls:          cbErrHandling()

Special Requirements:         None.

Copyright (c) 1995-2005, Measurement Computing Corp.
All Rights Reserved.
***************************************************************************/


/* Include files */
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "..\cbw.h"

/* Prototypes */
void ClearScreen (void);
void MoveCursor (int x, int y);


void main ()
   {
   /* Variable Declarations */
	int		ULStat;
	int		FileNumber;
	int		Count;
	char*	SourceDirectory;
	char	AbsolutePath[MAX_PATH];
	char	Filename[MAX_PATH];
    float   RevLevel = (float)CURRENTREVNUM;

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
    printf ("Demonstration of cbLogGetFileName()\n\n");

	/* Get the path to the binary log files */
	SourceDirectory = "..\\..";

    /* Display the names of all of the files in the source directory()
        Parameters:
            FileNumber  :the nth file in the directory; or GETFIRST or GETNEXT
            Path[]      :full path to directory containing binary log files
            Filename[]  :receives the full path to the binary log file
	*/

	FileNumber = GETFIRST;
	Count = 0;
	while (ULStat == NOERRORS)
	{
		ULStat = cbLogGetFileName(FileNumber, SourceDirectory, Filename);
		if (ULStat == NOERRORS)
		{
			Count++;
			_fullpath(AbsolutePath, Filename, MAX_PATH);
			printf ("%s\n", AbsolutePath);
			FileNumber = GETNEXT;
		}
		else if (ULStat != NOMOREFILES)
			printf("Error = %d\n", ULStat);
	}

	printf ("\nA total of %d files were found\n", Count);
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

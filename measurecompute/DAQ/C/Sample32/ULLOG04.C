/*ULLOG03.C****************************************************************

File:                         ULLOG03.C

Library Call Demonstrated:    cbLogReadFile()

Purpose:                      Reads a binary log file.

Demonstration:                Display the analog, CJC, and DIO data.

Other Library Calls:          cbErrHandling()
                              cbGetFilename()
                              cbGetFileInfo()

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
	int			ULStat;
	int			FileNumber;
	int			Version;
	int			Size;
	int			SampleInterval;
	int			SampleCount;
	int			StartDate;
	int			StartTime;
	int			StartSample = 0;
	char*		SourceDirectory;
	char		DestinationFilename[MAX_PATH];
	char		DestAbsolutePath[MAX_PATH];
	char		AbsolutePath[MAX_PATH];
	char		Filename[MAX_PATH];
	char*		ptrToExtension;

    float		RevLevel = (float)CURRENTREVNUM;

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
    printf ("Demonstration of cbLogConvertFile()\n\n");

	/* Get the path to the binary log files */
	SourceDirectory = "..\\..";

	/* Set the preferences 
		Parameters
			TimeFormat	:specifies times are 12 or 24 hour format
			TimeZone	:specifies local time of GMT
			Units		:specifies Fahrenheit, Celsius, or Kelvin
	*/
	cbLogSetPreferences(TIMEFORMAT_12HOUR, TIMEZONE_LOCAL, FAHRENHEIT);


    /* Get the name of the first binary log file in the source directory()
        Parameters:
            FileNumber  :the nth file in the directory; or GETFIRST or GETNEXT
            Path[]      :full path to directory containing binary log files
            Filename[]  :receives the full path to the binary log file
	*/
	FileNumber = GETFIRST;
	ULStat = cbLogGetFileName(FileNumber, SourceDirectory, Filename);

	/* Get the destination directory */
	strcpy(DestinationFilename, Filename);
	ptrToExtension = strrchr(DestinationFilename, '.');
	strcpy(ptrToExtension, ".CSV");


	if (ULStat == NOERRORS)
	{
		_fullpath(AbsolutePath, Filename, MAX_PATH);

		/* Get the file information for first binary log file in the directory
			Parameters:
				FileName        :the filename to retrieve information from
				Version         :receives the version information
				Size			:receives the file size information
		*/
		printf ("Calling cbLogGetFileInfo() to get file info for file:  %s\n\n", AbsolutePath);
		ULStat = cbLogGetFileInfo(Filename, &Version, &Size);


		/* Get the sample information for first binary log file in the directory
			Parameters:
				FileName        :the filename to retrieve information from
				SampleInterval  :receives the time between samples
				SampleCount		:receives the number of samples in the file
				StartDate		:receives the start date
				StartTime       :recveives the start time
		*/
		printf ("Calling cbLogGetSampleInfo() to get sample info for file:  %s\n\n", AbsolutePath);
		ULStat = cbLogGetSampleInfo(Filename, &SampleInterval, &SampleCount, &StartDate, &StartTime);


		if (ULStat == NOERRORS)
		{
			int		StartSample = 0;
			int		Delimiter = DELIMITER_COMMA;


			/* convert the log file to a .CSV file for Excel */
			ULStat = cbLogConvertFile(Filename, DestinationFilename, StartSample, SampleCount, Delimiter);

		}
	}

	if (ULStat == NOERRORS)
	{
		_fullpath(DestAbsolutePath, DestinationFilename, MAX_PATH);
		printf("\n\nThe file %s has been converted and saved in the directory %s\n", AbsolutePath, DestAbsolutePath);
	}
	else
		printf ("cbLogConvertFile failed:  error code %d\n", ULStat);
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

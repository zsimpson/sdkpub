/*ULLOG02.C****************************************************************

File:                         ULLOG02.C

Library Call Demonstrated:    cbLogGetFileInfo()

Purpose:                      Retrieves the header information from
                              a binary log file.

Demonstration:                Displays all of the header information 
                              for a binary log file.

Other Library Calls:          cbErrHandling()
                              cbGetFilename()

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
	int*		ChannelNumbers;
	int*		Units;
	int			AICount;
	int			CJCCount;
	int			DIOCount;
	char*		SourceDirectory;
	char		AbsolutePath[MAX_PATH];
	char		Filename[MAX_PATH];
	char*		postfix;
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
    printf ("Demonstration of how to get information from binaary log files\n\n");

	/* Get the path to ther binary log files */
	SourceDirectory = "..\\..";

    /* Get the name of the first binary log file in the source directory()
        Parameters:
            FileNumber          :the nth file in the directory; or GETFIRST or GETNEXT
            SourceDirectory[]   :full path to directory containing binary log files
            Filename[]          :receives the full path to the binary log file
	*/

	FileNumber = GETFIRST;
	ULStat = cbLogGetFileName(FileNumber, SourceDirectory, Filename);
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
		if (ULStat == NOERRORS)
		{
			/* Display the file header information */
			printf("\tFilename:                        %s\n", AbsolutePath);
			printf("\tFile version:                    %d\n", Version);
			printf("\tSize of binary file:             %d\n", Size);
		}
	}

	if (ULStat == NOERRORS)
	{
		/* Get the sample information for first binary log file in the directory
			Parameters:
				FileName        :the filename to retrieve information from
				SampleInterval  :receives the time between samples
				SampleCount		:receives the number of samples in the file
				StartDate		:receives the start date
				StartTime       :recveives the start time
		*/
		printf ("\n\n");
		printf ("Calling cbLogGetSampleInfo() to get sample info for file:  %s\n\n", AbsolutePath);

		ULStat = cbLogGetSampleInfo(Filename, &SampleInterval, &SampleCount, &StartDate, &StartTime);
		if (ULStat == NOERRORS)
		{
			/* Display the sample header information */
			switch (StartTime >> 24)
			{
				case 0:
					postfix = "AM";
					break;
				case 1:
					postfix = "PM";
					break;
				case 0xff:
				default:
					postfix = "";
			}

			printf("\tSample interval:                 %d\n", SampleInterval);
			printf("\tNumber of samples (rows):        %d\n", SampleCount);
			printf("\tStartDate:                       %d/%d/%d\n", (StartDate >> 8) & 0xff,		// month 
				                                                    StartDate & 0xff, 				// day
																	(StartDate >> 16) & 0xffff);	// year

			printf("\tStartTime:                       %d:%d:%d %s\n", (StartTime >> 16) & 0xff,	// hours
				                                                    (StartTime >> 8) & 0xff, 		// minutes
																	StartTime & 0xff,				// seconds
																	postfix);						
		}
	}
	
	if (ULStat == NOERRORS)
	{
		/* Get the AI channel count for first binary log file in the directory
			Parameters:
				FileName        :the filename to retrieve information from
				AICount			:receives the number of AI Channels
		*/
		printf ("\n\n");
		printf ("Calling cbLogGetAIChannelCount() to get the number of channels logged to the file:  %s\n\n", AbsolutePath);

		ULStat = cbLogGetAIChannelCount(Filename, &AICount);
		
		printf("\tNumber of analog channels:       %d\n", AICount);


		/* Get the AI information for first binary log file in the directory
			Parameters:
				FileName        :the filename to retrieve information from
				ChannelMask		:receives the channel mask
				UnitMask		:receives the unit mask
		*/
		printf ("\n\n");
		printf ("Calling cbLogGetAIInfo() to get AI info for file:  %s\n\n", AbsolutePath);

		ChannelNumbers = (int*)malloc(AICount * sizeof(int));
		Units = (int*)malloc(AICount * sizeof(int));


		ULStat = cbLogGetAIInfo(Filename, ChannelNumbers, Units);
		if (ULStat == NOERRORS)
		{
			int i;
			char*	UnitStr;
			
			/* Display the AI header information */
			for (i=0; i< AICount; i++)
			{
				if (Units[i] == UNITS_RAW)
					UnitStr = "Raw";
				else
					UnitStr = "Temperature";
				printf("\tChannel %d units:                 %s\n", ChannelNumbers[i], UnitStr);
			}
		}
	}

	if (ULStat == NOERRORS)
	{
		/* Get the CJC information for first binary log file in the directory
			Parameters:
				FileName        :the filename to retrieve information from
				CJCCount		:receives the number of CJC Channels
		*/
		printf ("\n\n");
		printf ("Calling cbLogGetCJCInfo() to get CJC info for file:  %s\n\n", AbsolutePath);

		ULStat = cbLogGetCJCInfo(Filename, &CJCCount);
		if (ULStat == NOERRORS)
		{
			/* Display the AI header information */
			printf("\tNumber of CJC channels:          %d\n", CJCCount);
		}
	}

	if (ULStat == NOERRORS)
	{
		/* Get the DIO information for first binary log file in the directory
			Parameters:
				FileName        :the filename to retrieve information from
				DIOCount		:receives the number of DIO Channels
		*/
		printf ("\n\n");
		printf ("Calling cbLogGetDIOInfo() to get DIO info for file:  %s\n\n", AbsolutePath);

		ULStat = cbLogGetDIOInfo(Filename, &DIOCount);
		if (ULStat == NOERRORS)
		{
			/* Display the AI header information */
			printf("\tNumber of DIO channels:          %d\n", DIOCount);
		}
	}

	if (ULStat != NOERRORS)
		printf("Error = %d\n", ULStat);


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

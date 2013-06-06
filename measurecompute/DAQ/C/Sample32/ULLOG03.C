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
	int			TimeFormat;
	int			TimeZone;
	int			Units;
	int			FileNumber;
	int			Version;
	int			Size;
	int			SampleInterval;
	int			SampleCount;
	int			StartDate;
	int			StartTime;
	int			AICount;
	int			CJCCount;
	int			DIOCount;
	int			StartSample = 0;
	int*		Dates = NULL;
	int*		Times = NULL;
	float*		Analog = NULL;
	int*		Dio = NULL;
	float*		Cjc = NULL;
	char*		postfix;
	char*		SourceDirectory;
	char		AbsolutePath[MAX_PATH];
	char		Filename[MAX_PATH];

    float		RevLevel = (float)CURRENTREVNUM;
	int			i, j;
	int			index;



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
    printf ("Demonstration of cbLogReadFile()\n\n");

	/* Get the path to the binary log files */
	SourceDirectory = "..\\..";

	/* Set the preferences 
		Parameters
			TimeFormat	:specifies times are 12 or 24 hour format
			TimeZone	:specifies local time of GMT
			Units		:specifies Fahrenheit, Celsius, or Kelvin
	*/
	TimeFormat = TIMEFORMAT_12HOUR;
	TimeZone = TIMEZONE_LOCAL;
	Units = FAHRENHEIT;
	cbLogSetPreferences(TimeFormat, TimeZone, Units);


    /* Get the name of the first binary log file in the source directory()
        Parameters:
            FileNumber  :the nth file in the directory; or GETFIRST or GETNEXT
            Path[]      :full path to directory containing binary log files
            Filename[]  :receives the full path to the binary log file
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


		/* Get the sample information for first binary log file in the directory
			Parameters:
				FileName        :the filename to retrieve information from
				SampleInterval  :receives the time between samples
				SampleCount		:receives the number of samples in the file
				StartDate		:receives the start date
				StartTime       :recveives the start time
		*/
		if (ULStat == NOERRORS)
		{
			printf ("Calling cbLogGetSampleInfo() to get sample info for file:  %s\n\n", AbsolutePath);
			ULStat = cbLogGetSampleInfo(Filename, &SampleInterval, &SampleCount, &StartDate, &StartTime);
		}


		/* Get the AI channel count for first binary log file in the directory
			Parameters:
				FileName        :the filename to retrieve information from
				AICount			:receives the number of AI Channels
		*/
		if (ULStat == NOERRORS)
		{
			printf ("Calling cbLogGetAIChannelCount() to get the number of channels logged to the file:  %s\n\n", AbsolutePath);
			ULStat = cbLogGetAIChannelCount(Filename, &AICount);
		}


		/* Get the CJC information for first binary log file in the directory
			Parameters:
				FileName        :the filename to retrieve information from
				CJCCount		:receives the number of CJC Channels
		*/
		if (ULStat == NOERRORS)
		{
			printf ("Calling cbLogGetCJCInfo() to get CJC info for file:  %s\n\n", AbsolutePath);
			ULStat = cbLogGetCJCInfo(Filename, &CJCCount);
		}


		/* Get the DIO information for first binary log file in the directory
			Parameters:
				FileName        :the filename to retrieve information from
				DIOCount		:receives the number of DIO Channels
		*/
		if (ULStat == NOERRORS)
		{
			printf ("Calling cbLogGetDIOInfo() to get DIO info for file:  %s\n\n", AbsolutePath);
			ULStat = cbLogGetDIOInfo(Filename, &DIOCount);
		}


		if (ULStat == NOERRORS)
		{
			/* Allocate the Date and Time arrays and read the data */
			/* Get the date/time information for first binary log file in the directory
				Parameters:
					FileName        :the filename to retrieve information from
					StartSample		:first sample to read
					SampleCount		:number of samples to read
					Dates			:receives the sample dates
					Times			:receives the sample times
			*/
			printf ("Calling cbLogReadTimeTags() to read the TIMESTAMP information from the file:  %s\n\n", AbsolutePath);
			Dates = malloc(SampleCount * sizeof(int));
			Times = malloc(SampleCount * sizeof(int));
			ULStat = cbLogReadTimeTags(Filename, StartSample, SampleCount, Dates, Times);


			/* Allocate the Analog array and read the data*/
			/* Get the Analog information for first binary log file in the directory
				Parameters:
					FileName        :the filename to retrieve information from
					StartSample		:first sample to read
					SampleCount		:number of samples to read
					Analog			:receives the analog data
			*/
			if ( AICount && (ULStat == NOERRORS) )
			{
				printf ("Calling cbLogReadAIChannels() to read the ANALOG data from the file:  %s\n\n", AbsolutePath);
				Analog = malloc(SampleCount * AICount * sizeof(float));
				ULStat = cbLogReadAIChannels(Filename, StartSample, SampleCount, Analog);
			}


			/* Allocate the Dio array and read the data */
			/* Get the DIO information for first binary log file in the directory
				Parameters:
					FileName        :the filename to retrieve information from
					StartSample		:first sample to read
					SampleCount		:number of samples to read
					Dio				:receives the dio data
			*/
			if ( DIOCount && (ULStat == NOERRORS) )
			{
				printf ("Calling cbLogReadAIChannels() to read the DIO data from the file:  %s\n\n", AbsolutePath);
				Dio = malloc(SampleCount * DIOCount * sizeof(int));
				ULStat = cbLogReadDIOChannels(Filename, StartSample, SampleCount, Dio);
			}


			/* Allocate the Cjc array and read the data */
			/* Get the CJC information for first binary log file in the directory
				Parameters:
					FileName        :the filename to retrieve information from
					StartSample		:first sample to read
					SampleCount		:number of samples to read
					Cjc				:receives the cjc data
			*/
			if ( CJCCount && (ULStat == NOERRORS) )
			{
				printf ("Calling cbLogReadAIChannels() to read the CJC data from the file:  %s\n\n", AbsolutePath);
				Cjc = malloc(SampleCount * CJCCount * sizeof(float));
				ULStat = cbLogReadCJCChannels(Filename, StartSample, SampleCount, Cjc);
			}


			if (ULStat == NOERRORS)
			{
				// display the contents of the log file
				for (i=0; i<SampleCount; i++)
				{
					index = i;
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

					printf("%d/%d/%d  ", (Dates[index] >> 8) & 0xff,		// month 
										Dates[index] & 0xff,				// day
										(Dates[index] >> 16) & 0xffff);		// year

					printf("%d:%d:%d %s  ", (Times[index] >> 16) & 0xff,	// hours
										(Times[index] >> 8) & 0xff,			// minutes
										Times[index] & 0xff,				// seconds
										postfix);

					if (Analog)
					{
						index = i * AICount;
						for (j=0; j<AICount; j++)
						{
							printf("%f\t", Analog[index++]);
						}
					}

					if (Cjc)
					{
						index = i * CJCCount;
						for (j=0; j<CJCCount; j++)
						{
							printf("%f\t", Cjc[index++]);
						}
					}

					if (Dio)
					{
						index = i * DIOCount;
						for (j=0; j<DIOCount; j++)
						{
							printf("%d  ", Dio[index++]);
						}
					}
				printf("\n");
				}
			}


			free(Dates);
			free(Times);

			if (Analog)
				free(Analog);

			if (Dio)
				free(Dio);

			if (Cjc)
				free(Cjc);
		}
	}

	if (ULStat != NOERRORS)
		printf ("cbLogReadFile failed:  error code %d\n", ULStat);
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

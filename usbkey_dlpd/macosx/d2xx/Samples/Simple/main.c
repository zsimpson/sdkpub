/*
	Simple example to open a maximum of 4 devices - write some data then read it back.
	Shows one method of using list devices also.
	Assumes the devices have a loopback connector on them and they also have a serial number

	To build use the following gcc statement 
	(assuming you have the d2xx library in the /usr/local/lib directory).
	gcc -o simple main.c -L. -lftd2xx -Wl,-rpath /usr/local/lib
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "../ftd2xx.h"

#define BUF_SIZE 16

#define MAX_DEVICES		5

// Globals
FT_HANDLE	ftHandle[MAX_DEVICES];
char * 	pcBufRead = NULL;

void quit()
{  
	int i;

	for(i = 0; i < MAX_DEVICES; i++) {
		if(ftHandle[i] != NULL) {
			FT_Close(ftHandle[i]);
			ftHandle[i] = NULL;
			printf("Closed device\n");
		}
	}

	if(pcBufRead)
		free(pcBufRead);

	exit(1);
}

int main()
{
	char 	cBufWrite[BUF_SIZE];
	char * 	pcBufLD[MAX_DEVICES + 1];
	char 	cBufLD[MAX_DEVICES][64];
	DWORD	dwRxSize = 0;
	DWORD 	dwBytesWritten, dwBytesRead;
	FT_STATUS	ftStatus;
	//FT_HANDLE	ftHandle;
	int	iNumDevs = 0;
	int	i, j;
	int	iDevicesOpen = 0;

	for(i = 0; i < MAX_DEVICES; i++) {
		pcBufLD[i] = cBufLD[i];
		ftHandle[i] = NULL;
	}
	pcBufLD[MAX_DEVICES] = NULL;

	ftStatus = FT_ListDevices(pcBufLD, &iNumDevs, FT_LIST_ALL | FT_OPEN_BY_SERIAL_NUMBER);
	
	if(ftStatus != FT_OK) {
		printf("Error: FT_ListDevices(%d)\n", ftStatus);
		return 1;
	}

	for(j = 0; j < BUF_SIZE; j++) {
		cBufWrite[j] = j;
	}
	
	for(i = 0; ( (i <MAX_DEVICES) && (i < iNumDevs) ); i++) {
		printf("Device %d Serial Number - %s\n", i, cBufLD[i]);
	}
	
    signal(SIGINT, quit);		// trap ctrl-c call quit fn 
		
	for(i = 0; ( (i <MAX_DEVICES) && (i < iNumDevs) ) ; i++) {
		/* Setup */
		if((ftStatus = FT_OpenEx(cBufLD[i], FT_OPEN_BY_SERIAL_NUMBER, &ftHandle[i])) != FT_OK){
			/* 
				This can fail if the ftdi_sio driver is loaded
		 		use lsmod to check this and rmmod ftdi_sio to remove
				also rmmod usbserial
		 	*/
			printf("Error FT_OpenEx(%d), device\n", ftStatus, i);
			return 1;
		}
	
		printf("Opened device %s\n", cBufLD[i]);

		iDevicesOpen++;
		if((ftStatus = FT_SetBaudRate(ftHandle[i], 9600)) != FT_OK) {
			printf("Error FT_SetBaudRate(%d), cBufLD[i] = %s\n", ftStatus, cBufLD[i]);
			break;
		}
//		for(j = 0; j < BUF_SIZE; j++) {
//			printf("cBufWrite[%d] = 0x%02X\n", j, cBufWrite[j]);
//		}
		
		/* Write */
		if((ftStatus = FT_Write(ftHandle[i], cBufWrite, BUF_SIZE, &dwBytesWritten)) != FT_OK) {
			printf("Error FT_Write(%d)\n", ftStatus);
			break;
		}
		sleep(1);
		
		/* Read */
		dwRxSize = 0;			
		while ((dwRxSize < BUF_SIZE) && (ftStatus == FT_OK)) {
			ftStatus = FT_GetQueueStatus(ftHandle[i], &dwRxSize);
		}
		if(ftStatus == FT_OK) {
			pcBufRead = (char*)realloc(pcBufRead, dwRxSize);
			memset(pcBufRead, 0xFF, dwRxSize);
			for(j = 0; j < dwRxSize; j++) {
				printf("pcBufRead[%d] = 0x%02X\n", j, pcBufRead[j]);
			}
			if((ftStatus = FT_Read(ftHandle[i], pcBufRead, dwRxSize, &dwBytesRead)) != FT_OK) {
				printf("Error FT_Read(%d)\n", ftStatus);
			}
			else {
				printf("FT_Read = %d\n", dwBytesRead);
				for(j = 0; j < dwBytesRead; j++) {
					printf("pcBufRead[%d] = 0x%02X\n", j, pcBufRead[j]);
				}
			}
		}
		else {
			printf("Error FT_GetQueueStatus(%d)\n", ftStatus);	
		}
	}

	for(i = 0; i < iDevicesOpen; i++) {
		if(ftHandle[i] != NULL) {
			FT_Close(ftHandle[i]);
			ftHandle[i] = NULL;
			printf("Closed device %s\n", cBufLD[i]);
		}
	}

	if(pcBufRead)
		free(pcBufRead);
	return 0;
}

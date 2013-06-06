/*
	To build use the following gcc statement 
	(assuming you have the d2xx library in the /usr/local/lib directory).
	gcc -o w32_simple main.c -L. -lftd2xx -Wl,-rpath /usr/local/lib
*/

#include <stdio.h>
#include <string.h>
#include "../../ftd2xx.h"

#define BUF_SIZE 0x11

#define MAX_DEVICES		5

int main()
{
	char 	cBufWrite[BUF_SIZE];
	char * 	pcBufRead = NULL;
	char * 	pcBufLD[MAX_DEVICES + 1];
	char 	cBufLD[MAX_DEVICES][64];
	DWORD	dwRxSize = 0;
	DWORD 	dwBytesWritten, dwBytesRead, dwErrors;
	FT_STATUS	ftStatus;
	FT_HANDLE	ftHandle[MAX_DEVICES];
	int	iNumDevs = 0;
	int	i, j;
	int	iDevicesOpen;
	FTDCB ftDCB, ftnewDCB;
	FTCOMSTAT ftComStat;
		
	for(i = 0; i < MAX_DEVICES; i++) {
		pcBufLD[i] = cBufLD[i];
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
		
	for(i = 0; ( (i <MAX_DEVICES) && (i < iNumDevs) ) ; i++) {
	
		memset(&ftDCB, 0, sizeof(FTDCB));
		
		ftHandle[i] = FT_W32_CreateFile(
						cBufLD[i],
						0,		// GENERIC_READ|GENERIC_WRITE ignored
						0,		// ignored
						0, 		// ignored
						0,		// OPEN_EXISTING ignored
						FT_OPEN_BY_SERIAL_NUMBER, // ignored FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED | FT_OPEN_BY_SERIAL_NUMBER,
						0		// ignored
						);
		/* Setup */
		if(ftHandle[i] == (FT_HANDLE)INVALID_HANDLE_VALUE){
			/* 
				This can fail if the ftdi_sio driver is loaded
		 		use lsmod to check this and rmmod ftdi_sio to remove
				also rmmod usbserial
		 	*/
			printf("Error FT_W32_CreateFile(%d), device\n", i);
			return 1;
		}
	
		printf("Opened device %s\n", cBufLD[i]);
		
		ftDCB.BaudRate = 9600;		
		
		if(FT_W32_SetCommState(ftHandle[i], &ftDCB) == FALSE) {
			ftStatus = FT_W32_GetLastError(ftHandle[i]);
			printf("Error FT_W32_SetCommState = %d)\n", ftStatus);
			return 1;
		}
		
		if(FT_W32_GetCommState(ftHandle[i], &ftnewDCB) == FALSE) {
			ftStatus = FT_W32_GetLastError(ftHandle[i]);
			printf("Error FT_W32_GetCommState = %d)\n", ftStatus);
			return 1;
		}
		
		if(ftnewDCB.BaudRate != ftDCB.BaudRate) {
			printf("New baud rate does not match baud rate set\n");
		}
				
		iDevicesOpen++;		
		
		cBufWrite[0] = 'h';
		cBufWrite[1] = 'e';
		cBufWrite[2] = 'l';
		cBufWrite[3] = 'l';
		cBufWrite[4] = 'o';
		cBufWrite[5] = ' ';
		cBufWrite[6] = 'f';
		cBufWrite[7] = 't';
		cBufWrite[8] = 'd';
		cBufWrite[9] = 'i';
		cBufWrite[10] = 'w';
		cBufWrite[11] = 'o';
		cBufWrite[12] = 'r';
		cBufWrite[13] = 'l';
		cBufWrite[14] = 'd';
		cBufWrite[15] = '\n';
		cBufWrite[16] = '\0';
		
		if(FT_W32_WriteFile(ftHandle[i], cBufWrite, BUF_SIZE, &dwBytesWritten, NULL) == FALSE) {
			ftStatus = FT_W32_GetLastError(ftHandle[i]);
			printf("Error FT_W32_WriteFile = %d)\n", ftStatus);
			return 1;
		}
		
		sleep(1);	// give it a chance to be received in a loopback test
		
		if(FT_W32_ClearCommError(ftHandle[i], &dwErrors, &ftComStat) == FALSE) {
			ftStatus = FT_W32_GetLastError(ftHandle[i]);
			printf("Error FT_W32_ClearCommError = %d)\n", ftStatus);
			return 1;
		}
		
		if(FT_W32_ReadFile(ftHandle[i], cBufWrite, ftComStat.cbInQue, &dwBytesRead, NULL) == FALSE) {
			ftStatus = FT_W32_GetLastError(ftHandle[i]);
			printf("Error FT_W32_ReadFile = %d)\n", ftStatus);
			return 1;
		}
		
		printf("dwBytesRead = %d\n", dwBytesRead);

	}
	iDevicesOpen = i;
	/* Cleanup */
	for(i = 0; i < iDevicesOpen; i++) {
		if(FT_W32_CloseHandle(ftHandle[i]) == FALSE) {
			ftStatus = FT_W32_GetLastError(ftHandle[i]);
			printf("Error FT_W32_CloseHandle = %d, device = %d)\n", ftStatus, i);
		}
		printf("Closed device %s\n", cBufLD[i]);
	}

	if(pcBufRead)
		free(pcBufRead);
	return 0;
}

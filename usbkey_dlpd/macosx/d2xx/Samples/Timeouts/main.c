/*
	A very simple example to show a 3 second timout when reading nothing from a 
	device. This example assumes that there is no hardware attached to the device
	so a timeout will occur after 3 seconds

	To build use the following gcc statement 
	(assuming you have the d2xx library in the /usr/local/lib directory).
	gcc -o timeouts main.c -L. -lftd2xx -Wl,-rpath /usr/local/lib
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "../ftd2xx.h"

#define BUF_SIZE 0x1000

// Globals
FT_HANDLE ftHandle = NULL;

void quit()
{  
	if(ftHandle != NULL) {
		FT_Close(ftHandle);
		ftHandle = NULL;
		printf("Closed device\n");
	}

	exit(1);
}

int main(int argc, char *argv[])
{
	char cBufRead[BUF_SIZE];
	DWORD dwBytesRead;
	FT_STATUS ftStatus;
	int iport;
	int i;

	if(argc > 1) {
		sscanf(argv[1], "%d", &iport);
	}
	else {
		iport = 0;
	}

    signal(SIGINT, quit);		// trap ctrl-c call quit fn 

	ftStatus = FT_Open(iport, &ftHandle);
	if(ftStatus != FT_OK) {
		/* 
			This can fail if the ftdi_sio driver is loaded
		 	use lsmod to check this and rmmod ftdi_sio to remove
			also rmmod usbserial
		 */
		printf("FT_Open(%d) failed\n", iport);
		return 1;
	}

	FT_SetTimeouts(ftHandle, 3000, 3000);	// 3 second read timeout

	for(i = 0; i < 10 ; i++) {
		FT_Read(ftHandle, cBufRead, BUF_SIZE, &dwBytesRead);
		if(dwBytesRead != BUF_SIZE)
			printf("Timeout %d\n", i);
		else
			printf("Read %d\n", dwBytesRead);
	}

	if(ftHandle != NULL) {
		FT_Close(ftHandle);
		ftHandle = NULL;
	}

	return 0;
}

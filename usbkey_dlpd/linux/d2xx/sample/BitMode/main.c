/*		
	To build use the following gcc statement 
	(assuming you have the d2xx library in the /usr/local/lib directory).
	gcc -o bitmode main.c -L. -lftd2xx -Wl,-rpath /usr/local/lib
*/

#include <stdio.h>
#include "../ftd2xx.h"

int main(int argc, char *argv[])
{
	DWORD dwBytesInQueue = 0;
	FT_STATUS	ftStatus;
	FT_HANDLE	ftHandle;
	unsigned char ucMode = 0x00;
	int iport;
	
	if(argc > 1) {
		sscanf(argv[1], "%d", &iport);
	}
	else {
		iport = 0;
	}
	
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
		
	ftStatus = FT_SetBitMode(ftHandle, 0xFF, 1);
	if(ftStatus != FT_OK) {
		printf("Failed to set bit mode\n");	
	}
	FT_SetBaudRate(ftHandle, 9600);
	
	FT_Write(ftHandle, &ucMode, 1, &dwBytesInQueue);

	ftStatus = FT_GetBitMode(ftHandle, &ucMode);
	if(ftStatus != FT_OK) {
		printf("Failed to get bit mode\n");
	}
	else {
		printf("ucMode = 0x%X\n", ucMode);	
	}

	FT_Close(ftHandle);
	
	return 0;
}

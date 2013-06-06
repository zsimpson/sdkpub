// ChipID.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>
#include "ftd2xx.h"
#include "FTChipID.h"
/*

g++ -o ChipID main.c -L. -lftchipid -Wl,-rpath /usr/local/lib

*/
int main(int argc, char* argv[])
{
	char Version[100];
	unsigned long NumDevices = 0, LocID = 0, ChipID = 0;
	char SerialNumber[256], Description[256], ErrorMessage[256];
	FTID_STATUS dStatus;
	FT_HANDLE ftHandle;
	FT_STATUS ftStatus;
	DWORD i, iNumDevs;
	FT_DEVICE_LIST_INFO_NODE *devInfo; 
	DWORD numDevs; 

	FTID_Constructor();	// allways call before any call to the libftchipid.so
	
	FTID_GetDllVersion(Version, 100);

	printf("Dll Version = %s\n\n", Version);
	
	dStatus = FTID_GetNumDevices(&NumDevices);

	if((dStatus == FTID_SUCCESS) && NumDevices) {

		printf("Number of 232R devices = %ld\n\n", NumDevices);

		for(int i = 0; i < (int)NumDevices; i++) {

			printf("Device %d\n", i);

			dStatus = FTID_GetDeviceSerialNumber(i, SerialNumber, 256);
			if(dStatus == FTID_SUCCESS) {
				printf("\tSerial Number: %s\n", SerialNumber);
			}

			dStatus = FTID_GetDeviceDescription(i, Description, 256);
			if(dStatus == FTID_SUCCESS) {
				printf("\tDescription: %s\n", Description);
			}

			dStatus = FTID_GetDeviceChipID(i, &ChipID);
			if(dStatus == FTID_SUCCESS) {
				printf("\tChip ID: 0x%08lX\n", ChipID);
			}
				
			printf("\n");
		}
	}	

	if(dStatus != FTID_SUCCESS) {
		FTID_GetErrorCodeString("EN", dStatus, ErrorMessage, 256);
		printf(ErrorMessage);
	}
	FTID_Destructor();	// call this when you wont be using the library any more
	
	
	//
	// Method on how to use the FTID_GetChipIDFromHandle API function
	//

	// 
	// create the device information list 
	// 
	ftStatus = FT_CreateDeviceInfoList(&numDevs); 
	if (ftStatus == FT_OK) { 
	   printf("Number of devices is %d\n",numDevs); 
	} 
	// 
	// allocate storage for list based on numDevs 
	// 
	devInfo = (FT_DEVICE_LIST_INFO_NODE*)malloc(sizeof(FT_DEVICE_LIST_INFO_NODE)*numDevs);
	
	if(devInfo == NULL) {
		printf("Insufficient resources to create device list\n");
		return 1;
	}
	
	//
	// get the device information list
	//
	ftStatus = FT_GetDeviceInfoList(devInfo, &iNumDevs);
	if (ftStatus == FT_OK) {
		for (i = 0; i < iNumDevs; i++) { 
			if(devInfo[i].Type == FT_DEVICE_232R) {
				FT_Open(i, &ftHandle);
				dStatus = FTID_GetChipIDFromHandle(ftHandle, &ChipID);
				if(dStatus == FTID_SUCCESS) {
					printf("\tChip ID: 0x%08lX\n", ChipID);
				}
				else {
					FTID_GetErrorCodeString("EN", dStatus, ErrorMessage, 256);
					printf(ErrorMessage);
				}
				FT_Close(ftHandle);
			}
		}
	} 		

	free(devInfo);
	printf("Press return to exit\n");
	getchar();

	return 0;
}

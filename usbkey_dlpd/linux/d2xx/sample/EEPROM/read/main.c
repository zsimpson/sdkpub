/*
	To build use the following gcc statement 
	(assuming you have the d2xx library in the /usr/local/lib directory).
	gcc -o read main.c -L. -lftd2xx -Wl,-rpath,/usr/local/lib
*/

#include <stdio.h>
#include <sys/time.h>
#include "../../ftd2xx.h"

int main(int argc, char *argv[])
{
	FT_STATUS	ftStatus;
	FT_HANDLE	ftHandle0;
	int iport;
	FT_PROGRAM_DATA Data;
	
	if(argc > 1) {
		sscanf(argv[1], "%d", &iport);
	}
	else {
		iport = 0;
	}
	printf("opening port %d\n", iport);
	
	ftStatus = FT_Open(iport, &ftHandle0);
	if(ftStatus != FT_OK) {
		/* 
			This can fail if the ftdi_sio driver is loaded
		 	use lsmod to check this and rmmod ftdi_sio to remove
			also rmmod usbserial
		 */
		printf("FT_Open(%d) failed\n", iport);
		return 1;
	}
	
	printf("ftHandle0 = %p\n", ftHandle0);

	Data.Signature1 = 0x00000000;
	Data.Signature2 = 0xffffffff;
	Data.Manufacturer = (char *)malloc(256);			// "FTDI"
	Data.ManufacturerId = (char *)malloc(256);		// "FT"
	Data.Description = (char *)malloc(256);			// "USB HS Serial Converter"
	Data.SerialNumber = (char *)malloc(256);			// "FT000001" if fixed, or NULL
	ftStatus = FT_EE_Read(ftHandle0, &Data);
	if(ftStatus != FT_OK) {
		printf("FT_EE_Read failed\n");
		FT_Close(ftHandle0);
		return 1;
	}
		
	FT_Close(ftHandle0);

	printf("Signature1 = %d\n", Data.Signature1);			
	printf("Signature2 = %d\n", Data.Signature2);			
	printf("Version = %d\n", Data.Version);				
								
	printf("VendorId = 0x%04X\n", Data.VendorId);				
	printf("ProductId = 0x%04X\n", Data.ProductId);
	printf("Manufacturer = %s\n", Data.Manufacturer);			
	printf("ManufacturerId = %s\n", Data.ManufacturerId);		
	printf("Description = %s\n", Data.Description);			
	printf("SerialNumber = %s\n", Data.SerialNumber);			
	printf("MaxPower = %d\n", Data.MaxPower);				
	printf("PnP = %d\n", Data.PnP) ;					
	printf("SelfPowered = %d\n", Data.SelfPowered);			
	printf("RemoteWakeup = %d\n", Data.RemoteWakeup);			
	//
	// Rev4 extensions
	//
	printf("Rev4 = 0x%X\n", Data.Rev4);					
	printf("IsoIn = 0x%X\n", Data.IsoIn);				
	printf("IsoOut = 0x%X\n", Data.IsoOut);				
	printf("PullDownEnable = 0x%X\n", Data.PullDownEnable);		
	printf("SerNumEnable = 0x%X\n", Data.SerNumEnable);			
	printf("USBVersionEnable = 0x%X\n", Data.USBVersionEnable);		
	printf("USBVersion = 0x%X\n", Data.USBVersion);

	//
	// FT2232C extensions
	//
	printf("Rev5 = 0x%X\n", Data.Rev5);					
	printf("IsoInA = 0x%X\n", Data.IsoInA);				
	printf("IsoInB = 0x%X\n", Data.IsoInB);				
	printf("IsoOutA = 0x%X\n", Data.IsoOutA);				
	printf("IsoOutB = 0x%X\n", Data.IsoOutB);				
	printf("PullDownEnable5 = 0x%X\n", Data.PullDownEnable5);		
	printf("SerNumEnable5 = 0x%X\n", Data.SerNumEnable5);		
	printf("USBVersionEnable5 = 0x%X\n", Data.USBVersionEnable5);	
	printf("USBVersion5 = 0x%X\n", Data.USBVersion5);			
	printf("AIsHighCurrent = 0x%X\n", Data.AIsHighCurrent);		
	printf("BIsHighCurrent = 0x%X\n", Data.BIsHighCurrent);		
	printf("IFAIsFifo = 0x%X\n", Data.IFAIsFifo);			
	printf("IFAIsFifoTar = 0x%X\n", Data.IFAIsFifoTar);			
	printf("IFAIsFastSer = 0x%X\n", Data.IFAIsFastSer);			
	printf("AIsVCP = 0x%X\n", Data.AIsVCP);				
	printf("IFBIsFifo = 0x%X\n", Data.IFBIsFifo);			
	printf("IFBIsFifoTar = 0x%X\n", Data.IFBIsFifoTar);			
	printf("IFBIsFastSer = 0x%X\n", Data.IFBIsFastSer);			
	printf("BIsVCP = 0x%X\n", Data.BIsVCP);	
	
	//
	// FT232R extensions
	//
	printf("UseExtOsc = 0x%X\n", Data.UseExtOsc);			// Use External Oscillator
	printf("HighDriveIOs = 0x%X\n", Data.HighDriveIOs);			// High Drive I/Os
	printf("EndpointSize = 0x%X\n", Data.EndpointSize);			// Endpoint size

	printf("PullDownEnableR = 0x%X\n", Data.PullDownEnableR);		// non-zero if pull down enabled
	printf("SerNumEnableR = 0x%X\n", Data.SerNumEnableR);		// non-zero if serial number to be used

	printf("InvertTXD = 0x%X\n", Data.InvertTXD);			// non-zero if invert TXD
	printf("InvertRXD = 0x%X\n", Data.InvertRXD);			// non-zero if invert RXD
	printf("InvertRTS = 0x%X\n", Data.InvertRTS);			// non-zero if invert RTS
	printf("InvertCTS = 0x%X\n", Data.InvertCTS);			// non-zero if invert CTS
	printf("InvertDTR = 0x%X\n", Data.InvertDTR);			// non-zero if invert DTR
	printf("InvertDSR = 0x%X\n", Data.InvertDSR);			// non-zero if invert DSR
	printf("InvertDCD = 0x%X\n", Data.InvertDCD);			// non-zero if invert DCD
	printf("InvertRI = 0x%X\n", Data.InvertRI);				// non-zero if invert RI

	printf("Cbus0 = 0x%X\n", Data.Cbus0);				// Cbus Mux control
	printf("Cbus1 = 0x%X\n", Data.Cbus1);				// Cbus Mux control
	printf("Cbus2 = 0x%X\n", Data.Cbus2);				// Cbus Mux control
	printf("Cbus3 = 0x%X\n", Data.Cbus3);				// Cbus Mux control
	printf("Cbus4 = 0x%X\n", Data.Cbus4);				// Cbus Mux control

	printf("RIsVCP = 0x%X\n", Data.RIsVCP);				// non-zero if using VCP drivers
	
	
	free(Data.Manufacturer);
	free(Data.ManufacturerId);
	free(Data.Description);
	free(Data.SerialNumber);
	
	return 0;
}

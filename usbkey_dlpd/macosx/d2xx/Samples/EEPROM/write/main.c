/*
	To build use the following gcc statement 
	(assuming you have the d2xx library in the /usr/local/lib directory).
	gcc -o write main.c -L. -lftd2xx -Wl,-rpath,/usr/local/lib
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
	FT_DEVICE	ftDevice; 
	
	if(argc > 1) {
		sscanf(argv[1], "%d", &iport);
	}
	else {
		iport = 0;
	}
	printf("opening port %d\n", iport);
	FT_SetVIDPID(0x0403, 0x6017);
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

		ftStatus = FT_GetDeviceInfo( 
				ftHandle0, 
				&ftDevice, 
				NULL, 
				NULL, 
				NULL, 
				NULL 
				); 

	if (ftStatus != FT_OK) { 
		printf("FT_GetDeviceType FAILED!\n");
		return 1;
	}  

	if (ftDevice == FT_DEVICE_BM) {

		Data.Signature1 = 0x00000000;
		Data.Signature2 = 0xffffffff;
		Data.VendorId = 0x0403;				
		Data.ProductId = 0x6001;
		Data.Manufacturer =  "FTDI";
		Data.ManufacturerId = "FT";
		Data.Description = "USB <-> Srial";
		Data.SerialNumber = "FT000001";		// if fixed, or NULL
		
		Data.MaxPower = 44;
		Data.PnP = 1;
		Data.SelfPowered = 0;
		Data.RemoteWakeup = 1;
		Data.Rev4 = 1;
		Data.IsoIn = 0;
		Data.IsoOut = 0;
		Data.PullDownEnable = 1;
		Data.SerNumEnable = 1;
		Data.USBVersionEnable = 0;
		Data.USBVersion = 0x110;

	}
	else if (ftDevice == FT_DEVICE_232R) {

		Data.Signature1 = 0x00000000;
		Data.Signature2 = 0xffffffff;
		Data.Version = 2;
		Data.VendorId = 0x0403;				
		Data.ProductId = 0x6001 ;
		Data.Manufacturer =  "FTDI";
		Data.ManufacturerId = "FT";
		Data.Description = "USB <-> Serial";
		Data.SerialNumber = "FT000008";		// if fixed, or NULL
		
		Data.MaxPower = 100;
		Data.PnP = 1;
		Data.SelfPowered = 0;
		Data.RemoteWakeup = 1;
			
		Data.UseExtOsc = 0x00;			// Use External Oscillator
		Data.HighDriveIOs = 0x00;			// High Drive I/Os
		Data.EndpointSize = 0x40;			// Endpoint size

		Data.PullDownEnableR = 0x00;		// non-zero if pull down enabled
		Data.SerNumEnableR = 0x01;		// non-zero if serial number to be used

		Data.InvertTXD = 0x00;			// non-zero if invert TXD
		Data.InvertRXD = 0x00;			// non-zero if invert RXD
		Data.InvertRTS = 0x00;			// non-zero if invert RTS
		Data.InvertCTS = 0x00;			// non-zero if invert CTS
		Data.InvertDTR = 0x00;			// non-zero if invert DTR
		Data.InvertDSR = 0x00;			// non-zero if invert DSR
		Data.InvertDCD = 0x00;			// non-zero if invert DCD
		Data.InvertRI = 0x00;				// non-zero if invert RI

		Data.Cbus0 = 0x02;				// Cbus Mux control
		Data.Cbus1 = 0x03;				// Cbus Mux control
		Data.Cbus2 = 0x01;				// Cbus Mux control
		Data.Cbus3 = 0x01;				// Cbus Mux control
		Data.Cbus4 = 0x05;				// Cbus Mux control

		Data.RIsVCP = 0;				// non-zero if using VCP drivers

	}
	else if (ftDevice == FT_DEVICE_2232C) {

		Data.Signature1 = 0x00000000;
		Data.Signature2 = 0xffffffff;
		Data.VendorId = 0x0403;				
		Data.ProductId = 0x6010;
		Data.Manufacturer =  "FTDI";
		Data.ManufacturerId = "FT";
		Data.Description = "USB <-> Serial";
		Data.SerialNumber = "FT123442";		// if fixed, or NULL
		
		Data.MaxPower = 200;
		Data.PnP = 1;
		Data.SelfPowered = 0;
		Data.RemoteWakeup = 0;

		Data.Rev5 = 1;					// non-zero if Rev5 chip, zero otherwise
		Data.IsoInA = 0;				// non-zero if in endpoint is isochronous
		Data.IsoInB = 0;				// non-zero if in endpoint is isochronous
		Data.IsoOutA = 0;				// non-zero if out endpoint is isochronous
		Data.IsoOutB = 0;				// non-zero if out endpoint is isochronous
		Data.PullDownEnable5 = 0;		// non-zero if pull down enabled
		Data.SerNumEnable5 = 1;			// non-zero if serial number to be used
		Data.USBVersionEnable5 = 0;		// non-zero if chip uses USBVersion
		Data.USBVersion5 = 0x0200;		// BCD (0x0200 => USB2)
		Data.AIsHighCurrent = 0;		// non-zero if interface is high current
		Data.BIsHighCurrent = 0;		// non-zero if interface is high current
		Data.IFAIsFifo = 0;				// non-zero if interface is 245 FIFO
		Data.IFAIsFifoTar = 0;			// non-zero if interface is 245 FIFO CPU target
		Data.IFAIsFastSer = 0;			// non-zero if interface is Fast serial
		Data.AIsVCP = 0;				// non-zero if interface is to use VCP drivers
		Data.IFBIsFifo = 0;				// non-zero if interface is 245 FIFO
		Data.IFBIsFifoTar = 0;			// non-zero if interface is 245 FIFO CPU target
		Data.IFBIsFastSer = 0;			// non-zero if interface is Fast serial
		Data.BIsVCP = 0;				// non-zero if interface is to use VCP drivers

	}								

	ftStatus = FT_EE_Program(ftHandle0, &Data);
	if(ftStatus != FT_OK) {
		printf("FT_EE_Program failed (%d)\n", ftStatus);
	}
	FT_Close(ftHandle0);
	return 0;
}

FTChipID for Linux.

This shared object can be used on x86 based Linux systems to extract the ChipID 
from a 232R device.

The API is fairly simple and can be used along with the d2xx driver (see 
www.ftdichip.com) to extract the 232R ChipID.

FTID_Constructor	-- 	constructor function to create the c++ object to access
						the	library
FTID_Destructor		--	For memory cleanup after calling FTID_Constructor
FTID_GetNumDevices	--	Returns the number of 232R devices on USB bus
FTID_GetDeviceSerialNumber	-- Returns the serial number for supplied index
FTID_GetDeviceDescription	-- Returns the device dexription for supplied index
FTID_GetDeviceChipID	-- Returns the ChipID for supplied index
FTID_GetDllVersion	-- Returns shared library version
FTID_GetErrorCodeString	-- Returns the error string relating to the error code supplied

Notes:
You must install the D2XX driver to enable this shared library to work

This shared library has been tested on some 2.4 and 2.6 kernels with varying 
degrees of success. I found that 2.6.7 kernel will not work - no solution appart from
upgrading kernel. If you find other kernels dont work then contact support2@ftdichip.com
and we will test it out at FTDI.

Sample code is provided in a c example.

Library is compiled using gcc 3.3.1.

No static library is provided at present.

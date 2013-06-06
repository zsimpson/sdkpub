#ifndef __FTCHIPID_H_
#define __FTCHIPID_H_

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the FTCHIPID_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// FTCHIPID_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.

#if defined(LINUX) || defined(_OSX_) || defined(__APPLE__)
#pragma error "oink"
#define __declspec(dllexport)
#define FTCHIPID_API 
#define WINAPI 
#include "WinTypes.h"

#else

#ifdef FTCHIPID_EXPORTS
#define FTCHIPID_API __declspec(dllexport)
#else
#define FTCHIPID_API __declspec(dllimport)
#endif

#endif

typedef unsigned long FTID_STATUS;

// this can be moved to the API header
#define FTID_SUCCESS						0
#define FTID_INVALID_HANDLE					1 // FT_INVALID_HANDLE
#define FTID_DEVICE_NOT_FOUND				2 // FT_DEVICE_NOT_FOUND
#define FTID_DEVICE_NOT_OPENED				3 // FT_DEVICE_NOT_OPENED
#define FTID_IO_ERROR						4 // FT_IO_ERROR
#define FTID_INSUFFICIENT_RESOURCES			5 // FT_INSUFFICIENT_RESOURCES
#define FTID_INVALID_PARAMETER				6 // FT_INVALID_PARAMETER

#define FTID_BUFFER_SIZE_TOO_SMALL			20
#define FTID_PASSED_NULL_POINTER			21
#define FTID_INVALID_LANGUAGE_CODE			22
#define FTID_INVALID_RHANDLE				23
#define FTID_INVALID_STATUS_CODE			0xFFFFFFFF

#ifdef __cplusplus
extern "C" {
#endif

#if defined (LINUX) || defined(_OSX_) || defined(__APPLE__)
FTCHIPID_API
BOOL FTID_Constructor();	// MUST be called before starting the app

FTCHIPID_API
BOOL FTID_Destructor();		// MUST be called for cleanup
#endif

// Device Related

FTCHIPID_API
FTID_STATUS WINAPI FTID_GetNumDevices(unsigned long * Devices);

FTCHIPID_API
FTID_STATUS WINAPI FTID_GetDeviceSerialNumber(unsigned long DeviceIndex, char * SerialBuffer, unsigned long SerialBufferLength);

FTCHIPID_API
FTID_STATUS WINAPI FTID_GetDeviceDescription(unsigned long DeviceIndex, char * DescriptionBuffer, unsigned long DescriptionBufferLength);

#if !defined (LINUX) && !defined(_WIN_CE_) && !defined(_OSX_) && !defined(__APPLE__) 
FTCHIPID_API
FTID_STATUS WINAPI FTID_GetDeviceLocationID(unsigned long DeviceIndex, unsigned long * LocationIDBuffer);
#endif

FTCHIPID_API
FTID_STATUS WINAPI FTID_GetDeviceChipID(unsigned long DeviceIndex, unsigned long * ChipIDBuffer);

FTCHIPID_API
FTID_STATUS WINAPI FTID_GetChipIDFromHandle(FT_HANDLE Handle, unsigned long * ChipIDBuffer);

// General
FTCHIPID_API
FTID_STATUS WINAPI FTID_GetDllVersion(char * VersionBuffer, unsigned long VersionBufferSize);

FTCHIPID_API
FTID_STATUS WINAPI FTID_GetErrorCodeString(char * Language, FTID_STATUS ErrorCode, char * ErrorBuffer, unsigned long ErrorBufferLength);

#ifdef __cplusplus
}
#endif


#endif

#ifndef __WINDOWS_TYPES__
#define __WINDOWS_TYPES__

#define MAX_NUM_DEVICES 50
#include <sys/time.h>

typedef unsigned long 	DWORD;
typedef unsigned long 	ULONG;
typedef unsigned short 	USHORT;
typedef short 			SHORT;
typedef unsigned char	UCHAR;
typedef unsigned short	WORD;
typedef unsigned char	BYTE;
typedef unsigned char	*LPBYTE;
typedef int 		BOOL;
typedef char 		BOOLEAN;
typedef char 		CHAR;
typedef int 		*LPBOOL;
typedef unsigned char 	*PUCHAR;
typedef const char	*LPCSTR;
typedef char		*PCHAR;
typedef void 		*PVOID;
typedef void 		*HANDLE;
typedef long 		LONG;
typedef int 		INT;
typedef unsigned int 	UINT;
typedef char 		*LPSTR;
typedef char 		*LPTSTR;
typedef DWORD 		*LPDWORD;
typedef WORD 		*LPWORD;
typedef ULONG		*PULONG;
typedef PVOID		LPVOID;
typedef void		VOID;
typedef unsigned long long int ULONGLONG;

typedef struct _OVERLAPPED {
	DWORD Internal;
	DWORD InternalHigh;
	DWORD Offset;
	DWORD OffsetHigh;
	HANDLE hEvent;
} OVERLAPPED, *LPOVERLAPPED;

typedef struct _SECURITY_ATTRIBUTES {
	DWORD nLength;
	LPVOID lpSecurityDescriptor;
	BOOL bInheritHandle;
} SECURITY_ATTRIBUTES , *LPSECURITY_ATTRIBUTES;

typedef struct timeval SYSTEMTIME;
typedef struct timeval FILETIME;
#ifndef TRUE
#define TRUE	1
#endif
#ifndef FALSE
#define FALSE	0
#endif
#endif

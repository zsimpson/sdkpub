// gsl18_vc6.cpp : Defines the entry point for the DLL application.
//

#include <windows.h>
#include "gsl18_vc6.h"
#include "stdio.h"
#include "conio.h"
#include "fcntl.h"
#include "io.h"


BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}


// This is an example of an exported variable
GSL18_VC6_API int nGsl18_vc6=0;

// This free fn is exported from the dll.  Used by zlab programs to force this dll
// to printf etc... to our dos box.
GSL18_VC6_API void gsl_set_stdout(long hStdout)
{
	// REDIRECT stdout
	// long hStdout = (long)GetStdHandle( STD_OUTPUT_HANDLE );
	*stdout = *_fdopen( _open_osfhandle( hStdout, _O_TEXT ), "w" );
	setvbuf( stdout, NULL, _IONBF, 0 ); }

// This is the constructor of a class that has been exported.
// see gsl18_vc6.h for the class definition
CGsl18_vc6::CGsl18_vc6()
{ 
	return; 
}


#ifndef _DATA_AND_MORPHING_H_
#define _DATA_AND_MORPHING_H_	
#include "VMDemoTk.h"


	int MemoryAllocation();
	int loaddata(Tcl_Interp  *interp);


	int OnMakeMorphing(float sk, Tcl_Interp  *interp);

	int FreeMemory();

    extern IplImage* datal;
    extern IplImage* datar;


#endif


	

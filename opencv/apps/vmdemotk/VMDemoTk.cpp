#include "VMDemoTk.h"
#include "VMDemoTkInit.h"

bool HaveMorph;
int*    scanlines_1;
int*    scanlines_2;
int*    scanlines_a;
int numScanlines;
CvSize      imgsize = {320, 240};

int TclInit(Tcl_Interp *interp, char **argv)
{
    if (Tcl_Init(interp) == TCL_ERROR)          
    {
        fprintf(stderr, "Tcl_Init failed: %s\n",
            interp->result);
        return 1;
    }

    if (Tk_Init(interp) == TCL_ERROR)
    {
        fprintf(stderr, "Tk_Init failed: %s\nwwwwwwwwwwwwww\n",
            interp->result);
        return 1;
    }

    return 0;
}


int main(int argc, char **argv)
{
    Tcl_Interp  *interp= Tcl_CreateInterp();
    if(!interp)
    {
        printf("No interpretator\n");
        return 1;
    }
    
    if (VMDemoTkInit ( interp, argc, argv)) return 1;
    Tk_MainLoop();
    
    return 0;
}

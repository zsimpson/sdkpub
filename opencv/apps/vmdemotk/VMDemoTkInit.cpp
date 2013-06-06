#include "VMDemoTkInit.h"
#include "VMDemoTk.h"
#include "NewTclCommands.h"	
#include <highgui.h>

int VMDemoTkInit ( Tcl_Interp *interp, int argc, char **argv)
{
    // creating the interpreter for tcl application
    if(!interp)
        interp = Tcl_CreateInterp();    
    if(!interp)
    {
        printf("No interpretator\n");
        return 1;
    }
    
    // finding out application location
    Tcl_FindExecutable(argv[0]);    
    
    // Here begins the first step on C and TCL
    // integration: The Tcl/Tk initialization.
    if (Tcl_Init(interp) == TCL_ERROR)          
    {
        fprintf(stderr, "Tcl_Init failed: %s\n",
            interp->result);
        return 1;
    }
    
    if (Tk_Init(interp) == TCL_ERROR)
    {
        fprintf(stderr, "Tk_Init failed: %s\n",
            interp->result);
        return 1;
    }
    
    
    //The second step, creating new Tcl commands for user interface widgets.
    
    // procedure for "set original windows position" button
    Tcl_CreateCommand (interp, "CSetpos", TKVMDemo_Setposition, 
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);  
    
    // fileopen dialog and procedure
    Tcl_CreateCommand (interp, "Cfileopen", TKVMDemo_fileopen,
        (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);
    
    // Command for slider
    Tcl_CreateCommand( interp, "Cscale", TKVMDemo_scale,
                       (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);
    
    // Command for showscanlines checkbutton
    Tcl_CreateCommand( interp, "CShowScanlines", TKVMDemo_ShowScanlines,
                       (ClientData *) NULL, (Tcl_CmdDeleteProc *) NULL);
    
    Tcl_CreateThreadExitHandler(OnExit, (ClientData *) NULL);
    
    //Now we evaluate the user interface script
    if(Tcl_EvalFile(interp, "interface.tcl") == TCL_ERROR)
    {
        printf("%s\nline %d\n", interp->result, interp->errorLine);
        return 1;
    }
    
    //Setting windows to the original position
    Tcl_Eval(interp, "CSetpos");
    
    cvvInitSystem(argc, argv);
    cvvNamedWindow( "left", 0 );
    cvvNamedWindow( "right", 0 );
    cvvNamedWindow( "result", 0 );
    
    return 0;
}

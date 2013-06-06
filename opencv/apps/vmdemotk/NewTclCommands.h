#ifndef _NEW_TCL_COMMANDS_H_
#define _NEW_TCL_COMMANDS_H_

#include "VMDemoTk.h"



int TKVMDemo_Setposition(ClientData cd, Tcl_Interp *interp,
		  int argc, char **argv);
int TKVMDemo_fileopen(ClientData cd, Tcl_Interp *interp,
		  int argc, char **argv);
int TKVMDemo_scale(ClientData cd, Tcl_Interp *interp,
		  int argc, char **argv);
int TKVMDemo_ShowScanlines(ClientData cd, Tcl_Interp *interp,
		  int argc, char **argv);

void	OnExit(ClientData clientData);

#endif

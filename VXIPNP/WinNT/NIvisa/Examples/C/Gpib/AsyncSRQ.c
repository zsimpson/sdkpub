/**************************************************************************/
/*                   Asynchronous SRQ Event Handling Example              */
/*                                                                        */
/* This example shows how to use an asynchronous event handling function  */
/* that is called when a service request (SRQ) is issued.                 */
/* This code uses VISA functions and sets a flag in the handler for the   */
/* occurrence of a service request from a GPIB device to break out of     */
/* an otherwise infinite loop.  The flow of the code is as follows:       */
/*                                                                        */
/*  Open A Session To The VISA Resource Manager                           */
/*  Open A Session To A GPIB Device                                       */
/*  Install An Event Handler For SRQ Events                               */
/*  Enable SRQ Events                                                     */
/*  Write A Command To The Instrument To Cause It To Generate An SRQ      */
/*  Start An Infinite Loop That Can Only Be Stopped By A Handler Flag     */
/*  Print Out The Data                                                    */
/*  Close The Instrument Session                                          */
/*  Close The Resource Manager Session                                    */
/**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "visa.h"

/*  Prototype for the SRQ event handler   */
ViStatus _VI_FUNCH SRQhandler(ViSession vi, ViEventType etype, ViEvent event, ViAddr userHandle);


static unsigned char data[1024];
static ViAddr uhandle;
static ViStatus status;
static ViUInt32 BytesToRead;
static ViSession inst;
static ViSession defaultRM;
static ViSession Sessionparam;
static ViEventType EventTypeparam;
static ViAddr Addressparam;
static ViUInt32 rcount, rdcount=0;
static ViBoolean stopflag = VI_FALSE;
static int letter;
static char stringinput[1024], stringinstruct[1024];


/*
 * The instrument session, the type of event, and a handle to the event are 
 * passed to the event handler function along with a user handle which is basically a 
 * label that could be used to reference the handler.
 * First, the event handler calls viReadSTB() to get the serial poll byte from the
 * instrument.  With GPIB SRQ events, viReadSTB() must be called otherwise
 * later SRQ events will not be detected.  The handler then reads in the
 * data to a global variable and sets a flag that allows the program to
 * finish.  This is an instrument specific implementation that requires 
 * viWrite() and viRead() to be called here.  Always return VI_SUCCESS from your handler.
 */
ViStatus _VI_FUNCH SRQhandler(ViSession vi, ViEventType etype, ViEvent event, ViAddr userHandle)
{
    ViUInt16 stb;

    Sessionparam = vi;
    EventTypeparam = etype;
    Addressparam = userHandle;

    status = viReadSTB (inst, &stb);
    strcpy (stringinput,"SENS: DATA?\n");
    status = viWrite (vi, (ViBuf)stringinput,strlen(stringinput), &rcount);
    BytesToRead = 1024;
    status = viRead (vi, data, BytesToRead, &rdcount);
    stopflag = VI_TRUE;

    return VI_SUCCESS;
}


int main(void)
{
    /*
     *  First we open a session to the VISA resource manager.  We are
     *  returned a handle to the resource manager session that we must
     *  use to open sessions to specific instruments.
     */
    status = viOpenDefaultRM (&defaultRM);
    if (status < VI_SUCCESS)
    {
      printf("Could not open a session to the VISA Resource Manager!\n");
      exit (EXIT_FAILURE);
    }
    
    /*
     *  Next we use the resource manager handle to open a session to a
     *  GPIB instrument at address 2.  A handle to this session is
     *  returned in the handle inst.
     */
    status = viOpen (defaultRM, "GPIB::2::INSTR", VI_NULL, VI_NULL, &inst);
    if (status < VI_SUCCESS)
    {
        printf("Could not open a session to the device simulator\nHit enter to continue.");
        fflush(stdin);
        getchar();
        goto Close;
    }
    
    /*
     *  Now we install the handler for service request events.
     *  We must pass our instrument session to the handler, the type of
     *  event to handle, the handler function name and a user handle
     *  which acts as a user-defined handle passed to the handler 
     *  function.
     */
    status = viInstallHandler (inst, VI_EVENT_SERVICE_REQ, SRQhandler, uhandle);
    if (status < VI_SUCCESS)
    {
        printf("The event handler could not be successfully installed.\nHit enter to continue.");
        fflush(stdin);
        getchar();
        goto Close;
    }
    
    /*  Now we must actually enable the service request event so that our
     *  handler will see the events.  Note that one of the parameters is 
     *  VI_HNDLR indicating that we want the SRQ events to be handled by
     *  an asynchronous handler.  The alternate mechanism for handling
     *  events is to queue them and read events from the queue when
     *  you want to dequeue them in your program.
     */
    status = viEnableEvent (inst, VI_EVENT_SERVICE_REQ, VI_HNDLR, VI_NULL);
    if (status < VI_SUCCESS)
    {
        printf("The SRQ event could not be enabled.\nHit enter to continue.");
        fflush(stdin);
        getchar();
        goto Close;
    }
    
    /* 
     *  Now the VISA write function is used to instruct the
     *  instrument to generate a sine wave and assert the SRQ line
     *  when it is finished.  Notice that this is specific to one 
     *  particular instrument.
     */
    strcpy (stringinstruct,"*ESE 0x01; *SRE 0x20; SOUR:FUNC SIN; *OPC\n");
    status = viWrite (inst, (ViBuf)stringinstruct,strlen(stringinstruct), &rcount);

    printf("The program has passed all of the other status tests.\n");
    if (status < VI_SUCCESS)
    {
        printf("Error writing to the instrument.\nHit enter to continue.");
        fflush(stdin);
        getchar();
        goto Close;
        
    }

    /*
     *  Now the program goes into a wait loop which will only terminate
     *  if a service request event triggers the asynchronous callback.
     */
    printf("Hit enter to continue.");
    letter = getchar();


    /* 
     *  If the asynchronous event handler was called, then stopflag was set.
     *  Now, we print out the data read back.
     */
    if (stopflag == VI_TRUE)
    {
        /* rdcount was set in callback */
         printf ("Here is the data %*s\n", rdcount, data);
         printf ("Hit enter to continue.");
         fflush(stdin);
         getchar();
    }

    /*  
     *  Now we must uninstall the event handler, and close the session to 
     *  the instrument and the session to the resource manager.
     */
    status = viUninstallHandler (inst, VI_EVENT_SERVICE_REQ, SRQhandler, uhandle);
    if (status < VI_SUCCESS)
    {
        printf("There was an error uninstalling the handler.\nHit enter to continue.");
        fflush(stdin);
        getchar();
    }

Close:
    status = viClose (inst);
    status = viClose (defaultRM);
    return 0;
}


/**********************************************************************/
/*          Asynchronous Interrupt Handling Example                   */
/*                                                                    */
/* This code opens a session to a controller at Logical Address zero  */
/* This example installs an event handler to receive interrupts or    */
/* signals.  The program can be easily tested by running it and then  */
/* asserting interrupts using VXI Interactive Control, VIC.           */
/* VIC can be used to assert an interrupt or generate a signal.       */
/* Send the StatusId = 0xfd00 for this example.  The driver does not  */
/* pass interrupts generated from National Instruments' controllers   */
/* with certain StatusId values to the event handler.                 */
/*                                                                    */
/* The general flow of this code is:                                  */
/* Open Resource Manager                                              */
/* Open VISA session to an instrument                                 */
/* Enable A Handler For Interrupt Events                              */
/* Wait For An Interrupt Event                                        */
/* (Assert An Interrupt From VIC)                                     */
/* Continue to Wait For Interrupt Events Until User Ends Program      */
/* Close the VISA session                                             */
/**********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "visa.h"

static ViUInt16 StatusID;
static ViSession instr;
static ViSession defaultRM;
static ViStatus status;
static int tempchar;

ViStatus _VI_FUNCH IntrHandler(ViSession instr, ViEventType etype, ViEvent event, ViAddr userhandle);

/*
 * Here we define the function that is called whenever an interrupt event
 * is received.
 */
ViStatus _VI_FUNCH IntrHandler(ViSession instr, ViEventType etype, ViEvent event, ViAddr userhandle)
{
   /* etype is a number which identifies the event type that has been received. */
   viGetAttribute (event, VI_ATTR_SIGP_STATUS_ID, &StatusID);
   printf("An event was received.  The Status/ID value is 0x%x\n",StatusID);

   /* System calls are allowed to be used inside the event handler on
    all VISA supported platforms other than Macintosh. */
   return VI_SUCCESS;
}

/*
 * main code.
 */
int main (void)
{
   /*
    * First we must call viOpenDefaultRM to get the manager
    * handle.  We will store this handle in defaultRM.
    */
   status=viOpenDefaultRM (&defaultRM);
   if (status < VI_SUCCESS)  
   {
      printf("Could not open a session to the VISA Resource Manager!\n");
      exit (EXIT_FAILURE);
   } 

   /*
    * Note: at this point it would be proper programming procedure to
    * to call viFindRsrc to find available instruments to which we can
    * open a session.  The viFindRsrc function returns the descriptor
    * for the first of these instrument.  viFindNext can then be used to
    * get descriptors for the other instruments.  These descriptors
    * are then used to open a session to the desired instrument.
    * For simplicity, we will assume there is a controller
    * at Logical Address zero and open a session to this address.
    */

   /*
    * Now we will open a VISA session to the device at logical
    * address zero.  We must use the resource manager handle
    * from viOpenDefaultRM.  We must also use a string which will
    * indicate which instrument to open.  This is called the
    * instrument descriptor.  The format for this string can
    * be found in the NI-VISA User Manual. After opening a session to the
    * device, we will get a handle to the instrument which we
    * will use in later VISA functions.  The remaining two parameters
    * in this function are reserved for future functionality.
    * They are given the values VI_NULL.
    */
   status = viOpen (defaultRM, "VXI::0::INSTR", VI_NULL, VI_NULL, &instr);
   if (status < VI_SUCCESS)
   {
      printf("Can not open a VISA session to VXI0::0::INSTR\n");
      viClose (defaultRM);
      exit (EXIT_SUCCESS);
   }

   /*
    * Now we will install the event handler that will monitor interrupt
    * events.  The handler is named IntrHandler.  uhandle is a handle
    * allowing data to be passed to the handler from the application.
    */
   status = viInstallHandler (instr, VI_EVENT_VXI_SIGP, IntrHandler, VI_NULL);
   if (status < VI_SUCCESS)
   {
      printf("Could not install the interrupt handler.\n");
      viClose (defaultRM);
      exit (EXIT_SUCCESS);
   }

   /*
    * Now we will enable signal processing events so the program can
    * receive them into its event handler.  It will only receive events for
    * interrupts or signals.  See the other interrupt example to see how things
    * would differ if events were queued.
    */
   status = viEnableEvent (instr, VI_EVENT_VXI_SIGP, VI_HNDLR, VI_NULL);
   if (status < VI_SUCCESS)
   {
      printf("Could not enable the interrupt event.\n");
      viClose (defaultRM);
      exit (EXIT_SUCCESS);
   }

   /*
    *  Under Windows 3.x or the Macintosh, Yield() or PeekMessage() functions
    *  may need to be called to give up processor time so that VISA events
    *  will be invoked.  Under WIN32 or UNIX, this is not necessary because
    *  VISA event handlers are spawned in a separate thread.
    */      
   printf("Press any key to stop waiting for events.\n");
   fflush(stdin);
   tempchar=getchar();

   /*
    * The VXI Interactive Control program, VIC, can be used to
    * assert an interrupt or generate a signal.  Send the StatusId = 0xFD00
    * for this example.  The driver does not pass interrupts generated from
    * National Instruments' controllers with certain StatusId values to
    * to the event handler.
    */

   /* Now we will uninstall the handler we installed to handle interrupts
    * Calling this function will implicitly call viDisableEvent().
    * Note that unlike viWaitonEvent, the event is closed for us when we
    * exit the handler.  Compare this with the other interrupt example. */
   status = viUninstallHandler (instr, VI_EVENT_VXI_SIGP, IntrHandler, VI_NULL);

    /* Now we will close the session to the instrument using
     * viClose. We will tell VISA what to close using the handle, "instr".  */
   viClose (instr);
   viClose (defaultRM);
   printf("\nHit Enter to continue.");
   fflush(stdin);
   getchar();

   return 0;
}


/**********************************************************************/
/*            Synchronous Interrupt Events Example                    */
/*                                                                    */
/*  This example is written using VISA.                               */
/*  This code opens a session to a controller at Logical Address zero */
/*  Then configures an event queue to receive interrupts.             */
/*  The program can be exercised by running it and then asserting an  */
/*  interrupt with VIC, the VXI Interactive Control program.          */
/*                                                                    */
/* The general flow of this code is:                                  */
/* Open Resource Manager                                              */
/*  Open VISA session to an instrument                                */
/*  Enable Signal Processing Events To Be Queued                      */
/*  Wait For An Interrupt Event                                       */
/*  [Assert an Interrupt from VIC -  AssertVXIint( 0, 1, 0xFD00 )]    */
/*  Check The Status ID Of The Interrupt Event                        */
/*  Close the VISA session                                            */
/**********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "visa.h"

static ViSession defaultRM;
static ViSession instr;
static ViUInt32 WaitTimeout;
static ViEvent event;
static ViEventType etype;
static ViUInt16 intrID;
static ViStatus status;

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
      printf ("Cannot open a session to the device.\n");
      viClose (defaultRM);
      exit (EXIT_SUCCESS);
   }

   /*
    * Now we will enable signal processing events so the program can
    * receive them into the event queue.  We will use the queuing method
    * instead of setting up a handler.  See the other interrupt example to
    * see how things would differ if a handler was set up.  The default
    * queue size is 50.  This can be changed with the viSetAttribute
    * function but it must be done before calling viEnableEvent().
    */
   printf("Waiting for an event...\n");
   status = viEnableEvent (instr, VI_EVENT_VXI_SIGP, VI_QUEUE, VI_NULL);
   if (status < VI_SUCCESS)
   {
      printf("Error enabling events.\n");
      viClose (instr);
      viClose (defaultRM);
      exit (EXIT_SUCCESS);
   }

   /*
    * Next we must use the viWaitOnEvent function to check the queue
    * for a signal processing event.  This function can be given a timeout
    * after which it will return if no event has been received. The 
    * timeout can be set to VI_TMO_IMMEDIATE to just pull the oldest event
    * off the queue.  To test this example an interrupt can be asserted
    * using VIC, the VXI Interactive Control program.
    * Call AssertVXIint with these arguments:  AssertVXIint( 0, 1, 0xFD00 )
    * to use the default controller to assert an interrupt on level 1 with a
    * StatusID of 0xFD00.  Note that most VXI interrupters will place its 
    * logical address in the lower byte of the StatusID.
    */
   printf("Waiting for an interrupt.  Use VIC to assert an interrupt with\n ");
   printf("these parameters: AssertVXIint( 0, 1, 0xFD00 )\n");

   WaitTimeout = 8000;  /* Wait 8 seconds for an event */
   status = viWaitOnEvent (instr, VI_EVENT_VXI_SIGP, WaitTimeout, &etype, &event);
   if (status < VI_SUCCESS)
   {
      printf ("No event was received in the designated period.\n");
   }
   else
   {
      /*
       * Now we will use the event handle returned by viWaitOnEvent to
       * check the Status ID attribute.  Only interrupts from LA 0
       * will be seen because it was set up in a session to LA 0.
       */
      status = viGetAttribute (event, VI_ATTR_SIGP_STATUS_ID, &intrID);
      printf ("The Status/ID was 0x%hX\n", intrID);

       /*
        * Now we will close the session for the event using viClose.
        */
       status = viClose (event);
    }

    /*
     * Now we will close the session to the instrument.
     */

   status = viClose (instr);
   status = viClose (defaultRM);
   printf ("\nHit Enter to continue.");
   fflush (stdin);
   getchar();

   return 0;
}


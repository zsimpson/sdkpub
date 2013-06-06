/**********************************************************************/
/*            Synchronous Trigger Events Example                      */
/*                                                                    */
/*  This code opens a session to a device at Logical Address two.     */
/*  The programs sets up an event queue to receive triggers on TTL    */
/*  Trigger line three.  The program can be tested easily by          */     
/*  running the program and then asserting a trigger in VIC, the VXI  */
/*  Interactive Control program.  The program is written using VISA.  */
/*                                                                    */
/* The general flow of this code is:                                  */
/* Open Resource Manager                                              */
/*  Open VISA session to an instrument                                */
/*  Enable a particular trigger line using the Trigger Attribute      */
/*  Enable Trigger Events To Be Queued                                */
/*  Wait For A Trigger Event                                          */
/*  [Source TTL Trigger line 3 using VIC - SrcTrig( -1, 3, 4, 1000 );]*/
/*  Check The ID Of Received Trigger Event To See If It Was Line 3    */
/*  Close The Event                                                   */
/*  Close the VISA session                                            */
/**********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "visa.h"

static ViSession defaultRM;
static ViSession instr;
static ViUInt32 WaitTimeout;
static ViInt16 trig_line;
static ViEvent event;
static ViEventType type;
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
    * address two. We must use the resource manager handle
    * from viOpenDefaultRM.  We must also use a string which will
    * indicate which instrument to open.  This is called the
    * instrument descriptor.  The format for this string can
    * be found in the NI-VISA User Manual. After opening a session to the
    * device, we will get a handle to the instrument which we
    * will use in later VISA functions.  The remaining two parameters
    * in this function are reserved for future functionality.
    * They are given the values VI_NULL.
    */
   status = viOpen (defaultRM, "VXI::2::INSTR", VI_NULL, VI_NULL, &instr);
   if (status < VI_SUCCESS)
   {
      printf ("Cannot open a session to the device.\n");
      viClose (defaultRM);
      exit (EXIT_SUCCESS);
   }
      
   /*
    * Now we will set the VI_ATTR_TRIG_ID.  This ID determines which trigger
    * lines will generate events in a particular session.  By default,
    * it is set to software triggers.  This attribute can only be changed 
    * before trigger events are enabled.  After they are enabled it is a
    * read-only attribute.  We will set the ID to look for TTL triggers
    * on line 3.
    */
   status = viSetAttribute (instr, VI_ATTR_TRIG_ID, VI_TRIG_TTL3);
   if (status < VI_SUCCESS)
   {
      printf ("Error setting the TTL trigger level to monitor\n");
      viClose (instr);
      viClose (defaultRM);
      exit (EXIT_SUCCESS);
   }
   
   /*
    * Now we will enable trigger events so this example can receive them
    * into its event queue.  It will only receive events for triggers on
    * TTL line 3.  We will use the queuing method instead of 
    * setting up a handler.  Refer to the interrupt handler example to see how
    * things would differ if a handler was set up.  The default queue size
    * is 50.  This can be changed with the viSetAttribute function but it
    * must be done before calling viEnableEvent().
    */
   status = viEnableEvent (instr, VI_EVENT_TRIG, VI_QUEUE, VI_NULL);
   if (status < VI_SUCCESS)
   {
      printf("Error enabling the trigger events\n");
      viClose (instr);
      viClose (defaultRM);
      exit (EXIT_SUCCESS);
   }

   /*
    * Next we will use the viWaitOnEvent function to check the queue
    * for a trigger event.  This function can be given a timeout after
    * which it will return if an event has not been received. The 
    * timeout can be set to VI_TMO_IMMEDIATE to just pull the oldest 
    * event off the queue.  To test this example, a trigger can be sourced
    * on TTL line three using VIC, the VXI Interactive Control program.
    * Call SrcTrig with these arguments: SrcTrig( -1, 3, 4, 1000 ) to 
    * generate a Sync trigger pulse on TTL line 3 with a 1000msec timeout.
    */
   printf ("Waiting for a trigger event...\n");

   WaitTimeout = 8000;  /* Wait 8 seconds for an event */
   status = viWaitOnEvent (instr, VI_EVENT_TRIG, WaitTimeout, &type, &event);
   if (status < VI_SUCCESS)
   {     /* error (possibly timeout?) */
      printf ("An error occurred waiting for the trigger.\n");
      printf ("No event was received.\n");
      viClose (defaultRM);
      printf("\nHit Enter to continue.");
      fflush(stdin);
      getchar();
      exit (EXIT_SUCCESS);
   }
   else  /* successfully received an event */
   {
      printf ("The trigger was successfully received.\n");
      /* Always call viClose on the event whenever viWaitOnEvent is successful. */
      status = viClose (event);
   }

    /*
     * Now we will close the event context, the session to the instrument, and the
     * resource manager session, all using viClose.
     */
   status = viClose (instr);
   status = viClose (defaultRM);

   printf("\nHit Enter to continue.");
   fflush(stdin);
   getchar();

   return 0;
}


/**************************************************************************/
/*             Synchronous SRQ Event Handling Example                     */
/*                                                                        */
/*  This example shows how to enable VISA to detect SRQ events.           */
/*  The program writes a command to a device and then waits to receive    */
/*  an SRQ event before trying to read the response.                      */
/*                                                                        */
/*  Open A Session To The VISA Resource Manager                           */
/*  Open A Session To A GPIB Device                                       */
/*  Enable SRQ Events                                                     */
/*  Write A Command To The Instrument                                     */
/*  Wait to receive an SRQ event                                          */
/*  Read the Data                                                         */
/*  Print Out The Data                                                    */
/*  Close The Instrument Session                                          */
/*  Close The Resource Manager Session                                    */
/**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "visa.h"

static ViSession inst;
static ViSession defaultRM;
static ViUInt32 WaitTimeout = 30000; /* Timeout in milliseconds */
static ViEvent ehandle;
static ViEventType etype;
static ViStatus status;
static ViUInt32 rcount;
static ViUInt16 statusByte;
static unsigned char data[3000];
static char stringinput[512], nextstringinput[512];

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
      printf("Could not open a session to the device simulator");
      goto Close;
   }
   

   /*  Now we must enable the service request event so that VISA
    *  will receive the events.  Note: one of the parameters is 
    *  VI_QUEUE indicating that we want the events to be handled by
    *  a synchronous event queue.  The alternate mechanism for handling
    *  events is to set up an asynchronous event handling function using
    *  the VI_HNDLR option.  The events go into a queue which by default
    *  can hold 50 events.  This maximum queue size can be changed with
    *  an attribute but it must be called before the events are enabled.
    */
   status = viEnableEvent (inst, VI_EVENT_SERVICE_REQ, VI_QUEUE, VI_NULL);
   if (status < VI_SUCCESS)
   {
      printf("The SRQ event could not be enabled");
      goto Close;
   }
   
   /* 
    *  Now the VISA write command is used to send a request to the
    *  instrument to generate a sine wave and assert the SRQ line
    *  when it is finished.  Notice that this is specific to one 
    *  particular instrument.
    */
   strcpy(stringinput,"SRE 0x10; SOUR:FUNC SIN\n");
   status = viWrite (inst, (ViBuf)stringinput, strlen(stringinput), &rcount);
   if (status < VI_SUCCESS)
   {
      printf("Error writing to the instrument\n");
      goto Close;
   }
   
   /*
    *  Now we wait for an SRQ event to be received by the event queue.
    *  The timeout is in milliseconds and is set to 30000 or 30 seconds.
    *  Notice that a handle to the event is returned by the viWaitOnEvent
    *  call.  This event handle can be used to obtain various
    *  attributes of the event.  Finally, the event handle should be closed
    *  to free system resources.
    */
   printf("\nWaiting for an SRQ Event\n\n");
   status = viWaitOnEvent (inst, VI_EVENT_SERVICE_REQ, WaitTimeout, &etype, &ehandle);

   /* 
    *  If an SRQ event was received we first read the status byte with
    *  the viReadSTB function.  This should always be called after
    *  receiving a GPIB SRQ event, or subsequent events will not be
    *  received properly.  Then the data is read and the event is closed
    *  and the data is displayed.  Otherwise sessions are closed and the
    *  program terminates.
    */
   if (status >= VI_SUCCESS)
   {
      status = viReadSTB (inst, &statusByte);
      if (status < VI_SUCCESS)
      {
         printf("There was an error reading the status byte");
         goto Close;
      }

      strcpy(nextstringinput,"SENS: DATA?\n");
      status = viWrite (inst, (ViBuf)nextstringinput, strlen(nextstringinput), &rcount);
      if (status < VI_SUCCESS)
      {
         printf("There was an error writing the command to get the data");
         goto Close;
      }     

      status = viRead (inst, data, 3000, &rcount);
      if (status < VI_SUCCESS)
      {
         printf("There was an error reading the data");
         goto Close;
      }

      status = viClose (ehandle);
      if (status < VI_SUCCESS)
      {
         printf("There was an error closing the event handle");
         goto Close;
      }

      printf("Here is the data: %*s\n", rcount, data);
   }
   
   /*  
    *  Now we must close the session to the instrument and the session
    *  to the resource manager.
    */
Close:
   status = viClose (inst);
   status = viClose (defaultRM);
   printf ("Hit enter to continue.");
   fflush (stdin);
   getchar();

   return 0;
}


/**************************************************************/
/*          High Level Register Access Example                */
/*                                                            */
/*  This example reads and writes the offset register of the  */
/*  device at logical address 0.  To do this, the code reads  */
/*  the register at 0xC006 in A16 space, then writes the value*/
/*  back to the same register.  Then it moves the first four  */
/*  configuration registers into local RAM and displays this  */
/*  on the STDIO window.  This code uses only VISA functions. */
/*                                                            */
/*   The general flow of this code is:                        */
/*    Open Resource Manager                                   */
/*    Open VISA session to the instrument at LA 0             */
/*    Read the offset register                                */
/*      Write the same value back to the offset register      */
/*      Move in the first 4 config registers                  */
/*      Close VISA session                                    */
/**************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "visa.h"

static ViSession defaultRM;
static ViSession instr;
static ViUInt16 value;
static ViBusAddress offset;
static ViUInt16 data[4];
static ViBusSize count;
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
   status = viOpen (defaultRM, "VXI0::0::INSTR", VI_NULL, VI_NULL, &instr);
   if (status < VI_SUCCESS)
   {  
      printf ("Cannot open a session to the device.\n");
      viClose (defaultRM);
      exit (EXIT_SUCCESS);
   }

   /*
    * Now we will read in the offset register and display it
    * on the screen.  We must use the session handle to the 
    * instrument from the viOpen function.  We will be reading
    * 16 bits by using the viIn16 function.
    */
   offset = 0x6; /* offset in A16 space from the base of the device's memory */

    /* 
     *  Note that the offset is relative to the base of the device's
     *  memory in that address space.  Offset is not the absolute address
     *  of the device.
     */
   status = viIn16 (instr, VI_A16_SPACE, offset, &value);
   if (status < VI_SUCCESS)         /* an error occurred */
   {
      printf ("Cannot communicate with device.\n");
   }
   else           /* read was successful */
   {
      printf ("The offset register of the device at LA 0 is 0x%x\n", value);
   }

   /*
    * Now we will write out the value just read with the 
    * viOut16 function. We will write this to the offset
    * register of the device at logical address zero
    * using the instrument handle returned from viOpen.
    */
   status = viOut16 (instr, VI_A16_SPACE, offset, value);
   if (status < VI_SUCCESS)       /* success */
   {
      printf("Cannot write data to registers.\n");
   }
   else           /* an error occurred */
   {
      printf ("0x%x was written correctly to the Offset Register.\n",value);
   }

  /*
   * Now we will move the first 4 configuration registers into local
   * memory.  This will be done using viMoveIn16.
   */
   offset = 0;       /* we want to get data from 0xC000-0xC007 */
   count  = 4;       /* move 4 16-bit pieces of data */

   status = viMoveIn16 (instr, VI_A16_SPACE, offset, count, data);
   if (status < VI_SUCCESS)    /* error occurred */
   {
      printf ("Could not move data.\n");
   }
   else    /* successful move */
   {
      printf ("\nThe first 4 configuration registers are:\n");
      printf ("Register 0 = 0x%04hX\n", data[0]);
      printf ("Register 1 = 0x%04hX\n", data[1]);
      printf ("Register 2 = 0x%04hX\n", data[2]);
      printf ("Register 3 = 0x%04hX\n", data[3]);
   }

  /*
   * Now we must close the session to the instrument using
   * viClose.  We must tell VISA what to close by use of the
   * instrument handle, "instr".  We will also close the VISA
   * Resource Manager.
   */

   status = viClose (instr);
   status = viClose (defaultRM);
   printf("\nHit Enter to continue.");
   fflush(stdin);
   getchar();

   return 0;
}


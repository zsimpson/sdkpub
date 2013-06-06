/**************************************************************/
/*             Low Level Register Access Example              */
/*                                                            */
/* This example uses low level register functions to read the */
/* offset register of a VXI device at logical address 0.  The */
/* program uses the viMapAddress function to map a window     */
/* to the A16 VXI address space and then uses viPeek to read  */
/* the value of this register.                                */
/*                                                            */
/* The general flow of this code is:                          */
/* Open Resource Manager                                      */
/* Open VISA session to an instrument                         */
/* Map the desired VXI memory to the local processor's memory */
/* Use viPeek to read the offset register                     */
/* Unmap the memory                                           */
/* Close the VISA session                                     */
/**************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "visa.h"

#define ADD_OFFSET(addr, offs)   (((ViPByte)addr) + (offs))

static ViSession defaultRM;
static ViSession instr;
static ViUInt16 value, access;
static ViBusAddress offset;
static ViAddr mapped_address, address;
static ViBusSize size;
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

   /* Now we will map a window to the A16 space containing the
    * configuration registers of the device using the viMapAddress
    * function.  This function will use the session to the
    * device we obtained using viOpen.
    */
   offset = 0x0;    /* read Offset register in A16 */
   size = 0x40;     /* we will map to all configuration registers */
   status = viMapAddress (instr, VI_A16_SPACE, offset, size, VI_FALSE, VI_NULL,&mapped_address);
   if (status < VI_SUCCESS)
   {
      printf ("Error mapping the address to local memory\n");
      printf ("Make sure you have a User Window configured in VXIedit\n");
      viClose (defaultRM);
      exit (EXIT_SUCCESS);
   }

   /*
    * Now we will use the viPeek16 function to read the value
    * of the Offset register for the device at LA 0 which we have
    * mapped to the A16 space.  We will do this using the pointer
    * returned from the viMapAddress function.  The viPeek function
    * basically just dereferences a pointer to the VXI address space.
    * The Offset register is at offset 0x6, so we need to increment
    * the mapped address.
    */

   /*
    * Now that we have mapped the window, we can use the pointer
    * to read and write to registers.  We could do this by directly
    * dereferencing the pointer, or by using viPeekXX/viPokeXX.  On
    * some O/S's you will not be able to directly dereference the pointer,
    * so your code is more portable if you use viPeekXX/viPokeXX.  To
    * find out if you can directly dereference the pointer, you can get
    * a VISA Attribute.  In the following code, we check to see if we
    * can dereference the pointer.  If that is permitted we will read
    * the Offset register by a direct dereference, otherwise we call
    * viPeek16.  After this we call viPeek again.
    */

   /* Now we will use a macro to manipulate the pointer.  This */
   /* macro will add the correct value to the pointer to make */
   /* it point to the Offset register. */
   address = ADD_OFFSET (mapped_address, 6);

   viGetAttribute (instr, VI_ATTR_WIN_ACCESS, &access);
   if (access == VI_DEREF_ADDR)  /* can dereference the pointer directly */
   {
      printf ("Direct Pointer Dereference was used to read the Offset Register.\n");
      value = *(ViPUInt16)address;
   }
   else       /* must use viPeek16 */
   {
      printf ("viPeek16 was used to read the Offset Register.\n");
      viPeek16 (instr, address, &value);
   }

   printf("The value read from the Offset register is 0x%hX\n", value);

   /* Now do viPeek16 again in case you could dereference the pointer in the first access. */
   viPeek16 (instr, address, &value);
   printf ("The value read from the Offset Register using viPeek16 was 0x%hx", value);

   /*
    * Now we need to unmap the User Window for completeness of
    * code.
    */
   status = viUnmapAddress (instr);

   /*
    * Finally, we need to close all the VISA sessions that we
    * opened
    */
   viClose (instr);
   viClose (defaultRM);
   printf("\nHit Enter to continue.");
   fflush(stdin);
   getchar();

   return 0;
}


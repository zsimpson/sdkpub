/**************************************************************/
/*          How to Share System Memory Example                */
/*                                                            */
/* This example demonstrates how to share memory from         */
/* a National Instruments controller to the VXI backplane.    */
/*                                                            */
/* Before proceeding, familiarize yourself with application   */
/* note 018, Use of Local Shared RAM on NI-VXI Interfaces,    */
/* from National Instrument's web or ftp site or              */
/* faxback system.                                            */
/*                                                            */
/* You will need to make some configuration changes in        */
/* VXIEdit or VXItedit or T&M Explorer.  Note that these      */
/* descriptions apply to MITE based controllers.              */
/* Please refer to the documentation that came with your      */
/* controller to determine how to configure shared memory     */
/* from system memory.                                        */
/*                                                            */
/* The following steps must be carried out before memory can  */
/* be shared.  If using VXIEdit or VXItedit, start below.     */
/* Is using the T&M Explorer, skip down to that section       */
/*                                                            */
/* VXIEdit/VXItedit  settings:                                */
/* 1. In the logical address configuration page for the       */
/*    controller set the Address Space parameter to A16/A24   */
/*   or A16/A32 (preferred) depending on which space you want */
/*   to use to share memory.  The A16/A32 allows you to share */
/*   all system RAM.                                          */
/*                                                            */
/* 2. Set the VXI Shared RAM Size.  parameter to program the  */
/*   VXI interface registers to map cycles from the           */
/*   VXI/VMEbus to the computer memory.  It is recommended    */
/*   that you set this to All System RAM.  A16/A24 does not   */
/*   usually allow you to select All System RAM               */
/*                                                            */
/* 3. Set the Shared RAM Pool to the amount of RAM that you   */
/*    actually need plus 1kB. The Shared RAM Pool indicates   */
/*    the amount of physically contiguous memory that is      */
/*    allocated on system startup.  This reserved memory can  */
/*    be shared to the VXI/VMEbus by the VISA MemAlloc call.  */
/*    Remember that the OS will be denied access to this      */
/*    memory, so take into account the memory requirements of */
/*    your OS and your applications with regard to the amount */
/*    of RAM in your system before setting this option.       */
/*    If VISA MemAlloc fails, it may be because your system   */
/*    could not provide for sufficient reserved memory for    */
/*    the Shared RAM Pool.                                    */
/*    If this happens, simply make the Shared RAM Pool        */
/*    smaller until VISA MemAlloc returns successfully.       */
/*                                                            */
/* T&M Explorer settings:                                     */
/* 1. Select the VXI controller, i.e. PCI-MXI-2.  Right click */
/*    on the selection and choose Hardware Configuration.     */
/*    Select the Shared Memory tab.  Note that you can get    */
/*   help on each step by right clicking on each setting.     */
/*                                                            */
/* 2. Select Share RAM in A24 Space or Select Share RAM in    */
/*    A32 Space (preferred).                                  */
/*                                                            */
/* 3. Next set the VXI Shared RAM Size parameter to program   */
/*      the VXI interface registers to map cycles from the    */
/*   VXI/VMEbus to the computer memory.                       */
/*    It is recommended to set this to All System RAM         */
/*      (usually not available if you have Share RAM in A24   */
/*   selected above).                                         */
/*                                                            */
/* 4. Set the Reserve Physical Memory to the amount of RAM    */
/*   that you actually need plus 1kB. The Reserve Physical    */
/*   Memory indicates the amount of physically contiguous     */
/*   memory that is allocated on system startup.  This        */
/*   reserved memory can be shared to the VXI/VMEbus by       */
/*   the VISA MemAlloc call.                                  */
/*   Remember that the OS will be denied access to this       */
/*   memory, so take into account the memory requirements of  */
/*   your OS and your applications with regard to the amount  */
/*   of RAM in your system before setting this option.        */
/*   If VISA MemAlloc fails, it may be because your system    */
/*   could not provide for sufficient reserved memory for the */
/*   Reserve Physical Memory.                                 */
/*   If this happens, simply make the Reserve Physical Memory */
/*   smaller until VISA MemAlloc returns successfully.        */
/*                                                            */
/*  Now, you are ready to run this example.  Keep in mind,    */
/*  that if VISA MemAlloc fails, request less memory in the   */
/*  Shared RAM Pool or Reserve Physical Memory settings.      */
/*  Obviously, the Size parameter passed into VISA MemAlloc   */
/*  must be made correspondingly smaller.                     */
/*                                                            */
/* The general flow of this code is:                          */
/* Open Resource Manager                                      */
/*  Open a session to LA 0                                    */
/*  Allocate the shared memory                                */
/*  Use viGetAttribute to determine the offset of the shared  */
/*    memory.                                                 */
/* Use viOut16 to write a value into shared memory            */
/*  Use viIn16 to read the value to see if the data was       */
/*       written correctly.                                   */
/*  Use viMemFree to free the shared memory buffer.           */
/*  Close VISA sessions                                       */
/**************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "visa.h"

static ViSession instr, defaultRM;
static ViAddr local_address;
static ViBusAddress offset;
static ViBusSize size;
static ViUInt16 addrspace, value;
static int base;
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

   /* Now we will allocate the first 100 bytes of shared
    * memory by the device at LA 0 using the viMemAlloc function.
    * This function is only valid on sessions to the local controller.
    * This function will return a pointer to local memory and
    * we will store this in the variable "offset."
    */

   /* This is how much memory we are going to set aside
    * in our local RAM.  Even though we have possibly many
    * megs requested in VXI space, we are only going to
    * use 0x100 bytes. This value is arbitrary for this example.
    */
   size = 0x100;
   status = viMemAlloc (instr, size, &offset);
   if (status < VI_SUCCESS)     /* an error occurred */
   {
      printf("Failed to successfully allocate system RAM.\n");
      viClose (defaultRM);
      printf("\nPress any key to exit...");
      fflush(stdin);
      getchar();
      exit (EXIT_SUCCESS);
   }

   /* We will determine in which address space the shared memory is located. */
   viGetAttribute (instr, VI_ATTR_MEM_SPACE, &addrspace);

   /* We will also find the base address of our controller so another */
   /* bus master can access our shared memory. */
   viGetAttribute (instr, VI_ATTR_MEM_BASE, &base);

   /*
    * Now we will try to do a cycle of high level In's and Out's
    * to show how the shared memory can be accessed.
    */

   /* Now let's write a value into this memory. */
   status = viOut16 (instr, addrspace, offset, 0xBEEF);
   if (status < VI_SUCCESS)
      printf ("Could not write into the shared memory.\n");


   /* At this point, you can use another bus master to access 
    * the shared memory at the Base + Offset. 
     * You may notice that you will not be able to self-access 
     * this memory from another application such as VIC or VISAIC.  
     * The hardware is not capable of allowing self-accesses.  
     * But the viIn16 and viOut16 in this example works because 
     * VISA keeps track of the actual memory buffer that is allocated 
     * and allows direct access to the memory. 
     * This allows viIn16 and viOut16 to work without accessing the VXI/VME bus. 
     */
   printf("The shared memory is located at absolute address 0x%08lX",base + offset);
   switch (addrspace)
   {
       case VI_A16_SPACE:
          printf(" in A16 address space.\n\n");     
          break;
       case VI_A24_SPACE:
          printf(" in A24 address space.\n\n");     
          break;
       case VI_A32_SPACE:
          printf(" in A32 address space.\n\n");     
          break;
       default:
          break;
    }

    /* Now let's read back from this location and see if it is */
    /* the correct value. */
   status = viIn16 (instr, addrspace, offset, &value);
   if (status < VI_SUCCESS)
      printf ("Could not read from shared memory.\n");
   else if (value == 0xBEEF)
      printf ("Value written = value read; sharing is successful!\n");
   else
      printf ("We wrote 0xBEEF, but read back 0x%04hX\n", value);

   /*
    * At this point we have to clean up after ourselves by freeing
    * the shared memory.
    * This will be done using the viMemFree function.
    */
   status = viMemFree (instr, offset);   /* free the allocated memory */
   if (status < VI_SUCCESS)
      printf("An error occurred in freeing the local memory.\n");

    /*
     * Now we will close the session to the instrument using
     * viClose.  We will tell VISA what to close using the
     * instrument handle "instr"
     */

   status = viClose (instr);
   status = viClose (defaultRM);
   printf("\nHit Enter to continue.");
   fflush(stdin);
   getchar();

   return 0;
}


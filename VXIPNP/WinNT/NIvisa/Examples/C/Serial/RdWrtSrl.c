/********************************************************************/
/*                Read and Write to a Serial Instrument             */
/*                                                                  */
/* This code demonstrates sending synchronous read & write commands */
/* through the serial port using VISA.                              */
/* The example writes the "*IDN?\n" string to the serial port (COM1)*/
/* and attempts to read back a result using the write and read      */
/* functions.                                                       */
/*                                                                  */
/* The general flow of the code is                                  */
/*    Open Resource Manager                                         */
/*    Open VISA Session to an Instrument                            */
/*    Configure the Serial Port                                     */
/*    Write the Identification Query Using viWrite                  */
/*    Try to Read a Response With viRead                            */
/*    Close the VISA Session                                        */
/********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "visa.h"

static ViSession defaultRM;     
static ViSession instr;     
static ViUInt32 retCount;
static ViUInt32 writeCount;
static ViStatus status;
static unsigned char buffer[100];
static char stringinput[512];


int main(void)
{
   /*
    * First we must call viOpenDefaultRM to get the manager
    * handle.  We will store this handle in defaultRM.
    */
   status=viOpenDefaultRM (&defaultRM);
   if (status < VI_SUCCESS)  
   {
      printf ("Could not open a session to the VISA Resource Manager!\n");
      exit (EXIT_FAILURE);
   }
                                                          
   /*
    * Now we will open a VISA session to the serial port (COM1).
    * We must use the handle from viOpenDefaultRM and we must   
    * also use a string that indicates which instrument to open.  This
    * is called the instrument descriptor.  The format for this string
    * can be found in the function panel by right clicking on the 
    * descriptor parameter. After opening a session to the
    * device, we will get a handle to the instrument which we 
    * will use in later VISA functions.  The AccessMode and Timeout
    * parameters in this function are reserved for future
    * functionality.  These two parameters are given the value VI_NULL.
    */
   status = viOpen (defaultRM, "ASRL1::INSTR", VI_NULL, VI_NULL, &instr);
   if (status < VI_SUCCESS) 
   {
      printf ("Cannot open a session to the device.\n");
      goto Close;
   }
  
   /* 
    * At this point we now have a session open to the serial instrument. 
    * Now we need to configure the serial port:
    */                                      
      
   /* Set the timeout to 5 seconds (5000 milliseconds). */
   status = viSetAttribute (instr, VI_ATTR_TMO_VALUE, 5000);
  
   /* Set the baud rate to 4800 (default is 9600). */
   status = viSetAttribute (instr, VI_ATTR_ASRL_BAUD, 4800);
  
   /* Set the number of data bits contained in each frame (from 5 to 8). 
    * The data bits for  each frame are located in the low-order bits of
    * every byte stored in memory.    
    */
   status = viSetAttribute (instr, VI_ATTR_ASRL_DATA_BITS, 8);
  
   /* Specify parity. Options: 
    * VI_ASRL_PAR_NONE  - No parity bit exists, 
    * VI_ASRL_PAR_ODD   - Odd parity should be used, 
    * VI_ASRL_PAR_EVEN  - Even parity should be used,
    * VI_ASRL_PAR_MARK  - Parity bit exists and is always 1,
    * VI_ASRL_PAR_SPACE - Parity bit exists and is always 0.
    */
   status = viSetAttribute (instr, VI_ATTR_ASRL_PARITY, VI_ASRL_PAR_NONE);
  
   /* Specify stop bit. Options:
    * VI_ASRL_STOP_ONE   - 1 stop bit is used per frame,
    * VI_ASRL_STOP_ONE_5 - 1.5 stop bits are used per frame,
    * VI_ASRL_STOP_TWO   - 2 stop bits are used per frame.
    */
   status = viSetAttribute (instr, VI_ATTR_ASRL_STOP_BITS, VI_ASRL_STOP_ONE);
  
    /* Specify that the read operation should terminate when a termination 
     * character is received.
     */
   status = viSetAttribute (instr, VI_ATTR_TERMCHAR_EN, VI_TRUE); 
 
    /* Set the termination character to 0xA                            
     */
   status = viSetAttribute (instr, VI_ATTR_TERMCHAR, 0xA);
  
 
    /* We will use the viWrite function to send the device the string "*IDN?\n",
     * asking for the device's identification.  
    */
   strcpy (stringinput,"*IDN?\n");
   status = viWrite (instr, (ViBuf)stringinput, strlen(stringinput), &writeCount);
   if (status < VI_SUCCESS)    
   {
      printf ("Error writing to the device.\n");
      goto Close;
   }
    
    /*
    * Now we will attempt to read back a response from the device to
    * the identification query that was sent.  We will use the viRead
    * function to acquire the data.  We will try to read back 100 bytes.
    * This function will stop reading if it finds the termination character
    * before it reads 100 bytes.
    * After the data has been read the response is displayed.
    */
   status = viRead (instr, buffer, 100, &retCount);
   if (status < VI_SUCCESS) 
   {
      printf ("Error reading a response from the device.\n");
   }
   else
   {
      printf ("\nData read: %*s\n", retCount, buffer);
   }


   /*
    * Now we will close the session to the instrument using
    * viClose. This operation frees all system resources.                     
    */
Close:
   status = viClose (instr);
   status = viClose (defaultRM);
   printf ("Hit enter to continue.");
   fflush (stdin);
   getchar();

   return 0;
}


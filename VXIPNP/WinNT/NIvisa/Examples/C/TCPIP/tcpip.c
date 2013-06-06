/*********************************************************************/
/* This example demonstrates opening a simple TCPIP connection and   */
/* does a read and checks a few properties.							 */
/*                                                                   */
/* The general flow of the code is                                   */
/*      Open Resource Manager                                        */
/*      Open a session to the TCP/IP site at NI                      */
/*      Perform a read, and check properties                         */
/*      Close all VISA Sessions                                      */
/*********************************************************************/


#include <stdio.h>
#include <stdlib.h>

#include "visa.h"

static char outputBuffer[VI_FIND_BUFLEN];
static ViSession defaultRM, instr;
static ViStatus status;
static ViUInt32 count;
static ViUInt16 portNo;

int main(void)
{
   /* First we will need to open the default resource manager. */
   status = viOpenDefaultRM (&defaultRM);
   if (status < VI_SUCCESS)
   {
      printf("Could not open a session to the VISA Resource Manager!\n");
      exit (EXIT_FAILURE);
   }  

   /* Now we will open a session via TCP/IP to ni.com */
   status = viOpen (defaultRM, "TCPIP0::ftp.ni.com::21::SOCKET", VI_NULL, VI_NULL, &instr);
   if (status < VI_SUCCESS)
   {
      printf ("An error occurred opening the session to TCPIP0::ftp.ni.com::21::SOCKET\n");
      viClose(defaultRM);
      exit (EXIT_FAILURE);
   }
   
   viSetAttribute (instr, VI_ATTR_TCPIP_NODELAY, VI_TRUE);
   
   status = viRead (instr, (ViBuf)outputBuffer, 25, &count);
   if (status < VI_SUCCESS)
   {
      printf("viRead failed with error code %x \n",status);
      viClose(defaultRM);
      exit (EXIT_FAILURE);
   }

   printf("The server response is:\n %s\n\n",outputBuffer);
   status = viGetAttribute (instr, VI_ATTR_TCPIP_ADDR, outputBuffer);
   printf(" Address:  %s\n",outputBuffer);
   
   status = viGetAttribute (instr, VI_ATTR_TCPIP_HOSTNAME, outputBuffer);
   printf(" Host Name:  %s\n",outputBuffer);
   
   status = viGetAttribute (instr, VI_ATTR_TCPIP_PORT, &portNo);
   printf(" Port:  %d\n",portNo);
   
   status = viGetAttribute (instr, VI_ATTR_RSRC_CLASS, outputBuffer);
   printf(" Resource Class:  %s\n",outputBuffer);

   status = viClose (instr);
   status = viClose (defaultRM);
   printf ("\nHit enter to continue.");
   fflush(stdin);
   getchar();

   return 0;  
}

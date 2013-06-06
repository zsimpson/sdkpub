/********************************************************************/
/* This example demonstrates VISA locking                           */
/*                                                                  */
/* In VISA, applications can open multiple sessions to the same     */
/* resource simultaneously and access that resource through these   */
/* different sessions concurrently.                                 */
/* In some cases, an application may need to restrict other         */
/* sessions from accessing that resource.                           */
/* For example, an application may need to execute a write and a    */
/* read operation as an atomic operation so that no other           */
/* operations intervene between the write and read operations.      */
/* If another application or even this same application were to     */
/* perform another write between this first write and read, then it */
/* could put the instrument in an unstable state.                   */
/* This is where locking becomes convenient.  The application can   */
/* lock the resource before invoking the write operation and unlock */
/* it after the read operation, to execute them as a single step.   */
/* This prevents other applications from accessing the resource     */
/* and prevents possible contention.  VISA defines locking          */
/* to restrict accesses to resources for such special circumstances.*/
/*                                                                  */
/* The VISA locking mechanism enforces arbitration of accesses to   */
/* resources on an individual basis. If a session locks a resource, */
/* operations invoked by other sessions are returned with an error. */
/*                                                                  */
/* This VI opens two sessions to an instrument and locks the first  */
/* session.  The first session then writes the String to Write to   */
/* the instrument and reads a response of the desired length.       */
/*                                                                  */
/* The second session tries to do the same task but will not        */
/* succeed unless the first session is unlocked.                    */
/*                                                                  */
/* The general flow of the code is                                  */
/*      Open Resource Manager                                       */
/*      Open 2 VISA sessions to an instrument                       */
/*      Lock the first session                                      */
/*      Read and write to that instrument using the first session   */
/*      Unlock the first session                                    */
/*      Now read and write to the instrument with the second session*/
/*      Close the VISA Sessions                                     */
/********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "visa.h"

static ViSession defaultRM;  
static ViSession instr1, instr2;     
static ViUInt32 retCount;
static ViUInt32 writeCount;
static ViStatus status; 
static unsigned char buffer[100];
static int cchar;
static char stringinput[512];


int main (void)
{
    /*
     * First we must call viOpenDefaultRM to get the resource manager
     * handle.  We will store this handle in defaultRM.
     */
   status=viOpenDefaultRM (&defaultRM);
   if (status < VI_SUCCESS)
   {
      printf("Could not open a session to the VISA Resource Manager!\n");
      exit (EXIT_FAILURE);
   }

    /*
     * Now we will open a session to a GPIB instrument at address 2.
     * We must use the handle from viOpenDefaultRM and we must   
     * also use a string that indicates which instrument to open.  This
     * is called the instrument descriptor.  The format for this string
     * can be found in the function panel by right clicking on the 
     * description parameter. After opening a session to the
     * device, we will get a handle to the instrument which we 
     * will use in later Visa functions.  The two parameters in this 
     * function which are reserved for future functionality.  
     * These two parameters are given the value VI_NULL.
     */
    status = viOpen (defaultRM, "GPIB0::2::INSTR", VI_NULL, VI_NULL, &instr1);
    if (status < VI_SUCCESS)  
    {
        printf ("Cannot open a session to the device.\n");
        goto Close;
    }

    /*
     * Now we will open another session to a GPIB instrument at address 2.
     */
    status = viOpen (defaultRM, "GPIB0::2::INSTR", VI_NULL, VI_NULL, &instr2);
    if (status < VI_SUCCESS)  
    {
        printf ("Cannot open a second session to the device.\n");
        goto Close;
    }
   
    /*
     * Now we will lock the first session to the resource using the
     * viLock function.  Notice that the locking command takes a parameter
     * which can be set to VI_EXCLUSIVE_LOCK or VI_SHARED_LOCK.  The exclusive
     * lock will only let that session access the device until the
     * lock is released.  The shared locking option uses the last two parameters
     * which are set to VI_NULL for the exclusive lock.  The first of these
     * is a requested access key for the shared lock.  The last parameter is
     * a return value with the actual key assigned to the lock.  If the shared
     * lock is used the return actual key value can be used by another session
     * for the actual key parameter to gain access to the locked resource.
     * Please refer to the NI-VISA User Manual for more information.
     */
    status = viLock (instr1, VI_EXCLUSIVE_LOCK, VI_TMO_IMMEDIATE, VI_NULL, VI_NULL);
    if (status < VI_SUCCESS)   
    {
        printf("Error locking the session");
        goto Close;
    }  
  
   
    /*
     * Now we will write the string "*IDN?\n" to the device and read back the
     * Response from the session that obtained a lock on the resource
     */
    strcpy(stringinput,"*IDN?\n");
    status = viWrite (instr1, (ViBuf)stringinput, strlen(stringinput), &writeCount);
    if (status < VI_SUCCESS)  
    {
        printf("Error writing to the device\n");
        goto Close;
    }
     
    /*
     * Now we will attempt to read back a response from the device to
     * the identification query that was sent.  We will use the viRead
     * function to acquire the data.  We will try to read back 100 bytes.
     * After the data has been read the response is displayed.
     */
    status = viRead (instr1, buffer, 100, &retCount);
    if (status < VI_SUCCESS) 
    {
        printf("Error reading a response from the device\n");
        goto Close;
    }
    else
    {
          printf("\nData read: %*s\n",retCount,buffer);
    }

    /*
     * Now we will ask the user if they want to unlock the resource.
     * Then we will try the same operations with the second session.  If the
     * resource is not unlocked these operations will fail as would any attempts
     * to modify global attributes by the second session.
     */
    printf("Do you wish to unlock the resource so the second session can also access it(y/n)?\n");
    cchar = getchar ();
    if (cchar == 'y' || cchar == 'Y')
    {
        status = viUnlock (instr1);
        if (status < VI_SUCCESS)
        {
            printf("Error unlocking the resource\n");
            goto Close;
        }
    } 

    /* 
     * Now we will attempt the same read and write sequence we attempted with the first
     * session.  If the lock was not removed this will fail
     */
    status = viWrite (instr2, (ViBuf)stringinput, strlen(stringinput), &writeCount);
    if (status == VI_ERROR_RSRC_LOCKED)
    {
        printf("The resource is locked you can't write to it!\n");
    }
     
    /*
     * Now we will attempt to read back a response from the device to
     * the identification query that was sent.  We will use the viRead
     * function to acquire the data.  We will try to read back 100 bytes.
     * After the data has been read the response is displayed.
     */
    status = viRead (instr2, buffer, 100, &retCount);
    if (status == VI_ERROR_RSRC_LOCKED)
    {
        printf("The resource is still locked you can't read from it!\n");
    }
    else
    {
        printf("\nData read: %*s\n",retCount,buffer);
    }

Close:
    status = viClose(instr1);
    status = viClose(instr2);
    status = viClose(defaultRM);
    printf("Finished closing sessions.\nHit enter to continue.\n");
    fflush(stdin);
    getchar();

    return 0;
}

// drun.cpp : implementation file
//

#include "stdafx.h"
#include "mltaccum.h"
#include "drun.h"
#include <stdio.h>
#include "initexp.h"
extern "C"
{
#define PIXCM 1
#include "platform.h"
#include "pigendef.h"
#include "pigenfcn.h"
#include "pimltfcn.h"
#include "piimgfcn.h"
PREHEAD int PISTDAPI PICM_UnlockCurrentFrame( void );
PREHEAD int PISTDAPI PICM_LockCurrentFrame(void **directaddress, unsigned long *size, unsigned int *status);
}
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "cheader.h"

void Test_WriteTestFile
(
 HANDLE fileptr,				   /* pointer to file		 */
 void huge *big_buffer,            /* buffer holding data.   */
 int byte_size_of_pixel            /* size of a pixel in bytes */
 );

HANDLE Open_WriteTestFile
(
 char     *runfile,                /* data file to write to. */
 void huge *big_buffer,            /* buffer holding data.   */
 int byte_size_of_pixel,            /* size of a pixel in bytes */
 long framesnumber
  );


/////////////////////////////////////////////////////////////////////////////
// Cdrun dialog


Cdrun::Cdrun(CWnd* pParent /*=NULL*/)
	: CDialog(Cdrun::IDD, pParent)
{
	//{{AFX_DATA_INIT(Cdrun)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Cdrun::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cdrun)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cdrun, CDialog)
	//{{AFX_MSG_MAP(Cdrun)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cdrun message handlers

void Cdrun::OnOK() 
{
	long buffer_size;
    static HANDLE hglb;
	static void *lpvBuffer;
	 
	int done_flag;
	unsigned int status;
	unsigned int error_code;
	int index = 0;						/*  index for while loops		*/
	BOOL error_flag = FALSE;	
	char outstring[64];					/*  use for the message box		*/
	HANDLE fileptr;


	/* for defaults */

	double expos;
	int controltype;
	int ccdtype;
	int interfacetype;
	int ioaddtype;
	int interupttype;
	int adctype;
	int readouttype;
    int versiontype;


	ReadDefaults( &expos, &numframes, &controltype,
				&ccdtype, &interfacetype, &ioaddtype, &interupttype,
				&adctype, &readouttype, &versiontype );

	/* Create a buffer and pointer to the buffer *
	*	to send to initialize the system		*/
	buffer_size = PICM_SizeNeedToAllocate();
    hglb = GlobalAlloc(GPTR, buffer_size );
    lpvBuffer = (void huge*) GlobalLock(hglb);
                            
    PICM_Set_AutoStop(1);

    PICM_SetROI(    1, 1,
                    512,
                    512,
                    1, 1,
                    &error_code); 

	  PICM_Initialize_System(
									lpvBuffer,
                                    &error_code);

	/*  Initializing done_flag to no data has been collected */
	done_flag = FALSE;

	/*  Open the file to store data in */
	fileptr = Open_WriteTestFile( "test.spe", lpvBuffer, 2, (long)numframes );


	/* while loop that runs until numframe images have been
		taken and while there is no error.  */
	while ((index<numframes) && (!error_flag))
	{
		PICM_Start_controller();

		/*	Wait for data to be collected. */
		while (!done_flag) 
			done_flag = PICM_ChkData(&status);

		done_flag = FALSE;

		if ((status & CONERROR) || (status & COMERROR) ||
			(status & INITERROR) || (status & DATAOVERRUN) ||
			(status & VIOLATION) || (status & MAILERROR) ||
			(status & XFERERRORCH0) || (status & XFERERRORCH1))
			PICM_Stop_controller();
		
		if (status & NEWDATARDY)
		{
			/*  Write Test File  */
			Test_WriteTestFile( fileptr, lpvBuffer, 2 );
			PICM_UnlockCurrentFrame( );
        }                
		else /* error in data collection */
		{
			sprintf (outstring, "%d frames have been collected", index);
			MessageBox (
					outstring,
                    "Collect Button",
                    MB_OK | MB_ICONEXCLAMATION );
			error_flag = TRUE;
		}
		/* implement index */
		index++;

	}

	PICM_Stop_controller();

	MessageBox (
				"Experiment Done!",
                "Done Button",
                MB_OK | MB_ICONEXCLAMATION );
	/*  close Output File		*/
    CloseHandle( fileptr );
	
}

/*****************************************************************
*
*		Open_WriteTestFile
*
*		Description:	Opens a file to write to.  Also writes
*						the header for that file.
*
*****************************************************************/
HANDLE Open_WriteTestFile
(
 char		*runfile,               /* data file to write to. */
 void huge	*big_buffer,            /* buffer holding data.   */
 int byte_size_of_pixel,            /* size of a pixel in bytes */
 long framesnumber
 )

{
	DWORD BytesToWrite = 4100;
	LPDWORD BytesWritten;
	DWORD temp;

    HANDLE fileptr = NULL;				   /* pointer to file		 */
    CSMAHead * header;

	BytesWritten = &temp;
    fileptr = CreateFile( runfile,
						  GENERIC_WRITE,
						  FILE_SHARE_WRITE,
						  0,
						  CREATE_ALWAYS,
						  FILE_ATTRIBUTE_NORMAL,
						  0);

    header = new CSMAHead;
    memset( header, 0, 4100 );
    /*  fill in some of the header  */
    header->noscan = -1;
    
	header->datatype = 3;  //unsigned integer
    
	header->ydim		= PICM_Get_pixeldimension_y();
    /* if multiple frame, * frameNum */
	header->lnoscan		= header->ydim*framesnumber;  
	header->xdim		= PICM_Get_pixeldimension_x();
    header->scramble = 1;
    header->lastvalue   = 0x5555;
	header->WinView_id  = 0x1234567;
	header->file_header_ver = HEADER_VERSION;
    
   
    /*  write CSMA HEADER to Output File  */
	WriteFile ( fileptr,
				(LPCVOID) header,
				BytesToWrite,
				BytesWritten,
				0);

    /*  release Header Memory  */
    delete ( header ); 

	return (fileptr);
}

/*****************************************************************************
*
*       Test_WriteTestFile
*
*       <some lines description>
*
*       global/static
*       in:     -
*
*       out:    -
*
*
*   errors: -
*
*-----------------------------------------------------------------------------
*/
void Test_WriteTestFile
(
 HANDLE fileptr,				   /* pointer to file		 */
 void *big_buffer,				   /* buffer holding data.   */
 int byte_size_of_pixel            /* size of a pixel in bytes */
 )
{
    /*  Generate a TEST CSMA DATA file  */
    LPCVOID address;
    DWORD BytesToWrite;
	LPDWORD BytesWritten;
	DWORD temp;

	BytesWritten = &temp;
          
    /*  write data to Output File  */
    address = (LPCVOID)big_buffer;

	BytesToWrite =	(long)PICM_Get_pixeldimension_x() * 
					(long)byte_size_of_pixel * 
					(long)PICM_Get_pixeldimension_y();
	WriteFile ( fileptr,
				address,
				BytesToWrite,
				BytesWritten,
				0);

   
}   /*  end of Test_WriteTestFile()  */

tagCSMAHEAD::tagCSMAHEAD()
{
  WinView_id = 0x1234567; // magic number should be a const def.
  file_header_ver = (float)HEADER_VERSION;

}

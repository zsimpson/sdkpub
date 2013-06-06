// dAcquire.cpp : implementation file
//

#include "stdafx.h"
#include "Mlt2comx.h"
#include "dAcquire.h"
#include <stdio.h>
#include <string.h>

extern "C"
{
#define PIXCM 1
#include "platform.h"
#include "pigendef.h"
#include "pigenfcn.h"
#include "pifcsfcn.h"
#include "pimltfcn.h"
#include "piimgfcn.h"
}

#include "cheader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HANDLE Test_WriteTestFile
(
 char     *runfile,                /* data file to write to. */
 void huge *big_buffer,            /* buffer holding data.   */
 int byte_size_of_pixel            /* size of a pixel in bytes */
  );


/////////////////////////////////////////////////////////////////////////////
// CdAcquire dialog


CdAcquire::CdAcquire(CWnd* pParent /*=NULL*/)
	: CDialog(CdAcquire::IDD, pParent)
{
	//{{AFX_DATA_INIT(CdAcquire)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CdAcquire::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CdAcquire)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CdAcquire, CDialog)
	//{{AFX_MSG_MAP(CdAcquire)
	ON_BN_CLICKED(IDC_RUN, OnRun)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CdAcquire message handlers
BOOL CdAcquire::OnInitDialog()
{
	PICM_Set_Temperature(-20.0);
    
    return TRUE;
}

void CdAcquire::OnRun() 
{
	long buffer_size;
    static HANDLE hglb;
	static HANDLE hglb2;
    static void *lpvBuffer;
    static void *lpvBuffer2;

	int controller_ok;
	int done_flag;
	unsigned int status;
	unsigned int error_code;
	BOOL error_flag = FALSE;	
    int last_frame_cnt = 1;

	/* Create a buffer and pointer to the buffer *
	*	to send to initialize the system		*/
    PICM_Set_AutoStop (TRUE);

    buffer_size = PICM_SizeNeedToAllocate();
    hglb = GlobalAlloc(GPTR, buffer_size );
    lpvBuffer = (void huge*) GlobalLock(hglb);
    hglb2 = GlobalAlloc(GPTR, buffer_size );
    lpvBuffer2 = (void huge*) GlobalLock(hglb2);
    
	controller_ok = PICM_Initialize_System(
									lpvBuffer,
                                    &error_code);

    while (last_frame_cnt < 3)
    {
        status = 0;
        controller_ok = PICM_Start_1frame();
        done_flag = FALSE;
        
        /* check for returned data */
        while (!done_flag)
            done_flag = PICM_ChkData(&status);
        
        /* write to a file */
        if (last_frame_cnt == 1)
            Test_WriteTestFile( "test.spe", lpvBuffer, 2);
        else
            Test_WriteTestFile( "test2.spe", lpvBuffer2, 2);

        controller_ok = PICM_Stop_1frame();
        PICM_SetNewUserBuffer(lpvBuffer2, &status);
        last_frame_cnt++;
    }

    if (done_flag >= 1)
        MessageBox ("Data was Collected",
                    "Collection",
                    MB_OK | MB_ICONEXCLAMATION);
    else
        MessageBox ("Error in Data Collection",
                    "Collection",
                    MB_OK | MB_ICONEXCLAMATION);

    /* Clean up and release buffer  */
    PICM_CleanUp();
}


/*****************************************************************
*
*		Test_WriteTestFile
*
*		Description:	Opens a file to write to.  Also writes
*						the header for that file.
*
*****************************************************************/

HANDLE Test_WriteTestFile
(
 char		*runfile,               /* data file to write to. */
 void huge	*big_buffer,            /* buffer holding data.   */
 int byte_size_of_pixel             /* size of a pixel in bytes */
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
	header->lnoscan		= header->ydim;  
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

	/*  Generate a TEST CSMA DATA file  */
    LPCVOID address;

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

    CloseHandle( fileptr );

	return fileptr;
}

tagCSMAHEAD::tagCSMAHEAD()
{
    WinView_id = 0x1234567; // magic number should be a const def.
    file_header_ver = (float)HEADER_VERSION;
}
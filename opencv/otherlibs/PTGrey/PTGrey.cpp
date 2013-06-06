// PTGrey.cpp : Defines the entry point for the DLL application.
//

#include "windows.h"

#include "PGControl.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "cv.h"
#include "ipl.h"
extern "C"
{
#include "highgui.h"
}

// PGR include files
#include "Digiclops.h"
#include "Triclops.h"
#if ( DIGICLOPS_VERSION > 200 )
#include "pgrgui.h"
#endif


#define PTGREYAPI __declspec(dllexport)
#include "PTGrey.h"

PTGREYAPI const char* GetErrorMessage();

HANDLE PTGreyProcessorThread;

DigiclopsContext digiclops	        = NULL; 
TriclopsContext tcontext	        = NULL; 
#if ( DIGICLOPS_VERSION > 200 )
PgrGuiContext   cameraControlContext    = NULL;
#endif

PGClient *PGC;
PGServer *PGS; 
char *PGreyData, *PGData; 
int SmootherStart; 
TriclopsColorImage t24Image;
TriclopsImage t8Image; 
TriclopsInput TriclopsIn[4]; 
TriclopsError tcError; 
DigiclopsError e; 
TriclopsImage16 tImage16;
TriclopsInput* TriclopsBuffer = 0; 
int PTFrameCount = 0, PTPrevFrameCount = 0, PTFreeFrameCount = 0, PTFrameNumber;
clock_t* tickCount;
int PointCount = 0;
static int RawResolution = 0, StereoResolution = 0;

#define _PT_MAX_THREADS 10
int threadIds[_PT_MAX_THREADS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int threadRefCount[_PT_MAX_THREADS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int activeThreadCount = 0;

HANDLE PTGreyDataMutex = 0;
HANDLE PTGreyFrameMutex = 0;

static char PTGreyErrorString[9128];

static IplImage* temp;
static IplImage* temp8;

const char* config_filename = 0;


void InitPGClient();
void copyTriclopsInput(TriclopsInput tInput, TriclopsInput* tOutput);
void WriteDisparityFile(TriclopsImage16* depthImage16, const char* filename);
void WritePointFile(TriclopsImage16 *image, char *filename);
void WriteColorPointFile(TriclopsImage16 *image, TriclopsColorImage *colorImage, char *filename);
BOOL PTRectifyInputDisparity();

PTGREYAPI const char* PTGreyGetErrorMessage()
{
    return PTGreyErrorString;
}
PTGREYAPI void ClearErrorMessage()
{
    PTGreyErrorString[0] = 0;
}

static void SetErrorMessage(const char* str, ...)
{
    va_list valist;
    va_start(valist, str);
    vsprintf(PTGreyErrorString, str, valist);
}

DWORD __stdcall CameraProcessor(void*);

/*BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}*/

void SetParameters () {
	if(triclopsSetDisparity(tcontext, PGC->MinDisparity, PGC->MaxDisparity))
        SetErrorMessage("triclopsSetDisparity setting error.");
	if (triclopsSetTextureValidation(tcontext, PGC->TextureValidation != 0))
        SetErrorMessage("triclopsSetTextureValidation setting error.");
	if(triclopsSetTextureValidationThreshold(tcontext, PGC->TextureValidationThreshold))
        SetErrorMessage("triclopsSetTextureValidationThreshold setting error. \n");
	if(triclopsSetTextureValidationMapping(tcontext, PGC->TextureValidationMapping))
        SetErrorMessage("triclopsSetTextureValidationMapping setting error. \n");

	if(triclopsSetUniquenessValidation(tcontext, PGC->UniquenessValidation != 0))
        SetErrorMessage("triclopsSetUniquenessValidation setting error. \n");
	if(triclopsSetUniquenessValidationThreshold(tcontext, PGC->UniquenessValidationThreshold))
        SetErrorMessage("triclopsSetUniquenessValidationThreshold setting error. \n");
	if(triclopsSetUniquenessValidationMapping(tcontext, PGC->UniquenessValidationMapping))
        SetErrorMessage("triclopsSetUniquenessValidationMapping setting error. \n");

	if(triclopsSetStereoMask(tcontext, PGC->StereoMask))
        SetErrorMessage("triclopsSetStereoMask setting error. \n");
	if(triclopsSetEdgeMask(tcontext, PGC->EdgeMask))
        SetErrorMessage("triclopsSetEdgeMask setting error. \n");

	if(triclopsSetEdgeCorrelation(tcontext, PGC->EdgeCorrelation != 0))
        SetErrorMessage("triclopsSetEdgeCorrelation setting error. \n");
	if (triclopsSetSubpixelInterpolation(tcontext, PGC->SubPixelInterpolation != 0))
        SetErrorMessage("triclopsSetSubpixelInterpolation setting error. \n");
	if(triclopsSetStrictSubpixelValidation(tcontext, PGC->StrictSubPixelValidation != 0))
        SetErrorMessage("triclopsSetStrictSubpixelValidation setting error. \n");

	if(triclopsSetRectify(tcontext, PGC->Rectify != 0))
        SetErrorMessage("triclopsSetRectify setting error. \n");
	if(triclopsSetLowpass( tcontext, PGC->LowPass != 0))
        SetErrorMessage("triclopsSetLowpass setting error. \n");
	if(triclopsSetDoStereo( tcontext, PGC->DoStereo != 0))
        SetErrorMessage("triclopsSetDoStereo setting error. \n");
	if(triclopsSetDebug(tcontext, PGC->PGDebug != 0))
        SetErrorMessage("triclopsSetDebug( setting error. \n");
}

PTGREYAPI BOOL PTGreyInitCamera()
{
    HANDLE hFileMappingObject;
    DigiclopsError digiclopsError;
    TriclopsError triclopsError;

    // Clear error string
    ClearErrorMessage();

	// allocate the Point Grey camera shared memory.
	hFileMappingObject = CreateFileMapping(HANDLE(-1), 0, PAGE_READWRITE, 0, 0xa000000, "PointGreySharedMemory");
    int e = GetLastError();
	PGreyData = (char*) MapViewOfFile(hFileMappingObject, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	PGC = (PGClient *) PGreyData;						// map server control structure in our shared buffer.
	PGS = (PGServer *) ((int)PGreyData + sizeof(PGClient));		// map client control structure in our shared buffer.

    PGS->BackGroundAvailable = 0;		// 
	PGS->Initializing = true;
	PGData = (char *) ((int)PGreyData + sizeof(PGClient) + sizeof(PGServer) + (32 - sizeof(PGClient) % 32));	   // aligned buffer
	PGS->DigiclopsBase = (char *) PGreyData;			// allow vb code to translate our buffer addresses

	// create the Digiclops context
    if(digiclopsError = digiclopsCreateContext(&digiclops))					
    {
        SetErrorMessage ("Error - digiclopsCreateContext: %s", digiclopsErrorToString(digiclopsError));
        return FALSE;
    }

#if ( DIGICLOPS_VERSION < 200 )
    // connect to the camera - note this assumes that the Digiclops is device 0
    // on the bus
    if(digiclopsError = digiclopsInitialize(digiclops, 0))
    {
        SetErrorMessage ("Error - digiclopsInitialize: %s", digiclopsErrorToString(digiclopsError));
        return FALSE;
    }
#else
    // connect to the camera - 
    // this call pops up a dialog that allows the user to select the
    // Digiclops from a list on the bus
    PgrGuiContext pgrGuiContext;
    PgrGuiError pgrGuiError = pgrguiCreateContext( &pgrGuiContext,
                                                   digiclops,
                                                   DIGICLOPS_INITIALIZE_DIALOG );
    if ( pgrGuiError != PGRGUI_ok )
    {
        SetErrorMessage ("Error - PGR Gui Create context: unknown error" );
        pgrguiDestroyContext( pgrGuiContext );
        return FALSE;
    }
    bool bResult;
    pgrguiShowModal( pgrGuiContext, &bResult );
    if ( !bResult )
    {
        SetErrorMessage ("Error - Select Digiclops: cancelled by user" );
        pgrguiDestroyContext( pgrGuiContext );
        return FALSE;
    }
    pgrguiDestroyContext( pgrGuiContext );
#endif

    /* Load the configuration file for the PointGrey camera */
#if ( DIGICLOPS_VERSION < 200 )
    if(config_filename == 0 || 
		(triclopsError = triclopsGetDefaultContextFromFile(&tcontext, const_cast<char*>(config_filename)))) 
    {
        SetErrorMessage ("Error - triclopsGetDefaultContextFromFile: %s", triclopsErrorToString(triclopsError));
        return FALSE;
    }
#else
    // if the config file name is null, try getting the configuration from the
    // camera
    if( config_filename == 0 )
    {
        if ( digiclopsGetTriclopsContextFromCamera( digiclops, &tcontext) )
        {
            SetErrorMessage ("Error - digiclopsGetTriclopsContextFromCamera: " );
            return FALSE;
        }
    }
    // try to read the configuration from a file
    else
    {
        if ( (triclopsError = triclopsGetDefaultContextFromFile(&tcontext, const_cast<char*>(config_filename)))) 
        {
            SetErrorMessage ("Error - triclopsGetDefaultContextFromFile: %s", triclopsErrorToString(triclopsError));
            return FALSE;
        }
    }
#endif

	if(digiclopsError = digiclopsStart(digiclops))					
    {
        SetErrorMessage ("Error - digiclopsStart: %s", digiclopsErrorToString(digiclopsError));
        return FALSE;
    }

#if ( DIGICLOPS_VERSION < 200 )
	// this call is obsolete for v2.0+ as the system automatically detects
	// the camera type
	if(digiclopsError = digiclopsSetCameraType(digiclops, DIGICLOPS_COLOR)) 
    {
        SetErrorMessage ("Error - digiclopsSetCameraType: %s", digiclopsErrorToString(digiclopsError));
        return FALSE;
    }
#endif

	if(digiclopsError = digiclopsSetImageTypes(digiclops, ALL_IMAGES))
    {
        SetErrorMessage ("Error - digiclopsSetImageTypes: %s", digiclopsErrorToString(digiclopsError));
        return FALSE;
    }

    // Initialize settings...
    InitPGClient();

	// Reallocate everything based on new rows and cols (if they changed).
    PGS->OutputBuffers[0] = PGData;
    for(int i = 1; i < PG_IMAGE_MAX; i++)
    {
        PGS->OutputBuffers[i] = PGS->OutputBuffers[i - 1] + PGC->MaxCols*PGC->MaxRows*PTGreyGetPixelSize(i - 1);
    }
	for(i = 0; i < PG_IMAGE_MAX; i++)
	{
		PGS->DataBuffers[i] = new char[PGC->MaxCols*PGC->MaxRows*PTGreyGetPixelSize(i)];
	}

	if (PGC->MaxCols*PGC->MaxRows*31 >= PGC->Total_Memory) 
    {
        SetErrorMessage("Insufficient buffer allocated.  Len = 0x%x\n", PGC->ncols*PGC->nrows*42 ); Sleep (4000); return 1;
    };
	PGS->FrameCount = 0;

   	PGS->Initializing = true;
	PGC->NewParameters = 0;		// reset for the next time.

    memset(PGS->NewData, 0, PG_IMAGE_MAX*sizeof(int));

#if ( DIGICLOPS_VERSION < 200 )
	if (PGC->nrows == 640) // Only 2 choices for raw input format.
    {	
		if(digiclopsError = digiclopsSetImageResolution(digiclops, (DigiclopsImageResolution) DIGICLOPS_640x480))
        {
            SetErrorMessage ("Error - digiclopsSetImageResolution: %s", digiclopsErrorToString(digiclopsError));
            return FALSE;
        }
	} 
    else 
    {
		if(digiclopsError = digiclopsSetImageResolution(digiclops, (DigiclopsImageResolution) DIGICLOPS_320x240))
        {
            SetErrorMessage ("Error - digiclopsSetImageResolution: %s", digiclopsError);
            return FALSE;
        }
	}
#else
    if (PGC->nrows > 320) // Only 2 choices for raw input format.
    {	
        if(digiclopsError = digiclopsSetImageResolution(digiclops, DIGICLOPS_FULL))
        {
            SetErrorMessage ("Error - digiclopsSetImageResolution: %s", digiclopsErrorToString(digiclopsError));
            return FALSE;
        }
    } 
    else 
    {
        if(digiclopsError = digiclopsSetImageResolution(digiclops, DIGICLOPS_HALF))
        {
            SetErrorMessage ("Error - digiclopsSetImageResolution: %s", digiclopsError);
            return FALSE;
        }
    }
#endif

	if(triclopsError = triclopsSetResolution(tcontext, PGC->DRows, PGC->DCols))
    {
        SetErrorMessage ("Error - triclopsSetResolution: %s", triclopsErrorToString(triclopsError));
        return FALSE;
    }

	PGS->Initializing = false;

	SetParameters ();

	if(triclopsError = triclopsSetImageBuffer(tcontext, (unsigned char *) PGS->DataBuffers[PT_EDGE_IMAGE], 
        TriImg_EDGE, TriCam_REFERENCE))	
    {
        SetErrorMessage ("Error - triclopsSetImageBuffer: %s", triclopsErrorToString(triclopsError)); 
        return FALSE;
    }
    
	if(triclopsSetResolutionAndPrepare(tcontext, PGC->DRows, PGC->DCols, PGC->nrows, PGC->ncols))
    {
        SetErrorMessage ("Error - triclopsSetResolutionAndPrepare: %s", triclopsErrorToString(triclopsError));	 // for 16-bit disparity buffer
    }


    triclopsSetSurfaceValidationSize(tcontext, 1000);
    triclopsSetSurfaceValidationMapping(tcontext, 0xff);
    triclopsSetSurfaceValidation(tcontext, 1);
    
    temp = cvCreateImage(cvSize(PGC->DCols, PGC->DRows), IPL_DEPTH_16U, 1);
    temp8 = cvCreateImage(cvSize(PGC->DCols, PGC->DRows), IPL_DEPTH_8U, 1);
    iplSet(temp8, PGC->MinDisparity);
    
    // must supply threadId for people running Win95/98
    DWORD threadId;
    PTGreyProcessorThread = CreateThread(0, 0, LPTHREAD_START_ROUTINE(CameraProcessor), 0, 0, &threadId);
    if ( PTGreyProcessorThread == 0 )
    {
        DWORD errorId = GetLastError();
        SetErrorMessage( "Fatal error : CreateThread failed : Error = %d", errorId );
        return FALSE;
    }
    PTGreyDataMutex = CreateMutex(0, FALSE, "PTGreyDataMutex");

    return TRUE;
}

static void _LoadRawImage (int ImageIndex)
{
    assert(ImageIndex >= 0 && ImageIndex < 4);
    
    DigiclopsError digiclopsError;
    TriclopsInput& TCIn = TriclopsIn[ImageIndex];

    int ImageType = PG_DIGICLOPS_IMAGE(ImageIndex);

    if(digiclopsError = digiclopsExtractTriclopsInput(digiclops, ImageType, &TCIn)) 
    {
        SetErrorMessage("Error - digiclopsExtractTriclopsInput: %s", digiclopsErrorToString(digiclopsError));
    }

	memcpy (PGS->DataBuffers[ImageIndex], (unsigned char *) TCIn.u.rgb32BitPacked.data, TCIn.ncols*TCIn.nrows*4);	   // 4 bytes per pixel
}

static void LoadRawImage (int ImageIndex) // used to copy raw images from triclops area to shared memory.
{
	if(!PGC->ImageList[ImageIndex]) 
    {
        return;
    }

    _LoadRawImage(ImageIndex);
}

static void LoadComputedImage(int ImageIndex) 		// used to get Rectified or Edge images.  
{
    DigiclopsError digiclopsError;
    TriclopsError triclopsError;
	if(!PGC->ImageList[ImageIndex])
    {
        return;
    }

    if(ImageIndex == PT_EDGE_IMAGE)
    {
        if (triclopsError = triclopsGetImage(tcontext, TriImg_EDGE, TriCam_REFERENCE, &t8Image)) 
        {
            SetErrorMessage("Error - triclopsGetImage: %s", triclopsErrorToString(triclopsError));
        }
    	memcpy (PGS->DataBuffers[ImageIndex], (unsigned char *) t8Image.data, PGC->DCols*PGC->DRows);
    }
    else if(ImageIndex == PT_RECTIFIED_IMAGE)
    {
        PTGreyImageType raw = PT_RIGHT_RAW_IMAGE;
        TriclopsInput& TCIn = TriclopsIn[raw];
        if(!PGC->ImageList[raw])
        {
            // Since this view has not been requested, the digiclopsExtractTriclops has
            // not been called for it
    		if(digiclopsError = digiclopsExtractTriclopsInput( 
                    digiclops, PG_DIGICLOPS_IMAGE(ImageIndex), &TCIn))
                SetErrorMessage("Error - digiclopsExtractTriclopsInput: %s", digiclopsErrorToString(digiclopsError));
        }
    	if(triclopsError = triclopsPreprocess(tcontext, &TCIn))
            SetErrorMessage("Error - triclopsPreprocess: %s", triclopsErrorToString(triclopsError));
#if ( DIGICLOPS_VERSION < 200 )
    	triclopsRectifyColorImage (tcontext, &TCIn, &t24Image);
#else
	triclopsRectifyColorImage (tcontext, TriCam_REFERENCE, &TCIn, &t24Image);
#endif
    	for (int i = 0, j = 0; i < t24Image.nrows * t24Image.ncols; i++, j += 4) 
        {
    		PGS->DataBuffers[ImageIndex][j + 2] = t24Image.red[i];
    		PGS->DataBuffers[ImageIndex][j + 1] = t24Image.green[i];
    		PGS->DataBuffers[ImageIndex][j + 0] = t24Image.blue[i];
    	}
    }
    else
    {
        assert(0);
    }
}

DWORD __stdcall CameraProcessor(void*)
{
	HANDLE hThread; 
	hThread = GetCurrentThread();
//	int e = SetThreadAffinityMask(hThread, 1);	// just the first processor please.
	CloseHandle (hThread);

    // Initialize PGS
    PGS->BackGroundAvailable = 0;

    while( 1 ) 
    {
        DigiclopsError digiclopsError;
        TriclopsError triclopsError;

		if (PGC->NewParameters) 
        {		// New settings are present for the camera.
			SetParameters ();
		}

        if(PGC->PGTerminate) 
            return 0;	// Requested termination.

		if(digiclopsError = digiclopsGrabImage(digiclops)) 
        {
            SetErrorMessage("Error - digiclopsGrabImage: %s", digiclopsErrorToString(digiclopsError));
            return -1;
        }

		LoadRawImage(PT_TOP_RAW_IMAGE);		// Look for any raw images.
		LoadRawImage(PT_LEFT_RAW_IMAGE);
		LoadRawImage(PT_RIGHT_RAW_IMAGE);

        if(PTFreeFrameCount)
        {
            // Require memory deallocation:
            for(int i = 0; i < PTFreeFrameCount*4; i++)
            {
                switch(TriclopsBuffer[i].inputType)
                {
                case TriInp_RGB:
                    free(TriclopsBuffer[i].u.rgb.red);
                    free(TriclopsBuffer[i].u.rgb.green);
                    free(TriclopsBuffer[i].u.rgb.blue);
                    break;
                case TriInp_RGB_32BIT_PACKED:
                    free(TriclopsBuffer[i].u.rgb32BitPacked.data);
                    break;
                }
            }

            delete TriclopsBuffer;
            TriclopsBuffer = 0;
            PTFreeFrameCount = 0;
            PTPrevFrameCount = PTFrameCount; // Initialize pre-frame-count here if frame count = 0
        }

        if(PTFrameCount != 0)
        {
            // Loading raw images
            if(!PGC->ImageList[0])
                if(digiclopsError = digiclopsExtractTriclopsInput(digiclops, TOP_IMAGE, &TriclopsIn[0])) 
                    SetErrorMessage("Error - digiclopsExtractTriclopsInput: %s", 
                        digiclopsErrorToString(digiclopsError));
            if(!PGC->ImageList[1])
                if(digiclopsError = digiclopsExtractTriclopsInput(digiclops, TOP_IMAGE, &TriclopsIn[1])) 
                    SetErrorMessage("Error - digiclopsExtractTriclopsInput: %s", 
                        digiclopsErrorToString(digiclopsError));
            if(!PGC->ImageList[2])
                if(digiclopsError = digiclopsExtractTriclopsInput(digiclops, TOP_IMAGE, &TriclopsIn[2])) 
                    SetErrorMessage("Error - digiclopsExtractTriclopsInput: %s", 
                        digiclopsErrorToString(digiclopsError));
			if(digiclopsError = digiclopsExtractTriclopsInput(digiclops, STEREO_IMAGE, &TriclopsIn[3]))
                SetErrorMessage("Error - digiclopsExtractTriclopsInput: %s", digiclopsErrorToString(digiclopsError));
            
            if(PTFrameNumber == 0)
            {
                // This is the first time, let's allocate the memory:
                TriclopsBuffer = new TriclopsInput[PTFrameCount*4];
                memset(TriclopsBuffer, 0, PTFrameCount*4*sizeof(TriclopsInput));
            }

            // Saving images
            for(int i = 0; i < 4; i++)
            {
                copyTriclopsInput(TriclopsIn[i], &TriclopsBuffer[4*PTFrameNumber + i]);
            }
            PTFrameNumber++;
            if(PTFrameNumber == PTFrameCount)
            {
                // Stop saving frames...
                PTPrevFrameCount = PTFrameCount;
                PTFrameNumber = 0;
                PTFrameCount = 0;
            }
        }

		if (PGC->ComputedView != 0 )	
        {
            TriclopsInput& TCIn = TriclopsIn[3]; // For stereo image
			// If any of the computed views have been requested, then fill it in.

            if(!TriclopsBuffer)
            {
                // The stereo image has not been extracted yet...
			    if(digiclopsError = digiclopsExtractTriclopsInput(digiclops, STEREO_IMAGE, &TCIn))
                    SetErrorMessage("Error - digiclopsExtractTriclopsInput: %s", digiclopsErrorToString(digiclopsError));
            }
			if(triclopsError = triclopsPreprocess(tcontext, &TCIn))
                SetErrorMessage("Error - triclopsPreprocess: %s", triclopsErrorToString(triclopsError));
			if(triclopsError = triclopsStereo(tcontext))
                SetErrorMessage("Error - triclopsStereo: %s", triclopsErrorToString(triclopsError));

			// The disparity, point cloud and background views are interrelated.  All need the image16 buffer.
			if(triclopsError = triclopsGetImage16(tcontext, TriImg16_DISPARITY, TriCam_REFERENCE, &tImage16))
                SetErrorMessage("Error - triclopsGetImage16: %s", triclopsErrorToString(triclopsError));

			if (PGC->ImageList[PT_DISPARITY_IMAGE] != 0 ) 
            {	// Disparity image 
/*
				for (int i=0 ;i<PGC->DRows*PGC->DCols; i++) 
                {
					int HighByte = tImage16.data[i];
					PGS->DataBuffers[PT_DISPARITY_IMAGE][i] = (tImage16.data[i] < 0xff00) ? (char) (HighByte >> 8) : (char) PGC->MinDisparity;
				}
*/

				IplImage* temp2 = cvCreateImageHeader(cvSize(PGC->DCols, PGC->DRows), IPL_DEPTH_8U, 1);
				cvSetImageData(temp2, (void*)PGS->DataBuffers[PT_DISPARITY_IMAGE], PGC->DCols);

				IplImage* temp1 = cvCreateImageHeader(cvSize(PGC->DCols, PGC->DRows), IPL_DEPTH_16U, 1);
				cvSetImageData(temp1, tImage16.data, tImage16.rowinc);
				IplImage* mask = iplCreateImageHeader(
					1, 0, IPL_DEPTH_1U, "GRAY", "GRAY",
					IPL_DATA_ORDER_PIXEL, IPL_ORIGIN_TL,
					IPL_ALIGN_DWORD, PGC->DCols, PGC->DRows, NULL, NULL,
					NULL, NULL);
				iplAllocateImage(mask, 0, 0);

				iplCopy(temp1, temp);
				iplRShiftS(temp, temp, 8);
				iplConvert(temp, temp2);
				iplThreshold(temp, mask, 0x0ff0);
				cvThreshold(temp2, temp2, 0xf0, 0, CV_THRESH_TOZERO_INV);
				temp8->maskROI = mask;
				temp2->maskROI = mask;
				iplOr(temp8, temp2, temp2);

				temp->maskROI = 0;
				iplDeallocate(mask, IPL_IMAGE_ALL);
				cvReleaseImageHeader(&temp1);
				cvReleaseImageHeader(&temp2);

			}

			if (PGC->ImageList[PT_DISPARITY_OBJ_IMAGE] != 0 ) 
            {	// Disparity image 
                memcpy(PGS->DataBuffers[PT_DISPARITY_OBJ_IMAGE], 
                    PGS->DataBuffers[PT_DISPARITY_IMAGE], 
                    PGC->DRows*PGC->DCols*PTGreyGetPixelSize(PT_DISPARITY_IMAGE));
			}

            // Get the edge image
			LoadComputedImage(PT_EDGE_IMAGE);

            // If they have requested a color rectified image or rectified image, provide that as well.
            LoadComputedImage(PT_RECTIFIED_IMAGE);

            if (PGC->ImageList[PT_BACKGROUND_IMAGE] != 0) 
            {
				memcpy (PGS->DataBuffers[PT_BACKGROUND_IMAGE], (unsigned char *) tImage16.data, PGC->DRows*PGC->DCols*2);
				PGS->BackGroundAvailable = 1;	// Unavailable until we are done averaging.
                PGC->ImageList[PT_BACKGROUND_IMAGE] = 0;
			}

            PointCount = 0;
            if (PGC->ImageList[PT_DISPARITY_OBJ_IMAGE] && PGS->BackGroundAvailable) 
// calculate object's disparity    
            {
				for (int i=0; i<PGC->DRows*PGC->DCols; i++) 
                {
                    unsigned char* bkg = (unsigned char*)PGS->DataBuffers[PT_BACKGROUND_IMAGE];
					PGS->DataBuffers[PT_DISPARITY_OBJ_IMAGE][i] = (char) PGC->MinDisparity;
					if (tImage16.data[i] < 0xff00) 
                    {	
                        // if the point is valid
						if ((tImage16.data[i] >> 8) > PGC->DisparityThreshold &&
                            (abs(tImage16.data[i] - bkg[i]) >> 8) > PGC->DifferenceThreshold)
                        {
							PGS->DataBuffers[PT_DISPARITY_OBJ_IMAGE][i] = (tImage16.data[i] >> 8);
						}
					}
				}

//    disparity image rectification procedure 
				if(PGC->ImageList[/*PT_RIGHT_RAW_IMAGE*/PT_RECTIFIED_IMAGE] !=0 && PGC->RectifiedDisparity != 0)
				{
//					PTRectifyInputDisparity();
				}

                if(PGC->ImageList[PT_POINTCLOUD_IMAGE])
                {
    				int Cnt = 0;
    				xyzTuple* OGLCloud = (xyzTuple *) PGS->DataBuffers[PT_POINTCLOUD_IMAGE];
    				for (i=0; i<PGC->DRows*PGC->DCols; i++) 
                    {
    					if (PGS->DataBuffers[PT_DISPARITY_OBJ_IMAGE][i] != PGC->MinDisparity) 
                        {	
    						triclopsRCD16ToXYZ	( tcontext, i/PGC->DCols, i%PGC->DCols, tImage16.data[i], &OGLCloud[Cnt].x, &OGLCloud[Cnt].y, &OGLCloud[Cnt].z);
    						if (OGLCloud[Cnt].z > 0 && OGLCloud[Cnt].z < PGC->ZCapValue) 
                            {  
                                Cnt++;
    						}
                            else 
                            { // make the cleaned up image even cleaner.
//    							PGS->DataBuffers[PT_DISPARITY_IMAGE][i] = (char) PGC->MinDisparity;	
                                PGS->DataBuffers[PT_DISPARITY_OBJ_IMAGE][i] = (char) PGC->MinDisparity;	
    						}
    					}
    				}
                    PointCount = Cnt;
                }
			}

//			WriteDisparityFile(&tImage16, "e:\\users\\vic\\cvl\\matlab\\data\\disparity.bmp");


            PGS->ticks = clock();
			PGS->FrameCount++;
		} else {
			PGS->BackGroundAvailable = 0;	// need to recapture background.
			Sleep (1);
		}

        PTGreyFreezeData(INFINITE);
		for(int i = 0; i < PG_IMAGE_MAX; i++)
		{
			if(PGC->ImageList[i])
				memcpy(PGS->OutputBuffers[i], PGS->DataBuffers[i], 
					PTGreyGetWidth(i)*PTGreyGetHeight(i)*PTGreyGetPixelSize(i));
		}
        memset(PGS->NewData, 255, PG_IMAGE_MAX*sizeof(int));
        PTGreyUnFreezeData();
	}
    
    return 0;
}

PTGREYAPI long PTGreyGetDataSize(int dataType)
{
	switch(dataType)
	{
	case PT_TOP_RAW_IMAGE:
	case PT_LEFT_RAW_IMAGE:
	case PT_RIGHT_RAW_IMAGE:
	case PT_OBJ_IMAGE:
		return PGC->nrows*PGC->ncols*3;

	case PT_RECTIFIED_IMAGE:
	case PT_DISPARITY_IMAGE:
	case PT_DISPARITY_OBJ_IMAGE:
	case PT_EDGE_IMAGE:
		return PGC->DRows*PGC->DCols;

	case PT_BACKGROUND_IMAGE:
		return PGC->DRows*PGC->DCols*2;

	case PT_POINTCLOUD_IMAGE:
		return PGC->DCols*PGC->DRows*12;

	default:
		assert(0);
		return -1;
	}
}

PTGREYAPI BOOL PTGreyGetData(int dataType, void* pData)
{
	int _size = PTGreyGetDataSize(dataType);
    int width = PTGreyGetWidth(dataType);
    int height = PTGreyGetHeight(dataType);
    if(_size <= 0)
    {
        SetErrorMessage("Data type %d not supported.", dataType);
        return FALSE;
    }

    if(!PGC->ImageList[dataType])
    {
        SetErrorMessage("Data type %d is not selected. Use PTGreySelectDataType.", dataType);
        return FALSE;
    }

	WaitForSingleObject(PTGreyDataMutex, INFINITE);

    int i;
    switch(dataType)
    {
    case PT_TOP_RAW_IMAGE:
    case PT_LEFT_RAW_IMAGE:
    case PT_RIGHT_RAW_IMAGE:
	case PT_RECTIFIED_IMAGE:
	case PT_OBJ_IMAGE:
        for(i = 0; i < width*height; i++)
        {
            ((char*)pData)[3*i + 2] = PGS->OutputBuffers[dataType][4*i + 2];
            ((char*)pData)[3*i + 1] = PGS->OutputBuffers[dataType][4*i + 1];
            ((char*)pData)[3*i] = PGS->OutputBuffers[dataType][4*i];
        }
        break;

    case PT_DISPARITY_IMAGE:
    case PT_DISPARITY_OBJ_IMAGE:
    case PT_EDGE_IMAGE:
        memcpy(pData, PGS->OutputBuffers[dataType], _size);
        break;

    default:
        assert(0);
        return FALSE;
    }

    PGS->NewData[dataType] = 0;

    ReleaseMutex(PTGreyDataMutex);

    return TRUE;
}

PTGREYAPI BOOL PTGreyFreezeData(int milliSec)
{
    int wait = WaitForSingleObject(PTGreyDataMutex, milliSec);
    if(wait == WAIT_OBJECT_0)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

PTGREYAPI void PTGreyUnFreezeData()
{
    ReleaseMutex(PTGreyDataMutex);
}

PTGREYAPI const char* PTGreyGetDataPointer(int dataType)
{
    if(dataType < 0 || dataType > PG_IMAGE_MAX)
        return 0;

    PGS->NewData[dataType] = 0;
    return PGS->OutputBuffers[dataType];
}

PTGREYAPI int PTGreyGetWidth(int dataType)
{
    switch(dataType)
    {
    case PT_TOP_RAW_IMAGE:
    case PT_RIGHT_RAW_IMAGE:
    case PT_LEFT_RAW_IMAGE:
	case PT_OBJ_IMAGE:
        return PGC->ncols;

	case PT_RECTIFIED_IMAGE:
    case PT_DISPARITY_IMAGE:
    case PT_DISPARITY_OBJ_IMAGE:
    case PT_EDGE_IMAGE:
    case PT_POINTCLOUD_IMAGE:
        return PGC->DCols;
        
    default:
        assert(0);
        return -1;
    }
}

PTGREYAPI int PTGreyGetHeight(int dataType)
{
    switch(dataType)
    {
    case PT_TOP_RAW_IMAGE:
    case PT_RIGHT_RAW_IMAGE:
    case PT_LEFT_RAW_IMAGE:
	case PT_OBJ_IMAGE:
        return PGC->nrows;

	case PT_RECTIFIED_IMAGE:
    case PT_DISPARITY_IMAGE:
    case PT_DISPARITY_OBJ_IMAGE:
    case PT_EDGE_IMAGE:
    case PT_POINTCLOUD_IMAGE:
        return PGC->DRows;

    default:
        assert(0);
        return -1;
    }
}

PTGREYAPI void PTGreySelectDataType(int dataType, int option)
{
    PTGreyFreezeData(INFINITE);
    if(dataType < 0 || dataType > PG_IMAGE_MAX)
    {
        return;
    }

    PGC->ImageList[dataType] = option;

    PGC->ComputedView = 0;
    for(int i = PTGreyImageType(3); i < PG_IMAGE_MAX; i++)
    {
        PGC->ComputedView = PGC->ComputedView | PGC->ImageList[i];
    }
    
    PTGreyUnFreezeData();
}

PTGREYAPI int PTGreyIsNewData(int dataType)
{
    if(dataType < 0 || dataType >= PG_IMAGE_MAX)
        return FALSE;
    return PGS->NewData[dataType];
}

PTGREYAPI long PTGreyGetPixelSize(int dataType)
{
    switch(dataType)
    {
    case PT_TOP_RAW_IMAGE:
    case PT_LEFT_RAW_IMAGE:
    case PT_RIGHT_RAW_IMAGE:
	case PT_RECTIFIED_IMAGE:
	case PT_OBJ_IMAGE:
        return 4;

    case PT_EDGE_IMAGE:
    case PT_DISPARITY_IMAGE:
    case PT_DISPARITY_OBJ_IMAGE:
        return 1;

    case PT_BACKGROUND_IMAGE:
        return 2;

    case PT_POINTCLOUD_IMAGE:
        return 12;

    default:
        assert(0);
        return -1;
    }
}

PTGREYAPI BOOL PTGreyGetProperty(const char* name, void* buffer)
{
    if(strcmp(name, "MinDisparity") == 0)
    {
        *(int*)buffer = PGC->MinDisparity;
    }
    else if(strcmp(name, "MaxDisparity") == 0)
    {
        *(int*)buffer = PGC->MaxDisparity;
    }
    else if(strcmp(name, "StereoResolution") == 0)
    {
        *(int*)buffer = PGC->DCols == 640 ? 2 : PGC->DCols == 320 ? 1 : 0;
    }
    else if(strcmp(name, "RawResolution") == 0)
    {
        *(int*)buffer = PGC->ncols == 640 ? 1 : 0;
    }
    else if(strcmp(name, "DifferenceThreshold") == 0)
    {
        *(float*)buffer = (float)PGC->DifferenceThreshold;
    }
    else if(strcmp(name, "DisparityThreshold") == 0)
    {
        *(float*)buffer = (float)PGC->DisparityThreshold;
    }
    else if(strcmp(name, "DepthThreshold") == 0)
    {
        *(float*)buffer = PGC->ZCapValue;
    }
    else if(strcmp(name, "CameraBrightness") == 0)
    {
        long value;
        bool isauto;
#if ( DIGICLOPS_VERSION < 200 )
        digiclopsGetVideoProperty(digiclops, DIGICLOPS_BRIGHTNESS, &value, &isauto);
#else
	digiclopsGetCameraProperty(digiclops, DIGICLOPS_GAIN, &value, &isauto);
#endif
        assert(value >= 0);
        *(int*)buffer = isauto ? -value : value;
    }
    else if(strcmp(name, "CameraIris") == 0)
    {
        long value;
        bool isauto;
#if ( DIGICLOPS_VERSION < 200 )
        digiclopsGetVideoProperty(digiclops, DIGICLOPS_IRIS, &value, &isauto);
#else
	digiclopsGetCameraProperty(digiclops, DIGICLOPS_SHUTTER, &value, &isauto);
#endif
        assert(value >= 0);
        *(int*)buffer = isauto ? -value : -value;
    }
    else if(strcmp(name, "CameraExposure") == 0)
    {
        long value;
        bool isauto;
#if ( DIGICLOPS_VERSION < 200 )
        digiclopsGetVideoProperty(digiclops, DIGICLOPS_EXPOSURE, &value, &isauto);
#else
	digiclopsGetCameraProperty(digiclops, DIGICLOPS_AUTO_EXPOSURE, &value, &isauto);
#endif
        assert(value >= 0);
        *(int*)buffer = isauto ? -value : -value;
    }
    else if(strcmp(name, "") == 0)
    {
        *(int*)buffer = PGC->RectifiedDisparity;
    }
    else
    {
        return FALSE;
    }

    return TRUE;
}

PTGREYAPI BOOL PTGreySetProperty(const char* name, void* buffer)
{
    BOOL ret = TRUE;
    PTGreyFreezeData(INFINITE);
    if(strcmp(name, "MinDisparity") == 0)
    {
        PGC->MinDisparity = *(int*)buffer;
    }
    else if(strcmp(name, "MaxDisparity") == 0)
    {
        PGC->MaxDisparity = *(int*)buffer;
    }
    else if(strcmp(name, "StereoResolution") == 0)
    {
        StereoResolution = *(int*)buffer;
    }
    else if(strcmp(name, "RawResolution") == 0)
    {
        RawResolution = *(int*)buffer;
    }
    else if(strcmp(name, "DifferenceThreshold") == 0)
    {
        PGC->DifferenceThreshold = (int)*(float*)buffer;
    }
    else if(strcmp(name, "DisparityThreshold") == 0)
    {
        PGC->DisparityThreshold = (int)*(float*)buffer;
    }
    else if(strcmp(name, "DepthThreshold") == 0)
    {
        PGC->ZCapValue = *(float*)buffer;
    }
    else if(strcmp(name, "CameraBrightness") == 0)
    {
        int input = *(int*)buffer;
        long value = abs(input);
        bool isauto = !!(input & 0x80000000);
#if ( DIGICLOPS_VERSION < 200 )
        digiclopsSetVideoPropertyAuto(digiclops, DIGICLOPS_BRIGHTNESS, isauto);
        digiclopsSetVideoProperty(digiclops, DIGICLOPS_BRIGHTNESS, value);
#else
	digiclopsSetCameraProperty(digiclops, DIGICLOPS_GAIN, value, isauto);
#endif
    }
    else if(strcmp(name, "CameraIris") == 0)
    {
        int input = *(int*)buffer;
        long value = abs(input);
        bool isauto = !!(input & 0x80000000);
#if ( DIGICLOPS_VERSION < 200 )
        digiclopsSetVideoPropertyAuto(digiclops, DIGICLOPS_IRIS, isauto);
        digiclopsSetVideoProperty(digiclops, DIGICLOPS_IRIS, value);
#else 
	digiclopsSetCameraProperty(digiclops, DIGICLOPS_SHUTTER, value, isauto);
#endif
    }
    else if(strcmp(name, "CameraExposure") == 0)
    {
        int input = *(int*)buffer;
        long value = abs(input);
        bool isauto = !!(input & 0x80000000);
#if ( DIGICLOPS_VERSION < 200 )
        digiclopsSetVideoPropertyAuto(digiclops, DIGICLOPS_EXPOSURE, isauto);
        digiclopsSetVideoProperty(digiclops, DIGICLOPS_EXPOSURE, value);
#else
	digiclopsSetCameraProperty(digiclops, DIGICLOPS_AUTO_EXPOSURE, value, isauto);
#endif
    }
    else if(strcmp(name, "") == 0)
    {
        PGC->RectifiedDisparity = *(int*)buffer;
    }

    PTGreyUnFreezeData();
    return ret;
}

void InitPGClient()
{
    PGC->Total_Memory = 0xa000000;
    PGC->MaxCols = 640;
    PGC->MaxRows = 480;
    switch(RawResolution)
    {
    case 0:
        PGC->ncols = 320;
        PGC->nrows = 240;
        break;
    case 1:
        PGC->ncols = 640;
        PGC->nrows = 480;
        break;
    default:
        assert(0);
        break;
    }

    switch(StereoResolution)
    {
    case 0:
        PGC->DCols = 160;
        PGC->DRows = 120;
        break;
    case 1:
        PGC->DCols = 320;
        PGC->DRows = 240;
        break;
    case 2:
        PGC->DCols = 640;
        PGC->DRows = 480;
        break;
    default:
        assert(0);
        break;
    }

    PGC->MinDisparity = 2;
    PGC->MaxDisparity = 80;
    
    PGC->SubPixelInterpolation = 1;
    PGC->StrictSubPixelValidation = 1;
    
    PGC->StereoMask = 15;
    PGC->Rectify = 1;
    PGC->LowPass = 1;
    PGC->DoStereo = 1;
    PGC->EdgeMask = 11;
    PGC->EdgeCorrelation = 1;
    PGC->PGDebug = 0;
    
    PGC->UniquenessValidation = 0;
    PGC->UniquenessValidationThreshold = 0.8f;
    PGC->UniquenessValidationMapping = 129;
    
    PGC->TextureValidation = 0;
    PGC->TextureValidationThreshold = 110;
    PGC->TextureValidationMapping = 130;
    
    PGC->ZCapValue = 1;
    PGC->DifferenceThreshold = 10;
    PGC->DisparityThreshold = 10;
    PGC->ZBucketMin = 50;

	PGC->RectifiedDisparity = 1; // rectification disparity option
}

PTGREYAPI void PTGreyShowPropertyPage()
{
#if (DIGICLOPS_VERSION < 200 )
    digiclopsDisplayPropertyPages(digiclops);
#else
    PTGreyShowWhiteBalance();
#endif

}

PTGREYAPI void PTGreyShowWhiteBalance()
{
#if (DIGICLOPS_VERSION < 200 )
    digiclopsDisplayWhiteBalancePropPages(digiclops);
#else
    PgrGuiError pgrGuiError;
    if ( cameraControlContext == NULL )
    {
        pgrGuiError = pgrguiCreateContext( &cameraControlContext,
                                           digiclops,
                                           DIGICLOPS_CAMERA_SETTINGS_DIALOG );
        if ( pgrGuiError != PGRGUI_ok )
        {
            SetErrorMessage( "Create Camera Control Context failed : %d",
                             pgrGuiError );
            pgrguiDestroyContext( cameraControlContext );
            cameraControlContext = NULL;
            return;
        }
    }

    // check window state
    BOOL bShowing;
    pgrguiGetWindowState( cameraControlContext, &bShowing );
    if ( bShowing )
    {
        // already showing, so lets pop it down
        pgrguiHideModeless( cameraControlContext );
    }
    else
    {
        pgrguiShowModeless( cameraControlContext, NULL );
    }
#endif
}

PTGREYAPI void PTGreySetTriclopsInputBuffer(int frames_count)
{
    PTGreyFreezeData(INFINITE);
    PTFrameCount = frames_count;
    PTFreeFrameCount = PTPrevFrameCount;
    PTFrameNumber = 0; /* Start grabbing frames */
    PTGreyUnFreezeData();
}

PTGREYAPI int PTGreyGetFrameNumber()
{
    return PTFrameCount ? PTFrameNumber : -1;
}

void copyTriclopsInput(TriclopsInput tInput, TriclopsInput* tOutput)
{
    memcpy(tOutput, &tInput, sizeof(TriclopsInput));
    if(tInput.inputType == TriInp_RGB_32BIT_PACKED)
    {
        int size = tInput.nrows*tInput.ncols*4;
        tOutput->u.rgb32BitPacked.data = malloc(size);
        memcpy(tOutput->u.rgb32BitPacked.data, tInput.u.rgb32BitPacked.data, size);
    }
    else
    {
        int size = tInput.nrows*tInput.ncols;
        tOutput->u.rgb.red = malloc(size);
        tOutput->u.rgb.green = malloc(size);
        tOutput->u.rgb.blue = malloc(size);
        memcpy(tOutput->u.rgb.red, tInput.u.rgb.red, size);
        memcpy(tOutput->u.rgb.green, tInput.u.rgb.green, size);
        memcpy(tOutput->u.rgb.blue, tInput.u.rgb.blue, size);
    }
}

PTGREYAPI void* PTGreyGetTriclopsBuffer()
{
    return TriclopsBuffer;
}

PTGREYAPI void PTGreyProcessFrames(void* _buffer, int grabCount, const char* dirName)
{
    TriclopsInput* buffer = (TriclopsInput*)_buffer;
	// write the data to a file
	for (int i = 0; i < grabCount; i++) 
	{
	    char filename[_MAX_PATH];
//        TriclopsInput triclopsTopInput = buffer[4*i];
//		TriclopsInput triclopsLeftInput = buffer[4*i + 1];
            TriclopsInput triclopsRightInput = buffer[4*i + 2];
            TriclopsInput triclopsStereoInput = buffer[4*i+3];
            
            // preprocessing the images
            triclopsPreprocess( tcontext, &triclopsStereoInput ) ;
            
            // stereo processing
            triclopsStereo( tcontext ) ;
            
            // rectify right color image
            sprintf(filename,"%sright_color_rect_%05d.ppm",dirName,i);
            printf("writing  image %s\n",filename);
            TriclopsColorImage colorImage;
#if ( DIGICLOPS_VERSION < 200 )
            triclopsRectifyColorImage( tcontext, &triclopsRightInput, &colorImage ) ;
#else
            triclopsRectifyColorImage( tcontext, TriCam_REFERENCE, &triclopsRightInput, &colorImage ) ;
#endif
            triclopsSaveColorImage(&colorImage, filename);
            
            
            // retrieve the interpolated depth image from the tcontext
            TriclopsImage16 depthImage16;
            triclopsGetImage16( tcontext, TriImg16_DISPARITY, TriCam_REFERENCE, &depthImage16 ) ;

        if (PGS->BackGroundAvailable) 
        {
			for(int i = 0; i < PGC->DRows*PGC->DCols; i++) 
            {
				if (depthImage16.data[i] < 0xff00) 
                {	
                    unsigned char* bkg = (unsigned char*)PGS->DataBuffers[PT_BACKGROUND_IMAGE];
                    // if the point is valid
					if ((depthImage16.data[i] >> 8) < PGC->DisparityThreshold ||
                        (abs(tImage16.data[i] - bkg[i]) >> 8) < PGC->DifferenceThreshold)
                    {
                        // Make the pixel invalid...
						depthImage16.data[i] = 0xff00;
					}
				}
			}
        }

//		sprintf(filename, "%sdisparity_%05d.bmp", dirName, i);
//		WriteDisparityFile(&depthImage16, filename);

		sprintf(filename,"%spoints_%05d.txt",dirName,i);
		printf("writing  point file %s\n",filename);
		WritePointFile(&depthImage16,filename);

		sprintf(filename,"%scolor_points_%05d.txt",dirName,i);
		printf("writing  point file %s\n",filename);
		WriteColorPointFile(&depthImage16,&colorImage,filename);
	}
}

void WriteDisparityFile(TriclopsImage16* depthImage16, const char* filename)
{
	int w = depthImage16->ncols;
	int h = depthImage16->nrows;
	// Prepare IplImage header
	IplImage* image = cvCreateImage(cvSize(w, h), IPL_DEPTH_8U, 1);
	for(int j = 0; j < h; j++)
	{
		for(int i = 0; i < w; i++)
		{
			int index = j*w + i;
			int disparity = depthImage16->data[j*w + i];
			disparity = disparity < 0xff00 ? disparity >> 8 : PGC->MinDisparity;
			image->imageData[j*image->widthStep + i] = char(disparity);
		}
	}

	save_iplimage(filename, image);
}


void WritePointFile(TriclopsImage16 *image, char *filename)
{
    int                 i,j;
	int					disparity;
    float               x, y, z;
	FILE *				filestream;
	
	filestream = fopen(filename,"w"); 
	FILE* f = fopen("disparity.txt", "w");
	assert(filestream);
	
	int pointCount = PGC->nrows*PGC->ncols;
	// fprintf(filestream,"%d\n",pointCount);
	
   // determine the number of pixels spacing per row
	int pixelinc    = image->rowinc/2;
	for ( i = 0; i < image->nrows; i++ )
	{
		unsigned short * row = image->data + i * pixelinc;
		for ( j = 0; j < image->ncols; j++ )
		{
			disparity = row[j];
			
			// filter invalid points
			if ( disparity < 0xFF00 )
			{
				triclopsRCD16ToXYZ( tcontext, j , i, disparity, &x, &y, &z );
				if (z > 0 && z < PGC->ZCapValue) fprintf(filestream, "%f %f %f %d %d\n",x, y, z, i, j);
//				fprintf(f, "%d ", char(disparity >> 8));
			}
			else
				fprintf(f, "%d ", char(PGC->MinDisparity));
		}
		fprintf(f, "\n");
	}
	
   	
	fclose(filestream);
	fclose(f);
}

void WriteColorPointFile(TriclopsImage16 *image, TriclopsColorImage *colorImage, char *filename)
{
    int                 i,j;
	int					disparity;
    float               x, y, z;
	int					r, g, b;
	FILE *				filestream;
	
	filestream = fopen(filename,"w"); 
	assert(filestream);
	
	int pointCount = PGC->nrows*PGC->ncols;
	// fprintf(filestream,"%d\n",pointCount);
	
	// determine the number of pixels spacing per row
	int pixelIndex = 0;
	int pixelinc    = image->rowinc/2;
	for ( i = 0; i < image->nrows; i++ )
	{
		unsigned short * row = image->data + i * pixelinc;
		for ( j = 0; j < image->ncols; j++ )
		{
			disparity = row[j];
			
			// filter invalid points
			if ( disparity < 0xFF00 )
			{
				triclopsRCD16ToXYZ( tcontext, i , j, disparity, &x, &y, &z );
				if (z > 0 && z < PGC->ZCapValue) {
					r = (int) colorImage->red[pixelIndex];
					g = (int) colorImage->green[pixelIndex];
					b = (int) colorImage->blue[pixelIndex];
					fprintf( filestream, "%d %d %f %f %f %d %d %d\n", x, y, z, r, g, b );
				}
				
			}

			// go to the next pixel
			pixelIndex++;
		}
	}
	
   	
	fclose(filestream);
}

PTGREYAPI int PTGreyGetPointCount()
{
    return PointCount;
}

PTGREYAPI void* PTGreyGetTriclopsImage16()
{
    return &tImage16;
}

PTGREYAPI __int64 PTGreyGetTime()
{
    return __int64(TriclopsIn[3].timeStamp.sec)*1000 + __int64(TriclopsIn[3].timeStamp.u_sec)/1000;
}

BOOL PTRectifyInputDisparity()
{
	
	IplImage *inputImage, *image_hsv, *img_p[2], *img_v, *image_disp,  *contour_mask;
//    IplImage *resizeImage;
	CvSeq *contour, *cont_max;
	CvPoint *big_t;
	double parameter[2];

//	unsigned char *clean;
	int i,j;
	int Ncols, Nrows;


    CvMemStorage* temp_storage = cvCreateMemStorage( 65536 ); 
    int header_size = sizeof(CvContour);

    Ncols = PGC->DCols;
	Nrows = PGC->DRows;
//	Ncols = PGC->ncols;
//	Nrows = PGC->nrows;

	inputImage = cvCreateImage(cvSize(Ncols, Nrows), IPL_DEPTH_8U, 3);

//	resizeImage = cvCreateImage(cvSize(PGC->DCols, PGC->DRows), IPL_DEPTH_8U, 3);

	char* data = inputImage->imageData;
	int step = inputImage->widthStep;

	for (i = 0; i < PGC->DRows; i++) 
	{
		for (j = 0; j < PGC->DCols; j++) 
		{
			int index = i*step + 3*j;
			int outind = i*PGC->DCols + j;

			data[index] = t24Image.red[outind];
			data[index + 1] = t24Image.green[outind];
			data[index + 2] = t24Image.blue[outind];
		}
	}


	image_hsv = iplCreateImageHeader(3, 0, IPL_DEPTH_8U, "HSV", "HSV", IPL_DATA_ORDER_PIXEL, IPL_ORIGIN_TL, IPL_ALIGN_QWORD,
									 PGC->DCols, PGC->DRows, NULL, NULL, NULL, NULL);
	printf("\n Create image_hsv header !!!");
	iplAllocateImage(image_hsv, 0, 0 ); // allocate image data

	inputImage->roi = 0;
//	resizeImage->roi = 0;

//	m_outputImage = cvCreateImage(cvSize(m_ncols, m_nrows), IPL_DEPTH_8U, 3);
//    m_outputImage->roi = 0;
	
//	iplResize(inputImage, resizeImage, Ncols, PGC->DCols, Nrows, PGC->DRows, IPL_INTER_NN);
	
	iplRGB2HSV(inputImage, image_hsv);
//	iplRGB2HSV(resizeImage, image_hsv);

	img_p[0] = cvCreateImage(cvSize(PGC->DCols, PGC->DRows), IPL_DEPTH_8U, 1);
	img_p[1] = cvCreateImage(cvSize(PGC->DCols, PGC->DRows), IPL_DEPTH_8U,1);
	img_v	 = cvCreateImage(cvSize(PGC->DCols, PGC->DRows), IPL_DEPTH_8U,1);

//	printf("\n Create img_p !!!");

	cvCvtPixToPlane(image_hsv, img_p[0], img_p[1], img_v, NULL);


	parameter[0] = (double)2;  /* size */
	parameter[1] = (double)10; /* minDisp */
	cvAdaptiveThreshold( img_p[1], img_v, (double)255, CV_STDDEV_ADAPTIVE_THRESH, CV_THRESH_BINARY, parameter); 

//	iplThreshold(img_p[1], img_p[1], 110);
	cvFindContours (/*img_p[1]*/img_v, temp_storage, &contour, header_size, 
                    CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);

//	float parameter =1.; 
//    cvApproxPoly (contour, header_size, temp_storage, &contour_a, (CvPolyApproxMethod)0, parameter );

// find the contour  with maximum disparity
    double max_disparity = 0;
	cont_max = NULL;
	contour_mask = cvCreateImage(cvSize(PGC->DCols, PGC->DRows), IPL_DEPTH_8U, 1);

	image_disp = cvCreateImageHeader(cvSize(PGC->DCols, PGC->DRows), IPL_DEPTH_8U, 1);

	cvSetImageData( image_disp, (char*) PGS->DataBuffers[PT_DISPARITY_OBJ_IMAGE], PGC->DCols );

//	image_disp1 = cvCreateImage(cvSize(PGC->DCols, PGC->DRows), IPL_DEPTH_8U, 1);
			
//	iplResize(image_disp, image_disp1, PGC->DCols, PGC->DCols, PGC->DRows, PGC->DRows, IPL_INTER_NN);
	


    while(contour!=NULL)
    {
        if( contour->total > 30) 
        {
            iplSet(contour_mask, 0/*PGC->MinDisparity*/);
			big_t = (CvPoint*)malloc(contour->total * sizeof(CvPoint));

		    cvCvtSeqToArray(contour, big_t );
			cvFillPoly (contour_mask, &big_t, &contour->total, 255, 1 /*PGC->MaxDisparity*/);
//			m_outputImage->roi->coi = 1;

			iplAnd(image_disp, contour_mask, contour_mask);
			double mean = cvMean(contour_mask);
			
			if(mean > max_disparity) 
            {
                max_disparity = mean;
				cont_max = contour;
            }
			free(big_t);
        }
        contour = contour->h_next;
    }

	iplSet(contour_mask, 0);
	big_t = (CvPoint*)malloc(cont_max->total * sizeof(CvPoint));

//	printf("\n cont_max !!! min_disp = %d max_disparity = %f cont = %d", PGC->MinDisparity, max_disparity, cont_max->total);

	cvCvtSeqToArray(cont_max, big_t );
	cvFillPoly (contour_mask, &big_t, &cont_max->total, 255, 1);

    iplSubtractS(image_disp, image_disp,PGC->MinDisparity, false);
	iplAnd(image_disp, contour_mask, image_disp);
    iplAddS(image_disp, image_disp, PGC->MinDisparity);

	free(big_t);

//	iplResize(image_disp1, image_disp,  PGC->DCols, PGC->DCols, PGC->DRows, PGC->DRows, IPL_INTER_NN);
//	printf("\n Resize !!!");

	cvReleaseImage(&img_p[0]);
	cvReleaseImage(&img_p[1]);
	cvReleaseImage(&img_v);
	iplDeallocateImage(image_hsv);
	cvReleaseImageHeader(&image_disp);
//	cvReleaseImage(&image_disp1);
	cvReleaseImage(&contour_mask);

	cvReleaseMemStorage( &temp_storage );

    return TRUE;

}

PTGREYAPI void PTGreyExitCamera(int millisec)
{
	cvReleaseImage(&temp);

//	for(int i = 0; i < PG_IMAGE_MAX; i++)
//	{
//		delete PGS->DataBuffers[i];
//	}

	PGC->PGTerminate = 1;
	WaitForSingleObject(PTGreyProcessorThread, millisec);
}

PTGREYAPI void* PTGreyGetTriclopsContext()
{
	return tcontext;
}

PTGREYAPI void PTGreySetConfigFileName(const char* config)
{
	if(config)	
	{
		config_filename = strdup(config);
	}
}
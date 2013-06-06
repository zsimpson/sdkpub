#ifndef __PG_CONTROL__
#define __PG_CONTROL__

/* the values of enum is important! */

typedef enum
{
    PT_TOP_RAW_IMAGE = 0,
    PT_LEFT_RAW_IMAGE = 1, 
    PT_RIGHT_RAW_IMAGE = 2, 
    PT_DISPARITY_IMAGE = 3, 

    PT_RECTIFIED_IMAGE = 4, 
    PT_EDGE_IMAGE = 5, 

    PT_OBJ_IMAGE = 6, /* Corresponds to the right camera */
    PT_DISPARITY_OBJ_IMAGE = 7, 

    PT_BACKGROUND_IMAGE = 8,
    PT_POINTCLOUD_IMAGE = 9, 
    PT_IMAGE_MAX = 10
} PTGreyImageType;

#define PG_IMAGE_MAX ((int)PT_IMAGE_MAX)
#define PG_RAW_IMAGE(x) ((PTGreyImageType)(((int)(x))&0x3))
#define PG_DIGICLOPS_IMAGE(x) (1<<(((int)(x))&0x3))

const static char* ImageNames[PT_IMAGE_MAX] = 
{ "Top raw image", "Left raw image", "Right raw image", 
    "Disparity", "Rectified image", "Edge image",
    "Object image", "Object disparity", "Background", 
    "Pointcloud"
};

#define PT_IMAGE_NAME(x) ImageNames[x]



// Structure needed to communicate to the companion task consuming the images.
typedef struct {
	HANDLE MyHandle;						// handle to our partner task.
	int   PGTerminate;
	int   VBTaskPresent;	// flag used to indicate that the VB code is in the driver's seat.

	int   ImageList[PG_IMAGE_MAX];		// Selected images

	int   nrows;							// Raw imput resolution
	int   ncols;
	int   DRows;						// Use the tmp values to speed up disparity computations.
	int   DCols;						// DRows and DCols are the Rows and Cols to display
	int   NewParameters;

	int   MinDisparity;
	int   MaxDisparity;

	int   TextureValidation;				// True or false
	float TextureValidationThreshold;
	int   TextureValidationMapping;

	int   UniquenessValidation;				// True or false
	float UniquenessValidationThreshold;
	int   UniquenessValidationMapping;

	int   StereoMask;
	int   SubPixelInterpolation;
	int   StrictSubPixelValidation;

	int   Rectify;
	int   LowPass;
	int   DoStereo;

	int   EdgeMask;
	int   EdgeCorrelation;
	int   PGDebug;					// Turn on debugs in the Point Grey code

	int	  Total_Memory;				// How much memory we have allocated to share.  Make sure we don't exceed this.
	float ZCapValue;				// Useful to trim uninteresting Z-Key data in the bud  
	int   DifferenceThreshold;		// Controls what values appear in the background subtraction
	int   ComputedView;				// a disparity, rectified, edge or pointcloud has been requested
	int   ShowCameraControl;		// Show the iris and brightness control (inside filter)
	int   ZBucketMin;				// a ZBucket must have more than this to qualify as meaningful.
	int	  MaxCols;					// maximum columns (so max buffer is obtained.)
	int	  MaxRows;					// maximum rows (so max buffer is obtained.)
    int   DisparityThreshold;       // if disparity < DisparityThreshold then disparity = MinDisparity
	int   RectifiedDisparity;       // disparity images rectification flag 

} PGClient;

typedef struct {
	int   Initializing;
    int   NewData[PG_IMAGE_MAX];

	char *DigiclopsBase;		// set this so other address spaces can translate databuffers above.
	char *DataBuffers[PG_IMAGE_MAX]; // Addresses of buffers for each image type
	char *OutputBuffers[PG_IMAGE_MAX]; // Addresses of buffers for each image type

	int   BackGroundAvailable;	// A background image is available.
	int   FrameCount;				// Server counts how many frames are coming over.
    long  ticks;               // Pointer to the clock value corresponding to the frame

	int   Top;						// BoundingBox for hand
	int   Left;						// BoundingBox for hand
	int   Width;						// BoundingBox for hand
	int   Height;						// BoundingBox for hand
} PGServer;

typedef struct {
	float x;
	float y;
	float z;
} xyzTuple;												

typedef struct {
	double CameraDistance;
	double CameraAzimuth;
	double CameraInclination;
	double CameraX;
	double CameraY;

	int Terminate;		// use this to terminate the OpenGL task.
	int VBTaskPresent;	// flag used to indicate that the VB code is in the driver's seat.
	int CloudCount;		// Count of xyz tuples in pointcloud after background subtraction.
	int MinCloudCount;	// Required minimum cloud count (or assume it is not an interesting point cloud.) 
	int ComputeHandRegion; // flag to indicate that the OpenGL task should compute the hand region.

	float NextLine[6];			// Expose the coordinates of the fitted line.

	float CenterX;		// This is the center of the hand in 3D
	float CenterY;
	float CenterZ;
} OpenGLData;

#endif /* __PG_CONTROL__ */
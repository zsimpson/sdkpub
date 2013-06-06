#if !defined(PTGREYAPI)
#define PTGREYAPI
#endif

PTGREYAPI BOOL PTGreyInitCamera();
PTGREYAPI long PTGreyGetDataSize(int dataType);
PTGREYAPI long PTGreyGetPixelSize(int dataType);
PTGREYAPI BOOL PTGreyGetData(int dataType, void* pData);
PTGREYAPI const char* PTGreyGetDataPointer(int dataType);
PTGREYAPI const char* PTGreyGetErrorMessage();
PTGREYAPI int PTGreyGetHeight(int dataType);
PTGREYAPI int PTGreyGetWidth(int dataType);
PTGREYAPI void PTGreySelectDataType(int dataType, int option);
PTGREYAPI int PTGreyIsNewData(int dataType);
PTGREYAPI BOOL PTGreyGetProperty(const char* name, void* buffer);
PTGREYAPI BOOL PTGreySetProperty(const char* name, void* buffer);
PTGREYAPI BOOL PTGreyFreezeData(int milliSec);
PTGREYAPI void PTGreyUnFreezeData();
PTGREYAPI void PTGreyShowPropertyPage();
PTGREYAPI void PTGreyShowWhiteBalance();
PTGREYAPI void PTGreySetTriclopsInputBuffer(int frames_count);
PTGREYAPI int PTGreyGetFrameNumber();
PTGREYAPI void* PTGreyGetTriclopsBuffer();
PTGREYAPI void PTGreyProcessFrames(void* buffer, int grabCount, const char* dirName);
PTGREYAPI int PTGreyGetPointCount();
PTGREYAPI void* PTGreyGetTriclopsContext();
PTGREYAPI void* PTGreyGetTriclopsImage16();
PTGREYAPI __int64 PTGreyGetTime();
PTGREYAPI void PTGreyExitCamera(int millisec);
PTGREYAPI void PTGreySetConfigFileName(const char* config);
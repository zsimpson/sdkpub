
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the GSL18_VC6_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// GSL18_VC6_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef GSL18_VC6_EXPORTS
#define GSL18_VC6_API __declspec(dllexport)
#else
#define GSL18_VC6_API __declspec(dllimport)
#endif

// This class is exported from the gsl18_vc6.dll
class GSL18_VC6_API CGsl18_vc6 {
public:
	CGsl18_vc6(void);
	// TODO: add your methods here.
};

extern GSL18_VC6_API int nGsl18_vc6;

GSL18_VC6_API void gsl_set_stdout(long handle);
	// Call this fn from your program so the gsl dll can spit printf debug commands out to your common zlab dos box


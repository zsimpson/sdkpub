/*M//////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                        Intel License Agreement
//                For Open Source Computer Vision Library
//
// Copyright (C) 2000, Intel Corporation, all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of Intel Corporation may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Intel Corporation or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/

//#include "windows.h"
//#include "AFXPRIV.H"

extern "C"
{
#include "highgui.h"
}


#include <streams.h>
#include <initguid.h>
#include "iProxyTrans.h"
#include "ProxyTransuids.h"
#include "iSyncFilter.h"
#include "syncfilteruids.h"
#include <windows.h>
#include <objbase.h>
#include "afxres.h"
#include "resource.h"
#include "cvcamavi.h"



#include "cvcam.h"


#include <vector>
using namespace std;

#define WM_GRAPHNOTIFY  WM_USER+13


struct _cam_properties
{
	int _enabled;
	int render;
	int window;
	void* callback;
    int rndwidth;
    int rndheight;

	_cam_properties() : _enabled(0), render(1), window(0), callback(0), rndwidth(0),
        rndheight(0) {};
};

static void* stereo_callback;

static vector<_cam_properties> cvcam_properties;

class SafeMoniker : public SafePointer<IMoniker>
{
public:
	SafeMoniker(const SafeMoniker& p) 
	{
		m_pointer = p.m_pointer;m_pointer->AddRef();
	};
	SafeMoniker(IMoniker* p) 
	{
		m_pointer = p;
	}
};

class SafeUnknown : public SafePointer<IUnknown>
{
public:
	SafeUnknown(const SafeUnknown& p) 
	{
		m_pointer = p.m_pointer;
		if(m_pointer)
		{
			m_pointer->AddRef();
		}
	};
	SafeUnknown(IUnknown* p) 
	{
		m_pointer = p;
	}
};



static IMoniker* _cvcamMon = 0;
static IBindCtx* _cvcamBCtx=0;
static SafePointer<ICreateDevEnum> _cvcamCreateDevEnum(NULL);
static SafePointer<IEnumMoniker>   _cvcamEnumMon(NULL);
static vector<SafeMoniker> _cvcamMonikers;
typedef SafePointer<IBaseFilter> SafeFilter;
static vector<SafeFilter> _cvcamSource(NULL);
//static SafePointer<IBaseFilter> _cvcamSource;
static SafePointer<IProxyTransform> _cvcamProxyTrans(NULL);
static SafePointer<ISyncFilter> _cvcamCvSync(NULL);
static SafePointer<IGraphBuilder> _cvcamGraphBuilder(NULL);
static SafePointer<IMediaControl> _cvcamMediaControl(NULL);
static SafePointer<IMediaEventEx> _cvcamMediaEventEx(NULL);
static SafePointer<IVideoWindow> _cvcamVideoWindow(NULL);
static SafePointer<IVideoWindow> _cvcamVideoWindow2(NULL);
//static SafePointer<IFilterGraph> _cvcamFilterGraph;
//typedef SafePointer<IBindCtx> SafeBindCtx;
//static vector<SafeBindCtx> _cvcamBindCtx;
static int camera_index = -1;

static cvcamAVIs theAvis;

/* Resets all the filters */
static void _cvcamReset()
{
	
    _cvcamSource.clear();
	_cvcamProxyTrans   = NULL;
    //*(&_cvcamMediaControl) = NULL;
    _cvcamMediaControl = NULL;
	//*(&(_cvcamMediaEventEx)) = NULL;
    _cvcamMediaEventEx = NULL;
	_cvcamVideoWindow  = NULL;
    _cvcamVideoWindow2 = NULL;
	_cvcamCvSync       = NULL;
    _cvcamGraphBuilder = NULL;
   
}
HINSTANCE DLLhinst;

BOOL WINAPI DllMain(
  HINSTANCE hinstDLL,  // handle to the DLL module
  DWORD fdwReason,     // reason for calling function
  LPVOID lpvReserved   // reserved
  )
{
    DLLhinst = hinstDLL;
    
    return TRUE;


}


static int _cvcamInitVideoSource(IBaseFilter** filter);

static int _cvcamInit2Cams();

static int cvcamAVISetProperty(int camera, const char* property, void* value);

static int cvcamAVIGetProperty(int camera, const char* property, void* value);

static int _cvcamNumberOfEnabled()
{
    int j = 0;
    for(uint i = 0; i < cvcam_properties.size(); i++)
			{
				if(cvcam_properties[i]._enabled)
				    j++;
            }

    return j;

}

static IPin* get_source_pin( IBaseFilter* pFilter, PIN_DIRECTION dir )
{

    ICaptureGraphBuilder2* cgb2;
    IPin*       pPin =0;

    if(FAILED(CoCreateInstance( CLSID_CaptureGraphBuilder2, NULL, 
                                CLSCTX_INPROC_SERVER, 
                      IID_ICaptureGraphBuilder2, (void **)&cgb2 )))
            
    {
        return 0;
    }

    cgb2->FindPin(pFilter, dir, &PIN_CATEGORY_CAPTURE , 
                  &MEDIATYPE_Video, FALSE, 0, &pPin);

    //hr = _cvcamGraphBuilder->Connect(pSourceOut, pProxyTransIn);

	//int render;
	//cvcamGetProperty(camera_index, CVCAM_PROP_RENDER, &render);
	//if(render)
	//			hr = _cvcamGraphBuilder->Render( pProxyTransOut );

    cgb2->Release();
    return pPin;


}
IPin* get_pin( IBaseFilter* pFilter, PIN_DIRECTION dir )
{
    IEnumPins*  pEnumPins = 0;
    IPin*       pPin = 0;

    if( pFilter )
    {
        pFilter->EnumPins( &pEnumPins );
        if( pEnumPins != 0 )
        {
            for(;;)
            {
                ULONG  cFetched = 0;
                PIN_DIRECTION pinDir = PIN_DIRECTION(-1); 
                pPin = 0;

                pEnumPins->Next( 1, &pPin, &cFetched );
                if( cFetched == 1 && pPin != 0 )
                {
                    pPin->QueryDirection( &pinDir );
                    if( pinDir == dir ) break;
                    pPin->Release();
                }
                else if(cFetched == 0)
                {
                    return 0;
                }
            }
            pEnumPins->Release();
        }
    }

    return pPin;
}


/* The function creates a video source enumerator */
static int _cvcamInitVideoSourceEnum()
{
	CoInitialize(0);

	vector<SafeUnknown>> _objects;
    
    if(FAILED(CoCreateInstance( CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,
                      IID_ICreateDevEnum, (void**)&_cvcamCreateDevEnum )) ||
                      !_cvcamCreateDevEnum.is_valid())
    {
        return -1;
    }

	return 0;
}
/* The function iterates through all video sources and returns the number of them; 
if the input argument is nonzero, returns the pointer to IBaseFilter of the source 
that was selected previously. If no source has been selected, selects the first one. 
The interface that is returned, should not be released by the user; it will be released 
automatically.*/
static int _cvcamInitVideoSource(IBaseFilter** filter)
{
	CoInitialize(0);

	int ret = _cvcamInitVideoSourceEnum();
	if(ret < 0)
		return ret;

    ASSERT(_cvcamCreateDevEnum->is_valid());
    /* Create capture device enumerator*/
    if(FAILED(_cvcamCreateDevEnum->CreateClassEnumerator( 
                CLSID_VideoInputDeviceCategory, &_cvcamEnumMon, 0)) || 
                !_cvcamEnumMon.is_valid())
    {
        return -1;
    }


	if(!_cvcamSource.size())//           [0]/*.is_valid()*/)
	{
		uint count = cvcam_properties.size();
		if(cvcam_properties.size() == 0)
		{
			/* Count the capture devices */
			unsigned long fetched = 1;
			for(count = 0; fetched != 0; count++)
			{
				_cvcamEnumMon->Next(1, &_cvcamMon, &fetched);
                if(fetched)
                {
				    _cvcamMonikers.push_back(_cvcamMon);

                    //_cvcamMon->AddRef();

                    SafePointer<IBaseFilter> pIBF;

                    _cvcamSource.push_back(pIBF);
                   // _cvcamBindCtx.push_back()
                }
			}
            count--;
			_cam_properties prop;
			cvcam_properties.assign(count, prop);
		}


		if(filter)
		{
			// find the user's camera selection
			for(uint i = 0; i < cvcam_properties.size(); i++)
			{
				if(cvcam_properties[i]._enabled)
				{
					camera_index = i;
				}
			}

			if(camera_index < 0)
			{
				/* select a video source and return a pointer to it */
				for(uint i = 0; i < count; i++)
				{
			        _cvcamMonikers[i]->BindToObject(0, 0, IID_IBaseFilter, 
                                                    (void **)filter);
					if(filter)
					{
						cvcam_properties[i]._enabled = 1;
                        //SafePointer<IBaseFilter> pfilter = *filter;
                        //pfilter->AddRef();
						//_cvcamSource.push_back( pfilter);
                        _cvcamSource[i]=*filter;
						camera_index = i;
						return count;
					}
				}
			}
			else
			{
				_cvcamMonikers[(uint)camera_index]->BindToObject(0, 0, IID_IBaseFilter,
                                                                (void **)filter);
				if(filter)
				{
                    //SafePointer<IBaseFilter> pfilter = *filter;
                    //pfilter->AddRef();
					//_cvcamSource.push_back( pfilter);
                    _cvcamSource[(uint)camera_index]=*filter;
				}
			}

			*filter = 0;
			return 0;
		}

		return count;
	}
	else
	{
		if(!filter)
			return cvcam_properties.size();

		for(uint i = 0; i < cvcam_properties.size(); i++)
		{
			if(cvcam_properties[i]._enabled)
			{
				/* Initialize the camera */
		        _cvcamMonikers[i]->BindToObject(0, 0, IID_IBaseFilter, (void **)filter);
				if(filter)
				{
					_cvcamSource[i]=*filter;
                    //_cvcamSource[0] = *filter;
					camera_index = i;
					return i;
				}
			}
		}

		/* No camera has been selected */
		*filter = 0;
		return -1;
	}
}

/* Creates a window for DS rendering */
HWND _cvcamCreateWindow()
{
	named_window("cvcam window", 0);
    return get_hwnd_byname("cvcam window");
}

/* Returns the actual number of currently available cameras */
CVCAM_API int cvcamGetCamerasCount()
{
	int n = _cvcamInitVideoSource(0);
    return (n>0)?n:0;
}

/* Summons the video format property page */
static void _cvcamSummonPinPropPage(int camera)
{
    if(!cvcam_properties[camera]._enabled)
        return;
    //Find the output pit that is connected to the next filter...
    CAUUID uuID;
    ISpecifyPropertyPages* pspp = 0;
    
    

    IBaseFilter* filter = _cvcamSource[camera].value();
    
    IPin* pPin = get_source_pin(_cvcamSource[camera].value(), PINDIR_OUTPUT);
    if(!pPin)
        pPin=get_pin(filter, PINDIR_OUTPUT);

    if(!pPin)
        return;

    pPin->QueryInterface(IID_ISpecifyPropertyPages, (void**)&pspp);
    if(!pspp)
        return;
        
    

    pspp->GetPages(&uuID);
    pspp->Release();

    /* Disconnect the pin to enable possible changes in the output format... */
	OAFilterState state = State_Stopped;
	if(_cvcamMediaControl.is_valid())
		_cvcamMediaControl->GetState(0, &state);
	if(state != State_Stopped)
		cvcamStop();


    //pPin->Disconnect();
    /*
    IBaseFilter* pFilter;
    _cvcamProxyTrans->QueryInterface(IID_IBaseFilter, (void**)&pFilter);
    IPin* pProxyPin = get_pin(pFilter, PINDIR_INPUT);
    pProxyPin->Disconnect();
    */
    OleCreatePropertyFrame(NULL, 0, 0, L"Video Source", 1, 
        (IUnknown**)&pPin, uuID.cElems, uuID.pElems,
        0, 0, NULL);
    //_cvcamGraphBuilder->Connect(pSPin, pProxyPin);
    if(state == State_Running)
        //_cvcamMediaControl->Run();
        cvcamStart();

    //pPin->AddRef(); //
}

/* Summons the video format property page */
static void _cvcamSummonFilterPropPage(int camera)
{
    if(!cvcam_properties[camera]._enabled)
        return;

    //Find the output pit that is connected to the next filter...
    CAUUID uuID;
    ISpecifyPropertyPages* pspp = 0;
    //IBaseFilter* filter =_cvcamSource[camera].value();
    //IMoniker* mon = _cvcamMonikers[camera].value();
    //_cvcamProxyTrans->QueryInterface(IID_IBaseFilter, (void**)&filter);
    //IPin* pProxyPin = get_pin(filter, PINDIR_INPUT);
    //pProxyPin->Disconnect();
    //_cvcamMonikers[0]->BindToObject(0, 0, IID_IBaseFilter, (void **)&filter);
    //IMoniker* mon = _cvcamMonikers[camera].value();
    //IMoniker* pmon;
    //_cvcamMonikers[camera]->QueryInterface(IID_IMoniker,(void**)&pmon);
    //pmon->BindToStorage(0,0,IID_IBaseFilter, (void **)&filter);
    //BindMoniker(mon,0,IID_IBaseFilter,(void **)&filter);
    //filter= _cvcamSource.value;
    /*
    IPropertyBag *pBag;
    HRESULT hr = mon->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
	if(SUCCEEDED(hr)) {
	    VARIANT var;
	    var.vt = VT_BSTR;
	    hr = pBag->Read(L"FriendlyName", &var, NULL);
        pBag->Release();
    }
    */
    //BindMoniker(mon,0,IID_IBaseFilter,(void **)&filter);
    //mon->BindToObject(0,0,IID_IBaseFilter, (void **)&filter);
    //IPin* pPin = get_source_pin(_cvcamSource[camera].value(), PINDIR_OUTPUT);
    //IPin* pPin = get_source_pin(filter, PINDIR_OUTPUT);
    //if(!pPin)
     //   pPin=get_pin(filter, PINDIR_OUTPUT);

    //if(!pPin)
     //   return;

    
    
    IBaseFilter* bf = _cvcamSource[camera].value();
//    IUnknown** ppobject = (IUnknown**)&pPin;
    bf->QueryInterface(IID_ISpecifyPropertyPages, (void**)&pspp);
    if(!pspp)
        return;
        
    

    pspp->GetPages(&uuID);
    pspp->Release();

    /* Disconnect the pin to enable possible changes in the output format... */
	OAFilterState state = State_Stopped;
	if(_cvcamMediaControl.is_valid())
		_cvcamMediaControl->GetState(0, &state);
	if(state != State_Stopped)
		cvcamStop();

/*
	IPin* pTempPin = 
	if(pPin)
*/
   // pPin->Disconnect();
    //IBaseFilter* pFilter;
    //_cvcamProxyTrans->QueryInterface(IID_IBaseFilter, (void**)&pFilter);
    //IPin* pProxyPin = get_pin(pFilter, PINDIR_INPUT);
   // pProxyPin->Disconnect();

    OleCreatePropertyFrame(NULL, 0, 0, L"Video Source", 1, 
        (IUnknown**)&bf, uuID.cElems, uuID.pElems,
        0, 0, NULL);
    //_cvcamGraphBuilder->Connect(pSPin, pProxyPin);
    if(state == State_Running)
        //_cvcamMediaControl->Run();
        cvcamStart();
}


#define CHECK_CAMERA(p) if((p) < 0 || (p) >= cvcam_properties.size()) return -1;
#define CHECK_ZERO if(!value) return -1;
#define CHECK_POSITIVE(p) if((p) < 0) return -1;

/* get/set the property of the camera. returns 0 if the property is not supported */
CVCAM_API int cvcamGetProperty(int camera, const char* property, void* value)
{
    if (camera>=AVIS_START) 
    {
        return cvcamAVIGetProperty(camera,property,value);
    }
	CHECK_CAMERA((uint)camera);
	
	if(strcmp(property, CVCAM_PROP_ENABLE) == 0)
	{
        CHECK_ZERO(value);
		*(int*)value = cvcam_properties[(uint)camera]._enabled;
		return 0;
	}
	else if(strcmp(property, CVCAM_PROP_RENDER) == 0)
	{
        CHECK_ZERO(value);
		*(int*)value = cvcam_properties[(uint)camera].render;
		return 0;
	}
	else if(strcmp(property, CVCAM_PROP_WINDOW) == 0)
	{
        CHECK_ZERO(value);
		*(int*)value = cvcam_properties[(uint)camera].window;
		return 0;
	}
	else if(strcmp(property, CVCAM_VIDEOFORMAT) == 0)
	{
		_cvcamSummonPinPropPage(camera);
        return 0;
	}
    
    else if(strcmp(property, CVCAM_CAMERAPROPS) == 0)
	{
		_cvcamSummonFilterPropPage(camera);
        return 0;
	}

    else if(strcmp(property, CVCAM_DESCRIPTION) == 0)
	{
        IPropertyBag *pBag;
        HRESULT hr = _cvcamMonikers[camera]->BindToStorage
                                (0, 0, IID_IPropertyBag, (void **)&pBag);
	    
        if(SUCCEEDED(hr)) 
        {
	        VARIANT var;
	        var.vt = VT_BSTR;
	        hr = pBag->Read(L"FriendlyName", &var, NULL);
            pBag->Release();
            char pcOut[100];
            strcpy (pcOut, "");
            int res = wcstombs(pcOut,var.bstrVal,100);
            strcpy(((CameraDescription*)value)->DeviceDescription, pcOut);
                
            VariantClear(&var);
            
            return (res>=0)-1;
        }
        else
        {
            strcpy(((CameraDescription*)value)->DeviceDescription,"");
            return -1;
 
        }//if(SUCCEEDED(hr)) 
		
	}

	return -2;
}
/////////////////////////////////////////////////////////////////////////////////////////
CVCAM_API int cvcamSetProperty(int camera, const char* property, void* value)
{
    if (camera>=AVIS_START) 
    {
        return cvcamAVISetProperty(camera,property,value);
    }
	if(strcmp(property, CVCAM_PROP_ENABLE) == 0)
	{
	    
		int val = (int)value;

        if(cvcam_properties[(uint)camera]._enabled && val)
            return -3;

		CHECK_POSITIVE(camera);
		if((uint)camera >= cvcam_properties.size()) return 0;
		cvcam_properties[(uint)camera]._enabled = val;
        if(val)
        {
            IBaseFilter* filter;
            _cvcamMonikers[camera]->BindToObject(0, 
                                                 0,
                                                 IID_IBaseFilter, 
                                                 (void **)&filter);
            if(filter)
            {
            
                _cvcamSource[camera]=filter;

            }
            else
                cvcam_properties[(uint)camera]._enabled = 0;
        }

        return 0;
	}
	else if	(strcmp(property, CVCAM_PROP_RENDER) == 0)
	{
		int val = (int)value;
		cvcam_properties[(uint)camera].render = val;
		return 0;
	}
	else if	(strcmp(property, CVCAM_PROP_WINDOW) == 0)
	{
		int val = *(int*)value;
		cvcam_properties[camera].window = val;
		return 0;
	}
	else if(strcmp(property, CVCAM_PROP_CALLBACK) == 0)
	{
		cvcam_properties[camera].callback = value;
		return 0;
	}

    else if(strcmp(property, CVCAM_STEREO_CALLBACK) == 0)
	{
	    stereo_callback = value;
		return 0;
	}

    else if	(strcmp(property, CVCAM_RNDWIDTH) == 0)
	{
		int val = *(int*)value;
        OAFilterState state = State_Stopped;
        
        if(_cvcamMediaControl.is_valid())
		    _cvcamMediaControl->GetState(0, &state);
	    if(state != State_Stopped)
		    cvcamStop();

		cvcam_properties[camera].rndwidth = val;
        
        if(state == State_Running)
            cvcamStart();
		return 0;
	}

    else if	(strcmp(property, CVCAM_RNDHEIGHT) == 0)
	{
		int val = *(int*)value;
        OAFilterState state = State_Stopped;
	    
        if(_cvcamMediaControl.is_valid())
		    _cvcamMediaControl->GetState(0, &state);
	    if(state != State_Stopped)
		    cvcamStop();
        
		cvcam_properties[camera].rndheight = val;
        if(state == State_Running)
            cvcamStart();
		return 0;
	}



	return -2;
}
/////////////////////////////////////////////////////////////////////////////////////////
/* gets all property names. the actual number of properties is returned. */
CVCAM_API int cvcamGetPropertiesList(int camera, const char** properties, int count)
{
	CHECK_CAMERA((uint)camera);
	if(count-- > 0)
	{
		properties[0] = CVCAM_PROP_ENABLE;
	}
	if(count-- > 0)
	{
		properties[1] = CVCAM_PROP_RENDER;
	}
	if(count-- > 0)
	{
		properties[2] = CVCAM_PROP_WINDOW;
	}

	return 3;
}
/////////////////////////////////////////////////////////////////////////////////////////
/* Prepares the currently enabled cameras for work */
CVCAM_API int cvcamInit()
{
    
    IBaseFilter* filter;
	vector<SafeUnknown> _objects;

	/* reset all filters */
//	_cvcamReset();

	/* Create a video source filter */
	_cvcamInitVideoSource(&filter);

	if(_cvcamNumberOfEnabled() == 2)
        return _cvcamInit2Cams();
	
    
    /* Create a proxy transform filter */
    if(FAILED(CoCreateInstance(CLSID_ProxyTransform, NULL, CLSCTX_INPROC_SERVER, 
                    IID_IProxyTransform, (void**)&_cvcamProxyTrans)))
	{
		return 0;
	}

	_cvcamProxyTrans->set_transform(
        (void(__cdecl*)(void*))cvcam_properties[camera_index].callback, 0);


	/* Create a filter graph object */
    if(FAILED(CoCreateInstance( CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, 
                      IID_IGraphBuilder, (void **)&_cvcamGraphBuilder )))
    {
        return 0;
    }

    ASSERT(!_cvcamMediaControl.is_valid());
    _cvcamGraphBuilder->QueryInterface(IID_IMediaControl,(void**)&_cvcamMediaControl);
    _cvcamGraphBuilder->QueryInterface(IID_IMediaEventEx,(void**)&_cvcamMediaEventEx);
    _cvcamGraphBuilder->QueryInterface(IID_IVideoWindow, (void**)&_cvcamVideoWindow);
//    _cvcamGraphBuilder->QueryInterface(IID_IFilterGraph, (void**)&_cvcamFilterGraph);

    IBaseFilter* pProxyTrans = 0;
    _cvcamProxyTrans->QueryInterface(IID_IBaseFilter, (void**)&pProxyTrans);
	_objects.push_back(SafeUnknown(pProxyTrans));

/*    if( m_MediaEventEx )
    {
        // Have the graph signal event via window callbacks for performance
        m_MediaEventEx->SetNotifyWindow((OAHWND)m_hWnd, WM_GRAPHNOTIFY, 0);
    }*/

    /* link all filters together*/
    if( _cvcamGraphBuilder.is_valid() )
    {
        HRESULT hr;
        hr = _cvcamGraphBuilder->AddFilter( (_cvcamSource[camera_index]).value(), 
                                            L"Video Source" );
        hr = _cvcamGraphBuilder->AddFilter( pProxyTrans, L"Script processing");

        
        IPin* pSourceOut    = get_source_pin( _cvcamSource[camera_index].value(),
                                              PINDIR_OUTPUT );
        IPin* pProxyTransIn     = get_pin( pProxyTrans, PINDIR_INPUT );
        IPin* pProxyTransOut    = get_pin( pProxyTrans, PINDIR_OUTPUT );
		_objects.push_back(SafeUnknown(pSourceOut));
		_objects.push_back(SafeUnknown(pProxyTransIn));
		_objects.push_back(SafeUnknown(pProxyTransOut));
    
        if( pSourceOut && pProxyTransIn && pProxyTransOut )
        {
            
            hr = _cvcamGraphBuilder->Connect(pSourceOut, pProxyTransIn);

			int render;
			cvcamGetProperty(camera_index, CVCAM_PROP_RENDER, &render);
			if(render)
				hr = _cvcamGraphBuilder->Render( pProxyTransOut );

        }
    }

    return 1;
}
/////////////////////////////////////////////////////////////////////////////////////////
//Makes the graph from 2 cameras and cvSync filter
static int _cvcamInit2Cams()
{
    /* Create a cvSync filter */
    if(FAILED(CoCreateInstance(CLSID_SyncFilter, NULL, CLSCTX_INPROC_SERVER, 
                    IID_ISyncFilter, (void**)&_cvcamCvSync)))
	{
		return 0;
	}

    if(stereo_callback)
        _cvcamCvSync->SetCallBack( (void(__cdecl*)(void*, void*))stereo_callback );

    /* Create a filter graph object */
    if(FAILED(CoCreateInstance( CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, 
                      IID_IGraphBuilder, (void **)&_cvcamGraphBuilder )))
    {
        _cvcamCvSync=NULL;
        return 0;
    }

    ASSERT(!_cvcamMediaControl.is_valid());
    _cvcamGraphBuilder->QueryInterface(IID_IMediaControl,(void**)&_cvcamMediaControl);
    //_cvcamGraphBuilder->QueryInterface(IID_IMediaEventEx,(void**)&_cvcamMediaEventEx);
    //_cvcamGraphBuilder->QueryInterface(IID_IVideoWindow, (void**)&_cvcamVideoWindow);
//    _cvcamGraphBuilder->QueryInterface(IID_IFilterGraph, (void**)&_cvcamFilterGraph);

    IBaseFilter* pSyncFilter = 0;
    _cvcamCvSync->QueryInterface(IID_IBaseFilter, (void**)&pSyncFilter);
    

    vector<SafeUnknown> _objects;
	_objects.push_back(SafeUnknown(pSyncFilter));

/* link all filters together*/
    if( _cvcamGraphBuilder.is_valid() )
    {
        HRESULT hr;

        

        vector<int> indexes;
        
        for(uint i = 0; i < cvcam_properties.size(); i++)
		{
			if(cvcam_properties[i]._enabled)
			{
                hr = _cvcamGraphBuilder->AddFilter( (_cvcamSource[i]).value(),
                                                    L"Video Source" );
                if(FAILED(hr)) 
                {
                    //_cvcamGraphBuilder=NULL;
                    //_cvcamCvSync=NULL;
                    return 0;
                }
                indexes.push_back(i);
            }
        }
                hr = _cvcamGraphBuilder->AddFilter( pSyncFilter, L"Script processing");
                if(FAILED(hr))
                {
                    //_cvcamGraphBuilder=NULL;
                    //_cvcamCvSync=NULL;
                    return 0;
                }

        
        IPin* pSourceOut1 = get_source_pin( _cvcamSource[indexes[0] ].value(),
                                            PINDIR_OUTPUT );
        if(!pSourceOut1)
        {
            //_cvcamGraphBuilder=NULL;
            //_cvcamCvSync=NULL;
            return 0;
        
        }
        IPin* pSourceOut2 = get_source_pin( _cvcamSource[indexes[1] ].value(),
                                            PINDIR_OUTPUT );
        if(!pSourceOut2)
        {
            //_cvcamGraphBuilder=NULL;
            //_cvcamCvSync=NULL;
            return 0;
        
        }
        

        IPin* pSyncInput1;
        IPin* pSyncInput2;
        IPin* pSyncOutput1;
        IPin* pSyncOutput2;
        pSyncFilter->FindPin(L"Input1", &pSyncInput1);
        pSyncFilter->FindPin(L"Input2", &pSyncInput2);
        pSyncFilter->FindPin(L"Output1", &pSyncOutput1);
        pSyncFilter->FindPin(L"Output2", &pSyncOutput2);

        
		
        _objects.push_back(SafeUnknown(pSourceOut1));
        _objects.push_back(SafeUnknown(pSourceOut2));
		_objects.push_back(SafeUnknown(pSyncInput1));
        _objects.push_back(SafeUnknown(pSyncInput2));
        _objects.push_back(SafeUnknown(pSyncOutput1));
        _objects.push_back(SafeUnknown(pSyncOutput2));
        
        
       
    
        if( pSourceOut1 && pSyncInput1 && pSyncOutput1 )
        {
            
            hr = _cvcamGraphBuilder->Connect(pSourceOut1, pSyncInput1);
            if(FAILED(hr)) 
            {
                //_cvcamGraphBuilder=NULL;
                //_cvcamCvSync=NULL;
                return 0;
            }
			int render;
			cvcamGetProperty(indexes[0], CVCAM_PROP_RENDER, &render);
			if(render)
				hr = _cvcamGraphBuilder->Render( pSyncOutput1 );
                if(FAILED(hr)) 
                {
                   // _cvcamGraphBuilder=NULL;
                    //_cvcamCvSync=NULL;
                    return 0;
                }
        }

        if( pSourceOut2 && pSyncInput2 && pSyncOutput2 )
        {
            
            hr = _cvcamGraphBuilder->Connect(pSourceOut2, pSyncInput2);
            if(FAILED(hr)) 
            {
                //_cvcamGraphBuilder=NULL;
                //_cvcamCvSync=NULL;
                return 0;
            }
			int render;
			cvcamGetProperty(indexes[1], CVCAM_PROP_RENDER, &render);
			
            if(render)
				hr = _cvcamGraphBuilder->Render( pSyncOutput2 );
                if(FAILED(hr)) 
                {
                    //_cvcamGraphBuilder=NULL;
                    //_cvcamCvSync=NULL;
                    return 0;
                }
        }
    
    }


    return 1;
};
/////////////////////////////////////////////////////////////////////////////////////////
int _cvcamStart2()
{
    
    vector<SafeUnknown> _objects;
    IBaseFilter* pcvSync = 0;

    vector<int> indexes;
        
        for(uint i = 0; i < cvcam_properties.size(); i++)
		{
			if(cvcam_properties[i]._enabled)
			{
                indexes.push_back(i);
            }
        }

    if(!(_cvcamCvSync.is_valid()))
        return -1;

    //We'll adjust video windows parameters. As we've possibly got 2 
    //renderers and so 2 windows, we can't get the IVideoWindow interface
    //from IGraphBuilder, so let's go directly to renderers;
    
    if(cvcam_properties[indexes[0]].render||cvcam_properties[indexes[1]].render)
    {
    
        _cvcamCvSync->QueryInterface(IID_IBaseFilter, (void**)&pcvSync);
	    _objects.push_back(SafeUnknown(pcvSync));

        IPin* output1;
        IPin* output2;

        ASSERT(pcvSync);

        pcvSync->FindPin(L"Output1", &output1);
        pcvSync->FindPin(L"Output2", &output2);

        _objects.push_back(SafeUnknown(output1));
        _objects.push_back(SafeUnknown(output2));

        ASSERT(output1&&output2);

        if( !_cvcamMediaControl.is_valid() )
	    {
            return -1;
        }//if( !_cvcamMediaControl.is_valid() )

        PIN_INFO PinInfo;
        IBaseFilter* renderer;
        IPin* pPin;

        if(cvcam_properties[indexes[0]].render)
        {

            output1->ConnectedTo(&pPin);
            if(!pPin)
                return VFW_E_NOT_CONNECTED;
            _objects.push_back(SafeUnknown(pPin));

            pPin->QueryPinInfo(&PinInfo);
            
            renderer = PinInfo.pFilter;

            _objects.push_back(SafeUnknown(renderer));


            //IVideoWindow* pVideoWindow;
            renderer->QueryInterface(IID_IVideoWindow, (void**)&_cvcamVideoWindow);

            

            HWND hWnd;
		
            cvcamGetProperty(indexes[0], CVCAM_PROP_WINDOW, &hWnd);
		    if(!hWnd)
		    {
			    hWnd = _cvcamCreateWindow();
			    cvcamSetProperty(indexes[0], CVCAM_PROP_WINDOW, &hWnd);
		    }
            
            _cvcamVideoWindow->put_Owner((OAHWND)hWnd);

            long flags;
            _cvcamVideoWindow->get_WindowStyle(&flags);
	        _cvcamVideoWindow->put_WindowStyle(flags & (~WS_CAPTION) | WS_CHILD);
	        _cvcamVideoWindow->put_MessageDrain((OAHWND)hWnd);

            // Get the rectangle dimensions and resize the client window
		    AM_MEDIA_TYPE amt;
	        pPin->ConnectionMediaType(&amt);
	        VIDEOINFOHEADER* vih = (VIDEOINFOHEADER*)amt.pbFormat;
	        if(!vih)
	        {
	            return -1;
	        }
        
            int rndheight = cvcam_properties[indexes[0]].rndheight?
            cvcam_properties[indexes[0]].rndheight:
            vih->bmiHeader.biHeight;


            int rndwidth = cvcam_properties[indexes[0]].rndwidth?
            cvcam_properties[indexes[0]].rndwidth:
            vih->bmiHeader.biWidth;
            

            _cvcamVideoWindow->SetWindowPosition( 0, 0, rndwidth, rndheight );
		    const char* name = get_name_byhwnd(hWnd);
		    resize(name, rndwidth, rndheight);

            //renderer->Release();
            //pPin->Release();
            //_cvcamVideoWindow = pVideoWindow;
            
            //pVideoWindow->Release();



        }//if(cvcam_properties[indexes[0]].render)


        if(cvcam_properties[indexes[1]].render)
        {
            output2->ConnectedTo(&pPin);
            pPin->QueryPinInfo(&PinInfo);
            
            renderer = PinInfo.pFilter;

            _objects.push_back(SafeUnknown(pPin));
            _objects.push_back(SafeUnknown(renderer));


            IVideoWindow* pVideoWindow;
            renderer->QueryInterface(IID_IVideoWindow, (void**)&pVideoWindow);

            HWND hWnd;
		
            cvcamGetProperty(indexes[1], CVCAM_PROP_WINDOW, &hWnd);
		    if(!hWnd)
		    {
			    hWnd = _cvcamCreateWindow();
			    cvcamSetProperty(indexes[1], CVCAM_PROP_WINDOW, &hWnd);
		    }
            
            pVideoWindow->put_Owner((OAHWND)hWnd);

            long flags;
            pVideoWindow->get_WindowStyle(&flags);
	        pVideoWindow->put_WindowStyle(flags & (~WS_CAPTION) | WS_CHILD);
	        pVideoWindow->put_MessageDrain((OAHWND)hWnd);

            // Get the rectangle dimensions and resize the client window
		    AM_MEDIA_TYPE amt;
	        pPin->ConnectionMediaType(&amt);
	        VIDEOINFOHEADER* vih = (VIDEOINFOHEADER*)amt.pbFormat;
	        if(!vih)
	        {
	            return -1;
	        }
        
            int rndheight = cvcam_properties[indexes[1]].rndheight?
            cvcam_properties[indexes[1]].rndheight:
            vih->bmiHeader.biHeight;


            int rndwidth = cvcam_properties[indexes[1]].rndwidth?
            cvcam_properties[indexes[1]].rndwidth:
            vih->bmiHeader.biWidth;
            

            pVideoWindow->SetWindowPosition( 0, 0, rndwidth, rndheight );
		    const char* name = get_name_byhwnd(hWnd);
		    resize(name, rndwidth, rndheight);

            
            //renderer->Release();
            //pPin->Release();

            _cvcamVideoWindow2 = pVideoWindow;
            //pVideoWindow->Release();



        }//if(cvcam_properties[indexes[0]].render)

    }//if(cvcam_properties[indexes[0]].render||cvcam_properties[indexes[1]].render)

   // MessageBox(NULL,"going run", NULL,MB_OK);
    _cvcamMediaControl->Run();
   // MessageBox(NULL,"ran", NULL,MB_OK);

    return 1;
}
/////////////////////////////////////////////////////////////////////////////////////////
/* Start the video */
CVCAM_API int cvcamStart()
{
    if(_cvcamNumberOfEnabled() == 2)
        return _cvcamStart2();

	vector<SafeUnknown> _objects;
    IBaseFilter* pProxyTrans = 0;
    _cvcamProxyTrans->QueryInterface(IID_IBaseFilter, (void**)&pProxyTrans);
	_objects.push_back(SafeUnknown(pProxyTrans));
    IPin* pProxyTransOut    = get_pin( pProxyTrans, PINDIR_OUTPUT );
	if(!pProxyTrans || !pProxyTransOut)
	{
		return -1;
	}

    if( !_cvcamMediaControl.is_valid() )
	{
		return -1;
	}

	int render;
	cvcamGetProperty(camera_index, CVCAM_PROP_RENDER, &render);
	if(render)
	{
		/* Get the window */
		HWND hWnd;
		cvcamGetProperty(camera_index, CVCAM_PROP_WINDOW, &hWnd);
		if(!hWnd)
		{
			hWnd = _cvcamCreateWindow();
			cvcamSetProperty(camera_index, CVCAM_PROP_WINDOW, &hWnd);
		}

	    HRESULT hres = _cvcamVideoWindow->put_Owner((OAHWND)hWnd);
	    long flags;
	    hres = _cvcamMediaEventEx->SetNotifyWindow((OAHWND)hWnd, WM_GRAPHNOTIFY, 0);
	    hres = _cvcamMediaEventEx->SetNotifyFlags(0x00);
	    hres = _cvcamMediaEventEx->CancelDefaultHandling(EC_COMPLETE);
	    hres = _cvcamVideoWindow->get_WindowStyle(&flags);
	    hres = _cvcamVideoWindow->put_WindowStyle(flags & (~WS_CAPTION) | WS_CHILD);
	    hres = _cvcamVideoWindow->put_MessageDrain((OAHWND)hWnd);

		// Get the rectangle dimensions and resize the client window
		AM_MEDIA_TYPE amt;
	    pProxyTransOut->ConnectionMediaType(&amt);
	    VIDEOINFOHEADER* vih = (VIDEOINFOHEADER*)amt.pbFormat;
	    if(!vih)
	    {
	        return -1;
	    }
        
        int rndheight = cvcam_properties[camera_index].rndheight?
            cvcam_properties[camera_index].rndheight:
            vih->bmiHeader.biHeight;


        int rndwidth = cvcam_properties[camera_index].rndwidth?
            cvcam_properties[camera_index].rndwidth:
            vih->bmiHeader.biWidth;
            

        _cvcamVideoWindow->SetWindowPosition( 0, 0, rndwidth, rndheight );
		const char* name = get_name_byhwnd(hWnd);
		resize(name, rndwidth, rndheight);
	}

    _cvcamMediaControl->Run();
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////
/* Stop the video */
CVCAM_API int cvcamStop()
{
    if( _cvcamMediaControl.is_valid() )
    {
        OAFilterState fs;
        _cvcamMediaControl->GetState(0,&fs);
        if(fs == State_Stopped)
            return S_OK;
        
        
        _cvcamMediaControl->StopWhenReady();
        
       

        if(_cvcamVideoWindow.is_valid() )
        {
            _cvcamVideoWindow->put_Visible(OAFALSE);
            _cvcamVideoWindow->put_Owner(NULL);
            _cvcamVideoWindow->put_MessageDrain(0);
            
        }
        
        if(_cvcamVideoWindow2.is_valid() )
        {
            _cvcamVideoWindow2->put_Visible(OAFALSE);
            _cvcamVideoWindow2->put_Owner(NULL);
            _cvcamVideoWindow2->put_MessageDrain(0);
            
        }

        
        

        
        
        
        return 0;
    }
	else
	{
		return -1;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
/* Pause the video; should be used for preventing data changes during frame reading 
	using "frame" and other properties */
CVCAM_API int cvcamPause()
{
    if( _cvcamMediaControl.is_valid() )
    {
        OAFilterState fs;
        _cvcamMediaControl->GetState(0,&fs);
        if(fs == State_Stopped)
            return S_OK;
        _cvcamMediaControl->Pause();
	}	
	
	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////
/* Resume the video */
CVCAM_API int cvcamResume()
{
    if( _cvcamMediaControl.is_valid() )
    {
        OAFilterState fs;
        _cvcamMediaControl->GetState(0,&fs);
        if(fs == State_Stopped)
            return S_OK;
        
        _cvcamMediaControl->Run();
	}

	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////
/* Frees all resources */
CVCAM_API int cvcamExit()
{
	_cvcamSource.clear();
	_cvcamReset();
    _cvcamCreateDevEnum = 0;
	_cvcamEnumMon = 0;
	_cvcamMonikers.clear();
    cvcam_properties.clear();

	

	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////

CVCAM_API int cvcamBuildStereo()
{
	return -1;
}
/////////////////////////////////////////////////////////////////////////////////////////
/*Procedure for camera selection dialog*/
BOOL CALLBACK SelectionDlgProc(HWND hwndDlg, UINT message,
		WPARAM wParam, LPARAM lParam) 
{
    switch (message) 
	{
        case WM_INITDIALOG:
        {
            int n = cvcamGetCamerasCount();
            CameraDescription descr;
            HWND cbwnd = GetDlgItem(hwndDlg,IDC_COMBO1);

            

            for(int k = 0; k < n; k++)
            {
                cvcamGetProperty(k, CVCAM_DESCRIPTION, (void*)&descr);
                SendMessage(cbwnd,CB_ADDSTRING ,0,(LPARAM) descr.DeviceDescription);

            
            }

            return FALSE;
        }//case WM_INITDIALOG:

        case WM_COMMAND: 
        {
            switch(LOWORD(wParam))
            {
                case IDOK:
                {
                    
                    //get 1-st combo selection
                    int firstcmb = 
                        SendDlgItemMessage(hwndDlg, IDC_COMBO1,CB_GETCURSEL,0,0);
                    
                    if(firstcmb == -1)//nothing selected
                    {
                        EndDialog(hwndDlg, 0);
                        DestroyWindow(hwndDlg);
			            return TRUE;
                    
                    }//if(firstcmb == -1)
                    
                    //get 2-nd combo selection

                    HWND checkwnd = GetDlgItem(hwndDlg,IDC_CHECK1);
                    long ischecked = SendMessage(checkwnd,BM_GETCHECK,0,0);
                    int secondcmb;
                    if(ischecked == BST_CHECKED)
                    {
                        secondcmb =
                        SendDlgItemMessage(hwndDlg, IDC_COMBO2,CB_GETCURSEL,0,0);
                        
                        //consider we've deleted the 1-st combo selection
                        //from the second one's list
                        if(secondcmb>=firstcmb) secondcmb++;
                    
                    }//if (ischecked == BST_CHECKED)
                    else
                        secondcmb = -1;

                    //remember windows
                    vector<HWND> wnd;
                    for(int i = 0; i< cvcamGetCamerasCount(); i++)
                    {
                        HWND wnd1;
                        cvcamGetProperty(i, CVCAM_PROP_WINDOW, (void*)&wnd1);
                        wnd.push_back(wnd1);
                    }
                    
                    //reset cvcam
                    cvcamStop();
                    cvcamExit();
                    cvcamGetCamerasCount();

                    //apply settings
                    cvcamSetProperty(firstcmb,CVCAM_PROP_ENABLE, (void*)CVCAMTRUE);
                    cvcamSetProperty(firstcmb,CVCAM_PROP_RENDER, (void*)CVCAMTRUE);
                    

                    if(secondcmb!=-1)
                    {
                        cvcamSetProperty(secondcmb,CVCAM_PROP_ENABLE, (void*)CVCAMTRUE);
                        cvcamSetProperty(secondcmb,CVCAM_PROP_RENDER, (void*)CVCAMTRUE);
                        
                               
                    }

                    for(int j = 0; j< cvcamGetCamerasCount(); j++)
                    cvcamSetProperty(j, CVCAM_PROP_WINDOW, (void*)&(wnd[j]));

                    //init cvcam
                    if(!cvcamInit() )
                    {
                        MessageBox(0,"bad camera(s) or other error","cvcam error",
                                    MB_OK|MB_ICONERROR);
                        
                        return FALSE;
                    
                    }

                    //making the return value. HIWORD is 
                    //number of cams selected(1 or 2).
                    //HIBYTE of LOWORD is 1-st cam index
                    //LOBYTE of LOWORD is 2-nd cam index

                    int ncams = (secondcmb==-1)?1:2;
                    int result = MAKELONG(MAKEWORD(secondcmb,firstcmb),ncams);

                    EndDialog(hwndDlg, result);
                    //DestroyWindow(hwndDlg);
			        return TRUE;    
                    
                }

                case IDCANCEL:
                {
                    EndDialog(hwndDlg, 0);
                    //DestroyWindow(hwndDlg);
			        return TRUE;
                
                
                }

                case IDC_CHECK1://do we want a second camera?
                {
                    HWND checkwnd = GetDlgItem(hwndDlg,IDC_CHECK1);
                    long ischecked = SendMessage(checkwnd,BM_GETCHECK,0,0);

                    HWND secondcombo = GetDlgItem(hwndDlg, IDC_COMBO2);

                    if(ischecked == BST_CHECKED) //we do
                    {
                        EnableWindow(secondcombo,TRUE);
                        
                        //fill the second combo
                        int n = cvcamGetCamerasCount();
                        CameraDescription descr;
                        HWND cbwnd = GetDlgItem(hwndDlg,IDC_COMBO2);

                        SendMessage(cbwnd,CB_RESETCONTENT ,0,0);
                          
            
                        for(int k = 0; k < n; k++)
                        {
                            cvcamGetProperty(k, CVCAM_DESCRIPTION, (void*)&descr);
                            SendMessage(cbwnd,CB_ADDSTRING ,0,
                                        (LPARAM) descr.DeviceDescription);

            
                        }

                        //remove item selected in a first combo
                        int selected = SendDlgItemMessage(hwndDlg, IDC_COMBO1,
                                                          CB_GETCURSEL,0,0);
                        SendMessage(cbwnd,CB_DELETESTRING ,(WPARAM)selected,0);                    
                    
                    }
                    else if(ischecked == BST_UNCHECKED)
                        EnableWindow(secondcombo,FALSE);

                    return FALSE;


                
                
                }//case IDC_CHECK1:

                case IDC_COMBO1:
                {
                    if(HIWORD(wParam)==CBN_SELCHANGE)
                    {
                        //reset the second combo
                        int n = cvcamGetCamerasCount();
                        CameraDescription descr;
                        HWND cbwnd = GetDlgItem(hwndDlg,IDC_COMBO2);

                        SendMessage(cbwnd,CB_RESETCONTENT ,0,0);
                          
            
                        for(int k = 0; k < n; k++)
                        {
                            cvcamGetProperty(k, CVCAM_DESCRIPTION, (void*)&descr);
                            SendMessage(cbwnd,CB_ADDSTRING ,0,
                                        (LPARAM) descr.DeviceDescription);

            
                        }

                        //remove item selected in a first combo
                        int selected = SendDlgItemMessage(hwndDlg, IDC_COMBO1,
                                                          CB_GETCURSEL,0,0);
                        SendMessage(cbwnd,CB_DELETESTRING ,(WPARAM)selected,0); 

                    
                    
                    
                    }//if(HIWORD(wParam)==CBN_SELCHANGE)

                    return FALSE;
                
                
                }//case IDC_COMBO1:
            
            
            
            
            
            
            }
        
        }//case WM_COMMAND:
    
    }//switch (message)

    return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////


/*Pops up a camera(s) selection dialog
Return value - number of cameras selected (0,1 or 2);
Argument(out): an array of selected cameras numbers
NULL if none selected. Should be released with free() when not needed.
if NULL passed, not used.
*/
int cvcamSelectCamera(int** out)  
{
    
      
    DWORD result = DialogBox( DLLhinst, MAKEINTRESOURCE(IDD_DIALOGBAR), 0,
                              SelectionDlgProc );

        
    
    if((out) && (HIWORD(result)))
    {
        *out = (int*)malloc(HIWORD(result)*sizeof(int));

        (*out)[0] = (int)HIBYTE(LOWORD(result));

        if(HIWORD(result) == 2)
            (*out)[1] = (int)LOBYTE(LOWORD(result));
    
    }//if((*out) && (HIWORD(result)))

    return HIWORD(result);
    
}
/////////////////////////////////////////////////////////////////////////////////////////
/*Plays a specified avi file into a specified window
if file is NULL, file browser is opened. if window is 0,
it is created. width and height mean output size's 0 means
those of avi file are used. __cdecl (*callback)(IplImage*) would be
called on every frame. NULL means no callback*/
CVCAM_API int cvcamPlayAVI(const char* file, 
                           void* window, 
                           int width, 
                           int height,
                           void* callback)
{
    //Get the file
    char path[256];
    memset(path,0,256);
    if(!file)
    {
        OPENFILENAME fn;
        fn.lStructSize = sizeof(OPENFILENAME);
        fn.hwndOwner = NULL;
        fn.lpstrFilter = NULL;
        fn.lpstrFile = path;
        fn.nMaxFile = 256;
        fn.lpstrFileTitle = NULL;
        fn.lpstrInitialDir = NULL;
        fn.lpstrTitle = NULL;
        fn.Flags = NULL;
        fn.lpstrDefExt = "avi";
        fn.hInstance = DLLhinst;
        fn.lpfnHook = NULL;
        fn.lpstrCustomFilter = NULL;
        fn.lCustData = NULL;


        if(!GetOpenFileName(&fn))
            return -1;
        
    
    }//if(!file)
    else
        strcpy(path,file);

    /* Get the window */
    HWND hWnd = *(HWND*)window;
		
	if(!hWnd)
    {
		hWnd = _cvcamCreateWindow();
    }
	

    SafePointer<IGraphBuilder> pGraph;
    SafePointer<IMediaControl> pMediaControl;
    SafePointer<IMediaEventEx>   pEvent;
    SafePointer<IVideoWindow>  pVideoWindow;
    SafePointer<IPin> pPin;
    SafePointer<IBasicVideo> pBasicVideo;
    SafePointer<IBaseFilter> pSFilter;
    SafePointer<IProxyTransform> pProxyTrans;
    SafePointer<IPin> pSourceOut, pProxyIn, pProxyOut;
    SafePointer<IEnumPins> pEnumPins;
    SafePointer<IBaseFilter> pProxyBase;
    
    //Initialise COM
    cvcamUseCom Iusecom;

    // Create the filter graph manager and query for interfaces.
    CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, 
                        IID_IGraphBuilder, (void **)&pGraph);

    // Build the graph.
    wchar_t wpath[256];
    mbstowcs(wpath, path, strlen(path)+1);

    
    HRESULT hres = pGraph->AddSourceFilter(wpath,L"source",&pSFilter);
    if(FAILED(hres))
        return -1;

    // Create a proxy transform filter 
    if(FAILED(CoCreateInstance(CLSID_ProxyTransform, NULL, CLSCTX_INPROC_SERVER, 
                    IID_IProxyTransform, (void**)&pProxyTrans)))
	{
		return -1;
	}

	//set callback
    pProxyTrans->set_transform((void(__cdecl*)(void*))callback, 0);

    //Get Source output pin
    pSFilter->EnumPins(&pEnumPins);

    unsigned long fetched(0);
    pEnumPins->Next(1,&pSourceOut,&fetched);
    if(!fetched)
        return -1;

    pEnumPins = NULL;
    
    //Put ProxyTrans into graph
    pProxyTrans->QueryInterface(IID_IBaseFilter,(void**)&pProxyBase);
    pGraph->AddFilter(pProxyBase.value(),L"proxy");
    
    //Get ProxyTrans Pins
    pProxyIn = get_pin( pProxyBase.value(), PINDIR_INPUT );
    pProxyOut= get_pin( pProxyBase.value(), PINDIR_OUTPUT );

    hres = pGraph->Connect(pSourceOut.value(),pProxyIn.value());
    if(FAILED(hres))
        return -1;
    hres = pGraph->Render(pProxyOut.value());
    if(FAILED(hres))
        return -1;


    
    //Gain additional interfaces
    pGraph->QueryInterface(IID_IMediaControl, (void **)&pMediaControl);
    pGraph->QueryInterface(IID_IMediaEventEx, (void **)&pEvent);
    pGraph->QueryInterface(IID_IVideoWindow, (void **)&pVideoWindow);

    if(!pMediaControl.is_valid() ||!pEvent.is_valid() ||!pVideoWindow.is_valid())
        return -1;

    //Set up the window
    hres = pVideoWindow->put_Owner((OAHWND)hWnd);
	long flags;
	hres = pEvent->SetNotifyWindow((OAHWND)hWnd, WM_GRAPHNOTIFY, 0);
	hres = pEvent->SetNotifyFlags(0x00);
	hres = pEvent->CancelDefaultHandling(EC_COMPLETE);
	hres = pVideoWindow->get_WindowStyle(&flags);
	hres = pVideoWindow->put_WindowStyle(flags & (~WS_CAPTION) | WS_CHILD);
	hres = pVideoWindow->put_MessageDrain((OAHWND)hWnd);

    // Get the rectangle dimensions and resize the client window
	hres = pGraph->QueryInterface(IID_IBasicVideo,(void**)&pBasicVideo);
    if(SUCCEEDED(hres))
    {
        long left, top, w, h;
        pBasicVideo->GetSourcePosition(&left, &top,&w,&h);
        pBasicVideo->SetDestinationPosition(0, 0, width?width:w, height?height:h);
        pVideoWindow->SetWindowPosition(0,0,width?width:w,height?height:h);
        const char* name = get_name_byhwnd(hWnd);
		resize(name, width?width:w, height?height:h);
   
    }//if(SUCCEEDED(hres))
    
    
    // Run the graph.
    pMediaControl->Run();

    // Wait for completion. 
    long evCode;
    pEvent->WaitForCompletion(INFINITE, &evCode);

    if(pVideoWindow.is_valid() )
    {
        pVideoWindow->put_Visible(OAFALSE);
        pVideoWindow->put_Owner(NULL);
        pVideoWindow->put_MessageDrain(0);
            
    }
    
    
    
    return 0;
} 

/////////////////////////////////////////////////////////////////////////////////////////
cvcamAVIFILE cvcamAVIOpenFile (char* file)
{
    return theAvis.AddSource(file, NULL);
}
/////////////////////////////////////////////////////////////////////////////////////////
int cvcamAVICloseFile (cvcamAVIFILE file)
{
    return theAvis.ReleaseSource(file);
}
/////////////////////////////////////////////////////////////////////////////////////////
int cvcamAVISetWindow (cvcamAVIFILE file, void* window)
{
    return theAvis[file]->SetWindow(*(HWND*)window);
}
/////////////////////////////////////////////////////////////////////////////////////////
int cvcamAVISetCallback (cvcamAVIFILE file, void* callback)
{
    return theAvis[file]->SetCallBack((void (__cdecl *)(void *))callback);
}
/////////////////////////////////////////////////////////////////////////////////////////
int cvcamAVISetSize (cvcamAVIFILE file, int width, int height)
{
    if(width >= 0)
        theAvis[file]->SetWidth(width);
    if(height >= 0)
        theAvis[file]->SetHeight(height);

    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////
int cvcamAVIRun (cvcamAVIFILE file)
{
    LONGLONG i = 0;
    theAvis[file]->SetPosition(&i);
    return theAvis[file]->Start();
}

int cvcamAVIStop (cvcamAVIFILE file)
{
    return theAvis[file]->Stop();
}
/////////////////////////////////////////////////////////////////////////////////////////
int cvcamAVIPause (cvcamAVIFILE file)
{
    return theAvis[file]->Pause();
}
/////////////////////////////////////////////////////////////////////////////////////////
int cvcamAVIResume (cvcamAVIFILE file)
{
    return theAvis[file]->Resume();
}
/////////////////////////////////////////////////////////////////////////////////////////
int cvcamAVIWaitCompletion (cvcamAVIFILE file)
{

    return theAvis[file]->WaitForCompletion();
}
/////////////////////////////////////////////////////////////////////////////////////////

int cvcamAVIIsRunning (cvcamAVIFILE file)
{
    return theAvis[file]->IsRunning();
}
/////////////////////////////////////////////////////////////////////////////////////////
static int cvcamAVISetProperty(int source, const char* property, void* value)
{
    if (strcmp(property,CVCAM_PROP_CALLBACK) == 0) 
    {
        return cvcamAVISetCallback(source, value);
    }
    if (strcmp(property,CVCAM_PROP_WINDOW) == 0) 
    {
        return cvcamAVISetWindow(source,value);
    }
    if (strcmp(property,CVCAM_RNDWIDTH) == 0) 
    {
        return cvcamAVISetSize(source,(int)value,-1);
        
    }
    if (strcmp(property,CVCAM_RNDHEIGHT) == 0) 
    {
        return cvcamAVISetSize(source,-1,(int)value);
    }
    if (strcmp(property,CVCAM_PROP_TIME_FORMAT) == 0) 
    {
        return theAvis[source]->SetTimeFormat((int)value);
    }
    if (strcmp(property,CVCAM_PROP_POSITION) == 0) 
    {
        return theAvis[source]->SetPosition((LONGLONG*)value);
        
    }

    return -1;

}
/////////////////////////////////////////////////////////////////////////////////////////
static int cvcamAVIGetProperty(int source, const char* property, void* value)
{
    if (strcmp(property,CVCAM_PROP_DURATION) == 0) 
    {
        return theAvis[source]->GetDuration((LONGLONG*)value);
    }
    if (strcmp(property,CVCAM_PROP_POSITION) == 0) 
    {
        return theAvis[source]->GetCurrentPosition((LONGLONG*)value);
        
    }

    return -1;
}
/////////////////////////////////////////////////////////////////////////////////////////
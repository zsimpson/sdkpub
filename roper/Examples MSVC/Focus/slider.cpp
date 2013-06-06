// Slider.cpp : .cpp file with several functions
//				concerning with setting sliders in dFocus.cpp
//
///////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Focus.h"
#include "dFocus.h"
#include "slider.h"

extern "C"
{
	#define PIXCM 1
	#include "platform.h"
	#include "pigendef.h"
	#include "pigenfcn.h"
}

/////////////////////////////////////////////////////////////////////////////
//
//  SetExposSliderRange
//
/////////////////////////////////////////////////////////////////////////////

void SetExposSliderRange
	(
	int			units,
	int			*expos_factor,
	double		*Roundoff,
	int			*max_slide,
	CSliderCtrl* pSlider
	)
{
	INT line_size, page_size;

	line_size     = 1;            // Shows as .01
    page_size     = 10;           // Shows as .1
    *expos_factor = 100;
    *max_slide    = HIGH_SEC * (*expos_factor);
    *Roundoff     = .005;

    pSlider->SetLineSize( line_size );
    pSlider->SetPageSize( page_size );
    pSlider->SetRange( 0, *max_slide, FALSE );
}

/////////////////////////////////////////////////////////////////////////////
//
//  SetExposSliderPos
//
//      NOTE: This function also checks exposure limits
//            and resets the exposure value if out of range.
//
/////////////////////////////////////////////////////////////////////////////

void SetExposSliderPos
    (
    double *exposure,
    INT    expos_factor,
    double Roundoff,
    INT    max_slide,
    CSliderCtrl* pSlider        // Slider control to set
    )
{	
	max_slide = HIGH_SEC * (expos_factor);
        // Do limit checks here
    if( *exposure > (double)max_slide )
        *exposure = (double)max_slide;
    else if( *exposure < 0.0 )
        *exposure = 0.0;

    pSlider->SetPos( (INT)( ( ( *exposure ) * (double)expos_factor ) + Roundoff ) );
}

/////////////////////////////////////////////////////////////////////////////
//
//  SetOffsetSliderRange
//
/////////////////////////////////////////////////////////////////////////////

void SetOffsetSliderRange 
	(
	int			*max_slide, 
	CSliderCtrl* pSlider
	)

{
	INT line_size, page_size;

	line_size     = 1;            
    page_size     = 10;           
    *max_slide    = 99;

    pSlider->SetLineSize( line_size );
    pSlider->SetPageSize( page_size );
    pSlider->SetRange( 0, *max_slide, FALSE );
}

/////////////////////////////////////////////////////////////////////////////
//
//  SetOffsetSliderPos
//
//      NOTE: This function also checks offset limits
//            and resets the offset value if out of range.
//
/////////////////////////////////////////////////////////////////////////////

void SetOffsetSliderPos
    (
    int *offset,
    INT    max_slide,
    CSliderCtrl* pSlider        // Slider control to set
    )
{
	max_slide = 99;
        // Do limit checks here
    if( *offset > max_slide )
        *offset = max_slide;
    else if( *offset < 0 )
        *offset = 0;

    pSlider->SetPos(*offset);
}

/////////////////////////////////////////////////////////////////////////////
//
//  SetBinSliderRange
//
/////////////////////////////////////////////////////////////////////////////

void SetBinSliderRange 
	(
	int			*max_slide, 
	CSliderCtrl* pSlider
	)

{
	INT line_size, page_size;

	line_size     = 1;            
    page_size     = 1;           
    *max_slide    = 7;

    pSlider->SetLineSize( line_size );
    pSlider->SetPageSize( page_size );
    pSlider->SetRange( 0, *max_slide, FALSE );
}

/////////////////////////////////////////////////////////////////////////////
//
//  SetBinSliderPos
//
//      NOTE: This function also checks offset limits
//            and resets the bin adjust value if out of range.
//
/////////////////////////////////////////////////////////////////////////////

void SetBinSliderPos
    (
    int *bitadjust,
    INT    max_slide,
    CSliderCtrl* pSlider        // Slider control to set
    )
{
	max_slide = 7;
        // Do limit checks here
    if( *bitadjust > max_slide )
        *bitadjust = max_slide;
    else if( *bitadjust < 0 )
        *bitadjust = 0;

    pSlider->SetPos(*bitadjust);
}

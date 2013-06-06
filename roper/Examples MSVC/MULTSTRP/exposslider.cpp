// ExposSlider.cpp : .cpp file with several functions
//						concerning the exposure slider.
//
///////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Multstrp.h"
#include "dExperiment.h"
#include "exposslider.h"

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
        // Do limit checks here
    if( *exposure > (double)max_slide )
        *exposure = (double)max_slide;
    else if( *exposure < 0.0 )
        *exposure = 0.0;

    pSlider->SetPos( (INT)( ( ( *exposure ) * (double)expos_factor ) + Roundoff ) );
}


// Slider.h : header file containing general function calls 
//                 for use with the sliders.
//
///////////////////////////////////////////////////////////////////////////

#ifndef SLIDER_H
#define SLIDER_H 1

#define HIGH_SEC	10

///////////////////////////////////////////////////////////////////////////
//
//							Functions defines
//
///////////////////////////////////////////////////////////////////////////

void SetExposSliderRange( INT units, INT *expos_factor, double *Roundoff,
                          INT *max_slide, CSliderCtrl* pSlider );

void SetExposSliderPos( double *exposure, INT expos_factor, double Roundoff,
                        INT max_slide, CSliderCtrl* pSlider );

#endif
// ExposSlider.h : header file containing general function calls 
//                 for use with the exposure slider.
//
///////////////////////////////////////////////////////////////////////////

#ifndef EXPOSSLIDER_H
#define EXPOSSLIDER_H 1

#define HIGH_SEC	1000

void SetExposSliderRange( INT units, INT *expos_factor, double *Roundoff,
                          INT *max_slide, CSliderCtrl* pSlider );

void SetExposSliderPos( double *exposure, INT expos_factor, double Roundoff,
                        INT max_slide, CSliderCtrl* pSlider );


#endif

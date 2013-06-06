#ifndef INIT_H
#define INIT_H 1

///////////////////////////////////////////////////////////////////////////
//
//							Functions defines
//
///////////////////////////////////////////////////////////////////////////

void ReadDefaults(
    double *expos_param,
    int *offset_param,
    int *bit_adjust_param,
	int *control_param,
	int *detect_param,
	int *interface_param,
	int *ioadd_param,
	int *interrupt_param,
	int *adc_param,
	int *readout_param,
	int *pan_param,
	int *zoom_param,
	int *focus_param,
    int *versiontype
    );

void WriteDefaults(
    double expos,
    int offset,
    int bit_adjust,
	int controller,
	int detector,
	int interfacecard,
	int ioaddress,
	int inter,
	int adctype,
	int readoutmode,
	int pan,
	int zoom,
	int focus,
    int version
    );

#endif
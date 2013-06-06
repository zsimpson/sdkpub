#ifndef INIT_H
#define INIT_H 1

///////////////////////////////////////////////////////////////////////////
//
//							Functions defines
//
///////////////////////////////////////////////////////////////////////////

void ReadDefaults(
    double *expos_param,
	int *xstart_param,
	int *ystart_param,
	int *xend_param,
	int *yend_param,
	int *control_param,
	int *detect_param,
	int *interface_param,
	int *ioadd_param,
	int *interrupt_param,
	int *adc_param,
	int *readout_param,
    int *version_param
    );

void WriteDefaults(
    double expos,
	int xst,
	int yst,
	int xnd,
	int ynd,
	int controller,
	int detector,
	int interfacecard,
	int ioaddress,
	int interrupt,
	int adctype,
	int readoutmode,
    int version
    );

#endif

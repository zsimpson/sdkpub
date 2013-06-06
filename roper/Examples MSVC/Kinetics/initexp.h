#ifndef INIT_H
#define INIT_H 1

///////////////////////////////////////////////////////////////////////////
//
//							Functions defines
//
///////////////////////////////////////////////////////////////////////////

void ReadDefaults(
    BOOL *nvram,
    double *expos_param,
    int *trigger_param,
	int *detect_param,
	int *interface_param,
	int *ioadd_param,
	int *interrupt_param,
	int *adc_param
    );

void WriteDefaults(
    BOOL nvram,
    double expos,
    int trigger,
	int detector,
	int interfacecard,
	int ioaddress,
	int interrupt,
	int adctype
    );

#endif
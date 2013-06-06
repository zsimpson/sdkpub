#include "stdafx.h"
#include "initexp.h"


extern "C"
{
#define PIXCM 1
#include "platform.h"
#include "pikindef.h"
#include "pigendef.h"
#include "pigenfcn.h"
}
char *FileName = "kinetics.dat";
char *FileFormat = "%x %f %d %d %d %d %d %d";

void ReadDefaults(
    BOOL *nvram_param,
    double *expos_param,
    int *trigger_param,
	int *detect_param,
	int *interface_param,
	int *ioadd_param,
	int *interrupt_param,
	int *adc_param
    )
{
    FILE *ini_fptr;
    BOOL nvram;
    float expos;
    int trigger;
	int detector;
	int interfc;
	int ioadd;
	int interupt;
	int adc;

    BOOL NeedDefaults = FALSE;

    ini_fptr = fopen( FileName, "r" );

    if( ini_fptr != NULL )
    {
        if( fscanf( ini_fptr, FileFormat, &nvram, &expos, &trigger,
					&detector, &interfc, &ioadd,
					&interupt, &adc) != 8 )
            NeedDefaults = TRUE;        // Set defaults

        fclose( ini_fptr );
    }
    else
    {
        NeedDefaults = TRUE;        // Set defaults
    }


    if( NeedDefaults == TRUE )
    {
        nvram = TRUE;
        expos = (float) 0.5;
        trigger = KINETICS_NO_TRIGGER;
		detector = EEV_576x384_3ph;
		interfc = TAXI_Interface;
		ioadd = 0xA00;
		interupt = CHANNEL_11;
		adc = 1;

    }
    *nvram_param        = nvram;
    *expos_param		= (double) expos;
	*detect_param		= detector;
    *trigger_param      = trigger;
	*interface_param	= interfc;
	*ioadd_param		= ioadd;
	*interrupt_param	= interupt;
	*adc_param			= adc;

}

void WriteDefaults(
    BOOL nvram,
    double expos,
    int trigger,
	int detector,
	int interfacecard,
	int ioaddress,
	int inter,
	int adctype
    )
{
    FILE *ini_fptr;

    ini_fptr = fopen( FileName, "w" );

    if( ini_fptr != NULL )
    {
        fprintf( ini_fptr, FileFormat, nvram, expos, trigger,
				detector, interfacecard, ioaddress,
				inter, adctype );

        fclose( ini_fptr );
    }
}

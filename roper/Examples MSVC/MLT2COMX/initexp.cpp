#include "stdafx.h"
#include "initexp.h"


extern "C"
{
#define PIXCM 1
#include "platform.h"
#include "pigendef.h"
#include "pigenfcn.h"
}
char *FileName = "image.dat";
char *FileFormat = "%f %d %d %d %d %d %d %d %d";

void ReadDefaults(
    double *expos_param,
	int *control_param,
	int *detect_param,
	int *interface_param,
	int *ioadd_param,
	int *interrupt_param,
	int *adc_param,
	int *readout_param,
    int *version_param
    )
{
    FILE *ini_fptr;
    float expos;
	int controller;
	int detector;
	int interfc;
	int ioadd;
	int interupt;
	int adc;
	int readoutmode;
    int version;

    BOOL NeedDefaults = FALSE;

    ini_fptr = fopen( FileName, "r" );

    if( ini_fptr != NULL )
    {
        if( fscanf( ini_fptr, FileFormat, &expos,
					&controller, &detector, &interfc, &ioadd,
					&interupt, &adc, &readoutmode, &version) != 9 )
            NeedDefaults = TRUE;        // Set defaults

        fclose( ini_fptr );
    }
    else
    {
        NeedDefaults = TRUE;        // Set defaults
    }


    if( NeedDefaults == TRUE )
    {
        expos = (float) 0.5;
		controller = ST133;
		detector = EEV_1024x1024_CCD47_10;
		interfc = PCI_TIMER_Interface;
		ioadd = 0xA00;
		interupt = CHANNEL_11;
		adc = 1;
		readoutmode = ROM_FULL;
        version = 2;

    }

    *expos_param		= (double) expos;
	*control_param		= controller;
	*detect_param		= detector;
	*interface_param	= interfc;
	*ioadd_param		= ioadd;
	*interrupt_param	= interupt;
	*adc_param			= adc;
	*readout_param		= readoutmode;
    *version_param      = version;

}




void WriteDefaults(
    double expos,
	int controller,
	int detector,
	int interfacecard,
	int ioaddress,
	int inter,
	int adctype,
	int readoutmode,
    int version
    )
{
    FILE *ini_fptr;

    ini_fptr = fopen( FileName, "w" );

    if( ini_fptr != NULL )
    {
        fprintf( ini_fptr, FileFormat, expos,
				controller, detector, interfacecard, ioaddress,
				inter, adctype, readoutmode, version );

        fclose( ini_fptr );
    }
}

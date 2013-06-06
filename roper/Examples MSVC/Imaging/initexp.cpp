#include "stdafx.h"
#include "Imaging.h"
#include "dExSetup.h"
#include "initexp.h"

extern "C"
{
#define PIXCM 1
#include "platform.h"
#include "pigendef.h"
#include "pigenfcn.h"
}
char *FileName = "image.dat";
char *FileFormat = "%f %d %d %d %d %d %d %d %d %d %d %d %d";

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
    )
{
    FILE *ini_fptr;
    float expos;
	int xstart, ystart;
	int xend, yend;
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
        if( fscanf( ini_fptr, FileFormat, &expos, &xstart, &ystart, &xend, &yend,
					&controller, &detector, &interfc, &ioadd,
					&interupt, &adc, &readoutmode, &version) != 13 )
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
		xstart = 1;
		ystart = 1;
		xend = 576;
		yend = 384;
		controller = ST133;
		detector = EEV_576x384_3ph;
		interfc = TAXI_Interface;
		ioadd = 0xA00;
		interupt = CHANNEL_11;
		adc = 1;
		readoutmode = ROM_FRAME_TRANSFER;
        version = 2;

    }

    *expos_param		= (double) expos;
	*xstart_param		= xstart;
	*ystart_param		= ystart;
	*xend_param			= xend;
	*yend_param         = yend;	
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
	int xst,
	int yst,
	int xnd,
	int ynd,
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
        fprintf( ini_fptr, FileFormat, expos, xst, yst, xnd, ynd,
				controller, detector, interfacecard, ioaddress,
				inter, adctype, readoutmode, version );

        fclose( ini_fptr );
    }
}

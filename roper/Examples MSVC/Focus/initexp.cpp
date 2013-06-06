#include "stdafx.h"
#include "Focus.h"
#include "dFocus.h"
#include "initexp.h"

/* PI FILES */
extern "C" {
#define PIXCM 1
#include "platform.h"
#include "pigendef.h"
#include "pifcsdef.h"
}

char *FileName = "focus.dat";
char *FileFormat = "%f %d %d %d %d %d %d %d %d %d %d %d %d %d";

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
    )
{
    FILE *ini_fptr;
	float expos;
    int offset;
    int bit_adjust;
	int controller;
	int detector;
	int interfc;
	int ioadd;
	int interupt;
	int adc;
	int readoutmode;
	int pan;
	int zoom;
	int focusmode;
    int vtype;      // version type

    BOOL NeedDefaults = FALSE;

    ini_fptr = fopen( FileName, "r" );

    if( ini_fptr != NULL )
    {
        if( fscanf( ini_fptr, FileFormat, &expos, &offset, &bit_adjust,
					&controller, &detector, &interfc, &ioadd,
					&interupt, &adc, &readoutmode, &pan, &zoom,
					&focusmode, &vtype) != 14 )
            NeedDefaults = TRUE;        // Set defaults

        fclose( ini_fptr );
    }
    else
    {
        NeedDefaults = TRUE;        // Set defaults
    }


    if( NeedDefaults == TRUE )
    {
        expos = 0.5;
        offset = 0;
        bit_adjust = 0;
		controller = ST133;
		detector = EEV_576x384_3ph;
		interfc = TAXI_Interface;
		ioadd = 0xA00;
		interupt = CHANNEL_11;
		adc = 1;
		readoutmode = ROM_FRAME_TRANSFER;
		pan = PAN_CC;
		zoom = ZX1;
		focusmode = BINNING_FOCUS;
        vtype = 2;
    }

    *expos_param		= (double) expos;
    *offset_param		= offset;
    *bit_adjust_param	= bit_adjust;
	*control_param		= controller;
	*detect_param		= detector;
	*interface_param	= interfc;
	*ioadd_param		= ioadd;
	*interrupt_param	= interupt;
	*adc_param			= adc;
	*readout_param		= readoutmode;
	*pan_param			= pan;
	*zoom_param			= zoom;
	*focus_param		= focusmode;
    *versiontype        = vtype;
}

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
    )
{
    FILE *ini_fptr;

    ini_fptr = fopen( FileName, "w" );

    if( ini_fptr != NULL )
    {
        fprintf( ini_fptr, FileFormat, expos, offset, bit_adjust, 
				controller, detector, interfacecard, ioaddress,
				inter, adctype, readoutmode, pan, zoom, focus, version );

        fclose( ini_fptr );
    }
}

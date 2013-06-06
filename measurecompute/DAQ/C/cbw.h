/*************************************************************************
 *
 * Name:   CBW.H
 *
 * C/C++ Windows header for Measurement Computing Universal Library
 *
 * (c) Copyright 1996-2008, Measurement Computing Corp.
 * All rights reserved.
 *
 * This header file should be included in all C/C++ programs that will
 * call the Measurement Computing Universal Library from Windows.
 *
 *
 **************************************************************************/

#if !defined (NT_DRIVER) && !defined (WIN95_DRIVER)
#include <windows.h>
#include <time.h>
#endif


/* Current Revision Number */
#define CURRENTREVNUM      5.90

/* System error code */
#define NOERRORS           0    /* No error occurred */
#define BADBOARD           1    /* Invalid board number specified */
#define DEADDIGITALDEV     2    /* Digital I/O device is not responding  */
#define DEADCOUNTERDEV     3    /* Counter I/O device is not responding */
#define DEADDADEV          4    /* D/A is not responding */
#define DEADADDEV          5    /* A/D is not responding */
#define NOTDIGITALCONF     6    /* Specified board does not have digital I/O */
#define NOTCOUNTERCONF     7    /* Specified board does not have a counter */
#define NOTDACONF          8    /* Specified board is does not have D/A */
#define NOTADCONF          9    /* Specified board does not have A/D */
#define NOTMUXCONF         10   /* Specified board does not have thermocouple inputs */
#define BADPORTNUM         11   /* Invalid port number specified */
#define BADCOUNTERDEVNUM   12   /* Invalid counter device */
#define BADDADEVNUM        13   /* Invalid D/A device */
#define BADSAMPLEMODE      14   /* Invalid sampling mode option specified */
#define BADINT             15   /* Board configured for invalid interrupt level */
#define BADADCHAN          16   /* Invalid A/D channel Specified */
#define BADCOUNT           17   /* Invalid count specified */
#define BADCNTRCONFIG      18   /* invalid counter configuration specified */
#define BADDAVAL           19   /* Invalid D/A output value specified */
#define BADDACHAN          20   /* Invalid D/A channel specified */
#define ALREADYACTIVE      22   /* A background process is already in progress */
#define PAGEOVERRUN		   23   /* DMA transfer crossed page boundary, may have gaps in data */
#define BADRATE            24   /* Inavlid sampling rate specified */
#define COMPATMODE         25   /* Board switches set for "compatible" mode */
#define TRIGSTATE          26   /* Incorrect intial trigger state D0 must=TTL low) */
#define ADSTATUSHUNG       27   /* A/D is not responding */
#define TOOFEW             28   /* Too few samples before trigger occurred */
#define OVERRUN            29   /* Data lost due to overrun, rate too high */
#define BADRANGE           30   /* Invalid range specified */
#define NOPROGGAIN         31   /* Board does not have programmable gain */
#define BADFILENAME        32   /* Not a legal DOS filename */
#define DISKISFULL         33   /* Couldn't complete, disk is full */
#define COMPATWARN         34   /* Board is in compatible mode, so DMA will be used */
#define BADPOINTER         35   /* Invalid pointer (NULL) */
#define TOOMANYGAINS       36   /* Too many gains */
#define RATEWARNING        37   /* Rate may be too high for interrupt I/O */
#define CONVERTDMA         38   /* CONVERTDATA cannot be used with DMA I/O */
#define DTCONNECTERR       39   /* Board doesn't have DT Connect */
#define FORECONTINUOUS     40   /* CONTINUOUS can only be used with BACKGROUND */
#define BADBOARDTYPE       41   /* This function can not be used with this board */
#define WRONGDIGCONFIG     42   /* Digital I/O is configured incorrectly */
#define NOTCONFIGURABLE    43   /* Digital port is not configurable */
#define BADPORTCONFIG      44   /* Invalid port configuration specified */
#define BADFIRSTPOINT      45   /* First point argument is not valid */
#define ENDOFFILE          46   /* Attempted to read past end of file */
#define NOT8254CTR         47   /* This board does not have an 8254 counter */
#define NOT9513CTR         48   /* This board does not have a 9513 counter */
#define BADTRIGTYPE        49   /* Invalid trigger type */
#define BADTRIGVALUE       50   /* Invalid trigger value */
#define BADOPTION          52   /* Invalid option specified for this function */
#define BADPRETRIGCOUNT    53   /* Invalid pre-trigger count sepcified */
#define BADDIVIDER         55   /* Invalid fout divider value */
#define BADSOURCE          56   /* Invalid source value  */
#define BADCOMPARE         57   /* Invalid compare value */
#define BADTIMEOFDAY       58   /* Invalid time of day value */
#define BADGATEINTERVAL    59   /* Invalid gate interval value */
#define BADGATECNTRL       60   /* Invalid gate control value */
#define BADCOUNTEREDGE     61   /* Invalid counter edge value */
#define BADSPCLGATE        62   /* Invalid special gate value */
#define BADRELOAD          63   /* Invalid reload value */
#define BADRECYCLEFLAG     64   /* Invalid recycle flag value */
#define BADBCDFLAG         65   /* Invalid BCD flag value */
#define BADDIRECTION       66   /* Invalid count direction value */
#define BADOUTCONTROL      67   /* Invalid output control value */
#define BADBITNUMBER       68   /* Invalid bit number */
#define NONEENABLED        69   /* None of the counter channels are enabled */
#define BADCTRCONTROL      70   /* Element of control array not ENABLED/DISABLED */
#define BADEXPCHAN         71   /* Invalid EXP channel */
#define WRONGADRANGE       72   /* Wrong A/D range selected for cbtherm */
#define OUTOFRANGE         73   /* Temperature input is out of range */
#define BADTEMPSCALE       74   /* Invalid temperate scale */
#define BADERRCODE         75   /* Invalid error code specified */
#define NOQUEUE            76   /* Specified board does not have chan/gain queue */
#define CONTINUOUSCOUNT    77   /* CONTINUOUS can not be used with this count value */
#define UNDERRUN           78   /* D/A FIFO hit empty while doing output */
#define BADMEMMODE         79   /* Invalid memory mode specified */
#define FREQOVERRUN        80   /* Measured frequency too high for gating interval */
#define NOCJCCHAN          81   /* Board does not have CJC chan configured */
#define BADCHIPNUM         82   /* Invalid chip number used with cbC9513Init */
#define DIGNOTENABLED      83   /* Digital I/O not enabled */
#define CONVERT16BITS      84   /* CONVERT option not allowed with 16 bit A/D */
#define NOMEMBOARD         85   /* EXTMEMORY option requires memory board */
#define DTACTIVE           86   /* Memory I/O while DT Active */
#define NOTMEMCONF         87   /* Specified board is not a memory board */
#define ODDCHAN            88   /* First chan in queue can not be odd */
#define CTRNOINIT          89   /* Counter was not initialized */
#define NOT8536CTR         90   /* Specified counter is not an 8536 */
#define FREERUNNING        91   /* A/D sampling is not timed */
#define INTERRUPTED        92   /* Operation interrupted with CTRL-C */
#define NOSELECTORS        93   /* Selector could not be allocated */
#define NOBURSTMODE        94   /* Burst mode is not supported on this board */
#define NOTWINDOWSFUNC     95   /* This function not available in Windows lib */
#define NOTSIMULCONF       96   /* Not configured for simultaneous update */
#define EVENODDMISMATCH    97   /* Even channel in odd slot in the queue */
#define M1RATEWARNING      98   /* DAS16/M1 sample rate too fast */
#define NOTRS485           99   /* Board is not an RS-485 board */
#define NOTDOSFUNC        100   /* This function not avaliable in DOS */
#define RANGEMISMATCH     101   /* Unipolar and Bipolar can not be used together in A/D que */
#define CLOCKTOOSLOW      102   /* Sample rate too fast for clock jumper setting */
#define BADCALFACTORS     103   /* Cal factors were out of expected range of values */
#define BADCONFIGTYPE     104   /* Invalid configuration type information requested */
#define BADCONFIGITEM     105   /* Invalid configuration item specified */
#define NOPCMCIABOARD     106   /* Can't acces PCMCIA board */
#define NOBACKGROUND      107   /* Board does not support background I/O */
#define STRINGTOOSHORT    108   /* String passed to cbGetBoardName is to short */
#define CONVERTEXTMEM     109   /* Convert data option not allowed with external memory */
#define BADEUADD                110   /* e_ToEngUnits addition error */
#define DAS16JRRATEWARNING      111   /* use 10 MHz clock for rates > 125KHz */
#define DAS08TOOLOWRATE         112   /* DAS08 rate set too low for AInScan warning */
#define AMBIGSENSORONGP         114   /* more than one sensor type defined for EXP-GP */
#define NOSENSORTYPEONGP        115   /* no sensor type defined for EXP-GP */
#define NOCONVERSIONNEEDED      116   /* 12 bit board without chan tags - converted in ISR */
#define NOEXTCONTINUOUS         117   /* External memory cannot be used in CONTINUOUS mode */
#define INVALIDPRETRIGCONVERT   118   /* cbAConvertPretrigData was called after failure in cbAPretrig */
#define BADCTRREG               119   /* bad arg to CLoad for 9513 */
#define BADTRIGTHRESHOLD        120   /* Invalid trigger threshold specified in cbSetTrigger */
#define BADPCMSLOTREF           121   /* No PCM card in specified slot */
#define AMBIGPCMSLOTREF         122   /* More than one MCC PCM card in slot */
#define BADSENSORTYPE           123   /* Bad sensor type selected in Instacal */
#define DELBOARDNOTEXIST        124   /* tried to delete board number which doesn't exist */
#define NOBOARDNAMEFILE         125   /* board name file not found */
#define CFGFILENOTFOUND         126   /* configuration file not found */
#define NOVDDINSTALLED          127   /* CBUL.386 device driver not installed */
#define NOWINDOWSMEMORY         128   /* No Windows memory available */
#define OUTOFDOSMEMORY          129   /* ISR data struct alloc failure */
#define OBSOLETEOPTION          130   /* Obsolete option for cbGetConfig/cbSetConfig */
#define NOPCMREGKEY             131	  /* No registry entry for this PCMCIA board */
#define NOCBUL32SYS             132	  /* CBUL32.SYS device driver is not loaded */
#define NODMAMEMORY             133   /* No DMA buffer available to device driver */
#define IRQNOTAVAILABLE         134	  /* IRQ in being used by another device */	
#define NOT7266CTR              135   /* This board does not have an LS7266 counter */
#define BADQUADRATURE           136   /* Invalid quadrature specified */
#define BADCOUNTMODE            137   /* Invalid counting mode specified */
#define BADENCODING             138   /* Invalid data encoding specified */
#define BADINDEXMODE            139   /* Invalid index mode specified */
#define BADINVERTINDEX          140   /* Invalid invert index specified */
#define BADFLAGPINS             141   /* Invalid flag pins specified */
#define NOCTRSTATUS             142	  /* This board does not support cbCStatus() */
#define NOGATEALLOWED           143	  /* Gating and indexing not allowed simultaneously */		     
#define NOINDEXALLOWED          144   /* Indexing not allowed in non-quadratue mode */   
#define OPENCONNECTION          145   /* Temperature input has open connection */
#define BMCONTINUOUSCOUNT       146   /* Count must be integer multiple of packetsize for recycle mode. */
#define BADCALLBACKFUNC         147   /* Invalid pointer to callback function passed as arg */
#define MBUSINUSE               148   /* MetraBus in use */
#define MBUSNOCTLR              149   /* MetraBus I/O card has no configured controller card */
#define BADEVENTTYPE            150   /* Invalid event type specified for this board. */
#define ALREADYENABLED          151	  /* An event handler has already been enabled for this event type */
#define BADEVENTSIZE            152   /* Invalid event count specified. */
#define CANTINSTALLEVENT        153	  /* Unable to install event handler */
#define BADBUFFERSIZE           154   /* Buffer is too small for operation */
#define BADAIMODE               155   /* Invalid analog input mode(RSE, NRSE, or DIFF) */ 
#define BADSIGNAL               156   /* Invalid signal type specified. */
#define BADCONNECTION           157   /* Invalid connection specified. */
#define BADINDEX                158   /* Invalid index specified, or reached end of internal connection list. */
#define NOCONNECTION            159   /* No connection is assigned to specified signal. */
#define BADBURSTIOCOUNT         160   /* Count cannot be greater than the FIFO size for BURSTIO mode. */
#define DEADDEV                 161   /* Device has stopped responding. Please check connections. */

#define INVALIDACCESS           163    /* Invalid access or privilege for specified operation */
#define UNAVAILABLE             164    /* Device unavailable at time of request. Please repeat operation. */
#define NOTREADY                165   /* Device is not ready to send data. Please repeat operation. */
#define BITUSEDFORALARM         169    /* The specified bit is used for alarm. */
#define PORTUSEDFORALARM        170    /* One or more bits on the specified port are used for alarm. */
#define PACEROVERRUN            171    /* Pacer overrun, external clock rate too fast. */
#define BADCHANTYPE             172    /* Invalid channel type specified. */
#define BADTRIGSENSE            173    /* Invalid trigger sensitivity specified. */
#define BADTRIGCHAN             174    /* Invalid trigger channel specified. */
#define BADTRIGLEVEL            175    /* Invalid trigger level specified. */
#define NOPRETRIGMODE           176    /* Pre-trigger mode is not supported for the specified trigger type. */
#define BADDEBOUNCETIME	        177    /* Invalid debounce time specified. */
#define BADDEBOUNCETRIGMODE     178    /* Invalid debounce trigger mode specified. */
#define BADMAPPEDCOUNTER        179    /* Invalid mapped counter specified. */
#define BADCOUNTERMODE          180    /* This function can not be used with the current mode of the specified counter. */
#define BADTCCHANMODE           181    /* Single-Ended mode can not be used for temperature input. */
#define BADFREQUENCY            182    /* Invalid frequency specified. */
#define BADEVENTPARAM           183    /* Invalid event parameter specified. */
#define NONETIFC                184		/* No interface devices were found with required PAN ID and/or RF Channel. */
#define DEADNETIFC              185		/* The interface device(s) with required PAN ID and RF Channel has failed. Please check connection. */
#define NOREMOTEACK             186		/* The remote device is not responding to commands and queries. Please check device. */
#define INPUTTIMEOUT            187		/* The device acknowledged the operation, but has not completed before the timeout. */
#define MISMATCHSETPOINTCOUNT		188		/* Number of Setpoints not equal to number of channels with setpoint flag set */
#define INVALIDSETPOINTLEVEL		189		/* Setpoint Level is outside channel range */
#define INVALIDSETPOINTOUTPUTTYPE	190		/* Setpoint Output Type is invalid*/
#define INVALIDSETPOINTOUTPUTVALUE  	191		/* Setpoint Output Value is outside channel range */
#define INVALIDSETPOINTLIMITS		192		/* Setpoint Comparison limit B greater than Limit A */
#define STRINGTOOLONG				193	/* The string entered is too long for the operation and/or device. */
#define INVALIDLOGIN					194   /* The account name and/or password entered is incorrect. */
#define SESSIONINUSE					195	/* The device session is already in use. */
#define NOEXTPOWER					196	/* External power is not connected. */
#define BADDUTYCYCLE				197 /* Invalid duty cycle specified. */
#define BADINITIALDELAY				199 /* Invalid initial delay specified */
#define NOTEDSSENSOR				1000  /* No TEDS sensor was detected on the specified channel. */
#define INVALIDTEDSSENSOR			1001  /* Connected TEDS sensor to the specified channel is not supported */
#define CALIBRATIONFAILED			1002  /* Calibration failed */
#define BITUSEDFORTERMINALCOUNTSTATUS   1003   /* The specified bit is used for terminal count stauts. */
#define PORTUSEDFORTERMINALCOUNTSTATUS  1004    /* One or more bits on the specified port are used for terminal count stauts. */
#define BADEXCITATION					1005    /* Invalid excitation specified */
#define BADBRIDGETYPE					1006    /* Invalid bridge type specified */
#define BADLOADVAL						1007    /* Invalid load value specified */
#define BADTICKSIZE						1008    /* Invalid tick size specified */


#define AIFUNCTION      1    /* Analog Input Function    */
#define AOFUNCTION      2    /* Analog Output Function   */
#define DIFUNCTION      3    /* Digital Input Function   */
#define DOFUNCTION      4    /* Digital Output Function  */
#define CTRFUNCTION     5    /* Counter Function         */
#define DAQIFUNCTION    6    /* Daq Input Function       */
#define DAQOFUNCTION	7    /* Daq Output Function      */

/* Calibration coefficient types */
#define COARSE_GAIN     0x01
#define COARSE_OFFSET   0x02
#define FINE_GAIN       0x04
#define FINE_OFFSET     0x08
#define GAIN            COARSE_GAIN
#define OFFSET          COARSE_OFFSET

/******************************************************************
;*
;*               **** ATTENTION ALL DEVELOPERS ****
;*
;* When adding error codes, first determine if these are errors
;* that can be caused by the user or if they will never happen
;* in normal operation unless there is a bug.
;*
;* Only if they are user error should you put them in the list
;* above.  In that case be sure to give them a name that means
;* something from the user's point of view - rather than from the
;* programmer.  For example NO_VDD_INSTALLED rather than
;* DEVICE_CALL_FAILED.
;*
;* Do not add any errors to the section above without getting
;* agreement by the dept. so that all user header files and header
;* files for other versions of the library can be updates together.
;*
;* If it's an internal error, then be sure to add it to the
;* correct section below.
;*
;********************************************************************/

/* Internal errors returned by 16 bit library */
#define INTERNALERR             200   /* 200-299 Internal library error  */
#define CANT_LOCK_DMA_BUF       201   /* DMA buffer could not be locked */
#define DMA_IN_USE              202   /* DMA already controlled by another VxD */
#define BAD_MEM_HANDLE          203   /* Invalid Windows memory handle */
#define NO_ENHANCED_MODE        204   /* Windows Enhance mode is not running */
#define MEMBOARDPROGERROR       211   /* Program error getting memory board source */

/* Internal errors returned by 32 bit library */
#define INTERNAL32_ERR          300   /* 300-399 32 bit library internal errors */
#define NO_MEMORY_FOR_BUFFER    301   /* 32 bit - default buffer allocation when no user buffer used with file */
#define WIN95_CANNOT_SETUP_ISR_DATA   302 /* 32 bit - failure on INIT_ISR_DATA IOCTL call */
#define WIN31_CANNOT_SETUP_ISR_DATA   303 /* 32 bit - failure on INIT_ISR_DATA IOCTL call */
#define CFG_FILE_READ_FAILURE   304   /* 32 bit - error reading board configuration file */
#define CFG_FILE_WRITE_FAILURE  305   /* 32 bit - error writing board configuration file */
#define CREATE_BOARD_FAILURE    306   /* 32 bit - failed to create board */
#define DEVELOPMENT_OPTION      307   /* 32 bit - Config Option item used in development only */
#define CFGFILE_CANT_OPEN       308   /* 32 bit - cannot open configuration file. */
#define CFGFILE_BAD_ID          309   /* 32 bit - incorrect file id. */
#define CFGFILE_BAD_REV         310   /* 32 bit - incorrect file version. */
#define CFGFILE_NOINSERT        311  /*; */
#define CFGFILE_NOREPLACE       312  /*; */
#define BIT_NOT_ZERO            313  /*; */
#define BIT_NOT_ONE             314  /*; */
#define BAD_CTRL_REG            315     /* No control register at this location. */
#define BAD_OUTP_REG            316     /* No output register at this location. */
#define BAD_RDBK_REG            317     /* No read back register at this location. */
#define NO_CTRL_REG             318     /* No control register on this board. */
#define NO_OUTP_REG             319     /* No control register on this board. */
#define NO_RDBK_REG             320     /* No control register on this board. */
#define CTRL_REG_FAIL           321     /* internal ctrl reg test failed. */
#define OUTP_REG_FAIL           322     /* internal output reg test failed. */
#define RDBK_REG_FAIL           323     /* internal read back reg test failed. */
#define FUNCTION_NOT_IMPLEMENTED 324
#define BAD_RTD_CONVERSION      325     /* Overflow in RTD calculation */
#define NO_PCI_BIOS             326     /* PCI BIOS not present in the PC */
#define BAD_PCI_INDEX           327     /* Invalid PCI board index passed to PCI BIOS */
#define NO_PCI_BOARD			328		/* Can't detact specified PCI board */
#define PCI_ASSIGN_FAILED		329		/* PCI resource assignment failed */
#define PCI_NO_ADDRESS			330     /* No PCI address returned */
#define PCI_NO_IRQ				331		/* No PCI IRQ returned */
#define CANT_INIT_ISR_INFO		332		/* IOCTL call failed on VDD_API_INIT_ISR_INFO */
#define CANT_PASS_USER_BUFFER	333		/* IOCTL call failed on VDD_API_PASS_USER_BUFFER */
#define CANT_INSTALL_INT		334		/* IOCTL call failed on VDD_API_INSTALL_INT */
#define CANT_UNINSTALL_INT		335		/* IOCTL call failed on VDD_API_UNINSTALL_INT */
#define CANT_START_DMA	        336		/* IOCTL call failed on VDD_API_START_DMA */
#define CANT_GET_STATUS         337		/* IOCTL call failed on VDD_API_GET_STATUS */
#define CANT_GET_PRINT_PORT		338		/* IOCTL call failed on VDD_API_GET_PRINT_PORT */
#define CANT_MAP_PCM_CIS		339		/* IOCTL call failed on VDD_API_MAP_PCM_CIS */
#define CANT_GET_PCM_CFG        340     /* IOCTL call failed on VDD_API_GET_PCM_CFG */
#define CANT_GET_PCM_CCSR		341		/* IOCTL call failed on VDD_API_GET_PCM_CCSR */
#define CANT_GET_PCI_INFO		342		/* IOCTL call failed on VDD_API_GET_PCI_INFO */
#define NO_USB_BOARD			343		/* Can't detect specified USB board */
#define NOMOREFILES				344		/* No more files in the directory */
#define BADFILENUMBER			345		/* Invalid file number */
#define INVALIDSTRUCTSIZE		346		/* Invalid structure size */
#define LOSSOFDATA				347		/* EOF marker not found, possible loss of data */
#define INVALIDBINARYFILE		348		/* File is not a valid MCC binary file */

/* DOS errors are remapped by adding DOS_ERR_OFFSET to them */
#define DOS_ERR_OFFSET      		500

/* These are the commonly occurring remapped DOS error codes */
#define DOSBADFUNC         501
#define DOSFILENOTFOUND    502
#define DOSPATHNOTFOUND    503
#define DOSNOHANDLES       504
#define DOSACCESSDENIED    505
#define DOSINVALIDHANDLE   506
#define DOSNOMEMORY        507
#define DOSBADDRIVE        515
#define DOSTOOMANYFILES    518
#define DOSWRITEPROTECT    519
#define DOSDRIVENOTREADY   521
#define DOSSEEKERROR       525
#define DOSWRITEFAULT      529
#define DOSREADFAULT       530
#define DOSGENERALFAULT    531

/* Windows internal error codes */
#define WIN_CANNOT_ENABLE_INT	603
#define WIN_CANNOT_DISABLE_INT	605
#define	WIN_CANT_PAGE_LOCK_BUFFER	606
#define NO_PCM_CARD			630

/* Maximum length of error string */
#define ERRSTRLEN          256

/* Maximum length of board name */
#define BOARDNAMELEN       25

/* Status values */
#define IDLE             0
#define RUNNING          1


/* Option Flags */
#define FOREGROUND       0x0000    /* Run in foreground, don't return till done */
#define BACKGROUND       0x0001    /* Run in background, return immediately */

#define SINGLEEXEC       0x0000    /* One execution */
#define CONTINUOUS       0x0002    /* Run continuously until cbstop() called */

#define TIMED            0x0000    /* Time conversions with internal clock */
#define EXTCLOCK         0x0004    /* Time conversions with external clock */

#define NOCONVERTDATA    0x0000    /* Return raw data */
#define CONVERTDATA      0x0008    /* Return converted A/D data */

#define NODTCONNECT      0x0000    /* Disable DT Connect */
#define DTCONNECT        0x0010    /* Enable DT Connect */
#define SCALEDATA        0x0010    /* Scale scan data to engineering units */

#define DEFAULTIO        0x0000    /* Use whatever makes sense for board */
#define SINGLEIO         0x0020    /* Interrupt per A/D conversion */
#define DMAIO            0x0040    /* DMA transfer */
#define BLOCKIO          0x0060    /* Interrupt per block of conversions */
#define BURSTIO         0x10000    /* Transfer upon scan completion */
#define RETRIGMODE      0x20000    /* Re-arm trigger upon acquiring trigger count samples */
#define NONSTREAMEDIO  0x040000    /* Non-streamed D/A output */
#define ADCCLOCKTRIG   0x080000    /* Output operation is triggered on ADC clock */
#define ADCCLOCK       0x100000    /* Output operation is paced by ADC clock */
#define HIGHRESRATE	   0x200000	   /* Use high resolution rate */
#define SHUNTCAL	   0x400000	   /* Enable Shunt Calibration */

#define BYTEXFER         0x0000    /* Digital IN/OUT a byte at a time */
#define WORDXFER         0x0100    /* Digital IN/OUT a word at a time */

#define INDIVIDUAL       0x0000    /* Individual D/A output */
#define SIMULTANEOUS     0x0200    /* Simultaneous D/A output */

#define FILTER           0x0000    /* Filter thermocouple inputs */
#define NOFILTER         0x0400    /* Disable filtering for thermocouple */

#define NORMMEMORY       0x0000    /* Return data to data array */
#define EXTMEMORY        0x0800    /* Send data to memory board ia DT-Connect */

#define BURSTMODE        0x1000    /* Enable burst mode */

#define NOTODINTS        0x2000    /* Disbale time-of-day interrupts */

#define EXTTRIGGER       0x4000     /* A/D is triggered externally */

#define NOCALIBRATEDATA  0x8000    /* Return uncalibrated PCM data */
#define CALIBRATEDATA    0x0000    /* Return calibrated PCM A/D data */

#define CTR16BIT		 0x0000	   /* Return 16-bit counter data */
#define CTR32BIT		 0x0100	   /* Return 32-bit counter data */
#define CTR48BIT		 0x0200	   /* Return 48-bit counter data */

#define ENABLED          1
#define DISABLED         0

#define UPDATEIMMEDIATE  0
#define UPDATEONCOMMAND  1

/* Arguments that are used in a particular function call should be set
   to NOTUSED */
#define NOTUSED          -1


/* types of error reporting */
#define DONTPRINT        0
#define PRINTWARNINGS    1
#define PRINTFATAL       2
#define PRINTALL         3

/* types of error handling */
#define DONTSTOP         0
#define STOPFATAL        1
#define STOPALL          2

/* channel types           */
#define ANALOG			 0      // Analog channel
#define DIGITAL8		 1		// 8-bit digital port
#define DIGITAL16		 2      // 16-bit digital port
#define CTR16			 3      // 16-bit counter
#define CTR32LOW		 4		// Lower 16-bits of 32-bit counter
#define CTR32HIGH		 5		// Upper 16-bits of 32-bit counter
#define CJC			 6      // CJC channel
#define TC			 7      // Thermocouple channel
#define ANALOG_SE		 8      // Analog channel, singel-ended mode
#define ANALOG_DIFF		 9      // Analog channel, Differential mode
#define SETPOINTSTATUS   	 10     // Setpoint status channel

/* channel type flags*/
#define SETPOINT_ENABLE  	0x100  // Enable setpoint detection

/* setpoint flags*/
#define SF_EQUAL_LIMITA					0x00 // Channel = LimitA value 
#define	SF_LESSTHAN_LIMITA				0x01 // Channel < LimitA value
#define SF_INSIDE_LIMITS				0x02 // Channel Inside LimitA and LimitB (LimitA < Channel < LimitB)
#define SF_GREATERTHAN_LIMITB			0x03 // Channel > LimitB
#define SF_OUTSIDE_LIMITS				0x04 // Channel Outside LimitA and LimitB (LimitA < Channel or Channel > LimitB)
#define SF_HYSTERESIS					0x05 // Use As Hysteresis
#define	SF_UPDATEON_TRUEONLY			0x00 // Latch output condition (output = output1 for duration of acquisition)
#define	SF_UPDATEON_TRUEANDFALSE		0x08 // Do not latch output condition (output = output1 when criteria met else output = output2)
 
/* Setpoint output channels */
#define SO_NONE			0 // No Output
#define SO_DIGITALPORT	1 // Output to digital Port
#define SO_FIRSTPORTC	1 // Output to first PortC
#define	SO_DAC0			2 // Output to DAC0
#define	SO_DAC1			3 // Output to DAC1
#define SO_DAC2			4 // Output to DAC2
#define SO_DAC3			5 // Output to DAC3
#define SO_TMR0			6 // Output to TMR0
#define SO_TMR1			7 // Output to TMR1

/* cbDaqSetTrigger trigger sources */
#define TRIG_IMMEDIATE       0
#define TRIG_EXTTTL			 1
#define TRIG_ANALOG_HW		 2
#define TRIG_ANALOG_SW		 3
#define TRIG_DIGPATTERN		 4
#define TRIG_COUNTER		 5
#define TRIG_SCANCOUNT		 6

/* cbDaqSetTrigger trigger sensitivities */
#define RISING_EDGE		0
#define FALLING_EDGE    1
#define ABOVE_LEVEL		2
#define BELOW_LEVEL		3
#define EQ_LEVEL		4
#define NE_LEVEL		5

/* trigger events */
#define START_EVENT		0
#define STOP_EVENT		1

/* settling time settings */
#define SETTLE_DEFAULT		0
#define SETTLE_1us		1
#define SETTLE_5us		2
#define SETTLE_10us		3
#define SETTLE_1ms		4

/* Types of digital input ports */
#define DIGITALOUT       1
#define DIGITALIN        2

/* DT Modes for cbMemSetDTMode() */
#define DTIN             0
#define DTOUT            2

#define FROMHERE        -1       /* read/write from current position */
#define GETFIRST        -2      /* Get first item in list */
#define GETNEXT         -3      /* Get next item in list */

/* Temperature scales */
#define CELSIUS          0
#define FAHRENHEIT       1
#define KELVIN           2
#define VOLTS			 4		/* special scale for DAS-TC boards */
#define NOSCALE			 5

/* Default option */
#define DEFAULTOPTION	 0x0000


/* Types of digital I/O Ports */
#define AUXPORT          1
#define FIRSTPORTA       10
#define FIRSTPORTB       11
#define FIRSTPORTCL      12
#define FIRSTPORTC		 12
#define FIRSTPORTCH      13
#define SECONDPORTA      14
#define SECONDPORTB      15
#define SECONDPORTCL     16
#define SECONDPORTCH     17
#define THIRDPORTA       18
#define THIRDPORTB       19
#define THIRDPORTCL      20
#define THIRDPORTCH      21
#define FOURTHPORTA      22
#define FOURTHPORTB      23
#define FOURTHPORTCL     24
#define FOURTHPORTCH     25
#define FIFTHPORTA       26
#define FIFTHPORTB       27
#define FIFTHPORTCL      28
#define FIFTHPORTCH      29
#define SIXTHPORTA       30
#define SIXTHPORTB       31
#define SIXTHPORTCL      32
#define SIXTHPORTCH      33
#define SEVENTHPORTA     34
#define SEVENTHPORTB     35
#define SEVENTHPORTCL    36
#define SEVENTHPORTCH    37
#define EIGHTHPORTA      38
#define EIGHTHPORTB      39
#define EIGHTHPORTCL     40
#define EIGHTHPORTCH     41

/* Selectable analog input modes */
#define RSE             0x1000      /* Referenced Single-Ended */
#define NRSE            0x2000      /* Non-Referenced Single-Ended */
#define DIFF            0x4000      /* Differential */


/* Selectable A/D Ranges codes */
#define BIP60VOLTS       20              /* -60 to 60 Volts */
#define BIP20VOLTS       15              /* -20 to +20 Volts */
#define BIP15VOLTS       21              /* -15 to +15 Volts */
#define BIP10VOLTS       1              /* -10 to +10 Volts */
#define BIP5VOLTS        0              /* -5 to +5 Volts */
#define BIP4VOLTS        16             /* -4 to + 4 Volts */
#define BIP2PT5VOLTS     2              /* -2.5 to +2.5 Volts */
#define BIP2VOLTS        14             /* -2.0 to +2.0 Volts */
#define BIP1PT25VOLTS    3              /* -1.25 to +1.25 Volts */
#define BIP1VOLTS        4              /* -1 to +1 Volts */
#define BIPPT625VOLTS    5              /* -.625 to +.625 Volts */
#define BIPPT5VOLTS      6              /* -.5 to +.5 Volts */
#define BIPPT25VOLTS     12              /* -0.25 to +0.25 Volts */
#define BIPPT2VOLTS      13              /* -0.2 to +0.2 Volts */
#define BIPPT1VOLTS      7              /* -.1 to +.1 Volts */
#define BIPPT05VOLTS     8              /* -.05 to +.05 Volts */
#define BIPPT01VOLTS     9              /* -.01 to +.01 Volts */
#define BIPPT005VOLTS    10             /* -.005 to +.005 Volts */
#define BIP1PT67VOLTS    11             /* -1.67 to +1.67 Volts */
#define BIPPT312VOLTS    17				 /* -0.312 to +0.312 Volts */
#define BIPPT156VOLTS    18				 /* -0.156 to +0.156 Volts */
#define BIPPT125VOLTS    22				 /* -0.125 to +0.125 Volts */
#define BIPPT078VOLTS    19				 /* -0.078 to +0.078 Volts */


#define UNI10VOLTS       100            /* 0 to 10 Volts*/
#define UNI5VOLTS        101            /* 0 to 5 Volts */
#define UNI4VOLTS        114            /* 0 to 4 Volts */
#define UNI2PT5VOLTS     102            /* 0 to 2.5 Volts */
#define UNI2VOLTS        103            /* 0 to 2 Volts */
#define UNI1PT67VOLTS    109            /* 0 to 1.67 Volts */
#define UNI1PT25VOLTS    104            /* 0 to 1.25 Volts */
#define UNI1VOLTS        105            /* 0 to 1 Volt */
#define UNIPT5VOLTS      110            /* 0 to .5 Volt */
#define UNIPT25VOLTS     111            /* 0 to 0.25 Volt */
#define UNIPT2VOLTS      112            /* 0 to .2 Volt */
#define UNIPT1VOLTS      106            /* 0 to .1 Volt */
#define UNIPT05VOLTS     113            /* 0 to .05 Volt */
#define UNIPT02VOLTS     108            /* 0 to .02 Volt*/
#define UNIPT01VOLTS     107            /* 0 to .01 Volt*/

#define MA4TO20          200            /* 4 to 20 ma */
#define MA2TO10          201            /* 2 to 10 ma */
#define MA1TO5           202            /* 1 to 5 ma */
#define MAPT5TO2PT5      203            /* .5 to 2.5 ma */
#define MA0TO20          204            /* 0 to 20 ma */
#define BIPPT025AMPS     205            /* -0.025 to 0.025 ma */

#define UNIPOLAR		 300
#define BIPOLAR			 301

#define BIPPT025VOLTSPERVOLT	400    /* -0.025 to +0.025 V/V */

/* Types of D/A    */
#define ADDA1     0
#define ADDA2     1

/* 8536 counter output 1 control */
#define NOTLINKED           0
#define GATECTR2            1
#define TRIGCTR2            2
#define INCTR2              3

/* 8536 trigger types */
#define  HW_START_TRIG	0
#define  HW_RETRIG      1
#define	 SW_START_TRIG	2

/* Types of 8254 counter configurations */
#define HIGHONLASTCOUNT     0
#define ONESHOT             1
#define RATEGENERATOR       2
#define SQUAREWAVE          3
#define SOFTWARESTROBE      4
#define HARDWARESTROBE      5

/* Where to reload from for 9513 counters */
#define LOADREG         0
#define LOADANDHOLDREG  1

/* Counter recycle modes for 9513 and 8536 */
#define ONETIME         0
#define RECYCLE         1

/* Direction of counting for 9513 counters */
#define COUNTDOWN       0
#define COUNTUP         1

/* Types of count detection for 9513 counters */
#define POSITIVEEDGE    0
#define NEGATIVEEDGE    1

/* Counter output control */
#define ALWAYSLOW       0       /* 9513 */
#define HIGHPULSEONTC   1       /* 9513 and 8536 */
#define TOGGLEONTC      2       /* 9513 and 8536 */
#define DISCONNECTED    4       /* 9513 */
#define LOWPULSEONTC    5       /* 9513 */
#define HIGHUNTILTC     6       /* 8536 */

/* 9513 Counter input sources */
#define TCPREVCTR       0
#define CTRINPUT1       1
#define CTRINPUT2       2
#define CTRINPUT3       3
#define CTRINPUT4       4
#define CTRINPUT5       5
#define GATE1           6
#define GATE2           7
#define GATE3           8
#define GATE4           9
#define GATE5           10
#define FREQ1           11
#define FREQ2           12
#define FREQ3           13
#define FREQ4           14
#define FREQ5           15
#define CTRINPUT6       101
#define CTRINPUT7       102
#define CTRINPUT8       103
#define CTRINPUT9       104
#define CTRINPUT10      105
#define GATE6           106
#define GATE7           107
#define GATE8           108
#define GATE9           109
#define GATE10          110
#define FREQ6           111
#define FREQ7           112
#define FREQ8           113
#define FREQ9           114
#define FREQ10          115
#define CTRINPUT11      201
#define CTRINPUT12      202
#define CTRINPUT13      203
#define CTRINPUT14      204
#define CTRINPUT15      205
#define GATE11          206
#define GATE12          207
#define GATE13          208
#define GATE14          209
#define GATE15          210
#define FREQ11          211
#define FREQ12          212
#define FREQ13          213
#define FREQ14          214
#define FREQ15          215
#define CTRINPUT16      301
#define CTRINPUT17      302
#define CTRINPUT18      303
#define CTRINPUT19      304
#define CTRINPUT20      305
#define GATE16          306
#define GATE17          307
#define GATE18          308
#define GATE19          309
#define GATE20          310
#define FREQ16          311
#define FREQ17          312
#define FREQ18          313
#define FREQ19          314
#define FREQ20          315

/* Counter load registers */
#define LOADREG0        0
#define LOADREG1        1
#define LOADREG2        2
#define LOADREG3        3
#define LOADREG4        4
#define LOADREG5        5
#define LOADREG6        6
#define LOADREG7        7
#define LOADREG8        8
#define LOADREG9        9
#define LOADREG10       10
#define LOADREG11       11
#define LOADREG12       12
#define LOADREG13       13
#define LOADREG14       14
#define LOADREG15       15
#define LOADREG16       16
#define LOADREG17       17
#define LOADREG18       18
#define LOADREG19       19
#define LOADREG20       20

/* 9513 Counter registers */
#define HOLDREG1        101
#define HOLDREG2        102
#define HOLDREG3        103
#define HOLDREG4        104
#define HOLDREG5        105
#define HOLDREG6        106
#define HOLDREG7        107
#define HOLDREG8        108
#define HOLDREG9        109
#define HOLDREG10       110
#define HOLDREG11       111
#define HOLDREG12       112
#define HOLDREG13       113
#define HOLDREG14       114
#define HOLDREG15       115
#define HOLDREG16       116
#define HOLDREG17       117
#define HOLDREG18       118
#define HOLDREG19       119
#define HOLDREG20       120 

#define ALARM1CHIP1     201
#define ALARM2CHIP1     202
#define ALARM1CHIP2     301
#define ALARM2CHIP2     302
#define ALARM1CHIP3     401
#define ALARM2CHIP3     402
#define ALARM1CHIP4     501
#define ALARM2CHIP4     502


/* LS7266 Counter registers */
#define COUNT1          601
#define COUNT2          602
#define COUNT3          603
#define COUNT4          604

#define PRESET1         701
#define PRESET2         702
#define PRESET3         703
#define PRESET4         704

#define PRESCALER1      801
#define PRESCALER2      802
#define PRESCALER3      803
#define PRESCALER4      804


/* Counter Gate Control */
#define NOGATE          0
#define AHLTCPREVCTR    1
#define AHLNEXTGATE     2
#define AHLPREVGATE     3
#define AHLGATE         4
#define ALLGATE         5
#define AHEGATE         6
#define ALEGATE         7

/* 7266 Counter Quadrature values */
#define NO_QUAD         0
#define X1_QUAD         1
#define X2_QUAD         2
#define X4_QUAD         4

/* 7266 Counter Counting Modes */
#define NORMAL_MODE     0
#define RANGE_LIMIT     1
#define NO_RECYCLE      2
#define MODULO_N        3

/* 7266 Counter encodings */
#define BCD_ENCODING	1
#define BINARY_ENCODING	2

/* 7266 Counter Index Modes */
#define INDEX_DISABLED  0
#define LOAD_CTR        1
#define LOAD_OUT_LATCH  2
#define RESET_CTR       3

/* 7266 Counter Flag Pins */
#define CARRY_BORROW          1
#define COMPARE_BORROW        2
#define CARRYBORROW_UPDOWN    3
#define INDEX_ERROR           4

/* Counter status bits */
#define C_UNDERFLOW     0x0001
#define C_OVERFLOW      0x0002
#define C_COMPARE       0x0004
#define C_SIGN          0x0008
#define C_ERROR         0x0010
#define C_UP_DOWN       0x0020
#define C_INDEX         0x0040

/* USB-QUAD08 Counter registers */
#define MAXLIMITREG0        0
#define MAXLIMITREG1        1
#define MAXLIMITREG2        2
#define MAXLIMITREG3        3
#define MAXLIMITREG4        4
#define MAXLIMITREG5        5
#define MAXLIMITREG6        6
#define MAXLIMITREG7        7

/* 25xx series counter mode constants */
#define TOTALIZE	0x0000
#define CLEAR_ON_READ	0x0001
#define ROLLOVER	0x0000
#define STOP_AT_MAX	0x0002
#define DECREMENT_OFF	0x0000
#define DECREMENT_ON	0x0020
#define BIT_16		0x0000
#define BIT_32		0x0004
#define BIT_48		0x10000
#define GATING_OFF	0x0000
#define GATING_ON	0x0010
#define LATCH_ON_SOS	0x0000
#define LATCH_ON_MAP	0x0008
#define UPDOWN_OFF		0x0000
#define UPDOWN_ON		0x1000
#define RANGE_LIMIT_OFF 0x0000
#define RANGE_LIMIT_ON  0x2000
#define NO_RECYCLE_OFF	0x0000
#define NO_RECYCLE_ON	0x4000
#define MODULO_N_OFF	0x0000
#define MODULO_N_ON		0x8000

#define PERIOD						0x0200
#define PERIOD_MODE_X1				0x0000
#define PERIOD_MODE_X10				0x0001
#define PERIOD_MODE_X100			0x0002
#define PERIOD_MODE_X1000			0x0003
#define PERIOD_MODE_BIT_16			0x0000
#define PERIOD_MODE_BIT_32			0x0004
#define PERIOD_MODE_BIT_48			0x10000
#define PERIOD_MODE_GATING_ON		0x0010

#define PULSEWIDTH					0x0300
#define PULSEWIDTH_MODE_BIT_16		0x0000
#define PULSEWIDTH_MODE_BIT_32		0x0004
#define PULSEWIDTH_MODE_BIT_48		0x10000
#define PULSEWIDTH_MODE_GATING_ON	0x0010

#define TIMING						0x0400
#define TIMING_MODE_BIT_16			0x0000
#define TIMING_MODE_BIT_32			0x0004
#define TIMING_MODE_BIT_48			0x10000

#define ENCODER							0x0500
#define ENCODER_MODE_X1					0x0000
#define ENCODER_MODE_X2					0x0001
#define ENCODER_MODE_X4					0x0002
#define ENCODER_MODE_BIT_16				0x0000
#define ENCODER_MODE_BIT_32				0x0004
#define ENCODER_MODE_BIT_48				0x10000
#define ENCODER_MODE_LATCH_ON_Z			0x0008
#define ENCODER_MODE_CLEAR_ON_Z_OFF		0x0000
#define ENCODER_MODE_CLEAR_ON_Z_ON		0x0020
#define ENCODER_MODE_RANGE_LIMIT_OFF	0x0000
#define ENCODER_MODE_RANGE_LIMIT_ON		0x2000
#define ENCODER_MODE_NO_RECYCLE_OFF		0x0000
#define ENCODER_MODE_NO_RECYCLE_ON		0x4000
#define ENCODER_MODE_MODULO_N_OFF		0x0000
#define ENCODER_MODE_MODULO_N_ON		0x8000

// obsolete encoder mode constants, use preferred constants above.
#define LATCH_ON_Z		0x0008
#define CLEAR_ON_Z_OFF	0x0000
#define CLEAR_ON_Z_ON	0x0020


/* 25xx series counter debounce time constants */
#define CTR_DEBOUNCE500ns      0
#define CTR_DEBOUNCE1500ns     1
#define CTR_DEBOUNCE3500ns     2
#define CTR_DEBOUNCE7500ns     3
#define CTR_DEBOUNCE15500ns    4
#define CTR_DEBOUNCE31500ns    5
#define CTR_DEBOUNCE63500ns    6   
#define CTR_DEBOUNCE127500ns   7   
#define CTR_DEBOUNCE100us      8
#define CTR_DEBOUNCE300us      9
#define CTR_DEBOUNCE700us      10
#define CTR_DEBOUNCE1500us     11
#define CTR_DEBOUNCE3100us     12
#define CTR_DEBOUNCE6300us     13
#define CTR_DEBOUNCE12700us    14
#define CTR_DEBOUNCE25500us    15
#define CTR_DEBOUNCE_NONE      16

/* 25xx series counter debounce trigger constants */
#define CTR_TRIGGER_AFTER_STABLE    0
#define CTR_TRIGGER_BEFORE_STABLE   1

/* 25xx series counter edge detection constants */
#define CTR_RISING_EDGE         0
#define CTR_FALLING_EDGE        1

/* Types of triggers */
#define TRIGABOVE           0
#define TRIGBELOW           1
#define GATE_NEG_HYS        2
#define GATE_POS_HYS        3
#define GATE_ABOVE          4
#define GATE_BELOW          5
#define GATE_IN_WINDOW      6
#define GATE_OUT_WINDOW     7
#define GATE_HIGH           8
#define GATE_LOW            9
#define TRIG_HIGH           10
#define TRIG_LOW            11
#define TRIG_POS_EDGE       12
#define TRIG_NEG_EDGE       13

/* Timer idle state */
#define IDLE_LOW			0
#define IDLE_HIGH			1

/* Signal I/O Configuration Parameters */
/* --Connections */
#define AUXIN0          0x01           
#define AUXIN1          0x02
#define AUXIN2          0x04
#define AUXIN3          0x08
#define AUXIN4          0x10
#define AUXIN5          0x20
#define AUXOUT0         0x0100
#define AUXOUT1         0x0200
#define AUXOUT2         0x0400

#define DS_CONNECTOR    0x01000

#define MAX_CONNECTIONS 4     /* maximum number connections per output signal type */


/* --Signal Types */
#define ADC_CONVERT     0x0001   
#define ADC_GATE        0x0002  
#define ADC_START_TRIG  0x0004
#define ADC_STOP_TRIG   0x0008
#define ADC_TB_SRC      0x0010
#define ADC_SCANCLK     0x0020
#define ADC_SSH         0x0040
#define ADC_STARTSCAN   0x0080
#define ADC_SCAN_STOP   0x0100

#define DAC_UPDATE      0x0200
#define DAC_TB_SRC      0x0400
#define DAC_START_TRIG  0x0800

#define SYNC_CLK        0x1000

#define CTR1_CLK        0x2000
#define CTR2_CLK        0x4000

#define DGND          0x8000

/* -- Signal Direction */
#define SIGNAL_IN       2
#define SIGNAL_OUT      4

/* -- Signal Polarity */
#define INVERTED        1
#define NONINVERTED     0


/* Types of configuration information */
#define GLOBALINFO         1
#define BOARDINFO          2
#define DIGITALINFO        3
#define COUNTERINFO        4
#define EXPANSIONINFO      5
#define MISCINFO           6
#define EXPINFOARRAY	   7
#define MEMINFO            8

/* Types of global configuration information */
#define GIVERSION          36      /* Config file format version number */
#define GINUMBOARDS        38      /* Maximum number of boards */
#define GINUMEXPBOARDS     40      /* Maximum number of expansion boards */

/* Types of board configuration information */
#define BIBASEADR           0       /* Base Address */
#define BIBOARDTYPE         1       /* Board Type (0x101 - 0x7FFF) */
#define BIINTLEVEL          2       /* Interrupt level */
#define BIDMACHAN           3       /* DMA channel */
#define BIINITIALIZED       4       /* TRUE or FALSE */
#define BICLOCK             5       /* Clock freq (1, 10 or bus) */
#define BIRANGE             6       /* Switch selectable range */
#define BINUMADCHANS        7       /* Number of A/D channels */
#define BIUSESEXPS          8       /* Supports expansion boards TRUE/FALSE */
#define BIDINUMDEVS         9       /* Number of digital devices */
#define BIDIDEVNUM          10      /* Index into digital information */
#define BICINUMDEVS         11      /* Number of counter devices */
#define BICIDEVNUM          12      /* Index into counter information */
#define BINUMDACHANS        13      /* Number of D/A channels */
#define BIWAITSTATE         14      /* Wait state enabled TRUE/FALSE */
#define BINUMIOPORTS        15      /* I/O address space used by board */
#define BIPARENTBOARD       16      /* Board number of parent board */
#define BIDTBOARD           17      /* Board number of connected DT board */
#define BINUMEXPS           18      /* Number of EXP boards installed */

/* NEW CONFIG ITEMS for 32 bit library */
#define BINOITEM             99      /* NO-OP return no data and returns DEVELOPMENT_OPTION error code */
#define BIDACSAMPLEHOLD      100     /* DAC sample and hold jumper state */
#define BIDIOENABLE          101     /* DIO enable */
#define BI330OPMODE          102     /* DAS16-330 operation mode (ENHANCED/COMPATIBLE) */
#define BI9513CHIPNSRC       103     /* 9513 HD CTR source (DevNo = ctr no.)*/
#define BICTR0SRC            104     /* CTR 0 source */
#define BICTR1SRC            105     /* CTR 1 source */
#define BICTR2SRC            106     /* CTR 2 source */
#define BIPACERCTR0SRC       107     /* Pacer CTR 0 source */
#define BIDAC0VREF           108     /* DAC 0 voltage reference */
#define BIDAC1VREF           109     /* DAC 1 voltage reference */
#define BIINTP2LEVEL         110     /* P2 interrupt for CTR10 and CTR20HD */
#define BIWAITSTATEP2        111     /* Wait state 2 */
#define BIADPOLARITY         112     /* DAS1600 Polarity state(UNI/BI) */
#define BITRIGEDGE           113     /* DAS1600 trigger edge(RISING/FALLING) */
#define BIDACRANGE           114     /* DAC Range (DevNo is channel) */
#define BIDACUPDATE          115     /* DAC Update (INDIVIDUAL/SIMULTANEOUS) (DevNo) */
#define BIDACINSTALLED       116     /* DAC Installed */
#define BIADCFG              117     /* AD Config (SE/DIFF) (DevNo) */
#define BIADINPUTMODE        118     /* AD Input Mode (Voltage/Current) */
#define BIDACPOLARITY        119     /* DAC Startup state (UNI/BI) */
#define BITEMPMODE           120     /* DAS-TEMP Mode (NORMAL/CALIBRATE) */
#define BITEMPREJFREQ        121     /* DAS-TEMP reject frequency */
#define BIDISOFILTER         122     /* DISO48 line filter (EN/DIS) (DevNo) */
#define BIINT32SRC           123     /* INT32 Intr Src */
#define BIINT32PRIORITY      124     /* INT32 Intr Priority */
#define BIMEMSIZE            125     /* MEGA-FIFO module size */
#define BIMEMCOUNT           126     /* MEGA-FIFO # of modules */
#define BIPRNPORT            127     /* PPIO series printer port */
#define BIPRNDELAY           128     /* PPIO series printer port delay */
#define BIPPIODIO            129     /* PPIO digital line I/O state */
#define BICTR3SRC            130     /* CTR 3 source */
#define BICTR4SRC            131     /* CTR 4 source */
#define BICTR5SRC            132     /* CTR 5 source */
#define BICTRINTSRC          133     /* PCM-D24/CTR3 interrupt source */
#define BICTRLINKING         134     /* PCM-D24/CTR3 ctr linking */
#define BISBX0BOARDNUM       135     /* SBX #0 board number */
#define BISBX0ADDRESS        136     /* SBX #0 address */
#define BISBX0DMACHAN        137     /* SBX #0 DMA channel */
#define BISBX0INTLEVEL0      138     /* SBX #0 Int Level 0 */
#define BISBX0INTLEVEL1      139     /* SBX #0 Int Level 1 */
#define BISBX1BOARDNUM       140     /* SBX #0 board number */
#define BISBX1ADDRESS        141     /* SBX #0 address */
#define BISBX1DMACHAN        142     /* SBX #0 DMA channel */
#define BISBX1INTLEVEL0      143     /* SBX #0 Int Level 0 */
#define BISBX1INTLEVEL1      144     /* SBX #0 Int Level 1 */
#define BISBXBUSWIDTH        145     /* SBX Bus width */
#define BICALFACTOR1         146     /* DAS08/Jr Cal factor */
#define BICALFACTOR2         147     /* DAS08/Jr Cal factor */
#define BIDACTRIG            148     /* PCI-DAS1602 Dac trig edge */
#define BICHANCFG            149     /* 801/802 chan config (devno =ch) */
#define BIPROTOCOL           150     /* 422 protocol */
#define BICOMADDR2           151     /* dual 422 2nd address */
#define BICTSRTS1            152     /* dual 422 cts/rts1 */
#define BICTSRTS2            153     /* dual 422 cts/rts2 */
#define BICTRLLINES          154     /* pcm com 422 ctrl lines */
#define BIWAITSTATEP1        155     /* Wait state P1 */
#define BIINTP1LEVEL         156     /* P1 interrupt for CTR10 and CTR20HD */
#define BICTR6SRC            157     /* CTR 6 source */
#define BICTR7SRC            158     /* CTR 7 source */
#define BICTR8SRC            159     /* CTR 8 source */
#define BICTR9SRC            160     /* CTR 9 source */
#define BICTR10SRC           161     /* CTR 10 source */
#define BICTR11SRC           162     /* CTR 11 source */
#define BICTR12SRC           163     /* CTR 12 source */
#define BICTR13SRC           164     /* CTR 13 source */
#define BICTR14SRC           165     /* CTR 14 source */
#define BITCGLOBALAVG		  166	 /* DASTC global average */
#define BITCCJCSTATE		     167	 /* DASTC CJC State(=ON or OFF) */
#define BITCCHANRANGE		  168	 /* DASTC Channel Gain */
#define BITCCHANTYPE		     169	 /* DASTC Channel thermocouple type */
#define BITCFWVERSION		  170	 /* DASTC Firmware Version */
#define BIFWVERSION          BITCFWVERSION /* Firmware Version */
#define BIPHACFG             180     /* Quad PhaseA config (devNo =ch) */
#define BIPHBCFG             190     /* Quad PhaseB config (devNo =ch) */
#define BIINDEXCFG           200     /* Quad Index Ref config (devNo =ch) */
#define BISLOTNUM            201     /* PCI/PCM card slot number */
#define BIAIWAVETYPE         202     /* analog input wave type (for demo board) */
#define BIPWRUPSTATE         203     /* DDA06 pwr up state jumper */
#define BIIRQCONNECT         204     /* DAS08 pin6 to 24 jumper */
#define BITRIGPOLARITY		  205 	 /* PCM DAS16xx Trig Polarity */
#define BICTLRNUM            206     /* MetraBus controller board number */
#define BIPWRJMPR            207     /* MetraBus controller board Pwr jumper */
#define BINUMTEMPCHANS       208     /* Number of Temperature channels */
#define BIADTRIGSRC          209     /* Analog trigger source */
#define BIBNCSRC             210     /* BNC source */ 
#define BIBNCTHRESHOLD       211     /* BNC Threshold 2.5V or 0.0V */
#define BIBURSTMODE          212     /* Board supports BURSTMODE */
#define BIDITHERON           213     /* A/D Dithering enabled */
#define BISERIALNUM          214    /* Serial Number for USB boards */
#define BIDACUPDATEMODE      215    /* Update immediately or upon AOUPDATE command */
#define BIDACUPDATECMD       216    /* Issue D/A UPDATE command */
#define BIDACSTARTUP         217    /* Store last value written for startup */ 
#define BIADTRIGCOUNT        219    /* Number of samples to acquire per trigger in retrigger mode */
#define BIADFIFOSIZE         220    /* Set FIFO override size for retrigger mode */
#define BIADSOURCE           221    /* Set source to internal reference or external connector(-1) */
#define BICALOUTPUT          222    /* CAL output pin setting */ 
#define BISRCADPACER         223    /* Source A/D Pacer output */
#define BIMFGSERIALNUM       224    /* Manufacturers 8-byte serial number */
#define BIPCIREVID           225    /* Revision Number stored in PCI header */
#define BIDIALARMMASK        230

#define BINETIOTIMEOUT       247

#define BISYNCMODE           251    /* Sync mode */

#define BIDIDEBOUNCESTATE    255    /* Digital inputs reset state */
#define BIDIDEBOUNCETIME     256      /* Digital inputs debounce Time */

#define BIPANID               258
#define BIRFCHANNEL           259

#define BIRSS                 261
#define BINODEID              262
#define BIDEVNOTES            263

#define BIADCSETTLETIME		  270

#define BIFACTORYID           272
#define BIHTTPPORT			  273
#define BIHIDELOGINDLG		  274
#define BIDACTRIGCOUNT		  284	/* Number of samples to generate per trigger in retrigger mode */
#define BIADTIMINGMODE		  285
#define BIRTDCHANTYPE		  286


/* Type of digital device information */
#define DIBASEADR           0       /* Base address */
#define DIINITIALIZED       1       /* TRUE or FALSE */
#define DIDEVTYPE           2       /* AUXPORT or xPORTA - CH */
#define DIMASK              3       /* Bit mask for this port */
#define DIREADWRITE         4       /* Read required before write */
#define DICONFIG            5      /* Current configuration */
#define DINUMBITS           6      /* Number of bits in port */
#define DICURVAL            7      /* Current value of outputs */
#define DIINMASK            8      /* Input bit mask for port */
#define DIOUTMASK           9      /* Output bit mask for port */

/* Types of counter device information */
#define CIBASEADR           0       /* Base address */
#define CIINITIALIZED       1       /* TRUE or FALSE */
#define CICTRTYPE           2       /* Counter type 8254, 9513 or 8536 */
#define CICTRNUM            3       /* Which counter on chip */
#define CICONFIGBYTE        4       /* Configuration byte */

/* Types of expansion board information */
#define XIBOARDTYPE         0       /* Board type */
#define XIMUX_AD_CHAN1      1       /* 0 - 7 */
#define XIMUX_AD_CHAN2      2       /* 0 - 7 or NOTUSED */
#define XIRANGE1            3       /* Range (gain) of low 16 chans */
#define XIRANGE2            4       /* Range (gain) of high 16 chans */
#define XICJCCHAN           5       /* TYPE_8254_CTR or TYPE_9513_CTR */
#define XITHERMTYPE         6       /* TYPEJ, TYPEK, TYPET, TYPEE, TYPER, or TYPES*/
#define XINUMEXPCHANS       7       /* Number of expansion channels on board*/
#define XIPARENTBOARD       8       /* Board number of parent A/D board*/
#define XISPARE0            9       /* 16 words of misc options */

#define XI5VOLTSOURCE       100     /* ICAL DATA - 5 volt source */
#define XICHANCONFIG        101     /* exp Data - chan config 2/4 or 3-wire devNo=chan */
#define XIVSOURCE           102     /* ICAL DATA - voltage source*/
#define XIVSELECT           103     /* ICAL Data - voltage select*/
#define XICHGAIN            104     /* exp Data - individual ch gain */
#define XIGND               105     /* ICAL DATA - exp grounding */
#define XIVADCHAN           106     /* ICAL DATA - Vexe A/D chan */
#define XIRESISTANCE        107     /* exp Data - resistance @0 (devNo =ch) */
#define XIFACGAIN           108	    /* ICAL DATA - RTD factory gain */
#define XICUSTOMGAIN        109 	/* ICAL DATA - RTD custom gain */
#define XICHCUSTOM          110		/* ICAL DATA - RTD custom gain setting*/
#define XIIEXE              111 	/* ICAL DATA - RTD Iexe */

/* Types of memory board information */
#define MIBASEADR           100 	/* mem data - base address */
#define MIINTLEVEL          101 	/* mem data - intr level */
#define MIMEMSIZE		    102		/* MEGA-FIFO module size */
#define MIMEMCOUNT		    103		/* MEGA-FIFO # of modules */



/* Types of events */
#define	ON_SCAN_ERROR				0x0001
#define ON_EXTERNAL_INTERRUPT		0x0002
#define ON_PRETRIGGER				0x0004
#define ON_DATA_AVAILABLE			0x0008
#define ON_END_OF_AI_SCAN			0x0010
#define ON_END_OF_AO_SCAN			0x0020
#define ON_CHANGE_DI             0x0040
#define ALL_EVENT_TYPES          0xffff

#define NUM_EVENT_TYPES		6
#define MAX_NUM_EVENT_TYPES 32

#define SCAN_ERROR_IDX				0
#define EXTERNAL_INTERRUPT_IDX	1
#define PRETRIGGER_IDX				2
#define DATA_AVAILABLE_IDX			3
#define END_OF_AI_IDX				4
#define END_OF_AO_IDX				5

/* ON_EXTERNAL_INTERRUPT event parameters*/
#define LATCH_DI			1
#define LATCH_DO			2


// time zone constants
#define TIMEZONE_LOCAL		0
#define TIMEZONE_GMT		1


// time format constants
#define TIMEFORMAT_12HOUR	0
#define TIMEFORMAT_24HOUR	1


// delimiter constants
#define DELIMITER_COMMA		0
#define DELIMITER_SEMICOLON	1
#define DELIMITER_SPACE		2
#define DELIMITER_TAB		3


// AI channel units in binary file
#define UNITS_TEMPERATURE	0
#define UNITS_RAW			1


#ifndef USHORT
  typedef unsigned short USHORT;
#endif

#define EXTCCONV 	__stdcall



/*
 * Universal Library Function Prototypes.
 * 3 flavors: WIN32, WIN16, LabWindows/CVI
 *                                    
 */

#if !defined (NT_DRIVER) && ! defined (WIN95_DRIVER)

#if defined (__cplusplus)
    extern "C"
    {
#endif  

#if defined (_WIN32)
	/* Win32 prototypes */

#ifdef EVENTCALLBACK
#undef EVENTCALLBACK
#endif

    typedef void (__stdcall *EVENTCALLBACK)(int, unsigned, unsigned, void*);

    int EXTCCONV cbACalibrateData (int BoardNum, long NumPoints, int Gain, 
                                   USHORT *ADData);
    int EXTCCONV cbGetRevision (float *RevNum, float *VxDRevNum);
    int EXTCCONV cbLoadConfig(char *CfgFileName);
    int EXTCCONV cbSaveConfig(char *CfgFileName);
    int EXTCCONV cbAConvertData (int BoardNum, long NumPoints, USHORT *ADData, 
		                         USHORT *ChanTags);
    int EXTCCONV cbAConvertPretrigData (int BoardNum, long PreTrigCount, 
		                                long TotalCount, USHORT *ADData, 
										USHORT *ChanTags);
    int EXTCCONV cbAIn (int BoardNum, int Chan, int Gain, USHORT *DataValue);
    int EXTCCONV cbAIn32 (int BoardNum, int Chan, int Gain, ULONG *DataValue, int Options);
    int EXTCCONV cbAInScan (int BoardNum, int LowChan, int HighChan, long Count,
                            long *Rate, int Gain, HGLOBAL MemHandle, 
							int Options);
    int EXTCCONV cbALoadQueue (int BoardNum, short *ChanArray, short *GainArray, 
		                       int NumChans);
    int EXTCCONV cbAOut (int BoardNum, int Chan, int Gain, USHORT DataValue);
    int EXTCCONV cbAOutScan (int BoardNum, int LowChan, int HighChan, 
		                     long Count, long *Rate, int Gain, 
							 HGLOBAL MemHandle, int Options);
    int EXTCCONV cbAPretrig (int BoardNum, int LowChan, int HighChan,
                             long *PreTrigCount, long *TotalCount, long *Rate, 
							 int Gain, HGLOBAL MemHandle, int Options);
    int EXTCCONV cbATrig (int BoardNum, int Chan, int TrigType, 
		                  USHORT TrigValue, int Gain, USHORT *DataValue);
    int EXTCCONV cbC7266Config (int BoardNum, int CounterNum, int Quadrature,
                                int CountingMode, int DataEncoding, int IndexMode,
                                int InvertIndex, int FlagPins, int GateEnable);
    int EXTCCONV cbC8254Config (int BoardNum, int CounterNum, int Config);
    int EXTCCONV cbC8536Config (int BoardNum, int CounterNum, int OutputControl,
                                int RecycleMode, int TrigType);
    int EXTCCONV cbC9513Config (int BoardNum, int CounterNum, int GateControl,
                                int CounterEdge, int CountSource, 
								int SpecialGate, int Reload, int RecycleMode, 
								int BCDMode, int CountDirection, 
								int OutputControl);
    int EXTCCONV cbC8536Init (int BoardNum, int ChipNum, int Ctr1Output);
    int EXTCCONV cbC9513Init (int BoardNum, int ChipNum, int FOutDivider, 
		                      int FOutSource, int Compare1, int Compare2, 
							  int TimeOfDay);
    int EXTCCONV cbCFreqIn (int BoardNum, int SigSource, int GateInterval,
                            USHORT *Count, long *Freq);
    int EXTCCONV cbCIn (int BoardNum, int CounterNum, USHORT *Count);
    int EXTCCONV cbCIn32 (int BoardNum, int CounterNum, ULONG *Count);
	int EXTCCONV cbCIn64 (int BoardNum, int CounterNum, ULONGLONG *Count);
    int EXTCCONV cbCLoad (int BoardNum, int RegNum, unsigned int LoadValue);
    int EXTCCONV cbCLoad32 (int BoardNum, int RegNum, ULONG LoadValue);
	int EXTCCONV cbCLoad64 (int BoardNum, int RegNum, ULONGLONG LoadValue);
    int EXTCCONV cbCStatus (int BoardNum, int CounterNum, ULONG *StatusBits);
    int EXTCCONV cbCStoreOnInt (int BoardNum, int IntCount, short *CntrControl,
                                HGLOBAL MemHandle);
	int EXTCCONV cbCInScan(int BoardNum, int FirstCtr,int LastCtr, LONG Count,
							LONG *Rate, HGLOBAL MemHandle, ULONG Options);
	int EXTCCONV cbCConfigScan(int BoardNum, int CounterNum, int Mode,int DebounceTime,
								int DebounceMode, int EdgeDetection,
								int TickSize, int MappedChannel);
    int EXTCCONV cbCClear (int BoardNum, int CounterNum);
    int EXTCCONV cbTimerOutStart (int BoardNum, int TimerNum, double *Frequency);
    int EXTCCONV cbTimerOutStop (int BoardNum, int TimerNum);
	int EXTCCONV cbPulseOutStart (int BoardNum, int TimerNum, double *Frequency, double *DutyCycle, unsigned int PulseCount, double *InitialDelay, int IdleState, int Options);
    int EXTCCONV cbPulseOutStop (int BoardNum, int TimerNum);
    int EXTCCONV cbDBitIn (int BoardNum, int PortType, int BitNum, 
                           USHORT *BitValue);
    int EXTCCONV cbDBitOut (int BoardNum, int PortType, int BitNum, USHORT BitValue);
    int EXTCCONV cbDConfigPort (int BoardNum, int PortNum, int Direction);
    int EXTCCONV cbDConfigBit (int BoardNum, int PortNum, int BitNum, int Direction);
    int EXTCCONV cbDIn (int BoardNum, int PortNum, USHORT *DataValue);
    int EXTCCONV cbDInScan (int BoardNum, int PortNum, long Count, long *Rate,
                            HGLOBAL MemHandle, int Options);
    int EXTCCONV cbDOut(int BoardNum, int PortNum, USHORT DataValue);
    int EXTCCONV cbDOutScan (int BoardNum, int PortNum, long Count, long *Rate,
                             HGLOBAL MemHandle, int Options);
    int EXTCCONV cbErrHandling (int ErrReporting, int ErrHandling);
    int EXTCCONV cbFileAInScan (int BoardNum, int LowChan, int HighChan,
                                long Count, long *Rate, int Gain, 
								char *FileName, int Options);
    int EXTCCONV cbFileGetInfo (char *FileName, short *LowChan, short *HighChan,
		                        long *PreTrigCount, long *TotalCount, 
								long *Rate, int *Gain);
    int EXTCCONV cbFilePretrig (int BoardNum, int LowChan, int HighChan,
                                long *PreTrigCount, long *TotalCount, 
								long *Rate, int Gain, char *FileName, 
								int Options);
    int EXTCCONV cbFileRead (char *FileName, long FirstPoint, long *NumPoints,
                             USHORT *DataBuffer);
    int EXTCCONV cbFlashLED(int BoardNum);
    int EXTCCONV cbGetErrMsg (int ErrCode, char *ErrMsg);
    int EXTCCONV cbGetIOStatus (int BoardNum, short *Status, long *CurCount,
                              long *CurIndex,int FunctionType);
    int EXTCCONV cbRS485 (int BoardNum, int Transmit, int Receive);
    int EXTCCONV cbStopIOBackground (int BoardNum, int FunctionType);
    int EXTCCONV cbTIn (int BoardNum, int Chan, int Scale, float *TempValue,
                        int Options);
    int EXTCCONV cbTInScan (int BoardNum, int LowChan, int HighChan, int Scale,
                            float *DataBuffer, int Options);
    int EXTCCONV cbMemSetDTMode (int BoardNum, int Mode);
    int EXTCCONV cbMemReset (int BoardNum);
    int EXTCCONV cbMemRead (int BoardNum, USHORT *DataBuffer, long FirstPoint, 
		                    long Count);
    int EXTCCONV cbMemWrite (int BoardNum, USHORT *DataBuffer,long FirstPoint, 
		                     long Count);
    int EXTCCONV cbMemReadPretrig (int BoardNum, USHORT *DataBuffer,
                                   long FirstPoint, long Count);
    int EXTCCONV cbWinBufToArray (HGLOBAL MemHandle, USHORT *DataArray, 
		                          long StartPt, long Count);
     int EXTCCONV cbWinBufToArray32 (HGLOBAL MemHandle, ULONG *DataArray, 
		                          long StartPt, long Count);

	  HGLOBAL EXTCCONV cbScaledWinBufAlloc (long NumPoints);
     int EXTCCONV cbScaledWinBufToArray (HGLOBAL MemHandle, double *DataArray, 
		                          long StartPt, long Count);
		
    int EXTCCONV cbWinArrayToBuf (USHORT *DataArray, HGLOBAL MemHandle, 
		                          long StartPt, long Count);
	int EXTCCONV cbScaledWinArrayToBuf (double *DataArray, HGLOBAL MemHandle, 
		                          long StartPt, long Count);

    HGLOBAL EXTCCONV cbWinBufAlloc (long NumPoints);
    HGLOBAL EXTCCONV cbWinBufAlloc32 (long NumPoints);
    HGLOBAL EXTCCONV cbWinBufAlloc64 (long NumPoints);
    int EXTCCONV cbWinBufFree (HGLOBAL MemHandle);
    int EXTCCONV cbInByte (int BoardNum, int PortNum);
    int EXTCCONV cbOutByte (int BoardNum, int PortNum, int PortVal);
    int EXTCCONV cbInWord (int BoardNum, int PortNum);
    int EXTCCONV cbOutWord (int BoardNum, int PortNum, int PortVal);

    int EXTCCONV cbGetConfig (int InfoType, int BoardNum, int DevNum, 
                              int ConfigItem, int *ConfigVal);
    int EXTCCONV cbGetConfigString (int InfoType, int BoardNum, int DevNum, 
                              int ConfigItem, char* ConfigVal, int* maxConfigLen);

    int EXTCCONV cbSetConfig (int InfoType, int BoardNum, int DevNum, 
		                      int ConfigItem, int ConfigVal);
    int EXTCCONV cbSetConfigString (int InfoType, int BoardNum, int DevNum, 
		                      int ConfigItem, char* ConfigVal, int* configLen);

    int EXTCCONV cbToEngUnits (int BoardNum, int Range, USHORT DataVal, 
		                       float *EngUnits);
    int EXTCCONV cbToEngUnits32 (int BoardNum, int Range, ULONG DataVal, 
		                       double *EngUnits);
    int EXTCCONV cbFromEngUnits (int BoardNum, int Range, float EngUnits, 
		                         USHORT *DataVal);
    int EXTCCONV cbGetBoardName (int BoardNum, char *BoardName);
    int EXTCCONV cbDeclareRevision(float *RevNum);
    int EXTCCONV cbSetTrigger (int BoardNum, int TrigType, USHORT LowThreshold, 
		                       USHORT HighThreshold);
 
	int EXTCCONV cbEnableEvent(int BoardNum, unsigned EventType, unsigned Count, 
					EVENTCALLBACK CallbackFunc, void *UserData);

	int EXTCCONV cbDisableEvent(int BoardNum, unsigned EventType);
   int EXTCCONV cbSelectSignal(int BoardNum,  int Direction, int Signal, int Connection, int Polarity);
   int EXTCCONV cbGetSignal(int BoardNum, int Direction, int Signal, int Index, int* Connection, int* Polarity);

   int EXTCCONV cbSetCalCoeff(int BoardNum, int FunctionType, int Channel, int Range, int Item, int Value, int Store);
   int EXTCCONV cbGetCalCoeff(int BoardNum, int FunctionType, int Channel, int Range, int Item, int* Value);


	// Get log file name

	// store the preferences
	int EXTCCONV cbLogSetPreferences(int timeFormat, int timeZone, int units);

	// get the preferences
	int EXTCCONV cbLogGetPreferences(int* timeFormat, int* timeZone, int* units);

	// Get log file name
	int EXTCCONV cbLogGetFileName(int fileNumber, char* path, char* filename);

	// Get info for log file
	int EXTCCONV cbLogGetFileInfo(char* filename, int* version, int* fileSize);

	// Get sample info for log file
	int EXTCCONV cbLogGetSampleInfo(char* filename, int* sampleInterval, int* sampleCount, 
									int* startDate, int* startTime);

	// Get the AI channel count for log file
	int EXTCCONV cbLogGetAIChannelCount(char* filename, int* aiCount);

	// Get AI info for log file
	int EXTCCONV cbLogGetAIInfo(char* filename, int* channelNumbers, int* units);

	// Get CJC info for log file
	int EXTCCONV cbLogGetCJCInfo(char* filename, int* cjcCount);

	// Get DIO info for log file
	int EXTCCONV cbLogGetDIOInfo(char* filename, int* dioCount);

	// read the time tags to an array
	int EXTCCONV cbLogReadTimeTags(char* filename, int startSample, int count, int* dateTags, int*timeTags);

	// read the analog data to an array
	int EXTCCONV cbLogReadAIChannels(char* filename, int startSample, int count, float* analog);

	// read the CJC data to an array
	int EXTCCONV cbLogReadCJCChannels(char* filename, int startSample, int count, float* cjc);

	// read the DIO data to an array
	int EXTCCONV cbLogReadDIOChannels(char* filename, int startSample, int count, int* dio);

	// convert the log file to a .TXT or .CSV file
	int EXTCCONV cbLogConvertFile(char* srcFilename, char* destFilename, int startSample, int count, int delimiter);

	int EXTCCONV cbDaqInScan(int BoardNum, short *ChanArray, short *ChanTypeArray, short *GainArray, int ChanCount, long *Rate,
							long *PretrigCount, long *TotalCount, HGLOBAL MemHandle, int Options);
	int EXTCCONV cbDaqSetTrigger(int BoardNum, int TrigSource, int TrigSense, int TrigChan, int ChanType, 
							   int Gain, float Level, float Variance, int TrigEvent);
	int EXTCCONV cbDaqSetSetpoints (int BoardNum, float *LimitAArray, float *LimitBArray, float *Reserved, int *SetpointFlagsArray,
		                       int *SetpointOutputArray, float *Output1Array, float *Output2Array, float *OutputMask1Array,
				       float *OutputMask2Array, int SetpointCount);

	int EXTCCONV cbDaqOutScan(int BoardNum, short *ChanArray, short *ChanTypeArray, short *GainArray, int ChanCount, long *Rate,
							 long Count, HGLOBAL MemHandle, int Options);
	int EXTCCONV cbGetTCValues(int BoardNum, short *ChanArray, short *ChanTypeArray, int ChanCount, HGLOBAL MemHandle, int FirstPoint,
							 long Count, int Scale, float *TempValArray);

	int EXTCCONV cbVIn (int BoardNum, int Chan, int Gain, float *DataValue, int Options);
	int EXTCCONV cbVIn32 (int BoardNum, int Chan, int Gain, double *DataValue, int Options);
	int EXTCCONV cbVOut (int BoardNum, int Chan, int Gain, float DataValue, int Options);
	
	int EXTCCONV cbDeviceLogin(int BoardNum, char* AccountName, char* Password);
	int EXTCCONV cbDeviceLogout(int BoardNum);

	int EXTCCONV cbTEDSRead(int BoardNum, int Chan, BYTE* DataBuffer, long *Count, int Options);

//****************************************************************************
//   Legacy Function Prototypes: to revert to legacy calls, un-comment the
//          prototypes immediately below.
//
//      int EXTCCONV cbGetStatus (int BoardNum, short *Status, long *CurCount, long *CurIndex);
//      int EXTCCONV cbStopBackground (int BoardNum);
//
//   Remove the following if using the above legacy function prototypes.
#define cbGetStatus cbGetIOStatus
#define cbStopBackground cbStopIOBackground
//****************************************************************************

#endif  /* if defined (_WIN32) */

#if defined (__cplusplus)
    }
#endif

#endif  /* ifndef NT_DRIVER */

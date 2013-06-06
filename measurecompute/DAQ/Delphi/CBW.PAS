
{***************************************}
{                                       }
{ Name:   CBW.PAS                       }
{                                       }
{ Delphi Interface Unit for             }
{ Measurement Computing's Universal     }
{     Library                           }
{                                       }
{ (c) Copyright 1996 - 2009             }
{     Measurement Computing Corp.       }
{     All rights reserved.              }
{                                       }
{***************************************}


unit Cbw;

{$D+,S+,L+}


interface


const

{ Current Revision Number}
  CURRENTREVNUM = 5.90;

{ System error code }
  NOERRORS           = 0;    { No error occurred }
  BADBOARD           = 1;    { Invalid board number specified }
  DEADDIGITALDEV     = 2;    { Digital I/O is not responding }
  DEADCOUNTERDEV     = 3;    { Counter is not responding }
  DEADDADEV          = 4;    { D/A is not responding }
  DEADADDEV          = 5;    { A/D is not responding }
  NOTDIGITALCONF     = 6;    { Specified board does not have digital I/O }
  NOTCOUNTERCONF     = 7;    { Specified board does not have a counter }
  NOTDACONF          = 8;    { Specified board is does not have D/A }
  NOTADCONF          = 9;    { Specified board does not have A/D }
  NOTMUXCONF         = 10;   { Specified board does not have thermocouple inputs }
  BADPORTNUM         = 11;   { Invalid port number specified }
  BADCOUNTERDEVNUM   = 12;   { Invalid counter device }
  BADDADEVNUM        = 13;   { Invalid D/A device }
  BADSAMPLEMODE      = 14;   { Inavlid sampling mode option specified }
  BADINT             = 15;   { Board configured for invalid interrupt level }
  BADADCHAN          = 16;   { Invalid A/D channel Specified }
  BADCOUNT           = 17;   { Invalid count specified }
  BADCNTRCONFIG      = 18;   { invalid counter configuration specified }
  BADDAVAL           = 19;   { Invalid D/A output value specified }
  BADDACHAN          = 20;   { Invalid D/A channel specified }
  ALREADYACTIVE      = 22;   { A background process is already in progress }
  PAGEOVERRUN      = 23;   { DMA page overrun - obsolete }
  BADRATE            = 24;   { Inavlid sampling rate specified }
  COMPATMODE         = 25;   { Board switches set for "compatible" mode }
  TRIGSTATE          = 26;   { Incorrect intial trigger state D0 must=TTL low) }
  ADSTATUSHUNG       = 27;   { A/D is not responding }
  TOOFEW             = 28;   { Too few samples before trigger occurred }
  OVERRUN            = 29;   { Data lost due to overrun, rate too high }
  BADRANGE           = 30;   { Invalid range specified }
  BADFILENAME        = 32;   { Not a legal DOS filename }
  DISKISFULL         = 33;   { Couldn't complete, disk is full }
  COMPATWARN         = 34;   { Board is in compatible mode, so DMA will be used }
  BADPOINTER         = 35;   { Invalid pointer (NULL) }
  RATEWARNING        = 37;   { Rate may be too high for interrupt I/O }
  CONVERTDMA         = 38;   { CONVERTDATA cannot be used with DMA I/O }
  DTCONNECTERR       = 39;   { Board doesn't have DT Connect }
  FORECONTINUOUS     = 40;   { CONTINUOUS can only be used with BACKGROUND }
  BADBOARDTYPE       = 41;   { This function can not be used with this board }
  WRONGDIGCONFIG     = 42;   { Digital I/O is configured incorrectly }
  NOTCONFIGURABLE    = 43;   { Digital port is not configurable }
  BADPORTCONFIG      = 44;   { Invalid port configuration specified }
  BADFIRSTPOINT      = 45;   { First point argument is not valid }
  ENDOFFILE          = 46;   { Attempted to read past end of file }
  NOT8254CTR         = 47;   { This board does not have an 8254 counter }
  NOT9513CTR         = 48;   { This board does not have a 9513 counter }
  BADTRIGTYPE        = 49;   { Invalid trigger type }
  BADTRIGVALUE       = 50;   { Invalid trigger value }
  BADOPTION          = 52;   { Invalid option sepcified for this function }
  BADPRETRIGCOUNT    = 53;   { Invalid pre-trigger count sepcified }
  BADDIVIDER         = 55;   { Invalid fout divider value }
  BADSOURCE          = 56;   { Invalid source value  }
  BADCOMPARE         = 57;   { Invalid compare value }
  BADTIMEOFDAY       = 58;   { Invalid time of day value }
  BADGATEINTERVAL    = 59;   { Invalid gate interval value }
  BADGATECNTRL       = 60;   { Invalid gate control value }
  BADCOUNTEREDGE     = 61;   { Invalid counter edge value }
  BADSPCLGATE        = 62;   { Invalid special gate value }
  BADRELOAD          = 63;   { Invalid reload value }
  BADRECYCLEFLAG     = 64;   { Invalid recycle flag value }
  BADBCDFLAG         = 65;   { Invalid BCD flag value }
  BADDIRECTION       = 66;   { Invalid count direction value }
  BADOUTCONTROL      = 67;   { Invalid output control value }
  BADBITNUMBER       = 68;   { Invalid bit number }
  NONEENABLED        = 69;   { None of the counter channels are enabled }
  BADCTRCONTROL      = 70;   { Element of control array not ENABLED/DISABLED }
  BADEXPCHAN         = 71;   { Invalid MUX channel }
  WRONGADRANGE       = 72;   { Wrong A/D range selected for cbtherm }
  OUTOFRANGE         = 73;   { Temperature input is out of range }
  BADTEMPSCALE       = 74;   { Invalid temperate scale }
  BADERRCODE         = 75;   { Invalid error code specified }
  NOQUEUE            = 76;   { Specified board does not have chan/gain queue}
  CONTINUOUSCOUNT    = 77;   { CONTINUOUS option can't be used with this count value }
  UNDERRUN           = 78;   { D/A FIFO hit empty while doing output }
  BADMEMMODE         = 79;   { Invalid memory mode specified }
  FREQOVERRUN        = 80;   { Measured freq to high for gating interval }
  NOCJCCHAN          = 81;   { Board does not have CJC chan configured }
  BADCHIPNUM         = 82;   { Invalid chip number used with cbC9513Init() }
  DIGNOTENABLED      = 83;   { Digital I/O on board is not enabled }
  CONVERT16BITS      = 84;   { Convert option not allowed with 16 bit A/D }
  NOMEMBOARD         = 85;   { EXTMEMORY option requires a memory board }
  DTACTIVE           = 86;   { Memory I/O while DT was active }
  NOTMEMCONF         = 87;   { Specified board is not a memory board }
  ODDCHAN            = 88;   { First chan in queue can not be odd }
  CTRNOINIT          = 89;   { Counter was not initialized }
  NOT8536CTR         = 90;   { Specified counter is not an 8536 }
  FREERUNNING        = 91;   { A/D is not timed. Running at fastest possible speed }
  INTERRUPTED        = 92;   { Operation was interrupted with CTRL-C key }
  NOSELECTORS        = 93;   { No selectors could be allocated }
  NOBURSTMODE        = 94;   { Burst mode is not supported on this board }
  NOTWINDOWSFUNC     = 95;   { This function not available in Windows lib }
  NOTSIMULCONF       = 96;   { Board not configured for simultaneous option }
  EVENODDMISMATCH    = 97;   { Even channel in odd slot in the queue }
  M1RATEWARNING      = 98;   { DAS16/M1 sample rate too fast for count }
  NOTRS485           = 99;   { Specified board is not a COM-485 }
  NOTDOSFUNC         = 100;  { This function not avaliable in DOS }
  RANGEMISMATCH      = 101;  { Unipolar and Bipolar can not be used together in A/D que }
  CLOCKTOOSLOW       = 102;  { Sample rate too fast for clock jumper setting }
  BADCALFACTORS      = 103;  { Cal factors were out of expected range of values }
  BADCONFIGTYPE      = 104;  { Invalid configuration type information requested }
  BADCONFIGITEM      = 105;  { Invalid configuration item specified }
  NOPCMCIABOARD      = 106;  { Can't acces PCMCIA board }
  NOBACKGROUND       = 107;  { Board does not support background I/O }
  STRINGTOOSHORT     = 108;  { String argument is not long enough }
  CONVERTEXTMEM      = 109;  { CONVERTDATA not allowed with EXTMEM }
  BADEUADD              = 110;   { e_ToEngUnits addition error }
  DAS16JRRATEWARNING    = 111;   { use 10 MHz clock for rates > 125KHz }
  DAS08TOOLOWRATE       = 112;   { DAS08 rate set too low for AInScan warning }
  MEMBOARDPROGERROR     = 113;   { Program error getting memory board source }
  AMBIGSENSORONGP       = 114;   { more than one sensor type defined for EXP-GP }
  NOSENSORTYPEONGP      = 115;   { no sensor type defined for EXP-GP }
  NOCONVERSIONNEEDED    = 116;   { 12 bit board without chan tags - converted in ISR }
  NOEXTCONTINUOUS       = 117;   { External memory cannot be used in CONTINUOUS mode }
  INVALIDPRETRIGCONVERT = 118;   { cbAConvertPretrigData was called after failure in cbAPretrig }
  BADCTRREG             = 119;   { bad arg to CLoad for 9513 }
  BADTRIGTHRESHOLD      = 120;   { Invalid trigger threshold specified in cbSetTrigger }
  BADPCMSLOTREF         = 121;   { Bad PCM Card slot reference }
  AMBIGPCMSLOTREF       = 122;   { Ambiguous PCM Card slot reference}
  BADSENSORTYPE         = 123;   { Bad sensor type selected in Instacal }
  DELBOARDNOTEXIST      = 124;   { tried to delete board number which doesn't exist }
  NOBOARDNAMEFILE       = 125;   { board name file not found }
  CFGFILENOTFOUND       = 126;   { configuration file not found }
  NOVDDINSTALLED        = 127;   { CBUL.386 device driver is not installed }
  NOWINDOWSMEMORY       = 128;   { No Windows memory avaliable }
  OUTOFDOSMEMORY        = 129;   { No DOS memory available }
  OBSOLETEOPTION        = 130;   { Option not supportedin cbGet/SetConfig }
  NOPCMREGKEY           = 131;   { No registry entry for this PCMCIA board }
  NOCBUL32SYS           = 132;   { CBUL32.SYS device driver not installed }
  NODMAMEMEMORY         = 133;   { No memory for device driver's DMA buffer }  
  IRQNOTAVAILABLE       = 134;   { IRQ in use by another device }
  NOT7266CTR            = 135;   { This board does not have an LS7266 counter }
  BADQUADRATURE         = 136;   { Invalid quadrature specified }
  BADCOUNTMODE          = 137;   { Invalid counting mode specified }
  BADENCODING           = 138;   { Invalid data encoding specified }
  BADINDEXMODE          = 139;   { Invalid index mode specified }
  BADINVERTINDEX        = 140;   { Invalid invert index specified }
  BADFLAGPINS           = 141;   { Invalid flag pins specified }
  NOCTRSTATUS           = 142;   { This board does not support cbCStatus() }
  NOGATEALLOWED         = 143;   { Gating and indexing not allowed simultaneously }
  NOINDEXALLOWED        = 144;   { Indexing not allowed in non-quadratue mode }
  OPENCONNECTION        = 145;   { Temperature input has open connection }
  BMCONTINUOUSCOUNT     = 146;   { Count must be integer multiple of packetsize for recycle mode. }
  BADCALLBACKFUNC       = 147;   { Invalid pointer to callback function passed as arg }
  MBUSINUSE              = 148;   { MetraBus in use }
  MBUSNOCTLR             = 149;   { MetraBus I/O card has no configured controller card }
  BADEVENTTYPE           = 150;   { Invalid event type specified for this board. }
  ALREADYENABLED        = 151;   { An event handler has already been enabled for this event type }
  BADEVENTSIZE          = 152;   { Invalid event count specified. }
  CANTINSTALLEVENT      = 153;   { Unable to install event handler }
  BADBUFFERSIZE         = 154;   { Buffer is too small for operation }
  BADAIMODE             = 155;    { Invalid Analog Input Mode (RSE, NRSE, DIFF) }
  BADSIGNAL             = 156;   { Invalid signal type specified. }
  BADCONNECTION         = 157;   { Invalid connection specified. }
  BADINDEX              = 158;   { Invalid index specified, or reached end of internal connection list. }
  NOCONNECTION          = 159;   { No connection is assigned to specified signal. }
  BADBURSTIOCOUNT       = 160;   { Count cannot be greater than the FIFO size for BURSTIO mode.}
  DEADDEV               = 161;   { Device has stopped responding. Please check connections. }

  INVALIDACCESS         = 163;    { Invalid access or privilege for specified operation }
  UNAVAILABLE           = 164;    { Device unavailable at time of request. Please repeat operation. }
  NOTREADY              = 165;   { Device is not ready to send data. Please repeat operation. }
  BITUSEDFORALARM        = 169;   { The specified bit is used for alarm. }
  PORTUSEDFORALARM       = 170;   { One or more bits on the specified port are used for alarm. }
  PACEROVERRUN       = 171;   { Pacer overrun, external clock rate too fast. }
  BADCHANTYPE        = 172;   { Invalid channel type specified. }
  BADTRIGSENSE           = 173;   { Invalid trigger sensitivity specified. }
  BADTRIGCHAN            = 174;   { Invalid trigger channel specified. }
  BADTRIGLEVEL           = 175;   { Invalid trigger level specified. }
  NOPRETRIGMODE          = 176;   { Pre-trigger mode is not supported for the specified trigger type. }
  BADDEBOUNCETIME        = 177;   { Invalid debounce time specified. }
  BADDEBOUNCETRIGMODE    = 178;   { Invalid debounce trigger mode specified. }
  BADMAPPEDCOUNTER       = 179;   { Invalid mapped counter specified. }
  BADCOUNTERMODE         = 180;   { This function can not be used with the current mode of the specified counter. }
  BADTCCHANMODE          = 181;   { Single-Ended mode can not be used for temperature input. }
  BADFREQUENCY           = 182;   { Invalid frequency specified. }
  BADEVENTPARAM          = 183;   { Invalid event parameter specified. }
  NONETIFC               = 184;    { No interface devices were found with required PAN ID and/or RF Channel. }
  DEADNETIFC             = 185;    { The interface device(s) with required PAN ID and RF Channel has failed. Please check connection. }
  NOREMOTEACK            = 186;    { The remote device is not responding to commands and queries. Please check device. }
  INPUTTIMEOUT           = 187;    { The device acknowledged the operation, but has not completed before the timeout. }
  MISMATCHSETPOINTCOUNT	 = 188;	   { Number of Setpoints not equal to number of channels with setpoint flag set. }
  INVALIDSETPOINTLEVEL	 = 189;	   { Setpoint Level is outside channel range. }
  INVALIDSETPOINTOUTPUTTYPE  = 190;   { Setpoint Output Type is invalid. }
  INVALIDSETPOINTOUTPUTVALUE = 	191;  { Setpoint Output Value is outside channel range. }
  INVALIDSETPOINTLIMITS	= 192;	      { Setpoint Comparison limit B greater than Limit A. }
  NOEXTPOWER = 196;	           { External power is not connected. }
  BADDUTYCYCLE = 197;	       { Invalid duty cycle specified. }
  BADINITIALDELAY = 199;       { Invalid initial delay specified. }
  NOTEDSSENSOR = 1000;         { No TEDS sensor was detected on the specified channel. }
  INVALIDTEDSSENSOR = 1001;    { Connected TEDS sensor to the specified channel is not supported. }
  CALIBRATIONFAILED = 1002;    { Calibration failed. }
  BITUSEDFORTERMINALCOUNTSTATUS = 1003;     { The specified bit is used for terminal count stauts. }
  PORTUSEDFORTERMINALCOUNTSTATUS = 1004;    { One or more bits on the specified port are used for terminal count stauts.}
  BADEXCITATION = 1005;    { Invalid excitation specified }
  BADBRIDGETYPE = 1006;    { Invalid bridge type specified. }
  BADLOADVAL = 1007;     { Invalid load value specified. }
  BADTICKSIZE = 1008;    { Invalid tick size specified. }



  INTERNALERR           = 200;   { 200-299 = 16 bit library internal error  }
  CANT_LOCK_DMA_BUF     = 201;   { DMA buffer could not be locked }
  DMA_IN_USE            = 202;   { DMA already controlled by another device }
  BAD_MEM_HANDLE        = 203;    { Invalid Windows memory handle }


  INTERNALERR32            = 300;  { 300-399 = 32 bit library internal error  }
  CFG_FILE_READ_FAILURE    = 304;  { Error reading from configuration file }
  CFG_FILE_WRITE_FAILURE   = 305; { Error writing to configuration file }
  CFGFILE_CANT_OPEN        = 308;  { Cannot open configuration file }
  BAD_RTD_CONVERSION       = 325;  { Overflow of RTD conversion }
  NO_PCI_BIOS              = 326;  { PCI BIOS not present on the PC }
  BAD_PCI_INDEX            = 327;  { Specified PCI board not detected }
  NO_PCI_BOARD             = 328;  { Specified PCI board not detected }
  CANT_INSTALL_INT         = 334;  { Cannot install interrupt handler. IRQ already in use }
  NO_USB_BOARD             = 343;  { Specified USB board not detected }

  PCMCIAERRS               = 400;  { 400-499 = PCMCIA errors }
                                                                

{ These are the commonly occurring remapped DOS error codes }
  DOSBADFUNC            = 501;
  DOSFILENOTFOUND       = 502;
  DOSPATHNOTFOUND       = 503;
  DOSNOHANDLES          = 504;
  DOSACCESSDENIED       = 505;
  DOSINVALIDHANDLE      = 506;
  DOSNOMEMORY           = 507;
  DOSBADDRIVE           = 515;
  DOSTOOMANYFILES       = 518;
  DOSWRITEPROTECT       = 519;
  DOSDRIVENOTREADY      = 521;
  DOSSEEKERROR          = 525;
  DOSWRITEFAULT         = 529;
  DOSREADFAULT          = 530;
  DOSGENERALFAULT       = 531;

  WIN_CANNOT_ENABLE_INT     = 603;     { Cannot enable interrupt. IRQ already in use }
  WIN_CANNOT_DISABLE_INT    = 605;     { Cannot disable interrupts }
  WIN_CANT_PAGE_LOCK_BUFFER = 606;     { Insufficient memory to page lock data buffer }
  NO_PCM_CARD               = 630;     { PCM card not detected }



  AIFUNCTION         =1;    { Analog Input Function    }
  AOFUNCTION         =2;    { Analog Output Function   }
  DIFUNCTION         =3;    { Digital Input Function   }
  DOFUNCTION         =4;    { Digital Output Function  }
  CTRFUNCTION        =5;    { Counter Function         }
  DAQIFUNCTION       =6;    { Daq Input Function       }
  DAQOFUNCTION       =7;    { Daq Output Function      }

  NOTUSED          = -1;

{ Maximum length of error string}
  ERRSTRLEN = 256;

{ Maximum length of board name string}
  BOARDNAMELEN = 25;


{ Status values }
  IDLE             = 0;
  RUNNING          = 1;

{ Option Flags }
  FOREGROUND       = $0000;    { Run in foreground, don't return till done }
  BACKGROUND       = $0001;    { Run in background, return immediately }

  SINGLEEXEC       = $0000;    { One execution }
  CONTINUOUS       = $0002;    { Run continuously until cbstop() called }

  TIMED            = $0000;    { Time conversions with internal clock }
  EXTCLOCK         = $0004;    { Time conversions with external clock }

  NOCONVERTDATA    = $0000;    { Return converted data }
  CONVERTDATA      = $0008;    { Return raw A/D data }

  NODTCONNECT      = $0000;    { Disable DT Connect }
  DTCONNECT        = $0010;    { Enable DT Connect }
  SCALEDATA        = $0010;    { Scale scan data to engineering units }

  DEFAULTIO        = $0000;    { Use whatever makes sense for board }
  SINGLEIO         = $0020;    { Interrupt per A/D conversion }
  DMAIO            = $0040;    { DMA transfer }
  BLOCKIO          = $0060;    { Interrupt per block of conversions }
  BURSTIO           = $10000;   { Transfer upon scan completion }
  RETRIGMODE       = $20000;   { Re-arm trigger upon acquiring trigger count samples }
  NONSTREAMEDIO    = $40000;    { Non-streamed D/A output }
  ADCCLOCKTRIG     = $80000;    { Output operation is triggered on ADC clock }
  ADCCLOCK         = $100000;    { Output operation is paced by ADC clock }
  HIGHRESRATE	   = $200000;	 { Use high resolution rate }
  SHUNTCAL         = $400000;    { Enable Shunt Calibration }

  BYTEXFER         = $0000;    { Digital IN/OUT a byte at a time }
  WORDXFER         = $0100;    { Digital IN/OUT a word at a time }

  INDIVIDUAL       = $0000;    { Individual D/A output }
  SIMULTANEOUS     = $0200;    { Simultaneous D/A output }

  FILTER           = $0000;    { Filter the input signal }
  NOFILTER         = $0400;    { Disable input filter }

  NORMMEMORY       = $0000;    { Return data to data array }
  EXTMEMORY        = $0800;    { Send data to memory board via DT-Connect }

  BURSTMODE        = $1000;    { Enable burst mode }

  NOTODINTS        = $2000;    { Disable time of day Interrupts }

  EXTTRIGGER       = $4000;    { A/D is triggered externally }

  NOCALIBRATEDATA  = $8000;    { Return uncalibrated PCM data }
  CALIBRATEDATA    = $0000;    { Return calibrated PCM A/D data }

  CTR16BIT         = $0000;    { Return 16-bit counter data }
  CTR32BIT         = $0100;    { Return 32-bit counter data }
  CTR48BIT         = $0200;    { Return 48-bit counter data }


  ENABLED          = 1;
  DISABLED         = 0;

  CBENABLED    = 1;
  CBDISABLED       = 0;

  UPDATEIMMEDIATE = 0;
  UPDATEONCOMMAND = 1;

{ types of error reporting }
  DONTPRINT        = 0;
  PRINTWARNINGS    = 1;
  PRINTFATAL       = 2;
  PRINTALL         = 3;

{ channel types }
  ANALOG           = 0;        { Analog channel }
  DIGITAL8         = 1;        { 8-bit digital port }
  DIGITAL16        = 2;        { 16-bit digital port }
  CTR16            = 3;        { 16-bit counter }
  CTR32LOW         = 4;        { Lower 16-bits of 32-bit counter }
  CTR32HIGH        = 5;        { Upper 16-bits of 32-bit counter }
  CJC              = 6;        { CJC channel }
  TC               = 7;        { Thermocouple channel }
  ANALOG_SE        = 8;        { Analog channel, singel-ended mode }
  ANALOG_DIFF      = 9;        { Analog channel, Differential mode }
  SETPOINTSTATUS   = 10;       { Setpoint status channel }

{ channel type flags }
  SETPOINT_ENABLE  = $0100;    { Enable setpoint detection }

{ setpoint flags }
  SF_EQUAL_LIMITA          = $0000;   { Channel = LimitA value } 
  SF_LESSTHAN_LIMITA       = $0001;   { Channel < LimitA value }
  SF_INSIDE_LIMITS         = $0002;   { Channel Inside LimitA and LimitB (LimitA < Channel < LimitB) }
  SF_GREATERTHAN_LIMITB    = $0003;   { Channel > LimitB }
  SF_OUTSIDE_LIMITS        = $0004;   { Channel Outside LimitA and LimitB (LimitA < Channel or Channel > LimitB) }
  SF_HYSTERESIS            = $0005;   { Use As Hysteresis }
  SF_UPDATEON_TRUEONLY     = $0000;   { Latch output condition (output = output1 for duration of acquisition) }
  SF_UPDATEON_TRUEANDFALSE = $0008;   { Do not latch output condition (output = output1 when criteria met else output = output2) }
 
{ Setpoint output channels }
  SO_NONE	       = 0; { No Output }
  SO_DIGITALPORT   = 1; { Output to digital port } 
  SO_FIRSTPORTC    = 1; { Output to first PortC }
  SO_DAC0          = 2; { Output to DAC0 }
  SO_DAC1          = 3; { Output to DAC1 }
  SO_DAC2          = 4; { Output to DAC2 }
  SO_DAC3          = 5; { Output to DAC3 }
  SO_TMR0          = 6; { Output to TMR0 }
  SO_TMR1          = 7; { Output to TMR1 }

{ cbDaqSetTrigger trigger sources }
 TRIG_IMMEDIATE    = 0;
 TRIG_EXTTTL       = 1;
 TRIG_ANALOG_HW    = 2;
 TRIG_ANALOG_SW    = 3;
 TRIG_DIGPATTERN   = 4;
 TRIG_COUNTER      = 5;
 TRIG_SCANCOUNT    = 6;

{ cbDaqSetTrigger trigger sensitivities }
 RISING_EDGE       = 0;
 FALLING_EDGE      = 1;
 ABOVE_LEVEL       = 2;
 BELOW_LEVEL       = 3;
 EQ_LEVEL          = 4;
 NE_LEVEL          = 5;

{ trigger events }
 START_EVENT       = 0;
 STOP_EVENT    = 1;

{ Settling time settings }
 SETTLE_DEFAULT = 0;
 SETTLE_1us = 1;
 SETTLE_5us = 2;
 SETTLE_10us = 3;
 SETTLE_1ms = 4;

{ types of error handling }
  DONTSTOP         = 0;
  STOPFATAL        = 1;
  STOPALL          = 2;

{ Types of digital input ports }
  DIGITALOUT       = 1;
  DIGITALIN        = 2;

{ Types of DT Modes for cbMemSetDTMode() }
  DTIN             = 0;
  DTOUT            = 2;

  FROMHERE        = -1;       { Read/Write from current poistion }
  GETFIRST        = -2;       { Get first item in list }
  GETNEXT         = -3;       { Get next item in list }


{ Temperature scales }
  CELSIUS          = 0;
  FAHRENHEIT       = 1;
  KELVIN           = 2;
  VOLTS            = 4;
  NOSCALE          = 5;

{ Default Option flag }
  DEFAULTOPTION    = $0000;


{ Types of digital I/O Ports }
  AUXPORT          = 1;
  FIRSTPORTA       = 10;
  FIRSTPORTB       = 11;
  FIRSTPORTCL      = 12;
  FIRSTPORTCH      = 13;
  SECONDPORTA      = 14;
  SECONDPORTB      = 15;
  SECONDPORTCL     = 16;
  SECONDPORTCH     = 17;
  THIRDPORTA       = 18;
  THIRDPORTB       = 19;
  THIRDPORTCL      = 20;
  THIRDPORTCH      = 21;
  FOURTHPORTA      = 22;
  FOURTHPORTB      = 23;
  FOURTHPORTCL     = 24;
  FOURTHPORTCH     = 25;
  FIFTHPORTA       = 26;
  FIFTHPORTB       = 27;
  FIFTHPORTCL      = 28;
  FIFTHPORTCH      = 29;
  SIXTHPORTA       = 30;
  SIXTHPORTB       = 31;
  SIXTHPORTCL      = 32;
  SIXTHPORTCH      = 33;
  SEVENTHPORTA     = 34;
  SEVENTHPORTB     = 35;
  SEVENTHPORTCL    = 36;
  SEVENTHPORTCH    = 37;
  EIGHTHPORTA      = 38;
  EIGHTHPORTB      = 39;
  EIGHTHPORTCL     = 40;
  EIGHTHPORTCH     = 41;


{ Selectable A/D Ranges codes }
  BIP60VOLTS       = 20;              { -60 to +60 Volts }
  BIP20VOLTS       = 15;              { -20 to +20 Volts }
  BIP15VOLTS       = 21;              { -15 to +15 Volts }
  BIP10VOLTS       = 1;               { -10 to +10 Volts }
  BIP5VOLTS        = 0;               { -5 to +5 Volts }
  BIP4VOLTS        = 16;              { -4 to + 4 Volts }
  BIP2PT5VOLTS     = 2;               { -2.5 to +2.5 Volts }
  BIP2VOLTS        = 14;              { -2.0 to +2.0 Volts }
  BIP1PT25VOLTS    = 3;               { -1.25 to +1.25 Volts }
  BIP1VOLTS        = 4;               { -1 to +1 Volts }
  BIPPT625VOLTS    = 5;               { -.625 to +.625 Volts }
  BIPPT5VOLTS      = 6;               { -.5 to +.5 Volts }
  BIPPT25VOLTS     = 12;              { -0.25 to +0.25 Volts }
  BIPPT2VOLTS      = 13;              { -0.2 to +0.2 Volts }
  BIPPT1VOLTS      = 7;               { -0.1 to +0.1 Volts }
  BIPPT05VOLTS     = 8;               { -0.05 to +0.05 Volts }
  BIPPT01VOLTS     = 9;               { -0.01 to +0.01 Volts }
  BIPPT005VOLTS    = 10;              { -0.005 to +0.005 Volts }
  BIP1PT67VOLTS    = 11;              { -1.67 to +1.67 Volts }
  BIPPT312VOLTS    = 17;              { -0.3125 to +0.3125 Volts }
  BIPPT156VOLTS    = 18;              { -0.15625 to +0.15625 Volts }
  BIPPT125VOLTS    = 22;              { -0.125 to +0.125 Volts }
  BIPPT078VOLTS    = 19;              { -0.078125 to +0.078125 Volts }

  UNI10VOLTS       = 100;             { 0 to 10 Volts }
  UNI5VOLTS        = 101;             { 0 to 5 Volts }
  UNI4VOLTS        = 114;             { 0 to 4 Volts }
  UNI2PT5VOLTS     = 102;             { 0 to 2.5 Volts }
  UNI2VOLTS        = 103;             { 0 to 2 Volts }
  UNI1PT67VOLTS    = 109;             { 0 to 1.67 Volts }
  UNI1PT25VOLTS    = 104;             { 0 to 1.25 Volts }
  UNI1VOLTS        = 105;             { 0 to 1 Volts }
  UNIPT5VOLTS      = 110;             { 0 to 0.5 Volts }
  UINTPT25VOLTS    = 111;             { 0 to 0.25 Volt }
  UNIPT2VOLTS      = 112;             { 0 to 0.2 Volts }
  UNIPT1VOLTS      = 106;             { 0 to 0.1 Volts }
  UNIPT05VOLTS     = 113;             { 0 to 0.05 Volts }
  UNIPT02VOLTS     = 108;             { 0 to 0.02 Volts }
  UNIPT01VOLTS     = 107;             { 0 to 0.01 Volts }

  MA4TO20          = 200;             { 4 to 20 ma }
  MA2TO10          = 201;             { 2 to 10 ma }
  MA1TO5           = 202;             { 1 to 5 ma }
  MAPT5TO2PT5      = 203;             { .5 to 2.5 ma }
  MA0TO20          = 204;             { 0 to 20 ma }
  BIPPT025AMPS     = 205;             { -0.025 to 0.025 ma }

  UNIPOLAR         = 300;             { Unipolar range }
  BIPOLAR          = 301;             { Bipolar range }

  BIPPT025VOLTSPERVOLT = 400;         { -0.025 to +0.025 V/V }


{ Types of D/A    }
  ADDA1     = 0;
  ADDA2     = 1;

{ 8536 counter output 1 control }
  NOTLINKED           = 0;
  GATECTR2            = 1;
  TRIGCTR2            = 2;
  INCTR2              = 3;

{ 8536 trigger types }
  HW_START_TRIG      = 0;
  HW_RETRIG          = 1;
  SW_START_TRIG      = 2;

{ Types of 8254 Counter configurations }
  HIGHONLASTCOUNT     = 0;
  ONESHOT             = 1;
  RATEGENERATOR       = 2;
  SQUAREWAVE          = 3;
  SOFTWARESTROBE      = 4;
  HARDWARESTROBE      = 5;

{ Where to reload from for 9513 counters }
  LOADREG         = 0;
  LOADANDHOLDREG  = 1;

{ Counter recycle modes }
  ONETIME         = 0;
  RECYCLE         = 1;

{ Direction of counting for 9513 counters }
  COUNTDOWN       = 0;
  COUNTUP         = 1;

{ Types of count detection for 9513 counters }
  POSITIVEEDGE    = 0;
  NEGATIVEEDGE    = 1;

{ Counter output control }
  ALWAYSLOW       = 0;    { 9513 }
  HIGHPULSEONTC   = 1;    { 9513 and 8536 }
  TOGGLEONTC      = 2;    { 9513 and 8536 }
  DISCONNECTED    = 4;    { 9513 }
  LOWPULSEONTC    = 5;    { 9513 }
  HIGHUNTILTC     = 6;    { 8536 }

{ Counter input sources }
  TCPREVCTR       = 0;
  CTRINPUT1       = 1;
  CTRINPUT2       = 2;
  CTRINPUT3       = 3;
  CTRINPUT4       = 4;
  CTRINPUT5       = 5;
  GATE1           = 6;
  GATE2           = 7;
  GATE3           = 8;
  GATE4           = 9;
  GATE5           = 10;
  FREQ1           = 11;
  FREQ2           = 12;
  FREQ3           = 13;
  FREQ4           = 14;
  FREQ5           = 15;
  CTRINPUT6       = 101;
  CTRINPUT7       = 102;
  CTRINPUT8       = 103;
  CTRINPUT9       = 104;
  CTRINPUT10      = 105;
  GATE6           = 106;
  GATE7           = 107;
  GATE8           = 108;
  GATE9           = 109;
  GATE10          = 110;
  FREQ6           = 111;
  FREQ7           = 112;
  FREQ8           = 113;
  FREQ9           = 114;
  FREQ10          = 115;
  CTRINPUT11       = 201;
  CTRINPUT12       = 202;
  CTRINPUT13       = 203;
  CTRINPUT14       = 204;
  CTRINPUT15       = 205;
  GATE11           = 206;
  GATE12           = 207;
  GATE13           = 208;
  GATE14           = 209;
  GATE15           = 210;
  FREQ11           = 211;
  FREQ12           = 212;
  FREQ13           = 213;
  FREQ14           = 214;
  FREQ15           = 215;
  CTRINPUT16       = 301;
  CTRINPUT17       = 302;
  CTRINPUT18       = 303;
  CTRINPUT19       = 304;
  CTRINPUT20       = 305;
  GATE16           = 306;
  GATE17           = 307;
  GATE18           = 308;
  GATE19           = 309;
  GATE20           = 310;
  FREQ16           = 311;
  FREQ17           = 312;
  FREQ18           = 313;
  FREQ19           = 314;
  FREQ20           = 315;

{ Counter load registers }
  LOADREG0        = 0;
  LOADREG1        = 1;
  LOADREG2        = 2;
  LOADREG3        = 3;
  LOADREG4        = 4;
  LOADREG5        = 5;
  LOADREG6        = 6;
  LOADREG7        = 7;
  LOADREG8        = 8;
  LOADREG9        = 9;
  LOADREG10       = 10;
  LOADREG11       = 11;
  LOADREG12       = 12;
  LOADREG13       = 13;
  LOADREG14       = 14;
  LOADREG15       = 15;
  LOADREG16       = 16;
  LOADREG17       = 17;
  LOADREG18       = 18;
  LOADREG19       = 19;
  LOADREG20       = 20;

{ 9513 Counter registers }
  HOLDREG1        = 101;
  HOLDREG2        = 102;
  HOLDREG3        = 103;
  HOLDREG4        = 104;
  HOLDREG5        = 105;
  HOLDREG6        = 106;
  HOLDREG7        = 107;
  HOLDREG8        = 108;
  HOLDREG9        = 109;
  HOLDREG10       = 110;
  HOLDREG11       = 111;
  HOLDREG12       = 112;
  HOLDREG13       = 113;
  HOLDREG14       = 114;
  HOLDREG15       = 115;
  HOLDREG16       = 116;
  HOLDREG17       = 117;
  HOLDREG18       = 118;
  HOLDREG19       = 119;
  HOLDREG20       = 120;

  ALARM1CHIP1     = 201;
  ALARM2CHIP1     = 202;
  ALARM1CHIP2     = 301;
  ALARM2CHIP2     = 302;
  ALARM1CHIP3     = 401;
  ALARM2CHIP3     = 402;
  ALARM1CHIP4     = 501;
  ALARM2CHIP4     = 502;

{ LS7266 Counter registers }
  COUNT1 = 601;
  COUNT2 = 602;
  COUNT3 = 603;
  COUNT4 = 604;

  PRESET1 = 701;
  PRESET2 = 702;
  PRESET3 = 703;
  PRESET4 = 704;

  PRESCALER1 = 801;
  PRESCALER2 = 802;
  PRESCALER3 = 803;
  PRESCALER4 = 804;

{  Counter Gate Control }
  NOGATE          = 0;
  AHLTCPREVCTR    = 1;
  AHLNEXTGATE     = 2;
  AHLPREVGATE     = 3;
  AHLGATE         = 4;
  ALLGATE         = 5;
  AHEGATE         = 6;
  ALEGATE         = 7;

{ 7266 Counter Quadrature values }
  NO_QUAD = 0;
  X1_QUAD = 1;
  X2_QUAD = 2;
  X4_QUAD = 4;

{ 7266 Counter Counting Modes }
  NORMAL_MODE = 0;
  RANGE_LIMIT = 1;
  NO_RECYCLE  = 2;
  MODULO_N    = 3;

{ 7266 Counter encodings }
  BCD_ENCODING    = 1;
  BINARY_ENCODING = 2;

{ 7266 Counter Index Modes }
  INDEX_DISABLED = 0;
  LOAD_CTR       = 1;
  LOAD_OUT_LATCH = 2;
  RESET_CTR      = 3;

{ 7266 Counter Flag Pins }
  CARRY_BORROW       = 1;
  COMPARE_BORROW     = 2;
  CARRYBORROW_UPDOWN = 3;
  INDEX_ERROR        = 4;

{ Counter status bits }
  C_UNDERFLOW = $0001;
  C_OVERFLOW  = $0002;
  C_COMPARE   = $0004;
  C_SIGN      = $0008;
  C_ERROR     = $0010;
  C_UP_DOWN   = $0020;
  C_INDEX     = $0040;

{ USB-QUAD08 Counter registers }
  MAXLIMITREG0  = 0;
  MAXLIMITREG1  = 1;
  MAXLIMITREG2  = 2;
  MAXLIMITREG3  = 3;
  MAXLIMITREG4  = 4;
  MAXLIMITREG5  = 5;
  MAXLIMITREG6  = 6;
  MAXLIMITREG7  = 7;

{ 25xx series counter mode constants }
  TOTALIZE        = $0000;
  CLEAR_ON_READ   = $0001;
  ROLLOVER        = $0000;
  STOP_AT_MAX     = $0002;
  DECREMENT_OFF   = $0000;
  DECREMENT_ON    = $0020;
  BIT_16          = $0000;
  BIT_32          = $0004;
  BIT_48          = $10000;
  GATING_OFF      = $0000;
  GATING_ON       = $0010;
  LATCH_ON_SOS    = $0000;
  LATCH_ON_MAP    = $0008;
  UPDOWN_OFF	  = $0000;
  UPDOWN_ON       = $1000;
  RANGE_LIMIT_OFF = $0000;
  RANGE_LIMIT_ON  = $2000;
  NO_RECYCLE_OFF  = $0000;
  NO_RECYCLE_ON	  = $4000;
  MODULO_N_OFF	  = $0000;
  MODULO_N_ON	  = $8000;

  PERIOD                = $0200;
  PERIOD_MODE_X1        = $0000;
  PERIOD_MODE_X10       = $0001;
  PERIOD_MODE_X100      = $0002;
  PERIOD_MODE_X1000     = $0003;
  PERIOD_MODE_BIT_16    = $0000;
  PERIOD_MODE_BIT_32    = $0004;
  PERIOD_MODE_BIT_48    = $10000;
  PERIOD_MODE_GATING_ON = $0010;

  PULSEWIDTH                = $0300;
  PULSEWIDTH_MODE_BIT_16    = $0000;
  PULSEWIDTH_MODE_BIT_32    = $0004;
  PULSEWIDTH_MODE_BIT_48    = $10000;
  PULSEWIDTH_MODE_GATING_ON = $0010;

  TIMING             = $0400;
  TIMING_MODE_BIT_16 = $0000;
  TIMING_MODE_BIT_32 = $0004;
  TIMING_MODE_BIT_48 = $10000;
  
  ENCODER                      = $0500;
  ENCODER_MODE_X1              = $0000;
  ENCODER_MODE_X2              = $0001;
  ENCODER_MODE_X4              = $0002;
  ENCODER_MODE_BIT_16 	       = $0000;
  ENCODER_MODE_BIT_32 	       = $0004;
  ENCODER_MODE_BIT_48          = $10000;
  ENCODER_MODE_LATCH_ON_Z      = $0008;
  ENCODER_MODE_CLEAR_ON_Z_OFF  = $0000;
  ENCODER_MODE_CLEAR_ON_Z_ON   = $0020;
  ENCODER_MODE_RANGE_LIMIT_OFF = $0000;
  ENCODER_MODE_RANGE_LIMIT_ON  = $2000;
  ENCODER_MODE_NO_RECYCLE_OFF  = $0000;
  ENCODER_MODE_NO_RECYCLE_ON   = $4000;
  ENCODER_MODE_MODULO_N_OFF    = $0000;
  ENCODER_MODE_MODULO_N_ON     = $8000;


{ obsolete encoder mode constants, use preferred constants above.}
  LATCH_ON_Z	    = $0008;
  CLEAR_ON_Z_OFF    = $0000;
  CLEAR_ON_Z_ON	    = $0020;

{ 25xx series counter debounce time constants }
  CTR_DEBOUNCE500ns    = 0;
  CTR_DEBOUNCE1500ns   = 1;
  CTR_DEBOUNCE3500ns   = 2;
  CTR_DEBOUNCE7500ns   = 3;
  CTR_DEBOUNCE15500ns  = 4;
  CTR_DEBOUNCE31500ns  = 5;
  CTR_DEBOUNCE63500ns  = 6;   
  CTR_DEBOUNCE127500ns = 7;   
  CTR_DEBOUNCE100us    = 8;
  CTR_DEBOUNCE300us    = 9;
  CTR_DEBOUNCE700us    = 10;
  CTR_DEBOUNCE1500us   = 11;
  CTR_DEBOUNCE3100us   = 12;
  CTR_DEBOUNCE6300us   = 13;
  CTR_DEBOUNCE12700us  = 14;
  CTR_DEBOUNCE25500us  = 15;
  CTR_DEBOUNCE_NONE    = 16;

{ 25xx series counter debounce trigger constants }
  CTR_TRIGGER_AFTER_STABLE  =  0;
  CTR_TRIGGER_BEFORE_STABLE =  1;

{ 25xx series counter edge detection constants }
 CTR_RISING_EDGE   = 0;
 CTR_FALLING_EDGE  = 1;


{ Types of triggers }
  TRIGABOVE       = 0;
  TRIGBELOW       = 1;
  GATENEGHYS      = 2;
  GATEPOSHYS      = 3;
  GATEABOVE       = 4;
  GATEBELOW       = 5;
  GATEINWINDOW    = 6;
  GATEOUTWINDOW   = 7;
  GATEHIGH        = 8;
  GATELOW         = 9;
  TRIGHIGH        = 10;
  TRIGLOW         = 11;
  TRIGPOSEDGE     = 12;
  TRIGNEGEDGE     = 13;

{ Timer idle state }
  IDLE_LOW		  =	0;
  IDLE_HIGH		  = 1;


{ Signal I/O Configuration Parameters }
{ --Connections }
  AUXIN0          = $01;           
  AUXIN1          = $02;
  AUXIN2          = $04;
  AUXIN3          = $08;
  AUXIN4          = $10;
  AUXIN5          = $20;

  AUXOUT0         = $0100;
  AUXOUT1         = $0200;
  AUXOUT2         = $0400;

  DS_CONNECTOR    = $01000;

  MAX_CONNECTIONS = 4;  { maximum number connections per output signal }


{ --Signal Types }
  ADC_CONVERT     = $0001;   
  ADC_GATE        = $0002;   
  ADC_START_TRIG  = $0004;  
  ADC_STOP_TRIG   = $0008;  
  ADC_TB_SRC      = $0010;
  ADC_SCANCLK     = $0020;
  ADC_SSH         = $0040;
  ADC_STARTSCAN   = $0080;
  ADC_SCAN_STOP   = $0100;

  DAC_UPDATE      = $0200;
  DAC_TB_SRC      = $0400;
  DAC_START_TRIG  = $0800;

  SYNC_CLK        = $1000;

  CTR1_CLK        = $2000;
  CTR2_CLK        = $4000;

  DGND          = $8000;

{ -- Signal Direction }
  SIGNAL_IN       = 2;
  SIGNAL_OUT      = 4;

{ -- Signal Polarity }
  INVERTED        = 1;
  NONINVERTED     = 0;

{ Types of configuration information }
  GLOBALINFO    = 1;
  BOARDINFO     = 2;
  DIGITALINFO   = 3;
  CTRINFO       = 4;
  COUNTERINFO   = 4;
  EXPINFO       = 5;
  EXPANSIONINFO = 5;
  MISCINFO      = 6;
  EXPINFOARRAY  = 7;
  MEMINFO       = 8;


{ Types of global configuration information }
  GIVERSION      = 36;
  GINUMBOARDS    = 38;
  GINUMEXPBOARDS = 40;

{ Types of board configuration information }
  BIBASEADR = 0;
  BIBOARDTYPE = 1;
  BIINTLEVEL = 2;
  BIDMACHAN = 3;
  BIINITIALIZED = 4;
  BICLOCK = 5;
  BIRANGE = 6;
  BINUMADCHANS = 7;
  BIUSESEXPS = 8;
  BIDINUMDEVS = 9;
  BIDIDEVNUM = 10;
  BICINUMDEVS = 11;
  BICIDEVNUM = 12;
  BINUMDACHANS = 13;
  BIWAITSTATE = 14;
  BINUMIOPORTS = 15;
  BIPARENTBOARD = 16;
  BIDTBOARD = 17;
  BINUMEXPS = 18;
  BISERIALNUM = 214;        { Serial Number for USB boards }
  BIDACUPDATEMODE = 215;    { Update immediately or upon BIDACUPDATECMD command }
  BIDACUPDATECMD = 216;     { Issue D/A UPDATE command }
  BIDACSTARTUP = 217;       { Restore last value written for startup } 
  BIADTRIGCOUNT = 219;      { Number of samples to acquire per trigger in retrigger mode }
  BIADFIFOSIZE = 220;       { Set FIFO override size for retrigger mode }
  BIADSOURCE = 221;         { Set A/D source to internal reference(>=0) or external connector(-1) }
  BICALOUTPUT  = 222;       { CAL output pin setting }
  BISRCADPACER = 223;       { Source A/D Pacer output } 
  BIDIALARMMASK = 224;

  BINETIOTIMEOUT = 247;

  BIDIDEBOUNCESTATE = 255;
  BIDIDEBOUNCETIME = 256;     { Digital inputs debounce Time }

  BIPANID = 258;
  BIRFCHANNEL = 259;

  BIRSS = 261;
  BINODEID = 262;
  BIDEVNOTES = 263;

  BIADCSETTLETIME = 270;  { Set settling time for A/D channels }
  
  BIFACTORYID = 272;
  BIHTTPPORT = 273;
  BIHIDELOGINDLG = 274;
  BIDACTRIGCOUNT = 284;      { Number of samples to generate per trigger in retrigger mode }


{ Types of digital device information }
  DIBASEADR = 0;
  DIINITIALIZED = 1;
  DIDEVTYPE = 2;
  DIMASK = 3;
  DIREADWRITE = 4;
  DICONFIG = 5;
  DINUMBITS = 6;
  DICURVAL = 7;
  DIINMASK = 8;
  DIOUTMASK = 9;

{ Types of counter device information }
  CIBASEADR = 0;
  CIINITIALIZED = 1;
  CICTRTYPE = 2;
  CICTRNUM = 3;
  CICONFIGBYTE = 4;

{ Types of expansion board information }
  XIBOARDTYPE = 0;
  XIMUXADCHAN1 = 1;
  XIMUXADCHAN2 = 2;
  XIRANGE1 = 3;
  XIRANGE2 = 4;
  XICJCCHAN = 5;
  XITHERMTYPE = 6;
  XINUMEXPCHANS = 7;
  XIPARENTBOARD = 8;
  XISPARE0 = 9;

{ Types of Events }
  ON_SCAN_ERROR = $1;
  ON_EXTERNAL_INTERRUPT = $2;
  ON_PRETRIGGER = $4;
  ON_DATA_AVAILABLE = $8;
  ON_END_OF_AI_SCAN =$10;
  ON_END_OF_AO_SCAN = $20;
  ON_CHANGE_DI = $40;
  ALL_EVENT_TYPES = $FFFF;

{ ON_EXTERNAL_INTERRUPT event parameters }
  LATCH_DI = $1;
  LATCH_DO = $2;

{$IFDEF WIN32}
{        32-bit function prototypes }
function cbLoadConfig(CfgFileName:PChar):Integer; stdcall;
function cbSaveConfig(CfgFileName:PChar):Integer; stdcall;
function cbAConvertData (BoardNum:Integer; NumPoints:Longint; var ADData:Word;
                         var ChanTags:Word):Integer; StdCall;
function cbACalibrateData (BoardNum:Integer; var NumPoints:Longint;
                           Gain:Integer; var ADData:Word):Integer; StdCall;
function cbAConvertPretrigData (BoardNum:Integer; PreTrigCount:Longint;
                                TotalCount:Longint; var ADData:Word;
                                var ChanTags:Word):Integer; StdCall;
function cbAIn (BoardNum:Integer; Chan:Integer; Gain:Integer;
                var DataValue:Word):Integer; StdCall;
function cbAIn32 (BoardNum:Integer; Chan:Integer; Gain:Integer;
                var DataValue:Longint; Options:Integer):Integer; StdCall;
function cbAInScan (BoardNum:Integer; LowChan:Integer; HighChan:Integer;
                    Count:Longint; var Rate:Longint; Gain:Integer;
                    MemHandle:Integer; Options:Integer):Integer; StdCall;
function cbALoadQueue (BoardNum:Integer; var ChanArray:SmallInt;
                       var GainArray:SmallInt; NumChans:LongInt):Integer; StdCall;
function cbAOut (BoardNum:Integer; Chan:Integer; Gain:Integer; DataValue:Word)
                 :Integer; StdCall;
function cbAOutScan (BoardNum:Integer; LowChan:Integer; HighChan:Integer;
                     Count:Longint; var Rate:Longint; Gain:Integer;
                     MemHandle:Integer; Options:Integer):Integer; StdCall;
function cbAPretrig (BoardNum:Integer; LowChan:Integer; HighChan:Integer;
                     var PreTrigCount:Longint; var TotalCount:Longint;
                     var Rate:Longint; Gain:Integer; MemHandle:Integer;
                     Options:Integer):Integer; StdCall;
function cbATrig (BoardNum:Integer; Chan:Integer; TrigType:Integer;
                  TrigValue:Word; Gain:Integer; var DataValue:Word)
                  :Integer; StdCall;
function cbC7266Config (BoardNum:Integer; CounterNum:Integer;
                        Quadrature:Integer; CountingMode:Integer;
                        DataEncoding:Integer; IndexMode:Integer;
                        InvertIndex:Integer; FlagPins:Integer;
                        GateEnable:Integer):Integer; StdCall;
function cbC8254Config (BoardNum:Integer; CounterNum:Integer; Config:Integer)
                        :Integer; StdCall;
function cbC9513Config (BoardNum:Integer; CounterNum:Integer;
                        GateControl:Integer; CounterEdge:Integer;
                        CountSource:Integer; SpecialGate:Integer;
                        Reload:Integer; RecycleMode:Integer;
                        BCDMode:Integer; CountDirection:Integer;
                        OutputControl:Integer):Integer; StdCall;
function cbC8536Init (BoardNum:Integer; ChipNum:Integer; Ctr1Output:Integer)
                      :Integer; StdCall;
function cbC8536Config (BoardNum:Integer; CounterNum:Integer;
                        OutputControl:Integer; RecycleMode:Integer;
                        TrigType:Integer):Integer; StdCall;
function cbC9513Init (BoardNum:Integer; ChipNum:Integer; FOutDivider:Integer;
                      FOutSource:Integer; Compare1:Integer; Compare2:Integer;
                      TimeOfDay:Integer):Integer; StdCall;
function cbCFreqIn (BoardNum:Integer; SigSource:Integer; GateInterval:Integer;
                    var Count:Word; var Freq:Longint):Integer; StdCall;
function cbCIn (BoardNum:Integer; CounterNum:Integer; var Count:Word)
                :Integer; StdCall;
function cbCIn32 (BoardNum:Integer; CounterNum:Integer; var Count:Longint)
                :Integer; StdCall;
function cbCLoad (BoardNum:Integer; RegNum:Integer; LoadValue:Word)
                  :Integer; StdCall;
function cbCLoad32 (BoardNum:Integer; RegNum:Integer; LoadValue:Longint)
                  :Integer; StdCall;
function cbCStoreOnInt (BoardNum:Integer; IntCount:Integer;
                        var CntrControl:SmallInt; MemHandle:Integer)
                        :Integer; StdCall;
function cbCStatus (BoardNum:Integer; CounterNum:Integer; var StatusBits:Longint)
                    :Integer; StdCall;
function cbCInScan (BoardNum:Integer; FirstCtr:Integer; LastCtr:Integer;
                    Count:Longint; var Rate:Longint; MemHandle:Integer; 
                    Options:Integer):Integer; StdCall;
function cbCConfigScan (BoardNum:Integer; CounterNum:Integer; Mode:Integer;
                        DebounceTime:Integer; DebounceMode:Integer; 
                        EdgeDetection:Integer; TickSize:Integer; MappedChannel:Integer)
                        :Integer; StdCall;
function cbCClear (BoardNum:Integer; CounterNum:Integer):Integer; StdCall;
function cbTimerOutStart (BoardNum:Integer; TimerNum:Integer; var Frequency:Double)
                        :Integer; StdCall;
function cbTimerOutStop (BoardNum:Integer; TimerNum:Integer ):Integer; StdCall;
function cbPulseOutStart (BoardNum:Integer; TimerNum:Integer; var Frequency:Double;
			 var DutyCycle:Double; PulseCount:Longint; var InitialDelay:Double;
			 IdleState:Integer; Options:Integer):Integer; StdCall;
function cbPulseOutStop (BoardNum:Integer; TimerNum:Integer ):Integer; StdCall;


{*****************************************************************************
   Legacy Function Prototypes: to revert to legacy calls, un-comment the
          prototypes immediately below.
}
{      function cbDBitIn (BoardNum:Integer; PortType:Integer; BitNum:Integer;
                  var BitValue:SmallInt):Integer; StdCall; }
{      function cbDBitOut (BoardNum:Integer; PortType:Integer; BitNum:Integer;
                    BitValue:Integer):Integer; StdCall; }

{ Remove the following if using the above legacy function prototypes. }
function cbDBitIn (BoardNum:Integer; PortType:Integer; BitNum:Integer;
                   var BitValue:Word):Integer; StdCall;
function cbDBitOut (BoardNum:Integer; PortType:Integer; BitNum:Integer;
                    BitValue:Word):Integer; StdCall;
{****************************************************************************}

function cbDConfigPort (Boardnum:Integer; PortNum:Integer; Direction:Integer)
                        :Integer; StdCall;
function cbDConfigBit (Boardnum:Integer; PortNum:Integer; BitNum:Integer; Direction:Integer)
                        :Integer; StdCall;
function cbDeclareRevision (var RevNum:Single):Integer; StdCall;
function cbDIn (BoardNum:Integer; PortNum:Integer; var DataValue:Word)
                :Integer; StdCall;
function cbDInScan (BoardNum:Integer; PortNum:Integer; Count:Longint;
                    var Rate:Longint; MemHandle:Integer; Options:Integer)
                    :Integer; StdCall;
function cbDOut (BoardNum:Integer; PortNum:Integer; DataValue:Word)
                 :Integer; StdCall;
function cbDOutScan (BoardNum:Integer; PortNum:Integer; Count:Longint;
                     var Rate:Longint; MemHandle:Integer; Options:Integer)
                     :Integer; StdCall;
function cbErrHandling (ErrReporting:Integer; ErrHandling:Integer)
                        :Integer; StdCall;
function cbFileAInScan (BoardNum:Integer; LowChan:Integer; HighChan:Integer;
                        Count:Longint; var Rate:Longint; Gain:Integer;
                        FileName:PChar; Options:Integer):Integer; StdCall;
function cbFileGetInfo (FileName:PChar; var LowChan:SmallInt;
                        var HighChan:SmallInt; var PreTrigCount:Longint;
                        var TotalCount:Longint; var Rate:Longint;
                        var Gain:LongInt):Integer; StdCall;
function cbFilePretrig (BoardNum:Integer; LowChan:Integer; HighChan:Integer;
                        var PreTrigCount:Longint; var TotalCount:Longint;
                        var Rate:Longint; Gain:Integer;
                        FileName:PChar; Options:Integer):Integer; StdCall;
function cbFileRead (FileName:PChar; FirstPoint:Longint; var NumPoints:Longint;
                     var DataBuffer:Word):Integer; StdCall;
function cbFlashLED (BoardNum:Integer):Integer; StdCall;
function cbGetErrMsg (ErrCode:Integer; ErrMsg:PChar):Integer; StdCall;
function cbGetRevision (var DLLRevNum:Single; var VXDRevNum:Single)
                        :Integer; StdCall;
{*****************************************************************************
   Legacy Function Prototypes: to revert to legacy calls, un-comment the
          prototypes immediately below.
}
{      function cbGetStatus (BoardNum:Integer; var Status:SmallInt;
                      var CurCount:Longint; var CurIndex:Longint)
                      :Integer; StdCall; }

{      function cbStopBackground (BoardNum:Integer):Integer; StdCall; }

{ Remove the following if using the above legacy function prototypes. }
function cbGetStatus (BoardNum:Integer; var Status:SmallInt;
                      var CurCount:Longint; var CurIndex:Longint;FunctionType:Integer)
                      :Integer; StdCall;
function cbStopBackground (BoardNum:Integer;FunctionType:Integer):Integer; StdCall;
{****************************************************************************}

function cbRS485 (BoardNum:Integer; Transmit:Integer; Receive:Integer)
                  :Integer; StdCall;

function cbTIn (BoardNum:Integer; Chan:Integer; Scale:Integer;
                var TempValue:Single; Options:Integer):Integer; StdCall;
function cbTInScan (BoardNum:Integer; LowChan:Integer; HighChan:Integer;
                    Scale:Integer; var DataBuffer:Single; Options:Integer)
                    :Integer; StdCall;
function cbMemSetDTMode (BoardNum:Integer; Mode:Integer):Integer; StdCall;
function cbMemReset (BoardNum:Integer):Integer; StdCall;
function cbMemRead (BoardNum:Integer; var DataBuffer:Word; FirstPoint:Longint;
                    Count:Longint):Integer; StdCall;
function cbMemWrite (BoardNum:Integer; var DataBuffer:Word; FirstPoint:Longint;
                     Count:Longint):Integer; StdCall;
function cbMemReadPretrig (BoardNum:Integer; var DataBuffer:Word;
                           FirstPoint:Longint; Count:Longint):Integer; StdCall;
function cbInByte (BoardNum:Integer; PortNum:Integer):Integer; StdCall;
function cbOutByte (BoardNum:Integer; PortNum:Integer; PortVal:Integer)
                    :Integer; StdCall;
function cbInWord (BoardNum:Integer; PortNum:Integer):Integer; StdCall;
function cbOutWord (BoardNum:Integer; PortNum:Integer; PortVal:Integer)
                    :Integer; StdCall;
{*****************************************************************************
   Legacy Function Prototypes: to revert to legacy calls, un-comment the
          prototypes immediately below.
}
{      function cbGetConfig (InfoType:Integer; BoardNum:Integer; DevNum:Integer;
                  ConfigItem:Integer; var ConfigVal:SmallInt):Integer; StdCall; }

{ Remove the following if using the above legacy function prototypes. }
function cbGetConfig (InfoType:Integer; BoardNum:Integer; DevNum:Integer;
                    ConfigItem:Integer; var ConfigVal:Integer):Integer; StdCall;
{****************************************************************************}

function cbGetConfigString (InfoType:Integer; BoardNum:Integer; DevNum:Integer;
                            ConfigItem:Integer; ConfigVal:PChar; 
                            var maxConfigLen:Integer):Integer; StdCall;


function cbSetConfig (InfoType:Integer; BoardNum:Integer; DevNum:Integer;
                      ConfigItem:Integer; ConfigVal:Integer):Integer; StdCall;

function cbSetConfigString (InfoType:Integer; BoardNum:Integer; DevNum:Integer;
                            ConfigItem:Integer; ConfigVal:PChar; 
                            var ConfigLen:Integer):Integer; StdCall;

function cbToEngUnits (BoardNum:Integer; Range:Integer; DataVal:Word;
                       var EngUnits:Single):Integer; StdCall;
function cbToEngUnits32 (BoardNum:Integer; Range:Integer; DataVal:LongInt;
                       var EngUnits:Double):Integer; StdCall;
function cbFromEngUnits (BoardNum:Integer; Range:Integer; EngUnits:Single;
                         var DataVal:Word):Integer; StdCall;
function cbGetBoardName (BoardNum:Integer; BoardName:PChar):Integer; StdCall;
function cbWinBufToArray (MemHandle:Integer; var ADData:Word;
                          FirstPoint:Longint; Count:Longint):Integer; StdCall;
function cbWinBufToArray32 (MemHandle:Integer; var ADData:LongInt;
                          FirstPoint:Longint; Count:Longint):Integer; StdCall;

function cbScaledWinBufAlloc (NumPoints:Longint):Integer; StdCall;
function cbScaledWinBufToArray (MemHandle:Integer; var ADData:Double;
                          FirstPoint:Longint; Count:Longint):Integer; StdCall;

function cbWinArrayToBuf (var ADData:Word; MemHandle:Integer;
                          FirstPoint:Longint; Count:Longint):Integer; StdCall;
function cbScaledWinArrayToBuf (var ADData:Double; MemHandle:Integer;
                          FirstPoint:Longint; Count:Longint):Integer; StdCall;
function cbWinBufAlloc (NumPoints:Longint):Integer; StdCall;
function cbWinBufFree (MemHandle:Integer):Integer; StdCall;
function cbWinBufAlloc32 (NumPoints:Longint):Integer; StdCall;
function cbWinBufAlloc64 (NumPoints:Longint):Integer; StdCall;

{*****************************************************************************
   Legacy Function Prototypes: to revert to legacy calls, un-comment the
          prototypes immediately below.
}
{      function cbSetTrigger (BoardNum:Integer; TrigType:Integer; LowThreshold:Integer;
                       HighThreshold:Integer):Integer; StdCall; }

{ Remove the following if using the above legacy function prototypes. }
function cbSetTrigger (BoardNum:Integer; TrigType:Integer; LowThreshold:Word;
                       HighThreshold:Word):Integer; StdCall;
{****************************************************************************}

function cbEnableEvent(BoardNum:Integer; EventType:LongInt; EventSize:LongInt;  
                        Callback:Pointer; UserData:Pointer):Integer; StdCall;
function cbDisableEvent(BoardNum:Integer; EventType:LongInt):Integer; StdCall;

function cbSelectSignal(BoardNum:Integer; Direction:LongInt; Signal:LongInt; 
                  Connection:LongInt; Polarity:LongInt):Integer;StdCall;
function cbGetSignal(BoardNum:Integer; Direction:LongInt; Signal:LongInt; 
         Index:LongInt; var Connection:LongInt; var Polarity:LongInt)
         :Integer;StdCall;

function cbLogSetPreferences(timeFormat:Integer; timeZone:Integer; units:Integer):Integer; StdCall;
function cbLogGetPreferences(var timeFormat:Integer; var timeZone:Integer; var units:Integer):Integer; StdCall;
function cbLogGetFileName(fileNumber:Integer; var path:Byte; var filename:Byte):Integer; StdCall;
function cbLogGetFileInfo(var filename:Byte; var version:Integer; var fileSize:Integer):Integer ; StdCall;
function cbLogGetSampleInfo(var filename:Byte; var sampleInterval:Integer; var sampleCount:Integer;
                            var startDate:Integer; var startTime:Integer):Integer; StdCall;
function cbLogGetAIChannelCount(var filename:Byte; var aiCount:Integer):Integer; StdCall;
function cbLogGetAIInfo(var filename:Byte; var channelMask:Integer; var unitMask:Integer; var aiCount:Integer):Integer; StdCall;
function cbLogGetCJCInfo(var filename:Byte; var cjcCount:Integer):Integer; StdCall;
function cbLogGetDIOInfo(var filename:Byte; var dioCount:Integer):Integer; StdCall;
function cbLogReadTimeTags(var filename:Byte; startSample:Integer; count:Integer; var dateTags:Integer;
                           var timeTags:Integer):Integer; StdCall;
function cbLogReadAIChannels(var filename:Byte; startSample:Integer; count:Integer; var analog:Single):Integer; StdCall;
function cbLogReadCJCChannels(var filename:Byte; startSample:Integer; count:Integer; var cjc:Single):Integer; StdCall;
function cbLogReadDIOChannels(var filename:Byte; startSample:Integer; count:Integer; var dio:Integer):Integer; StdCall;
function cbLogConvertFile(var srcFilename:Byte; destFilename:Byte; startSample:Integer; count:Integer; delimiter:Integer):Integer; StdCall;


function cbDaqInScan(BoardNum:Integer; var ChanArray:SmallInt; var ChanTypeArray:SmallInt;
             var GainArray:SmallInt; ChanCount:Integer; var Rate:LongInt;
             var PretrigCount:LongInt; var TotalCount:LongInt; MemHandle:Integer;
             Options:Integer):Integer;StdCall;
function cbDaqSetTrigger(BoardNum:Integer; TrigSource:Integer; TrigSense:Integer; 
             TrigChan:Integer; ChanType:Integer; Gain:Integer; Level:Single;
                         Variance:Single; TrigEvent:Integer):Integer;StdCall;
function cbDaqSetSetpoints (BoardNum:Integer; var LimitAArray:Single; var LimitBArray:Single;
	     var Reserved:Single; var SetpointFlagsArray:Integer; var SetpointOutputArray:Integer;
	     var Output1Array:Single; var Output2Array:Single; var OutputMask1Array:Single;
             var OutputMask2Array:Single; SetpointCount:Integer):Integer;StdCall;
function cbDaqOutScan(BoardNum:Integer; var ChanArray:SmallInt; var ChanTypeArray:SmallInt;
              var GainArray:SmallInt; ChanCount:Integer; var Rate:LongInt;
              Count:LongInt; MemHandle:Integer; Options:Integer):Integer;StdCall;
function cbGetTCValues(BoardNum:Integer;  var ChanArray:SmallInt; var ChanTypeArray:SmallInt;
               ChanCount:Integer; MemHandle:Integer; FirstPoint:Integer; Count:LongInt;
                       Scale:Integer; var TempValArray:Single):Integer;StdCall;

function cbVIn (BoardNum:Integer; Chan:Integer; Gain:Integer;
                var DataValue:Single;Options:Integer):Integer; StdCall;

function cbVIn32 (BoardNum:Integer; Chan:Integer; Gain:Integer;
                var DataValue:Double;Options:Integer):Integer; StdCall;

function cbVOut (BoardNum:Integer; Chan:Integer; Gain:Integer;
                 DataValue:Single; Options:Integer):Integer; StdCall;

function cbDeviceLogin(BoardNum:Integer; AccountName:PChar; Password:PChar):Integer; StdCall;
function cbDeviceLogout(BoardNum: Integer):Integer; StdCall;

function cbTEDSRead(BoardNum:Integer; Chan:Integer; var DataBuffer:Byte; var Count:Longint;
		 Options:Integer):Integer; StdCall;


{$ENDIF} {WIN32}

{***************************************************************************}

implementation
{$IFDEF WIN32}
{        32-bit function prototypes }
function cbLoadConfig; external 'CBW32.DLL';
function cbSaveConfig; external 'CBW32.DLL';
function cbAConvertData; external 'CBW32.DLL';
function cbACalibrateData; external 'CBW32.DLL';
function cbAConvertPretrigData; external 'CBW32.DLL';
function cbAIn; external 'CBW32.DLL';
function cbAIn32; external 'CBW32.DLL';
function cbAInScan; external 'CBW32.DLL';
function cbALoadQueue; external 'CBW32.DLL';
function cbAOut; external 'CBW32.DLL';
function cbAOutScan; external 'CBW32.DLL';
function cbAPretrig; external 'CBW32.DLL';
function cbATrig; external 'CBW32.DLL';
function cbC7266Config; external 'CBW32.DLL';
function cbC8254Config; external 'CBW32.DLL';
function cbC9513Config; external 'CBW32.DLL';
function cbC8536Init; external 'CBW32.DLL';
function cbC8536Config; external 'CBW32.DLL';
function cbC9513Init; external 'CBW32.DLL';
function cbCFreqIn; external 'CBW32.DLL';
function cbCIn; external 'CBW32.DLL';
function cbCIn32; external 'CBW32.DLL';
function cbCLoad; external 'CBW32.DLL';
function cbCLoad32; external 'CBW32.DLL';
function cbCStatus; external 'CBW32.DLL';
function cbCStoreOnInt; external 'CBW32.DLL';
function cbCInScan; external 'CBW32.DLL';
function cbCConfigScan; external 'CBW32.DLL';
function cbCClear; external 'CBW32.DLL'; 
function cbTimerOutStart; external 'CBW32.DLL'; 
function cbTimerOutStop; external 'CBW32.DLL'; 
function cbPulseOutStart; external 'CBW32.DLL'; 
function cbPulseOutStop; external 'CBW32.DLL'; 
function cbDBitIn; external 'CBW32.DLL';
function cbDBitOut; external 'CBW32.DLL';
function cbDConfigPort; external 'CBW32.DLL';
function cbDConfigBit; external 'CBW32.DLL';
function cbDeclareRevision; external 'CBW32.DLL';
function cbDIn; external 'CBW32.DLL';
function cbDInScan; external 'CBW32.DLL';
function cbDOut; external 'CBW32.DLL';
function cbDOutScan; external 'CBW32.DLL';
function cbErrHandling; external 'CBW32.DLL';
function cbFileAInScan; external 'CBW32.DLL';
function cbFileGetInfo; external 'CBW32.DLL';
function cbFilePretrig; external 'CBW32.DLL';
function cbFileRead; external 'CBW32.DLL';
function cbFlashLED; external 'CBW32.DLL';
function cbGetErrMsg; external 'CBW32.DLL';

{*****************************************************************************
   Legacy Function Prototypes: to revert to legacy calls, un-comment the
          prototypes immediately below.
}
{      function cbGetStatus; external 'CBW32.DLL'; }
{      function cbStopBackground; external 'CBW32.DLL' }     

{ Remove the following if using the above legacy function prototypes. }         
function cbGetStatus; external 'CBW32.DLL' name 'cbGetIOStatus';
function cbStopBackground; external 'CBW32.DLL' name 'cbStopIOBackground';
{*****************************************************************************
}

function cbRS485; external 'CBW32.DLL';
function cbTIn; external 'CBW32.DLL';
function cbTInScan; external 'CBW32.DLL';
function cbMemSetDTMode; external 'CBW32.DLL';
function cbMemReset; external 'CBW32.DLL';
function cbMemRead; external 'CBW32.DLL';
function cbMemWrite; external 'CBW32.DLL';
function cbMemReadPretrig; external 'CBW32.DLL';
function cbInByte; external 'CBW32.DLL';
function cbOutByte; external 'CBW32.DLL';
function cbInWord; external 'CBW32.DLL';
function cbOutWord; external 'CBW32.DLL';
function cbGetConfig; external 'CBW32.DLL';
function cbGetConfigString; external 'CBW32.DLL';
function cbGetRevision; external 'CBW32.DLL';
function cbSetConfig; external 'CBW32.DLL';
function cbSetConfigString; external 'CBW32.DLL';
function cbToEngUnits; external 'CBW32.DLL';
function cbToEngUnits32; external 'CBW32.DLL';
function cbFromEngUnits; external 'CBW32.DLL';
function cbGetBoardName; external 'CBW32.DLL';
function cbWinBufToArray; external 'CBW32.DLL';
function cbWinBufToArray32; external 'CBW32.DLL';
function cbScaledWinBufAlloc; external 'CBW32.DLL';
function cbScaledWinBufToArray; external 'CBW32.DLL';
function cbWinArrayToBuf; external 'CBW32.DLL';
function cbScaledWinArrayToBuf; external 'CBW32.DLL';
function cbWinBufAlloc; external 'CBW32.DLL';
function cbWinBufFree; external 'CBW32.DLL';
function cbWinBufAlloc32; external 'CBW32.DLL';
function cbWinBufAlloc64; external 'CBW32.DLL';
function cbSetTrigger; external 'CBW32.DLL';
function cbEnableEvent; external 'CBW32.DLL';
function cbDisableEvent; external 'CBW32.DLL';
function cbSelectSignal; external 'CBW32.DLL';
function cbGetSignal; external 'CBW32.DLL';

function cbLogSetPreferences; external 'CBW32.DLL';
function cbLogGetPreferences; external 'CBW32.DLL';
function cbLogGetFileName; external 'CBW32.DLL';
function cbLogGetFileInfo; external 'CBW32.DLL';
function cbLogGetSampleInfo; external 'CBW32.DLL';

function cbLogGetAIChannelCount; external 'CBW32.DLL';
function cbLogGetAIInfo; external 'CBW32.DLL';
function cbLogGetCJCInfo; external 'CBW32.DLL';
function cbLogGetDIOInfo; external 'CBW32.DLL';
function cbLogReadTimeTags; external 'CBW32.DLL';
function cbLogReadAIChannels; external 'CBW32.DLL';
function cbLogReadCJCChannels; external 'CBW32.DLL';
function cbLogReadDIOChannels; external 'CBW32.DLL';
function cbLogConvertFile; external 'CBW32.DLL';

function cbDaqInScan; external 'CBW32.DLL';
function cbDaqSetTrigger; external 'CBW32.DLL';
function cbDaqSetSetpoints; external 'CBW32.DLL';
function cbDaqOutScan; external 'CBW32.DLL';
function cbGetTCValues; external 'CBW32.DLL';

function cbVIn; external 'CBW32.DLL';
function cbVIn32; external 'CBW32.DLL';
function cbVOut; external 'CBW32.DLL';

function cbDeviceLogin; external 'CBW32.DLL'
function cbDeviceLogout; external 'CBW32.DLL'
function cbTEDSRead; external 'CBW32.DLL'


{$ENDIF} {WIN32}
end.

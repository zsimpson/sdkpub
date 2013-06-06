// CHeader.h : definition of WinX/32 (CSMA-style) file header
//
// Copyright (C) 1997-2000 Roper Scientific
// All rights reserved
/////////////////////////////////////////////////////////////////////////////
//   This revision:  $Revision: 20 $
//   Last check-in   $Date: 2/06/03 3:36p $
//   Last changes by $Author: Hgrannis $
//   Changes:
/*   $Log: /WinX32 V2.5/INCLUDE/cheader.h $
*  
*  20    2/06/03 3:36p Hgrannis
*  File header 2.2 additions.
*  
*  19    7/25/02 3:22p Hgrannis
*  Added some AvGain.
*  
*  18    7/14/00 3:39p Terry
*  Put back "noscan" and "scramble" for 2.4 compatability
*  
*  17    7/05/00 10:34a Terry
*  Expand some pulser comments
*  
*  16    6/23/00 2:28p Terry
*  Add SpecSlitPosUnits & SpecGrooves
*  
*  15    6/21/00 8:06a Terry
*  Add new controllers to "CSMA" list; Add more members to header struct
*  
*  14    6/01/00 2:48p Terry
*  Cleanup file header, add new stuff
*  
*  13    5/19/00 7:29a Terry
*  Add pulse file name & single width/delay to header
*  
*/
/////////////////////////////////////////////////////////////////////////////

#if !defined(CHEADER_H)
#define CHEADER_H  /* define shows that include is now done */

#include "bvstruct.h"

/* NOTE: the following values should not change, otherwise the header will */
/* be bleeped up.                                                          */
#define HDRNAMEMAX 120     /* max char str length for file name            */
#define USERINFOMAX 1000   /* user information space.                      */
#define COMMENTMAX 80      /* User comment string max length (5 comments)  */
#define LABELMAX 16        /* Label string max length.                     */
#define FILEVERMAX 16      /* File version string max length.              */
#define DATEMAX 10         /* string length of file creation date string as ddmmmyyyy\0 */
#define ROIMAX 10          /* Max size of roi array of structures.         */
#define TIMEMAX 7          /* Max time store as hhmmss\0                   */

#define HEADER_VERSION  2.2

enum CSCTRLTYPE {
  C_UNKNOWN         =  -1,
  C_ST1000          =  0,
  C_ST120NEW        =  1,
  C_ST120OLD        =  2,
  C_ST130           =  3,
  C_ST121           =  4,
  C_ST138           =  5,
  C_DC131           =  6,
  C_ST133           =  7,
  C_ST135           =  8,
  C_VICCD           =  9,
  C_ST116           = 10,
  C_OMA3            = 11,
  C_OMA4            = 12,
  C_ST143           = 13,
  C_VICCDBOX        = 14,
  C_MICROMAX        = 15,
  C_SPECTROMAX      = 16,
  C_MICROVIEW       = 17,
  C_LOW_COST_SPEC   = 18,
  C_ST133_5MHZ      = 19,
  C_EMPTY_5MHZ      = 20,
  C_EPIX_CONTROLLER = 21,
  C_PVCAM           = 22,
  C_GENERIC         = 23
};

#pragma pack(1)

typedef struct tagROIinfo       // ROI information
{
  WORD  startx;                 // left x start value.
  WORD  endx;                   // right x value.
  WORD  groupx;                 // amount x is binned/grouped in hw.
  WORD  starty;                 // top y start value.
  WORD  endy;                   // bottom y value.
  WORD  groupy;                 // amount y is binned/grouped in hw.
} ROIinfo;                      // 12 Bytes Each

typedef struct tagCSMAHEAD {
#ifdef __cplusplus                // STARTING
  tagCSMAHEAD();                  // ADDRESS
#endif                            // (decimal)
  SHORT   ControllerVersion;      //    0  Hardware Version
  SHORT   LogicOutput;            //    2  Definition of Output BNC
  WORD    AmpHiCapLowNoise;       //    4  Amp Switching Mode
  WORD    xDimDet;                //    6  Detector x dimension of chip.
  SHORT   mode;                   //    8  timing mode
  float   exp_sec;                //   10  alternitive exposure, in sec.
  SHORT   VChipXdim;              //   14  Virtual Chip X dim
  SHORT   VChipYdim;              //   16  Virtual Chip Y dim
  WORD    yDimDet;                //   18  y dimension of CCD or detector.
  char    date[DATEMAX];          //   20  date
  SHORT   VirtualChipFlag;        //   30  On/Off
  char    Spare_1[2];             //   32
  SHORT   noscan;                 //   34  Old number of scans - should always be -1
  float   DetTemperature;         //   36  Detector Temperature Set
  SHORT   DetType;                //   40  CCD/DiodeArray type
  WORD    xdim;                   //   42  actual # of pixels on x axis
  SHORT   stdiode;                //   44  trigger diode
  float   DelayTime;              //   46  Used with Async Mode
  WORD    ShutterControl;         //   50  Normal, Disabled Open, Disabled Closed
  SHORT   AbsorbLive;             //   52  On/Off
  WORD    AbsorbMode;             //   54  Reference Strip or File
  SHORT   CanDoVirtualChipFlag;   //   56  T/F Cont/Chip able to do Virtual Chip
  SHORT   ThresholdMinLive;       //   58  On/Off
  float   ThresholdMinVal;        //   60  Threshold Minimum Value
  SHORT   ThresholdMaxLive;       //   64  On/Off
  float   ThresholdMaxVal;        //   66  Threshold Maximum Value
  SHORT   SpecAutoSpectroMode;    //   70  T/F Spectrograph Used
  float   SpecCenterWlNm;         //   72  Center Wavelength in Nm
  SHORT   SpecGlueFlag;           //   76  T/F File is Glued
  float   SpecGlueStartWlNm;      //   78  Starting Wavelength in Nm
  float   SpecGlueEndWlNm;        //   82  Starting Wavelength in Nm
  float   SpecGlueMinOvrlpNm;     //   86  Minimum Overlap in Nm
  float   SpecGlueFinalResNm;     //   90  Final Resolution in Nm
  SHORT   PulserType;             //   94  0=None, PG200=1, PTG=2, DG535=3
  SHORT   CustomChipFlag;         //   96  T/F Custom Chip Used
  SHORT   XPrePixels;             //   98  Pre Pixels in X direction
  SHORT   XPostPixels;            //  100  Post Pixels in X direction
  SHORT   YPrePixels;             //  102  Pre Pixels in Y direction 
  SHORT   YPostPixels;            //  104  Post Pixels in Y direction
  SHORT   asynen;                 //  106  asynchron enable flag  0 = off
  SHORT   datatype;               //  108  experiment datatype
                                  //       0 =   FLOATING POINT
                                  //       1 =   LONG INTEGER
                                  //       2 =   INTEGER
                                  //       3 =   UNSIGNED INTEGER
  SHORT   PulserMode;             //  110  Repetitive/Sequential
  USHORT  PulserOnChipAccums;     //  112  Num PTG On-Chip Accums
  DWORD   PulserRepeatExp;        //  114  Num Exp Repeats (Pulser SW Accum)
  float   PulseRepWidth;          //  118  Width Value for Repetitive pulse (usec)
  float   PulseRepDelay;          //  122  Width Value for Repetitive pulse (usec)
  float   PulseSeqStartWidth;     //  126  Start Width for Sequential pulse (usec)
  float   PulseSeqEndWidth;       //  130  End Width for Sequential pulse (usec)
  float   PulseSeqStartDelay;     //  134  Start Delay for Sequential pulse (usec)
  float   PulseSeqEndDelay;       //  138  End Delay for Sequential pulse (usec)
  SHORT   PulseSeqIncMode;        //  142  Increments: 1=Fixed, 2=Exponential
  SHORT   PImaxUsed;              //  144  PI-Max type controller flag
  SHORT   PImaxMode;              //  146  PI-Max mode
  SHORT   PImaxGain;              //  148  PI-Max Gain
  SHORT   BackGrndApplied;        //  150  1 if background subtraction done
  SHORT   PImax2nsBrdUsed;        //  152  T/F PI-Max 2ns Board Used
  WORD    minblk;                 //  154  min. # of strips per skips
  WORD    numminblk;              //  156  # of min-blocks before geo skps
  SHORT   SpecMirrorLocation[2];  //  158  Spectro Mirror Location, 0=Not Present
  SHORT   SpecSlitLocation[4];    //  162  Spectro Slit Location, 0=Not Present
  SHORT   CustomTimingFlag;       //  170  T/F Custom Timing Used
  char    ExperimentTimeLocal[TIMEMAX];//  172  Experiment Local Time as hhmmss\0
  char    ExperimentTimeUTC[TIMEMAX];  //  179  Experiment UTC Time as hhmmss\0
  SHORT   ExposUnits;             //  186  User Units for Exposure
  WORD    ADCoffset;              //  188  ADC offset
  WORD    ADCrate;                //  190  ADC rate
  WORD    ADCtype;                //  192  ADC type
  WORD    ADCresolution;          //  194  ADC resolution
  WORD    ADCbitAdjust;           //  196  ADC bit adjust
  WORD    gain;                   //  198  gain
  char    Comments[5][COMMENTMAX];//  200  File Comments
  WORD    geometric;              //  600  geometric ops: rotate 0x01,
                                  //       reverse 0x02, flip 0x04
  char    xlabel[LABELMAX];       //  602  intensity display string
  WORD    cleans;                 //  618  cleans
  WORD    NumSkpPerCln;           //  620  number of skips per clean.
  SHORT   SpecMirrorPos[2];       //  622  Spectrograph Mirror Positions
  float   SpecSlitPos[4];         //  626  Spectrograph Slit Positions
  SHORT   AutoCleansActive;       //  642  T/F
  SHORT   UseContCleansInst;      //  644  T/F
  SHORT   AbsorbStripNum;         //  646  Absorbance Strip Number
  SHORT   SpecSlitPosUnits;       //  648  Spectrograph Slit Position Units
  float   SpecGrooves;            //  650  Spectrograph Grating Grooves
  SHORT   srccmp;                 //  654  number of source comp. diodes
  WORD    ydim;                   //  656  y dimension of raw data.
  SHORT   scramble;               //  658  0=scrambled,1=unscrambled
  SHORT   ContinuousCleansFlag;   //  660  T/F Continuous Cleans Timing Option
  SHORT   ExternalTriggerFlag;    //  662  T/F External Trigger Timing Option
  long    lnoscan;                //  664  Number of scans (Early WinX)
  long    lavgexp;                //  668  Number of Accumulations
  float   ReadoutTime;            //  672  Experiment readout time
  SHORT   TriggeredModeFlag;      //  676  T/F Triggered Timing Option
  char    Spare_2[10];            //  678  
  char    sw_version[FILEVERMAX]; //  688  Version of SW creating this file
  SHORT   type;                   //  704  0=1000,1=new120,2=old120,3=130,
                                  //       st121=4,st138=5,dc131(PentaMax)=6,
                                  //       st133(MicroMax)=7,st135(GPIB)=8,
                                  //       VICCD=9, ST116(GPIB)=10,
                                  //       OMA3(GPIB)=11,OMA4=12
  SHORT   flatFieldApplied;       //  706  1 if flat field was applied.
  char    Spare_3[16];            //  708  
  SHORT   kin_trig_mode;          //  724  Kinetics Trigger Mode
  char    dlabel[LABELMAX];       //  726  Data label.
  char    Spare_4[436];           //  742
  char    PulseFileName[HDRNAMEMAX]; //  1178  Name of Pulser File with
                                  //           Pulse Widths/Delays (for Z-Slice)
  char    AbsorbFileName[HDRNAMEMAX]; // 1298 Name of Absorbance File (if File Mode)
  DWORD   NumExpRepeats;          // 1418  Number of Times experiment repeated
  DWORD   NumExpAccums;           // 1422  Number of Time experiment accumulated
  SHORT   YT_Flag;                // 1426  Set to 1 if this file contains YT data
  float   clkspd_us;              // 1428  Vert Clock Speed in micro-sec
  SHORT   HWaccumFlag;            // 1432  set to 1 if accum done by Hardware.
  SHORT   StoreSync;              // 1434  set to 1 if store sync used.
  SHORT   BlemishApplied;         // 1436  set to 1 if blemish removal applied.
  SHORT   CosmicApplied;          // 1438  set to 1 if cosmic ray removal applied
  SHORT   CosmicType;             // 1440  if cosmic ray applied, this is type.
  float   CosmicThreshold;        // 1442  Threshold of cosmic ray removal.
  long    NumFrames;              // 1446  number of frames in file.
  float   MaxIntensity;           // 1450  max intensity of data (future)
  float   MinIntensity;           // 1454  min intensity of data (future)
  char    ylabel[LABELMAX];       // 1458  y axis label.
  WORD    ShutterType;            // 1474  shutter type.
  float   shutterComp;            // 1476  shutter compensation time.
  WORD    readoutMode;            // 1480  readout mode, full,kinetics, etc
  WORD    WindowSize;             // 1482  window size for kinetics only.
  WORD    clkspd;                 // 1484  clock speed for kinetics & frame transfer.
  WORD    interface_type;         // 1486  computer interface
                                  //       (isa-taxi, pci, eisa, etc.)
  SHORT   NumROIsInExperiment;    // 1488  May be more than the 10 allowed in
                                  //       this header (if 0, assume 1)
  char    Spare_5[16];            // 1490
  WORD    controllerNum;          // 1506  if multiple controller system will
                                  //       have controller number data came from.
                                  //       this is a future item.
  WORD    SWmade;                 // 1508  Which software package created this file
  SHORT   NumROI;                 // 1510  number of ROIs used. if 0 assume 1.
  ROIinfo ROIinfoblk[ROIMAX];     // 1512  ROI information
  char    FlatField[HDRNAMEMAX];  // 1632  Flat field file name.
  char    background[HDRNAMEMAX]; // 1752  background sub. file name.
  char    blemish[HDRNAMEMAX];    // 1872  blemish file name.
  float   file_header_ver;        // 1992  version of this file header
  char    YT_Info[1000];          // 1996-2996  Reserved for YT information
  LONG    WinView_id;             // 2996  == 0x01234567L if in use by WinView
  struct {                        //  X     Y
    double offset;                // 3000  3489  offset for absolut data scaling
    double factor;                // 3008  3497  factor for absolut data scaling
    char   current_unit;          // 3016  3505  selected scaling unit
    char   CalibReserved1;        // 3017  3506  reserved
    char   display_string[40];    // 3018  3507  string used for drawing axes...
    char   CalibReserved2[40];    // 3058  3547  reserved
    char   calib_valid;           // 3098  3587  flag if calibration is valid
    char   input_unit;            // 3099  3588  current input units for "calib_value"
    char   polynounit;            // 3100  3589  linear UNIT and used in the "polynocoeff"
    char   polynoorder;           // 3101  3590  ORDER of calibration POLYNOM
    char   calib_count;           // 3102  3591  valid calibration data pairs
    double pixel_position[10];    // 3103  3592  pixel pos. of calibration data
    double calib_value[10];       // 3183  3672  calibration VALUE at above pos
    double polynocoeff[6];        // 3263  3752  polynom COEFFICIENTS
    double laser_position;        // 3311  3800  laser wavenumber for relativ WN
    char   CalibReserved3;        // 3319  3808  reserved
    BYTE   leftover_flag;         // 3320  3809  not used.
    char   user_label[40];        // 3321  3810  Calibration label
    char   expansion[128];        // 3361  3850  Expansion area
  } xcalibration,                 // 3000 -> 3488  X axis calibration
    ycalibration;                 // 3489 -> 3977  Y axis calibration
  char     Istring[40];           // 3978  special intensity scaling string
  char     Spare_6[25];           // 4018  
  BYTE     SpecType;              // 4043 spectrometer type (acton, spex, etc.)
  BYTE     SpecModel;             // 4044 spectrometer model (type dependent)
  BYTE     PulseBurstUsed;        // 4045 pulser burst mode on/off
  DWORD    PulseBurstCount;       // 4046 pulser triggers per burst
  double   PulseBurstPeriod;      // 4050 pulser burst period (in usec)
  BYTE     PulseBracketUsed;      // 4058 pulser bracket pulsing on/off
  BYTE     PulseBracketType;      // 4059 pulser bracket pulsing type
  double   PulseTimeConstFast;    // 4060 pulser slow exponential time constant (in usec)
  double   PulseAmplitudeFast;    // 4068 pulser fast exponential amplitude constant
  double   PulseTimeConstSlow;    // 4076 pulser slow exponential time constant (in usec)
  double   PulseAmplitudeSlow;    // 4084 pulser slow exponential amplitude constant
  SHORT    AnalogGain;            // 4092 analog gain
  SHORT    AvGainUsed;            // 4094 avalanche gain was used
  SHORT    AvGain;                // 4096 avalanche gain value
  SHORT    lastvalue;             // 4098 Always the LAST value in the header
} CSMAHead;                       // 4100 Bytes Total Header Size


#pragma pack()

#endif // CHEADER_H
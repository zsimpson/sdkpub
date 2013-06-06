unit EV04;
{===============================================================================

  File:                         ULEV04.MAK

  Library Call Demonstrated:    cbEnableEvent - ON_SCAN_ERROR
                                              - ON_END_OF_AO_SCAN
                                cbDisableEvent()


  Purpose:                      Paces a waveform out channel 0 using cbAOutScan.
                                At scan start, it sets the digital output high,
                                and upon scan completion, it sets the digital
                                output low. Fatal errors such as UNDERRUN
                                errors, cause the scan to be aborted.

  Demonstration:                Shows how to enable and respond to events.

  Other Library Calls:          cbAOutScan()
                                cbErrHandling()
                                cbDOut()

  Special Requirements:         Board 0 must support event handling, paced
                                analog outputs, and cbDOut.

  (c) Copyright 2001-2002, Measurement Computing Corp.
  All rights reserved.
===============================================================================}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Cbw;

type
  TfrmEventDisplay = class(TForm)
    cmdEnableEvents: TButton;
    cmdDisableEvents: TButton;
    cmdStart: TButton;
    cmdStop: TButton;
    Label1: TLabel;
    Label2: TLabel;
    txtStatus: TEdit;
    txtTotalCount: TEdit;
    chkAutoRestart: TCheckBox;
    procedure cmdStopClick(Sender: TObject);
    procedure cmdStartClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure cmdDisableEventsClick(Sender: TObject);
    procedure cmdEnableEventsClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    DataPtr:PWordArray;
  end;

  PWord = ^Word;

var
  frmEventDisplay: TfrmEventDisplay;

implementation

var

  Rate:LongInt;

const
  BoardNum = 0;
  Channel = 0;
  TotalCount = 2000;
  SampleRate = 1000;
  Range = BIP5VOLTS;
  Options = BACKGROUND;

  PortNum = FIRSTPORTA;
  PortDir = DIGITALOUT;
  SIGNAL_ON = $FF;
  SIGNAL_OFF = $00;
  
  PI = 3.1415926536;


{$R *.DFM}



{
 This gets called upon ON_END_OF_AO_SCAN events.
 For these event types, the EventData supplied curresponds
 to the number of samples output since the start of cbAOutScan.
}
procedure MyCallback(Bd:LongInt; EventType:LongInt;
                          SampleCount:LongInt; UserData: Pointer);stdcall;
var
   Display:    TfrmEventDisplay;
   ULStat:     Integer;

begin
   Display := UserData;

   //give the library a chance to cleanup
   cbStopBackground(Bd, AOFUNCTION);
   
   //signal external device that scan is complete
   cbDOut(Bd, PortNum, SIGNAL_OFF);

   //update the display
   Display.txtTotalCount.Text := IntToStr(SampleCount);
   Display.txtStatus.Text     := 'IDLE';

   if (Display.chkAutoRestart.Checked) then
      begin
      //start a new scan
      Rate := SampleRate;
      ULStat := cbAOutScan( Bd, Channel, Channel, TotalCount, Rate,
                      Range, LongInt(Display.DataPtr), Options);
      if (ULStat = NOERRORS) then
         //signal external device that there's an active scan in progress
         cbDOut(Bd, PortNum, SIGNAL_ON);
         Display.txtTotalCount.Text := '0';
         Display.txtStatus.Text     := 'RUNNING';
      end;

end;


//A scan error occurred; abort and reset the controls.
procedure OnErrCallback(Bd:LongInt; EventType:LongInt;
                              ErrNo:LongInt; UserData: Pointer);stdcall;
var
   Display:    TfrmEventDisplay;

begin
     Display := UserData;

     cbStopBackground(Bd, AOFUNCTION);
   
     // Reset the bAutoRestart such that the ON_END_OF_AO_SCAN event does
     // not automatically start a new scan
     Display.chkAutoRestart.Checked := False;

end;



procedure TfrmEventDisplay.cmdEnableEventsClick(Sender: TObject);
var
   ULStat : Integer;
   EventType: LongInt;
   EventSize: LongInt;
   
begin
   {
    Enable and connect one or more event types to a single user callback
    function using cbEnableEvent().

    Parameters:
      BoardNum    :the number used by CB.CFG to describe this board
      EventType   :the condition that will cause an event to fire
      EventSize   :only used for ON_DATA_AVAILABLE to determine how
                   many samples to collect before firing an event
      @MyCallback :the address of the user function to call when above event
                  type occurs. Note that this function cannot be a member
                  function. So, send self-reference to handle instance specific
                  data.
      Self        :provide reference to this instance of the form so that
                   handler accesses this form's data, not some other's.
    }
    EventType := ON_END_OF_AO_SCAN;
    EventSize := 0;
    ULStat := cbEnableEvent(BoardNum, EventType, EventSize, @MyCallback, Self);
	if ULStat <> NOERRORS then exit;
   {
    Since ON_SCAN_ERROR event doesn't use the EventSize, we can set it to anything
    we choose without affecting the ON_DATA_AVAILABLE setting.
   }
   EventType := ON_SCAN_ERROR;
   cbEnableEvent(BoardNum, EventType, EventSize, @OnErrCallback, Self);

end;



procedure TfrmEventDisplay.cmdDisableEventsClick(Sender: TObject);
begin
   {
   Disable and disconnect all event types with cbDisableEvent()

   Since disabling events that were never enabled is harmless,
   we can disable all the events at once.

   Parameters:
     BoardNum         :the number used by CB.CFG to describe this board
     ALL_EVENT_TYPES  :all event types will be disabled
   }
   cbDisableEvent(BoardNum, ALL_EVENT_TYPES);
end;



procedure TfrmEventDisplay.cmdStartClick(Sender: TObject);
var
   ULStat:Integer;

begin
   //start a new scan
   Rate := SampleRate;
   ULStat := cbAOutScan(BoardNum, Channel, Channel, TotalCount,
                        Rate, Range, LongInt(DataPtr),Options);
   if ULStat = NOERRORS then
      begin
      txtStatus.Text := 'RUNNING';
      txtTotalCount.Text := '0';
      end;
end;




procedure TfrmEventDisplay.cmdStopClick(Sender: TObject);
begin
   //make sure we don't restart the scan ON_END_OF_AI_SCAN
   chkAutoRestart.Checked := False;

   cbStopBackground(BoardNum, AOFUNCTION);

   txtStatus.Text := 'IDLE';
end;



procedure TfrmEventDisplay.FormCreate(Sender: TObject);
var
   Phase: Double;
   val: Single;
   i:Integer;

begin
   {
    Initiate error handling
    activating error handling will trap errors like
    bad channel numbers and non-configured conditions.

    Parameters:
       PRINTALL    :all warnings and errors encountered will be printed
       DONTSTOP    :if an error is encountered, the program will not stop,
                    errors must be handled locally
   }
    cbErrHandling(PRINTALL, DONTSTOP);

   //prepare digital port for signalling external device
   cbDConfigPort(BoardNum, PortNum, PortDir);

   //allocate the data buffer and store the waveform
   DataPtr := PWordArray(cbWinBufAlloc(TotalCount));
   for i:=0 to TotalCount-1 do
     begin
     Phase := 2*PI*i/TotalCount;
     val := 2040*(1+sin(Phase));
     DataPtr^[0] := Trunc(val);
     end;
end;

procedure TfrmEventDisplay.FormDestroy(Sender: TObject);
begin
   // make sure to shut down
   cbStopBackground(BoardNum, AOFUNCTION);

    // disable any active events
    cbDisableEvent(BoardNum, ALL_EVENT_TYPES);

    // and free the data buffer
    cbWinBufFree(LongInt(DataPtr));
end;

end.

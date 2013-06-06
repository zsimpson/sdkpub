unit ev02;
{ULEV02.DPR================================================================

 File:                         ULEV02.PAS

 Library Call Demonstrated:    cbEnableEvent  - ON_SCAN_ERROR
                                              - ON_DATA_AVAILABLE
                                              - ON_END_OF_AI_SCAN
                               cbDisableEvent()

 Purpose:                      Scans a single channel and displays the latest
                               sample acquired every EventSize or more samples.
                               Also updates the latest sample upon scan completion
                               or end. Fatal errors such as OVERRUN errors, cause
                               the scan to be aborted.


 Demonstration:                Shows how to enable and respond to events.

 Other Library Calls:          cbErrHandling()
                               cbAInScan()
                               

 Special Requirements:         Board 0 must support event handling and have
                               paced analog inputs.


 (c) Copyright 2001-2002, Measurement Computing Corp.
 All rights reserved.
==========================================================================}

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
    Label3: TLabel;
    Label4: TLabel;
    chkAutoRestart: TCheckBox;
    txtEventSize: TEdit;
    txtStatus: TEdit;
    txtSampleCount: TEdit;
    txtLatestSample: TEdit;
    procedure cmdEnableEventsClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure cmdDisableEventsClick(Sender: TObject);
    procedure cmdStartClick(Sender: TObject);
    procedure cmdStopClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    DataPtr: PWordArray;
  end;

  PWord = ^Word;

var
  frmEventDisplay: TfrmEventDisplay;
  Rate: LongInt;

const
  BoardNum = 0;
  Channel = 0;
  TotalCount = 2000;
  SampleRate = 1000;
  Range = BIP5VOLTS;
  Options = BACKGROUND;

implementation

{$R *.DFM}


{
 This gets called upon ON_DATA_AVAILABLE and ON_END_OF_AI_SCAN events.
 For these event types, the EventData supplied curresponds
 to the number of samples collected since the start of cbAInScan.
}
procedure MyCallback(Bd: LongInt; EventType: LongInt; SampleCount: LongInt; UserData: Pointer); stdcall;
var
   SampleIdx: LongInt;
   Data: Word;
   Volts: Single;
   Display: TfrmEventDisplay;

begin
   Display := UserData;

   //get the latest sample
   SampleIdx := (SampleCount-1) mod TotalCount;
   Data := Display.DataPtr^[SampleIdx];
   cbToEngUnits(Bd, Range, Data, Volts);

   //update the display
   Display.txtSampleCount.Text := IntToStr(SampleCount);
   Display.txtLatestSample.Text := FloatToStrF(Volts, ffFixed, 6, 4) +' V';

   if (EventType = ON_END_OF_AI_SCAN) then
      begin
      //Give the library a chance to clean up
      cbStopbackground(Bd, AIFUNCTION);

      if (Display.chkAutoRestart.Checked) then
         begin
         //start a new scan
         Rate := SampleRate;
         cbAInScan(Bd, Channel, Channel, TotalCount, Rate,
               Range, LongInt(Display.DataPtr),Options);
         end
      else
          begin
          //reset the status display
          Display.txtStatus.Text := 'IDLE';
          end;
      end;
end;



//A scan error occurred; so, abort and reset the controls.
procedure OnErrorCallback(Bd:LongInt; EventType: LongInt; ErrNo: LongInt; UserData: Pointer); stdcall;
var
   Display: TfrmEventDisplay;

begin
   Display := UserData;

   {
    We don't need to update the display here since that will happen during
    the ON_END_OF_AI_SCAN and/or ON_DATA_AVAILABLE events to follow this event
    -- yes, this event is handled before any others and this event should be
    accompanied by a ON_END_OF_AI_SCAN
   }
   cbStopBackground(Bd, AIFUNCTION);

   {
    Reset the bAutoRestart such that the ON_END_OF_AI_SCAN event does
    not automatically start a new scan
   }
   Display.chkAutoRestart.Checked := False;

end;



procedure TfrmEventDisplay.cmdEnableEventsClick(Sender: TObject);
var
  ULStat: Integer;
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
  EventType := ON_DATA_AVAILABLE + ON_END_OF_AI_SCAN;
  EventSize := StrToInt(txtEventSize.Text);
  ULStat := cbEnableEvent(BoardNum, EventType, EventSize, @MyCallback, Self);
  If ULStat <> 0 then exit;
  {
   Since ON_SCAN_ERROR event doesn't use the EventSize, we can set it to anything
   we choose without affecting the ON_DATA_AVAILABLE setting.
  }
  EventType := ON_SCAN_ERROR;
  EventSize := 0;
  cbEnableEvent(BoardNum, EventType, EventSize, @OnErrorCallback, Self);

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
   ULStat: Integer;
begin
   {
   Collect the values with cbAInScan()
   Parameters:
     BoardNum%   :the number used by CB.CFG to describe this board
     Channel     :the channel of the scan
     TotalCount  :the total number of A/D samples to collect
     Rate        :sample rate
     Range       :the gain for the board
     DataPtr     :the handle to the buffer to hold the data
     Options     :data collection options
   }
   Rate := SampleRate;
   ULStat := cbAInScan(BoardNum, Channel, Channel, TotalCount, Rate,
                                          Range, LongInt(DataPtr),Options);
   if ULStat = NOERRORS then
      begin
      txtStatus.Text       := 'RUNNING';
      txtLatestSample.Text := 'NA';
      txtSampleCount.Text  := ' 0';
      end
   else 
      cbStopBackground(BoardNum, AIFUNCTION);

end;



procedure TfrmEventDisplay.cmdStopClick(Sender: TObject);
begin
   //make sure we don't restart the scan ON_END_OF_AI_SCAN
   chkAutoRestart.Checked := False;

   cbStopBackground(BoardNum, AIFUNCTION);
   txtStatus.Text := 'IDLE';
end;



procedure TfrmEventDisplay.FormCreate(Sender: TObject);
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

    //allocate the data buffer for cbAInscan
    DataPtr := PWordArray(cbWinBufAlloc(TotalCount));
end;



procedure TfrmEventDisplay.FormDestroy(Sender: TObject);
begin
    // make sure to shut down
    cbStopBackground( BoardNum,AIFUNCTION);

    // disable any active events
    cbDisableEvent(BoardNum, ALL_EVENT_TYPES);

    // and free the data buffer
    cbWinBufFree(LongInt(DataPtr));

end;








end.

unit EV03;
{ULEV03.DPR================================================================

 File:                         ULEV03.PAS

 Library Call Demonstrated:    cbEnableEvent  - ON_SCAN_ERROR
                                              - ON_PRETRIGGER
                                              - ON_END_OF_AI_SCAN
                               cbDisableEvent()
                               cbAPretrig()

 Purpose:                      Scans a single channel with cbAPretrig and sets
                               digital outputs high upon first trigger event.
                               Upon scan completion, it displays immediate points
                               before and after the trigger. Fatal errors such as
                               OVERRUN errors, cause the scan to be aborted, but TOOFEW
                               errors are ignored.


 Demonstration:                Shows how to enable and respond to events.

 Other Library Calls:          cbErrHandling()
                               cbDOut()
                               

 Special Requirements:         Board 0 must support event handling, cbAPretrig,
                               and cbDOut.


 (c) Copyright 2001-2002, Measurement Computing Corp.
 All rights reserved.
==========================================================================}
interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Cbw, Grids;

type
  TfrmEventDisplay = class(TForm)
    cmdEnableEvents: TButton;
    cmdDisableEvents: TButton;
    cmdStart: TButton;
    cmdStop: TButton;
    Label1: TLabel;
    Label2: TLabel;
    txtStatus: TEdit;
    txtPreCount: TEdit;
    chkAutoRestart: TCheckBox;
    grdPreTrigData: TStringGrid;
    grdPostTrigData: TStringGrid;
    Label3: TLabel;
    Label4: TLabel;
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure FormActivate(Sender: TObject);
    procedure cmdEnableEventsClick(Sender: TObject);
    procedure cmdDisableEventsClick(Sender: TObject);
    procedure cmdStartClick(Sender: TObject);
    procedure cmdStopClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    ActualPreCount:LongInt;
    PreCount: LongInt;
    DataPtr: PWordArray;

  end;


  PWord = ^Word;


var
  frmEventDisplay: TfrmEventDisplay;


implementation

var
  TotalCount: LongInt;
  Rate: LongInt;
  ChanTags: array[0..10512] of Word;

const
  BoardNum   = 0;
  Channel    = 0;
  PreCountSet   = 100;
  TotalCountSet = 10000;
  BufferSize = 10512;
  SampleRate = 1000;
  Range      = BIP5VOLTS;
  Options    = BACKGROUND;

  SIGNAL_ON  = $FF;
  SIGNAL_OFF = $00;

{$R *.DFM}


{
 This gets called for each ON_PRETRIGGER and ON_END_OF_AI_SCAN events.
 For the ON_PRETRIGGER event, the EventData supplied corresponds to the
 number of pretrigger samples available in the buffer.
 For the ON_END_OF_AI_SCAN event, the EventData supplied corresponds to the
 number of samples aquired since the start of cbAPretrig.
}
procedure MyCallback( Bd:LongInt; EventType:LongInt;
                             SampleCount:LongInt; UserData: Pointer);stdcall;
var
   ULStat:          Integer;
   i, N, SampleIdx: LongInt;
   Volts:           Single;
   Display:         TfrmEventDisplay;

begin
   Display := UserData;

   if (EventType = ON_PRETRIGGER) then
      begin
      //store and display the actual number of pre-trigger samples collected
      Display.ActualPreCount := SampleCount;
      Display.txtPreCount.Text := IntToStr(Display.ActualPreCount);

      //signal external device that trigger has been detected
      cbDOut(Bd, FIRSTPORTA, SIGNAL_ON);
      end;


   if (EventType = ON_END_OF_AI_SCAN) then
      begin
      //give the library a chance to clean up
      cbStopBackground(Bd, AIFUNCTION);
      
      Display.txtStatus.Text := 'IDLE';

      cbDOut(Bd, FIRSTPORTA, SIGNAL_OFF);

      //align the data so that oldest data is first
      cbAConvertPretrigData(Bd, Display.PreCount, TotalCount, Display.DataPtr^[0], ChanTags[0]);

      //update the Pre- and Post- Trigger data displays
      N := Display.grdPreTrigData.RowCount - 1;
      for i:=0 to N do
         begin

         //Avoid indexing invalid pretrigger data
         if Display.ActualPreCount<10-i then
            Display.grdPreTrigData.Cells[1,i] := 'NA'
         else
             begin
             SampleIdx := PreCountSet-(N-i);
             cbToEngUnits(Bd, Range, Display.DataPtr^[SampleIdx], Volts);
             Display.grdPreTrigData.Cells[1,i] := FloatToStrF(Volts, ffFixed, 6, 4)+' V';
             end;

         SampleIdx := Display.PreCount + i;
         cbToEngUnits(Bd, Range, Display.DataPtr^[SampleIdx], Volts);
         Display.grdPostTrigData.Cells[1,i] := FloatToStrF(Volts, ffFixed, 6, 4)+' V';
         end;

      if (Display.chkAutoRestart.Checked) then
         begin
         //start a new scan
         Display.ActualPrecount := 0;
         Display.PreCount := PreCountSet;
         TotalCount := TotalCountSet;
         Rate := SampleRate;
         ULStat := cbAPretrig(Bd, Channel, Channel, Display.PreCount, TotalCount,
                              Rate, Range, LongInt(Display.DataPtr), Options);
         if (ULStat = NOERRORS) then
            begin
            Display.txtStatus.Text := 'RUNNING';
            Display.txtPreCount.Text := 'NA'
            end
         else
             begin
             cbStopBackground(Bd, AIFUNCTION);

             Display.txtStatus.Text := 'IDLE';
             end;
         end
      else
          begin
          Display.txtStatus.Text := 'IDLE';
          end;
      end;
end;



//A scan error occurred; if fatal(not TOOFEW), abort and reset the controls.
procedure OnErrCallback( Bd: LongInt; EventType: LongInt;
                              ErrNo:LongInt; UserData: Pointer);stdcall;
var
   Display: TfrmEventDisplay;

begin
   Display := UserData;

   {
    We don't need to update the display here since that will happen during
    the ON_END_OF_AI_SCAN  event to follow this event -- yes, this event is
    handled before any others, and if fatal, this event should be accompanied
    by an ON_END_OF_AI_SCAN event.
   }
   if (ErrNo<>TOOFEW) then
     begin
     cbStopBackground(Bd, AIFUNCTION);

     // Reset the chkAutoRestart such that the ON_END_OF_AI_SCAN event does
     // not automatically start a new scan
     Display.chkAutoRestart.Checked := False;
     end;
end;



procedure TfrmEventDisplay.cmdEnableEventsClick(Sender: TObject);
var
   ULStat:Integer;
   EventType:LongInt;
   EventSize:LongInt;

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
   EventType := ON_PRETRIGGER + ON_END_OF_AI_SCAN;
   EventSize := 0;
   ULStat := cbEnableEvent(BoardNum, EventType, EventSize, @MyCallback, Self);
   if (ULStat <> NOERRORS) then exit;
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
   i:LongInt;

begin
   //start a new scan
   ActualPrecount := 0;
   PreCount       := PreCountSet;
   TotalCount     := TotalCountSet;
   Rate           := SampleRate;
   ULStat := cbAPretrig(BoardNum, Channel, Channel, PreCount, TotalCount,
                        Rate, Range, LongInt(DataPtr), Options);
   if (ULStat = NOERRORS) then
      begin
      //update the display
      txtStatus.Text := 'RUNNING';
      txtPreCount.Text := 'NA';
      for i:=0 to grdPreTrigData.RowCount-1 do
         begin
         grdPreTrigData.Cells[1,i] := 'NA';
         grdPostTrigData.Cells[1,i] := 'NA';
         end;
      end;
end;



procedure TfrmEventDisplay.cmdStopClick(Sender: TObject);
begin
   //make sure we don't restart the scan ON_END_OF_AI_SCAN
   chkAutoRestart.Checked := False;

   cbStopBackground(BoardNum, AIFUNCTION);

   txtStatus.Text := 'IDLE';
end;



procedure TfrmEventDisplay.FormActivate(Sender: TObject);
var
   i: Integer;

begin
     //initialize the grid control
     for i:=0 to grdPreTrigData.RowCount -1 do
       begin
       grdPreTrigData.Cells[0,i] := 'Trig - '+IntToStr(10-i);
       grdPreTrigData.Cells[1,i] := 'NA';

       grdPostTrigData.Cells[0,i] := 'Trig + '+IntToStr(i);
       grdPostTrigData.Cells[1,i] := 'NA';
       end;

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
    DataPtr := PWordArray(cbWinBufAlloc(BufferSize));

   //prepare digital port for signalling external device 
   cbDConfigPort(BoardNum, FIRSTPORTA, DIGITALOUT);
end;



procedure TfrmEventDisplay.FormDestroy(Sender: TObject);
begin
     // make sure to shut down
    cbStopBackground(BoardNum, AIFUNCTION);

    // disable any active events
    cbDisableEvent(BoardNum, ALL_EVENT_TYPES);

    // and free the data buffer
    cbWinBufFree(LongInt(DataPtr));
end;

end.

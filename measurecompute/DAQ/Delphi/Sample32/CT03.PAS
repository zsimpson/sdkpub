unit Ct03;
{
ULCT03.DPR***************************************************************

  File:                         CT03.PAS

  Library Call Demonstrated:    9513 Counter Functions
                                   cbC9513Config()
                                   cbCStoreOnInt()

  Purpose:                      Operate the counter.

  Demonstration:                Sets up 2 counters to store values in
                                response to an interrupt.

  Other Library Calls:          cbC9513Init()
                                   cbCLoad()
                                   cbCStopBackground()
                                   cbErrHandling()

  Special Requirements:         Board 0 must have a 9513 Counter.
                                IR enable must be tied low.
                                Generation of an interrupt(pin 1).

(c) Copyright 1995 - 2002, Measurement Computing Corp.
All rights reserved.
**************************************************************************
}
interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, StdCtrls, ExtCtrls, cbw;

type
  TfrmCount = class(TForm)
    cmdQuit: TButton;
    MemoData: TMemo;
    cmdStart: TButton;
    tmrReadCount: TTimer;
    cmdStop: TButton;
    procedure cmdQuitClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure cmdStartClick(Sender: TObject);
    procedure tmrReadCountTimer(Sender: TObject);
    procedure cmdStopClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
   frmCount: TfrmCount;

implementation

{$R *.DFM}

var
   ULStat:                Integer;
   ChipNum:               Integer;
   FOutDivider:           Integer;
   FOutSource:            Integer;
   Compare1:              Integer;
   Compare2:              Integer;
   TimeOfDay:             Integer;
   CounterNum:            Integer;
   GateControl:           Integer;
   CounterEdge:           Integer;
   CountSource:           Integer;
   SpecialGate:           Integer;
   ReLoad:                Integer;
   RecycleMode:           Integer;
   BCDMode:               Integer;
   CountDirection:        Integer;
   OutputControl:         Integer;
   LoadValue:             Integer;
   ErrReporting:          Integer;
   ErrHandling:           Integer;
   CurCount:              Longint;
   CurIndex:              Longint;
   DataBuffer:            array [0..20] of Word;   {10 counters (CIO-CTR10) }
   MemHandle:             Integer;              { 
                                                      must point to block of memory
                                         large enough to hold 
                                         IntCount*NumCntrs data values 
                                        }
   FirstPoint:            Word;
   Stat:                  string[10];
   RevLevel:              Single;

   CntrControl:           array [0..20] of SmallInt;
   Status:                SmallInt;
   

const
   BoardNum:              Integer = 0;
   IntCount:           Integer = 100; { number of INT to collect data }
   MaxNumCntrs:           Integer = 20;    { maximum number of counters for all models }
   NumCntrs:           Integer = 10;    { Number of onboard 9513 counters.
                                 UPDATE THIS VALUE ACCORDING TO ACTUAL 
                                 NUMBER OF COUNTERS FOR THE MODEL INSTALLED
                               }


procedure TfrmCount.FormCreate(Sender: TObject);
var
   RegName:       Integer;
   CntrIdx:       Integer;

begin
  {declare Revision Level}
   RevLevel := CURRENTREVNUM;
   ULStat := cbDeclareRevision(RevLevel);

   {
   set up internal error handling for the Universal Library
   }
   ErrReporting := PRINTALL;       {set Universal Library to print all errors}
   ErrHandling := STOPALL;         {set Universal Library to stop on errors}
   ULStat := cbErrHandling(ErrReporting, ErrHandling);
 
   {
   initialize the board level features
     Parameters:
        BoardNum    :the number used by CB.CFG to describe this board
        ChipNum     :selects counter chip on board
        FOutDivider :the F-Out divider (0-15)
        FOutSource  :the signal source for F-Out
        Compare1    :status of comparator 1
        Compare2    :status of comparator 2
        TimeOfDay   :time of day control mode
   }
   ChipNum := 1;
   FOutDivider := 10;     {set up OSC OUT for 10Hz signal which can be used}
   FOutSource := FREQ5;   {as an interrupt source for this example}
   Compare1 := 0;         {DISABLED}
   Compare2 := 0;         {DISABLED}
   TimeOfDay := 0;        {DISABLED}

   ULStat := cbC9513Init (BoardNum, ChipNum, FOutDivider, FOutSource, Compare1, Compare2, TimeOfDay);
   If ULStat <> 0 then exit;
   MemoData.Text := Format('Chip # %d has been configured with FOutSource = "FREQ4".', [ChipNum]);
   MemoData.Lines.Add (' ');
   {
   set the configurable operations of the counter
     Parameters:
        BoardNum       :the number used by CB.CFG to describe this board
        CounterNum     :the counter to be configured (0-5)
        GateControl    :gate control value
        CounterEdge    :which edge to count
        CountSource    :signal source
        SpecialGate    :status of special gate
        ReLoad         :method of reloading the counter
        RecycleMode    :recycle mode
        BCDMode        :counting mode, BCD or binary
        CountDirection :direction for the counting (COUNTUP or COUNTDOWN)
        OutputControl  :output signal type and level
   }
   CounterNum := 1;
   GateControl := NOGATE;
   CounterEdge := POSITIVEEDGE;
   CountSource := FREQ3;
   SpecialGate := 0;      {DISABLED}
   ReLoad := LOADREG;
   RecycleMode := RECYCLE;
   BCDMode := 0;          {DISABLED}
   CountDirection := COUNTUP;
   OutputControl := ALWAYSLOW;

   ULStat := cbC9513Config (BoardNum, CounterNum , GateControl, CounterEdge, CountSource,
                           SpecialGate, ReLoad, RecycleMode, BCDMode, CountDirection, OutputControl);
   If ULStat <> 0 then exit;
   {set up second counter}
   CounterNum := 2;
   CountSource := FREQ5;
   ULStat := cbC9513Config (BoardNum, CounterNum , GateControl, CounterEdge, CountSource,
                           SpecialGate, ReLoad, RecycleMode, BCDMode, CountDirection, OutputControl);
   If ULStat <> 0 then exit;
   MemoData.Text :=
   'Counters 1 and 2 have been configured for use with cbStoreOnInt() function.';
   MemoData.Lines.Add (' ');
   {
   load the 2 counters with starting values of zero with cbCLoad()
     Parameters:
        BoardNum    :the number used by CB.CFG to describe this board
        RegName     :the reg. to be loading with the starting value
        LoadValue   :the starting value to place in the counter
   }
   LoadValue := 0;
   for RegName := LOADREG1 to LOADREG2 do
   begin
      ULStat := cbCLoad (BoardNum, RegName, LoadValue);
      If ULStat <> 0 then exit;
   end;
   MemoData.Lines.Add (Format('The value %d has been loaded into counters 1 and 2.',
                                         [LoadValue]));
   MemoData.Lines.Add (' ');
   MemoData.Lines.Add ('Click  "Start"  to read status of background operation.');
   {
   set the counters to store their values upon an interrupt
     Parameters:
        BoardNum       :the number used by CB.CFG to describe this board
        IntCount       :maximum number of interrupts
        CntrControl[]  :array which indicates the channels to be used
        DataBuffer[]   :array that receives the count values for enabled
                        channels each time an interrupt occurs
   }
   { set all channels to DISABLED }
   for CntrIdx := 0 to MaxNumCntrs do
   begin
      CntrControl[CntrIdx] := 0;
   end;
   { enable the channels to be monitored }
   CntrControl[0] := 1;  {ENABLED}
   CntrControl[1] := 1;  {ENABLED}

   {
   Set up a buffer in Windows to contain the data.  We're allocating enough space
   for MaxNumCntrs in case NumCntrs had not been updated for the installed board.
   }
   MemHandle := cbWinBufAlloc (IntCount*MaxNumCntrs);

   ULStat := cbCStoreOnInt (BoardNum, IntCount, CntrControl[0], MemHandle);
   If ULStat <> 0 then exit;
end;

procedure TfrmCount.cmdStartClick(Sender: TObject);
begin
   tmrReadCount.Enabled := True;
end;

procedure TfrmCount.tmrReadCountTimer(Sender: TObject);
var
   CntrIdx:       Integer;

begin
   MemoData.Text := 'Current status of background operation:';
   MemoData.Lines.Add (' ');
   {
   use a timer to check counts stored by interrupts
      Parameters:
         BoardNum    :the number used by CB.CFG to describe this board
         Status      :
         CurCount    :
         CurIndex    : index into Windows buffer identifying the last 
                  set of data put into the buffer.  
         FunctionType:A/D operation (CTRFUNCTIOM)

   }
   ULStat := cbGetStatus(BoardNum, Status, CurCount, CurIndex, CTRFUNCTION);
   If ULStat <> 0 then exit;

   { the latest data put in the buffer begins at (CurCount-1)*NumCntrs }
   FirstPoint := 0;

   { Scaling CurIndex by the NumCntrs onboard gives us the location of the latest
    set of NumCntrs readings in the windows data buffer. }
   If CurIndex>0 then 
      FirstPoint := NumCntrs*CurIndex;
   
   ULStat := cbWinBufToArray(MemHandle, DataBuffer[0], FirstPoint, NumCntrs);
   If ULStat <> 0 then exit;

   for CntrIdx := 0 to 4 do
   begin
      Stat := 'ENABLED ';
      if (CntrControl[CntrIdx] = 0) then  Stat := 'DISABLED';
      MemoData.Lines.Add (Format('Counter %d status: %s,  count: %d',
                                          [CntrIdx + 1, Stat, DataBuffer[CntrIdx]]));
   end;
   
   MemoData.Lines.Add (' ');
   MemoData.Lines.Add (Format('Number of interrupts so far = %d', [CurCount]));
end;

procedure TfrmCount.cmdStopClick(Sender: TObject);
begin
   {
   the background operation must be explicitly stopped
   use cbStopBackground to end the operation
     Parameters:
        BoardNum    :the number used by CB.CFG to describe this board
        FunctionType: Counter operation (CTRFUNCTIOM)

   }
   tmrReadCount.Enabled := False;
   ULStat := cbStopBackground(BoardNum, CTRFUNCTION);

end;

procedure TfrmCount.cmdQuitClick(Sender: TObject);
begin
   tmrReadCount.Enabled := False;
   ULStat := cbStopBackground(BoardNum, CTRFUNCTION);

   ULStat := cbWinBufFree(MemHandle);    {Free up memory for use by
                                          other programs}
   Close;
end;

end.

unit Ct02;
{
ULCT02.DPR***************************************************************

  File:                         CT02.PAS

  Library Call Demonstrated:    9513 Counter Functions
                                   cbC9513Init()
                                   cbC9513Config()
                                   cbCLoad()
                                   cbCIn()

  Purpose:                      Operate the counter.

  Demonstration:                Initializes, configures, loads, and
                                reads the counter.

  Other Library Calls:          cbErrHandling()

  Special Requirements:         Board 0 must have a 9513 Counter.
                                Uses internal clock.

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
    procedure cmdQuitClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure cmdStartClick(Sender: TObject);
    procedure tmrReadCountTimer(Sender: TObject);
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
   RegName:               Integer;
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
   Count:                 Word;
   RevLevel:              Single;

const
   BoardNum:              Integer = 0;

procedure TfrmCount.FormCreate(Sender: TObject);
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
   FOutDivider := 0;
   FOutSource := FREQ4;
   Compare1 := DISABLED;
   Compare2 := DISABLED;
   TimeOfDay := DISABLED;

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
   CountSource := FREQ4;
   SpecialGate := DISABLED;
   ReLoad := LOADREG;
   RecycleMode := RECYCLE;
   BCDMode := DISABLED;
   CountDirection := COUNTUP;
   OutputControl := ALWAYSLOW;

   ULStat := cbC9513Config (BoardNum, CounterNum , GateControl, CounterEdge, CountSource,
                           SpecialGate, ReLoad, RecycleMode, BCDMode, CountDirection, OutputControl);
   If ULStat <> 0 then exit;
   MemoData.Text := Format(
   'Counter # %d has been configured with CountDirection =  "COUNTUP"  and Output =  "ALWAYSLOW".',
                                    [CounterNum]);
   MemoData.Lines.Add (' ');
   {
   Send a starting value to the counter with cbCLoad()
     Parameters:
        BoardNum    :the number used by CB.CFG to describe this board
        RegName     :the reg. to be loading with the starting value
        LoadValue   :the starting value to place in the counter
   }
   LoadValue := 1;
   RegName := LOADREG1;
   ULStat := cbCLoad (BoardNum, RegName, LoadValue);
   If ULStat <> 0 then exit;
   MemoData.Lines.Add (Format('The value %d has been loaded into counter # %d.',
                                         [LoadValue, CounterNum]));
   MemoData.Lines.Add (' ');
   MemoData.Lines.Add ('Click  "Start"  to read counter');
end;

procedure TfrmCount.cmdStartClick(Sender: TObject);
begin
   tmrReadCount.Enabled := True;
end;

procedure TfrmCount.tmrReadCountTimer(Sender: TObject);
begin
   {
    use a timer to keep checking the counter value with cbCIn()
      Parameters:
         BoardNum    :the number used by CB.CFG to describe this board
         CounterNum  :the counter to be setup
         Count       :the count value in the counter
   }
   ULStat := cbCIn (BoardNum, CounterNum, Count);
   If ULStat <> 0 then exit;
   MemoData.Text := Format('Value read at counter # %d is %d counts.', [CounterNum, Count]);
end;

procedure TfrmCount.cmdQuitClick(Sender: TObject);
begin
   Close;
end;

end.

unit Ct04;
{
ULCT04.DPR***************************************************************

  File:                         CT04.PAS

  Library Call Demonstrated:    cbCFreqIn()

  Purpose:                      Measure the frequency of a signal.

  Demonstration:                Intializes the counter and measures
                                a frequency.

  Other Library Calls:          cbErrHandling()

  Special Requirements:         Board 0 must have a 9513 Counter.
                                External freq. at counter 1 input.
                                (100Hz < freq < 330kHz)

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
   SigSource:             Integer;
   FOutDivider:           Integer;
   FOutSource:            Integer;
   Compare1:              Integer;
   Compare2:              Integer;
   TimeOfDay:             Integer;
   GateInterval:          Integer;
   ErrReporting:          Integer;
   ErrHandling:           Integer;
   Freq:                  Longint;
   Count:                 Word;
   MemHandle:             Integer;
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
   set up a buffer in Windows to contain the data
   }
   Count := 10;
   MemHandle := cbWinBufAlloc (Count);
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
   FOutDivider := 1;     {set up OSC OUT for 10Hz signal which can be used}
   FOutSource := FREQ3;   {as an interrupt source for this example}
   Compare1 := 0;         {DISABLED}
   Compare2 := 0;         {DISABLED}
   TimeOfDay := 0;        {DISABLED}

   ULStat := cbC9513Init (BoardNum, ChipNum, FOutDivider, FOutSource, Compare1, Compare2, TimeOfDay);
   If ULStat <> 0 then exit;
   MemoData.Text := Format('Chip # %d has been configured with FOutSource =  "FREQ3".', [ChipNum]);
   MemoData.Lines.Add ('This frequency (10kHz) can be used as test source by connecting pin 30 to pin 36.');
   MemoData.Lines.Add (' ');
   MemoData.Lines.Add ('(All pin numbers apply to CIO-CTR05)');
   MemoData.Lines.Add (' ');
   {
   measure the frequency of the internally-generated 10 kHz signal
     Parameters:
        BoardNum         :the number used by CB.CFG to describe this board
        SigSource        :the signal to be measured
        GateInterval     :gating interval in milliseconds
        Count            :the raw count during GateInterval is returned here
        Freq             :the calculated frequency (Hz) is returned here
   }
   MemoData.Lines.Add ('There must be a TTL frequency at counter 1 input in the range 100Hz to 330kHz.');
   MemoData.Lines.Add
   ('Counter 4 output (pin 32) must be connected to counter 5 gate (pin 12).');
   MemoData.Lines.Add (' ');
   MemoData.Lines.Add ('Click  "Start"  to read frequency at counter 1 input.');
end;

procedure TfrmCount.cmdStartClick(Sender: TObject);
begin
   cmdStop.Enabled := True;
   cmdStart.Enabled := False;
   SigSource := CTRINPUT1;
   GateInterval := 100;
   tmrReadCount.Enabled := True;
end;

procedure TfrmCount.tmrReadCountTimer(Sender: TObject);
begin
   MemoData.Text := 'Frequency measured with cbFreqIn():';
   MemoData.Lines.Add (' ');
   {
   measure the frequency of the internally-generated 10 kHz signal
     Parameters:
        BoardNum         :the number used by CB.CFG to describe this board
        SigSource        :the signal to be measured
        GateInterval     :gating interval in milliseconds
        Count            :the raw count during GateInterval is returned here
        Freq             :the calculated frequency (Hz) is returned here
   }
   ULStat := cbCFreqIn (BoardNum, SigSource, GateInterval, Count, Freq);
   MemoData.Lines.Add (Format('Counter value at end of interval: %d', [Count]));
   MemoData.Lines.Add (Format('Frequency of signal at counter 1 input: %d', [Freq]));
end;

procedure TfrmCount.cmdStopClick(Sender: TObject);
begin
   tmrReadCount.Enabled := False;
   cmdStart.Enabled := True;
   cmdStop.Enabled := False;
end;

procedure TfrmCount.cmdQuitClick(Sender: TObject);
begin
   tmrReadCount.Enabled := False;
   Close;
end;

end.

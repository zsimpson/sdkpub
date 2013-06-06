unit CT07;
{
 ULCT07.DPR***************************************************************

  File:                         CT07.PAS

  Library Call Demonstrated:    Event Counter Functions
                                     cbCLoad32()
                                     cbCIn32()

  Purpose:                      Operate the counter.

  Demonstration:                Resets and reads the event counter.

  Other Library Calls:          cbErrHandling()

  Special Requirements:         Board 0 must have an event counter,
                                such as the miniLAB 1008 and PDM-1208LS.

(c) Copyright 2003, Measurement Computing Corp.
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
   RegName:               Integer;
   LoadValue:             LongInt;
   Count:                 LongInt;
   ErrReporting:          Integer;
   ErrHandling:           Integer;


const
   BoardNum:              Integer = 0;
	CounterNum:            Integer = 1;

procedure TfrmCount.FormCreate(Sender: TObject);
begin
   {
   set up internal error handling for the Universal Library
   }
   ErrReporting := PRINTALL;       {set Universal Library to print all errors}
   ErrHandling := STOPALL;         {set Universal Library to stop on errors}
   ULStat := cbErrHandling(ErrReporting, ErrHandling);

   {
   Send a starting value to the counter with cbCLoad32()
     Parameters:
        BoardNum    :the number used by CB.CFG to describe this board
        RegName     :the counter register to be loading with the starting value
        LoadValue   :the starting value to place in the counter
   }
   LoadValue := 0;       { Event counters can only be reset to 0. }
   RegName := LOADREG1;
   ULStat := cbCLoad32 (BoardNum, RegName, LoadValue);
   If ULStat <> 0 then exit;
   MemoData.Text := Format('The value %d has been loaded into counter # %d.',
                                         [LoadValue, CounterNum]);
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
    use a timer to keep checking the counter value with cbCIn32()
      Parameters:
         BoardNum    :the number used by CB.CFG to describe this board
         CounterNum  :the counter to be read
         Count       :the count value in the counter
   }
   ULStat := cbCIn32 (BoardNum, CounterNum, Count);
   If ULStat <> 0 then exit;
   MemoData.Text := Format('Value read at counter # %d is %d counts.', [CounterNum, Count]);
end;

procedure TfrmCount.cmdQuitClick(Sender: TObject);
begin
   Close;
end;

end.

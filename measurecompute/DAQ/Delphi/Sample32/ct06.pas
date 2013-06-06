unit Ct06;
{
ULCT06.DPR***************************************************************

  File:                         CT06.PAS

  Library Call Demonstrated:    7266 Counter Functions
                                   cbC7266Config()
                                   cbCLoad32()
                                   cbCIn32()
                                   cbCStatus()
               

  Purpose:                      Operate the counter.

  Demonstration:                configures, loads, and
                                reads the counter and status.

  Other Library Calls:          cbErrHandling()

  Special Requirements:         Board 0 must have a 7266 Counter.

                                These functions are only available in
                                the 32 bit version of the Universal Library

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
   CounterNum:            Integer;
   Quadrature:            Integer;
   CountingMode:          Integer;
   DataEncoding:          Integer;
   IndexMode:             Integer;
   InvertIndex:           Integer;
   FlagPins:              Integer;
   GateEnable:            Integer;
   RegName:               Integer;
   LoadValue:             Longint;
   ErrReporting:          Integer;
   ErrHandling:           Integer;
   Count:                 LongInt;
   StatusBits:            LongInt;
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

    { set the configurable operations of the counter
        Parameters:
            BoardNum       :the number used by CB.CFG to describe this board
            CounterNum     :the counter to be configured (0-5)
            Quadrature     :Select type of counter input
            CountingMode   :Slects how counter will operate
            IndexMode      :Selects what index signal will control
            InvertIndex    :Set to ENABLED id index signal is inverted
            FlagPins       :Select which signals will drive Flag pins
            GateEnable     :Set to ENABLED to use external gating signal */
    }
    CounterNum := 1;
    Quadrature := X1_QUAD;
    CountingMode := MODULO_N;
    DataEncoding := BINARY_ENCODING;
    IndexMode := INDEX_DISABLED;
    InvertIndex := DISABLED;
    FlagPins := CARRY_BORROW;
    GateEnable := DISABLED;
    ULStat := cbC7266Config (BoardNum, CounterNum , Quadrature, CountingMode,
                            DataEncoding, IndexMode, InvertIndex, FlagPins,
                            GateEnable);
   If ULStat <> 0 then exit;
   MemoData.Text := Format(
   'Counter # %d has been configured.',
                                    [CounterNum]);
   MemoData.Lines.Add (' ');
   {
   Send a starting value to the counter with cbCLoad32()
     Parameters:
        BoardNum    :the number used by CB.CFG to describe this board
        RegName     :the reg. to be loading with the starting value
        LoadValue   :the starting value to place in the counter
   }
   LoadValue := 1000;
   RegName := COUNT1 + CounterNum -1;
   ULStat := cbCLoad32 (BoardNum, RegName, LoadValue);
   If ULStat <> 0 then exit;
   MemoData.Lines.Add (Format('The value %d has been loaded into counter # %d.',
                                         [LoadValue, CounterNum]));
   LoadValue := 2000;
   RegName := PRESET1 + CounterNum -1;
   ULStat := cbCLoad32 (BoardNum, RegName, LoadValue);
   If ULStat <> 0 then exit;
   MemoData.Lines.Add (Format('The maximum count of %d has been loaded into counter # %d.',
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
   ULStat := cbCIn32 (BoardNum, CounterNum, Count);
   If ULStat <> 0 then exit;
   MemoData.Text := Format('Value read at counter # %d is %d counts.', [CounterNum, Count]);
   MemoData.Lines.Add (' ');

   ULStat := cbCStatus (BoardNum, CounterNum, StatusBits);
   If ULStat <> 0 then exit;
   if (StatusBits and C_UP_DOWN) <> 0 then
       begin
       MemoData.Lines.Add ('Direction: UP');
       end
   else
       begin
       MemoData.Lines.Add ('Direction: DOWN');
       end
   end;

procedure TfrmCount.cmdQuitClick(Sender: TObject);
begin
   Close;
end;

end.

unit Ct01;
{
 ULCT01.DPR***************************************************************

  File:                         CT01.PAS

  Library Call Demonstrated:    8254 Counter Functions
                                     cbC8254Config()
                                     cbCLoad()
                                     cbCIn()

  Purpose:                      Operate the counter.

  Demonstration:                Configures, loads and reads the counter.

  Other Library Calls:          cbErrHandling()

  Special Requirements:         Board 0 must have an 8254 counter.

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
   RegName:               Integer;
   Config:                Integer;
   LoadValue:             Integer;
   Count:                 Word;
   ErrReporting:          Integer;
   ErrHandling:           Integer;
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
    configure the counter for desired operation
      Parameters:
         BoardNum    :the number used by CB.CFG to describe this board
         CounterNum  :the counter to be setup
         Config      :the operation mode of counter to be configured
   }
   CounterNum := 1;
   Config := HIGHONLASTCOUNT;
   ULStat := cbC8254Config (BoardNum, CounterNum , Config);
   If ULStat <> 0 then exit;
   MemoData.Text := Format('Counter # %d has been configured for "HIGHONLASTCOUNT".', [CounterNum]);
   MemoData.Lines.Add (' ');
   {
   Send a starting value to the counter with cbCLoad()
     Parameters:
        BoardNum    :the number used by CB.CFG to describe this board
        RegName     :the reg. to be loading with the starting value
        LoadValue   :the starting value to place in the counter
   }
   LoadValue := 1000;
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
         CounterNum  :the counter to be read
         Count       :the value read from the counter
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

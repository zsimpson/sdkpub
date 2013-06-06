unit Ai13;
{
ULAI13.DPR================================================================

File:                         AI13.PAS

Library Call Demonstrated:    cbAInScan(), sampling mode options.

Purpose:                      Scans a range of A/D Input Channels and
                              stores the sample data in an array using
                              a user specified sampling mode.

Demonstration:                Displays the analog input on two channels.

Other Library Calls:          cbErrHandling()

Special Requirements:         Board 0 must have an A/D converter.
                              Analog signals on two input channels.
                              board must support the mode selected.

 (c) Copyright 1995 - 2002, Measurement Computing Corp.
 All rights reserved.
==========================================================================
}
interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, StdCtrls, ExtCtrls, cbw;

type
  TfrmAInScan = class(TForm)
    cmdStart: TButton;
    cmdQuit: TButton;
    Memo1: TMemo;
    rbDMA: TRadioButton;
    rbSINGLEIO: TRadioButton;
    rbBLOCKIO: TRadioButton;
    rbDEFAULT: TRadioButton;
    procedure cmdStartClick(Sender: TObject);
    procedure cmdQuitClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure rbDMAClick(Sender: TObject);
    procedure rbSINGLEIOClick(Sender: TObject);
    procedure rbBLOCKIOClick(Sender: TObject);
    procedure rbDEFAULTClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
   frmAInScan: TfrmAInScan;

implementation

{$R *.DFM}

var
   ULStat, Options:        Integer;
   MemHandle:              Integer;
   FirstPoint:             Longint;
   ADData:                 array[0..2048] of Word;
   ErrReporting:           Integer;
   ErrHandling:            Integer;
    RevLevel:                Single;
    Rate:                  LongInt;


const
   BoardNum:               Integer = 0;
   LowChan:                Integer = 0;
   HighChan:               Integer = 1;
   Count:                  Longint = 2048;
   TargetRate:            LongInt = 3125;
   Range:                  Integer = BIP5VOLTS;

procedure TfrmAInScan.FormCreate(Sender: TObject);
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
   MemHandle := cbWinBufAlloc (Count);
   Memo1.Text := 'Select a mode or click "Start"';
   Rate := TargetRate;
end;

procedure TfrmAInScan.cmdStartClick(Sender: TObject);
var
   index:         Integer;

begin
   Memo1.Text := 'Acquiring data....';
   Application.ProcessMessages;
   {
    Collect the values with cbAInScan()
        Parameters:
            BoardNum    :the number used by CB.CFG to describe this board
            LowChan     :low channel of the scan
            HighChan    :high channel of the scan
            Count       :the total number of A/D samples to collect
            Rate        :ignored because of EXTCLOCK option
            Gain        :the gain for the board
            MemHandle   :Windows memory set up with cbWinBufAlloc()
            Options     :data collection options
   }
   Rate := TargetRate;
   ULStat := cbAInScan(BoardNum, LowChan, HighChan,
                    Count, Rate, Range, MemHandle, Options);
   If ULStat <> 0 then exit;
   {
   Transfer the data from the Windows buffer to an array.  This data
   could also be accessed directly using a pointer.
   }
   FirstPoint := 0;
   ULStat := cbWinBufToArray (MemHandle, ADData[0], FirstPoint, Count);
   If ULStat <> 0 then exit;
   Memo1.Text := 'The first 8 values are:';
   Memo1.Lines.Add (' ');
   index := 0;
   while index < 8 do
   begin
      Memo1.Lines.Add ('Channel 0: ' + IntToStr(ADData[index]));
      Memo1.Lines.Add ('Channel 1: ' + IntToStr(ADData[index + 1]));
      Memo1.Lines.Add (' ');
      Inc(index, 2);
   end;
end;

procedure TfrmAInScan.rbDMAClick(Sender: TObject);
begin
   Options := CONVERTDATA + DMAIO;
   Memo1.Text := 'Click "Start" to acquire data and transfer in blocks via DMA.';
end;

procedure TfrmAInScan.rbSINGLEIOClick(Sender: TObject);
begin
   Options := CONVERTDATA + SINGLEIO;
   Memo1.Text := 'Click "Start" to acquire data and transfer via interrupt.';
end;

procedure TfrmAInScan.rbBLOCKIOClick(Sender: TObject);
begin
   Options := CONVERTDATA + BLOCKIO;
   Memo1.Text := 'Click "Start" to acquire data and transfer in blocks via REPINSW.';
end;

procedure TfrmAInScan.rbDEFAULTClick(Sender: TObject);
begin
   Options := CONVERTDATA;   {the Universal Library selects sample mode
                             based on speed of acquisition and board type}
end;

procedure TfrmAInScan.cmdQuitClick(Sender: TObject);
begin
   ULStat := cbWinBufFree (MemHandle);
   Close;
end;

end.

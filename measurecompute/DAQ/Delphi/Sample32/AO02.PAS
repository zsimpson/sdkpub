unit Ao02;
{
ULAO02.DPR****************************************************************

 File:                         AO02.PAS

 Library Call Demonstrated:    cbAOutScan()

 Purpose:                      Writes to a range of D/A Output Channels.

 Demonstration:                Sends a digital output to the D/A channels

 Other Library Calls:          cbErrHandling()

 Special Requirements:         Board 0 must have a D/A converter.

(c) Copyright 1995 - 2002, Measurement Computing Corp.
All rights reserved.
**************************************************************************
}
interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, StdCtrls, ExtCtrls, cbw;

type
  TfrmAOut = class(TForm)
    cmdQuit: TButton;
    MemoData: TMemo;
    cmdStart: TButton;
    procedure cmdQuitClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure cmdStartClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
   frmAOut: TfrmAOut;

implementation

{$R *.DFM}

var
   ULStat:                Integer;
   DAData:                array [0..2] of Word;
   ErrReporting:          Integer;
   ErrHandling:           Integer;
   MemHandle:             Integer;
   Rate:                  LongInt;
   RevLevel:              Single;

const
   BoardNum:              Integer = 0;
   NumChans:              Integer = 2;
   LowChan:               Integer = 0;
   HighChan:              Integer = 1;
   FirstPoint:            Longint = 0;
   Gain:                  Integer = BIP5VOLTS;
   Count:                 LongInt = 2;
   Options:               Integer = 0;

procedure TfrmAOut.FormCreate(Sender: TObject);
var
   index:      Integer;

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
   for index := LowChan to HighChan do       {load the output array with values}
   begin
       DAData[index] := 4095 div (index + 1) + 4095 mod (index + 1);
   end;
   MemHandle := cbWinBufAlloc (Count);
   If MemHandle = 0 then exit;
   ULStat := cbWinArrayToBuf (DAData[0], MemHandle, FirstPoint, Count);
   If ULStat <> 0 then exit;
   MemoData.Text := 'Click "Start" to send data to D/A';
end;

procedure TfrmAOut.cmdStartClick(Sender: TObject);
begin
   {
    send the output values to the D/A range using cbAOutScan()
     Parameters:
         BoardNum    :the number used by CB.CFG to describe this board
         LowChan     :the lower channel of the scan
         HighChan    :the upper channel of the scan
         Gain        :
         MemHandle   :
         OutValue    :array of values to send to the scanned channels
   }
   Rate := NOTUSED;
   ULStat := cbAOutScan (BoardNum, LowChan, HighChan, Count, Rate,
                                   Gain, MemHandle, Options);
   If ULStat <> 0 then exit;
   MemoData.Text := 'Data has been sent to D/A';
end;

procedure TfrmAOut.cmdQuitClick(Sender: TObject);
begin
   Close;
end;

end.

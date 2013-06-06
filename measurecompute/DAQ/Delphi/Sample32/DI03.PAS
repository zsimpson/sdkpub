unit Di03;
{
ULDI03.DPR ================================================================

 File:                         DI03.PAS

 Library Call Demonstrated:    cbDInScan()

 Purpose:                      Multiple reads of a digital input port.

 Demonstration:                Reads a digital input port and displays
                               the data.

 Other Library Calls:          cbDConfigPort()
                               cbErrHandling()

 Special Requirements:         Board 0 must support paced digital input
                               (for example, CIO-PDMA16).

 (c) Copyright 1995 - 2002, Measurement Computing Corp.
 All rights reserved.
===========================================================================
}
interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, StdCtrls, ExtCtrls, cbw;

type
  TfrmDIO = class(TForm)
    tmrDIn: TTimer;
    cmdStart: TButton;
    cmdQuit: TButton;
    MemoData: TMemo;
    procedure tmrDInTimer(Sender: TObject);
    procedure cmdStartClick(Sender: TObject);
    procedure cmdQuitClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  frmDIO: TfrmDIO;

implementation

{$R *.DFM}

var
   ULStat:          Integer;
   Options:         Integer;
   PortNum:         Integer;
   Direction:       Integer;
   DataBuffer:      array [0..14] of Word;
   MemHandle:       Integer;
   ErrReporting:    Integer;
   ErrHandling:     Integer;
   ValString:       string;
   Rate:            LongInt;
   Digits:          Integer;
   RevLevel:        Single;

const
   BoardNum:        Integer = 0;
   Count:           Longint = 15;
   FirstPoint:      Longint = 0;
   TargetRate:      Longint = 15;

procedure TfrmDIO.FormCreate(Sender: TObject);
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
   MemoData.Text := 'Click Start to read digital inputs...';
   MemHandle := cbWinBufAlloc (Count);
   {
   configure FIRSTPORTA and FIRSTPORTB for digital input
     Parameters:
        BoardNum    :the number used by CB.CFG to describe this board.
        PortNum     :the input port
        Direction   :sets the port for input or output
   }
   PortNum := FIRSTPORTB;
   Direction := DIGITALIN;
   ULStat := cbDConfigPort (BoardNum, PortNum, Direction);
   If ULStat <> 0 then exit;
   PortNum := FIRSTPORTA;
   ULStat := cbDConfigPort (BoardNum, PortNum, Direction);
   If ULStat <> 0 then exit;
end;

procedure TfrmDIO.cmdStartClick(Sender: TObject);
begin
   tmrDIn.Enabled := True;
end;

procedure TfrmDIO.tmrDInTimer(Sender: TObject);
var 
   index:         Integer;

begin
   {
   read the digital input ports
     Parameters:
        BoardNum    :the number used by CB.CFG to describe this board
        PortNum     :the input port
        Count       :number of times to read to the digital input
        Rate        :sample rate in samples/second
        DataBuffer[]:the array for the digital input values sent to the port
        Options     :options for data operation
   }
   Options := WORDXFER;
   {reading the values into the memory buffer}
   Rate := TargetRate;
   ULStat := cbDInScan (BoardNum, PortNum, Count, Rate, MemHandle, Options);
   If ULStat <> 0 then exit;
   ULStat := cbWinBufToArray (MemHandle, DataBuffer[0], FirstPoint, Count);
   If ULStat <> 0 then exit;
   MemoData.Text := 'The value of the port is (in hex): (FIRSTPORTA & B combined)';
   Digits := 4;
   for index := 0 to Count-1 do
   begin
      ValString := IntToHex(DataBuffer[index], Digits);
      MemoData.Lines.Add (Format('Read no. %d value:  %s', [index, ValString]));
      MemoData.Lines.Add (' ');
   end;
end;

procedure TfrmDIO.cmdQuitClick(Sender: TObject);
begin
   ULStat := cbWinBufFree (MemHandle);
   tmrDIn.Enabled := False;
   Close;
end;

end.

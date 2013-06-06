unit Do03;
{
ULDI03.DPR ================================================================

 File:                         DO03.PAS

 Library Call Demonstrated:    cbDOutScan()

 Purpose:                      Multiple writes to a digital output port.

 Demonstration:                Writes to a digital output port and displays
                               the data.

 Other Library Calls:          cbDConfigPort()
                               cbErrHandling()

 Special Requirements:         Board 0 must support paced digital output
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
    cmdStart: TButton;
    cmdQuit: TButton;
    MemoData: TMemo;
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
	Rate:            Longint;
   DataBuffer:      array [0..9] of Word;
   MemHandle:       Integer;
   ErrReporting:    Integer;
   ErrHandling:     Integer;
   ValString:       string;
   RevLevel:        Single;

const
   BoardNum:        Integer = 0;
   Count:           Longint = 10;
   FirstPoint:      Longint = 0;
   TargetRate:      Longint = 3;

procedure TfrmDIO.FormCreate(Sender: TObject);
var
   index:      Integer;
   data:       Integer;

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
   MemHandle := cbWinBufAlloc (Count);
   {
   configure FIRSTPORTA and FIRSTPORTB for digital input
     Parameters:
        BoardNum    :the number used by CB.CFG to describe this board.
        PortNum     :the input port
        Direction   :sets the port for input or output
   }
   PortNum := FIRSTPORTB;
   Direction := DIGITALOUT;
   ULStat := cbDConfigPort (BoardNum, PortNum, Direction);
   If ULStat <> 0 then exit;
   PortNum := FIRSTPORTA;
   ULStat := cbDConfigPort (BoardNum, PortNum, Direction);
   If ULStat <> 0 then exit;

	Rate := TargetRate;
   MemoData.Text := Format
   ('Click Start to write the following array to digital outputs at %dHz...', [Rate]);
   MemoData.Lines.Add (' ');
   {
   place values into the output array
   }
   data := 1;
   for  index := 0 to Count - 1 do
   begin
      DataBuffer[index] := data;
      ValString := ValString + Format( '   %d', [DataBuffer[index]]);
      data := data * 2
   end;
   MemoData.Lines.Add (ValString);
   {
   Transfer the array to the buffer set up using cbWinBufAlloc()
   }
   ULStat := cbWinArrayToBuf (DataBuffer[0], MemHandle, FirstPoint, Count);
   If ULStat <> 0 then exit;
end;

procedure TfrmDIO.cmdStartClick(Sender: TObject);
begin
   MemoData.Text := 'Writing array to digital outputs....';
   Application.ProcessMessages;

	Rate := TargetRate;
   Options := WORDXFER;
   ULStat := cbDOutScan (BoardNum, PortNum, Count, Rate, MemHandle, Options);
   If ULStat <> 0 then exit;
   MemoData.Text := 'Array has been written to digital outputs.'
end;

procedure TfrmDIO.cmdQuitClick(Sender: TObject);
begin
   ULStat := cbWinBufFree (MemHandle);
   Close;
end;

end.

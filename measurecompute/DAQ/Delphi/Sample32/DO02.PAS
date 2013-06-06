unit Do02;
{
ULDO02.DPR ================================================================

 File:                         DO02.PAS

 Library Call Demonstrated:    cbDBitOut()

 Purpose:                      Sets the state of a single digital output bit.

 Demonstration:                Configures FIRSTPORTA for output and
                               writes a bit value to the port.

 Other Library Calls:          cbDConfigPort()
                               cbErrHandling()

 Special Requirements:         Board 0 must have a programmable digital
                               I/O port.

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
    cmdQuit: TButton;
    MemoData: TMemo;
    chkBit0: TCheckBox;
    chkBit7: TCheckBox;
    chkBit6: TCheckBox;
    chkBit5: TCheckBox;
    chkBit4: TCheckBox;
    chkBit3: TCheckBox;
    chkBit2: TCheckBox;
    chkBit1: TCheckBox;
    procedure cmdQuitClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure chkBit0Click(Sender: TObject);
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
   DataValue:       Word;
   PortType:        Integer;
   BitNum:          Integer;
   BitValue:        Integer;
   Direction:       Integer;
   ErrReporting:    Integer;
   ErrHandling:     Integer;
   RevLevel:        Single;

const
   BoardNum:   Integer = 0;

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
   {
   configure FIRSTPORTA for digital output
     Parameters:
        BoardNum    :the number used by CB.CFG to describe this board.
        PortType    :the output port
        Direction   :sets the port for input or output
   }
   PortType := FIRSTPORTA;
   Direction := DIGITALOUT;
   ULStat := cbDConfigPort (BoardNum, PortType, Direction);
   If ULStat <> 0 then exit;
   {initialize port value}
   DataValue := 0;
   ULStat := cbDOut (BoardNum, PortType, DataValue);
   If ULStat <> 0 then exit;
   MemoData.Text := 'Use radio buttons to set digital bits...';
end;

procedure TfrmDIO.chkBit0Click(Sender: TObject);
begin
   {
   write BitValue to BitNum of FIRSTPORTA
     Parameters:
        BoardNum    :the number used by CB.CFG to describe this board
        PortType    :must be FIRSTPORTA or AUXPORT
        BitNum      :the number of the bit to be set to BitValue
        BitValue    :the value written to the port
   }
   BitNum := Integer((Sender As TCheckBox).Tag);
   BitValue := Integer((Sender As TCheckBox).Checked);
   PortType:=FIRSTPORTA;
   ULStat := cbDBitOut (BoardNum, PortType, BitNum, BitValue);
   If ULStat <> 0 then exit;
   MemoData.Text := 'The following bit and value was written to FIRSTPORTA:';
   MemoData.Lines.Add (' ');
   MemoData.Lines.Add (Format('Bit number %d was set to the value %d', [BitNum, BitValue]));
end;

procedure TfrmDIO.cmdQuitClick(Sender: TObject);
begin
   Close;
end;

end.

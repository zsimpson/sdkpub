unit Di02;
{
ULDI02.DPR ================================================================

File:                          DI02.PAS

 Library Call Demonstrated:    cbDBitIn()

 Purpose:                      Reads bits from a digital input port.

 Demonstration:                Configures FIRSTPORTA and B for input and
                               reads the bit values. Unstable bit values
                               are due to the nature of the 8255 input
                               ports when left floating.

 Other Library Calls:          cbDConfigPort()
                               cbErrHandling()

 Special Requirements:         Board 0 must have a programmable digital I/O port.

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
   PortNum:         Integer;
   PortType:        Integer;
   Direction:       Integer;
   ValString:       string;
   ErrReporting:    Integer;
   ErrHandling:     Integer;
   RevLevel:        Single;

   BitValue:        Word;


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
   MemoData.Text := 'Click Start to read digital inputs...';
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
   BitNum:        Integer;

begin
   PortType := FIRSTPORTA;            {when using cbDBitIn with programmable
                                      ports, PortType is ALWAYS FIRSTPORTA}
   ValString := '  ';
   for  BitNum := 0 to 15 do
   begin
      {
      read the input bits from the ports and display
        Parameters:
           BoardNum    :the number used by CB.CFG to describe this board
           PortType    :must be FIRSTPORTA (or AUXPORT for fixed ports)
           BitNum      :the input port
           BitValue    :the value read from the port
      }
      ULStat := cbDBitIn (BoardNum, PortType, BitNum, BitValue);
      If ULStat <> 0 then exit;
      ValString := '  ' + (IntToStr(BitValue)) + ValString;
   end;
   MemoData.Text := 'Bit status is:';
   MemoData.Lines.Add (' ');
   MemoData.Lines.Add ('Bitnum: 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0');
   MemoData.Lines.Add ('Bitval:' + ValString);
end;

procedure TfrmDIO.cmdQuitClick(Sender: TObject);
begin
   tmrDIn.Enabled := False;
   Close;
end;

end.

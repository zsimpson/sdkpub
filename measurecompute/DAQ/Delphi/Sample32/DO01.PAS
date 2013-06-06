unit Do01;
{
ULDO01.DPR ================================================================

 File:                         DO01.PAS

 Library Call Demonstrated:    cbDOut()

 Purpose:                      Writes a byte to a digital output port.

 Demonstration:                Configures FIRSTPORTA for output and
                               writes a value to the port.

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
    sbDOutVal: TScrollBar;
    procedure cmdQuitClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure sbDOutValScroll(Sender: TObject; ScrollCode: TScrollCode;
      var ScrollPos: Integer);
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
   PortNum:         Integer;
   Direction:       Integer;
   ErrReporting:    Integer;
   ErrHandling:     Integer;
   RevLevel:        Single;

const
   BoardNum:        Integer = 0;

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
        PortNum     :the output port
        Direction   :sets the port for input or output
   }
   PortNum := FIRSTPORTA;
   Direction := DIGITALOUT;
   ULStat := cbDConfigPort (BoardNum, PortNum, Direction);
   If ULStat <> 0 then exit;
   {initialize port value}
   DataValue := 0;
   ULStat := cbDOut (BoardNum, PortNum, DataValue);
   If ULStat <> 0 then exit;
   MemoData.Text := 'Use scroll bar to set digital output value...';
end;

procedure TfrmDIO.sbDOutValScroll(Sender: TObject; ScrollCode: TScrollCode;
  var ScrollPos: Integer);
begin
   DataValue := ScrollPos;
   {
   write the value to FIRSTPORTA
     Parameters:
        BoardNum    :the number used by CB.CFG to describe this board
        PortNum     :the output port
        DataValue   :the value written to the port
   }
   ULStat := cbDOut (BoardNum, PortNum, DataValue);
   If ULStat <> 0 then exit;
   MemoData.Text := Format('The byte value %d was written to FIRSTPORTA.', [DataValue]);
end;

procedure TfrmDIO.cmdQuitClick(Sender: TObject);
begin
   Close;
end;

end.

unit mbDi01;
{
ULMBDI01.DPR ================================================================

File:                         mbDI01.PAS

Library Call Demonstrated:    cbDIn() for MetraByte cards

Purpose:                      Reads a byte from a digital input port.

Demonstration:                Configures FIRSTPORTA for input and
                              reads the value on the port.

Other Library Calls:          cbErrHandling()

Special Requirements:         Board 1 must have a digital input port.

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
    EditBoardNum: TEdit;
    LabelBoardNum: TLabel;
    procedure tmrDInTimer(Sender: TObject);
    procedure cmdStartClick(Sender: TObject);
    procedure cmdQuitClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure EditBoardNumChange(Sender: TObject);
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
   BoardNum : Integer = 1;
   ULStat:          Integer;
   DataValue:       Word;
   BitValue:        Integer;
   PowerVal:        Integer;
   PortNum:         Integer;
   ErrReporting:    Integer;
   ErrHandling:     Integer;
   ValString:       String;
   Result:          Integer;
   RevLevel:        Single;

const
   Zero:       Integer = 0;
   One:        Integer = 1;

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
   PortNum:=FIRSTPORTA;

end;

procedure TfrmDIO.cmdStartClick(Sender: TObject);
begin
   tmrDIn.Enabled := True;
end;

procedure TfrmDIO.tmrDInTimer(Sender: TObject);
var I : integer;
begin
   {
   read the 7 bits digital input and display
     Parameters:
        BoardNum    :the number used by CB.CFG to describe this board
        PortNum     :the input port
        DataValue   :the value read from the port
   }
   ULStat := cbDIn (BoardNum, PortNum, DataValue);
   If ULStat <> 0 then exit;
   {
   display the value collected from the port
   }
   MemoData.Text := Format('The byte value at FIRSTPORTA is  %d', [DataValue]);
   MemoData.Lines.Add (' ');
   {
   parse DataValue into bit values to indicate on/off status
   }
   ValString := ' ';
   MemoData.Lines.Add ('Bit status is:');
   MemoData.Lines.Add ('  7  6  5  4  3  2  1  0');
   for  I := 0 to 7 do
   begin
      BitValue := Zero;
      PowerVal := 1 shl (I);
      Result := DataValue and PowerVal;
      if Result <> 0 then
      begin
         BitValue := One;
      end;
      ValString := '  ' + (IntToStr(BitValue)) + ValString;
   end;
   MemoData.Lines.Add (ValString);
end;

procedure TfrmDIO.cmdQuitClick(Sender: TObject);
begin
   tmrDIn.Enabled := False;
   Close;
end;

procedure TfrmDIO.EditBoardNumChange(Sender: TObject);
     var i : integer;
begin
    i:=StrToInt(EditBoardNum.Text);
    if (i<1) or (i>15) then EditBoardNum.Text:='1';
    BoardNum:=StrToInt(EditBoardNum.Text);
end;

end.

unit Ai01;
{
ULAI01.DPR ================================================================

 File:                          AI01.PAS

 Library Call Demonstrated:    cbAIn()

 Purpose:                      Reads an A/D Input Channel.

 Demonstration:                Displays the analog input on a user-specified
                               channel and converts the data to voltage.

 Other Library Calls:          cbErrHandling()
                               cbToEngUnits()

 Special Requirements:         Board 0 must have an A/D converter.
                               Analog signal on an input channel.

 (c) Copyright 1995 - 2002, Measurement Computing Corp.
 All rights reserved.
===========================================================================
}
interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, StdCtrls, ExtCtrls, cbw;

type
  TfrmAIn1 = class(TForm)
    tmrAIn: TTimer;
    cmdStart: TButton;
    cmdQuit: TButton;
    MemoData: TMemo;
    EditChan: TEdit;
    Label1: TLabel;
    procedure tmrAInTimer(Sender: TObject);
    procedure cmdStartClick(Sender: TObject);
    procedure cmdQuitClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure EditChanChange(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  frmAIn1: TfrmAIn1;

implementation

{$R *.DFM}

var
   ULStat:           Integer;
   DataValue:        Word;
   ValString:        string;
   ErrHandling:      Integer;
   ErrReporting:     Integer;
   Code:             Integer;
   EngUnits:         Single;
   RevLevel:         Single;
   Chan:             Integer;

const
   BoardNum:         Integer = 0;       {the number used by CB.CFG to describe this board}
   Range:            LongInt = BIP5VOLTS;   {set input range to +/-5V}
   DefaultChan:      Integer = 0;           {the channel used in this example to acquire data}

procedure TfrmAIn1.FormCreate(Sender: TObject);
begin
  {declare Revision Level}
   RevLevel := CURRENTREVNUM;
   ULStat := cbDeclareRevision(RevLevel);

  {set up internal error handling for the Universal Library}
   ErrReporting := PRINTALL;       {set Universal Library to print all errors}
   ErrHandling := STOPALL;         {set Universal Library to stop on errors}
   ULStat := cbErrHandling(ErrReporting, ErrHandling);
   MemoData.Text := 'Click Start to acquire data';

   Chan := DefaultChan;
end;

procedure TfrmAIn1.cmdStartClick(Sender: TObject);
begin
   tmrAIn.Enabled := True;
end;

procedure TfrmAIn1.tmrAInTimer(Sender: TObject);

begin
   ULStat := cbAIn(BoardNum, Chan, Range, DataValue);
   If ULStat <> 0 then exit;
   ValString := 'Channel ' + IntToStr(Chan) + ' counts:   ' + IntToStr(DataValue);
   MemoData.Text := ValString;
   ULStat := cbToEngUnits (BoardNum, Range, DataValue, EngUnits);
   If ULStat <> 0 then exit;
   ValString := Format('Channel %d voltage:    %f', [Chan, EngUnits]);
   MemoData.Lines.Add (ValString);
end;

procedure TfrmAIn1.EditChanChange(Sender: TObject);
begin
   Val(EditChan.Text, Chan, Code);
end;

procedure TfrmAIn1.cmdQuitClick(Sender: TObject);
begin
   tmrAIn.Enabled := False;
   Close;
end;

end.

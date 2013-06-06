unit Ao01;
{
ULAO01.DPR****************************************************************

 File:                         AO01.PAS

 Library Call Demonstrated:    cbAOut()

 Purpose:                      Writes to a D/A Output Channel.

 Demonstration:                Sends a digital output to D/A 0
                               until a key is pressed.

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
    EditChan: TEdit;
    Label1: TLabel;
    sbTrigVal: TScrollBar;
    lblTrigVal: TLabel;
    procedure cmdQuitClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure EditChanChange(Sender: TObject);
    procedure sbTrigValScroll(Sender: TObject; ScrollCode: TScrollCode;
      var ScrollPos: Integer);
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
   Chan:                  Integer;
   DataValue:             Word;
   ErrReporting:          Integer;
   ErrHandling:           Integer;
   EngUnits:              Single;
   Code:                  Integer;
   RevLevel:              Single;

const
   BoardNum:              Integer = 0;
   DefaultChan:           Integer = 0;
   Range:                 Integer = BIP5VOLTS;

procedure TfrmAOut.FormCreate(Sender: TObject);
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
   MemoData.Text := 'Use scroll bar to set analog output.';
   EngUnits := 0;
   ULStat := cbFromEngUnits(BoardNum, Range, EngUnits, DataValue);
   If ULStat <> 0 then exit;

   Chan := DefaultChan;
   ULStat := cbAOut (BoardNum, Chan, Range, DataValue);
   If ULStat <> 0 then exit;

end;

procedure TfrmAOut.EditChanChange(Sender: TObject);
begin
   Val(EditChan.Text, Chan, Code);
end;

procedure TfrmAOut.sbTrigValScroll(Sender: TObject;
          ScrollCode: TScrollCode; var ScrollPos: Integer);
begin
   EngUnits := ScrollPos / 100;
   lblTrigVal.Caption := Format('Analog output value = %f volts', [EngUnits]);
   ULStat := cbFromEngUnits(BoardNum, Range, EngUnits, DataValue);
   If ULStat <> 0 then exit;
   ULStat := cbAOut (BoardNum, Chan, Range, DataValue);
   If ULStat <> 0 then exit;
   MemoData.Text := Format('Code sent to output %d:  %d  (%f volts)', [Chan, DataValue, EngUnits]);
end;

procedure TfrmAOut.cmdQuitClick(Sender: TObject);
begin
   Close;
end;

end.

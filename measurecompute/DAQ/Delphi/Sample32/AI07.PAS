unit Ai07;
{
ULAI07.DPR****************************************************************

File:                         AI07.PAS

Library Call Demonstrated:    cbATrig()

Purpose:                      Waits for a specified analog input channel
                              go above or below a specified value.

Demonstration:                Reads the analog input on a user-specified
                              channel until the user-specified trigger
                              value is detected.

Other Library Calls:          cbErrHandling()

Special Requirements:         Board 0 must have an A/D converter.

(c) Copyright 1995 - 2002, Measurement Computing Corp.
All rights reserved.
**************************************************************************
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
    rbTrigTypeHi: TRadioButton;
    rbTrigTypeLo: TRadioButton;
    sbTrigVal: TScrollBar;
    lblTrigVal: TLabel;
    procedure cmdStartClick(Sender: TObject);
    procedure cmdQuitClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure EditChanChange(Sender: TObject);
    procedure rbTrigTypeHiClick(Sender: TObject);
    procedure rbTrigTypeLoClick(Sender: TObject);
    procedure sbTrigValScroll(Sender: TObject; ScrollCode: TScrollCode;
      var ScrollPos: Integer);
    function GetTrigCounts(bd:Integer; gain:Integer; val:Single):Word;
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
   ULStat:                Integer;
   DataValue, TrigValue:  Word;
   Polarity:              string;
   ErrReporting:          Integer;
   ErrHandling:           Integer;
   Code:                  Integer;
   EngUnits, TrigVolts:   Single;
   TrigType:              Integer;
   RevLevel:              Single;
   Chan:                  Integer;


const
   BoardNum:              Integer = 0;
   DefaultChan:           Integer = 0;
   Range:                 Integer = BIP5VOLTS;
   {
   data will be acquired when values are below TrigVolts
   }


procedure TfrmAIn1.FormCreate(Sender: TObject);
begin
  {declare Revision Level}
   RevLevel := CURRENTREVNUM;
   ULStat := cbDeclareRevision(RevLevel);

   {set up internal error handling for the Universal Library}
   ErrReporting := PRINTALL;       {set Universal Library to print all errors}
   ErrHandling := STOPALL;         {set Universal Library to stop on errors}
   ULStat := cbErrHandling(ErrReporting, ErrHandling);
   TrigType := TRIGBELOW;
   Polarity := 'Less than ';
   MemoData.Text := 'Click Start to acquire data';

   Chan := DefaultChan;
end;

procedure TfrmAIn1.cmdStartClick(Sender: TObject);
begin
   {
   monitor the channel with cbATrig()
        Parameters:
            BoardNum    :the number used by CB.CFG to describe this board
            Chan        :the input channel number
            TrigType    :specifies whether the trigger is to be above or
                         below TrigValue
            TrigValue   :the threshold value that will cause the trigger
            Gain        :the gain value
            DataValue   :the input value read from Chan
   }
   TrigValue := GetTrigCounts(BoardNum, Range, TrigVolts);
   MemoData.Text := Format('Waiting for the trigger value (%s %f volts on channel %d).....',
                                    [Polarity, TrigVolts, Chan]);
   Application.ProcessMessages;

   ULStat := cbATrig (BoardNum, Chan, TrigType, TrigValue, Range, DataValue);
   If ULStat <> 0 then exit;
   MemoData.Text := Format('The value that caused the trigger was %d ',
                                            [DataValue]);
   ULStat := cbToEngUnits (BoardNum, Range, DataValue, EngUnits);
   If ULStat <> 0 then exit;
   MemoData.Lines.Add (Format('Channel %d voltage:    %f volts', [Chan, EngUnits]));
end;

procedure TfrmAIn1.EditChanChange(Sender: TObject);
begin
   Val(EditChan.Text, Chan, Code);
end;

procedure TfrmAIn1.rbTrigTypeHiClick(Sender: TObject);
begin
   TrigType := TRIGABOVE;
   Polarity := 'Greater than '
end;

procedure TfrmAIn1.rbTrigTypeLoClick(Sender: TObject);
begin
   TrigType := TRIGBELOW;
   Polarity := 'Less than '
end;

procedure TfrmAIn1.sbTrigValScroll(Sender: TObject;
          ScrollCode: TScrollCode; var ScrollPos: Integer);
begin
   TrigVolts := ScrollPos / 2;
   lblTrigVal.Caption := Format('Trigger value = %f volts', [TrigVolts]);
end;

procedure TfrmAIn1.cmdQuitClick(Sender: TObject);
begin
   tmrAIn.Enabled := False;
   Close;
end;

function TfrmAIn1.GetTrigCounts(bd:Integer; gain:Integer; val:Single):Word;
var 
   FSCounts:      Word;
   FSEngUnits:    Single;
   fcounts:       Single;

begin
   {check if 'gain' is bipolar or unipolar}
   FSCounts := 0;
   ULStat := cbToEngUnits(bd, gain, FSCounts, FSEngUnits);
   if (FSEngUnits < 0) then
      begin
      {'gain' is bipolar}
      {test bitness of A/D}
      FSCounts := $0FFF; {max 12-bit value}
      ULStat := cbToEngUnits(bd, gain, FSCounts, FSEngUnits);
      if (FSEngUnits < 0) then
         begin
         {must be a 16-bit A/D}
         FSCounts := $FFFF;
         ULStat := cbToEngUnits(bd, gain, FSCounts, FSEngUnits);
         end;

      fcounts := (FSCounts/2.0)*(1.0+val/FSEngUnits);
      Result := Trunc(fcounts);
      end
   else
      begin
      {'gain' is unipolar}
      {test bitness of A/D}
      FSCounts := $0FFF;
      ULStat := cbToEngUnits(bd, gain, FSCounts, FSEngUnits);
      ULStat := cbToEngUnits(bd, gain, FSCounts+$1000, fcounts);
      if (fcounts >= 2.0*FSEngUnits) then
         begin
         {must be 16-bit A/D}
         FSCounts := $FFFF;
         ulstat := cbToEngUnits(bd, gain, FSCounts, FSEngUnits);
         end;

      fcounts := FSCounts*val/FSEngUnits;
      Result := Trunc(fcounts);
      end;

   if (Result>FSCounts) then Result := FSCounts;

end;

end.

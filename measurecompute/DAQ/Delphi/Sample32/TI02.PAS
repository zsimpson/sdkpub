unit Ti02;
{
ULTI02.DPR ================================================================

File:                         TI02.PAS

Library Call Demonstrated:    cbTInScan()

Purpose:                      Scans multiplexer input channels.

Demonstration:                Displays the temperature inputs on a range of
                              channels.

Other Library Calls:          cbErrHandling()

Special Requirements:         Board 0 must have an A/D converter with an
                              attached EXP board. Thermocouples must be
                              wired to mux channels 0 and 1.

(c) Copyright 1995 - 2002, Measurement Computing Corp.
All rights reserved.
===========================================================================
}
interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, StdCtrls, ExtCtrls, cbw;

type
  TfrmTInScan = class(TForm)
    tmrAIn: TTimer;
    cmdStart: TButton;
    cmdQuit: TButton;
    MemoData: TMemo;
    procedure tmrAInTimer(Sender: TObject);
    procedure cmdStartClick(Sender: TObject);
    procedure cmdQuitClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  frmTInScan: TfrmTInScan;

implementation

{$R *.DFM}

var
   ULStat:           Integer;
   Scale:            Integer;
   Options:          Integer;
   ADChan:           Integer;
   LowMUX:           Integer;
   HighMUX:          Integer;
   LowChan:          Integer;
   HighChan:         Integer;
   NumChans:         Integer;
   DataBuffer:       Array [0..3] of Single;
   ErrReporting:     Integer;
   ErrHandling:      Integer;
   RevLevel:         Single;
   UsesEXPs:        Integer;


const
   BoardNum:         Integer = 0;   {the number used by CB.CFG to describe this board}

procedure TfrmTInScan.FormCreate(Sender: TObject);
var
   InfoType:      Integer;
   DevNum:        Integer;
   ConfigItem:    Integer;

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
   determine via cbGetConfig if board uses expansion boards for temperature measurements
   }
   InfoType := BOARDINFO;
   DevNum   := 0;
   ConfigItem := BIUSESEXPS;
   UsesEXPs := 0;
   ULStat := cbGetConfig(InfoType, BoardNum, DevNum, ConfigItem, UsesEXPs);
   if (ULStat<>0) then UsesEXPs := 0;

   MemoData.Text := 'Click Start to acquire data';
end;

procedure TfrmTInScan.cmdStartClick(Sender: TObject);
begin
   {
   Parameters:
      BoardNum    :the number used by CB.CFG to describe this board
      LowChan     :the starting channel of the scan
      HighChan    :the ending channel of the scan
      Scale       :temperature scale (Celsius, Fahrenheit, Kelvin)
      Options     :either NOFILTER or FILTER to average data
      DataBuffer[]:the array where the temperature values are collected
   }
   Scale := FAHRENHEIT;
   Options := 0;
   LowMUX := 0;
   HighMUX := 1;
   if (UsesEXPs>1) then
       begin
      LowChan := (ADChan + 1) * 16 + LowMUX;
      HighChan := (ADChan + 1) * 16 + HighMUX;
      end
   else
       begin
      LowChan := LowMUX;
      HighChan := HighMUX;
      end;

   NumChans := HighMUX - LowMUX + 1;
   tmrAIn.Enabled := True;
end;

procedure TfrmTInScan.tmrAInTimer(Sender: TObject);
var
   Chan:       Integer;

begin
   {
   collect the data with cbTInScan()
   Input values will be collected from a thermocouple into TempValue
   }
   ULStat := cbTInScan (BoardNum, LowChan, HighChan, Scale, DataBuffer[0], Options);
   MemoData.Text := Format('Scanning from channel %d to channel %d.', [LowMUX, HighMUX]);
   MemoData.Lines.Add (' ');
   MemoData.Lines.Add ('The temperatures at the thermocouples are:');
   MemoData.Lines.Add (' ');
   for Chan := 0 to NumChans -1 do
   begin
      MemoData.Lines.Add (Format('Channel %d:   %f degrees F', [Chan, DataBuffer[Chan]]));
   end;
end;

procedure TfrmTInScan.cmdQuitClick(Sender: TObject);
begin
   tmrAIn.Enabled := False;
   Close;
end;

end.

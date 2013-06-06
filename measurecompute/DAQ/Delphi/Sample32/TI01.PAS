unit Ti01;
{
ULTI01.DPR ================================================================

File:                         TI01.PAS

Library Call Demonstrated:    cbTIn()

Purpose:                      Reads a multiplexer input channel.

Demonstration:                Displays the temperature input on a MUX
                              channel.

Other Library Calls:          cbErrHandling()

Special Requirements:         Board 0 must have an A/D converter with an
                              attached EXP board. A thermocouple must be
                              attached to mux channel 0.

(c) Copyright 1995 - 2002, Measurement Computing Corp.
All rights reserved.
===========================================================================
}
interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, StdCtrls, ExtCtrls, cbw;

type
  TfrmTIn = class(TForm)
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
  frmTIn: TfrmTIn;

implementation

{$R *.DFM}

var
   ULStat:           Integer;
   Options:          Integer;
   ADChan:           Integer;
   MUXChan:          Integer;
   Chan:             Integer;
   TempValue:        Single;
   TUnits:           String[11];
   ErrReporting:     Integer;
   ErrHandling:      Integer;
   RevLevel:         Single;
   UsesEXPs:        Integer;

const
   BoardNum:         Integer = 0;   {the number used by CB.CFG to describe this board}

procedure TfrmTIn.FormCreate(Sender: TObject);
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

procedure TfrmTIn.cmdStartClick(Sender: TObject);
begin
   tmrAIn.Enabled := True;
end;

procedure TfrmTIn.tmrAInTimer(Sender: TObject);
var 
   Scale:         Integer;

begin
   {
   collect the data with cbTIn()
   Input values will be collected from a thermocouple into TempValue
   }
   MemoData.Text := 'The temperature measured is:';
   MemoData.Lines.Add (' ');
   for Scale := 0 to 2 do
   begin
      {
      Parameters:
          BoardNum    :the number used by CB.CFG to describe this board
          Chan        :the input channel
          Scale       :temperature scale (Celsius, Fahrenheit, Kelvin)
          TempValue   :the temperature value collected
          Options     :either NOFILTER or FILTER to average data
      }
      Options := NOFILTER;
      ADChan := 0;
      MUXChan := 0;
     if UsesEXPs>0 then 
      Chan := (ADChan + 1) * 16 + MUXChan
     else
      Chan := MUXChan;

      ULStat := cbTIn (BoardNum, Chan, Scale, TempValue, Options);
      If ULStat <> 0 then
      begin
         tmrAIn.Enabled := False;
         exit;
      end;

      Case Scale of
         0:      TUnits := 'Celsius';
         1:      TUnits := 'Fahrenheit';
         2:      TUnits := 'Kelvin';
      end;
      MemoData.Lines.Add (Format
               ('Channel %d:   %f degrees %s', [Chan, TempValue, TUnits]));
   end;
end;

procedure TfrmTIn.cmdQuitClick(Sender: TObject);
begin
   tmrAIn.Enabled := False;
   Close;
end;

end.

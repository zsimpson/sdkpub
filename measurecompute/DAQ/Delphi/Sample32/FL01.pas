unit FL01;
 {
 ULFL01.DPR***************************************************************

  File:                         FL01.PAS

  Library Call Demonstrated:    cbFlashLED()

  Demonstration:                Flashes onboard LED

  Other Library Calls:          cbErrHandling()

  Special Requirements:         Board 0 must have an visible LED,
                                such as the miniLAB 1008 and PDM-1208LS.

(c) Copyright 2003, Measurement Computing Corp.
All rights reserved.
**************************************************************************
}
interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, cbw;

type
  TForm1 = class(TForm)
    Button1: TButton;
    procedure FlashClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.DFM}

var
   ULStat:          Integer;
   ErrReporting:    Integer;
   ErrHandling:     Integer;

const
   BoardNum:         Integer = 0;

procedure TForm1.FormCreate(Sender: TObject);
begin
   {
   set up internal error handling for the Universal Library
   }
   ErrReporting := PRINTALL;       {set Universal Library to print all errors}
   ErrHandling := STOPALL;         {set Universal Library to stop on errors}
   ULStat := cbErrHandling(ErrReporting, ErrHandling);
end;

procedure TForm1.FlashClick(Sender: TObject);
begin
     cbFlashLED(BoardNum)

end;



end.

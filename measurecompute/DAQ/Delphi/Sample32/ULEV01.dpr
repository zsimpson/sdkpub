program ULEV01;

uses
  Forms,
  EV01 in 'EV01.pas' {frmEventDisplay},
  cbw in '..\cbw.pas';

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TfrmEventDisplay, frmEventDisplay);
  Application.Run;
end.

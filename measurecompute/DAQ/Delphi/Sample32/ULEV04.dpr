program ULEV04;

uses
  Forms,
  EV04 in 'EV04.pas' {frmEventDisplay},
  cbw in '..\cbw.pas';

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TfrmEventDisplay, frmEventDisplay);
  Application.Run;
end.

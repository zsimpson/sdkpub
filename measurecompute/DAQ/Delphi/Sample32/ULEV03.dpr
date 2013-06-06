program ULEV03;

uses
  Forms,
  EV03 in 'EV03.pas' {frmEventDisplay},
  cbw in '..\cbw.pas';

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TfrmEventDisplay, frmEventDisplay);
  Application.Run;
end.

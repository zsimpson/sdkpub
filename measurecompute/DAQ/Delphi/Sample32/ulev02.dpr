program ulev02;

uses
  Forms,
  ev02 in 'ev02.pas' {frmEventDisplay},
  cbw in '..\cbw.pas';

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TfrmEventDisplay, frmEventDisplay);
  Application.Run;
end.

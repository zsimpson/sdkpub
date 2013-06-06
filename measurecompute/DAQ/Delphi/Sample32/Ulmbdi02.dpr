program Ulmbdi02;

uses
  Forms,
  mbDi02 in 'mbDI02.PAS' {frmDIO},
  cbw in '..\cbw.pas';

{$R *.RES}

begin
  Application.CreateForm(TfrmDIO, frmDIO);
  Application.Run;
end.

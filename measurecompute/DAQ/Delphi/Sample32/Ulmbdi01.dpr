program Ulmbdi01;

uses
  Forms,
  mbDi01 in 'mbDI01.PAS' {frmDIO},
  cbw in '..\cbw.pas';

{$R *.RES}

begin
  Application.CreateForm(TfrmDIO, frmDIO);
  Application.Run;
end.

program Ulmbdo02;

uses
  Forms,
  mbDo02 in 'mbDO02.PAS' {frmDIO},
  cbw in '..\cbw.pas';

{$R *.RES}

begin
  Application.CreateForm(TfrmDIO, frmDIO);
  Application.Run;
end.

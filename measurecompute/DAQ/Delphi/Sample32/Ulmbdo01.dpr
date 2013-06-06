program Ulmbdo01;

uses
  Forms,
  mbDo01 in 'mbDO01.PAS' {frmDIO},
  cbw in '..\cbw.pas';

{$R *.RES}

begin
  Application.CreateForm(TfrmDIO, frmDIO);
  Application.Run;
end.

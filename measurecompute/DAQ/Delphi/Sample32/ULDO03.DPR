program Uldo03;

uses
  Forms,
  Do03 in 'DO03.PAS' {frmDIO},
  cbw in '..\cbw.pas';

{$R *.RES}

begin
  Application.CreateForm(TfrmDIO, frmDIO);
  Application.Run;
end.

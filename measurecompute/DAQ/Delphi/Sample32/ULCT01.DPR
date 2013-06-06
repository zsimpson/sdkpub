program Ulct01;

uses
  Forms,
  Ct01 in 'CT01.PAS' {frmCount},
  cbw in '..\cbw.pas';

{$R *.RES}

begin
  Application.CreateForm(TfrmCount, frmCount);
  Application.Run;
end.

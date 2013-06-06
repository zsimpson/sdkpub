program Ulfi01;

uses
  Forms,
  Fi01 in 'FI01.PAS' {frmFileAInScan},
  cbw in '..\cbw.pas';

{$R *.RES}

begin
  Application.CreateForm(TfrmFileAInScan, frmFileAInScan);
  Application.Run;
end.

program Ulfi02;

uses
  Forms,
  Fi02 in 'FI02.PAS' {frmFileAInScan},
  cbw in '..\cbw.pas';

{$R *.RES}

begin
  Application.CreateForm(TfrmFileAInScan, frmFileAInScan);
  Application.Run;
end.

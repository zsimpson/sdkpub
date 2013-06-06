program Ulfi03;

uses
  Forms,
  Fi03 in 'FI03.PAS' {frmFileAInScan},
  cbw in '..\cbw.pas';

{$R *.RES}

begin
  Application.CreateForm(TfrmFileAInScan, frmFileAInScan);
  Application.Run;
end.

program Ulai06;

uses
  Forms,
  Ai06 in 'AI06.PAS' {frmAInScan},
  cbw in '..\cbw.pas';

{$R *.RES}

begin
  Application.CreateForm(TfrmAInScan, frmAInScan);
  Application.Run;
end.

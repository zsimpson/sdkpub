program Ulai03;

uses
  Forms,
  Ai03 in 'AI03.PAS' {frmAInScan},
  cbw in '..\cbw.pas';

{$R *.RES}

begin
  Application.CreateForm(TfrmAInScan, frmAInScan);
  Application.Run;
end.

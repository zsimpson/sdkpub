program Ulai14;

uses
  Forms,
  Ai14 in 'AI14.PAS' {frmAInScan},
  cbw in '..\cbw.pas';

{$R *.RES}

begin
  Application.CreateForm(TfrmAInScan, frmAInScan);
  Application.Run;
end.

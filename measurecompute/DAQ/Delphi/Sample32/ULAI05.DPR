program Ulai05;

uses
  Forms,
  Ai05 in 'AI05.PAS' {frmAInScan},
  cbw in '..\cbw.pas';

{$R *.RES}

begin
  Application.CreateForm(TfrmAInScan, frmAInScan);
  Application.Run;
end.

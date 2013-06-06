program Ulai09;

uses
  Forms,
  Ai09 in 'AI09.PAS' {frmAInScan},
  cbw in '..\cbw.pas';

{$R *.RES}

begin
  Application.CreateForm(TfrmAInScan, frmAInScan);
  Application.Run;
end.

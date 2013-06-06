program Ulaio01;

uses
  Forms,
  Aio01 in 'Aio01.pas' {frmAInAoutScan},
  cbw in '..\cbw.pas';

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TfrmAInAoutScan, frmAInAoutScan);
  Application.Run;
end.

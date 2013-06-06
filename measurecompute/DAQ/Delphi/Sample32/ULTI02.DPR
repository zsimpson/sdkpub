program Ulti02;

uses
  Forms,
  Ti02 in 'TI02.PAS' {frmTInScan},
  cbw in '..\cbw.pas';

{$R *.RES}

begin
  Application.CreateForm(TfrmTInScan, frmTInScan);
  Application.Run;
end.

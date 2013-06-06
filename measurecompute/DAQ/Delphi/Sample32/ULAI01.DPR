program Ulai01;

uses
  Forms,
  Ai01 in 'AI01.PAS' {frmAIn1},
  cbw in '..\cbw.pas';

{$R *.RES}

begin
  Application.CreateForm(TfrmAIn1, frmAIn1);
  Application.Run;
end.

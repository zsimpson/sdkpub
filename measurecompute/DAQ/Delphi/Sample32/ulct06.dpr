program Ulct06;

uses
  Forms,
  Ct06 in 'CT06.PAS' {frmCount},
  cbw in '..\cbw.pas';

{$R *.RES}

begin
  Application.CreateForm(TfrmCount, frmCount);
  Application.Run;
end.

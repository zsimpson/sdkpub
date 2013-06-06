program Ulct04;

uses
  Forms,
  Ct04 in 'CT04.PAS' {frmCount},
  cbw in '..\cbw.pas';

{$R *.RES}

begin
  Application.CreateForm(TfrmCount, frmCount);
  Application.Run;
end.

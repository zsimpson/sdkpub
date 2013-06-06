program Ulct03;

uses
  Forms,
  Ct03 in 'CT03.PAS' {frmCount},
  cbw in '..\cbw.pas';

{$R *.RES}

begin
  Application.CreateForm(TfrmCount, frmCount);
  Application.Run;
end.

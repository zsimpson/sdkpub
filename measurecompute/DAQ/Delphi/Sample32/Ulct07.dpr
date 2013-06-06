program ULCT07;

uses
  Forms,
  CT07 in 'CT07.PAS' {frmCount},
  cbw in '..\cbw.pas';

{$R *.RES}

begin
  Application.CreateForm(TfrmCount, frmCount);
  Application.Run;
end.

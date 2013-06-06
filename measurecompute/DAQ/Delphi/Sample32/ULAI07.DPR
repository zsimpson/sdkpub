program Ulai07;

uses
  Forms,
  Ai07 in 'AI07.PAS' {frmAIn1},
  cbw in '..\cbw.pas';

{$R *.RES}

begin
  Application.CreateForm(TfrmAIn1, frmAIn1);
  Application.Run;
end.

program Ulao01;

uses
  Forms,
  Ao01 in 'AO01.PAS' {frmAOut},
  cbw in '..\cbw.pas';

{$R *.RES}

begin
  Application.CreateForm(TfrmAOut, frmAOut);
  Application.Run;
end.

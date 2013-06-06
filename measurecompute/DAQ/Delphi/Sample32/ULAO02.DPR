program Ulao02;

uses
  Forms,
  Ao02 in 'AO02.PAS' {frmAOut},
  cbw in '..\cbw.pas';

{$R *.RES}

begin
  Application.CreateForm(TfrmAOut, frmAOut);
  Application.Run;
end.

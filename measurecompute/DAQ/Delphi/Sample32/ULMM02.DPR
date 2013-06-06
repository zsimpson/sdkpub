program Ulmm02;

uses
  Forms,
  Mm02 in 'MM02.PAS' {frmXMem},
  cbw in '..\cbw.pas';

{$R *.RES}

begin
  Application.CreateForm(TfrmXMem, frmXMem);
  Application.Run;
end.

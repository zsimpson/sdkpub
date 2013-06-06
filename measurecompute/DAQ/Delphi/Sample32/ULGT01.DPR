program Ulgt01;

uses
  Forms,
  Gt01 in 'GT01.PAS' {frmErrors},
  cbw in '..\cbw.pas';

{$R *.RES}

begin
  Application.CreateForm(TfrmErrors, frmErrors);
  Application.Run;
end.

program Uldi06;

uses
  Forms,
  Di06 in 'DI06.PAS' {frmDIO},
  cbw in '..\cbw.pas';

{$R *.RES}

begin
  Application.CreateForm(TfrmDIO, frmDIO);
  Application.Run;
end.

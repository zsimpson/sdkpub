program Ulgt03;

uses
  Forms,
  Gt03 in 'GT03.PAS' {frmConfig},
  cbw in '..\cbw.pas';

{$R *.RES}

begin
  Application.CreateForm(TfrmConfig, frmConfig);
  Application.Run;
end.

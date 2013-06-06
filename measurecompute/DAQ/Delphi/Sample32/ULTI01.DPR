program Ulti01;

uses
  Forms,
  Ti01 in 'TI01.PAS' {frmTIn},
  cbw in '..\cbw.pas';

{$R *.RES}

begin
  Application.CreateForm(TfrmTIn, frmTIn);
  Application.Run;
end.

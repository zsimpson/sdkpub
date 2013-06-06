program Ulmm01;

uses
  Forms,
  Mm01 in 'MM01.PAS' {frmXMem},
  cbw in '..\cbw.pas';

{$R *.RES}

begin
  Application.CreateForm(TfrmXMem, frmXMem);
  Application.Run;
end.

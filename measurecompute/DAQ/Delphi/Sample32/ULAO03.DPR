program Ulao03;

uses
  Forms,
  Ao03 in 'Ao03.pas' {frmAO03},
  Cbw in '..\Cbw.pas';

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TfrmAO03, frmAO03);
  Application.Run;
end.

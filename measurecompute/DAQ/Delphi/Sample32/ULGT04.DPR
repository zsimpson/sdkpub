program Ulgt04;

uses
  Forms,
  Gt04 in 'GT04.PAS' {frmBoards},
  cbw in '..\cbw.pas';

{$R *.RES}

begin
  Application.CreateForm(TfrmBoards, frmBoards);
  Application.Run;
end.

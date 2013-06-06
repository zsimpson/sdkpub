program ULFL01;

uses
  Forms,
  FL01 in 'FL01.pas' {Form1},
  Cbw in '..\Cbw.pas';

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.

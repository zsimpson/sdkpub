unit Gt01;
{
ULGT01.DPR ================================================================

 File:                         GT01.PAS

 Library Call Demonstrated:    cbGetErrMsg()

 Purpose:                      Returns the error message associated
                               with an error code.

 Demonstration:                An invalid board # is generated and the
                               associated message is retrieved.

 Other Library Calls:          cbErrHandling()

 (c) Copyright 1995 - 2002, Measurement Computing Corp.
 All rights reserved.
===========================================================================
}
interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, StdCtrls, ExtCtrls, cbw;

type
  TfrmErrors = class(TForm)
    cmdStart: TButton;
    cmdQuit: TButton;
    MemoData: TMemo;
    procedure cmdStartClick(Sender: TObject);
    procedure cmdQuitClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  frmErrors: TfrmErrors;

implementation

{$R *.DFM}

var
   ULStat:          Integer;
   Range:           Integer;
   ECode:           Integer;
   DataValue:       Word;
   ErrMessage:      String;
   ErrReporting:    Integer;
   ErrHandling:     Integer;
   ErrMsg:          PChar;
   NullString:      array [0..ERRSTRLEN] of Char;
   RevLevel:              Single;

   {
   String arguments in the Universal Library (and most DLLs) expect a
   null terminated string.  This can be accomplished in Delphi by setting
   up an array of type Char and assigning a pointer (ErrMsg) to it. The array
   must be dimensioned to at least the length of the longest message.
   }

const
   BoardNum:        Integer = 99;    {invalid board number used to generate error}
   Chan:            Integer = 0;

procedure TfrmErrors.FormCreate(Sender: TObject);
begin
  {declare Revision Level}
   RevLevel:= CURRENTREVNUM;
   ULStat := cbDeclareRevision(RevLevel);

   {
   set up internal error handling for the Universal Library
   }
   ErrReporting := DONTPRINT;      {set Universal Library ignore all errors}
   ErrHandling := DONTSTOP;
   ULStat := cbErrHandling(ErrReporting, ErrHandling);
   ErrMsg := @NullString;          {assign a pointer to the Char array}
   MemoData.Text := 'Click Start to generate an error.';
end;

procedure TfrmErrors.cmdStartClick(Sender: TObject);
begin
   {
   Generate an error by calling cbAIn with an invalid board number
   }
   ULStat := cbAIn(BoardNum, Chan, Range, DataValue);
   {
   trap the error and determine the message to print
     Parameters:
        ULStat        :the error code returned by the invalid call statement
        ErrMsg        :pointer to the Char array NullString
   }
   ECode := cbGetErrMsg (ULStat, ErrMsg);
   ErrMessage := StrPas(ErrMsg);      {convert the null terminated string to Pascal string}
   MemoData.Text := 'The following error was detected:';
   MemoData.Lines.Add (' ');
   MemoData.Lines.Add (format('Error Code: %d', [ULStat]));
   MemoData.Lines.Add (Format('Message: %s', [ErrMessage]));
end;

procedure TfrmErrors.cmdQuitClick(Sender: TObject);
begin
   Close;
end;

end.

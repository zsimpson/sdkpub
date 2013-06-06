unit Gt04;
{
ULGT04.DPR=================================================================
File:                         GT04.PAS

Library Call Demonstrated:    cbGetBoardName()

Purpose:                      Prints a list of all boards installed in
                              the system.  Prints a list of all supported
                              boards.

Other Library Calls:          cbErrHandling(), cbGetConfig()

Special Requirements:         ---

(c) Copyright 1995 - 2002, Measurement Computing Corp.
All rights reserved.
===========================================================================
}
interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, StdCtrls, ExtCtrls, cbw;

type
  TfrmBoards = class(TForm)
    cmdQuit: TButton;
    MemoData: TMemo;
    cmdList: TButton;
    procedure cmdQuitClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure cmdListClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }

  end;

var
  frmBoards: TfrmBoards;


implementation

{$R *.DFM}

var
   ULStat:          Integer;
   NumBoards:       Integer;
   ErrReporting:    Integer;
   ErrHandling:     Integer;
   InfoType:        Integer;
   DevNum:          Integer;
   ConfigItem:      Integer;
   BoardName:       PChar;
   NullString:      array [0..BOARDNAMELEN] of Char;
   RevLevel:              Single;
   ConfigVal:       Integer;

   {
   String arguments in the Universal Library (and most DLLs) expect a
   null terminated string.  This can be accomplished in Delphi by setting
   up an array of type Char and assigning a pointer (BoardName) to it. The array
   must be dimensioned to at least the length of the longest message.
   }


procedure TfrmBoards.FormCreate(Sender: TObject);

var
  BoardNum: Integer;

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
   BoardName := @NullString;          {assign a pointer to the Char array}
   MemoData.Text := 'List of Installed Boards:';
   frmBoards.MemoData.Lines.Add (' ');
   {
   Get the number of boards installed in system
   }
   InfoType := GLOBALINFO;
   BoardNum := 0;
   DevNum := 0;
   ConfigItem := GINUMBOARDS;

   cbGetConfig (InfoType, BoardNum, DevNum, ConfigItem, ConfigVal);
   NumBoards := ConfigVal;
   for BoardNum := 0 to NumBoards -1 do
   begin
      {
      Get board name of each board using board number
      }
      cbGetBoardName (BoardNum, BoardName);
      frmBoards.MemoData.Lines.Add (StrPas(BoardName));
   end;
end;

procedure TfrmBoards.cmdListClick(Sender: TObject);
begin
   MemoData.Text := 'List of supported boards:';
   frmBoards.MemoData.Lines.Add (' ');
   {
   Get the first board type in list of supported boards
   (the first string in the list of names is "Not Installed")
   }
   cbGetBoardName (GETFIRST, BoardName);
   frmBoards.MemoData.Lines.Add (StrPas(BoardName));
   while StrLen(BoardName) > 0 do
   begin
      {
      Get each consecutive board type in list
      }
      cbGetBoardName (GETNEXT, BoardName);
      frmBoards.MemoData.Lines.Add (StrPas(BoardName));
   end;
end;

procedure TfrmBoards.cmdQuitClick(Sender: TObject);
begin
   Close;
end;

end.

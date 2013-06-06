unit Gt03;
{
ULGT03.DPR=================================================================
File:                         GT03.PAS

Library Call Demonstrated:    cbGetConfig()

Purpose:                      Prints a list of all boards installed in
                              the system and their base addresses.  Also
                              prints the addresses of each digital and
                              counter device on each board and any EXP
                              boards that are connected to A/D channels.

Other Library Calls:          cbErrHandling(), cbGetBoardName()

 (c) Copyright 1995 - 2002, Measurement Computing Corp.
 All rights reserved.
===========================================================================
}
interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, StdCtrls, ExtCtrls, cbw;

type
  TfrmConfig = class(TForm)
    cmdQuit: TButton;
    MemoData: TMemo;
    procedure cmdQuitClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }

  end;

var
  frmConfig: TfrmConfig;

procedure PrintADInfo (BoardNum: Integer);
procedure PrintDAInfo (BoardNum: Integer);
procedure PrintDigInfo (BoardNum: Integer);
procedure PrintCtrInfo (BoardNum: Integer);
procedure PrintExpInfo (BoardNum: Integer);

implementation

{$R *.DFM}

var
   BoardNum:        Integer;
   ULStat:          Integer;
   ErrReporting:    Integer;
   ErrHandling:     Integer;
   InfoType:        Integer;
    DevNum:          SmallInt;
    ConfigVal:       Integer;
    NumBoards:       SmallInt;
    BoardType:       SmallInt;
    BaseAdr:         Integer;
   ConfigItem:      Integer;
   BoardName:       PChar;
   NullString:      array [0..BOARDNAMELEN] of Char;
   NumADChans:      array [0..10] of Integer;
   RevLevel:              Single;

   {
   String arguments in the Universal Library (and most DLLs) expect a
   null terminated string.  This can be accomplished in Delphi by setting
   up an array of type Char and assigning a pointer (BoardName) to it. The array
   must be dimensioned to at least the length of the longest message.
   }

procedure TfrmConfig.FormCreate(Sender: TObject);
var
   Board:   Integer;
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
   BoardNum := 0;
   BoardName := @NullString;          {assign a pointer to the Char array}
   MemoData.Text := 'List of Installed Boards:';
   {
   Get the number of boards installed in system
   }
   InfoType := GLOBALINFO;
   BoardNum := 0;
   DevNum := 0;
   ConfigItem := GINUMBOARDS;

   cbGetConfig (InfoType, BoardNum, DevNum, ConfigItem, ConfigVal);
   NumBoards := ConfigVal;
   for Board := 0 to NumBoards -1 do
   begin
      {
      Get board type of each board
      }
      InfoType := BOARDINFO;
      ConfigItem := BIBOARDTYPE;
      cbGetConfig (InfoType, Board, DevNum, ConfigItem, ConfigVal);
      BoardType := ConfigVal;
      if ConfigVal > 0 then      {If a board is installed}
      begin
         {Get the board's name using board type (BoardNum could also be used)}
         cbGetBoardName (Board, BoardName);
         frmConfig.MemoData.Lines.Add (' ');
         frmConfig.MemoData.Lines.Add (StrPas(BoardName));
         {Get the board's base address}
         ConfigItem := BIBASEADR;
         cbGetConfig (InfoType, Board, DevNum, ConfigItem, ConfigVal);
         BaseAdr := ConfigVal;
         frmConfig.MemoData.Lines.Add ('Base Address = ' + IntToHex(Word(BaseAdr), 3));
         PrintADInfo (Board);
         PrintDAInfo (Board);
         PrintDigInfo (Board);
         PrintCtrInfo (Board);
         PrintExpInfo (Board);
      end;
   end;
end;

procedure PrintDAInfo;
var
    NumDevs: SmallInt;
begin
   InfoType := BOARDINFO;
   DevNum := 0;
   ConfigItem := BINUMDACHANS;

   cbGetConfig (InfoType, BoardNum, DevNum, ConfigItem, ConfigVal);
   NumDevs := ConfigVal;
   frmConfig.MemoData.Lines.Add (Format('        Number of D/A channels: %d', [NumDevs]));
end;

procedure PrintADInfo;
var
    NumDevs: SmallInt;
begin
   InfoType := BOARDINFO;
   DevNum := 0;
   ConfigItem := BINUMADCHANS;

   cbGetConfig (InfoType, BoardNum, DevNum, ConfigItem, ConfigVal);
   NumDevs := ConfigVal;
   NumADChans[BoardNum] := NumDevs;
   frmConfig.MemoData.Lines.Add (Format('        Number of A/D channels: %d', [NumDevs]));
end;

procedure PrintDigInfo;
var
    NumDevs: Integer;
    NumBits: Integer;
  Device:    Integer;
begin
   {get the number of digital devices for this board }
   InfoType := BOARDINFO;
   DevNum := 0;
   ConfigItem := BIDINUMDEVS;

   cbGetConfig (InfoType, BoardNum, DevNum, ConfigItem, NumDevs);
   for Device := 0 to NumDevs -1 do
   begin
      {For each digital device, get the base address and number of bits }
      InfoType := DIGITALINFO;
      ConfigItem := DINUMBITS;
      cbGetConfig (InfoType, BoardNum, Device, ConfigItem, NumBits);
      frmConfig.MemoData.Lines.Add (Format
                     ('        Digital Device #%d : %d bits', [Device, NumBits]));
   end;
end;

procedure PrintCtrInfo;
var
   NumDevs: Integer;

begin
   {Get the number of counter devices for this board }
   InfoType := BOARDINFO;
   DevNum := 0;
   ConfigItem := BICINUMDEVS;
   cbGetConfig (InfoType, BoardNum, DevNum, ConfigItem, NumDevs);
 

   frmConfig.MemoData.Lines.Add (Format
                     ('        Counter Devices: #%d', [NumDevs]));
end;

procedure PrintExpInfo;
var
    DevIdx: Integer;
    NumDevs: Integer;
    BoardType: Integer;
    ADChan1: Integer;
    ADChan2: Integer;

begin
   { Get the number of Exps attached to BoardNum }
   InfoType := BOARDINFO;
   DevNum   := 0;
   ConfigItem := BINUMEXPS;
   cbGetConfig(InfoType, BoardNum, DevNum, ConfigItem, NumDevs);
         
   for DevIdx := 0 to NumDevs-1 do    
      begin      
      ConfigItem  := XIBOARDTYPE;
      InfoType    := EXPANSIONINFO;
      cbGetConfig(InfoType, BoardNum, DevIdx, ConfigItem, BoardType);

      ConfigItem := XIMUXADCHAN1;
      cbGetConfig(InfoType, BoardNum, DevIdx, ConfigItem, ADChan1);

      if (BoardType = 770) Then
         begin
         ConfigItem := XIMUXADCHAN2;
         cbGetConfig(InfoType, BoardNum, DevIdx, ConfigItem, ADChan2);
         frmConfig.MemoData.Lines.Add (Format
                  ('        A/D channels #%d and #%d connected to EXP (devID=%d)', [ADChan1, ADChan2, BoardType]));
         end
      else
         frmConfig.MemoData.Lines.Add (Format
                  ('        A/D channel #%d connected to EXP (devID=%d)', [ADChan1, BoardType]));
      
      end;

end;

procedure TfrmConfig.cmdQuitClick(Sender: TObject);
begin
   Close;
end;

end.

unit Mm02;
{
ULMM02.DPR================================================================

File:                         MM02.PAS

Library Call Demonstrated:    cbMemRead() and cbMemWrite()

Purpose:                      Write data to a memory board and then read
                              it back again

Demonstrates:                 Reading and writing data to memory in blocks

Other Library Calls:          cbErrHandling()

Special Requirements:         Board 5 must be a memory borad

(c) Copyright 1995 - 2002, Measurement Computing Corp.
All rights reserved.
***************************************************************************/
}
interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, StdCtrls, ExtCtrls, cbw;

type
  TfrmXMem = class(TForm)
    cmdQuit: TButton;
    Memo1: TMemo;
    procedure cmdQuitClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  frmXMem: TfrmXMem;

implementation

{$R *.DFM}

var
   ULStat:          Integer;
   FirstPoint:      Integer;
   BoardNum:        Integer;
   Count:           LongInt;
   DataBuffer1:     Array [0..500] of Word;
   DataBuffer2:     Array [0..500] of Word;
   RevLevel:        Single;

const
   MEMBOARD:    Integer = 5;
   NUMPOINTS:   Integer = 100;
   NUMBLOCKS:   Integer = 5;

procedure TfrmXMem.FormCreate(Sender: TObject);
var
   BlockNum:        Integer;
   index:           Integer;

begin
  {declare Revision Level}
   RevLevel := CURRENTREVNUM;
   ULStat := cbDeclareRevision(RevLevel);

   {This program writes 500 values to the memory board by writing
   5 blocks of 100 values to consecutive locations in the memory board.

   The values that are written correspond to the memory board address that
   they are stored at.  So for example the value 203 is stored at address 203
   in memory.
   It then reads the data back and displays it. }

   FirstPoint := 0;                    { Set address of first point to write }
   for BlockNum:=0 to NUMBLOCKS-1 do   { load the arrays with values }
   begin
      for index := 0 to NUMPOINTS do
      begin
         DataBuffer1[index] := BlockNum * NUMPOINTS+index;
         DataBuffer2[index] := 0;
      end;
      {
      Write the block to the memory board
       MEMBOARD - Board number of the memory board
       DataBuffer1 - Array of data to be written
       FirstPoint - Address to write first point (or NEXTONE)
       NUMPOINTS - Number of points to write
      }
      BoardNum := MEMBOARD;
      Count := NUMPOINTS;
      ULStat := cbMemWrite (BoardNum, DataBuffer1[0], FirstPoint, Count);
      FirstPoint := FROMHERE;
   end;
   {Address=   0        100       200       300       400}
   FirstPoint := 0;                    { Set address of first point to read }
   Memo1.Text := 'Note that values = address location:';
   Memo1.Lines.Add ('Data read from memory board...');
   for BlockNum:=0 to NUMBLOCKS-1 do
   begin
      {
      Read the block from the memory board
       MEMBOARD - Board number of the memory board
       DataBuffer2 - Array data is to be read into
       FirstPoint - Address of first point to read (or NEXTONE)
       NUMPOINTS - Number of points to read
      }
      ULStat := cbMemRead (BoardNum, DataBuffer2[0], FirstPoint, Count);
      FirstPoint := FROMHERE;
      Memo1.Lines.Add (' ');
      for index := 0 to 5 do
      begin
         Memo1.Lines.Add (Format('Address %d = %d', [BlockNum*Count + index, DataBuffer2[index]]));
      end;
   end;
end;

procedure TfrmXMem.cmdQuitClick(Sender: TObject);
begin
   Close;
end;

end.

unit Mm03;
{
ULMM03.DPR================================================================

File:                         MM03.PAS

Library Call Demonstrated:    cbAInScan() with EXTMEMORY option

Purpose:                      Collect data from A/D to memory board

Demonstrates:                 How to use the EXTMEMORY option to
                              send data to a memory board and how to
                              read the data back again.

Other Library Calls:          cbMemRead(), cbErrHandling()

Special Requirements:         Board 0 must be an A/D board with DT-Connect
                              support.  Board 5 must be a memory board.
                              A/D and memory boards must be connected together
                              via a DT-Connect cable.

 (c) Copyright 1995 - 2002, Measurement Computing Corp.
 All rights reserved.
==========================================================================
}
interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, StdCtrls, ExtCtrls, cbw;

type
  TfrmAInScan = class(TForm)
    cmdStart: TButton;
    cmdQuit: TButton;
    Memo1: TMemo;
    cmdReadBlock: TButton;
    procedure cmdStartClick(Sender: TObject);
    procedure cmdQuitClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure cmdReadBlockClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
   frmAInScan: TfrmAInScan;

implementation

{$R *.DFM}

const
   ADBOARD:     Integer = 0;
   MEMBOARD:    Integer = 5;
   NUMPOINTS:   Integer = 2048;
   BUFSIZE:     Integer = 8;

var
   BlockNum:                                    Integer;
   ULStat, BoardNum, LowChan, HighChan, Gain:   Integer;
   Options, FirstPoint, DataPoint:              Integer;
   Count, Rate:                                 LongInt;
   DataBuffer:                                  Array [0..100] of Word;
   ErrReporting:                                Integer;
   ErrHandling:                                 Integer;
   Dummy:                                       Integer;
   RevLevel:        Single;

procedure TfrmAInScan.FormCreate(Sender: TObject);
begin
  {declare Revision Level}
   RevLevel := CURRENTREVNUM;
   ULStat := cbDeclareRevision(RevLevel);

   {
   set up internal error handling for the Universal Library
   }
   ErrReporting := PRINTALL;       {set Universal Library to print all errors}
   ErrHandling := STOPALL;         {set Universal Library to stop on errors}
   ULStat := cbErrHandling(ErrReporting, ErrHandling);
   {
   Demonstration of cbAInScan() with EXTMEMORY option
   This program collects 1000 points from an A/D and transfers them
   directly via DT-Connect to an attached memory board
   It then reads the data in block from the memory board and prints the
   values on the screen.
   }
   Memo1.Text := 'Click start to acquire data';
end;

procedure TfrmAInScan.cmdStartClick(Sender: TObject);
var
   index:            Integer;

begin
   {
   Reset memory board to the start of memory
   }
   BoardNum := MEMBOARD;
   ULStat := cbMemReset(BoardNum);
   {
   Collect data to memory with cbAInScan() and the EXTMEMORY option
   Parameters:
      BoardNum    :the number used by CB.CFG to describe this board
      LowChan     :the first channel of the scan
      HighChan    :the last channel of the scan
      Count       :the total number of A/D samples to collect
      Rate        :sample rate in samples per second
      Gain        :the gain for the board
      Dummy       :placeholder for data array (array not required
                   since data will be stored in external memory)
      Options     :data collection options
   }
   BoardNum := ADBOARD;
   LowChan := 0;
   HighChan := 1;
   Count := NUMPOINTS;
   Rate := 5000;
   Gain := BIP5VOLTS;
   Options := EXTMEMORY;
   ULStat := cbAInScan (BoardNum, LowChan, HighChan, Count, Rate, Gain, Dummy, Options);
   {
   Read the data back from the memory board in blocks.  Print each block
   of data on the screen.
   }
   FirstPoint := 0;                    { Set address of first point to read }
   {
   Read a block of data from  the memory board
      BoardNum - Board number of the memory board
      DataBuffer - Array of data to read data into
      FirstPoint - Address to read (first point)
      Count - Number of points to read
   }
   BoardNum := MEMBOARD;
   Count := BUFSIZE;
   BlockNum := 0;
   ULStat := cbMemRead (BoardNum,  DataBuffer[0], FirstPoint, Count);
   Memo1.Text := 'The first block of ten read from the memory board:';
   Memo1.Lines.Add (' ');
   for index:=0 TO BUFSIZE - 1 do           { Print one screen of data }
   begin
      {
      Raw data from memory board contains a 4 bit channel number (LSB's)
      and a 12 bit A/D value (MSB's).  Convert to just a 12 bit A/D value.
      }
      DataPoint := DataBuffer[index] shr 4;
      Memo1.Lines.Add (Format('Data point %d:   %d', [BlockNum * 10 + index, DataPoint]));
   end;
   BlockNum := BlockNum + 1;
   cmdReadBlock.Enabled := True;
end;

procedure TfrmAInScan.cmdReadBlockClick(Sender: TObject);
var
   index:      Integer;

begin
   Memo1.Text := Format('Block %d from memory board:', [BlockNum]);
   Memo1.Lines.Add (' ');
   FirstPoint := FROMHERE;
   ULStat := cbMemRead (BoardNum,  DataBuffer[0], FirstPoint, Count);
   for index:=0 TO BUFSIZE - 1 do           { Print one screen of data }
   begin
      {
      Raw data from memory board contains a 4 bit channel number (LSB's)
      and a 12 bit A/D value (MSB's).  Convert to just a 12 bit A/D value.
      }
      DataPoint := DataBuffer[index] shr 4;
      Memo1.Lines.Add (Format('Data point %d:   %d', [BlockNum * BUFSIZE + index, DataPoint]));
   end;
   BlockNum := BlockNum + 1;
   If BlockNum = NUMPOINTS/BUFSIZE then cmdReadBlock.Enabled := False;
end;

procedure TfrmAInScan.cmdQuitClick(Sender: TObject);
begin
   Close;
end;

end.

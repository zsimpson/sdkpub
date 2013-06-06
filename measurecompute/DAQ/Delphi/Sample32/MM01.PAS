unit Mm01;
{
ULMM01.DPR================================================================

File:                         MM01.PAS

Library Call Demonstrated:    cbAPretrig() with EXTMEMORY option and
                              cbReadPretrigData()

Purpose:                      Collect pre-trig data from A/D to memory board

Demonstrates:                 How to use the collect pre-trigger data
                              to memory board and then retreive the data.

Other Library Calls:          cbErrHandling()

Special Requirements:         Board0 must be an A/D board.
                              Board 5 must be a memory board.
                              A/D and memory boards must be connected together
                              via a DT-Connect cable.

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
    cmdStart: TButton;
    cmdQuit: TButton;
    Memo1: TMemo;
    Memo2: TMemo;
    procedure cmdQuitClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure cmdStartClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  frmXMem: TfrmXMem;

implementation

{$R *.DFM}

const
   ADBOARD:         Integer = 0;   { Board number of A/D }
   MEMBOARD:        Integer = 5;   { Board number of memory board }
   BUFSIZE:         Integer = 100; { Size of buffer for cbMemRead() } 
   

var
   BoardNum:        Integer;
   LowChan:         Integer;
   HighChan:        Integer;
   Range:           Integer;
   Options:         Integer;
   ULStat:          Integer;
   DataPoint:       Word;
   PretrigCount:    LongInt;
   Count:           LongInt;
   TotalCount:      LongInt;
   Rate:            LongInt;
   FirstPoint:      LongInt;
   Dummy:           Word;
   DataBuffer:      Array [0..100] of word;
   ErrReporting:    Integer;
   ErrHandling:     Integer;
   RevLevel:        Single;

procedure TfrmXMem.FormCreate(Sender: TObject);
begin
  {declare Revision Level}
   RevLevel := CURRENTREVNUM;
   ULStat := cbDeclareRevision(RevLevel);

{set up internal error handling for the Universal Library
   Disable error handling
     Normally it is more convenient to use the automatic error handling to
     detect errors.  In this program though we are likely to encounter a
     TRIGSTATE error when cbAPretrig() is called so the error handling is
     turned off and the the error is handled by checking the error code
     returned by cbAPretrig().
     Parameters:
        DONTPRINT  :Universal Library will ignore non-fatal errors
        DONTSTOP   :error handling is left to local code}

   ErrReporting := DONTPRINT;
   ErrHandling := DONTSTOP;

   ULStat := cbErrHandling(ErrReporting, ErrHandling);
   Memo1.Text := 'Make sure trig in is at TTL low,  then click  "Start"  to acquire data.';
end;

procedure TfrmXMem.cmdStartClick(Sender: TObject);
var
   index:         Integer;
begin
   Memo1.Text := 'Waiting for trigger....';
   Memo2.Text := ' ';
   Application.ProcessMessages;
   {Collect data to memory with cbAPretrig() and the EXTMEMORY option
   Parameters:
      BoardNum     :the number used by CB.CFG to describe this board
      LowChan      :the first channel of the scan
      HighChan     :the last channel of the scan
      PretrigCount :Number of pre-trigger points to collect
      TotalCount   :the total number of A/D samples to collect
      Rate         :sample rate in samples per second
      Range        :the gain for the board
      Dummy:       :placeholder...array not required because of EXTMEMORY option
      Options      :data collection options  }

   BoardNum := MEMBOARD;
   cbMemReset (BoardNum);  {reset memory board counter to beginning}

   BoardNum := ADBOARD;
   LowChan := 0;
   HighChan := 0;
   PretrigCount := 10;
   TotalCount := 10000;
   Rate := 10000;
   Range := BIP5VOLTS;
   Options := EXTMEMORY;
   repeat
      ULStat := cbAPretrig (BoardNum, LowChan, HighChan, PretrigCount, TotalCount, Rate,
                                                      Range, Dummy, Options);
   until (ULStat <> TRIGSTATE);

   if ULStat <> NOERRORS then Memo1.Text := Format('Error %d occurred....', [ULStat]);
   {Turn automatic error handling back on again
      Parameters:
         PRINTALL    :all warnings and errors encountered will be printed
         DONTSTOP    :if any error is encountered, the program will continue }
   ULStat := cbErrHandling (PRINTALL, DONTSTOP);

   {Read the first block of data from the memory board.
   Read a block of data from  the memory board
      BoardNum - Board number of the memory board
      DataBuffer - Array of data to read data into
      FirstPoint - Address to read first point (or FROMHERE)
      NUMPOINTS - Number of points to read  }
   FirstPoint := 0;                     { Set address of first point to read }
   BoardNum := MEMBOARD;
   Count := BUFSIZE;
   ULStat := cbMemReadPretrig (BoardNum, DataBuffer[0], FirstPoint, Count);
   If ULStat <> 0 then exit;
   Memo1.Text := 'Pre-trigger data:';
   Memo1.Lines.Add (' ');
   If ULStat <> 0 then exit;

   For index := 0 to 9 do
   begin
      {Raw data from memory board contains a 4 bit channel number (LSB's)
      and a 12 bit A/D value (MSB's).  Convert to just a 12 bit A/D value. }
      DataPoint := DataBuffer[index] shr 4;
      Memo1.Lines.Add (Format('Trigger - %d:  %d', [10 - index, DataPoint]));
   end;
   Memo2.Text := 'Post-trigger data:';
   Memo2.Lines.Add (' ');
   For index := 10 to 19 do
   begin
      DataPoint := DataBuffer[index] shr 4;
      Memo2.Lines.Add (Format('Trigger + %d:  %d', [index - 10, DataPoint]));
   end;
end;

procedure TfrmXMem.cmdQuitClick(Sender: TObject);
begin
   Close;
end;

end.

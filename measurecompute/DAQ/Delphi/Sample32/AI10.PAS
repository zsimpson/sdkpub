unit Ai10;
{
ULAI10.DPR================================================================

File:                         AI10.PAS

Library Call Demonstrated:    cbALoadQueue()

Purpose:                      Loads an A/D board's channel/gain queue.

Demonstration:                Prepares a channel/gain queue and loads it
                              to the board. An analog input function
                              is then called to show how the queue
                              values work.

Other Library Calls:          cbErrHandling()

Special Requirements:         Board 0 must have an A/D converter and
                              channel gain queue hardware (for example,
                              CIO-DAS16/330i or CIO-DAS16/M1).

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
    tmrAIn: TTimer;
    cmdStart: TButton;
    cmdQuit: TButton;
    Memo1: TMemo;
    cmdLoadQ: TButton;
    cmdUnLoadQ: TButton;
    Memo2: TMemo;
    Memo3: TMemo;
    Memo4: TMemo;
    procedure tmrAInTimer(Sender: TObject);
    procedure cmdStartClick(Sender: TObject);
    procedure cmdQuitClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure cmdLoadQClick(Sender: TObject);
    procedure cmdUnLoadQClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
   frmAInScan: TfrmAInScan;

implementation

{$R *.DFM}

var
   ULStat:                 Integer;
   MemHandle:              Integer;
   ADData:                 array [0..39] of Word;  {NumPoints * NumChans}
   ChanTags:               array [0..39] of Word;
   NumChans:               LongInt;
   Samples:                LongInt;
   Rate:                   LongInt;
   ErrHandling:            Integer;
   ErrReporting:           Integer;
   RevLevel:                Single;
   ChanArray:              array [0..3] of SmallInt;
   GainArray:              array [0..3] of SmallInt;

const
   BoardNum:               Integer = 0;
   LowChan:                SmallInt = 0;
   HighChan:               SmallInt = 3;
   Count:                  Longint = 40;
   FirstPoint:             LongInt = 0;
   Range:                  Integer = BIP10VOLTS;
   NumPoints:              LongInt = 10;
   TargetRate:             LongInt = 1000;
   Options:                Integer = NOCONVERTDATA;
   {
   initially only one channel is sampled
   }

procedure TfrmAInScan.FormCreate(Sender: TObject);
begin
  {declare Revision Level}
   RevLevel := CURRENTREVNUM;
   ULStat := cbDeclareRevision(RevLevel);

   {set up internal error handling for the Universal Library}

   ErrReporting := PRINTALL;       {set Universal Library to print all errors}
   ErrHandling := STOPALL;         {set Universal Library to stop on errors}
   ULStat := cbErrHandling(ErrReporting, ErrHandling);

   {set up a buffer in Windows to contain the data}
   MemHandle := cbWinBufAlloc (Count);
   Samples := NumPoints * 1;
   Memo1.Text := 'Click start to acquire data';
end;

procedure TfrmAInScan.cmdStartClick(Sender: TObject);
begin
   tmrAIn.Enabled := True;
end;

procedure TfrmAInScan.tmrAInTimer(Sender: TObject);
var
   index:         Integer;

begin
   {
   call an analog input function to show how the gain queue values
   supercede those passed to the function

   Parameters:  (see Initialization section)
      BoardNum    :the number used by CB.CFG to describe this board
      LowChan     :low channel of the scan
      HighChan    :high channel of the scan
      Count       :the total number of A/D samples to collect
      Rate        :sample rate in samples per second
      Gain        :the gain for the board
      MemHandle   :Windows memory set up with cbWinBufAlloc()
      Options     :data collection options
   }
   Rate := TargetRate;
   ULStat := cbAInScan(BoardNum, LowChan, HighChan,
                    Samples, Rate, Range, MemHandle, Options);
   If ULStat <> 0 then exit;
   {
   Transfer the data from the Windows buffer to an array.  This data
   could also be accessed directly using a pointer.
   }
   ULStat := cbWinBufToArray (MemHandle, ADData[0], FirstPoint, Samples);
   If ULStat <> 0 then exit;
   ULStat := cbAConvertData(BoardNum, Count, ADData[0], ChanTags[0]);
   If ULStat <> 0 then exit;
   Memo1.Text := Format('Channel 0 data, gain code = %d', [GainArray[0]]);
   Memo1.Lines.Add (' ');
   Memo2.Text := Format('Channel 1 data, gain code = %d', [GainArray[1]]);
   Memo2.Lines.Add (' ');
   Memo3.Text := Format('Channel 2 data, gain code = %d', [GainArray[2]]);
   Memo3.Lines.Add (' ');
   Memo4.Text := Format('Channel 3 data, gain code = %d', [GainArray[3]]);
   Memo4.Lines.Add (' ');
   For index := 0 to Samples-1 do
   begin
      case ChanTags[index] of
         0: Memo1.Lines.Add (Format('Channel %d:  %d, sample # %d',
                                   [ChanTags[index], ADData[index], index]));
         1: Memo2.Lines.Add (Format('Channel %d:  %d, sample # %d',
                                   [ChanTags[index], ADData[index], index]));
         2: Memo3.Lines.Add (Format('Channel %d:  %d, sample # %d',
                                   [ChanTags[index], ADData[index], index]));
         3: Memo4.Lines.Add (Format('Channel %d:  %d, sample # %d',
                                   [ChanTags[index], ADData[index], index]));
      end;
   end;
end;

procedure TfrmAInScan.cmdLoadQClick(Sender: TObject);
begin
   { set up a channel/gain queue }
   ChanArray[0] := 0;
   GainArray[0] := BIP10VOLTS;

   ChanArray[1] := 1;
   GainArray[1] := BIP5VOLTS;

   ChanArray[2] := 2;
   GainArray[2] := BIP2PT5VOLTS;

   ChanArray[3] := 3;
   GainArray[3] := BIP1PT25VOLTS;
   {
   load the channel/gain values into the queue
      Parameters:
         BoardNum    :the number used by CB.CFG to describe this board
         ChanArray[] :array of channel values
         GainArray[] :array of gain values
         NumChans    :the number of elements in the arrays (0=disable queue)
   }
   NumChans := 4;
   ULStat := cbALoadQueue (BoardNum, ChanArray[0], GainArray[0], NumChans);
   If ULStat <> 0 then exit;
   Samples := NumPoints * 4;
end;

procedure TfrmAInScan.cmdUnLoadQClick(Sender: TObject);
begin
   {
   disable the channel/gain queue
      Parameters:
         BoardNum    :the number used by CB.CFG to describe this board
         ChanArray[] :array of channel values
         GainArray[] :array of gain values
         NumChans    :0 = disable queue
   }
   NumChans := 0;
   ULStat := cbALoadQueue (BoardNum, ChanArray[0], GainArray[0], NumChans);
   If ULStat <> 0 then exit;
   Samples := NumPoints * 1;
end;

procedure TfrmAInScan.cmdQuitClick(Sender: TObject);
begin
   tmrAIn.Enabled := False;
   ULStat := cbWinBufFree (MemHandle);
   Close;
end;

end.

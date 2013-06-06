unit Ai08;
{
ULAI08.DPR================================================================

File:                         AI08.PAS

Library Call Demonstrated:    cbAPretrig()

Purpose:                      Waits for a trigger, then returns a specified
                              number of analog samples before and after
                              the trigger.

Demonstration:                Displays the analog input on one channel and
                              waits for the trigger.

Other Library Calls:          cbErrHandling()

Special Requirements:         Board 0 must support cbAPretrig.
                              Analog signal on an input channel.


(c) Copyright 1995 - 2002, Measurement Computing Corp.
All rights reserved.
***************************************************************************/
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
  frmAInScan: TfrmAInScan;

implementation

{$R *.DFM}

var
   ULStat:                Integer;
   MemHandle:             Integer;
   ADData:                array[0..2000] of Word;
   {
   array must be dimensioned at least TotalCount + 512
   }
   ErrReporting:          Integer;
   ErrHandling:           Integer;
   RevLevel:              Single;
   Rate:                  LongInt;
   PretrigCount:          LongInt;
   TotalCount:            LongInt;


const
   BoardNum:              Integer = 0;
   Count:                 LongInt = 600;
   FirstPoint:            LongInt = 0;
   TargetRate:           LongInt = 2000;
   LowChan:               Integer = 0;
   HighChan:              Integer = 0;
   Range:                 Integer = BIP5VOLTS;
   Options:               Integer = CONVERTDATA;
   TargetPretrigCount:    LongInt = 10;
   DefaultCount:          LongInt = 700;
   BufferSize:            LongInt = 2000;

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
   set up a buffer in Windows to contain the data
   }
   MemHandle := cbWinBufAlloc (BufferSize);
   Memo1.Text := 'Make sure trig in is at TTL low,  then click  "Start"  to acquire data.';
end;

procedure TfrmAInScan.cmdStartClick(Sender: TObject);
var
   index:         Integer;

begin
   Memo1.Text := 'Waiting for trigger....';
   Memo2.Text := ' ';
   Application.ProcessMessages;
   {
   Collect the values after the trigger
     Parameters:
        BoardNum    :the number used by CB.CFG to describe this board
        LowChan     :low channel of the scan
        HighChan    :high channel of the scan
        PretrigCount:number of pre-trigger A/D samples to collect
        TotalCount  :the total number of A/D samples to collect
        Rate        :sample rate in samples per second per channel
        Gain        :the gain for the board
        MemHandle   :the memory buffer for the collected data values
        Options     :data collection options
   }
   PreTrigCount := TargetPretrigCount;
   TotalCount := DefaultCount;
   Rate := TargetRate;
   ULStat := cbAPretrig (BoardNum, LowChan, HighChan,
                     PreTrigCount, TotalCount, Rate, Range, MemHandle, Options);
   If ULStat <> 0 then exit;
   Memo1.Text := 'Pre-trigger data:';
   Memo1.Lines.Add (' ');
   {
   Transfer the data from the Windows buffer to an array.  This data
   could also be accessed directly using a pointer.
   }
   ULStat := cbWinBufToArray (MemHandle, ADData[0], FirstPoint, Count);
   If ULStat <> 0 then exit;
   For index := 0 to 9 do
   begin
      Memo1.Lines.Add (Format('Trigger - %d:  %d', [10 - index, ADData[index]]));
   end;

   Memo2.Text := 'Post-trigger data:';
   Memo2.Lines.Add (' ');
   For index := 10 to 19 do
   begin
      Memo2.Lines.Add (Format('Trigger + %d:  %d', [10 - index, ADData[index]]));
   end;
end;

procedure TfrmAInScan.cmdQuitClick(Sender: TObject);
begin
   ULStat := cbWinBufFree (MemHandle);
   Close;
end;

end.

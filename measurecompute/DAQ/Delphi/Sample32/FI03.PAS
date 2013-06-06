unit Fi03;
{
ULFI03.DPR================================================================

 File:                         FI03.PAS

 Library Call Demonstrated:    File Operations:
                               cbFilePretrig%()
                               cbFileRead()
                               cbFileGetInfo()

 Purpose:                      Stream data continuously to a streamer file
                               until a trigger is received, continue data
                               streaming until total number of samples minus
                               the number of pretrigger samples is reached.

 Demonstration:                Creates a file and scans analog data to the
                               file continuously, overwriting previous data.
                               When a trigger is received, acquisition stops
                               after (TotalCount& - PreTrigCount&) samples
                               are stored. Displays the data in the file and
                               the information in the file header. Prints
                               data from PreTrigger-4 to PreTrigger+10.

 Other Library Calls:          cbErrHandling%()

 Special Requirements:         Board 0 must have an A/D converter.

(c) Copyright 1995 - 2002, Measurement Computing Corp.
All rights reserved.
***************************************************************************/
}
interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, StdCtrls, ExtCtrls, cbw;

type
  TfrmFileAInScan = class(TForm)
    cmdStart: TButton;
    cmdQuit: TButton;
    Memo1: TMemo;
    Memo2: TMemo;
    edFileName: TEdit;
    procedure cmdQuitClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure cmdStartClick(Sender: TObject);
    procedure edFileNameChange(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  frmFileAInScan: TfrmFileAInScan;

implementation

{$R *.DFM}

var
   ULStat:                Integer;
   LowChan:               Integer;
   HighChan:              Integer;
   Options:               Integer;
   FirstPoint:            Longint;
   PreTrigCount:          Longint;
   TotalCount:            LongInt;
   NumPoints:             LongInt;
   Rate:                  LongInt;
   Range:                 Integer;
   DataBuffer:            array [0..20] of Word;
   FileName:              PChar;
   ErrReporting:          Integer;
   ErrHandling:           Integer;
   RevLevel:              Single;

const
   BoardNum:              Integer = 0;
   TestPoints:            Longint = 1280;
   DefaultRange:          Integer = BIP5VOLTS;
   TargetPreTrigCount:    Longint = 256;
   TargetRate:            LongInt = 50000;


procedure TfrmFileAInScan.FormCreate(Sender: TObject);
begin
  {declare Revision Level}
   RevLevel:= CURRENTREVNUM;
   ULStat := cbDeclareRevision(RevLevel);

   {
   set up internal error handling for the Universal Library
   }
   ErrReporting := PRINTALL;       {set Universal Library to print all errors}
   ErrHandling := STOPALL;         {set Universal Library to stop on errors}
   ULStat := cbErrHandling(ErrReporting, ErrHandling);
   {
   set up the collection parameters
   }
   TotalCount  := TestPoints;
   FileName := 'C:\DEMO.DAT';
   LowChan := 0;
   HighChan := 1;
   PreTrigCount := TargetPreTrigCount;
   Rate := TargetRate;
   Options := TIMED + NODTCONNECT;
   Range := DefaultRange;
   Memo1.Text := 'Make sure trig in is at TTL low,  then click  "Start"  to acquire data.';
   Memo1.Lines.Add (' ');
   Memo1.Lines.Add (Format(
   '%d samples from channel %d to %d at %dHz/chan to file named %s with %d pretrigger samples.',
                    [TotalCount , LowChan, HighChan, Rate, FileName, PreTrigCount]));
end;

procedure TfrmFileAInScan.cmdStartClick(Sender: TObject);
var
    LowChannel, HighChannel :    SmallInt;
    Gain                    :    LongInt;
    x                       :    Integer;

begin
   {
   Collect the values with cbFileAInScan()
     Parameters:
        BoardNum   :the number used by CB.CFG to describe this board
        LowChan    :first A/D channel of the scan
        HighChan   :last A/D channel of the scan
        PreTrigCount:number of samples befor trigger to take
        TotalCount :the total number of A/D samples to collect
        Rate       :sample rate in samples per second
        Range       :the gain for the board
        FileName   :the filename for the collected data values
        Options    :data collection options
   }
   PreTrigCount := TargetPreTrigCount;
   Rate := TargetRate;
   Range := DefaultRange;
   UlStat := cbFilePretrig (BoardNum, LowChan, HighChan, PreTrigCount, TotalCount, Rate, Range, FileName, Options);
   If ULStat <> 0 then exit;

   {
   read back information from the file
   }
   ULStat := cbFileGetInfo (FileName, LowChannel, HighChannel, PreTrigCount, TotalCount, Rate, Gain);
   If ULStat <> 0 then exit;
   Memo2.Text := Format('cbFileGetInfo read the following information from the %s file header:', [FileName]);
   Memo2.Lines.Add (' ');
   Memo2.Lines.Add (Format('%d total samples and %d pretrigger samples were collected at %dHz.',
                               [TotalCount, PreTrigCount, Rate]));
   Memo2.Lines.Add (' ');
   Memo2.Lines.Add (Format('Channels scanned were %d to %d with gain code set to %d.',
                    [LowChannel, HighChannel, Range]));
   {
   show the data using cbFileRead()
     Parameters:
        FileName      :the filename containing the data
        TestPoints     :the number of data values to read from the file
        FirstPoint    :index of the first data value to read
        DataBuffer[]  :array to read data into
   }
   NumPoints := 20;    { read the first twenty points of the file }
   FirstPoint := PreTrigCount - 10;     { start at trigger - 10 }
   ULStat := cbFileRead (FileName, FirstPoint, NumPoints,  DataBuffer[0]);
   {
   display the data values read from the file
   }
   Memo1.Lines.Add (' ');
   Memo1.Lines.Add ('Pre-trigger data:');
   Memo1.Lines.Add (' ');
   For x := 0 to 9 do
   begin
      Memo1.Lines.Add (Format('Trigger - %d:  %d', [10 - x, DataBuffer[x]]));
   end;

   Memo2.Lines.Add (' ');
   Memo2.Lines.Add ('Post-trigger data:');
   Memo2.Lines.Add (' ');
   For x := 10 to 19 do
   begin
      Memo2.Lines.Add (Format('Trigger + %d:  %d', [x - 10, DataBuffer[x]]));
   end;

end;

procedure TfrmFileAInScan.edFileNameChange(Sender: TObject);
begin
   StrPCopy(FileName, edFileName.Text);
end;

procedure TfrmFileAInScan.cmdQuitClick(Sender: TObject);
begin
   Close;
end;

end.

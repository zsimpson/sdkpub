unit Fi02;
{
ULFI02.DPR================================================================

 File:                         FI02.PAS

 Library Call Demonstrated:    File Operations:
                               cbFileRead()
                               cbFileGetInfo()

 Purpose:                      Read information & data from a streamer file.

 Demonstration:                Creates a file and scans analog data to the
                               file. Displays the data in the file and the
                               information in the file header.

 Other Library Calls:          cbFileAInScan()
                               cbErrHandling()

 Special Requirements:         Board 0 must have A/D converter.

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
   Options:               Integer;
   FirstPoint:            LongInt;
   PreTrigCount:          LongInt;
   Count:                 LongInt;
   TotalCount:            LongInt;
   LowChan:               Integer;
   HighChan:              Integer;
   Rate:                  LongInt;
   Range:                 Integer;
   DataBuffer:            array [0..5000] of Word;
   FileName:              PChar;
   ErrReporting:          Integer;
   ErrHandling:           Integer;
   RevLevel:              Single;

const
   BoardNum:              Integer = 0;
   TestPoints:            Longint = 5000;
   DefaultRange:          Integer = BIP5VOLTS;
   TargetRate:            LongInt = 5000;

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
   Count := TestPoints;
   FileName := 'C:\DEMO.DAT';
   LowChan := 0;
   HighChan := 1;
   Rate := TargetRate;
   Options := TIMED + NODTCONNECT;
   Range := DefaultRange;

   Memo1.Text :=
     'Click  "Start"  to acquire data to a file with the following parameters:';
   Memo1.Lines.Add (' ');
   Memo1.Lines.Add (Format('%d samples from channel %d to %d at %dHz/chan to file named %s.',
                    [Count, LowChan, HighChan, Rate, FileName]));
end;

procedure TfrmFileAInScan.cmdStartClick(Sender: TObject);
var
    LowChannel, HighChannel :    SmallInt;
    Gain                    :    LongInt;
    DisplayCount            :    Integer;
    index                   :    Integer;

begin
   {
   Collect the values with cbFileAInScan()
     Parameters:
        BoardNum   :the number used by CB.CFG to describe this board
        LowChan    :first A/D channel of the scan
        HighChan   :last A/D channel of the scan
        Count      :the total number of A/D samples to collect
        Rate       :sample rate in samples per second
        Range      :the gain for the board
        FileName   :the filename for the collected data values
        Options    :data collection options
   }
   Count := TestPoints;
   Rate := TargetRate;
   Range := DefaultRange;
   ULStat := cbFileAInScan (BoardNum, LowChan, HighChan, Count, Rate, Range, FileName, Options);
   If ULStat <> 0 then exit;
   {
   read back information from the file
   }

   ULStat := cbFileGetInfo (FileName, LowChannel, HighChannel, PreTrigCount, TotalCount, Rate, Gain);
   If ULStat <> 0 then exit;
   Memo2.Text := Format('cbFileGetInfo read the following information from the %s file header:', [FileName]);
   Memo2.Lines.Add (' ');
   Memo2.Lines.Add (Format('%d samples were collected at %dHz.', [TotalCount, Rate]));
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
   DisplayCount := 5;    { read the first five points of the file }
   FirstPoint := 0;   { start at the first point }
   ULStat := cbFileRead (FileName, FirstPoint, DisplayCount,  DataBuffer[0]);
   {
   display the data values read from the file
   }
   Memo2.Lines.Add ('The first five data values read using cbFileRead:');
   for index := FirstPoint to DisplayCount  - 1 do
   begin
      Memo2.Lines.Add (Format('Sample %d:  %d', [index, DataBuffer[index]]));
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

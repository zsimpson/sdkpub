unit Fi01;
{
ULFI01.DPR================================================================

 File:                         FI01.PAS

 Library Call Demonstrated:    cbFileAInScan()
                               cbFileGetInfo()

 Purpose:                      Scan a range of A/D channels and store the
                               data in a disk file.

 Demonstration:                Collects data points from one analog input
                               channel. A file is created and data are
                               collected into the file. File stats are then
                               read back and displayed.

 Other Library Calls:          cbErrHandling()

 Special Requirements:         Board 0 must have A/D converters.

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
   PreTrigCount:          LongInt;
   Count:                 Longint;
   TotalCount:            LongInt;
   Rate:                  LongInt;
   Range:                 Integer;
   Options:               Integer;
   FileName:              PChar;
   ErrReporting:          Integer;
   ErrHandling:           Integer;
   RevLevel:              Single;

const
   BoardNum:              Integer = 0;
   DefaultRange:          Integer = BIP5VOLTS;
   NumPoints:             LongInt = 128000;
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
   Count := NumPoints;
   FileName := 'C:\DEMO.DAT';
   Rate := TargetRate;              { sampling rate (samples per second) }
   LowChan := 0;
   HighChan := 1;
   Options := TIMED + NODTCONNECT;
   Range := DefaultRange;

   Memo1.Text :=
     'Click  "Start"  to acquire data to a file with the following parameters:';
   Memo1.Lines.Add (' ');
   Memo1.Lines.Add (Format('%d samples at %dHz to file named %s.', [Count, Rate, FileName]));
end;

procedure TfrmFileAInScan.cmdStartClick(Sender: TObject);
var
    LowChannel,HighChannel  :  SmallInt;
    Gain                    :  LongInt;

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

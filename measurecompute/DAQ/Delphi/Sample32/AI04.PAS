unit Ai04;
{
 ULAI04.DPR================================================================

 File:                         AI04.PAS

 Library Call Demonstrated:    cbAInScan() with cbAConvertData()

 Purpose:                      Demonstrate the conversion of data values
                               after they have been collected.

 Demonstration:                Collects 10 data points from one analog input.
                               Data are collected as 16-bit values and
                               are converted to channel numbers and
                               12-bit data values using cbAConvertData.

 Other Library Calls:          cbAConvertData()
                               cbGetStatus()
                               cbStopBackground()
                               cbErrHandling()

 Special Requirements:         Board 0 must have a 12 bit A/D converter
                               that carries channel tags with data.  This
                               includes most 12 bit boards but excludes the
                               PCM-DAS08 and PCM-DAS16/12.
                               Analog signal on an input channel.

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
    tmrCheckStatus: TTimer;
    cmdStart: TButton;
    cmdQuit: TButton;
    Memo1: TMemo;
    cmdConvert: TButton;
    procedure cmdStartClick(Sender: TObject);
    procedure cmdQuitClick(Sender: TObject);
    procedure cmdConvertClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure tmrCheckStatusTimer(Sender: TObject);
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
   ErrReporting:           Integer;
   ErrHandling:            Integer;
   ChanTags, ADData :      array[0..10] of Word;
   CurCount, CurIndex:     LongInt;
   FirstPoint:             LongInt;
   Rate:                   LongInt;
   RevLevel:               Single;
   Status:                 SmallInt;

const
   BoardNum:               Integer = 0;
   Count:                  LongInt = 10;
   TargetRate:             LongInt = 1000;
   LowChan:                Integer = 0;
   HighChan:               Integer = 0;
   Range:                  LongInt = BIP5VOLTS;
   Options:                Integer = NOCONVERTDATA + BACKGROUND;

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
   MemHandle := cbWinBufAlloc (Count);
   Memo1.Text := 'Click "Start" to acquire data';
end;

procedure TfrmAInScan.cmdStartClick(Sender: TObject);
begin
   {
    Collect the values with cbAInScan()
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
   Memo1.Text := ' ';
   Rate := TargetRate;
   ULStat := cbAInScan(BoardNum, LowChan, HighChan,
                    Count, Rate, Range, MemHandle, Options);
   If ULStat <> 0 then exit;
   tmrCheckStatus.Enabled := True;
end;

procedure TfrmAInScan.cmdConvertClick(Sender: TObject);
var 
   index:      Integer;

begin
   {
   Use cbAConvertData() to convert the 16-bit values in
   ADData() to 12-bit values
   Parameters:
      NumPoints   :the number of data values to convert
      ADData :the array holding the 16-bit data values to be converted
   }
   cmdConvert.Enabled := False;
   ULStat := cbAConvertData(BoardNum, Count, ADData[0], ChanTags[0]);
   Memo1.Text := 'Converted data values:';
   Memo1.Lines.Add (' ');
   For index := 0 to 9 do
   begin
      Memo1.Lines.Add (Format('Channel %d, sample number %d:  %d',
                                   [ChanTags[index], index, ADData[index]]));
   end;
end;

procedure TfrmAInScan.tmrCheckStatusTimer(Sender: TObject);
var
   index:         Integer;

begin
   {
    This timer will check the status of the background data collection

    Parameters:
      BoardNum    :the number used by CB.CFG to describe this board
      Status%     :current status of the background data collection
      CurCount&   :current number of samples collected
      CurIndex&   :index to the data buffer pointing to the start of the
                   most recently collected scan
      FunctionType: A/D operation (AIFUNCTION)

   }
   ULStat := cbGetStatus(BoardNum, Status, CurCount, CurIndex,AIFUNCTION);
   If ULStat <> 0 Then Exit;
   {
    Check if the background operation has finished. If it has, then
    transfer the data from the memory buffer set up by Windows to an
    array for use by Delphi
    The BACKGROUND operation must be explicitly stopped
   }
   If (Status = IDLE) Then
   begin
      ULStat := cbStopBackground(BoardNum, AIFUNCTION);
      If ULStat <> 0 Then Exit;
      tmrCheckStatus.Enabled := False;
      If MemHandle = 0 Then Exit;

      {
      Transfer the data from the Windows buffer to an array.  This data
      could also be accessed directly using a pointer.
      }
      FirstPoint := 0;
      ULStat := cbWinBufToArray (MemHandle, ADData[0], FirstPoint, Count);
      If ULStat <> 0 then exit;
      Memo1.Text := 'Raw data values:';
      Memo1.Lines.Add (' ');
      For index := 0 to 9 do
      begin
         Memo1.Lines.Add (Format('Channel 0, sample number %d:  %d', [index, ADData[index]]));
      end;
      cmdConvert.Enabled := True;
   end;
end;

procedure TfrmAInScan.cmdQuitClick(Sender: TObject);
begin
   tmrCheckStatus.Enabled := False;
   ULStat := cbStopBackground(BoardNum, AIFUNCTION);
   If ULStat <> 0 Then Exit;
   ULStat := cbWinBufFree (MemHandle);
   Close;
end;

end.

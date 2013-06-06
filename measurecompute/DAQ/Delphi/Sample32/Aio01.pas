unit Aio01;
{
ULAIO01.DPR================================================================

 File:                         AIO01.PAS

 Library Call Demonstrated:    cbGetStatus()
                               cbStopBackground()

 Purpose:                      Run Simultaneous input/output functions using
                               the same board.

 Demonstration:                cbAoutScan function generates a ramp signal
                               while cbAinScan Displays the analog input on
                               one channel.

 Other Library Calls:          cbAinScan()
                               cbAoutScan()
                               cbErrHandling()

 Special Requirements:         Board 0 must support simultaneous paced input
                               and paced output. See hardware documentation.

 (c) Copyright 1995 - 2002, Measurement Computing Corp.
 All rights reserved.
==========================================================================
}
interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, StdCtrls, ExtCtrls, cbw;

type
  TfrmAInAoutScan = class(TForm)
    tmrCheckStatus: TTimer;
    cmdADStart: TButton;
    cmdQuit: TButton;
    Memo1: TMemo;
    lblShowADCount: TLabel;
    lblShowADIndex: TLabel;
    lblShowADStat: TLabel;
    cmdADStop: TButton;
    Panel1: TPanel;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    cmdDAStart: TButton;
    cmdDAStop: TButton;
    lblShowDAStat: TLabel;
    lblShowDAIndex: TLabel;
    lblShowDACount: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Panel2: TPanel;
    procedure cmdADStartClick(Sender: TObject);
    procedure cmdDAStartClick(Sender: TObject);
    procedure cmdQuitClick(Sender: TObject);
    procedure cmdADStopClick(Sender: TObject);
    procedure cmdDAStopClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure tmrCheckStatusTimer(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
   frmAInAoutScan: TfrmAInAoutScan;

implementation

{$R *.DFM}

var
   ULStat:                   Integer;
   ErrReporting:             Integer;
   ErrHandling:              Integer;
   ADData:                   array[0..10000] of Word;
   PrnNum:                   Integer;
   Rate:                     LongInt;
   NumPoints:                LongInt;
   ADMemHandle:              Integer;
   ADCurCount, ADCurIndex:   LongInt;
   ADUserTerm:               Boolean;
   DAMemHandle:              Integer;
   DAData:                   array[0..10000] of Word;
   DACurCount, DACurIndex:   LongInt;
   DAUserTerm:               Boolean;
   FirstPoint:               LongInt;

   RevLevel:                 Single;
   ADStatus,DAStatus:        SmallInt;

const
   BoardNum:                 Integer = 0;
   Count:                    LongInt = 10000;
   TargetRate:               LongInt = 1000;
   LowChan:                  Integer = 0;
   HighChan:                 Integer = 0;
   Range:                    LongInt = BIP5VOLTS;
   Options:                  Integer = BACKGROUND;

procedure TfrmAInAoutScan.FormCreate(Sender: TObject);
var
  I: Integer;
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
   ADMemHandle := cbWinBufAlloc (Count);
   Memo1.Text := 'Click start to acquire data';

   { Generate D/A ramp data to be output via cbAoutScan function }

   for I:= 0 to Count-1 do
   begin
     DAData[I]:= 32768 + Trunc((I / Count) * 32768) - 16384;

   end;

   { Allocate memory to be used by cbAoutscan function }
   DAMemHandle := cbWinBufAlloc (Count);
   If DAMemHandle = 0 then exit;

   { Copy the data to Windows buffer to be used by cbAoutScan }
   ULStat := cbWinArrayToBuf (DAData[0], DaMemHandle, 0, Count);
   If ULStat <> 0 then exit;

end;

procedure TfrmAInAoutScan.cmdADStartClick(Sender: TObject);
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
            ADMemHandle :Windows memory set up with cbWinBufAlloc()
            Options     :data collection options
   }
   Memo1.Text := ' ';
   ADUserTerm := False;
   PrnNum := 1000;
   Rate := TargetRate;
   ULStat := cbAInScan(BoardNum, LowChan, HighChan,
                    Count, Rate, Range, ADMemHandle, Options);
   If ULStat <> 0 then exit;
   CmdADStop.Visible := True;
   CmdADStart.Visible := False;
   cmdQuit.Enabled := False;

end;

procedure TfrmAInAoutScan.cmdDAStartClick(Sender: TObject);
begin
   {
    Send the values with cbAoutScan()
        Parameters:  (see Initialization section)
            BoardNum    :the number used by CB.CFG to describe this board
            LowChan     :low channel of the scan
            HighChan    :high channel of the scan
            Count       :the total number of D/A samples to send to the DAC
            Rate        :sample rate in samples per second
            Gain        :the gain for the board
            DAMemHandle :Windows memory set up with cbWinBufAlloc()
            Options     :data output options
   }
   Memo1.Text := ' ';
   DAUserTerm := False;
   PrnNum := 1000;
   Rate := TargetRate;
   ULStat := cbAoutScan(BoardNum, LowChan, HighChan,
                    Count, Rate, Range, DAMemHandle, Options);
   If ULStat <> 0 then exit;
   CmdDAStop.Visible := True;
   CmdDAStart.Visible := False;
   cmdQuit.Enabled := False;

end;

procedure TfrmAInAoutScan.tmrCheckStatusTimer(Sender: TObject);
var 
	index:			Integer;
begin
   {
    This timer will check the status of the background data collection
    and the status of data output

    cbGetStatus Parameters:
      BoardNum    :the number used by CB.CFG to describe this board
      
      ADStatus    :current status of the background data collection
      ADCurCount  :current number of samples collected
      ADCurIndex  :index to the data buffer pointing to the start of the
                   most recently collected scan
     Subsystem   :the subsystem for which to get status(AIFUNCTION)
   }
   ULStat := cbGetStatus(BoardNum, ADStatus, ADCurCount, ADCurIndex, AIFUNCTION);
   If ULStat <> 0 Then Exit;

   lblShowADCount.Caption := IntToStr(ADCurCount);
   lblShowADIndex.Caption := IntToStr(ADCurIndex);
   {
    Check if the background operation has finished. If it has, then
    transfer the data from the memory buffer set up by Windows to an
    array for use by Delphi
    The BACKGROUND operation must be explicitly stopped
   }
   If (ADStatus = RUNNING) And (ADUserTerm = False) Then
   begin
      lblShowADStat.Caption := 'Running';
      If (ADCurCount > PrnNum) then
      begin
         Memo1.Text := '';
         NumPoints := 1;
         FirstPoint := PrnNum;
         ULStat := cbWinBufToArray (ADMemHandle, ADData[0], FirstPoint, NumPoints);
         If ULStat <> 0 then exit;
         Memo1.Lines.Add (Format('Sample number %d:   %d',[PrnNum, ADData[0]]));
         Inc(PrnNum, 1000);
      end
   end
   Else
   begin
      ULStat := cbStopBackground(BoardNum,AIFUNCTION);
      CmdADStop.Visible := False;
      CmdADStart.Visible := True;
      If ULStat <> 0 Then Exit;
      lblShowADStat.Caption := 'Idle';
      ULStat := cbGetStatus(BoardNum, ADStatus, ADCurCount, ADCurIndex, AIFUNCTION);
      If ULStat <> 0 Then Exit;
      lblShowADCount.Caption := IntToStr(ADCurCount);
      lblShowADIndex.Caption := IntToStr(ADCurIndex);
      If ADMemHandle = 0 Then Exit;

      {
      Transfer the data from the Windows buffer to an array.  This data
      could also be accessed directly using a pointer.
      }
      FirstPoint := 0;
      ULStat := cbWinBufToArray (ADMemHandle, ADData[0], FirstPoint, Count);
      If ULStat <> 0 then exit;
      Memo1.Text := '';
      index := 0;
      while index < 4 do
      begin
         Memo1.Lines.Add (Format('Channel 0, sample number %d:  %d', [index, ADData[index]]));
         Memo1.Lines.Add ('');
         Inc(index, 2);
      end;
   end;

   { cbGetStatus Parameters:
      BoardNum    :the number used by CB.CFG to describe this board
      ADStatus    :current status of the background DAC operation
      ADCurCount  :current number of samples sent to the DAC
      ADCurIndex  :index to the data buffer pointing to the start of the
                   most recently sent data
     Subsystem   :the subsystem for which to get status(AOFUNCTION)
   }
   ULStat := cbGetStatus(BoardNum, DAStatus, DACurCount, DACurIndex, AOFUNCTION);
   If ULStat <> 0 Then Exit;

   lblShowDACount.Caption := IntToStr(DACurCount);
   lblShowDAIndex.Caption := IntToStr(DACurIndex);
   {
    Check if the background operation has finished. If it has, then
    The BACKGROUND operation must be explicitly stopped
   }
   If (DAStatus = RUNNING) And (DAUserTerm = False) Then
   begin
      lblShowDAStat.Caption := 'Running';
   end
   Else
   begin
      ULStat := cbStopBackground(BoardNum,AOFUNCTION);
      CmdDAStop.Visible := False;
      CmdDAStart.Visible := True;
      If ULStat <> 0 Then Exit;
      lblShowDAStat.Caption := 'Idle';
      ULStat := cbGetStatus(BoardNum, DAStatus, DACurCount, DACurIndex, AOFUNCTION);
      If ULStat <> 0 Then Exit;
      lblShowDACount.Caption := IntToStr(DACurCount);
      lblShowDAIndex.Caption := IntToStr(DACurIndex);

  end;

  If (ADStatus = IDLE) And (DAStatus = IDLE) Then
  begin
      cmdQuit.Enabled := True;
  end

end;

procedure TfrmAInAoutScan.cmdADStopClick(Sender: TObject);
begin
   ADUserTerm := True;      {ends background operation}
end;

procedure TfrmAInAoutScan.cmdDAStopClick(Sender: TObject);
begin
   DAUserTerm := True;      {ends background operation}
end;

procedure TfrmAInAoutScan.cmdQuitClick(Sender: TObject);
begin
   tmrCheckStatus.Enabled := False;
   ULStat := cbStopBackground(BoardNum,AIFUNCTION);
   ULStat := cbStopBackground(BoardNum,AOFUNCTION);
   ULStat := cbWinBufFree (ADMemHandle);
   ULStat := cbWinBufFree (DAMemHandle);
   Close;
end;

end.

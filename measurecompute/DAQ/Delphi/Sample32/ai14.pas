unit Ai14;
{
ULAI14.DPR================================================================

 File:                         AI14.PAS

 Library Call Demonstrated:    cbSetTrigger()

 Purpose:                      Selects the trigger source. This trigger is
                               used to initiate A/D conversions using cbAinscan
                               with EXTTRIGGER selected.

 Demonstration:                Selects the trigger source and type.
                               Displays the analog input on two channels.

 Other Library Calls:          cbErrHandling()

 Special Requirements:         Board 0 must have software selectable triggering
                               source and type.
                               Board 0 must have an A/D converter.
                               Analog signals on two input channels.

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
    procedure tmrAInTimer(Sender: TObject);
    procedure cmdStartClick(Sender: TObject);
    procedure cmdQuitClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
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
   ErrReporting:          Integer;
   ErrHandling:           Integer;
   ADData:                array[0..600] of Word;
   Revlevel:              Single;
   LowThreshold:          Word;
   HighThreshold:         Word;
   TrigType:              Integer;
   Rate:                  LongInt;

const
   BoardNum:              Integer = 0;
   Count:                 Integer = 600;
   FirstPoint:            LongInt = 0;
   LowChan:               Integer = 0;
   HighChan:              Integer = 1;
   Range:                 LongInt = BIP5VOLTS;
   TargetRate:            LongInt = 1000;
   Options:               Integer = CONVERTDATA or EXTTRIGGER;



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
   Memo1.Text := 'Click start to acquire data';

   Rate := TargetRate;
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
   Select the Trigger source
        Parameters:
          BoardNum      :the number used by CB.CFG to describe this board
          TrigType     :the type of triggering based on external trigger source
          LowThreshold  :Low threshold when the trigger input is analog
          HighThreshold :High threshold when the trigger input is analog

   }
   
   { convert thresholds from engineering units(in Volts) to counts }
   ULStat := cbFromEngUnits(BoardNum, BIP10VOLTS, 1.0, HighThreshold);  { analog triggers use +/-10 V rang }
   ULStat := cbFromEngUnits(BoardNum, BIP10VOLTS, 0.1, LowThreshold);  
   TrigType := TRIGABOVE;
   ULStat := cbSetTrigger(BoardNum, TrigType, LowThreshold, HighThreshold);
   If ULStat = NOERRORS then
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
      Rate := TargetRate;
      ULStat := cbAInScan(BoardNum, LowChan, HighChan,
                       Count, Rate, Range, MemHandle, Options);
      If ULStat <> 0 then exit;
      Memo1.Text := '';
      
      {
      Transfer the data from the Windows buffer to an array.  This data
      could also be accessed directly using a pointer.
      }
      ULStat := cbWinBufToArray (MemHandle, ADData[0], FirstPoint, Count);
      If ULStat <> 0 then exit;

      index := 0;
      while index < 8 do
      begin
         Memo1.Lines.Add (Format('Channel 0: %d', [ADData[index]]));
         Memo1.Lines.Add (Format('Channel 1: %d', [ADData[index + 1]]));
         Memo1.Lines.Add ('');
         Inc(index, 2);
      end;
   end;
end;

procedure TfrmAInScan.cmdQuitClick(Sender: TObject);
begin
   tmrAIn.Enabled := False;
   ULStat := cbWinBufFree (MemHandle);
   Close;
end;

end.

unit Di04;
{
ULDI04.DPR ================================================================

 File:                         DI04.PAS

 Library Call Demonstrated:    cbDIn()

 Purpose:                      Reads a digital input port.

 Demonstration:                Reads the value on AUXPORT.

 Other Library Calls:          cbErrHandling()
                               cbGetConfig() using DIGITALINFO
                               cbDConfigPort()

 Special Requirements:         Board 0 must have a digital input port.

 (c) Copyright 1995 - 2003, Measurement Computing Corp.
 All rights reserved.
===========================================================================
}
interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, StdCtrls, ExtCtrls, cbw;

type
  TfrmDIO = class(TForm)
    tmrDIn: TTimer;
    cmdStart: TButton;
    cmdQuit: TButton;
    MemoData: TMemo;
    procedure tmrDInTimer(Sender: TObject);
    procedure cmdStartClick(Sender: TObject);
    procedure cmdQuitClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  frmDIO: TfrmDIO;

implementation

{$R *.DFM}

var
   ULStat:          Integer;
   DataValue:       Word;
   BitValue:        Integer;
   PowerVal:        Integer;
   PortNum:         Integer;
   ValString:       string;
   ErrReporting:    Integer;
   ErrHandling:     Integer;
   Result:          Integer;
   RevLevel:        Single;

const
   BoardNum:   Integer = 0;
   Zero:       Integer = 0;
   One:        Integer = 1;

procedure TfrmDIO.FormCreate(Sender: TObject);
var
   devNum:          Integer;
   PortType:        Integer;
   inmask, outmask: Integer;

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


   { Determine if board has AUXPORT 
     Parameters:
         DIGITALINFO : information about digital devices on the board 
         BoardNum    : the number used by CB.CFG to describe this board
         devNum      : 0-based digital device index
         DIDEVTYPE   : retrieve type of digital device - AUXPORT, FIRSTPORTA, ...
         PortType    : return value for type of device
   }
   devNum := 0;
   PortType := 0;
   ULStat := cbGetConfig(DIGITALINFO, BoardNum, devNum, DIDEVTYPE, PortType);
   If (ULStat <> NOERRORS) then
      begin
      MemoData.Text := 'ERROR: Not able to determine device type of digital port';
      end
   Else If (PortType <> AUXPORT) then
      begin
      MemoData.Text := 'ERROR: This board does NOT have an AUXPORT';
      cmdStart.Enabled := False;
      end
   Else
      begin
      MemoData.Text := 'Click Start to read digital inputs...';
      cmdStart.Enabled := True;
      end;


   { Check if AUXPORT needs configuring 
     Parameters:
         DIGITALINFO : information about digital devices on the board 
         BoardNum    : the number used by CB.CFG to describe this board
         devNum      : 0-based digital device index
         DIINMASK/DIOUTMASK   : get input/output bitmask configuration for port
         mask    : bitmask indicating corresponding bit is in direction of ConfigItem(DIINMASk or DIOUTMASK)
   }
   inmask := 0;
   outmask := 0;
   ULStat := cbGetConfig(DIGITALINFO, BoardNum, devNum, DIINMASK, inmask);
   If (ULStat <> NOERRORS) then  MemoData.Lines.Add('ERROR: Failed to retrieve digital IN mask.');

   ULStat := cbGetConfig(DIGITALINFO, BoardNum, devNum, DIOUTMASK, outmask);
   if (ULStat <> NOERRORS) then MemoData.Lines.Add('ERROR: Failed to retrieve digital OUT mask.');
   { Only non-configurable AUXPORT's have overlapping input and output bitmasks }
   if (0 = (inmask and outmask))  then cbDConfigPort(BoardNum, AUXPORT, DIGITALIN); 

end;

procedure TfrmDIO.cmdStartClick(Sender: TObject);
begin
   tmrDIn.Enabled := True;
end;

procedure TfrmDIO.tmrDInTimer(Sender: TObject);
var
   bitNum:              Integer;

begin
   {
   read the 4 bits digital input and display
     Parameters:
        BoardNum    :the number used by CB.CFG to describe this board
        PortNum     :the input port
        DataValue   :the value read from the port
   }
   PortNum := AUXPORT;
   ULStat := cbDIn (BoardNum, PortNum, DataValue);
   If ULStat <> 0 then exit;
   {
   display the value collected from the port
   }
   MemoData.Text := Format('The nibble value at AUXPORT is  %d', [DataValue]);
   MemoData.Lines.Add (' ');
   {
   parse DataValue into bit values to indicate on/off status
   }
   ValString := ' ';
   MemoData.Lines.Add ('Bit status is:');
   MemoData.Lines.Add (' ');
   MemoData.Lines.Add ('Bit num:  3  2  1  0');
   for  bitNum := 0 to 3 do
   begin
      BitValue := Zero;
      PowerVal := 1 shl (bitNum);
      Result := DataValue and PowerVal;
      if Result <> 0 then
      begin
         BitValue := One;
      end;
      ValString := '  ' + (IntToStr(BitValue)) + ValString;
   end;
   MemoData.Lines.Add ('  Value: ' +  ValString);
end;

procedure TfrmDIO.cmdQuitClick(Sender: TObject);
begin
   tmrDIn.Enabled := False;
   Close;
end;

end.

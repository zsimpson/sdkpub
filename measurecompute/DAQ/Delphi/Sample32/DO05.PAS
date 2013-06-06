unit Do05;
{
ULDO05.DPR ================================================================

 File:                         DO05.PAS

 Library Call Demonstrated:    cbDBitOut()

 Purpose:                      Sets the state of a single digital output bit.

 Demonstration:                Writes a bit value to the AUXPORT.

 Other Library Calls:          cbDConfigPort()
                               cbErrHandling()
                               cbGetConfig() using DIGITALINFO

 Special Requirements:         Board 0 must have a digital output port.

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
    cmdQuit: TButton;
    MemoData: TMemo;
    chkBit0: TCheckBox;
    chkBit3: TCheckBox;
    chkBit2: TCheckBox;
    chkBit1: TCheckBox;
    procedure cmdQuitClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure chkBit0Click(Sender: TObject);
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
   PortType:        Integer;
   BitNum:          Integer;
   ErrReporting:    Integer;
   ErrHandling:     Integer;
   BitValue:        SmallInt;

const
   BoardNum:        Integer = 0;

procedure TfrmDIO.FormCreate(Sender: TObject);
var
   devNum         : Integer;
   inmask, outmask: Integer;

begin
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
   cbGetConfig(DIGITALINFO, BoardNum, devNum, DIDEVTYPE, PortType);
   If (ULStat <> NOERRORS) then
      begin
      MemoData.Text := 'ERROR: Not able to determine device type of digital port';
      end
   Else If (PortType <> AUXPORT) then
      begin
      MemoData.Text := 'ERROR: This board does NOT have an AUXPORT';
      end
   Else
      begin
      MemoData.Text := 'Use radio buttons to set digital bits...';
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
	If (ULStat <> NOERRORS) then 	MemoData.Lines.Add('ERROR: Failed to retrieve digital IN mask.');

   ULStat := cbGetConfig(DIGITALINFO, BoardNum, devNum, DIOUTMASK, outmask);
	If (ULStat <> NOERRORS) then 	MemoData.Lines.Add('ERROR: Failed to retrieve digital IN mask.');

   { Only non-configurable AUXPORT's have overlapping input and output bitmasks }
   If (0 = (inmask and outmask)) then  cbDConfigPort(BoardNum, AUXPORT, DIGITALOUT);

   
end;

procedure TfrmDIO.chkBit0Click(Sender: TObject);
begin
   {
   write BitValue to BitNum of AUXPORT
     Parameters:
        BoardNum    :the number used by CB.CFG to describe this board
        PortType    :must be FIRSTPORTA or AUXPORT
        BitNum      :the number of the bit to be set to BitValue
        BitValue    :the value written to the port
   }
   BitNum := Integer((Sender As TCheckBox).Tag);
   BitValue := Integer((Sender As TCheckBox).Checked);
   PortType:=AUXPORT;
   ULStat := cbDBitOut (BoardNum, PortType, BitNum, BitValue);
   If ULStat <> 0 then exit;
   MemoData.Text := 'The following bit and value was written to AUXPORT:';
   MemoData.Lines.Add (' ');
   MemoData.Lines.Add (Format('Bit number %d was set to the value %d', [BitNum, BitValue]));
end;

procedure TfrmDIO.cmdQuitClick(Sender: TObject);
begin
   Close;
end;

end.

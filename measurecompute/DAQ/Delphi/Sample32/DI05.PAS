unit Di05;
{
ULDI05.DPR ================================================================

File:                         DI05.PAS

Library Call Demonstrated:    cbDBitIn()

Purpose:                      Reads digital AUXPORT bits.

Demonstration:                Sets cbDBitIn() to use AUXPORT and reads
                              the values at the AUXPORT pins.

Other Library Calls:          cbErrHandling()
                              cbGetConfig() using DIGITALINFO
                              cbDConfigPort()

Special Requirements:         Board 0 must have an AUXPORT.

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
   PortType:        Integer;
   ValString:       string;
   ErrReporting:    Integer;
   ErrHandling:     Integer;
   BitValue:        Word;

const
   BoardNum:   Integer = 0;

procedure TfrmDIO.FormCreate(Sender: TObject);
var
   devNum            : Integer;
   PortType          : Integer;
   inmask, outmask   : Integer;

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
   If (ULStat <> NOERRORS) then  MemoData.Lines.Add('ERROR: Failed to retrieve digital OUT mask.');

   { Only non-configurable AUXPORT's have overlapping input and output bitmasks }
   If (0 = (inmask and outmask)) then  cbDConfigPort(BoardNum, AUXPORT, DIGITALIN); 

end;

procedure TfrmDIO.cmdStartClick(Sender: TObject);
begin
   tmrDIn.Enabled := True;
end;

procedure TfrmDIO.tmrDInTimer(Sender: TObject);
var
  BitNum: Integer;

begin
   PortType := AUXPORT;
   ValString := '  ';
   for  BitNum := 0 to 3 do
   begin
      {
      read the input bits from the ports and display
        Parameters:
           BoardNum    :the number used by CB.CFG to describe this board
           PortType    :must be AUXPORT (or FIRSTPORTA for prog. ports)
           BitNum      :the input port
           BitValue    :the value read from the port
      }
      ULStat := cbDBitIn (BoardNum, PortType, BitNum, BitValue);
      If ULStat <> 0 then exit;
      ValString := '  ' + (IntToStr(BitValue)) + ValString;
   end;
   MemoData.Text := 'Bit status is:';
   MemoData.Lines.Add (' ');
   MemoData.Lines.Add ('Bit number:  3  2  1  0');
   MemoData.Lines.Add ('Bit value: ' + ValString);
end;

procedure TfrmDIO.cmdQuitClick(Sender: TObject);
begin
   tmrDIn.Enabled := False;
   Close;
end;

end.

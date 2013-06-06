unit Do04;
{
ULDO04.DPR ================================================================

 File:                         DO04.PAS

 Library Call Demonstrated:    cbDOut()

 Purpose:                      Writes a bit to a digital output port.

 Demonstration:                Writes a selected value to AUXPORT.

 Other Library Calls:          cbErrHandling()
                               cbGetConfig() using DIGITALINFO
                               cbDConfigPort()

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
    sbDOutVal: TScrollBar;
    procedure cmdQuitClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure sbDOutValScroll(Sender: TObject; ScrollCode: TScrollCode;
      var ScrollPos: Integer);
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
   PortNum:         Integer;
   ErrReporting:    Integer;
   ErrHandling:     Integer;

const
   BoardNum:   Integer = 0;

procedure TfrmDIO.FormCreate(Sender: TObject);
var
   devNum         : Integer;
   PortType       : Integer;
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
      MemoData.Text := 'Use scroll bar to set digital output value...';
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
	If (ULStat <> NOERRORS) then 	MemoData.Lines.Add('ERROR: Failed to retrieve digital OUT mask.');

   { Only non-configurable AUXPORT's have overlapping input and output bitmasks }
   If (0 = (inmask and outmask)) then  cbDConfigPort(BoardNum, AUXPORT, DIGITALOUT);

   {initialize port value}
   PortNum := AUXPORT;
   DataValue := 0;
   ULStat := cbDOut (BoardNum, PortNum, DataValue);
   If ULStat <> 0 then exit;
   
end;

procedure TfrmDIO.sbDOutValScroll(Sender: TObject; ScrollCode: TScrollCode;
  var ScrollPos: Integer);
begin
   DataValue := ScrollPos;
   {
   write the value to FIRSTPORTA
     Parameters:
        BoardNum    :the number used by CB.CFG to describe this board
        PortNum     :the output port
        DataValue   :the value written to the port
   }
   ULStat := cbDOut (BoardNum, PortNum, DataValue);
   If ULStat <> 0 then exit;
   MemoData.Text := Format('The byte value %d was written to AUXPORT.', [DataValue]);
end;

procedure TfrmDIO.cmdQuitClick(Sender: TObject);
begin
   Close;
end;

end.

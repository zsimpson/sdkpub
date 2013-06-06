unit Ao03;
{ULAO03================================================================

 File:                         AO03.PAS

 Library Call Demonstrated:    cbAOut()
                               cbSetConfig() using BIDACUPDATEMODE and
                                   BIDACUPDATECMD

 Purpose:                      Demonstrates difference between UPDATEIMMEDIATE
                               and UPDATEONCOMMAND D/A Update modes

 Demonstration:                Delays outputs until user sends BIDACUPDATECMD

 Other Library Calls:          cbErrHandling()
                               cbFromEng()

 Special Requirements:         Board 0 must support BIDACUPDATEMODE settings,
                               such as the PCI-DAC6700's.


 (c) Copyright 2003, Measurement Computing Corp.
 All rights reserved.
==========================================================================}

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Grids, ExtCtrls, cbw;

type
  TfrmAO03 = class(TForm)
    Label1: TLabel;
    SendDataBtn: TButton;
    UpdateBtn: TButton;
    edtAOutVolts0: TEdit;
    edtAOutVolts1: TEdit;
    edtAOutVolts2: TEdit;
    edtAOutVolts3: TEdit;
    RadioGroup1: TRadioGroup;
    rdioUpdateImmediately: TRadioButton;
    rdioUpdateOnCommand: TRadioButton;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    procedure FormCreate(Sender: TObject);
    procedure UpdateBtnClick(Sender: TObject);
    procedure rdioUpdateImmediatelyClick(Sender: TObject);
    procedure rdioUpdateOnCommandClick(Sender: TObject);
    procedure SendDataBtnClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  frmAO03: TfrmAO03;
  DevNum:  LongInt;       //device index used by cbSetConfig()
  ULStat:  LongInt;

const
     BdNum = 0;         //Board Number of device
     Range = BIP10VOLTS;// Analog Output range
     DontCare = 0;      //place-holder for variable not used in function call
     AllDevices = -1;   //negative values indicate all devices for cbSetConfig()

implementation

{$R *.DFM}


procedure TfrmAO03.FormCreate(Sender: TObject);
begin
   { Initiate error handling
     activating error handling will trap errors like
     bad channel numbers and non-configured conditions.
     Parameters:
       PRINTALL    :all warnings and errors encountered will be printed
       DONTSTOP    :if an error is encountered, the program will not stop,
                    errors must be handled locally      }
   cbErrHandling(PRINTALL, STOPALL);

   { Set default mode for updating D/A's on command
     Parameters
        BOARDINFO   : General information about the board
        BdNum       : Number used by CB.CFG to describe this board
        DevNum      : Selects device; in this case, selects D/A channel to configure
                      Note that -1 selects all D/A channels
        BIDACUPDATEMODE : Selects update mode for D/A, whether immediately (via cbAOut
                          or cbAOutScan) or upon issuing BIDACUPDATECMD
        UPDATEONCOMMAND : Delay D/A output updates from cbAOut or cbAOutScan until
                          BIDACUPDATECMD is issued. }
   ULStat := cbSetConfig(BOARDINFO, BdNum, DevNum, BIDACUPDATEMODE, UPDATEONCOMMAND);
   If ULStat <> 0 then exit;
end;



procedure TfrmAO03.UpdateBtnClick(Sender: TObject);
var
    ConfigVal:  LongInt;

begin
   { Issue command to update all the D/A's with the last value written
     to them via cbAOut or cbAOutScan
     Parameters
      BOARDINFO   : General information about the board
      BdNum       : Number used by CB.CFG to describe this board
      DevNum      : Not used for BIDACUPDATECMD
      BIDACUPDATECMD : Update D/A outputs with last value written
      ConfigVal   : Note used for BIDACUPDATECMD }
    DevNum := DontCare;
    ConfigVal := DontCare;
    ULStat := cbSetConfig(BOARDINFO, BdNum, DevNum, BIDACUPDATECMD, ConfigVal);
    If ULStat <> 0 then exit;
end;



procedure TfrmAO03.rdioUpdateImmediatelyClick(Sender: TObject);
begin
   { Set DAC Update mode to update immediately upon cbAOut or cbAOutScan
    Parameters
      BOARDINFO   : General information about the board
      BdNum       : Number used by CB.CFG to describe this board
      DevNum      : Selects device; in this case, selects D/A channel to configure
                    Note that -1 selects all D/A channels
      BIDACUPDATEMODE : Selects update mode for D/A, whether immediately (via cbAOut
                        or cbAOutScan) or upon issuing BIDACUPDATECMD
      UPDATEIMMEDIATE : Update D/A outputs immediately upon cbAOut or cbAOutScan }
   DevNum := AllDevices;
   ULStat := cbSetConfig(BOARDINFO, BdNum, DevNum, BIDACUPDATEMODE, UPDATEIMMEDIATE);
   If ULStat <> 0 then exit;
end;



procedure TfrmAO03.rdioUpdateOnCommandClick(Sender: TObject);
begin
   { Set DAC Update mode to hold off updating D/A's until command is sent
     Parameters
        BOARDINFO   : General information about the board
        BdNum       : Number used by CB.CFG to describe this board
        DevNum      : Selects device; in this case, selects D/A channel to configure
                      Note that -1 selects all D/A channels
        BIDACUPDATEMODE : Selects update mode for D/A, whether immediately (via cbAOut
                          or cbAOutScan) or upon issuing BIDACUPDATECMD
        UPDATEONCOMMAND : Delay D/A output updates from cbAOut or cbAOutScan until
                          BIDACUPDATECMD is issued.}
   DevNum := AllDevices;
   ULStat := cbSetConfig(BOARDINFO, BdNum, DevNum, BIDACUPDATEMODE, UPDATEONCOMMAND);
   If ULStat <> 0 then exit;
end;



procedure TfrmAO03.SendDataBtnClick(Sender: TObject);
var
   chan:          Integer;
   volts:         Single;
   daCounts:      Word;

begin
     chan := 0;
     volts := StrToFloat(edtAoutvolts0.Text);
     { Convert from volts to D/A counts
       Parameters:
         BdNum       :the number used by CB.CFG to describe this board
         Range       :voltage range to be used by cbAOut
         volts       :value in engineering units to be converted
         dadata      :the value in binary counts corresponding to volts  }
     ULStat := cbFromEngUnits(BdNum, Range, volts, daCounts);
     If ULStat <> 0 then exit;

     { Load D/A value
       Parameters:
         BdNum    :the number used by CB.CFG to describe this board
         chan     :the D/A output channel
         Range    :voltage range
         daCount  :the value in binary counts to send to Chan  }
     ULStat := cbAOut(BdNum, chan, Range, daCounts);
     If ULStat <> 0 then exit;

     chan := 1;
     volts := StrToFloat(edtAoutvolts1.Text);
     cbFromEngUnits(BdNum, Range, volts, daCounts);
     ULStat := cbAOut(BdNum, chan, Range, daCounts);
     If ULStat <> 0 then exit;

     chan := 2;
     volts := StrToFloat(edtAoutvolts2.Text);
     cbFromEngUnits(BdNum, Range, volts, daCounts);
     ULStat := cbAOut(BdNum, chan, Range, daCounts);
     If ULStat <> 0 then exit;

     chan := 3;
     volts := StrToFloat(edtAoutvolts3.Text);
     cbFromEngUnits(BdNum, Range, volts, daCounts);
     ULStat := cbAOut(BdNum, chan, Range, daCounts);
     If ULStat <> 0 then exit;

end;

end.

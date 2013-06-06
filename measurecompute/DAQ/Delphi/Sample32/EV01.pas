unit EV01;
{ULEV01.DPR================================================================

 File:                         ULEV01.PAS

 Library Call Demonstrated:    cbEnableEvent - ON_EXTERNAL_INTERRUPT
                               cbDisableEvent()

 Purpose:                      Generates an event for each pulse set at a
                               digital or counter External Interrupt pin,
                               and reads the digital input at FIRSTPORTA
                               every UpdateSize events.


 Demonstration:                Shows how to enable and respond to events.

 Other Library Calls:          cbErrHandling()
                               cbDConfigPort()
                               cbDIn()

 Special Requirements:         Board 0 must have an external interrupt pin
                               and support the ON_EXTERNAL_INTERRUPT event.


 (c) Copyright 2001-2002, Measurement Computing Corp.
 All rights reserved.
==========================================================================}


interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Cbw, StdCtrls;

type
  TfrmEventDisplay = class(TForm)
    cmdEnableEvents: TButton;
    cmdDisableEvents: TButton;
    Label2: TLabel;
    Label3: TLabel;
    Label1: TLabel;
    Label4: TLabel;
    txtInterruptCount: TEdit;
    txtEventCount: TEdit;
    txtInterruptsMissed: TEdit;
    txtDigitalIn: TEdit;

    procedure cmdEnableEventsClick(Sender: TObject);
    procedure cmdDisableEventsClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    EventCount: Integer;      //number of events handled since enabling events

  end;

  TEventCallback = procedure(BoardNum: Integer; EventType: Integer; EventData: Integer);

var
  frmEventDisplay: TfrmEventDisplay;


implementation



const
  BoardNum    = 0;          //Board number
  PortNum     = FIRSTPORTA;  //digital port to read ON_EXTERNAL_INTERRUPT event
  Direction   = DIGITALIN;  //set direction of PortNum to input

  UpdateCount = 10;         //controls how often to read FIRSTPORTA and update the display


{$R *.DFM}

{
 This gets called for each ON_EXTERNAL_INTERRUPT event. For this event type,
 the EventData supplied curresponds to the number of interrupts that occurred
 since the event was last enabled.
}
procedure MyCallback(Bd: LongInt; EventType: LongInt; InterruptCount: LongInt;
                  UserData: Pointer);stdcall;
var
   ULStat: Integer;
   DigitalData: Word;
   Display: TfrmEventDisplay;

begin
    Display := UserData;
    Inc(Display.EventCount);


    {
     We only update the display every UPDATE_SIZE events since the work below
     is "expensive." The longer we spend in this handler and the more frequent
     the interrupts occur, the more likely we'll miss interrupts.
    }
    if (Display.EventCount mod UpdateCount)=0 then
       begin
       Display.txtEventCount.Text := IntToStr(Display.EventCount);
       Display.txtInterruptCount.Text := IntToStr(InterruptCount);
       Display.txtInterruptsMissed.Text :=
                                          IntToStr(InterruptCount-Display.EventCount);

       {
        read FIRSTPORTA digital input and display

        Parameters:
          bd           :the number used by CB.CFG to describe this board
          PortNum      :the input port
          DigitalData  :the value read from the port
       }
       
       ULStat := cbDIn(bd, PortNum, DigitalData);
       if (ULStat = NOERRORS) then
          begin
          Display.txtDigitalIn.Text := IntToHex(DigitalData, 2);
          end;
       end;
end;


procedure TfrmEventDisplay.cmdEnableEventsClick(Sender: TObject);
var
   ULStat: Integer;
   EventType: Integer;
   EventSize: Integer;

begin

   {
    Enable and connect one or more event types to a single user callback
    function using cbEnableEvent().

    Parameters:
      BoardNum    :the number used by CB.CFG to describe this board
      EventType   :the condition that will cause an event to fire
      EventSize   :only used for ON_DATA_AVAILABLE to determine how
                   many samples to collect before firing an event
      @MyCallback :the address of the user function to call when above event
                  type occurs. Note that this function cannot be a member
                  function. So, send self-reference to handle instance specific
                  data.
      Self        :provide reference to this instance of the form so that
                   handler accesses this form's data, not some other's.
   }
   EventType := ON_EXTERNAL_INTERRUPT;
   EventSize := 0;
   ULStat := cbEnableEvent(BoardNum, EventType, EventSize, @MyCallback, Self);
   if (ULStat = NOERRORS) then
      begin
      //reset all counts and displays
      EventCount := 0;
      txtInterruptsMissed.Text := '0';
      txtEventCount.Text := '0';
      txtInterruptCount.Text := '0';
      end;


end;

procedure TfrmEventDisplay.cmdDisableEventsClick(Sender: TObject);

begin
  {
   Disable and disconnect all event types with cbDisableEvent()

   Since disabling events that were never enabled is harmless,
   we can disable all the events at once.

   Parameters:
     BoardNum         :the number used by CB.CFG to describe this board
     ALL_EVENT_TYPES  :all event types will be disabled
  }
  cbDisableEvent(BoardNum, ALL_EVENT_TYPES);

end;

procedure TfrmEventDisplay.FormCreate(Sender: TObject);

begin
  {
   Initiate error handling
    activating error handling will trap errors like
    bad channel numbers and non-configured conditions.

   Parameters:
       PRINTALL    :all warnings and errors encountered will be printed
       DONTSTOP    :if an error is encountered, the program will not stop,
                    errors must be handled locally
  }
  cbErrHandling(PRINTALL, DONTSTOP);

  {
  configure FIRSTPORTA for digital input

  Parameters:
      BoardNum    :the number used by CB.CFG to describe this board.
      FIRSTPORTA  :the input port
      DIGITALIN   :sets the port for input
  }
  cbDConfigPort(BoardNum, FIRSTPORTA, DIGITALIN);

end;

procedure TfrmEventDisplay.FormDestroy(Sender: TObject);

begin
  {
   Make sure all events are disabled before exiting
   Disable and disconnect all event types with cbDisableEvent()

   Since disabling events that were never enabled is harmless,
    we can disable all the events at once.

   Parameters:
     BoardNum         :the number used by CB.CFG to describe this board
     ALL_EVENT_TYPES  :all event types will be disabled
  }
  cbDisableEvent(BoardNum, ALL_EVENT_TYPES);

end;




end.

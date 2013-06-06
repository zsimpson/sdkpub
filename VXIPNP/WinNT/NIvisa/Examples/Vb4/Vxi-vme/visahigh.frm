VERSION 4.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   285
   ClientLeft      =   1125
   ClientTop       =   10350
   ClientWidth     =   1560
   Height          =   690
   Left            =   1065
   LinkTopic       =   "Form1"
   ScaleHeight     =   285
   ScaleWidth      =   1560
   Top             =   10005
   Width           =   1680
End
Attribute VB_Name = "Form1"
Attribute VB_Creatable = False
Attribute VB_Exposed = False
Private Sub Form_Initialize()
    MsgBox ("This program writes to and reads from the configuration registers of a VXI device at logical address zero.  It requires the vpptype.bas and visa32.bas modules to be included in the project to run.  The program displays the status of each command in the debug window when run.")
End Sub

Private Sub Form_KeyPress(KeyAscii As Integer)
    End
End Sub

'
' For this code to run, the files visa32.bas and vpptype.bas
' must be added to the project.  These files should have been
' installed with VISA.
'
' This code reads and writes the offset register of the
' device at logical address 0.  To do this, the code reads
' the register at 0xC006 in A16 space, the writes the value
' back to the same register.  Then it moves the first four
' configuation registers into local RAM and displays this
' in the Debug.Print window.  This code uses only VISA functions.
'
' The general flow of the code is:
'   Open Resource Manager
'   Open VISA session to the instrument at LA 0
'   Read the offset register
'   Write the same value back to the offset register
'   Move in the first 4 configuration registers
'   Close VISA session
'
Private Sub Form_Load()

Dim defaultRM As Long
Dim status As Long
Dim vinstr As Long
Dim response As String * 256
Dim offset As Long
Dim value As Integer
Dim count As Long
Dim data(0 To 3) As Integer

' First we must call viOpenDefaultRM to get the manager handle
' We will store this handle in defaultRM

status = viOpenDefaultRM(defaultRM)
status = viStatusDesc(defaultRM, status, response)
Debug.Print "viOpenDefaultRM", Hex(status), response

' To open a session we must use the resource manager handle from
' viOpenDefaultRM, and we must use a string which will
' indicate which instrument to open.  This is called the
' instrument descriptor.  The format for this string can be
' found in the NI-VISA programmers reference manual.  After
' opening a session to the device, we will get a handle to the
' instrument which we will use in later VISA functions.  The
' two parameters in this function which are 0 are reserved
' for future functionality.

status = viOpen(defaultRM, "VXI0::0::INSTR", 0, 0, vinstr)
status = viStatusDesc(defaultRM, status, response)
Debug.Print "viOpen", Hex(status), response

' Now we will read in the offset register and display it on
' the screen.  We must use the session handle to the instrument
' from the viOpen function.  We will be reading 16 bits by using
' the viIn16 function.

offset = 6  ' offset in A16 space from the base of device memory

' Note that the offset is relative to the base of the device's
' memory space, not the base of the entire address space.

status = viIn16(vinstr, VI_A16_SPACE, offset, value)
status = viStatusDesc(defaultRM, status, response)
Debug.Print "viIn16", Hex(status), response
Debug.Print "Register at offset 6", Hex(value)

' Now we will write out the value just read with the viOut16
' function.  We will write this to the offset register for the device at
' logical address 0 using the instrument handle we acquired
' from viOpen.

status = viOut16(vinstr, VI_A16_SPACE, offset, value)
status = viStatusDesc(defaultRM, status, response)
Debug.Print "viOut16", Hex(status), response

' Now we will move the first 4 configuration registers into local
' memory.  This will be done using viMoveIn16.  We will move all
' data into memory starting at the base address specified by "data(0)"

offset = 0          ' we want to get data from 0xC000-0xC007
count = 4           ' move 4 16-bit pieces of data

status = viMoveIn16(vinstr, VI_A16_SPACE, offset, count, data(0))
status = viStatusDesc(defaultRM, status, response)
Debug.Print "viMoveIn16", Hex(status), response

Debug.Print "Register at offset 0", Hex(data(0))
Debug.Print "Register at offset 2", Hex(data(1))
Debug.Print "Register at offset 4", Hex(data(2))
Debug.Print "Register at offset 6", Hex(data(3))

' Now we must close the session to the instrument using
' viClose.  We must tell VISA what to close by use of the
' instrument handle, "vinstr".  We will also close the VISA
' Resource Manager.

status = viClose(vinstr)
status = viStatusDesc(defaultRM, status, response)
Debug.Print "viClose", Hex(status), response

status = viClose(defaultRM)
status = viStatusDesc(defaultRM, status, response)
Debug.Print "viClose", Hex(status), response

Debug.Print "Hit any key to quit."

End Sub



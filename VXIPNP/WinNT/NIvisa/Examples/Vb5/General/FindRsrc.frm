VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   405
   ClientLeft      =   255
   ClientTop       =   10470
   ClientWidth     =   1800
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   405
   ScaleWidth      =   1800
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub Form_Initialize()
    MsgBox ("This program finds all of the resources present in the system and displays the instrument descriptor for each resource.  The program displays the status of each command in the debug window when run.")
End Sub

Private Sub Form_KeyPress(KeyAscii As Integer)
    End
End Sub

'
' In Visual Basic 5 the VISA library can be referenced by choosing Project >> References
' and selecting Visa Library from the list (you may first need to browse for visa32.dll).
' This allows the VISA functions and VISA data types to be used in a program.
'
' This code finds all of the resources in the system and displays
' the instrument descriptor for each resource.
' This code uses only VISA functions.  The status of each VISA function
' is displayed in the debugging window along with the data read
' by the instrument.
'
' The general flow of the code is:
'   Open Resource Manager
'   Find the first available resource and display its descriptor
'   Display the descriptors for each additional resource
'   Close the VISA session
'   Close the Resource Manager

Private Sub Form_Load()

Dim defaultRM As ViSession
Dim status As ViStatus
Dim response As String * VI_FIND_BUFLEN
Dim descriptor As String * VI_FIND_BUFLEN
Dim nlist As ViFindList
Dim count As ViUInt32
Dim x As Long

' First we must call viOpenDefaultRM to get the manager handle
' We will store this handle in defaultRM.  The function viStatusDesc
' returns a text description of the status code returned by viOpenDefaultRM

status = viOpenDefaultRM(defaultRM)
status = viStatusDesc(defaultRM, status, response)
Debug.Print "viOpenDefaultRM", Hex(status), response

' Next we use the viFindRsrc command to tell VISA to search for all
' available resources in the system.  The instrument descriptor for the
' first resource is returned along with the number of resources found.

status = viFindRsrc(defaultRM, "?*INSTR", nlist, count, descriptor)
status = viStatusDesc(defaultRM, status, response)
Debug.Print "viFindRsrc", Hex(status), response
Debug.Print "The number of resources found was", count

If (count = 0) Then
    Debug.Print "No resources were found"
Else
    Debug.Print "The first resource is", descriptor
End If

' Now we will use the viFindNext command to retrieve each of the
' instrument descriptors for the remaining resources.
x = 1

While (x < count)
    status = viFindNext(nlist, descriptor)
    status = viStatusDesc(defaultRM, status, response)
    Debug.Print "viFindNext", Hex(status), response
    Debug.Print "The next resource is", descriptor
    x = x + 1
Wend

' Now we will close the VISA Resource Manager and the
' list of found resources.

status = viClose(nlist)
status = viStatusDesc(defaultRM, status, response)
Debug.Print "viClose", Hex(status), response

status = viClose(defaultRM)
status = viStatusDesc(defaultRM, status, response)
Debug.Print "viClose", Hex(status), response

Debug.Print "Hit any key to quit"

End Sub



Option Strict Off
Option Explicit On 
Imports System.Runtime.InteropServices
Module EventHandler
	
	' In Visual Basic, we must provide MccDaq.MccBoard.EnableEvent with the address of
	' a procedure declared in a "standard module"--a module containing only
	' procedure, type, and data declarations and definitions.
	'
	
	' Although we can't directly use a function method to handle the event, we
	' can supply a reference via the UserData parameter to the object or form
	' that initiated the event and use its methods for handling the event.
	'
    ' NOTE THAT UserData MUST BE TYPED TO MATCH THAT USED IN THE MccDaq.MccBoard.EnableEvent CALL!
	'
    Public Sub MyCallback(ByVal bd As Integer, ByVal EventType As MccDaq.EventType, ByVal EventData As UInt32, ByVal userData As System.IntPtr)

        Dim lEventData As Long
        Dim userStruct As UserData = CType(Marshal.PtrToStructure(userData, GetType(UserData)), UserData)

        'Since Visual Basic doesn't handle unsigned integers well, convert EventData from unsigned 
        ' 32-bit integer to signed 64-bit value. 
        lEventData = Convert.ToInt64(EventData)
        
        Call userStruct.ThisObj.OnEvent(bd, EventType, lEventData)

        Marshal.DestroyStructure(userData, (userData.GetType))

    End Sub



    Public Sub OnErrorCallback(ByVal bd As Integer, ByVal EventType As MccDaq.EventType, ByVal EventData As UInt32, ByVal userData As System.IntPtr)
        Dim lEventData As Long = Convert.ToInt64(EventData)
        Dim userStruct As UserData = CType(Marshal.PtrToStructure(userData, GetType(UserData)), UserData)
        Call userStruct.ThisObj.OnScanError(bd, EventType, lEventData)
        Marshal.DestroyStructure(userData, (userData.GetType))

    End Sub
End Module
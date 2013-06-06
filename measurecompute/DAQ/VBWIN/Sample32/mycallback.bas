Attribute VB_Name = "EventHandler"

' In Visual Basic, we must provide cbEnableEvent with the address of
' a procedure declared in a "standard module"--a module containing only
' procedure, type, and data declarations and definitions.
'

' Although we can't directly use a function method to handle the event, we
' can supply a reference via the UserData parameter to the object or form
' that initiated the event and use its methods for handling the event.
'
' NOTE THAT UserData MUST BE TYPED TO MATCH THAT USED IN THE cbEnableEvent CALL!
'
Public Sub MyCallback(ByVal bd As Integer, ByVal EventType As Long, _
                  ByVal EventData As Long, ByRef UserData As frmEventDisplay)

 Call UserData.OnEvent(bd, EventType, EventData)

End Sub



Public Sub OnErrorCallback(ByVal bd As Integer, ByVal EventType As Long, _
                        ByVal EventData As Long, ByRef UserData As frmEventDisplay)
   
   Call UserData.OnScanError(bd, EventType, EventData)
   
End Sub


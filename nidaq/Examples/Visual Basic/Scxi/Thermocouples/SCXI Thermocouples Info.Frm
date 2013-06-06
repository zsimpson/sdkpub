VERSION 5.00
Begin VB.Form CJCInfo 
   Caption         =   "CJC Information"
   ClientHeight    =   5535
   ClientLeft      =   2655
   ClientTop       =   2355
   ClientWidth     =   6735
   LinkTopic       =   "Form1"
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   5535
   ScaleWidth      =   6735
   Begin VB.CommandButton Command1 
      Caption         =   "Return"
      Height          =   375
      Left            =   5640
      TabIndex        =   1
      Top             =   5040
      Width           =   975
   End
   Begin VB.TextBox Text1 
      Height          =   4815
      Left            =   120
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   0
      Text            =   "SCXI Thermocouples Info.frx":0000
      Top             =   120
      Width           =   6495
   End
End
Attribute VB_Name = "CJCInfo"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
    CJCInfo.Hide
End Sub


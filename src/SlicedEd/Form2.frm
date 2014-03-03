VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "COMCTL32.OCX"
Begin VB.Form Form2 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Form2"
   ClientHeight    =   495
   ClientLeft      =   45
   ClientTop       =   375
   ClientWidth     =   1710
   ControlBox      =   0   'False
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   495
   ScaleWidth      =   1710
   StartUpPosition =   1  '所有者中心
   Begin ComctlLib.ProgressBar pgrbar 
      Height          =   495
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   1695
      _ExtentX        =   2990
      _ExtentY        =   873
      _Version        =   327682
      Appearance      =   1
   End
End
Attribute VB_Name = "Form2"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Form_Load()
  pgrbar.Value = 0
End Sub

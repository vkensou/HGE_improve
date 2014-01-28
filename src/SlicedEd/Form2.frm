VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "Mscomctl.ocx"
Begin VB.Form Form2 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Form2"
   ClientHeight    =   240
   ClientLeft      =   45
   ClientTop       =   375
   ClientWidth     =   2055
   ControlBox      =   0   'False
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   240
   ScaleWidth      =   2055
   StartUpPosition =   1  'CenterOwner
   Begin MSComctlLib.ProgressBar pgrbar 
      Height          =   255
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   2055
      _ExtentX        =   3625
      _ExtentY        =   450
      _Version        =   393216
      Appearance      =   1
   End
End
Attribute VB_Name = "Form2"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Form_Load()
  pgrbar.value = 0
End Sub

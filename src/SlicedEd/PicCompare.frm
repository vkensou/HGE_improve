VERSION 5.00
Begin VB.Form PicCompare 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "图片比较"
   ClientHeight    =   4875
   ClientLeft      =   45
   ClientTop       =   375
   ClientWidth     =   3720
   BeginProperty Font 
      Name            =   "宋体"
      Size            =   12
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form3"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4875
   ScaleWidth      =   3720
   StartUpPosition =   1  'CenterOwner
   Begin VB.CommandButton Command2 
      Caption         =   "取消"
      Height          =   390
      Left            =   2715
      TabIndex        =   2
      Top             =   4410
      Width           =   900
   End
   Begin VB.CommandButton Command1 
      Caption         =   "确定"
      Height          =   390
      Left            =   1755
      TabIndex        =   1
      Top             =   4410
      Width           =   900
   End
   Begin VB.ListBox List1 
      Height          =   4140
      Left            =   105
      TabIndex        =   0
      Top             =   90
      Width           =   3510
   End
End
Attribute VB_Name = "PicCompare"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False


Private Sub Form_Load()
  Dim n As Long
  If dqIndex = 0 Then Exit Sub
  If UBound(Images) < 2 Then Me.Hide: Exit Sub
  For n = 1 To dqIndex - 1
    List1.AddItem Images(n).FileName
  Next n
  For n = dqIndex + 1 To UBound(Images)
    List1.AddItem Images(n).FileName
  Next n
End Sub
Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
  If UnloadMode = 0 Then Cancel = 1
  Call Command2_Click
End Sub
Private Sub Command1_Click()
  Me.Hide
End Sub
Private Sub Command2_Click()
  List1.ListIndex = -1
  Me.Hide
End Sub



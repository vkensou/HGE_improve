VERSION 5.00
Begin VB.Form SelectFrame 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "选择帧"
   ClientHeight    =   4395
   ClientLeft      =   45
   ClientTop       =   375
   ClientWidth     =   6990
   BeginProperty Font 
      Name            =   "宋体"
      Size            =   12
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form4"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4395
   ScaleWidth      =   6990
   StartUpPosition =   1  'CenterOwner
   Begin VB.CommandButton Command2 
      Caption         =   "取消"
      Height          =   570
      Left            =   5475
      TabIndex        =   3
      Top             =   3570
      Width           =   1215
   End
   Begin VB.CommandButton Command1 
      Caption         =   "确定"
      Height          =   570
      Left            =   4050
      TabIndex        =   2
      Top             =   3570
      Width           =   1215
   End
   Begin SlicedEd.ShowPicture ShowPicture1 
      Height          =   3180
      Left            =   1755
      TabIndex        =   1
      Top             =   150
      Width           =   4950
      _ExtentX        =   8731
      _ExtentY        =   5609
   End
   Begin VB.ListBox List1 
      Height          =   3180
      Left            =   165
      TabIndex        =   0
      Top             =   150
      Width           =   1485
   End
End
Attribute VB_Name = "SelectFrame"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
  Me.Hide
End Sub

Private Sub Command2_Click()
  List1.ListIndex = -1
  Me.Hide
End Sub
Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
  If UnloadMode = 0 Then Cancel = 1: Command2_Click
End Sub


Private Sub Form_Load()
  Dim n As Long
  On Error GoTo t
  For n = 1 To UBound(frames)
    List1.AddItem n
  Next n
  ShowPicture1.AutoRedraw = True
  ShowPicture1.ImageWidth = 0
  ShowPicture1.ImageHeight = 0
  Exit Sub
t:
End Sub

Private Sub List1_Click()
  If List1.ListIndex = -1 Then Exit Sub
  ShowFrame ShowPicture1, List1.ListIndex + 1, 0
  Exit Sub
End Sub

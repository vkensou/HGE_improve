VERSION 5.00
Begin VB.Form RapidAdd 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "快速建立切片"
   ClientHeight    =   2430
   ClientLeft      =   45
   ClientTop       =   375
   ClientWidth     =   3705
   BeginProperty Font 
      Name            =   "宋体"
      Size            =   12
      Charset         =   134
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2430
   ScaleWidth      =   3705
   StartUpPosition =   2  'CenterScreen
   Begin VB.TextBox Text3 
      Height          =   360
      Left            =   1035
      TabIndex        =   7
      Text            =   "1"
      Top             =   1080
      Width           =   1530
   End
   Begin VB.TextBox Text2 
      Height          =   360
      Left            =   1035
      TabIndex        =   5
      Text            =   "1"
      Top             =   615
      Width           =   1530
   End
   Begin VB.TextBox Text1 
      Height          =   360
      Left            =   1035
      TabIndex        =   3
      Text            =   "1"
      Top             =   150
      Width           =   1530
   End
   Begin VB.CommandButton Command2 
      Caption         =   "取消"
      Height          =   480
      Left            =   2730
      TabIndex        =   1
      Top             =   1755
      Width           =   870
   End
   Begin VB.CommandButton Command1 
      Caption         =   "确定"
      Height          =   480
      Left            =   1665
      TabIndex        =   0
      Top             =   1755
      Width           =   870
   End
   Begin VB.Label Label3 
      AutoSize        =   -1  'True
      Caption         =   "总数："
      Height          =   240
      Left            =   180
      TabIndex        =   6
      Top             =   1140
      Width           =   720
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      Caption         =   "竖："
      Height          =   240
      Left            =   180
      TabIndex        =   4
      Top             =   675
      Width           =   480
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "横："
      Height          =   240
      Left            =   180
      TabIndex        =   2
      Top             =   210
      Width           =   480
   End
End
Attribute VB_Name = "RapidAdd"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Public hy As Boolean

Private Sub Command1_Click()
  hy = True
  Me.Hide
End Sub

Private Sub Command2_Click()
  hy = False
  Me.Hide
End Sub

Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
  If UnloadMode = 0 Then Cancel = 1
  Call Command2_Click

End Sub

Private Sub Text1_Change()
  Text1.Text = Val(Text1.Text)
  If Val(Text1.Text) < 1 Then Text1.Text = "1"
  Text3.Text = Text1.Text * Text2.Text
End Sub

Private Sub Text2_Change()
  Text2.Text = Val(Text2.Text)
  If Val(Text2.Text) < 1 Then Text2.Text = "1"
  Text3.Text = Text1.Text * Text2.Text
End Sub

Private Sub Text3_Change()
  Text3.Text = Val(Text3.Text)
  If Text3.Text > Text1.Text * Text2.Text Then Text3.Text = Text1.Text * Text2.Text
End Sub

VERSION 5.00
Begin VB.Form PicZoom 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "图像缩放"
   ClientHeight    =   4980
   ClientLeft      =   45
   ClientTop       =   375
   ClientWidth     =   3705
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
   ScaleHeight     =   332
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   247
   StartUpPosition =   1  'CenterOwner
   Begin VB.PictureBox Picture1 
      BackColor       =   &H00FF00FF&
      Height          =   720
      Left            =   345
      ScaleHeight     =   44
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   44
      TabIndex        =   10
      Top             =   3075
      Width           =   720
   End
   Begin VB.CheckBox Check2 
      Caption         =   "使用透明色"
      Height          =   270
      Left            =   375
      TabIndex        =   9
      Top             =   2685
      Value           =   1  'Checked
      Width           =   1560
   End
   Begin VB.TextBox Text2 
      Height          =   360
      Left            =   1410
      TabIndex        =   8
      Text            =   "200"
      Top             =   1650
      Width           =   1125
   End
   Begin VB.TextBox Text1 
      Height          =   360
      Left            =   1395
      TabIndex        =   7
      Text            =   "300"
      Top             =   1095
      Width           =   1125
   End
   Begin VB.CommandButton Command2 
      Caption         =   "取消"
      Height          =   495
      Left            =   2355
      TabIndex        =   4
      Top             =   4275
      Width           =   1155
   End
   Begin VB.CommandButton Command1 
      Caption         =   "确定"
      Height          =   495
      Left            =   930
      TabIndex        =   3
      Top             =   4275
      Width           =   1155
   End
   Begin VB.CheckBox Check1 
      Caption         =   "保持比例"
      Height          =   390
      Left            =   360
      TabIndex        =   1
      Top             =   2040
      Value           =   1  'Checked
      Width           =   1965
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      Caption         =   "高："
      Height          =   240
      Left            =   600
      TabIndex        =   6
      Top             =   1695
      Width           =   480
   End
   Begin VB.Label Label3 
      AutoSize        =   -1  'True
      Caption         =   "宽："
      Height          =   240
      Left            =   600
      TabIndex        =   5
      Top             =   1155
      Width           =   480
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      Caption         =   "图像大小："
      Height          =   240
      Left            =   300
      TabIndex        =   2
      Top             =   765
      Width           =   1200
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "图片当前高：300，宽：200"
      Height          =   240
      Left            =   285
      TabIndex        =   0
      Top             =   195
      Width           =   2880
   End
End
Attribute VB_Name = "PicZoom"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim d As Long
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

Private Sub Picture1_Click()
On Error GoTo kk
  Form1.CD1.CancelError = True
  Form1.CD1.Color = Picture1.BackColor
  Form1.CD1.ShowColor
  Picture1.BackColor = Form1.CD1.Color
kk:
End Sub

Private Sub Text1_Change()
  Dim s As Double
  If d = 0 Then
    Text1.Text = CInt(Val(Text1.Text))
    If Check1.Value = 1 Then
      d = 1
      s = CInt(Text1.Text * Images(dqIndex).CurBit.Height / Images(dqIndex).CurBit.Width)
      If s = 0 Then s = 1
      Text2.Text = s
      d = 0
    End If
  End If
End Sub

Private Sub Text2_Change()
  Dim s As Double
  If d = 0 Then
    Text2.Text = CInt(Val(Text2.Text))
    If Check1.Value = 1 Then
      d = 1
      s = CInt(Text2.Text * Images(dqIndex).CurBit.Width / Images(dqIndex).CurBit.Height)
      If s = 0 Then s = 1
      Text1.Text = s
      d = 0
    End If
  End If
End Sub

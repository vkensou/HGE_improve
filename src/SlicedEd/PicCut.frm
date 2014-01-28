VERSION 5.00
Begin VB.Form PicCut 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "图片修剪"
   ClientHeight    =   3900
   ClientLeft      =   45
   ClientTop       =   375
   ClientWidth     =   4935
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
   ScaleHeight     =   3900
   ScaleWidth      =   4935
   StartUpPosition =   1  'CenterOwner
   Begin VB.Frame Frame2 
      Caption         =   "修掉"
      Height          =   1050
      Left            =   142
      TabIndex        =   8
      Top             =   1980
      Width           =   4650
      Begin VB.CheckBox Check1 
         Caption         =   "右端"
         Height          =   330
         Index           =   3
         Left            =   1965
         TabIndex        =   12
         Top             =   600
         Value           =   1  'Checked
         Width           =   1080
      End
      Begin VB.CheckBox Check1 
         Caption         =   "底端"
         Height          =   330
         Index           =   2
         Left            =   180
         TabIndex        =   11
         Top             =   600
         Value           =   1  'Checked
         Width           =   1080
      End
      Begin VB.CheckBox Check1 
         Caption         =   "左端"
         Height          =   330
         Index           =   1
         Left            =   1965
         TabIndex        =   10
         Top             =   285
         Value           =   1  'Checked
         Width           =   1080
      End
      Begin VB.CheckBox Check1 
         Caption         =   "顶端"
         Height          =   330
         Index           =   0
         Left            =   180
         TabIndex        =   9
         Top             =   285
         Value           =   1  'Checked
         Width           =   1080
      End
   End
   Begin VB.CommandButton Command2 
      Caption         =   "取消"
      Height          =   525
      Left            =   3630
      TabIndex        =   7
      Top             =   3240
      Width           =   1110
   End
   Begin VB.CommandButton Command1 
      Caption         =   "确定"
      Height          =   525
      Left            =   2220
      TabIndex        =   6
      Top             =   3240
      Width           =   1110
   End
   Begin VB.Frame Frame1 
      Caption         =   "基于"
      Height          =   1785
      Left            =   142
      TabIndex        =   0
      Top             =   120
      Width           =   4650
      Begin VB.PictureBox Picture1 
         BackColor       =   &H00FF00FF&
         Enabled         =   0   'False
         Height          =   360
         Left            =   1950
         ScaleHeight     =   300
         ScaleWidth      =   1125
         TabIndex        =   13
         Top             =   360
         Width           =   1185
      End
      Begin VB.OptionButton Option1 
         Caption         =   "右下角颜色"
         Height          =   330
         Index           =   4
         Left            =   1965
         TabIndex        =   5
         Top             =   1260
         Width           =   1695
      End
      Begin VB.OptionButton Option1 
         Caption         =   "左下角颜色"
         Height          =   330
         Index           =   3
         Left            =   210
         TabIndex        =   4
         Top             =   1260
         Width           =   1695
      End
      Begin VB.OptionButton Option1 
         Caption         =   "右上角颜色"
         Height          =   330
         Index           =   2
         Left            =   1965
         TabIndex        =   3
         Top             =   817
         Width           =   1695
      End
      Begin VB.OptionButton Option1 
         Caption         =   "左上角颜色"
         Height          =   330
         Index           =   1
         Left            =   210
         TabIndex        =   2
         Top             =   817
         Value           =   -1  'True
         Width           =   1695
      End
      Begin VB.OptionButton Option1 
         Caption         =   "指定颜色"
         Height          =   330
         Index           =   0
         Left            =   210
         TabIndex        =   1
         Top             =   375
         Width           =   1695
      End
   End
End
Attribute VB_Name = "PicCut"
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

Private Sub Option1_Click(Index As Integer)
  Picture1.Enabled = Index = 0
End Sub

Private Sub Picture1_Click()
On Error GoTo kk
  Form1.CD1.CancelError = True
  Form1.CD1.Color = Picture1.BackColor
  Form1.CD1.ShowColor
  Picture1.BackColor = Form1.CD1.Color
kk:
End Sub
Private Sub Form_QueryUnload(Cancel As Integer, UnloadMode As Integer)
  If UnloadMode = 0 Then Cancel = 1
  Call Command2_Click
End Sub


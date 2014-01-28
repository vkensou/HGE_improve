VERSION 5.00
Begin VB.Form MVEdit 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "动画编辑器"
   ClientHeight    =   6150
   ClientLeft      =   45
   ClientTop       =   375
   ClientWidth     =   9735
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
   ScaleHeight     =   6150
   ScaleWidth      =   9735
   StartUpPosition =   1  'CenterOwner
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   1
      Left            =   405
      Top             =   4365
   End
   Begin VB.CommandButton Command2 
      Caption         =   "删除"
      Height          =   360
      Left            =   1125
      TabIndex        =   4
      Top             =   3510
      Width           =   705
   End
   Begin VB.CommandButton Command1 
      Caption         =   "新建"
      Height          =   330
      Left            =   120
      TabIndex        =   3
      Top             =   3510
      Width           =   705
   End
   Begin VB.Frame Frame1 
      Caption         =   "编辑"
      Enabled         =   0   'False
      Height          =   4845
      Left            =   2070
      TabIndex        =   2
      Top             =   180
      Width           =   7455
      Begin VB.CommandButton Command9 
         Caption         =   "全部应用"
         Height          =   345
         Left            =   4920
         TabIndex        =   16
         Top             =   3960
         Width           =   1290
      End
      Begin VB.CheckBox Check1 
         Caption         =   "循环"
         Height          =   300
         Left            =   150
         TabIndex        =   15
         Top             =   4455
         Width           =   1320
      End
      Begin VB.CommandButton Command8 
         Caption         =   "播放"
         Height          =   360
         Left            =   135
         TabIndex        =   14
         Top             =   4005
         Width           =   795
      End
      Begin VB.CommandButton Command7 
         Caption         =   "确定"
         Enabled         =   0   'False
         Height          =   345
         Left            =   4080
         TabIndex        =   13
         Top             =   3960
         Width           =   675
      End
      Begin VB.TextBox Text1 
         Enabled         =   0   'False
         Height          =   375
         Left            =   3030
         TabIndex        =   12
         Text            =   "0"
         Top             =   3945
         Width           =   915
      End
      Begin SlicedEd.ShowPicture ShowPicture1 
         Height          =   3360
         Left            =   1755
         TabIndex        =   10
         Top             =   330
         Width           =   5265
         _ExtentX        =   9287
         _ExtentY        =   5927
      End
      Begin VB.CommandButton Command6 
         Caption         =   "下移"
         Height          =   405
         Left            =   900
         TabIndex        =   9
         Top             =   3015
         Width           =   690
      End
      Begin VB.CommandButton Command5 
         Caption         =   "上移"
         Height          =   405
         Left            =   135
         TabIndex        =   8
         Top             =   3015
         Width           =   690
      End
      Begin VB.CommandButton Command4 
         Caption         =   "移除"
         Height          =   405
         Left            =   900
         TabIndex        =   7
         Top             =   2505
         Width           =   690
      End
      Begin VB.CommandButton Command3 
         Caption         =   "加入"
         Height          =   405
         Left            =   135
         TabIndex        =   6
         Top             =   2505
         Width           =   690
      End
      Begin VB.ListBox List2 
         Height          =   1980
         Left            =   210
         TabIndex        =   5
         Top             =   465
         Width           =   1440
      End
      Begin VB.Label Label4 
         AutoSize        =   -1  'True
         Caption         =   "Label4"
         Height          =   240
         Left            =   2745
         TabIndex        =   18
         Top             =   4440
         Width           =   720
      End
      Begin VB.Label Label3 
         AutoSize        =   -1  'True
         Caption         =   "Label3"
         Height          =   240
         Left            =   1755
         TabIndex        =   17
         Top             =   4485
         Width           =   720
      End
      Begin VB.Label Label2 
         AutoSize        =   -1  'True
         Caption         =   "持续时间："
         Height          =   240
         Left            =   1800
         TabIndex        =   11
         Top             =   3975
         Width           =   1200
      End
   End
   Begin VB.ListBox List1 
      Height          =   2940
      Left            =   120
      TabIndex        =   0
      Top             =   465
      Width           =   1830
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "动画："
      Height          =   240
      Left            =   135
      TabIndex        =   1
      Top             =   135
      Width           =   720
   End
End
Attribute VB_Name = "MVEdit"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private dqm As Long
Private Declare Function GetTickCount Lib "kernel32" () As Long
Private bsj As ClsGameTimer, bn As Long

Private Sub Check1_Click()
  MVs(dqm).Mode = Check1.Value
End Sub

Private Sub Command1_Click()
  ReDim Preserve MVs(UBound(MVs) + 1)
  ReDim MVs(UBound(MVs)).frames(0)
  
  List1.AddItem UBound(MVs)
  List1.ListIndex = List1.ListCount - 1
End Sub

Private Sub Command2_Click()
  If List1.ListIndex = -1 Then Exit Sub
  Dim v As Long
  v = List1.ListIndex + 1
  Dim n As Long
  For n = v To UBound(MVs) - 1
    MVs(n) = MVs(n + 1)
  Next n
  ReDim Preserve MVs(UBound(MVs) - 1)
  List1.Clear
  For n = 1 To UBound(MVs)
    List1.AddItem n
  Next n
  If v < List1.ListCount Then List1.ListIndex = v - 1 Else List1.ListIndex = List1.ListCount - 1
End Sub

Private Sub Command3_Click()
  SelectFrame.Show 1
  Dim v As Long, n As Long
  v = SelectFrame.List1.ListIndex
  Unload SelectFrame
  If v = -1 Then Exit Sub
  ReDim Preserve MVs(dqm).frames(UBound(MVs(dqm).frames) + 1)
  MVs(dqm).frames(UBound(MVs(dqm).frames)).Index = v + 1
  RefreshMVWH dqm
  ShowPicture1.ImageWidth = MVs(dqm).Width
  ShowPicture1.ImageHeight = MVs(dqm).Height
  List2.AddItem v + 1
  List2.ListIndex = List2.ListCount - 1
End Sub

Private Sub Command4_Click()
  If List2.ListIndex = -1 Then Exit Sub
  Dim v As Long
  v = List2.ListIndex + 1
  Dim n As Long
  For n = v To UBound(MVs(dqm).frames) - 1
    MVs(dqm).frames(n) = MVs(dqm).frames(n + 1)
  Next n
  ReDim Preserve MVs(dqm).frames(UBound(MVs(dqm).frames) - 1)
  RefreshMVWH dqm
  ShowPicture1.ImageWidth = MVs(dqm).Width
  ShowPicture1.ImageHeight = MVs(dqm).Height
  List2.Clear
  For n = 1 To UBound(MVs(dqm).frames)
    List2.AddItem MVs(dqm).frames(n).Index
  Next n
End Sub

Private Sub Command5_Click()
  If List2.ListIndex = -1 Then Exit Sub
  If List2.ListIndex = 0 Then Exit Sub
  Dim v As Long
  v = List2.ListIndex + 1
  Dim ls As typFrameInfo
  ls = MVs(dqm).frames(v - 1)
  MVs(dqm).frames(v - 1) = MVs(dqm).frames(v)
  MVs(dqm).frames(v) = ls
  
  ShowMV
  
End Sub

Private Sub Command6_Click()
  If List2.ListIndex = -1 Then Exit Sub
  If List2.ListIndex = List2.ListCount - 1 Then Exit Sub
  Dim v As Long
  v = List2.ListIndex + 1
  Dim ls As typFrameInfo
  
  ls = MVs(dqm).frames(v + 1)
  MVs(dqm).frames(v + 1) = MVs(dqm).frames(v)
  MVs(dqm).frames(v) = ls
    
  ShowMV
End Sub

Private Sub Command7_Click()
  If List2.ListIndex = -1 Then Exit Sub
  If Val(Text1.Text) < 0 Then Text1.Text = "0"
  MVs(dqm).frames(List2.ListIndex + 1).Time = Text1.Text
  
End Sub

Private Sub Command8_Click()
  If List2.ListIndex = -1 Then Exit Sub
  If List2.ListCount = 0 Then Exit Sub
  Set bsj = New ClsGameTimer
  bsj.StartTick
  bn = 1
  ShowFrame ShowPicture1, MVs(dqm).frames(bn).Index, 1, MVs(dqm).cx, MVs(dqm).cy
  Timer1.Enabled = True
End Sub

Private Sub Command9_Click()
  If List2.ListIndex = -1 Then Exit Sub
  If Val(Text1.Text) < 0 Then Text1.Text = "0"
  Dim n As Long
  For n = 1 To UBound(MVs(dqm).frames)
    MVs(dqm).frames(n).Time = Text1.Text
  Next n
End Sub

Private Sub Form_Load()
  Dim n As Long
  For n = 1 To UBound(MVs)
    List1.AddItem n
  Next n
  ShowPicture1.AutoRedraw = True
  ShowPicture1.ImageWidth = 0
  ShowPicture1.ImageHeight = 0
End Sub

Private Sub List1_Click()
  dqm = List1.ListIndex + 1
  Frame1.Enabled = True
  Timer1.Enabled = False
  ShowPicture1.ImageWidth = MVs(dqm).Width
  ShowPicture1.ImageHeight = MVs(dqm).Height
  ShowMV
  If List2.ListCount > 0 Then List2.ListIndex = 0
End Sub
Private Sub ShowMV()
  Dim n As Long
  List2.Clear
  For n = 1 To UBound(MVs(dqm).frames)
    List2.AddItem MVs(dqm).frames(n).Index
  Next n
  Label3.Caption = MVs(dqm).Width
  Label4.Caption = MVs(dqm).Height
  Check1.Value = MVs(dqm).Mode
End Sub

Private Sub List2_Click()
  If List2.ListIndex = -1 Then Exit Sub
  Dim x As Long: x = List2.ListIndex + 1
  ShowFrame ShowPicture1, MVs(dqm).frames(x).Index, 1, MVs(dqm).cx, MVs(dqm).cy
  Text1.Enabled = True
  Command7.Enabled = True
  Text1.Text = MVs(dqm).frames(x).Time
  Timer1.Enabled = False
End Sub

Private Sub Text1_Change()
  Text1.Text = Val(Text1.Text)
End Sub

Private Sub Timer1_Timer()
  If List1.ListIndex = -1 Then Timer1.Enabled = False: Exit Sub
  If List2.ListIndex = -1 Then Timer1.Enabled = False: Exit Sub
  If bsj.NowTick > MVs(dqm).frames(bn).Time Then
    bn = bn + 1
    If bn > UBound(MVs(dqm).frames) Then
      If Check1.Value Then
        bn = 1
      Else
      bsj.StopTick
      Timer1.Enabled = False
      Exit Sub
      End If
    End If
    bsj.StartTick
    ShowFrame ShowPicture1, MVs(dqm).frames(bn).Index, 1, MVs(dqm).cx, MVs(dqm).cy
  End If
End Sub

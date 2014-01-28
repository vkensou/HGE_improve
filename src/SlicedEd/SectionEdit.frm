VERSION 5.00
Begin VB.Form SectionEdit 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Form4"
   ClientHeight    =   6660
   ClientLeft      =   45
   ClientTop       =   375
   ClientWidth     =   10440
   BeginProperty Font 
      Name            =   "宋体"
      Size            =   12
      Charset         =   134
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form4"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   6660
   ScaleWidth      =   10440
   StartUpPosition =   2  'CenterScreen
   Begin VB.CheckBox Check2 
      Caption         =   "关联原图形"
      Height          =   360
      Left            =   255
      TabIndex        =   24
      Top             =   5670
      Width           =   1710
   End
   Begin VB.CheckBox Check1 
      Caption         =   "全部"
      Height          =   360
      Left            =   255
      TabIndex        =   15
      Top             =   6165
      Width           =   1020
   End
   Begin VB.Frame Frame1 
      Caption         =   "切片信息"
      Enabled         =   0   'False
      Height          =   2235
      Left            =   2280
      TabIndex        =   3
      Top             =   4230
      Width           =   7770
      Begin VB.CommandButton Command6 
         Caption         =   "置底"
         Height          =   405
         Left            =   6825
         TabIndex        =   23
         Top             =   758
         Width           =   810
      End
      Begin VB.CommandButton Command5 
         Caption         =   "中间"
         Height          =   405
         Left            =   5947
         TabIndex        =   22
         Top             =   758
         Width           =   810
      End
      Begin VB.CommandButton Command4 
         Caption         =   "置顶"
         Height          =   405
         Left            =   5070
         TabIndex        =   21
         Top             =   758
         Width           =   810
      End
      Begin VB.CommandButton Command3 
         Caption         =   "置右"
         Height          =   405
         Left            =   6825
         TabIndex        =   19
         Top             =   293
         Width           =   810
      End
      Begin VB.CommandButton Command2 
         Caption         =   "中间"
         Height          =   405
         Left            =   5947
         TabIndex        =   18
         Top             =   293
         Width           =   810
      End
      Begin VB.CommandButton Command1 
         Caption         =   "置左"
         Height          =   405
         Left            =   5070
         TabIndex        =   17
         Top             =   293
         Width           =   810
      End
      Begin VB.TextBox Text2 
         Height          =   450
         Left            =   3090
         TabIndex        =   8
         Text            =   "0"
         Top             =   1215
         Width           =   1335
      End
      Begin VB.TextBox Text1 
         Height          =   450
         Left            =   615
         TabIndex        =   6
         Text            =   "0"
         Top             =   1215
         Width           =   1335
      End
      Begin VB.Label Label12 
         AutoSize        =   -1  'True
         Caption         =   "纵坐标："
         Height          =   240
         Left            =   4110
         TabIndex        =   20
         Top             =   840
         Width           =   960
      End
      Begin VB.Label Label11 
         AutoSize        =   -1  'True
         Caption         =   "横坐标："
         Height          =   240
         Left            =   4110
         TabIndex        =   16
         Top             =   375
         Width           =   960
      End
      Begin VB.Label Label10 
         AutoSize        =   -1  'True
         Caption         =   "0"
         Height          =   240
         Left            =   2985
         TabIndex        =   14
         Top             =   195
         Width           =   120
      End
      Begin VB.Label Label9 
         AutoSize        =   -1  'True
         Caption         =   "0"
         Height          =   240
         Left            =   2220
         TabIndex        =   13
         Top             =   195
         Width           =   120
      End
      Begin VB.Label Label8 
         AutoSize        =   -1  'True
         Caption         =   "0"
         Height          =   240
         Left            =   1770
         TabIndex        =   12
         Top             =   435
         Width           =   120
      End
      Begin VB.Label Label7 
         AutoSize        =   -1  'True
         Caption         =   "0"
         Height          =   240
         Left            =   720
         TabIndex        =   11
         Top             =   420
         Width           =   120
      End
      Begin VB.Label Label6 
         AutoSize        =   -1  'True
         Caption         =   "高："
         Height          =   240
         Left            =   1215
         TabIndex        =   10
         Top             =   420
         Width           =   480
      End
      Begin VB.Label Label5 
         AutoSize        =   -1  'True
         Caption         =   "宽："
         Height          =   240
         Left            =   255
         TabIndex        =   9
         Top             =   420
         Width           =   480
      End
      Begin VB.Label Label4 
         AutoSize        =   -1  'True
         Caption         =   "Y:"
         Height          =   240
         Left            =   2730
         TabIndex        =   7
         Top             =   1320
         Width           =   240
      End
      Begin VB.Label Label3 
         AutoSize        =   -1  'True
         Caption         =   "X:"
         Height          =   240
         Left            =   210
         TabIndex        =   5
         Top             =   1320
         Width           =   240
      End
      Begin VB.Label Label2 
         AutoSize        =   -1  'True
         Caption         =   "中心坐标："
         Height          =   240
         Left            =   180
         TabIndex        =   4
         Top             =   915
         Width           =   1200
      End
   End
   Begin SlicedEd.ShowPicture ShowPicture1 
      Height          =   3420
      Left            =   2400
      TabIndex        =   2
      Top             =   540
      Width           =   7575
      _ExtentX        =   13361
      _ExtentY        =   6033
   End
   Begin VB.ListBox List1 
      Height          =   3420
      Left            =   315
      TabIndex        =   0
      Top             =   540
      Width           =   1620
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "切片列表："
      Height          =   240
      Left            =   330
      TabIndex        =   1
      Top             =   195
      Width           =   1200
   End
End
Attribute VB_Name = "SectionEdit"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private dqq As Long

Private Sub Command1_Click()
  If UBound(qps) = 0 Then Exit Sub
  If dqq = 0 Then Exit Sub
  If Check2.Value = 1 Then
    qps(dqq).cx = -qps(dqq).ox
  Else
    qps(dqq).cx = 0
  End If
  Dim n As Long
  If Check1.Value = 1 Then
    For n = 1 To UBound(qps)
      If Check2.Value = 1 Then
      Else
        qps(n).cx = 0
      End If
    Next n
  End If
  ShowQp ShowPicture1, dqq, 1
  Text1.Text = qps(dqq).cx
  Text2.Text = qps(dqq).cy
End Sub

Private Sub Command2_Click()
  If UBound(qps) = 0 Then Exit Sub
  If dqq = 0 Then Exit Sub
  If Check2.Value = 1 Then
    qps(dqq).cx = qps(dqq).oWidth / 2 - qps(dqq).ox
  Else
    qps(dqq).cx = (qps(dqq).Width - 1) / 2
  End If
  Dim n As Long
  If Check1.Value = 1 Then
    For n = 1 To UBound(qps)
      If Check2.Value = 1 Then
        qps(n).cx = qps(n).oWidth / 2 - qps(n).ox
        Debug.Print qps(n).cx + qps(n).ox
      Else
        qps(n).cx = (qps(n).Width - 1) / 2
      End If
    Next n
  End If
  ShowQp ShowPicture1, dqq, 1
  Text1.Text = qps(dqq).cx
  Text2.Text = qps(dqq).cy
End Sub

Private Sub Command3_Click()
  If UBound(qps) = 0 Then Exit Sub
  If dqq = 0 Then Exit Sub
  If Check2.Value = 1 Then
    qps(dqq).cx = qps(dqq).oWidth - 1 - qps(dqq).ox
  Else
    qps(dqq).cx = qps(dqq).Width - 1
  End If
  Dim n As Long
  If Check1.Value = 1 Then
    For n = 1 To UBound(qps)
      If Check2.Value = 1 Then
        qps(n).cx = qps(n).oWidth - 1 - qps(n).ox
      Else
        qps(n).cx = qps(n).Width - 1
      End If
    Next n
  End If
  ShowQp ShowPicture1, dqq, 1
  Text1.Text = qps(dqq).cx
  Text2.Text = qps(dqq).cy
End Sub

Private Sub Command4_Click()
  If UBound(qps) = 0 Then Exit Sub
  If dqq = 0 Then Exit Sub
  If Check2.Value = 1 Then
    qps(dqq).cy = -qps(dqq).oy
  Else
    qps(dqq).cy = 0
  End If
  Dim n As Long
  If Check1.Value = 1 Then
    For n = 1 To UBound(qps)
      If Check2.Value = 1 Then
        qps(n).cy = -qps(n).oy
      Else
        qps(n).cy = 0
      End If
    Next n
  End If
  ShowQp ShowPicture1, dqq, 1
  Text1.Text = qps(dqq).cx
  Text2.Text = qps(dqq).cy
End Sub

Private Sub Command5_Click()
  If UBound(qps) = 0 Then Exit Sub
  If dqq = 0 Then Exit Sub
  If Check2.Value = 1 Then
    qps(dqq).cy = qps(dqq).oHeight / 2 - qps(dqq).oy
  Else
    qps(dqq).cy = (qps(dqq).Height - 1) / 2
  End If
  Dim n As Long
  If Check1.Value = 1 Then
    For n = 1 To UBound(qps)
      If Check2.Value = 1 Then
        qps(n).cy = qps(n).oHeight / 2 - qps(n).oy
      Else
        qps(n).cy = (qps(n).Height - 1) / 2
      End If
    Next n
  End If
  ShowQp ShowPicture1, dqq, 1
  Text1.Text = qps(dqq).cx
  Text2.Text = qps(dqq).cy
End Sub

Private Sub Command6_Click()
  If UBound(qps) = 0 Then Exit Sub
  If dqq = 0 Then Exit Sub
  If Check2.Value = 1 Then
    qps(dqq).cy = qps(dqq).oHeight - 1 - qps(dqq).oy
  Else
    qps(dqq).cy = qps(dqq).Height - 1
  End If
  Dim n As Long
  If Check1.Value = 1 Then
    For n = 1 To UBound(qps)
      If Check2.Value = 1 Then
        qps(n).cy = qps(n).oHeight - 1 - qps(n).oy
        Debug.Print qps(n).cy + qps(n).oy
      Else
        qps(n).cy = qps(n).Height - 1
      End If
    Next n
  End If
  ShowQp ShowPicture1, dqq, 1
  Text1.Text = qps(dqq).cx
  Text2.Text = qps(dqq).cy
End Sub

Private Sub Form_Load()
  List1.Clear
  ShowPicture1.AutoRedraw = True
  On Error GoTo k
  Dim n As Long
  For n = 1 To UBound(qps)
    List1.AddItem n
  Next n
  If List1.ListCount > 0 Then List1.ListIndex = 0
k:
End Sub

Private Sub List1_Click()
  dqq = List1.ListIndex + 1
  If List1.ListIndex = -1 Then
    Frame1.Enabled = False
  Else
    ShowPicture1.ImageWidth = qps(dqq).Width
    ShowPicture1.ImageHeight = qps(dqq).Height
    ShowQp ShowPicture1, dqq, 1
    Text1.Text = qps(dqq).cx
    Text2.Text = qps(dqq).cy
    Label7.Caption = ShowPicture1.ImageWidth
    Label8.Caption = ShowPicture1.ImageHeight
    Label9.Caption = qps(dqq).ox
    Label10.Caption = qps(dqq).oy
    Frame1.Enabled = True
  End If
End Sub

Private Sub Text1_Change()
  Text1.Text = Val(Text1.Text)
  qps(dqq).cx = Text1.Text
  ShowQp ShowPicture1, dqq, 1
End Sub

Private Sub Text2_Change()
  Text2.Text = Val(Text2.Text)
  qps(dqq).cy = Text2.Text
  ShowQp ShowPicture1, dqq, 1
End Sub

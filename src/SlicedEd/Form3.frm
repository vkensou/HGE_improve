VERSION 5.00
Begin VB.Form FrameEdit 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Ö¡±à¼­Æ÷"
   ClientHeight    =   8370
   ClientLeft      =   45
   ClientTop       =   375
   ClientWidth     =   10920
   BeginProperty Font 
      Name            =   "ËÎÌå"
      Size            =   12
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form3"
   MaxButton       =   0   'False
   ScaleHeight     =   8370
   ScaleWidth      =   10920
   StartUpPosition =   1  'CenterOwner
   Begin VB.Frame Frame1 
      Caption         =   "±à¼­"
      Enabled         =   0   'False
      Height          =   7410
      Left            =   2100
      TabIndex        =   4
      Top             =   210
      Width           =   8685
      Begin VB.CheckBox Check1 
         Caption         =   "Ó¦ÓÃÔ­Æ«ÒÆ"
         Height          =   360
         Left            =   180
         TabIndex        =   20
         Top             =   4080
         Value           =   1  'Checked
         Width           =   1560
      End
      Begin VB.TextBox Text2 
         Height          =   360
         Left            =   3180
         TabIndex        =   19
         Text            =   "0"
         Top             =   6075
         Width           =   1410
      End
      Begin VB.TextBox Text1 
         Height          =   360
         Left            =   3180
         TabIndex        =   18
         Text            =   "0"
         Top             =   5655
         Width           =   1410
      End
      Begin SlicedEd.ShowPicture ShowPicture1 
         Height          =   5025
         Left            =   1815
         TabIndex        =   11
         Top             =   465
         Width           =   6645
         _ExtentX        =   11721
         _ExtentY        =   8864
      End
      Begin VB.CommandButton Command6 
         Caption         =   "ÏÂÒÆ"
         Height          =   375
         Left            =   885
         TabIndex        =   10
         Top             =   3405
         Width           =   675
      End
      Begin VB.CommandButton Command5 
         Caption         =   "ÉÏÒÆ"
         Height          =   375
         Left            =   90
         TabIndex        =   9
         Top             =   3405
         Width           =   675
      End
      Begin VB.CommandButton Command4 
         Caption         =   "ÒÆ³ý"
         Height          =   375
         Left            =   885
         TabIndex        =   8
         Top             =   2820
         Width           =   675
      End
      Begin VB.CommandButton Command3 
         Caption         =   "¼ÓÈë"
         Height          =   375
         Left            =   90
         TabIndex        =   7
         Top             =   2835
         Width           =   675
      End
      Begin VB.ListBox List2 
         Height          =   1980
         Left            =   165
         TabIndex        =   6
         Top             =   705
         Width           =   1440
      End
      Begin VB.Label Label8 
         AutoSize        =   -1  'True
         Caption         =   "ÇÐÆ¬Æ«ÒÆY£º"
         Height          =   240
         Left            =   1875
         TabIndex        =   17
         Top             =   6135
         Width           =   1320
      End
      Begin VB.Label Label7 
         AutoSize        =   -1  'True
         Caption         =   "ÇÐÆ¬Æ«ÒÆX£º"
         Height          =   240
         Left            =   1875
         TabIndex        =   16
         Top             =   5715
         Width           =   1320
      End
      Begin VB.Label Label6 
         AutoSize        =   -1  'True
         Caption         =   "0"
         Height          =   240
         Left            =   960
         TabIndex        =   15
         Top             =   6105
         Width           =   120
      End
      Begin VB.Label Label5 
         AutoSize        =   -1  'True
         Caption         =   "0"
         Height          =   240
         Left            =   960
         TabIndex        =   14
         Top             =   5670
         Width           =   120
      End
      Begin VB.Label Label4 
         AutoSize        =   -1  'True
         Caption         =   "Ö¡¸ß£º"
         Height          =   240
         Left            =   240
         TabIndex        =   13
         Top             =   6105
         Width           =   720
      End
      Begin VB.Label Label3 
         AutoSize        =   -1  'True
         Caption         =   "Ö¡¿í£º"
         Height          =   240
         Left            =   240
         TabIndex        =   12
         Top             =   5670
         Width           =   720
      End
      Begin VB.Label Label2 
         AutoSize        =   -1  'True
         Caption         =   "ÇÐÆ¬"
         Height          =   240
         Left            =   195
         TabIndex        =   5
         Top             =   360
         Width           =   480
      End
   End
   Begin VB.CommandButton Command2 
      Caption         =   "É¾³ý"
      Height          =   390
      Left            =   1060
      TabIndex        =   3
      Top             =   3315
      Width           =   705
   End
   Begin VB.CommandButton Command1 
      Caption         =   "ÐÂ½¨"
      Height          =   390
      Left            =   245
      TabIndex        =   2
      Top             =   3315
      Width           =   705
   End
   Begin VB.ListBox List1 
      Height          =   2700
      Left            =   135
      TabIndex        =   1
      Top             =   495
      Width           =   1740
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "Ö¡£º"
      Height          =   240
      Left            =   165
      TabIndex        =   0
      Top             =   195
      Width           =   480
   End
End
Attribute VB_Name = "FrameEdit"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim dqz As Long

Private Sub Command1_Click()
  Dim ubd As Long
  ubd = UBound(frames) + 1
  ReDim Preserve frames(ubd)
  ReDim frames(ubd).qps(0)
  List1.AddItem ubd
  List1.ListIndex = List1.ListCount - 1
End Sub

Private Sub Command2_Click()
  If List1.ListIndex = -1 Then Exit Sub
  Dim v As Long
  v = List1.ListIndex + 1
  Dim n As Long
  For n = v To UBound(frames) - 1
    frames(n) = frames(n + 1)
  Next n
  ReDim Preserve frames(UBound(frames) - 1)
  List1.Clear
  For n = 1 To UBound(frames)
    List1.AddItem n
  Next n
  If v < List1.ListCount Then List1.ListIndex = v - 1 Else List1.ListIndex = List1.ListCount - 1
  If List1.ListCount = 0 Then Frame1.Enabled = False
End Sub

Private Sub Command3_Click()
  SelectSection.Show 1
  Dim v As Long, n As Long
  v = SelectSection.List1.ListIndex + 1
  Unload SelectSection
  If v = 0 Then Exit Sub
  For n = 1 To UBound(frames(dqz).qps)
    If frames(dqz).qps(n).Index = v Then Exit Sub
  Next n
  With frames(dqz)
  Dim Index As Long: Index = UBound(.qps) + 1
  ReDim Preserve .qps(Index)
  .qps(Index).Index = v
  If Check1.Value Then
  .qps(Index).x = qps(v).ox
  .qps(Index).y = qps(v).oy
  End If
  End With
  RefreshFrameWH dqz
  List2.AddItem v
  List2.ListIndex = List2.ListCount - 1
  ShowFrame ShowPicture1, dqz, 0
  Label5.Caption = frames(dqz).Width
  Label6.Caption = frames(dqz).Height
End Sub

Private Sub Command4_Click()
  If List2.ListIndex = -1 Then Exit Sub
  Dim v As Long
  v = List2.ListIndex + 1
  Dim n As Long
  For n = v To UBound(frames(dqz).qps) - 1
    frames(dqz).qps(n) = frames(dqz).qps(n + 1)
  Next n
  ReDim Preserve frames(dqz).qps(UBound(frames(dqz).qps) - 1)
  RefreshFrameWH dqz
  List2.Clear
  For n = 1 To UBound(frames(dqz).qps)
    List2.AddItem frames(dqz).qps(n).Index
  Next n
  ShowFrame ShowPicture1, dqz, 0
  Label5.Caption = frames(dqz).Width
  Label6.Caption = frames(dqz).Height
End Sub

Private Sub Command5_Click()
  If List2.ListIndex = -1 Then Exit Sub
  If List2.ListIndex = 0 Then Exit Sub
  Dim v As Long
  v = List2.ListIndex + 1
  Dim lsi As typqpinfo
  lsi = frames(dqz).qps(v - 1)
  frames(dqz).qps(v - 1) = frames(dqz).qps(v)
  frames(dqz).qps(v) = lsi
  
  List2.Clear
  Dim n As Long
  For n = 1 To UBound(frames(dqz).qps)
    List2.AddItem frames(dqz).qps(n).Index
  Next n
  ShowFrame ShowPicture1, dqz, 1
End Sub

Private Sub Command6_Click()
  If List2.ListIndex = -1 Then Exit Sub
  If List2.ListIndex = List2.ListCount - 1 Then Exit Sub
  Dim v As Long
  v = List2.ListIndex + 1
  
  Dim lsi As typqpinfo
  lsi = frames(dqz).qps(v + 1)
  frames(dqz).qps(v + 1) = frames(dqz).qps(v)
  frames(dqz).qps(v) = lsi

  List2.Clear
  Dim n As Long
  For n = 1 To UBound(frames(dqz).qps)
    List2.AddItem frames(dqz).qps(n).Index
  Next n
  ShowFrame ShowPicture1, dqz, 1
End Sub

Private Sub Form_Load()
  If UBound(frames) <> 0 Then
    List1.Clear
    Dim n As Long
    For n = 1 To UBound(frames)
      List1.AddItem n
    Next n
  End If
  ShowPicture1.AutoRedraw = True
  ShowPicture1.ImageWidth = 0
  ShowPicture1.ImageHeight = 0
End Sub

Private Sub List1_Click()
  dqz = List1.ListIndex + 1
  Frame1.Enabled = True
  List2.Clear
  Dim n As Long
  For n = 1 To UBound(frames(dqz).qps)
    List2.AddItem frames(dqz).qps(n).Index
  Next n
  ShowFrame ShowPicture1, dqz, 0
  Label5.Caption = frames(dqz).Width
  Label6.Caption = frames(dqz).Height
End Sub

Private Sub List2_Click()
  If List2.ListIndex = -1 Then Exit Sub
  Text1.Text = frames(dqz).qps(List2.ListIndex + 1).x
  Text2.Text = frames(dqz).qps(List2.ListIndex + 1).y
End Sub

Private Sub Text1_Change()
  Text1.Text = Val(Text1.Text)
  frames(dqz).qps(List2.ListIndex + 1).x = Text1.Text
  RefreshFrameWH dqz
End Sub

Private Sub Text2_Change()
  Text2.Text = Val(Text2.Text)
  frames(dqz).qps(List2.ListIndex + 1).y = Text2.Text
  RefreshFrameWH dqz
End Sub

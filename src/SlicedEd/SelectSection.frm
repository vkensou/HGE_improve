VERSION 5.00
Begin VB.Form SelectSection 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "选择切片"
   ClientHeight    =   3165
   ClientLeft      =   45
   ClientTop       =   375
   ClientWidth     =   4560
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
   ScaleHeight     =   3165
   ScaleWidth      =   4560
   StartUpPosition =   1  'CenterOwner
   Begin SlicedEd.ShowPicture ShowPicture1 
      Height          =   2460
      Left            =   1140
      TabIndex        =   3
      Top             =   150
      Width           =   3270
      _ExtentX        =   5768
      _ExtentY        =   4339
   End
   Begin VB.CommandButton Command2 
      Caption         =   "取消"
      Height          =   375
      Left            =   3615
      TabIndex        =   2
      Top             =   2685
      Width           =   825
   End
   Begin VB.CommandButton Command1 
      Caption         =   "确定"
      Height          =   375
      Left            =   2625
      TabIndex        =   1
      Top             =   2685
      Width           =   825
   End
   Begin VB.ListBox List1 
      Height          =   2460
      Left            =   120
      TabIndex        =   0
      Top             =   150
      Width           =   885
   End
End
Attribute VB_Name = "SelectSection"
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
  For n = 1 To UBound(qps)
    List1.AddItem n
  Next n
  ShowPicture1.AutoRedraw = True
  Exit Sub
t:
End Sub


Private Sub List1_Click()
  If List1.ListIndex = -1 Then Exit Sub
  Dim x As Long: x = List1.ListIndex + 1
  ShowQp ShowPicture1, x, 0
  'ShowPicture1.Cls
  'ShowPicture1.ImageWidth = qps(X).qpv.Right + 1
  'ShowPicture1.ImageHeight = qps(X).qpv.Bottom + 1
  'FreeImage_PaintTransparent ShowPicture1.hDC, qphb2, 0, 0, ShowPicture1.ImageWidth, ShowPicture1.ImageHeight, qps(X).mbd.X, qps(X).mbd.Y, ShowPicture1.ImageWidth, ShowPicture1.ImageHeight
  'ShowPicture1.Refresh
  
  'FreeImage_PaintTransparent ShowPicture1.hDC, qphb, 0, 0, ShowPicture1.ImageWidth, ShowPicture1.ImageHeight, qps(X).mbd.X, qps(X).mbd.Y, ShowPicture1.ImageWidth, ShowPicture1.ImageHeight
  'ShowPicture1.AutoRedraw = True
  'BitBlt ShowPicture1.hDC, 0, 0, ShowPicture1.ImageWidth, ShowPicture1.ImageHeight, qphb, qps(X).mbd.X, qps(X).mbd.Y, vbSrcCopy
  'Set ShowPicture1.Picture = ShowPicture1.Image
  'ShowPicture1.AutoRedraw = False
End Sub

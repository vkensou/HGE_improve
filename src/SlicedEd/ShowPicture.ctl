VERSION 5.00
Begin VB.UserControl ShowPicture 
   ClientHeight    =   2220
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   3315
   ScaleHeight     =   148
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   221
   Begin VB.VScrollBar Scroll1 
      Height          =   1950
      Left            =   3000
      TabIndex        =   3
      Top             =   -15
      Visible         =   0   'False
      Width           =   300
   End
   Begin VB.HScrollBar Scroll2 
      Height          =   300
      Left            =   -45
      TabIndex        =   2
      Top             =   1890
      Visible         =   0   'False
      Width           =   2985
   End
   Begin VB.PictureBox PicBack 
      BorderStyle     =   0  'None
      Height          =   1815
      Left            =   45
      ScaleHeight     =   121
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   193
      TabIndex        =   0
      Top             =   0
      Width           =   2895
      Begin VB.PictureBox PicShow 
         AutoSize        =   -1  'True
         BackColor       =   &H00FFFFFF&
         BorderStyle     =   0  'None
         Height          =   1290
         Left            =   0
         ScaleHeight     =   86
         ScaleMode       =   3  'Pixel
         ScaleWidth      =   79
         TabIndex        =   1
         Top             =   0
         Width           =   1185
      End
   End
End
Attribute VB_Name = "ShowPicture"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Public Event MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
Public Event MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
Public Event MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
Public Event Click()
Public Event Paint()

Public Pic As PictureBox

Private Sub PicShow_Click()
  RaiseEvent Click
End Sub

Private Sub PicShow_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
  RaiseEvent MouseDown(Button, Shift, X, Y)
End Sub

Private Sub PicShow_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
  RaiseEvent MouseMove(Button, Shift, X, Y)
End Sub

Private Sub PicShow_MouseUp(Button As Integer, Shift As Integer, X As Single, Y As Single)
  RaiseEvent MouseUp(Button, Shift, X, Y)
End Sub

Private Sub PicShow_Paint()
  RaiseEvent Paint
End Sub

Private Sub UserControl_Initialize()
  Call InitPic(True)
  Set Pic = PicShow
End Sub

Private Sub UserControl_InitProperties()
  UserControl_Resize
  Call InitPic(True)
End Sub

Private Sub UserControl_Resize()
  With PicBack
   .Left = 0
   .Top = 0
   .Height = UserControl.ScaleHeight
   .Width = UserControl.ScaleWidth
  End With
  With Scroll1
   .Top = 0
   .Left = UserControl.ScaleWidth - 20
   .Width = 20
   .Height = UserControl.ScaleHeight
  End With
  With Scroll2
   .Top = UserControl.ScaleHeight - 20
   .Left = 0
   .Width = IIf(Scroll1.Left > 0, Scroll1.Left, 0)
   .Height = 20
  End With
  SetScroll
End Sub





Public Property Set Picture(aa As StdPicture)
  Call InitPic(True)
  Set PicShow.Picture = aa
  Call LoadPic
End Property
Public Property Get Picture() As StdPicture
  Set Picture = PicShow.Picture
End Property
Public Property Get hDC() As Long
  hDC = PicShow.hDC
End Property
Public Property Get ImageWidth() As Long
  If Not PicShow.Picture Is Nothing Then ImageWidth = PicShow.ScaleWidth
End Property
Public Property Let ImageWidth(ByVal aa As Long)
  PicShow.Width = aa
  SetScroll
End Property
Public Property Get ImageHeight() As Long
  If Not PicShow.Picture Is Nothing Then ImageHeight = PicShow.ScaleHeight
End Property
Public Property Let ImageHeight(ByVal aa As Long)
  PicShow.Height = aa
  SetScroll
End Property
Public Property Let AutoRedraw(ByVal aa As Boolean)
  PicShow.AutoRedraw = aa
End Property
Public Property Get AutoRedraw() As Boolean
  AutoRedraw = PicShow.AutoRedraw
End Property
Public Property Get Image() As StdPicture
  Set Image = PicShow.Image
End Property


Public Sub Cls(Optional ByVal Q As Boolean = False)
  InitPic Q
End Sub
Public Sub Refresh()
  PicShow.Refresh
End Sub

Private Sub InitPic(Optional ByVal Q As Boolean = False)
  With PicShow
    .Cls
    If Q = True Then
      Set .Picture = Nothing
      .Left = 0
      .Top = 0
      .Width = 0
      .Height = 0
      Scroll1.Visible = False
      Scroll2.Visible = False
      Scroll1.Value = 0
      Scroll2.Value = 0
    End If
  End With
End Sub
Private Sub LoadPic()
  SetScroll
End Sub
Private Sub Scroll1_Change()                                 '¹ö¶¯Ìõ²Ù×÷
  PicShow.Top = -Scroll1.Value
End Sub
Private Sub Scroll1_Scroll()
  PicShow.Top = -Scroll1.Value
End Sub
Private Sub Scroll2_Change()
  PicShow.Left = -Scroll2.Value
End Sub
Private Sub Scroll2_Scroll()
  PicShow.Left = -Scroll2.Value
End Sub

Private Sub SetScroll()
  Dim H As Boolean, W As Boolean
  W = PicShow.Width > PicBack.Width
  H = PicShow.Height > PicBack.Height
  
  Scroll1.Visible = False
  Scroll2.Visible = False
  If Not (W Or H) Then
    PicShow.Left = 0
    PicShow.Top = 0
  Else
    If W Then If PicShow.Height > UserControl.ScaleHeight - 20 Then H = True
    If H Then If PicShow.Width > UserControl.ScaleWidth - 20 Then W = True
    If W Then
      PicBack.Height = UserControl.ScaleHeight - 20
      Scroll2.Max = PicShow.Width - PicBack.Width: Scroll2.Min = 0
      Scroll2.SmallChange = IIf(Scroll2.Max * 0.1 < 1, 1, Scroll2.Max * 0.1)
      Scroll2.LargeChange = IIf(Scroll2.Max * 0.2 < 1, 1, Scroll2.Max * 0.2)
      Scroll2.Value = 0
      Scroll2.Width = IIf(H, UserControl.ScaleWidth - 20, UserControl.ScaleWidth)
      Scroll2.Visible = True
    End If
    If H Then
      PicBack.Width = UserControl.ScaleWidth - 20
      Scroll1.Max = PicShow.Height - PicBack.Height: Scroll1.Min = 0
      Scroll1.SmallChange = IIf(Scroll1.Max * 0.1 < 1, 1, Scroll1.Max * 0.1)
      Scroll1.LargeChange = IIf(Scroll1.Max * 0.2 < 1, 1, Scroll1.Max * 0.2)
      Scroll2.Value = 0
      Scroll1.Height = IIf(W, UserControl.ScaleHeight - 20, UserControl.ScaleHeight)
      Scroll1.Visible = True
    End If
  End If
End Sub

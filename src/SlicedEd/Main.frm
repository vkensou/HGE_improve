VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "comdlg32.ocx"
Begin VB.Form Main 
   Caption         =   "切片动画编辑器"
   ClientHeight    =   6960
   ClientLeft      =   225
   ClientTop       =   555
   ClientWidth     =   8970
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
   ScaleHeight     =   464
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   598
   StartUpPosition =   2  'CenterScreen
   Begin SlicedEd.ShowPicture ShowPicture1 
      Height          =   3285
      Left            =   1620
      TabIndex        =   2
      Top             =   60
      Width           =   3825
      _ExtentX        =   6747
      _ExtentY        =   5794
   End
   Begin VB.ListBox List1 
      Height          =   2460
      Left            =   -15
      TabIndex        =   1
      Top             =   -15
      Width           =   1500
   End
   Begin MSComDlg.CommonDialog CD1 
      Left            =   8100
      Top             =   3030
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.Label Label1 
      Height          =   240
      Left            =   30
      TabIndex        =   0
      Top             =   6675
      Width           =   720
   End
   Begin VB.Menu m_file 
      Caption         =   "文件"
      Begin VB.Menu m_Open 
         Caption         =   "打开图片"
      End
      Begin VB.Menu m_save 
         Caption         =   "保存图片"
      End
      Begin VB.Menu m_close 
         Caption         =   "关闭图片"
      End
      Begin VB.Menu m_OpenF 
         Caption         =   "打开帧信息"
      End
      Begin VB.Menu m_savef 
         Caption         =   "保存帧信息"
      End
   End
   Begin VB.Menu m_do 
      Caption         =   "图片处理"
      Begin VB.Menu m_recover 
         Caption         =   "恢复原图"
      End
      Begin VB.Menu m_colorrepalce 
         Caption         =   "颜色替换"
      End
      Begin VB.Menu m_zoom 
         Caption         =   "图片缩放"
      End
      Begin VB.Menu m_cut 
         Caption         =   "图片修剪"
      End
      Begin VB.Menu m_compare 
         Caption         =   "图片比较不同"
      End
      Begin VB.Menu m_compare2 
         Caption         =   "图片比较相同"
      End
      Begin VB.Menu m_combine 
         Caption         =   "图片合并"
         Visible         =   0   'False
      End
   End
   Begin VB.Menu m_picinfo 
      Caption         =   "图片信息"
   End
   Begin VB.Menu m_section 
      Caption         =   "切片"
      Begin VB.Menu m_AddSection 
         Caption         =   "新增切片"
      End
      Begin VB.Menu m_RapidAdd 
         Caption         =   "快速增加切片"
      End
      Begin VB.Menu m_DelSection 
         Caption         =   "删除切片"
      End
      Begin VB.Menu m_MaxSection 
         Caption         =   "切片扩至最大"
      End
      Begin VB.Menu m_CutSection 
         Caption         =   "切片修剪"
      End
      Begin VB.Menu m_CutSection2 
         Caption         =   "切片修剪2"
      End
      Begin VB.Menu m_MergeSection 
         Caption         =   "切片合并"
      End
   End
   Begin VB.Menu m_frame 
      Caption         =   "帧"
      Begin VB.Menu m_SectionEdit 
         Caption         =   "切片编辑"
      End
      Begin VB.Menu m_frameedit 
         Caption         =   "帧编辑器"
      End
      Begin VB.Menu m_MVEdit 
         Caption         =   "动画编辑器"
      End
   End
End
Attribute VB_Name = "Main"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Public scy As Boolean
Private Graphics As Long
Private dqx As Long, dqy As Long
Private dqcolor As Long, dqcr As Byte, dqcg As Byte, dqcb As Byte, dqca As Byte
Private gz As Long  '临时工作图片
Private smode As Long
Private picmode As Long

Private Sub Form_Load()
  FreeImage_Initialise
  Call Form_Resize
  ReDim Images(0)
  'ReDim ytm(0), yt2(0), ytw(0), yth(0)
  'ReDim dq2(0), dqw(0), dqh(0), qp(0)
  
  ReDim qps(0)
  ReDim frames(0)
  ReDim frames(0).qps(0)
  ReDim MVs(0)
  ReDim MVs(0).frames(0)
  ShowPicture1.AutoRedraw = True
  ShowPicture1.Pic.ScaleMode = 3
End Sub

Private Sub Form_Resize()
  With Label1
    .Left = 0
    .Width = IIf(Me.ScaleWidth = 0, 800, Me.ScaleWidth)
    .Height = 16
    .Top = IIf(Me.ScaleHeight = 0, 600, Me.ScaleHeight) - .Height
  End With
  With List1
    List1.Left = 0
    List1.Top = 0
    List1.Height = Label1.Top
    List1.Width = 100
  End With
  With ShowPicture1
    .Left = 100
    .Top = 0
    .Height = Label1.Top
    .Width = IIf(Me.ScaleWidth = 0, 800, Me.ScaleWidth) - 100
  End With
End Sub

Private Sub Form_Unload(Cancel As Integer)
  Dim n As Long
  For n = 1 To UBound(Images)
    FreeImage_Unload Images(n).OriBit.Bitmap
    FreeImage_Unload Images(n).CurBit.Bitmap
  Next n
  
  FreeImage_DeInitialise
End Sub

Private Sub List1_Click()
  dqIndex = List1.ListIndex + 1
  qpIndex = 0
  smode = 0
  ShowImage dqIndex
  ShowQp dqIndex
End Sub

Private Sub m_AddSection_Click()
  If List1.ListIndex = -1 Then Exit Sub
  Dim ubd As Long
  ubd = UBound(Images(dqIndex).qp) + 1
  ReDim Preserve Images(dqIndex).qp(ubd)
  With Images(dqIndex).qp(ubd)
    .Left = 0
    .Top = 0
    .Right = Images(dqIndex).CurBit.Width - 1
    .Bottom = Images(dqIndex).CurBit.Height - 1
  End With
  ShowQp dqIndex
  hg = False
End Sub

Private Sub m_close_Click()
  If List1.ListIndex = -1 Then Exit Sub
  Dim n As Long, Q As Long, ubd As Long
  Q = List1.ListIndex + 1
  FreeImage_Unload Images(Q).OriBit.Bitmap
  FreeImage_Unload Images(Q).CurBit.Bitmap
  List1.RemoveItem List1.ListIndex
  If Q = UBound(Images) Then
    ubd = UBound(Images) - 1
    ReDim Preserve Images(ubd)
    'ReDim Preserve ytm(ubd), ytw(ubd), yth(ubd), yt2(ubd) ', yt(ubd)
    'ReDim Preserve dqw(ubd), dqh(ubd), qp(ubd), mt(ubd), dq2(ubd) 'dq(ubd)
    dqIndex = ubd
  Else
    ubd = UBound(Images) - 1
    For n = Q To ubd
      Images(n) = Images(n + 1)
      'ytm(n) = ytm(n + 1)
      'yt2(n) = yt2(n + 1)
      'ytw(n) = ytw(n + 1)
      'yth(n) = yth(n + 1)
      'dqw(n) = dqw(n + 1)
      'dqh(n) = dqh(n + 1)
      'qp(n) = qp(n + 1)
      'dq2(n) = dq2(n + 1)
    Next n
    ReDim Preserve Images(ubd)
    'ReDim Preserve ytm(ubd), yt2(ubd), ytw(ubd), yth(ubd)
    'ReDim Preserve dq2(ubd), dqw(ubd), dqh(ubd), mt(ubd)
    
    List1.ListIndex = Q - 1
  End If
  If ubd = 0 Then
    ShowImage 0
  ElseIf UBound(Images) < Q Then
    List1.ListIndex = Q - 2
  Else
    List1.ListIndex = Q - 1
  End If
  hg = False
End Sub

Private Sub m_colorrepalce_Click()
  If Images(dqIndex).CurBit.Width = 0 Or Images(dqIndex).CurBit.Height = 0 Then Exit Sub
On Error GoTo kk
  Dim th As Long
  CD1.CancelError = True
  CD1.ShowColor
  th = CD1.Color
  If th = dqcolor Then Exit Sub
  
  Form2.Show
  Form2.Caption = "正在替换颜色..."
  Form2.Refresh

  Dim n As Long, m As Long, p2 As Long, P3 As Long, n2 As Integer, m2 As Integer
  Dim th1 As Long
  For m = 0 To Images(dqIndex).CurBit.Height - 1
    For n = 0 To Images(dqIndex).CurBit.Width - 1
      FreeImage_GetPixelColorByLong Images(dqIndex).CurBit.Bitmap, n, m, P3
      If P3 = dqcolor Then
        FreeImage_SetPixelColorByLong Images(dqIndex).CurBit.Bitmap, n, m, th1
      End If
      DoEvents
    Next n
    Form2.pgrbar.Value = 100 * m / (Images(dqIndex).CurBit.Height - 1)
  Next m
  Unload Form2
  ShowImage dqIndex
  
kk:
End Sub

Private Sub m_compare_Click()
  If List1.ListIndex = -1 Then Exit Sub
  If UBound(Images) < 2 Then Exit Sub
  PicCompare.Show 1
  If PicCompare.List1.ListIndex = -1 Then Unload PicCompare: Exit Sub
  Dim mb As Long
  If PicCompare.List1.ListIndex + 1 < dqIndex Then
    mb = PicCompare.List1.ListIndex + 1
  Else
    mb = PicCompare.List1.ListIndex + 2
  End If
  Dim n As Long, m As Long
  Dim c1 As RGBQUAD, c2 As RGBQUAD
  For m = 0 To Images(dqIndex).CurBit.Height - 1
    For n = 0 To Images(dqIndex).CurBit.Width - 1
      FreeImage_GetPixelColor Images(dqIndex).CurBit.Bitmap, n, Images(dqIndex).CurBit.Height - m - 1, c1
      FreeImage_GetPixelColor Images(mb).CurBit.Bitmap, n, Images(dqIndex).CurBit.Height - m - 1, c2
      Images(dqIndex).mt(n, m) = (Not (c1.rgbReserved = 0 And c2.rgbReserved = 0)) And (c1.rgbRed <> c2.rgbRed Or c1.rgbGreen <> c2.rgbGreen Or c1.rgbBlue <> c2.rgbBlue Or c1.rgbReserved <> c2.rgbReserved)
    Next n
  Next m
  Unload PicCompare
  ShowImage dqIndex
  ShowQp dqIndex
End Sub
Private Sub m_compare2_Click()
  If List1.ListIndex = -1 Then Exit Sub
  If UBound(Images) < 2 Then Exit Sub
  PicCompare.Show 1
  If PicCompare.List1.ListIndex = -1 Then Unload PicCompare: Exit Sub
  Dim mb As Long
  If PicCompare.List1.ListIndex + 1 < dqIndex Then
    mb = PicCompare.List1.ListIndex + 1
  Else
    mb = PicCompare.List1.ListIndex + 2
  End If
  Dim n As Long, m As Long
  Dim c1 As RGBQUAD, c2 As RGBQUAD
  For m = 0 To Images(dqIndex).CurBit.Height - 1
    For n = 0 To Images(dqIndex).CurBit.Width - 1
      FreeImage_GetPixelColor Images(dqIndex).CurBit.Bitmap, n, Images(dqIndex).CurBit.Height - m - 1, c1
      FreeImage_GetPixelColor Images(mb).CurBit.Bitmap, n, Images(dqIndex).CurBit.Height - m - 1, c2
      Images(dqIndex).mt(n, m) = Not (c1.rgbReserved = 0 And c2.rgbReserved = 0) And c1.rgbRed = c2.rgbRed And c1.rgbGreen = c2.rgbGreen And c1.rgbBlue = c2.rgbBlue And c1.rgbReserved = c2.rgbReserved
    Next n
  Next m
  Unload PicCompare
  ShowImage dqIndex
  ShowQp dqIndex
End Sub

Private Sub m_cut_Click()
  If Images(dqIndex).CurBit.Width = 0 Or Images(dqIndex).CurBit.Height = 0 Then Exit Sub
  PicCut.Show 1
  If PicCut.hy = True Then
    Dim cutrect As RECTF, cutcolor As Long
    Dim n As Long, m As Long
    If PicCut.Option1(0).Value Then
      cutcolor = PicCut.Picture1.BackColor
    ElseIf PicCut.Option1(1).Value Then
      FreeImage_GetPixelColorByLong Images(dqIndex).CurBit.Bitmap, 0, Images(dqIndex).CurBit.Height - 1, cutcolor
    ElseIf PicCut.Option1(2).Value Then
      FreeImage_GetPixelColorByLong Images(dqIndex).CurBit.Bitmap, Images(dqIndex).CurBit.Width - 1, Images(dqIndex).CurBit.Height - 1, cutcolor
    ElseIf PicCut.Option1(3).Value Then
      FreeImage_GetPixelColorByLong Images(dqIndex).CurBit.Bitmap, 0, 0, cutcolor
    ElseIf PicCut.Option1(4).Value Then
      FreeImage_GetPixelColorByLong Images(dqIndex).CurBit.Bitmap, Images(dqIndex).CurBit.Width - 1, 0, cutcolor
    End If
    With cutrect
      .Left = 0: .Top = 0: .Right = Images(dqIndex).CurBit.Width - 1: .Bottom = Images(dqIndex).CurBit.Height - 1
    End With
    Dim s As Long
    If PicCut.Check1(0) = 1 Then
      For m = cutrect.Top To cutrect.Bottom
        For n = cutrect.Left To cutrect.Right
          FreeImage_GetPixelColorByLong Images(dqIndex).CurBit.Bitmap, n, Images(dqIndex).CurBit.Height - 1 - m, s
          If s <> cutcolor And s <> -1 Then cutrect.Top = m: GoTo d1
        Next n
      Next m
    End If
d1:
    If PicCut.Check1(1) = 1 Then
      For n = cutrect.Left To cutrect.Right
        For m = cutrect.Top To cutrect.Bottom
          FreeImage_GetPixelColorByLong Images(dqIndex).CurBit.Bitmap, n, Images(dqIndex).CurBit.Height - 1 - m, s
          If s <> cutcolor And s <> -1 Then cutrect.Left = n: GoTo d2
        Next m
      Next n
    End If
d2:
    
    If PicCut.Check1(2) = 1 Then
      For m = cutrect.Bottom To cutrect.Top Step -1
        For n = cutrect.Left To cutrect.Right
          FreeImage_GetPixelColorByLong Images(dqIndex).CurBit.Bitmap, n, Images(dqIndex).CurBit.Height - 1 - m, s
          If s <> cutcolor And s <> -1 Then cutrect.Bottom = m: GoTo d3
        Next n
      Next m
    End If
d3:
    
    
    If PicCut.Check1(3) = 1 Then
      For n = cutrect.Right To cutrect.Left Step -1
        For m = cutrect.Top To cutrect.Bottom
          FreeImage_GetPixelColorByLong Images(dqIndex).CurBit.Bitmap, n, Images(dqIndex).CurBit.Height - 1 - m, s
          If s <> cutcolor And s <> -1 Then cutrect.Right = n: GoTo d4
        Next m
      Next n
    End If
d4:
    
    Images(dqIndex).CurBit.Width = cutrect.Right - cutrect.Left + 1
    Images(dqIndex).CurBit.Height = cutrect.Bottom - cutrect.Top + 1
    Dim lsv As Long
    lsv = FreeImage_Copy(Images(dqIndex).CurBit.Bitmap, cutrect.Left, cutrect.Top, Images(dqIndex).CurBit.Width, Images(dqIndex).CurBit.Height)
    FreeImage_Unload Images(dqIndex).CurBit.Bitmap
    Images(dqIndex).CurBit.Bitmap = lsv
    ShowImage dqIndex
    Label1.Caption = "图片宽：" & Images(dqIndex).CurBit.Width & "," & "高：" & Images(dqIndex).CurBit.Height
    Dim ls() As Boolean
    ReDim ls(cutrect.Right - cutrect.Left, cutrect.Bottom - cutrect.Top)
    For m = 0 To Images(dqIndex).CurBit.Height - 1
      For n = 0 To Images(dqIndex).CurBit.Width - 1
        ls(n, m) = Images(dqIndex).mt(cutrect.Left + n, cutrect.Top + m)
      Next n
    Next m
    ReDim Images(dqIndex).mt(cutrect.Right - cutrect.Left, cutrect.Bottom - cutrect.Top)
    Images(dqIndex).mt = ls
  End If
  Unload PicCut
  hg = False
End Sub

Private Sub m_CutSection_Click()
  If List1.ListIndex = -1 Then Exit Sub
  Dim ubd As Long
  ubd = UBound(Images(dqIndex).qp)
  If ubd = 0 Then Exit Sub
  Dim n As Long, m As Long, i As Long
  On Error Resume Next
  For i = 1 To ubd
    If Images(dqIndex).qp(i).Left < 0 Then Images(dqIndex).qp(i).Left = 0
    If Images(dqIndex).qp(i).Top < 0 Then Images(dqIndex).qp(i).Top = 0
    If Images(dqIndex).qp(i).Right >= Images(dqIndex).CurBit.Width Then Images(dqIndex).qp(i).Right = Images(dqIndex).CurBit.Width - 1
    If Images(dqIndex).qp(i).Bottom >= Images(dqIndex).CurBit.Height Then Images(dqIndex).qp(i).Bottom = Images(dqIndex).CurBit.Height - 1
    
    For n = Images(dqIndex).qp(i).Left To Images(dqIndex).qp(i).Right
      For m = Images(dqIndex).qp(i).Top To Images(dqIndex).qp(i).Bottom
        If Images(dqIndex).mt(n, m) = True Then Images(dqIndex).qp(i).Left = n: GoTo a1
      Next m
    Next n
a1:
    For m = Images(dqIndex).qp(i).Top To Images(dqIndex).qp(i).Bottom
      For n = Images(dqIndex).qp(i).Left To Images(dqIndex).qp(i).Right
        If Images(dqIndex).mt(n, m) = True Then Images(dqIndex).qp(i).Top = m: GoTo a2
      Next n
    Next m
a2:

    For n = Images(dqIndex).qp(i).Right To Images(dqIndex).qp(i).Left Step -1
      For m = Images(dqIndex).qp(i).Top To Images(dqIndex).qp(i).Bottom
        If Images(dqIndex).mt(n, m) = True Then Images(dqIndex).qp(i).Right = n: GoTo a3
      Next m
    Next n
a3:

    For m = Images(dqIndex).qp(i).Bottom To Images(dqIndex).qp(i).Top Step -1
      For n = Images(dqIndex).qp(i).Left To Images(dqIndex).qp(i).Right
        If Images(dqIndex).mt(n, m) = True Then Images(dqIndex).qp(i).Bottom = m: GoTo a4
      Next n
    Next m
a4:

  Next i
  
  ShowQp dqIndex
  hg = False
End Sub

Private Sub m_CutSection2_Click()
  If List1.ListIndex = -1 Then Exit Sub
  Dim ubd As Long
  ubd = UBound(Images(dqIndex).qp)
  If ubd = 0 Then Exit Sub
  Dim n As Long, m As Long, i As Long
  Dim s As Long
  For i = 1 To ubd
    If Images(dqIndex).qp(i).Left < 0 Then Images(dqIndex).qp(i).Left = 0
    If Images(dqIndex).qp(i).Top < 0 Then Images(dqIndex).qp(i).Top = 0
    If Images(dqIndex).qp(i).Right >= Images(dqIndex).CurBit.Width Then Images(dqIndex).qp(i).Right = Images(dqIndex).CurBit.Width - 1
    If Images(dqIndex).qp(i).Bottom >= Images(dqIndex).CurBit.Height Then Images(dqIndex).qp(i).Bottom = Images(dqIndex).CurBit.Height - 1

    For n = Images(dqIndex).qp(i).Left To Images(dqIndex).qp(i).Right
      For m = Images(dqIndex).qp(i).Top To Images(dqIndex).qp(i).Bottom
        FreeImage_GetPixelColorByLong Images(dqIndex).CurBit.Bitmap, n, Images(dqIndex).CurBit.Height - 1 - m, s
        If s <> dqcolor And s <> -1 Then Images(dqIndex).qp(i).Left = n: GoTo a1
      Next m
    Next n
a1:
    For m = Images(dqIndex).qp(i).Top To Images(dqIndex).qp(i).Bottom
      For n = Images(dqIndex).qp(i).Left To Images(dqIndex).qp(i).Right
        FreeImage_GetPixelColorByLong Images(dqIndex).CurBit.Bitmap, n, Images(dqIndex).CurBit.Height - 1 - m, s
        If s <> dqcolor And s <> -1 Then Images(dqIndex).qp(i).Top = m: GoTo a2
      Next n
    Next m
a2:

    For n = Images(dqIndex).qp(i).Right To Images(dqIndex).qp(i).Left Step -1
      For m = Images(dqIndex).qp(i).Top To Images(dqIndex).qp(i).Bottom
        FreeImage_GetPixelColorByLong Images(dqIndex).CurBit.Bitmap, n, Images(dqIndex).CurBit.Height - 1 - m, s
        If s <> dqcolor And s <> -1 Then Images(dqIndex).qp(i).Right = n: GoTo a3
      Next m
    Next n
a3:

    For m = Images(dqIndex).qp(i).Bottom To Images(dqIndex).qp(i).Top Step -1
      For n = Images(dqIndex).qp(i).Left To Images(dqIndex).qp(i).Right
        FreeImage_GetPixelColorByLong Images(dqIndex).CurBit.Bitmap, n, Images(dqIndex).CurBit.Height - 1 - m, s
        If s <> dqcolor And s <> -1 Then Images(dqIndex).qp(i).Bottom = m: GoTo a4
      Next n
    Next m
a4:

  Next i
  
  ShowQp dqIndex
  hg = False
End Sub

Private Sub m_DelSection_Click()
  If List1.ListIndex = -1 Then Exit Sub
  Dim ubd As Long
  ubd = UBound(Images(dqIndex).qp)
  If ubd = 0 Then Exit Sub
  If qpIndex = 0 Then Exit Sub
  Dim n As Long
  ubd = ubd - 1
  For n = qpIndex To ubd
    Images(dqIndex).qp(n) = Images(dqIndex).qp(n + 1)
  Next n
  ReDim Preserve Images(dqIndex).qp(ubd)
  If qpIndex = ubd + 1 Then qpIndex = ubd
  ShowQp dqIndex
  hg = False
End Sub

Private Sub m_frameedit_Click()
  FrameEdit.Show 1
End Sub

Private Sub m_MaxSection_Click()
  If List1.ListIndex = -1 Then Exit Sub
  Dim ubd As Long
  ubd = UBound(Images(dqIndex).qp)
  If ubd = 0 Then Exit Sub
  Images(dqIndex).qp(qpIndex).Left = 0
  Images(dqIndex).qp(qpIndex).Top = 0
  Images(dqIndex).qp(qpIndex).Right = Images(dqIndex).CurBit.Width - 1
  Images(dqIndex).qp(qpIndex).Bottom = Images(dqIndex).CurBit.Height - 1
  ShowQp dqIndex
  hg = False
End Sub

Private Sub m_MergeSection_Click()
  Dim n As Long, m As Long, i As Long, a As Long
  smode = 1
  If hg = False Then
  For n = 1 To UBound(Images)
    a = a + UBound(Images(n).qp)
  Next n
  If a = 0 Then Exit Sub
  
  MsgBox "总共" & Str(a) & "个切片"
  ReDim qps(a), frames(0), MVs(0)
  i = 1
  For n = 1 To UBound(Images)
    For m = 1 To UBound(Images(n).qp)
      qps(i).bl = n
      qps(i).cx = 0: qps(i).cy = 0
      qps(i).ox = Images(n).qp(m).Left: qps(i).oy = Images(n).qp(m).Top
      qps(i).Width = Images(n).qp(m).Right - Images(n).qp(m).Left + 1
      qps(i).Height = Images(n).qp(m).Bottom - Images(n).qp(m).Top + 1
      i = i + 1
    Next m
  Next n
  'Dim v As qpt
  'For n = 1 To a
  '  For m = n + 1 To a
  '    If qps(n).Height < qps(m).Height Then
   '     v = qps(n)
   '     qps(n) = qps(m)
   '     qps(m) = v
   '   End If
   ' Next m
  'Next n
  Dim lsrs() As Block ', tw As Long, mw As Long, w2 As Long
  ReDim lsrs(UBound(qps))
  For n = 1 To UBound(qps)
    'lsrs(n) = qps(n).qpv
    lsrs(n).Width = qps(n).Width + 1
    lsrs(n).Height = qps(n).Height + 1
  Next n
  
  'w2 = tw / 2
  'If w2 < mw Then w2 = mw
  'qpw = w2
  GetBPSolution lsrs, qpw, qph
  FreeImage_Unload qphb2
  qphb2 = FreeImage_Allocate(qpw, qph, 32)
  Dim ls As Long
  For n = 1 To UBound(qps)
    qps(n).Left = lsrs(n).Left + 1: qps(n).Top = lsrs(n).Top + 1
    'Debug.Print lsrs(n).Left, lsrs(n).Top, lsrs(n).Right, lsrs(n).Bottom
    ls = FreeImage_Copy(Images(qps(n).bl).CurBit.Bitmap, qps(n).ox, qps(n).oy, qps(n).ox + qps(n).Width, qps(n).oy + qps(n).Height)
    qps(n).ox = qps(n).ox Mod Images(qps(n).bl).VP
    qps(n).oy = qps(n).oy Mod Images(qps(n).bl).HP
    qps(n).oWidth = Images(qps(n).bl).VP
    qps(n).oHeight = Images(qps(n).bl).HP
    'ls = FreeImage_Copy(dq2(qps(n).bl), qps(n).qpv.Left, qps(n).qpv.Top, qps(n).qpv.Left + qps(n).qpv.Right + 1, qps(n).qpv.Top + qps(n).qpv.Bottom + 1)
    FreeImage_Paste qphb2, ls, qps(n).Left, qps(n).Top, 255
    FreeImage_Unload ls
  Next n
  End If
  List1.ListIndex = -1
  Call ShowHb
  hg = True
End Sub
Private Sub ShowHb()
  picmode = 1
  ShowPicture1.Cls
  ShowPicture1.ImageWidth = qpw
  ShowPicture1.ImageHeight = qph
  'ShowPicture1.AutoRedraw = True
  FreeImage_PaintTransparent ShowPicture1.hDC, qphb2
  'BitBlt ShowPicture1.hDC, 0, 0, qpw, qph, qphb, 0, 0, vbSrcCopy
  ShowPicture1.Refresh
  'Set ShowPicture1.Picture = ShowPicture1.Image
  'ShowPicture1.AutoRedraw = False
End Sub

Private Sub m_MVEdit_Click()
  MVEdit.Show 1
End Sub

Private Sub m_open_Click()
  CD1.CancelError = False
  CD1.Filter = "图片文件(*.bmp;*.jpg;*.gif;*.png)|*.bmp;*.jpg;*.gif;*.png"
  CD1.ShowOpen
  If CD1.Filename = "" Then Exit Sub
  
  DrawImage CD1.Filename
  hg = False
End Sub
Private Sub DrawImage(ByVal ImagePath As String, Optional ByVal x As Long, Optional ByVal y As Long, Optional ByVal w As Long, Optional ByVal h As Long)
  Dim timage As Long
  Dim fimage As Long
  
  ShowPicture1.Cls
  Dim fif As FREE_IMAGE_FORMAT
  fif = FreeImage_GetFileType(ImagePath)
  fimage = FreeImage_Load(fif, ImagePath)
  fimage = FreeImage_ConvertColorDepth(fimage, FICF_RGB_ALPHA, True)
  FreeImage_PreMultiplyWithAlpha fimage
  w = FreeImage_GetWidth(fimage)
  h = FreeImage_GetHeight(fimage)
  ShowPicture1.ImageWidth = w
  ShowPicture1.ImageHeight = h
  FreeImage_PaintTransparent ShowPicture1.hDC, fimage
  ShowPicture1.Refresh
  Dim ubd As Long
  ubd = UBound(Images) + 1
  ReDim Preserve Images(ubd), Images(ubd).mt(w - 1, h - 1), Images(ubd).qp(0) 'qp(ubd) ', mt(ubd)
  'ReDim qp(ubd).pqr(0) ', mt(ubd).mps(w - 1, h - 1)
  Images(ubd).Filename = ltw1(ImagePath)
  With Images(ubd).OriBit
  .Bitmap = fimage
  .Width = w
  .Height = h
  End With
  With Images(ubd).CurBit
  .Bitmap = FreeImage_Clone(fimage)
  .Width = w
  .Height = h
  End With
  Images(ubd).VNum = 1: Images(ubd).HNum = 1
  Images(ubd).VP = w: Images(ubd).HP = h
  List1.AddItem Images(ubd).Filename
  List1.ListIndex = ubd - 1
  dqIndex = ubd
  dqx = 0: dqy = 0: dqcolor = 0
  Label1.Caption = "图片宽：" & Images(ubd).CurBit.Width & "," & "高：" & Images(ubd).CurBit.Height
End Sub

Private Function ShowImage(ByVal Index As Integer) As Long
  If dqIndex = 0 Then Exit Function
  picmode = 0
  ShowPicture1.Cls
  ShowPicture1.ImageWidth = Images(Index).CurBit.Width
  ShowPicture1.ImageHeight = Images(Index).CurBit.Height
  'ShowPicture1.AutoRedraw = True
  FreeImage_PaintTransparent ShowPicture1.hDC, Images(Index).CurBit.Bitmap
  'BitBlt ShowPicture1.hDC, 0, 0, dqw(Index), dqh(Index), dq(Index), 0, 0, vbSrcCopy
  ShowPicture1.Refresh
  'Set ShowPicture1.Picture = ShowPicture1.Image
  'ShowPicture1.AutoRedraw = False
  If Index <> 0 Then
    Me.Caption = "游戏图片加工软件  ——  " & List1.Text
  Else
    Me.Caption = "游戏图片加工软件"
  End If
  
End Function
Private Function ShowQp(ByVal Index As Integer) As Long
  If dqIndex = 0 Then Exit Function
  If smode <> 0 Then Exit Function
  Dim n As Long, m As Long
  ShowPicture1.Cls
  FreeImage_PaintTransparent ShowPicture1.hDC, Images(Index).CurBit.Bitmap
  For n = 1 To UBound(Images(dqIndex).qp)
    If qpIndex = n Then ShowPicture1.Pic.ForeColor = vbRed Else ShowPicture1.Pic.ForeColor = vbBlack
    With Images(dqIndex).qp(n)
    ShowPicture1.Pic.Line (.Left + 4, .Top)-(.Right - 4, .Top)
    ShowPicture1.Pic.Line (.Left, .Top + 4)-(.Left, .Bottom - 4)
    ShowPicture1.Pic.Line (.Right, .Top + 4)-(.Right, .Bottom - 4)
    ShowPicture1.Pic.Line (.Left + 4, .Bottom)-(.Right - 4, .Bottom)
    
    ShowPicture1.Pic.Line (.Left - 4, .Top - 4)-(.Left + 5, .Top - 4)
    ShowPicture1.Pic.Line (.Left - 4, .Top - 4)-(.Left - 4, .Top + 5)
    ShowPicture1.Pic.Line (.Left + 4, .Top + 4)-(.Left + 4, .Top - 4)
    ShowPicture1.Pic.Line (.Left + 4, .Top + 4)-(.Left - 4, .Top + 4)
    
    ShowPicture1.Pic.Line (.Right - 4, .Top - 4)-(.Right + 5, .Top - 4)
    ShowPicture1.Pic.Line (.Right - 4, .Top - 4)-(.Right - 4, .Top + 5)
    ShowPicture1.Pic.Line (.Right + 4, .Top + 4)-(.Right + 4, .Top - 4)
    ShowPicture1.Pic.Line (.Right + 4, .Top + 4)-(.Right - 4, .Top + 4)
    
    ShowPicture1.Pic.Line (.Left - 4, .Bottom - 4)-(.Left + 5, .Bottom - 4)
    ShowPicture1.Pic.Line (.Left - 4, .Bottom - 4)-(.Left - 4, .Bottom + 5)
    ShowPicture1.Pic.Line (.Left + 4, .Bottom + 4)-(.Left + 4, .Bottom - 4)
    ShowPicture1.Pic.Line (.Left + 4, .Bottom + 4)-(.Left - 4, .Bottom + 4)
    
    ShowPicture1.Pic.Line (.Right - 4, .Bottom - 4)-(.Right + 5, .Bottom - 4)
    ShowPicture1.Pic.Line (.Right - 4, .Bottom - 4)-(.Right - 4, .Bottom + 5)
    ShowPicture1.Pic.Line (.Right + 4, .Bottom + 4)-(.Right + 4, .Bottom - 4)
    ShowPicture1.Pic.Line (.Right + 4, .Bottom + 4)-(.Right - 4, .Bottom + 4)
    
    ShowPicture1.Pic.CurrentX = .Left + 4
    ShowPicture1.Pic.CurrentY = .Top + 4
    ShowPicture1.Pic.Print n
    End With
  Next n
  
  If Images(Index).CurBit.Width - 1 = UBound(Images(Index).mt, 1) And Images(Index).CurBit.Height - 1 = UBound(Images(Index).mt, 2) Then
    For m = 0 To Images(Index).CurBit.Height - 1
      For n = 0 To Images(Index).CurBit.Width - 1
        If Images(Index).mt(n, m) <> False Then ShowPicture1.Pic.PSet (n, m), vbGreen
      Next n
    Next m
  End If
  
End Function

Private Function ltw1(ByVal L As String) As String
  Dim k As Long, h As Long
  k = InStrRev(L, "\") + 1
  h = InStrRev(L, ".")
  ltw1 = Mid$(L, k, h - k)
End Function

Private Sub m_OpenF_Click()
  CD1.CancelError = False
  CD1.Filter = "信息文件(*.edat)|*.edat"
  CD1.ShowOpen
  If CD1.Filename = "" Then Exit Sub
  Dim bcs As String
  bcs = CD1.Filename
  bcs = Left$(bcs, Len(bcs) - 5) & ".png"
  If Dir(bcs) = "" Then Exit Sub
  
  OpenF CD1.Filename
  
  Dim fif As FREE_IMAGE_FORMAT
  FreeImage_Unload qphb2
  fif = FreeImage_GetFileType(bcs)
  qphb2 = FreeImage_Load(fif, bcs)
  qpw = FreeImage_GetWidth(qphb2)
  qph = FreeImage_GetHeight(qphb2)
  'DeleteDC qphb

  'GdiCreatehDC qphb, qpw, qph
  'GdiLoadPicture qphb, bcs, qpw, qph
  
  Call ShowHb
End Sub

Private Sub m_picinfo_Click()
  If Images(dqIndex).CurBit.Width = 0 Or Images(dqIndex).CurBit.Height = 0 Then Exit Sub
  PicInfo.Show 1
End Sub

Private Sub m_RapidAdd_Click()
  If List1.ListIndex = -1 Then Exit Sub
  Load RapidAdd
  RapidAdd.Show 1
  Dim m As Long, n As Long
  Dim v As Single, h As Single, v1 As Long, h1 As Long
  Dim ubd As Long
  v1 = RapidAdd.Text1.Text
  h1 = RapidAdd.Text2.Text
  m = RapidAdd.Text3.Text
  v = Images(dqIndex).CurBit.Width / v1
  h = Images(dqIndex).CurBit.Height / h1
  Images(dqIndex).VNum = v1: Images(dqIndex).HNum = h1
  Images(dqIndex).VP = v: Images(dqIndex).HP = h
  For n = 1 To m
    ubd = UBound(Images(dqIndex).qp) + 1
    ReDim Preserve Images(dqIndex).qp(ubd)
    With Images(dqIndex).qp(ubd)
    .Left = ((n - 1) Mod v1) * v
    .Top = ((n - 1) \ v1) * h
    .Right = .Left + v - 1
    .Bottom = .Top + h - 1
    End With
    hg = False
  Next n
  Unload RapidAdd
  ShowQp dqIndex
End Sub

Private Sub m_recover_Click()
  With Images(dqIndex)
  FreeImage_Unload .CurBit.Bitmap
  .CurBit.Width = .OriBit.Width
  .CurBit.Height = .OriBit.Height
  .CurBit.Bitmap = FreeImage_Clone(.OriBit.Bitmap)
  Images(dqIndex).VNum = 1: Images(dqIndex).HNum = 1
  Images(dqIndex).VP = .CurBit.Width: Images(dqIndex).HP = .CurBit.Height
  ReDim .mt(.OriBit.Width - 1, .OriBit.Height - 1)
  End With

  ShowImage dqIndex
  Label1.Caption = "图片宽：" & Images(dqIndex).CurBit.Width & "," & "高：" & Images(dqIndex).CurBit.Height
  hg = False
End Sub

Private Sub m_save_Click()
  If Images(dqIndex).CurBit.Width = 0 Or Images(dqIndex).CurBit.Height = 0 Then Exit Sub
On Error GoTo k
  CD1.CancelError = True
  CD1.Filter = "BMP(*.bmp)|*.bmp|PNG(*.png)|*.png"
v:
  CD1.ShowSave
  If CD1.Filename = "" Then Exit Sub
  Dim bcs As String
  bcs = CD1.Filename
  Dim a As FREE_IMAGE_FORMAT
  If CD1.FilterIndex = 0 Then
    bcs = IIf(Right$(bcs, 4) <> ".bmp", bcs & ".bmp", bcs)
    a = FIF_BMP
  Else
    bcs = IIf(Right$(bcs, 4) <> ".png", bcs & ".png", bcs)
    a = FIF_PNG
  End If
  If Dir(bcs) <> "" Then If MsgBox("文件 " & CD1.FileTitle & " 已存在。要替换它吗？", vbOKCancel) = vbCancel Then GoTo v
  'SavePicture ShowPicture1.Picture, CD1.Filename
  
  FreeImage_Save a, Images(dqIndex).CurBit.Bitmap, CD1.Filename
k:
End Sub

Private Sub m_savef_Click()
  If hg = False Then Exit Sub
On Error GoTo k
  CD1.CancelError = True
  CD1.Filter = "信息文件(*.edat)|*.edat"
v:
  CD1.ShowSave
  If CD1.Filename = "" Then Exit Sub
  Dim bcs As String
  bcs = CD1.Filename
  bcs = IIf(Right$(bcs, 5) <> ".edat", bcs & ".edat", bcs)
  If Dir(bcs) <> "" Then If MsgBox("文件 " & CD1.FileTitle & " 已存在。要替换它吗？", vbOKCancel) = vbCancel Then GoTo v
  
  ShowHb
  FreeImage_Save FIF_PNG, qphb2, Left$(bcs, Len(bcs) - 5) & ".png"
  SaveF bcs
  SaveF2 Left$(bcs, Len(bcs) - 4) & "dat"
k:
End Sub

Private Sub m_SectionEdit_Click()
  SectionEdit.Show 1
End Sub

Private Sub m_zoom_Click()
  Dim sw As Long, sh As Long, sc As Long, scy As Boolean
  If Images(dqIndex).CurBit.Width = 0 Or Images(dqIndex).CurBit.Height = 0 Then Exit Sub
  Load PicZoom
  PicZoom.Label1 = "图片宽：" & Images(dqIndex).CurBit.Width & "," & "高：" & Images(dqIndex).CurBit.Height
  PicZoom.Text1 = Images(dqIndex).CurBit.Width
  PicZoom.Text2 = Images(dqIndex).CurBit.Height
  PicZoom.Check2.Value = 1
  PicZoom.Picture1.BackColor = dqcolor
  PicZoom.Show 1
  
  If PicZoom.hy = True Then
    sw = PicZoom.Text1: sh = PicZoom.Text2: sc = PicZoom.Picture1.BackColor: scy = PicZoom.Check2.Value
    If sw <> Images(dqIndex).CurBit.Width Or sw <> Images(dqIndex).CurBit.Height Then
      Images(dqIndex).CurBit.Width = sw: Images(dqIndex).CurBit.Height = sh
      Images(dqIndex).CurBit.Bitmap = FreeImage_RescaleEx(Images(dqIndex).CurBit.Bitmap, sw, sh, False, True)
      Images(dqIndex).VNum = 1: Images(dqIndex).HNum = 1
      Images(dqIndex).VP = Images(dqIndex).CurBit.Width: Images(dqIndex).HP = Images(dqIndex).CurBit.Height

      ShowImage dqIndex
      Label1.Caption = "图片宽：" & Images(dqIndex).CurBit.Width & "," & "高：" & Images(dqIndex).CurBit.Height
    End If
  End If
  Unload PicZoom
  hg = False
  
  ReDim Images(dqIndex).mt(Images(dqIndex).CurBit.Width - 1, Images(dqIndex).CurBit.Height - 1)
End Sub

Private Sub ShowPicture1_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
  If List1.ListIndex = -1 Then Exit Sub
  If picmode = 1 Then Exit Sub
  If Button = 1 Then
  Dim ubd As Long
  ubd = UBound(Images(dqIndex).qp)
  If ubd = 0 Then Exit Sub
  
  Dim n As Long
  qpIndex = 0
  qpdrag = 0
  For n = 1 To ubd
    With Images(dqIndex).qp(n)
    If x > .Left - 4 And y > .Top - 4 And x < .Right + 4 And y < .Bottom + 4 Then
      qpIndex = n
      
      If x < .Left + 4 Then
        qpdrag = qpdrag Or 1
      ElseIf x > .Right - 4 Then
        qpdrag = qpdrag Or 4
      End If
      
      If y < .Top + 4 Then
        qpdrag = qpdrag Or 2
      ElseIf y > .Bottom - 4 Then
        qpdrag = qpdrag Or 8
      End If
      
      If qpdrag = 0 Then
        ShowPicture1.Pic.MousePointer = 5
      ElseIf (qpdrag = 1) Or (qpdrag = 4) Then
        ShowPicture1.Pic.MousePointer = 9
      ElseIf (qpdrag = 2) Or (qpdrag = 8) Then
        ShowPicture1.Pic.MousePointer = 7
      ElseIf (qpdrag = 3) Or (qpdrag = 12) Then
        ShowPicture1.Pic.MousePointer = 8
      Else
        ShowPicture1.Pic.MousePointer = 6
      End If
      qpx = x: qpy = y
      Exit For
    End If
    End With
  Next n
  ShowQp dqIndex
  End If
End Sub

Private Sub ShowPicture1_MouseMove(Button As Integer, Shift As Integer, x As Single, y As Single)
  If List1.ListIndex = -1 Then Exit Sub
  If picmode = 1 Then Exit Sub

  Label1.Caption = "图片宽：" & Images(dqIndex).CurBit.Width & "," & "高：" & Images(dqIndex).CurBit.Height & "   坐标 X：" & x & "," & "Y：" & y & "   选中颜色：" & dqcolor & ",ARGB" & dqca & "," & dqcr & "," & dqcg & "," & dqcb
  
  With Images(dqIndex).qp(qpIndex)
  If Button = 1 Then
  
    If UBound(Images(dqIndex).qp) = 0 Then Exit Sub
    If qpIndex = 0 Then Exit Sub
    If qpdrag = 0 Then
      .Left = .Left - qpx + x
      .Right = .Right - qpx + x
      .Top = .Top - qpy + y
      .Bottom = .Bottom - qpy + y
    End If
    If qpdrag And 1 Then
      .Left = .Left - qpx + x
    End If
    If qpdrag And 2 Then
      .Top = .Top - qpy + y
    End If
    If qpdrag And 4 Then
      .Right = .Right - qpx + x
    End If
    If qpdrag And 8 Then
      .Bottom = .Bottom - qpy + y
    End If
    
    qpx = x: qpy = y
    ShowQp dqIndex
    hg = False
  ElseIf Button = 0 Then
    qpdrag = 0
    If UBound(Images(dqIndex).qp) = 0 Or qpIndex = 0 Then
      ShowPicture1.Pic.MousePointer = 0
    Else
      If x > .Left - 4 And y > .Top - 4 And x < .Right + 4 And y < .Bottom + 4 Then
        If x < .Left + 4 Then
          qpdrag = qpdrag Or 1
        ElseIf x > .Right - 4 Then
          qpdrag = qpdrag Or 4
        End If
      
        If y < .Top + 4 Then
          qpdrag = qpdrag Or 2
        ElseIf y > .Bottom - 4 Then
          qpdrag = qpdrag Or 8
        End If
      
        If qpdrag = 0 Then
          ShowPicture1.Pic.MousePointer = 0
        ElseIf (qpdrag = 1) Or (qpdrag = 4) Then
          ShowPicture1.Pic.MousePointer = 9
        ElseIf (qpdrag = 2) Or (qpdrag = 8) Then
          ShowPicture1.Pic.MousePointer = 7
        ElseIf (qpdrag = 3) Or (qpdrag = 12) Then
          ShowPicture1.Pic.MousePointer = 8
        Else
          ShowPicture1.Pic.MousePointer = 6
        End If
      Else
        ShowPicture1.Pic.MousePointer = 0
      End If
    End If
  End If
  End With
End Sub

Private Sub ShowPicture1_MouseUp(Button As Integer, Shift As Integer, x As Single, y As Single)
  If List1.ListIndex = -1 Then Exit Sub
  If picmode = 1 Then Exit Sub

  dqx = x: dqy = y
  Dim dy2 As Single
  dy2 = Images(dqIndex).CurBit.Height - 1 - dqy
  'If GetPixel(dq(dqIndex), dqx, dqy) <> -1 Then dqcolor = GetPixel(dq(dqIndex), dqx, dqy)
  Dim lc As Long
  If FreeImage_GetPixelColorByLong(Images(dqIndex).CurBit.Bitmap, dqx, dy2, lc) Then dqcolor = lc
  
  FreeImage_GetPixelColorEx Images(dqIndex).CurBit.Bitmap, dqx, dy2, dqca, dqcr, dqcg, dqcb
  
  Label1.Caption = "图片宽：" & Images(dqIndex).CurBit.Width & "," & "高：" & Images(dqIndex).CurBit.Height & "   坐标 X：" & x & "," & "Y：" & y & "   选中颜色： " & dqcolor & ", ARGB" & dqca & "," & dqcr & "," & dqcg & "," & dqcb
  
  If Button = 1 Then
  If UBound(Images(dqIndex).qp) = 0 Then Exit Sub
  If qpIndex = 0 Then Exit Sub
    Dim jh As Long
    With Images(dqIndex).qp(qpIndex)
      If .Left > .Right Then
        jh = .Left
        .Left = .Right
        .Right = jh
      End If
      If .Top > .Bottom Then
        jh = .Top
        .Top = .Bottom
        .Bottom = jh
      End If
      hg = False
      
    End With
    qpdrag = 0
    qpx = 0: qpy = 0
    ShowPicture1.Pic.MousePointer = 0
    ShowQp dqIndex
  End If
End Sub

Private Sub ShowPicture1_Paint()
  If List1.ListIndex = -1 Then Exit Sub
  Call ShowQp(dqIndex)
End Sub

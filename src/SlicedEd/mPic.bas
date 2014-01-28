Attribute VB_Name = "mPic"
Public Type RECTF
        Left As Single
        Top As Single
        Right As Single
        Bottom As Single
End Type
Public Type POINTAPI
        x As Long
        y As Long
End Type

Public Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (Destination As Any, Source As Any, ByVal Length As Long)

Public Type Rects
  rectv() As RECTF
End Type

Public dqIndex As Long
Public qpIndex As Long
Public qpdrag As Long
Public qpx As Long, qpy As Long
'Public ytm() As String
'Public yt2() As Long  '原图片
'Public ytw() As Long, yth() As Long    '原图宽高
'Public dq2() As Long  '当前图片
'Public dqw() As Long, dqh() As Long    '当前宽高
'Public qp() As tqp
'Public mt() As mtp

Public Type tqp
  pqr() As RECTF
End Type
Public Type mtp
  mps() As Boolean
End Type

Public Type ImageInfo
  Bitmap As Long
  Width As Long
  Height As Long
End Type
Public Type ImageInfoE
  Filename As String
  CurBit As ImageInfo
  OriBit As ImageInfo
  mt() As Boolean
  qp() As RECTF
  '横切多少，纵切多少
  VNum As Long
  HNum As Long
  '每横格多长，每纵格多长
  VP As Single
  HP As Single
End Type
Public Images() As ImageInfoE
Public Type qpt
  bl As Long
  'qpv As RECTF
  'mbd As POINTAPI
  cx As Single
  cy As Single
  ox As Single
  oy As Single
  oWidth As Single
  oHeight As Single
  Left As Single
  Top As Single
  Width As Single
  Height As Single
End Type
Public Type typqpinfo
  Index As Long
  x As Long
  y As Long
End Type
Public Type typFrame
  Width As Single
  Height As Single
  cx As Single
  cy As Single
  'qph() As Long
  'qpwz() As POINTAPI
  qps() As typqpinfo
End Type
Public Type typFrameInfo
  Index As Long
  Time As Long
  x As Long
  y As Long
End Type
Public Type TypAnim
  Width As Single
  Height As Single
  cx As Single
  cy As Single
  frames() As typFrameInfo
  Mode As Long
End Type

'Public qphb As Long
Public qphb2 As Long, qpw As Long, qph As Long

Public a1 As Rects
Public z1 As Rects, zw As Long, zh As Long, mj As Long
Public hg As Boolean

Public qps() As qpt
Public frames() As typFrame
Public MVs() As TypAnim

Public Function SaveF(ByVal FilePath As String) As Long
  If hg = False Then Exit Function
  Dim n As Long, m As Long
  If Dir(FilePath) <> "" Then Kill FilePath
  Open FilePath For Binary As #1
    Put #1, , UBound(qps)
    Put #1, , qps
    Put #1, , UBound(frames)
    For n = 1 To UBound(frames)
      Put #1, , frames(n).cx
      Put #1, , frames(n).cy
      Put #1, , frames(n).Width
      Put #1, , frames(n).Height
      Put #1, , UBound(frames(n).qps)
      Put #1, , frames(n).qps
    Next n
    Put #1, , UBound(MVs)
    For n = 1 To UBound(MVs)
      Put #1, , MVs(n).cx
      Put #1, , MVs(n).cy
      Put #1, , MVs(n).Width
      Put #1, , MVs(n).Height
      Put #1, , UBound(MVs(n).frames)
      Put #1, , MVs(n).frames
      Put #1, , MVs(n).Mode
    Next n
  Close
End Function

Public Function SaveF2(ByVal FilePath As String) As Long
  If hg = False Then Exit Function
  Dim n As Long, m As Long
  If Dir(FilePath) <> "" Then Kill FilePath
  Open FilePath For Binary As #1
    Put #1, , UBound(qps)
    For n = 1 To UBound(qps)
      Put #1, , qps(n).cx
      Put #1, , qps(n).cy
      Put #1, , qps(n).Left
      Put #1, , qps(n).Top
      Put #1, , qps(n).Width
      Put #1, , qps(n).Height
    Next n
    Put #1, , UBound(frames)
    For n = 1 To UBound(frames)
      Put #1, , UBound(frames(n).qps)
      For m = 1 To UBound(frames(n).qps)
        Put #1, , frames(n).qps(m).Index
        Put #1, , frames(n).qps(m).x
        Put #1, , frames(n).qps(m).y
      Next m
    Next n
    Put #1, , UBound(MVs)
    For n = 1 To UBound(MVs)
      Put #1, , UBound(MVs(n).frames)
      For m = 1 To UBound(MVs(n).frames)
        Put #1, , MVs(n).frames(m).Index
        Put #1, , MVs(n).frames(m).Time
        Put #1, , MVs(n).frames(m).x
        Put #1, , MVs(n).frames(m).y
      Next m
      Put #1, , MVs(n).Mode
    Next n
  Close
End Function


Public Function OpenF(ByVal FilePath As String) As Long
  If Dir(FilePath) = "" Then Exit Function
  Dim n As Long, m As Long, r As Long
  
  ReDim qps(0)
  ReDim frames(0)
  ReDim frames(0).qps(0)
  ReDim MVs(0)
  ReDim MVs(0).frames(0)

  
  Open FilePath For Binary As #1
    Get #1, , r
    ReDim qps(r)
    Get #1, , qps
    Get #1, , r
    ReDim frames(r)
    For n = 1 To r
      Get #1, , frames(n).cx
      Get #1, , frames(n).cy
      Get #1, , frames(n).Width
      Get #1, , frames(n).Height
      Get #1, , r
      ReDim frames(n).qps(r)
      Get #1, , frames(n).qps
    Next n
    Get #1, , r
    ReDim MVs(r)
    For n = 1 To r
      Get #1, , MVs(n).cx
      Get #1, , MVs(n).cy
      Get #1, , MVs(n).Width
      Get #1, , MVs(n).Height
      Get #1, , r
      ReDim MVs(n).frames(r)
      Get #1, , MVs(n).frames
      Get #1, , MVs(n).Mode
    Next n
    hg = True
  Close
End Function

Function ShowQp(ByRef sp As ShowPicture, Index As Long, flag As Long) As Long
  If Index = -1 Then Exit Function
  'If flag = 0 Then
    sp.ImageWidth = qps(Index).Width
    sp.ImageHeight = qps(Index).Height
    sp.Cls
  'End If
  FreeImage_PaintTransparent sp.hDC, qphb2, 0, 0, sp.ImageWidth, sp.ImageHeight, qps(Index).Left, qps(Index).Top, sp.ImageWidth, sp.ImageHeight
  If flag = 1 Then
    sp.Pic.ForeColor = vbRed
    sp.Pic.Line (qps(Index).cx - 4, qps(Index).cy)-(qps(Index).cx + 4, qps(Index).cy)
    sp.Pic.Line (qps(Index).cx, qps(Index).cy - 4)-(qps(Index).cx, qps(Index).cy + 4)
  End If
  'If flag = 0 Then
  sp.Refresh
End Function

Function ShowFrame(ByRef sp As ShowPicture, Index As Long, Optional flag As Long = 0, Optional ByRef x As Variant, Optional ByRef y As Single = 0) As Long
  If Index = 0 Then Exit Function
  If flag = 0 Then
  sp.ImageWidth = frames(Index).Width
  sp.ImageHeight = frames(Index).Height
  End If
  sp.Cls
  Dim n As Long
  For n = 1 To UBound(frames(Index).qps)
    If IsMissing(x) Then
    FreeImage_PaintTransparent sp.hDC, qphb2, frames(Index).cx + frames(Index).qps(n).x - qps(frames(Index).qps(n).Index).cx, frames(Index).cy + frames(Index).qps(n).y - qps(frames(Index).qps(n).Index).cy _
      , 0, 0, qps(frames(Index).qps(n).Index).Left, qps(frames(Index).qps(n).Index).Top, qps(frames(Index).qps(n).Index).Width, qps(frames(Index).qps(n).Index).Height
    Else
    FreeImage_PaintTransparent sp.hDC, qphb2, x + frames(Index).qps(n).x - qps(frames(Index).qps(n).Index).cx, y + frames(Index).qps(n).y - qps(frames(Index).qps(n).Index).cy _
      , 0, 0, qps(frames(Index).qps(n).Index).Left, qps(frames(Index).qps(n).Index).Top, qps(frames(Index).qps(n).Index).Width, qps(frames(Index).qps(n).Index).Height
    End If
  Next n
  sp.Refresh
End Function

Function RefreshFrameWH(Index As Long) As Long
  Dim n As Long, x1 As Long, x2 As Long, y1 As Long, y2 As Long, x3 As Long, y3 As Long
  If UBound(frames(Index).qps) = 0 Then
    frames(Index).Width = 0
    frames(Index).Height = 0
    frames(Index).cx = 0
    frames(Index).cy = 0
    Exit Function
  End If
  x1 = frames(Index).qps(1).x - qps(frames(Index).qps(1).Index).cx
  y1 = frames(Index).qps(1).y - qps(frames(Index).qps(1).Index).cy
  x3 = qps(frames(Index).qps(1).Index).cx - frames(Index).qps(1).x
  y3 = qps(frames(Index).qps(1).Index).cy - frames(Index).qps(1).y
  x2 = frames(Index).qps(1).x - qps(frames(Index).qps(1).Index).cx + qps(frames(Index).qps(1).Index).Width - 1
  y2 = frames(Index).qps(1).y - qps(frames(Index).qps(1).Index).cy + qps(frames(Index).qps(1).Index).Height - 1
  For n = 2 To UBound(frames(Index).qps)
    If frames(Index).qps(n).x - qps(frames(Index).qps(n).Index).cx < x1 Then
      x1 = frames(Index).qps(n).x - qps(frames(Index).qps(n).Index).cx
      x3 = qps(frames(Index).qps(n).Index).cx - frames(Index).qps(n).x
    End If
    If frames(Index).qps(n).y - qps(frames(Index).qps(n).Index).cy < y1 Then
      y1 = frames(Index).qps(n).y - qps(frames(Index).qps(n).Index).cy
      y3 = qps(frames(Index).qps(n).Index).cy - frames(Index).qps(n).y
    End If
    If frames(Index).qps(n).x - qps(frames(Index).qps(n).Index).cx + qps(frames(Index).qps(n).Index).Width - 1 > x2 Then _
      x2 = frames(Index).qps(n).x - qps(frames(Index).qps(n).Index).cx + qps(frames(Index).qps(n).Index).Width - 1
    If frames(Index).qps(n).y - qps(frames(Index).qps(n).Index).cy + qps(frames(Index).qps(n).Index).Height - 1 > y2 Then _
      y2 = frames(Index).qps(n).y - qps(frames(Index).qps(n).Index).cy + qps(frames(Index).qps(n).Index).Height - 1
  Next n
  frames(Index).cx = x3
  frames(Index).cy = y3
  frames(Index).Width = x2 - x1 + 1
  frames(Index).Height = y2 - y1 + 1
End Function


Function RefreshMVWH(Index As Long) As Long
  Dim n As Long, x1 As Long, x2 As Long, y1 As Long, y2 As Long, x3 As Long, y3 As Long
  If UBound(MVs(Index).frames) = 0 Then
    MVs(Index).Width = 0
    MVs(Index).Height = 0
    MVs(Index).cx = 0
    MVs(Index).cy = 0
    Exit Function
  End If
  x1 = -frames(MVs(Index).frames(1).Index).cx
  y1 = -frames(MVs(Index).frames(1).Index).cy
  x3 = frames(MVs(Index).frames(1).Index).cx
  y3 = frames(MVs(Index).frames(1).Index).cy
  x2 = -frames(MVs(Index).frames(1).Index).cx + frames(MVs(Index).frames(1).Index).Width - 1
  y2 = -frames(MVs(Index).frames(1).Index).cy + frames(MVs(Index).frames(1).Index).Height - 1
  For n = 2 To UBound(MVs(Index).frames)
    If -frames(MVs(Index).frames(n).Index).cx < x1 Then
      x1 = -frames(MVs(Index).frames(n).Index).cx
      x3 = frames(MVs(Index).frames(n).Index).cx
    End If
    If -frames(MVs(Index).frames(n).Index).cy < y1 Then
      y1 = -frames(MVs(Index).frames(n).Index).cy
      y3 = frames(MVs(Index).frames(n).Index).cy
    End If
    If -frames(MVs(Index).frames(n).Index).cx + frames(MVs(Index).frames(n).Index).Width - 1 > x2 Then _
      x2 = -frames(MVs(Index).frames(n).Index).cx + frames(MVs(Index).frames(n).Index).Width - 1
    If -frames(MVs(Index).frames(n).Index).cy + frames(MVs(Index).frames(n).Index).Height - 1 > y2 Then _
      y2 = -frames(MVs(Index).frames(n).Index).cy + frames(MVs(Index).frames(n).Index).Height - 1
  Next n
  MVs(Index).cx = x3
  MVs(Index).cy = y3
  MVs(Index).Width = x2 - x1 + 1
  MVs(Index).Height = y2 - y1 + 1
End Function

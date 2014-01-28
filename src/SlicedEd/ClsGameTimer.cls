VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "ClsGameTimer"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Private Declare Function GetTickCount Lib "kernel32" () As Long

Dim JZTick As Long
Dim TempTick As Long
Dim NowTick1 As Long
Dim YanChi As Long
Dim YanChiA As Long
'计时器是否启动
Dim UTick As Boolean
'计时器是否暂停
Dim ZT As Boolean
Dim ZtTime As Long
Public Jc As Object

Private Sub Class_Initialize()
  InitTick
  'Set Jc = Main.m_VBGameEngine
End Sub

Public Function InitTick()
  JZTick = 0
  TempTick = 0
  NowTick1 = 0
  YanChi = 0
  YanChiA = 0
  UTick = False
  ZT = True
  ZtTime = 0
End Function
Public Function StartTick()
  InitTick
  JZTick = GetTickCount
  UTick = True
  ZT = False
End Function
Public Function PauseTick()
  If UTick = True Then
    If ZT = False Then
      ZtTime = NowTick
      YanChiA = GetTickCount
      ZT = True
    End If
  End If
End Function
Public Function GoonTick()
  If UTick = True Then
    If ZT = True Then
      TempTick = GetTickCount
      YanChi = TempTick - YanChiA + YanChi
      ZT = False
    End If
  End If
End Function
Public Function StopTick()
  InitTick
End Function
Public Function NowTick() As Long
  If UTick = False Then Exit Function
  If ZT = False Then
    TempTick = GetTickCount
    NowTick1 = TempTick - JZTick - YanChi
    NowTick = NowTick1
  Else
    NowTick = ZtTime
  End If
End Function
Public Function SetTick(ByVal aa As Long) As Long
  If UTick = False Then Exit Function
  If ZT = False Then
    TempTick = GetTickCount
    YanChi = TempTick - JZTick - aa
  Else
    GoonTick
    SetTick aa
    PauseTick
  End If
End Function

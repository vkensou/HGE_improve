VERSION 5.00
Begin VB.Form PicInfo 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "图片信息"
   ClientHeight    =   3030
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
   LinkTopic       =   "Form3"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3030
   ScaleWidth      =   4560
   StartUpPosition =   1  'CenterOwner
   Begin VB.CommandButton Command1 
      Caption         =   "确定"
      Height          =   450
      Left            =   3345
      TabIndex        =   8
      Top             =   2490
      Width           =   1080
   End
   Begin VB.Frame Frame2 
      Caption         =   "切片信息（在原图位置）"
      Height          =   1125
      Left            =   135
      TabIndex        =   3
      Top             =   1275
      Width           =   4290
      Begin VB.Label Label6 
         AutoSize        =   -1  'True
         Caption         =   "Y2:300"
         Height          =   240
         Left            =   2085
         TabIndex        =   7
         Top             =   705
         Width           =   720
      End
      Begin VB.Label Label5 
         AutoSize        =   -1  'True
         Caption         =   "X2：100"
         Height          =   240
         Left            =   420
         TabIndex        =   6
         Top             =   705
         Width           =   840
      End
      Begin VB.Label Label4 
         AutoSize        =   -1  'True
         Caption         =   "Y1：0"
         Height          =   240
         Left            =   2085
         TabIndex        =   5
         Top             =   300
         Width           =   600
      End
      Begin VB.Label Label3 
         AutoSize        =   -1  'True
         Caption         =   "X1：50"
         Height          =   240
         Left            =   420
         TabIndex        =   4
         Top             =   300
         Width           =   720
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "图片信息"
      Height          =   900
      Left            =   135
      TabIndex        =   0
      Top             =   180
      Width           =   4290
      Begin VB.Label Label2 
         AutoSize        =   -1  'True
         Caption         =   "高：600"
         Height          =   240
         Left            =   2115
         TabIndex        =   2
         Top             =   405
         Width           =   840
      End
      Begin VB.Label Label1 
         AutoSize        =   -1  'True
         Caption         =   "宽：800"
         Height          =   240
         Left            =   330
         TabIndex        =   1
         Top             =   405
         Width           =   840
      End
   End
End
Attribute VB_Name = "PicInfo"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
  Unload Me
End Sub

Private Sub Form_Load()
  Label1.Caption = "宽：" & Images(dqIndex).CurBit.Width
  Label2.Caption = "高：" & Images(dqIndex).CurBit.Height
  'Label3.Caption = "X1：" & qp(dqIndex).Left
  'Label4.Caption = "Y1：" & qp(dqIndex).Top
  'Label5.Caption = "X2：" & qp(dqIndex).Right
  'Label6.Caption = "Y2：" & qp(dqIndex).Bottom
End Sub

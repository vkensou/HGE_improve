// AnimEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "AnimationEd.h"
#include "AnimEdit.h"
#include "globaldata_animall.h"

// CAnimEdit 对话框

IMPLEMENT_DYNAMIC(CAnimEdit, CDialog)

CAnimEdit::CAnimEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CAnimEdit::IDD, pParent)
	, fnum(0)
	, sfps(0)
{

}

CAnimEdit::~CAnimEdit()
{
}

void CAnimEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, fnum);
	DDX_Text(pDX, IDC_EDIT2, sfps);
}


BEGIN_MESSAGE_MAP(CAnimEdit, CDialog)
	ON_BN_CLICKED(IDOK, &CAnimEdit::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CAnimEdit::OnBnClickedCancel)
END_MESSAGE_MAP()


// CAnimEdit 消息处理程序

void CAnimEdit::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	OnOK();
}

void CAnimEdit::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}

BOOL CAnimEdit::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	fnum = nowskt->GetFrameNum();
	sfps = nowskt->GetFps();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

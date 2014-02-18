// AnimEdit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AnimationEd.h"
#include "AnimEdit.h"
#include "globaldata_animall.h"

// CAnimEdit �Ի���

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


// CAnimEdit ��Ϣ�������

void CAnimEdit::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	OnOK();
}

void CAnimEdit::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}

BOOL CAnimEdit::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	fnum = nowskt->GetFrameNum();
	sfps = nowskt->GetFps();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

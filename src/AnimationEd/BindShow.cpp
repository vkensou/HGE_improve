// BindShow.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AnimationEd.h"
#include "BindShow.h"
#include "hge.h"
#include "showslicedpicture.h"
#include "showslicedframe.h"
#include "showslicedanimation.h"
#include "globaldata_animall.h"

// CBindShow �Ի���

IMPLEMENT_DYNAMIC(CBindShow, CDialog)

CBindShow::CBindShow(CWnd* pParent /*=NULL*/)
	: CDialog(CBindShow::IDD, pParent)
	, bonename(_T(""))
	, filename(_T(""))
	, picname(_T(""))
{
}

CBindShow::~CBindShow()
{
}

void CBindShow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BONENAME, bonename);
	DDX_Text(pDX, IDC_FILENAME, filename);
	DDX_Control(pDX, IDC_COMBO1, cbindex);
	DDX_Text(pDX, IDC_PICNAME, picname);
}


BEGIN_MESSAGE_MAP(CBindShow, CDialog)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON2, &CBindShow::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CBindShow::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CBindShow::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON3, &CBindShow::OnBnClickedButton3)
END_MESSAGE_MAP()


// CBindShow ��Ϣ�������

BOOL CBindShow::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//cbbindtype.AddString(L"��");
	//cbbindtype.AddString(L"PICTURE");
	//cbbindtype.AddString(L"SLICEDPICTURE");
	//cbbindtype.AddString(L"SLICEDFRAME");
	//cbbindtype.AddString(L"FRAMEANIMATION");
	//cbbindtype.AddString(L"SLICEDANIMATION");
	//cbbindtype.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CBindShow::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: �ڴ˴������Ϣ����������

}

void CBindShow::ResfreshData(int index)
{
	if(index == -1)
		bonename = L"δѡ��";
	else
		bonename.Format(L"��ͷ%d",index);
	UpdateData(FALSE);
}

void CBindShow::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
    CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, L"ͼƬ��Ϣ�ļ�(*.dat)|*.dat", NULL);

    if (dlgFile.DoModal())
	{
		UpdateData(TRUE);
        filename = dlgFile.GetFileName();
		dat->LoadData(dlgFile.GetPathName());
		cbindex.ResetContent();
		CString k;
		for(UINT i = 0 ;i < dat->slices.size();i++)
		{
			k.Format(L"%d",i+1);
			cbindex.AddString(k);
		}
	}
	UpdateData(FALSE);
}

void CBindShow::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
    CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, L"ͼƬ�ļ�(*.png)|*.png", NULL);

    if (dlgFile.DoModal())
	{
		UpdateData(TRUE);
		picname = dlgFile.GetFileName();
		if(dat->tex)hge->Texture_Free(dat->tex);
		dat->tex = hge->Texture_Load(dlgFile.GetPathName());
	}
	UpdateData(FALSE);
}


void CBindShow::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!hotbone)return ;
	if(hotbone->BindPoint().part)
		delete hotbone->BindPoint().part;
	//switch (bindtype)
	//{
	//case SLICEDPICTURE:
	//	{
			hotbone->BindPoint().part = new SlicedPicture();
			SlicedPicture* p = (SlicedPicture*)hotbone->bind.part;
			p->SetPictureData(dat);
			p->SetSliceIndex(cbindex.GetCurSel()+1);
	//		break;
	//	}
	//case SLICEDFRAME:
	//	{
	//		SlicedFrame* p = (SlicedFrame*)hotbone->bind.part;
	//		p->SetPictureData(dat);
	//		p->SetFrameIndex(cbindex.GetCurSel()+1);
	//		break;
	//	}
	//case SLICEDANIMATION:
	//	{
	//		SlicedAnimation* p = (SlicedAnimation*)hotbone->bind.part;
	//		p->SetPictureData(dat);
	//		p->SetAnimationIndex(cbindex.GetCurSel()+1);
	//		break;
	//	}
	//}
	if(hotbone->BindPoint().part)
	{
		hotbone->BindPoint().part->SetPosition(hotbone->BindPoint().GetX(),hotbone->BindPoint().GetY());
		hotbone->BindPoint().part->SetRotation(hotbone->GetRotate() + hotbone->BindPoint().GetRotation());
		hotbone->BindPoint().part->SetScale(hotbone->BindPoint().GetHScale(),hotbone->BindPoint().GetVScale());
	}
}

void CBindShow::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//switch (bindtype)
	//{
	//case 0:
	//	
	//}
}


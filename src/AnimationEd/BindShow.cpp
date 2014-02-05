// BindShow.cpp : 实现文件
//

#include "stdafx.h"
#include "AnimationEd.h"
#include "BindShow.h"
#include "hge.h"
#include "showslicedpicture.h"
#include "showslicedframe.h"
#include "showslicedanimation.h"
#include "globaldata_animall.h"

// CBindShow 对话框

IMPLEMENT_DYNAMIC(CBindShow, CDialog)

CBindShow::CBindShow(CWnd* pParent /*=NULL*/)
	: CDialog(CBindShow::IDD, pParent)
	, bindtype(0)
	, bonename(_T(""))
	, filename(_T(""))
{
	tempdata = 0;
}

CBindShow::~CBindShow()
{
	delete tempdata;
}

void CBindShow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO1, bindtype);
	DDX_Control(pDX, IDC_COMBO1, cbbindtype);
	DDX_Text(pDX, IDC_BONENAME, bonename);
	DDX_Text(pDX, IDC_FILENAME, filename);
	DDX_Control(pDX, IDC_COMBO2, cbindex);
}


BEGIN_MESSAGE_MAP(CBindShow, CDialog)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON2, &CBindShow::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CBindShow::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CBindShow::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CBindShow 消息处理程序

BOOL CBindShow::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	cbbindtype.AddString(L"无");
	cbbindtype.AddString(L"PICTURE");
	cbbindtype.AddString(L"SLICEDPICTURE");
	cbbindtype.AddString(L"SLICEDFRAME");
	cbbindtype.AddString(L"FRAMEANIMATION");
	cbbindtype.AddString(L"SLICEDANIMATION");
	cbbindtype.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CBindShow::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码

}

void CBindShow::ResfreshData(int index)
{
	if(index == -1)
		bonename = L"未选择";
	else
		bonename.Format(L"骨头%d",index);
	UpdateData(FALSE);
}

void CBindShow::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strFile = L"";

    CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, L"图片信息文件(*.dat)|*.dat", NULL);

    if (dlgFile.DoModal())
	{
		UpdateData(TRUE);
        filename = dlgFile.GetFileName();

		wchar_t path_buffer[_MAX_PATH];
		wchar_t drive[_MAX_DRIVE];
		wchar_t dir[_MAX_DIR];
		wchar_t fname[_MAX_FNAME];
		wchar_t ext[_MAX_EXT];
		_wsplitpath(dlgFile.GetPathName(),drive,dir,fname,ext);
		_wmakepath( path_buffer, drive, dir, fname, L"png" );
		picfile = path_buffer;
		tempdata = new PictureData();
		tempdata->LoadData(dlgFile.GetPathName());
		cbindex.ResetContent();
		int s=0;
		switch (bindtype)
		{
		case 2:
			s = tempdata->slices.size();
			break;
		case 3:
			s = tempdata->frames.size();
			break;
		case 5:
			s = tempdata->animations.size();
			break;
		}
		CString k;
		for(int i = 0 ;i < s;i++)
		{
			k.Format(L"%d",i+1);
			cbindex.AddString(k);
		}
	}
	UpdateData(FALSE);
}
void CBindShow::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!hotbone)return ;
	HGE* hge = hgeCreate(HGE_VERSION);
	tempdata->tex = hge->Texture_Load(picfile);
	switch (bindtype)
	{
	case SLICEDPICTURE:
		{
			hotbone->bind.part = new SlicedPicture();
			SlicedPicture* p = (SlicedPicture*)hotbone->bind.part;
			p->SetPictureData(tempdata);
			p->SetSliceIndex(cbindex.GetCurSel()+1);
			break;
		}
	case SLICEDFRAME:
		{
			SlicedFrame* p = (SlicedFrame*)hotbone->bind.part;
			p->SetPictureData(tempdata);
			p->SetFrameIndex(cbindex.GetCurSel()+1);
			break;
		}
	case SLICEDANIMATION:
		{
			SlicedAnimation* p = (SlicedAnimation*)hotbone->bind.part;
			p->SetPictureData(tempdata);
			p->SetAnimationIndex(cbindex.GetCurSel()+1);
			break;
		}
	}
	if(hotbone->BindPoint().part)
	{
		hotbone->BindPoint().part->SetPosition(hotbone->BindPoint().GetX(),hotbone->BindPoint().GetY());
		hotbone->BindPoint().part->SetRotation(hotbone->GetRotate() + hotbone->BindPoint().GetRotation());
		hotbone->BindPoint().part->SetScale(hotbone->BindPoint().GetHScale(),hotbone->BindPoint().GetVScale());
	}
	hge->Release();
}

void CBindShow::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	//switch (bindtype)
	//{
	//case 0:
	//	
	//}
}

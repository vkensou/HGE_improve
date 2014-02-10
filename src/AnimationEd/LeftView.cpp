// LeftView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AnimationEd.h"
#include "LeftView.h"
#include "globaldata_view.h"

// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CFormView)

CLeftView::CLeftView()
	: CFormView(CLeftView::IDD)
{

}

CLeftView::~CLeftView()
{
}

void CLeftView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, bonelist);
	DDX_Control(pDX, IDC_BUTTON1, btop);
	DDX_Control(pDX, IDC_BUTTON2, bup);
	DDX_Control(pDX, IDC_BUTTON3, bdown);
	DDX_Control(pDX, IDC_BUTTON4, bbottom);
}

BEGIN_MESSAGE_MAP(CLeftView, CFormView)
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_LBN_SELCHANGE(IDC_LIST1, &CLeftView::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDC_BUTTON1, &CLeftView::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CLeftView::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CLeftView::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CLeftView::OnBnClickedButton4)
END_MESSAGE_MAP()


// CLeftView ���

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CLeftView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CLeftView ��Ϣ�������

void CLeftView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	CRect rect;
	GetClientRect(&rect); // ��ȡ��ǰ�ͻ���view��С
	CSize size;
	size.cx = rect.right - rect.left;
	size.cy = rect.bottom - rect.top;
	SetScrollSizes(MM_HIMETRIC, size); // ��CScrollView�Ĵ�С����Ϊ��ǰ�ͻ�����С
	//bonelist.MoveWindow(0,0,10,10);
	//jointlist.MoveWindow(rect.Width()/2,0,rect.Width()/2,rect.Height());
	if(btop)
	{
		cy = (cx /4 - 32)/2;
		btop.MoveWindow(0 + cy,0,32,32);
		bup.MoveWindow(cx /4 + cy,0,32,32);
		bdown.MoveWindow(cx/2 + cy,0,32,32);
		bbottom.MoveWindow(cx * 3/4 + cy,0,32,32);
	}
	rect.top = 32;
	//rect.bottom -= 32;
	if(rect.bottom <0)
		rect.bottom = 0;
	if(bonelist)
		bonelist.MoveWindow(rect);
}

void CLeftView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	CRect rect;
	GetClientRect(&rect); // ��ȡ��ǰ�ͻ���view��С
	int cx = rect.right ,cy = rect.bottom ;
	rect.top = 32;
	bonelist.MoveWindow(rect);
		cy = (cx /4 - 32)/2;
		btop.MoveWindow(0 + cy,0,32,32);
		bup.MoveWindow(cx /4 + cy,0,32,32);
		bdown.MoveWindow(cx/2 + cy,0,32,32);
		bbottom.MoveWindow(cx * 3/4 + cy,0,32,32);

	// TODO: �ڴ����ר�ô����/����û���
}

void CLeftView::OnSetFocus(CWnd* pOldWnd)
{
	CFormView::OnSetFocus(pOldWnd);

	// TODO: �ڴ˴������Ϣ����������
	
	CMenu* pMainMenu = AfxGetMainWnd()->GetMenu();
	if (pMainMenu != NULL)
	{
		CMenu* pSubMenu = pMainMenu->GetSubMenu(4);//start from 0
		MENUITEMINFO MenuItemInfo;
		MenuItemInfo.cbSize = sizeof(MENUITEMINFO);
		MenuItemInfo.fState = MFS_ENABLED;
		pSubMenu->SetMenuItemInfo(4, &MenuItemInfo, TRUE);//start from 0

		pSubMenu = pMainMenu->GetSubMenu(5);//start from 0
		MenuItemInfo.fState = MFS_DISABLED;
		pSubMenu->SetMenuItemInfo(5, &MenuItemInfo, TRUE);//start from 0
	}
	hotbone=0;
	CString a;
	if(bonelist.GetCount()>0 && bonelist.GetCurSel()>-1)
	{
		bonelist.GetText(bonelist.GetCurSel(),a);
		SelectBone(_ttoi(a));
	}
	else
		SelectBone(-1);


}

int CLeftView::RefreshBoneList()
{
	bonelist.ResetContent();
	CString ss;
	std::list<hgeBone*>::iterator itor;
	hgeBone* vv;
	for(itor = nowskt->bones.begin();itor != nowskt->bones.end();itor++)
	{
		vv = *itor;
		ss.Format(L"%d",vv->GetID() );
		bonelist.AddString(ss);
	}
	return nowskt->bones.size();
}

void CLeftView::SetIndex(int index)
{
	if(index>-1)
	{
		CString a1;
		for(int i = 0;i<bonelist.GetCount();i++)
		{
			bonelist.GetText(i,a1);
			if(index == _ttoi(a1))
			{
				bonelist.SetCurSel(i);
				break;
			}
		}
	}
	else
		bonelist.SetCurSel(-1);
}

void CLeftView::OnLbnSelchangeList1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	mode = 0;
	CString a;
	if(bonelist.GetCount()>0 && bonelist.GetCurSel()>-1)
	{
		bonelist.GetText(bonelist.GetCurSel(),a);
		SelectBone(_ttoi(a));
	}
	else
		SelectBone(-1);

}

void CLeftView::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	nowskt->BoneTop(hotbone);
	this->RefreshBoneList();
	SetIndex(hotbone->GetID());
}

void CLeftView::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	nowskt->BoneUp(hotbone);
	this->RefreshBoneList();
	SetIndex(hotbone->GetID());
}

void CLeftView::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	nowskt->BoneDown(hotbone);
	this->RefreshBoneList();
	SetIndex(hotbone->GetID());
}

void CLeftView::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	nowskt->BoneBottom(hotbone);
	this->RefreshBoneList();
	SetIndex(hotbone->GetID());
}

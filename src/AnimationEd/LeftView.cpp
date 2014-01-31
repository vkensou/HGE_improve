// LeftView.cpp : 实现文件
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
}

BEGIN_MESSAGE_MAP(CLeftView, CFormView)
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_LBN_SELCHANGE(IDC_LIST1, &CLeftView::OnLbnSelchangeList1)
END_MESSAGE_MAP()


// CLeftView 诊断

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


// CLeftView 消息处理程序

void CLeftView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect rect;
	GetClientRect(&rect); // 获取当前客户区view大小
	CSize size;
	size.cx = rect.right - rect.left;
	size.cy = rect.bottom - rect.top;
	SetScrollSizes(MM_HIMETRIC, size); // 将CScrollView的大小设置为当前客户区大小
	if(bonelist)
		bonelist.MoveWindow(rect);
	//bonelist.MoveWindow(0,0,10,10);
	//jointlist.MoveWindow(rect.Width()/2,0,rect.Width()/2,rect.Height());

}

void CLeftView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	CRect rect;
	GetClientRect(&rect); // 获取当前客户区view大小
	bonelist.MoveWindow(rect);
	// TODO: 在此添加专用代码和/或调用基类
}

void CLeftView::OnSetFocus(CWnd* pOldWnd)
{
	CFormView::OnSetFocus(pOldWnd);

	// TODO: 在此处添加消息处理程序代码
	
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
	SelectBone(bonelist.GetCurSel());
}

int CLeftView::RefreshBoneList()
{
	UINT m = bonelist.GetCount();
	if(m>bones.size())
	{
		for(UINT i = 0;i<m-bones.size();i++)
			bonelist.DeleteString(bonelist.GetCount()-1);
	}
	else if(m<bones.size())
	{
		CString l;
		for(UINT i = 0;i<bones.size()-m;i++)
		{
			l.Format(L"%d",bonelist.GetCount());
			bonelist.AddString(l);
		}
	}
	return bones.size();
}

void CLeftView::SetIndex(int index)
{
	if(index < -1 || index >= (int)bones.size())return ;
	bonelist.SetCurSel(index);
}

void CLeftView::OnLbnSelchangeList1()
{
	// TODO: 在此添加控件通知处理程序代码
	mode = 0;
	SelectBone(bonelist.GetCurSel());
}

// LeftView2.cpp : 实现文件
//

#include "stdafx.h"
#include "AnimationEd.h"
#include "LeftView2.h"
#include "globaldata_view.h"

// CLeftView2

IMPLEMENT_DYNCREATE(CLeftView2, CFormView)

CLeftView2::CLeftView2()
	: CFormView(CLeftView2::IDD)
{

}

CLeftView2::~CLeftView2()
{
}

void CLeftView2::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, jointlist);
}

BEGIN_MESSAGE_MAP(CLeftView2, CFormView)
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()


// CLeftView2 诊断

#ifdef _DEBUG
void CLeftView2::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CLeftView2::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CLeftView2 消息处理程序

void CLeftView2::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect rect;
	GetClientRect(&rect); // 获取当前客户区view大小
	CSize size;
	size.cx = rect.right - rect.left;
	size.cy = rect.bottom - rect.top;
	SetScrollSizes(MM_HIMETRIC, size); // 将CScrollView的大小设置为当前客户区大小
	if(jointlist)
		jointlist.MoveWindow(rect);
}

void CLeftView2::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	CRect rect;
	GetClientRect(&rect); // 获取当前客户区view大小
	jointlist.MoveWindow(rect);
}

void CLeftView2::OnSetFocus(CWnd* pOldWnd)
{
	CFormView::OnSetFocus(pOldWnd);

	// TODO: 在此处添加消息处理程序代码
	CMenu* pMainMenu = AfxGetMainWnd()->GetMenu();
	if (pMainMenu != NULL && pMainMenu->GetMenuItemCount() >= 5)
	{
		CMenu* pSubMenu = pMainMenu->GetSubMenu(5);//start from 0
		MENUITEMINFO MenuItemInfo;
		MenuItemInfo.cbSize = sizeof(MENUITEMINFO);
		MenuItemInfo.fState = MFS_ENABLED;
		pSubMenu->SetMenuItemInfo(5, &MenuItemInfo, TRUE);//start from 0

		pSubMenu = pMainMenu->GetSubMenu(4);//start from 0
		MenuItemInfo.fState = MFS_DISABLED;
		pSubMenu->SetMenuItemInfo(4, &MenuItemInfo, TRUE);//start from 0
	}

}

int CLeftView2::RefreshJointList()
{
	if(hotbone==0)return 0;
	jointlist.ResetContent();
	CString cont;
	cont = L"头结点";
	jointlist.AddString(cont);
	cont = L"尾结点";
	jointlist.AddString(cont);
	cont = L"绑定结点";
	jointlist.AddString(cont);
	cont = L"控制结点";
	jointlist.AddString(cont);
	return 0;
}
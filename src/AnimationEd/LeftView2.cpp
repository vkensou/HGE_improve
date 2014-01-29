// LeftView2.cpp : ʵ���ļ�
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


// CLeftView2 ���

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


// CLeftView2 ��Ϣ�������

void CLeftView2::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	CRect rect;
	GetClientRect(&rect); // ��ȡ��ǰ�ͻ���view��С
	CSize size;
	size.cx = rect.right - rect.left;
	size.cy = rect.bottom - rect.top;
	SetScrollSizes(MM_HIMETRIC, size); // ��CScrollView�Ĵ�С����Ϊ��ǰ�ͻ�����С
	if(jointlist)
		jointlist.MoveWindow(rect);
}

void CLeftView2::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	CRect rect;
	GetClientRect(&rect); // ��ȡ��ǰ�ͻ���view��С
	jointlist.MoveWindow(rect);
}

void CLeftView2::OnSetFocus(CWnd* pOldWnd)
{
	CFormView::OnSetFocus(pOldWnd);

	// TODO: �ڴ˴������Ϣ����������
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
	cont = L"ͷ���";
	jointlist.AddString(cont);
	cont = L"β���";
	jointlist.AddString(cont);
	cont = L"�󶨽��";
	jointlist.AddString(cont);
	cont = L"���ƽ��";
	jointlist.AddString(cont);
	return 0;
}
// RightView.cpp : 实现文件
//

#include "stdafx.h"
#include "AnimationEd.h"
#include "RightView.h"


// CRightView

IMPLEMENT_DYNCREATE(CRightView, CFormView)

CRightView::CRightView()
	: CFormView(CRightView::IDD)
{

}

CRightView::~CRightView()
{
}

void CRightView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRightView, CFormView)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CRightView 诊断

#ifdef _DEBUG
void CRightView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CRightView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CRightView 消息处理程序

void CRightView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect rect;
	GetClientRect(&rect); // 获取当前客户区view大小
	CSize size;
	size.cx = rect.right - rect.left;
	size.cy = rect.bottom - rect.top;
	SetScrollSizes(MM_HIMETRIC, size); // 将CScrollView的大小设置为当前客户区大小
}

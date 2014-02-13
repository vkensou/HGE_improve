// DownView.cpp : 实现文件
//

#include "stdafx.h"
#include "AnimationEd.h"
#include "DownView.h"
#include "globaldata_animall.h"
#include "globaldata_view.h"


// CDownView

IMPLEMENT_DYNCREATE(CDownView, CFormView)

CDownView::CDownView()
	: CFormView(CDownView::IDD)
{

}

CDownView::~CDownView()
{
}

void CDownView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, slider);
}

BEGIN_MESSAGE_MAP(CDownView, CFormView)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDownView 诊断

#ifdef _DEBUG
void CDownView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDownView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDownView 消息处理程序

void CDownView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect rect;
	GetClientRect(&rect); // 获取当前客户区view大小
	CSize size;
	size.cx = rect.right - rect.left;
	size.cy = rect.bottom - rect.top;
	SetScrollSizes(MM_HIMETRIC, size); // 将CScrollView的大小设置为当前客户区大小

	if(slider)
	{
		slider.MoveWindow(0,(cy - 50)/2,cx,50);
	}
}

void CDownView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	// TODO: 在此添加专用代码和/或调用基类
	CRect rect;
	GetClientRect(&rect); // 获取当前客户区view大小
	slider.MoveWindow(0,(rect.Height() - 50)/2,rect.Width(),50);
	RefreshData();
}

void CDownView::RefreshData()
{
	if(editmode)
	{
		slider.SetRangeMin(0);
		slider.SetRangeMax(0);
	}
	else
	{
		if(nowskt->framesnum>0)
		{
			slider.SetRangeMin(1);
			slider.SetRangeMax(nowskt->framesnum);
		}
		else
		{
			slider.SetRangeMin(0);
			slider.SetRangeMax(0);
		}
	}
}
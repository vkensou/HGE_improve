// DownView.cpp : ʵ���ļ�
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


// CDownView ���

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


// CDownView ��Ϣ�������

void CDownView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	CRect rect;
	GetClientRect(&rect); // ��ȡ��ǰ�ͻ���view��С
	CSize size;
	size.cx = rect.right - rect.left;
	size.cy = rect.bottom - rect.top;
	SetScrollSizes(MM_HIMETRIC, size); // ��CScrollView�Ĵ�С����Ϊ��ǰ�ͻ�����С

	if(slider)
	{
		slider.MoveWindow(0,(cy - 50)/2,cx,50);
	}
}

void CDownView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	// TODO: �ڴ����ר�ô����/����û���
	CRect rect;
	GetClientRect(&rect); // ��ȡ��ǰ�ͻ���view��С
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
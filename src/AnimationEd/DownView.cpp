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
	, animidx(0)
{

}

CDownView::~CDownView()
{
}

void CDownView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, slider);
	DDX_LBIndex(pDX, IDC_LIST1, animidx);
	DDX_Control(pDX, IDC_LIST1, lbanim);
	DDX_Control(pDX, IDC_BUTTON1, bplay);
	DDX_Control(pDX, IDC_BUTTON2, bstop);
}

BEGIN_MESSAGE_MAP(CDownView, CFormView)
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_LBN_SELCHANGE(IDC_LIST1, &CDownView::OnLbnSelchangeList1)
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

	if(lbanim)
	{
		lbanim.MoveWindow(0,0,130,cy);
		slider.MoveWindow(130,(cy - 50)/2,cx-130,50);
		bplay.MoveWindow(132,0,60,40);
		bstop.MoveWindow(192,0,60,40);
	}
}

void CDownView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	// TODO: �ڴ����ר�ô����/����û���
	CRect rect;
	GetClientRect(&rect); // ��ȡ��ǰ�ͻ���view��С
	lbanim.MoveWindow(0,0,130,rect.Height());
	slider.MoveWindow(130,(rect.Height() - 50)/2,rect.Width()-130,50);
	bplay.MoveWindow(132,0,60,40);
	bstop.MoveWindow(192,0,60,40);
	RefreshData();
}

void CDownView::RefreshData(int idx)
{
	lbanim.ResetContent();
	if(editmode)
	{
		slider.SetRangeMin(0);
		slider.SetRangeMax(0);
		bplay.SetWindowTextW(L"����");
		bplay.EnableWindow(false);
		bstop.EnableWindow(false);
	}
	else
	{
		CString l;
		for(int i = 0;i<nowskt->anims.size();i++)
		{
			l.Format(L"%d",i+1);
			lbanim.AddString(l);
		}
		if(nowskt->anims.size()>0)
		{
			if(idx > -1)
			{
				lbanim.SetCurSel(idx);
				nowskt->SetAnimIndex(idx);
			}
			else
			{
				lbanim.SetCurSel(0);
				nowskt->SetAnimIndex(0);
			}
		}
		if(nowskt->GetFrameNum()>0)
		{
			slider.SetRangeMin(1);
			slider.SetRangeMax(nowskt->GetFrameNum());
			nowskt->SetFrameIndex(0);
			bplay.SetWindowTextW(L"����");
			bplay.EnableWindow(true);
			bstop.EnableWindow(false);
		}
		else
		{
			slider.SetRangeMin(0);
			slider.SetRangeMax(0);
			bplay.SetWindowTextW(L"����");
			bplay.EnableWindow(false);
			bstop.EnableWindow(false);
		}
	}
}

void CDownView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CFormView::OnHScroll(nSBCode, nPos, pScrollBar);
	if(editmode)return;
	int v;
	v = slider.GetPos();
	nowskt->SetFrameIndex(v-1);
	nowskt->SetPosition(0,0);
	g_rightview->RefreshProperty();
}

void CDownView::OnLbnSelchangeList1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(editmode)return;
	nowskt->SetAnimIndex(lbanim.GetCurSel());
	if(nowskt->GetFrameNum()>0)
	{
		slider.SetRangeMin(1);
		slider.SetRangeMax(nowskt->GetFrameNum());
		nowskt->SetFrameIndex(0);
		nowskt->SetPosition(0,0);
		bplay.SetWindowTextW(L"����");
		bplay.EnableWindow(true);
		bstop.EnableWindow(false);
	}
	else
	{
		slider.SetRangeMin(0);
		slider.SetRangeMax(0);
		bplay.SetWindowTextW(L"����");
		bplay.EnableWindow(false);
		bstop.EnableWindow(false);
	}
}

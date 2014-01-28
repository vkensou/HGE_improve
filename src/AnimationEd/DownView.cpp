// DownView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AnimationEd.h"
#include "DownView.h"


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
}

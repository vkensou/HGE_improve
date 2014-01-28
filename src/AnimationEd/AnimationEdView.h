
// AnimationEdView.h : CAnimationEdView ��Ľӿ�
//


#pragma once
#include "animationeddoc.h"

class CAnimationEdView : public CView
{
protected: // �������л�����
	CAnimationEdView();
	DECLARE_DYNCREATE(CAnimationEdView)

// ����
public:
	CAnimationEdDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CAnimationEdView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // AnimationEdView.cpp �еĵ��԰汾
inline CAnimationEdDoc* CAnimationEdView::GetDocument() const
   { return reinterpret_cast<CAnimationEdDoc*>(m_pDocument); }
#endif


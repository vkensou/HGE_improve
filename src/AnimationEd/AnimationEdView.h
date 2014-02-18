
// AnimationEdView.h : CAnimationEdView 类的接口
//


#pragma once
#include "animationeddoc.h"

class CAnimationEdView : public CView
{
protected: // 仅从序列化创建
	CAnimationEdView();
	DECLARE_DYNCREATE(CAnimationEdView)

// 属性
public:
	CAnimationEdDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CAnimationEdView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // AnimationEdView.cpp 中的调试版本
inline CAnimationEdDoc* CAnimationEdView::GetDocument() const
   { return reinterpret_cast<CAnimationEdDoc*>(m_pDocument); }
#endif


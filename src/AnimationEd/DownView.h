#pragma once
#include "afxcmn.h"
#include "afxwin.h"



// CDownView ������ͼ

class CDownView : public CFormView
{
	DECLARE_DYNCREATE(CDownView)

protected:
	CDownView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CDownView();

public:
	enum { IDD = IDD_DOWNVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CSliderCtrl slider;
	virtual void OnInitialUpdate();
	void RefreshData(int idx = -1);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	int animidx;
	CListBox lbanim;
	afx_msg void OnLbnSelchangeList1();
};



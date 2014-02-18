#pragma once
#include "afxwin.h"



// CLeftView2 窗体视图

class CLeftView2 : public CFormView
{
	DECLARE_DYNCREATE(CLeftView2)

protected:
	CLeftView2();           // 动态创建所使用的受保护的构造函数
	virtual ~CLeftView2();

public:
	enum { IDD = IDD_LEFTVIEW2 };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CListBox jointlist;
	virtual void OnInitialUpdate();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	int RefreshJointList();
	void SetIndex(UINT index);
	afx_msg void OnLbnSelchangeList1();
};



#pragma once
#include "afxcmn.h"



// CDownView 窗体视图

class CDownView : public CFormView
{
	DECLARE_DYNCREATE(CDownView)

protected:
	CDownView();           // 动态创建所使用的受保护的构造函数
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CSliderCtrl slider;
	virtual void OnInitialUpdate();
	void RefreshData();
};



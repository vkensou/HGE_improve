#pragma once
#include "afxwin.h"



// CLeftView ������ͼ

class CLeftView : public CFormView
{
	DECLARE_DYNCREATE(CLeftView)

protected:
	CLeftView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CLeftView();

public:
	enum { IDD = IDD_LEFTVIEW };
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
	CListBox bonelist;
	virtual void OnInitialUpdate();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	int RefreshBoneList();
	void SetIndex(int index);
	afx_msg void OnLbnSelchangeList1();
	CButton btop;
	CButton bup;
	CButton bdown;
	CButton bbottom;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};


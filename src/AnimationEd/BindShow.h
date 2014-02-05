#pragma once
#include "afxwin.h"
#include "showpicturedata.h"

using namespace Show;
// CBindShow �Ի���

class CBindShow : public CDialog
{
	DECLARE_DYNAMIC(CBindShow)

public:
	CBindShow(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBindShow();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	void ResfreshData(int index);
	CString bonename;
	CString filename;
	afx_msg void OnBnClickedButton2();
	CComboBox cbindex;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnCbnSelchangeCombo1();
	CString picname;
	afx_msg void OnBnClickedButton3();
};

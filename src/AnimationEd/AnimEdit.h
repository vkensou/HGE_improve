#pragma once


// CAnimEdit �Ի���

class CAnimEdit : public CDialog
{
	DECLARE_DYNAMIC(CAnimEdit)

public:
	CAnimEdit(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAnimEdit();

// �Ի�������
	enum { IDD = IDD_ANIM_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	int fnum;
	int sfps;
	virtual BOOL OnInitDialog();
};

#pragma once


// CAnimEdit 对话框

class CAnimEdit : public CDialog
{
	DECLARE_DYNAMIC(CAnimEdit)

public:
	CAnimEdit(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAnimEdit();

// 对话框数据
	enum { IDD = IDD_ANIM_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	int fnum;
	int sfps;
	virtual BOOL OnInitDialog();
};

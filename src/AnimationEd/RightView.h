#pragma once



// CRightView 窗体视图

class CRightView : public CFormView
{
	DECLARE_DYNCREATE(CRightView)

protected:
	CRightView();           // 动态创建所使用的受保护的构造函数
	virtual ~CRightView();

public:
	enum { IDD = IDD_RIGHTVIEW };
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
	afx_msg LRESULT OnPropertyChanged(WPARAM,LPARAM);
private:
	CMFCPropertyGridCtrl m_MFCPGCtrl;
	int mpage;
public:
	virtual void OnInitialUpdate();
	void RefreshProperty();
	void SetPropertyPage(int,bool = false);
};



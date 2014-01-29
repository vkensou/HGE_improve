// RightView.cpp : 实现文件
//

#include "stdafx.h"
#include "AnimationEd.h"
#include "RightView.h"
#include "globaldata_animall.h"

// CRightView

IMPLEMENT_DYNCREATE(CRightView, CFormView)

CRightView::CRightView()
	: CFormView(CRightView::IDD)
{

}

CRightView::~CRightView()
{
}

void CRightView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRightView, CFormView)
	ON_WM_SIZE()
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)
END_MESSAGE_MAP()


// CRightView 诊断

#ifdef _DEBUG
void CRightView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CRightView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CRightView 消息处理程序

void CRightView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect rect;
	GetClientRect(&rect); // 获取当前客户区view大小
	if(m_MFCPGCtrl)
		m_MFCPGCtrl.MoveWindow(rect);
	CSize size;
	size.cx = rect.right - rect.left;
	size.cy = rect.bottom - rect.top;
	SetScrollSizes(MM_HIMETRIC, size); // 将CScrollView的大小设置为当前客户区大小
}

void CRightView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	CRect rc;   
	GetClientRect(rc);  
	m_MFCPGCtrl.Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_BORDER,rc,this,2);
	m_MFCPGCtrl.EnableHeaderCtrl(true,_T("参数"),_T("值"));
	m_MFCPGCtrl.EnableDescriptionArea();
	m_MFCPGCtrl.SetVSDotNetLook();
	m_MFCPGCtrl.MarkModifiedProperties(0);
	m_MFCPGCtrl.SetAlphabeticMode(false);
	m_MFCPGCtrl.SetShowDragContext();
	CMFCPropertyGridProperty *pGroup1 = new CMFCPropertyGridProperty(_T("参数组1"));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("x1"),(_variant_t)0.f,_T("头结点X坐标"),0));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("y1"),(_variant_t)0.f,_T("头结点Y坐标"),1));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("x2"),(_variant_t)0.f,_T("尾结点X坐标"),2));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("y2"),(_variant_t)0.f,_T("尾结点Y坐标"),3));
	pGroup1->Expand(TRUE);
	m_MFCPGCtrl.AddProperty(pGroup1);
}

LRESULT CRightView::OnPropertyChanged (WPARAM,LPARAM lParam) 
{ 
	CMFCPropertyGridProperty* pProp = (CMFCPropertyGridProperty*) lParam; 
	int i = pProp->GetData();
	float x;
	if(hotbone==0)return 0;
	switch(i)
	{
	case 0:
		x = hotbone->GetHeadY();
		hotbone->SetHead(pProp->GetValue().fltVal,x);
		break;
	case 1:
		hotbone->SetHead(hotbone->GetHeadX(),pProp->GetValue().fltVal);
		break;
	case 2:
		hotbone->SetTail(pProp->GetValue().fltVal,hotbone->GetTailY());
		break;
	case 3:
		hotbone->SetTail(hotbone->GetTailX(),pProp->GetValue().fltVal);
		break;
	}
	//CString s = pProp->GetName();  //被改变的参数名  
	//COleVariant t = pProp->GetOriginalValue();  //改变之前的值  
	//i = t.intVal;      //从COleVariant到CString  
	return 0; 
}

void CRightView::RefreshProperty()
{
	if(hotbone==0)return;
	CMFCPropertyGridProperty* pGroup1=0,*pProp=0;
	pGroup1 = m_MFCPGCtrl.GetProperty(0);
	pProp = pGroup1->GetSubItem(0);
	pProp->SetValue((_variant_t)hotbone->GetHeadX());
	pProp = pGroup1->GetSubItem(1);
	pProp->SetValue((_variant_t)hotbone->GetHeadY());
	pProp = pGroup1->GetSubItem(2);
	pProp->SetValue((_variant_t)hotbone->GetTailX());
	pProp = pGroup1->GetSubItem(3);
	pProp->SetValue((_variant_t)hotbone->GetTailY());
}
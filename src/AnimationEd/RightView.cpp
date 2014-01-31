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
	mpage = 0;
	m_MFCPGCtrl.RemoveAll();
}

LRESULT CRightView::OnPropertyChanged (WPARAM,LPARAM lParam) 
{ 
	CMFCPropertyGridProperty* pProp= (CMFCPropertyGridProperty*) lParam; 
	int i = pProp->GetData();
	CMFCPropertyGridProperty* pGroup1 = m_MFCPGCtrl.GetProperty(0);
	CMFCPropertyGridProperty* pProp1;
	switch (mpage)
	{
	case 1:
		if(hotbone==0)
		{
			SetPropertyPage(0);
			return 0;
		}
		switch(i)
		{
		case 0:
			hotbone->SetPosition(pProp->GetValue().fltVal,hotbone->GetY());
			pProp1 = pGroup1->GetSubItem(3);
			pProp1->SetValue((_variant_t)hotbone->GetHeadX());
			pProp1 = pGroup1->GetSubItem(4);
			pProp1->SetValue((_variant_t)hotbone->GetHeadY());
			pProp1 = pGroup1->GetSubItem(5);
			pProp1->SetValue((_variant_t)hotbone->GetTailX());
			pProp1 = pGroup1->GetSubItem(6);
			pProp1->SetValue((_variant_t)hotbone->GetTailY());
			break;
		case 1:
			hotbone->SetPosition(hotbone->GetX(),pProp->GetValue().fltVal);
			pProp1 = pGroup1->GetSubItem(3);
			pProp1->SetValue((_variant_t)hotbone->GetHeadX());
			pProp1 = pGroup1->GetSubItem(4);
			pProp1->SetValue((_variant_t)hotbone->GetHeadY());
			pProp1 = pGroup1->GetSubItem(5);
			pProp1->SetValue((_variant_t)hotbone->GetTailX());
			pProp1 = pGroup1->GetSubItem(6);
			pProp1->SetValue((_variant_t)hotbone->GetTailY());
			break;
		case 2:
			hotbone->SetRotate(pProp->GetValue().fltVal);
			pProp1 = pGroup1->GetSubItem(3);
			pProp1->SetValue((_variant_t)hotbone->GetHeadX());
			pProp1 = pGroup1->GetSubItem(4);
			pProp1->SetValue((_variant_t)hotbone->GetHeadY());
			pProp1 = pGroup1->GetSubItem(5);
			pProp1->SetValue((_variant_t)hotbone->GetTailX());
			pProp1 = pGroup1->GetSubItem(6);
			pProp1->SetValue((_variant_t)hotbone->GetTailY());
			break;
		case 3:
			hotbone->SetHead(pProp->GetValue().fltVal,hotbone->GetHeadY());
			pProp1 = pGroup1->GetSubItem(0);
			pProp1->SetValue((_variant_t)hotbone->GetX());
			pProp1 = pGroup1->GetSubItem(1);
			pProp1->SetValue((_variant_t)hotbone->GetY());
			pProp1 = pGroup1->GetSubItem(7);
			pProp1->SetValue((_variant_t)hotbone->GetLength());
			break;
		case 4:
			hotbone->SetHead(hotbone->GetHeadX(),pProp->GetValue().fltVal);
			pProp1 = pGroup1->GetSubItem(0);
			pProp1->SetValue((_variant_t)hotbone->GetX());
			pProp1 = pGroup1->GetSubItem(1);
			pProp1->SetValue((_variant_t)hotbone->GetY());
			pProp1 = pGroup1->GetSubItem(7);
			pProp1->SetValue((_variant_t)hotbone->GetLength());
			break;
		case 5:
			hotbone->SetTail(pProp->GetValue().fltVal,hotbone->GetTailY());
			pProp1 = pGroup1->GetSubItem(0);
			pProp1->SetValue((_variant_t)hotbone->GetX());
			pProp1 = pGroup1->GetSubItem(1);
			pProp1->SetValue((_variant_t)hotbone->GetY());
			pProp1 = pGroup1->GetSubItem(7);
			pProp1->SetValue((_variant_t)hotbone->GetLength());
			break;
		case 6:
			hotbone->SetTail(hotbone->GetTailX(),pProp->GetValue().fltVal);
			pProp1 = pGroup1->GetSubItem(0);
			pProp1->SetValue((_variant_t)hotbone->GetX());
			pProp1 = pGroup1->GetSubItem(1);
			pProp1->SetValue((_variant_t)hotbone->GetY());
			pProp1 = pGroup1->GetSubItem(7);
			pProp1->SetValue((_variant_t)hotbone->GetLength());
			break;
		}
		break;
	case 2:
		if(hotbone==0)
		{
			SetPropertyPage(0);
			return 0;
		}
		switch(i)
		{
		case 0:
			hotbone->SetHead(pProp->GetValue().fltVal,hotbone->GetHeadY());
			break;
		case 1:
			hotbone->SetHead(hotbone->GetHeadX(),pProp->GetValue().fltVal);
			break;
		}
		break;
	case 3:
		if(hotbone==0)
		{
			SetPropertyPage(0);
			return 0;
		}
		switch(i)
		{
		case 0:
			hotbone->SetTail(pProp->GetValue().fltVal,hotbone->GetTailY());
			break;
		case 1:
			hotbone->SetTail(hotbone->GetTailX(),pProp->GetValue().fltVal);
			break;
		}
		break;
	case 5:
		if(hotbone==0)
		{
			SetPropertyPage(0);
			return 0;
		}
		pGroup1 = m_MFCPGCtrl.GetProperty(0);
		switch(i)
		{
		case 0:
			hotbone->SetPosition(pProp->GetValue().fltVal,hotbone->GetY());
			break;
		case 1:
			hotbone->SetPosition(hotbone->GetX(),pProp->GetValue().fltVal);
			break;
		case 2:
			hotbone->SetControlRelative(pProp->GetValue().fltVal);
			pProp1 = pGroup1->GetSubItem(3);
			pProp1->SetValue((_variant_t)hotbone->GetControlAbsolute());
			pProp1 = pGroup1->GetSubItem(0);
			pProp1->SetValue((_variant_t)hotbone->GetX());
			pProp1 = pGroup1->GetSubItem(1);
			pProp1->SetValue((_variant_t)hotbone->GetY());
			break;
		case 3:
			hotbone->SetControlAbsolute(pProp->GetValue().fltVal);
			pProp1 = pGroup1->GetSubItem(2);
			pProp1->SetValue((_variant_t)hotbone->GetControlRelative());
			pProp1 = pGroup1->GetSubItem(0);
			pProp1->SetValue((_variant_t)hotbone->GetX());
			pProp1 = pGroup1->GetSubItem(1);
			pProp1->SetValue((_variant_t)hotbone->GetY());
			break;
		case 4:
			{
			CString d = pProp->GetValue().bstrVal;
			if(d==L"头结点")
				hotbone->SetControlBasis(true);
			else
				hotbone->SetControlBasis(false);
			pProp1 = pGroup1->GetSubItem(2);
			pProp1->SetValue((_variant_t)hotbone->GetControlRelative());
			pProp1 = pGroup1->GetSubItem(3);
			pProp1->SetValue((_variant_t)hotbone->GetControlAbsolute());
			break;
			}
		case 5:
			hotbone->SetRotate(pProp->GetValue().fltVal);
			break;
		}
		break;
	case 6:
		if(hotbone==0 || hotjoint==0)
		{
			SetPropertyPage(0);
			return 0;
		}
		switch(i)
		{
		case 0:
			hotbone->SetJointRelative(hotjoint,pProp->GetValue().fltVal);
			pProp1 = pGroup1->GetSubItem(1);
			pProp1->SetValue((_variant_t)hotbone->GetJointAbsolute(hotjoint));
			break;
		case 1:
			hotbone->SetJointAbsolute(hotjoint,pProp->GetValue().fltVal);
			pProp1 = pGroup1->GetSubItem(0);
			pProp1->SetValue((_variant_t)hotbone->GetJointRelative(hotjoint));
			break;
		case 2:
			{
				CString d = pProp->GetValue().bstrVal;
				if(d==L"头结点")
					hotbone->SetJointBasis(hotjoint,true);
				else
					hotbone->SetJointBasis(hotjoint,false);
				pProp1 = pGroup1->GetSubItem(0);
				pProp1->SetValue((_variant_t)hotbone->GetJointRelative(hotjoint));
				pProp1 = pGroup1->GetSubItem(1);
				pProp1->SetValue((_variant_t)hotbone->GetJointAbsolute(hotjoint));
				break;
			}
		}
		break;
	}
	//CString s = pProp->GetName();  //被改变的参数名  
	//COleVariant t = pProp->GetOriginalValue();  //改变之前的值  
	//i = t.intVal;      //从COleVariant到CString  
	return 0; 
}

void CRightView::RefreshProperty()
{
	CMFCPropertyGridProperty* pGroup1=0,*pProp=0;
	switch(mpage)
	{
	case 1:
		if(hotbone==0)
		{
			SetPropertyPage(0);
			return;
		}
		pGroup1 = m_MFCPGCtrl.GetProperty(0);
		pProp = pGroup1->GetSubItem(0);
		pProp->SetValue((_variant_t)hotbone->GetX());
		pProp = pGroup1->GetSubItem(1);
		pProp->SetValue((_variant_t)hotbone->GetY());
		pProp = pGroup1->GetSubItem(2);
		pProp->SetValue((_variant_t)hotbone->GetRotate());
		pProp = pGroup1->GetSubItem(3);
		pProp->SetValue((_variant_t)hotbone->GetHeadX());
		pProp = pGroup1->GetSubItem(4);
		pProp->SetValue((_variant_t)hotbone->GetHeadY());
		pProp = pGroup1->GetSubItem(5);
		pProp->SetValue((_variant_t)hotbone->GetTailX());
		pProp = pGroup1->GetSubItem(6);
		pProp->SetValue((_variant_t)hotbone->GetTailY());
		pProp = pGroup1->GetSubItem(7);
		pProp->SetValue((_variant_t)hotbone->GetLength());
		break;
	case 2:
		if(hotbone==0)
		{
			SetPropertyPage(0);
			return;
		}
		pGroup1 = m_MFCPGCtrl.GetProperty(0);
		pProp = pGroup1->GetSubItem(0);
		pProp->SetValue((_variant_t)hotbone->GetHeadX());
		pProp = pGroup1->GetSubItem(1);
		pProp->SetValue((_variant_t)hotbone->GetHeadY());
		break;
	case 3:
		if(hotbone==0)
		{
			SetPropertyPage(0);
			return;
		}
		pGroup1 = m_MFCPGCtrl.GetProperty(0);
		pProp = pGroup1->GetSubItem(0);
		pProp->SetValue((_variant_t)hotbone->GetTailX());
		pProp = pGroup1->GetSubItem(1);
		pProp->SetValue((_variant_t)hotbone->GetTailY());
		break;
	case 5:
		if(hotbone==0)
		{
			SetPropertyPage(0);
			return;
		}
		pGroup1 = m_MFCPGCtrl.GetProperty(0);
		pProp = pGroup1->GetSubItem(0);
		pProp->SetValue((_variant_t)hotbone->GetX());
		pProp = pGroup1->GetSubItem(1);
		pProp->SetValue((_variant_t)hotbone->GetY());
		pProp = pGroup1->GetSubItem(2);
		pProp->SetValue((_variant_t)hotbone->GetControlRelative());
		pProp = pGroup1->GetSubItem(3);
		pProp->SetValue((_variant_t)hotbone->GetControlAbsolute());
		pProp = pGroup1->GetSubItem(4);
		if(hotbone->GetControlBasis()==true)
			pProp->SetValue((_variant_t)L"头结点");
		else
			pProp->SetValue((_variant_t)L"尾结点");
		pProp = pGroup1->GetSubItem(5);
		pProp->SetValue((_variant_t)hotbone->GetRotate());
		break;
	case 6:
		if(hotbone==0 || hotjoint==0)
		{
			SetPropertyPage(0);
			return;
		}
		pGroup1 = m_MFCPGCtrl.GetProperty(0);
		pProp = pGroup1->GetSubItem(0);
		pProp->SetValue((_variant_t)hotbone->GetJointRelative(hotjoint));
		pProp = pGroup1->GetSubItem(1);
		pProp->SetValue((_variant_t)hotbone->GetJointAbsolute(hotjoint));
		pProp = pGroup1->GetSubItem(2);
		if(hotbone->GetJointBasis(hotjoint)==true)
			pProp->SetValue((_variant_t)L"头结点");
		else
			pProp->SetValue((_variant_t)L"尾结点");
	}
}

void CRightView::SetPropertyPage(int n)
{
	if(n == mpage)return ;
	mpage = n;
	m_MFCPGCtrl.RemoveAll();
	m_MFCPGCtrl.SetAlphabeticMode(true);
	m_MFCPGCtrl.SetAlphabeticMode(false);
	switch (mpage)
	{
	case 0:
		break;
	case 1:
		{
			CMFCPropertyGridProperty *pGroup1 = new CMFCPropertyGridProperty(_T("骨头"));
			pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("X"),(_variant_t)0.f,_T("控制节点的X轴坐标"),0));
			pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Y"),(_variant_t)0.f,_T("控制节点的Y轴坐标"),1));
			pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("倾斜角"),(_variant_t)0.f,_T("头结点指向尾结点的有向线段的倾斜角。改变这个值骨头将以控制点为中心旋转。"),2));
			pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("X1"),(_variant_t)0.f,_T("头结点X轴坐标"),3));
			pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Y1"),(_variant_t)0.f,_T("头结点Y轴坐标"),4));
			pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("X2"),(_variant_t)0.f,_T("尾结点X轴坐标"),5));
			pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Y2"),(_variant_t)0.f,_T("尾结点Y轴坐标"),6));
			CMFCPropertyGridProperty *pp1 = new CMFCPropertyGridProperty(_T("长度"),(_variant_t)0.f,_T("骨头长度"),7);
			pp1->AllowEdit(0);
			pGroup1->AddSubItem(pp1);
			pGroup1->Expand(TRUE);
			m_MFCPGCtrl.AddProperty(pGroup1);
			break;
		}
	case 2:
		{
			CMFCPropertyGridProperty *pGroup1 = new CMFCPropertyGridProperty(_T("头结点"));
			pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("X"),(_variant_t)0.f,_T("X轴坐标"),0));
			pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Y"),(_variant_t)0.f,_T("Y轴坐标"),1));
			pGroup1->Expand(TRUE);
			m_MFCPGCtrl.AddProperty(pGroup1);
			break;
		}
	case 3:
		{
			CMFCPropertyGridProperty *pGroup1 = new CMFCPropertyGridProperty(_T("尾结点"));
			pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("X"),(_variant_t)0.f,_T("X轴坐标"),0));
			pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Y"),(_variant_t)0.f,_T("Y轴坐标"),1));
			pGroup1->Expand(TRUE);
			m_MFCPGCtrl.AddProperty(pGroup1);
			break;
		}
	case 4:
		break;
	case 5:
		{
			CMFCPropertyGridProperty *pGroup1 = new CMFCPropertyGridProperty(_T("控制结点"));
			pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("X"),(_variant_t)0.f,_T("X轴坐标，改变该值将导致骨头沿X轴平移"),0));
			pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Y"),(_variant_t)0.f,_T("Y轴坐标，改变该值将导致骨头沿Y轴平移"),1));
			pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("相对位置"),(_variant_t)0.f,_T("结点在骨头上相对基准点的位置"),2));
			pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("绝对位置"),(_variant_t)0.f,_T("结点在骨头上距离基准点的距离"),3));
			CMFCPropertyGridProperty *pProp = new CMFCPropertyGridProperty(_T("基准点"),(_variant_t)L"头结点",_T("控制点坐标是根据头结点还是尾结点确定"),4);
			pProp->AddOption(L"头结点");	pProp->AddOption(L"尾结点");
			pProp->AllowEdit(false);
			pGroup1->AddSubItem(pProp);
			pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("倾斜角"),(_variant_t)0.f,_T("头结点指向尾结点的有向线段的倾斜角。改变这个值骨头将以控制点为中心旋转。"),5));
			//pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("倾角"),(_variant_t)0.f,_T("骨头的倾角"),1));
			pGroup1->Expand(TRUE);
			m_MFCPGCtrl.AddProperty(pGroup1);
			break;
		}
	case 6:
		{
			CMFCPropertyGridProperty *pGroup1 = new CMFCPropertyGridProperty(_T("关节"));
			pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("相对位置"),(_variant_t)0.f,_T("关节在骨头上相对基准点的位置"),0));
			pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("绝对位置"),(_variant_t)0.f,_T("关节在骨头上距离基准点的距离"),1));
			CMFCPropertyGridProperty *pProp = new CMFCPropertyGridProperty(_T("基准点"),(_variant_t)L"头结点",_T("控制点坐标是根据头结点还是尾结点确定"),2);
			pProp->AddOption(L"头结点");	pProp->AddOption(L"尾结点");
			pProp->AllowEdit(false);
			pGroup1->AddSubItem(pProp);
			pGroup1->Expand(TRUE);
			m_MFCPGCtrl.AddProperty(pGroup1);
			break;
		}
	}
}
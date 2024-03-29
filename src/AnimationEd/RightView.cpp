// RightView.cpp : 实现文件
//

#include "stdafx.h"
#include "AnimationEd.h"
#include "RightView.h"
#include "globaldata_animall.h"
#include "globaldata_view.h"

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
	if(editmode)
	{
		if(hotbone==0)
		{
			SetPropertyPage(0);
			return 0;
		}
		switch (mpage)
		{
		case 1:
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
				hotbone->SetRotate(Radian(pProp->GetValue().fltVal));
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
				pProp1 = pGroup1->GetSubItem(2);
				pProp1->SetValue((_variant_t)Degree(hotbone->GetRotate()));
				break;
			case 4:
				hotbone->SetHead(hotbone->GetHeadX(),pProp->GetValue().fltVal);
				pProp1 = pGroup1->GetSubItem(0);
				pProp1->SetValue((_variant_t)hotbone->GetX());
				pProp1 = pGroup1->GetSubItem(1);
				pProp1->SetValue((_variant_t)hotbone->GetY());
				pProp1 = pGroup1->GetSubItem(7);
				pProp1->SetValue((_variant_t)hotbone->GetLength());
				pProp1 = pGroup1->GetSubItem(2);
				pProp1->SetValue((_variant_t)Degree(hotbone->GetRotate()));
				break;
			case 5:
				hotbone->SetTail(pProp->GetValue().fltVal,hotbone->GetTailY());
				pProp1 = pGroup1->GetSubItem(0);
				pProp1->SetValue((_variant_t)hotbone->GetX());
				pProp1 = pGroup1->GetSubItem(1);
				pProp1->SetValue((_variant_t)hotbone->GetY());
				pProp1 = pGroup1->GetSubItem(7);
				pProp1->SetValue((_variant_t)hotbone->GetLength());
				pProp1 = pGroup1->GetSubItem(2);
				pProp1->SetValue((_variant_t)Degree(hotbone->GetRotate()));
				break;
			case 6:
				hotbone->SetTail(hotbone->GetTailX(),pProp->GetValue().fltVal);
				pProp1 = pGroup1->GetSubItem(0);
				pProp1->SetValue((_variant_t)hotbone->GetX());
				pProp1 = pGroup1->GetSubItem(1);
				pProp1->SetValue((_variant_t)hotbone->GetY());
				pProp1 = pGroup1->GetSubItem(7);
				pProp1->SetValue((_variant_t)hotbone->GetLength());
				pProp1 = pGroup1->GetSubItem(2);
				pProp1->SetValue((_variant_t)Degree(hotbone->GetRotate()));
				break;
			case 7:
				hotbone->SetLength(pProp->GetValue().fltVal);
				pProp1 = pGroup1->GetSubItem(3);
				pProp1->SetValue((_variant_t)hotbone->GetHeadX());
				pProp1 = pGroup1->GetSubItem(4);
				pProp1->SetValue((_variant_t)hotbone->GetHeadY());
				pProp1 = pGroup1->GetSubItem(5);
				pProp1->SetValue((_variant_t)hotbone->GetTailX());
				pProp1 = pGroup1->GetSubItem(6);
				pProp1->SetValue((_variant_t)hotbone->GetTailY());
				break;
			case 8:
				{
					int d = pProp->GetValue().intVal;
					if(nowskt->GetBoneFromID(d)==0)
						//if(nowskt->bones[d]==0)
					{
						hotbone->SetFather(-1,0);
						_variant_t v;
						v = -1;
						v.ChangeType(VT_I4);
						pProp->SetValue(v);
					}
					else
					{
						if(!hotbone->SetFather(d,nowskt->GetBoneFromID(d)))
						{
							_variant_t v;
							v = hotbone->GetFather();
							v.ChangeType(VT_I4);
							pProp->SetValue(v);
						}
					}
					break;
				}
			case 9:
				{
					CString b = pProp->GetValue().bstrVal;
					if(b==L"是")
					{
						nowskt->mainbone = hotbone;
						nowskt->mbidx = hotbone->GetID();
					}
					else
					{
						nowskt->mainbone = 0;
						nowskt->mbidx = -1;
					}
				}
			}
			break;
		case 2:
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
		case 4:
			//pGroup1 = m_MFCPGCtrl.GetProperty(0);
			switch(i)
			{
			case 2:
				hotbone->BindPoint().SetRelative(pProp->GetValue().fltVal);
				pProp1 = pGroup1->GetSubItem(3);
				pProp1->SetValue((_variant_t)hotbone->BindPoint().GetAbsolute());
				pProp1 = pGroup1->GetSubItem(0);
				pProp1->SetValue((_variant_t)hotbone->BindPoint().GetX());
				pProp1 = pGroup1->GetSubItem(1);
				pProp1->SetValue((_variant_t)hotbone->BindPoint().GetY());
				break;
			case 3:
				hotbone->BindPoint().SetAbsolute(pProp->GetValue().fltVal);
				pProp1 = pGroup1->GetSubItem(2);
				pProp1->SetValue((_variant_t)hotbone->BindPoint().GetRelative());
				pProp1 = pGroup1->GetSubItem(0);
				pProp1->SetValue((_variant_t)hotbone->BindPoint().GetX());
				pProp1 = pGroup1->GetSubItem(1);
				pProp1->SetValue((_variant_t)hotbone->BindPoint().GetY());
				break;
			case 4:
				{
					CString d = pProp->GetValue().bstrVal;
					if(d==L"头结点")
						hotbone->BindPoint().SetBasis(true);
					else
						hotbone->BindPoint().SetBasis(false);
					pProp1 = pGroup1->GetSubItem(2);
					pProp1->SetValue((_variant_t)hotbone->BindPoint().GetRelative());
					pProp1 = pGroup1->GetSubItem(3);
					pProp1->SetValue((_variant_t)hotbone->BindPoint().GetAbsolute());
					break;
				}
			case 5:
				hotbone->BindPoint().SetRotation(Radian(pProp->GetValue().fltVal));
				break;
			case 6:
				hotbone->BindPoint().SetScale(pProp->GetValue().fltVal ,hotbone->BindPoint().GetHScale());
				break;
			case 7:
				hotbone->BindPoint().SetScale(hotbone->BindPoint().GetVScale() ,pProp->GetValue().fltVal );
				break;
			}
			break;
		case 5:
			//pGroup1 = m_MFCPGCtrl.GetProperty(0);
			switch(i)
			{
			case 0:
				hotbone->SetPosition(pProp->GetValue().fltVal,hotbone->GetY());
				break;
			case 1:
				hotbone->SetPosition(hotbone->GetX(),pProp->GetValue().fltVal);
				break;
			case 2:
				hotbone->ControlPoint().SetRelative(pProp->GetValue().fltVal);
				pProp1 = pGroup1->GetSubItem(3);
				pProp1->SetValue((_variant_t)hotbone->ControlPoint().GetAbsolute());
				pProp1 = pGroup1->GetSubItem(0);
				pProp1->SetValue((_variant_t)hotbone->GetX());
				pProp1 = pGroup1->GetSubItem(1);
				pProp1->SetValue((_variant_t)hotbone->GetY());
				break;
			case 3:
				hotbone->ControlPoint().SetAbsolute(pProp->GetValue().fltVal);
				pProp1 = pGroup1->GetSubItem(2);
				pProp1->SetValue((_variant_t)hotbone->ControlPoint().GetRelative());
				pProp1 = pGroup1->GetSubItem(0);
				pProp1->SetValue((_variant_t)hotbone->GetX());
				pProp1 = pGroup1->GetSubItem(1);
				pProp1->SetValue((_variant_t)hotbone->GetY());
				break;
			case 4:
				{
					CString d = pProp->GetValue().bstrVal;
					if(d==L"头结点")
						hotbone->ControlPoint().SetBasis(true);
					else
						hotbone->ControlPoint().SetBasis(false);
					pProp1 = pGroup1->GetSubItem(2);
					pProp1->SetValue((_variant_t)hotbone->ControlPoint().GetRelative());
					pProp1 = pGroup1->GetSubItem(3);
					pProp1->SetValue((_variant_t)hotbone->ControlPoint().GetAbsolute());
					break;
				}
			case 5:
				hotbone->SetRotate(Radian(pProp->GetValue().fltVal));
				break;
			}
			break;
		case 6:
			if(hotjoint==0)
			{
				SetPropertyPage(0);
				return 0;
			}
			switch(i)
			{
			case 0:
				hotjoint->SetRelative(pProp->GetValue().fltVal);
				pProp1 = pGroup1->GetSubItem(1);
				pProp1->SetValue((_variant_t)hotjoint->GetAbsolute());
				break;
			case 1:
				hotjoint->SetAbsolute(pProp->GetValue().fltVal);
				pProp1 = pGroup1->GetSubItem(0);
				pProp1->SetValue((_variant_t)hotjoint->GetRelative());
				break;
			case 2:
				{
					CString d = pProp->GetValue().bstrVal;
					if(d==L"头结点")
						hotjoint->SetBasis(true);
					else
						hotjoint->SetBasis(false);
					pProp1 = pGroup1->GetSubItem(0);
					pProp1->SetValue((_variant_t)hotjoint->GetRelative());
					pProp1 = pGroup1->GetSubItem(1);
					pProp1->SetValue((_variant_t)hotjoint->GetAbsolute());
					break;
				}
			case 4:
				{
					hotjoint->angle = Radian(pProp->GetValue().fltVal);
					hotjoint->bindjoint->angle = - hotjoint->angle;
					hotjoint->bone->SetPositionByJoint(hotjoint);
				}
			}
			break;
		}
		//CString s = pProp->GetName();  //被改变的参数名  
		//COleVariant t = pProp->GetOriginalValue();  //改变之前的值  
		//i = t.intVal;      //从COleVariant到CString  
	}
	else
	{
		switch(mpage)
		{
		case 0:
			switch(i)
			{
			case 0:
				{
					nowskt->SetOffset(pProp->GetValue().fltVal,nowskt->GetOY());
					break;
				}
			case 1:
				{
					nowskt->SetOffset(nowskt->GetOX(),pProp->GetValue().fltVal);
					break;	
				}
			}
			break;
		case 1:
			if(!hotbone)return 0;
			hotbone->SetRotateE(Radian(pProp->GetValue().fltVal));
			break;
		}
	}
	return 0; 
}

void CRightView::RefreshProperty()
{
	CMFCPropertyGridProperty* pGroup1=0,*pProp=0;
	if(editmode)
	{
		if(hotbone==0)
		{
			SetPropertyPage(0);
			return;
		}
		switch(mpage)
		{
		case 1:
			pGroup1 = m_MFCPGCtrl.GetProperty(0);
			pProp = pGroup1->GetSubItem(0);
			pProp->SetValue((_variant_t)hotbone->GetX());
			pProp = pGroup1->GetSubItem(1);
			pProp->SetValue((_variant_t)hotbone->GetY());
			pProp = pGroup1->GetSubItem(2);
			pProp->SetValue((_variant_t)Degree(hotbone->GetRotate()));
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
			pProp = pGroup1->GetSubItem(8);
			{
				_variant_t t = hotbone->GetFather();
				t.ChangeType(pProp->GetValue().vt);
				if(t != pProp->GetValue())
					pProp->SetValue(t);
			}
			pProp = pGroup1->GetSubItem(9);
			if(nowskt->mainbone == hotbone)
				pProp->SetValue((_variant_t)L"是");
			else
				pProp->SetValue((_variant_t)L"否");
			break;
		case 2:
			pGroup1 = m_MFCPGCtrl.GetProperty(0);
			pProp = pGroup1->GetSubItem(0);
			pProp->SetValue((_variant_t)hotbone->GetHeadX());
			pProp = pGroup1->GetSubItem(1);
			pProp->SetValue((_variant_t)hotbone->GetHeadY());
			break;
		case 3:
			pGroup1 = m_MFCPGCtrl.GetProperty(0);
			pProp = pGroup1->GetSubItem(0);
			pProp->SetValue((_variant_t)hotbone->GetTailX());
			pProp = pGroup1->GetSubItem(1);
			pProp->SetValue((_variant_t)hotbone->GetTailY());
			break;
		case 4:
			pGroup1 = m_MFCPGCtrl.GetProperty(0);
			pProp = pGroup1->GetSubItem(0);
			pProp->SetValue((_variant_t)hotbone->BindPoint().GetX());
			pProp = pGroup1->GetSubItem(1);
			pProp->SetValue((_variant_t)hotbone->BindPoint().GetY());
			pProp = pGroup1->GetSubItem(2);
			pProp->SetValue((_variant_t)hotbone->BindPoint().GetRelative());
			pProp = pGroup1->GetSubItem(3);
			pProp->SetValue((_variant_t)hotbone->BindPoint().GetAbsolute());
			pProp = pGroup1->GetSubItem(4);
			if(hotbone->BindPoint().GetBasis()==true)
				pProp->SetValue((_variant_t)L"头结点");
			else
				pProp->SetValue((_variant_t)L"尾结点");
			if(hotbone->BindPoint().part)
			{
				pProp = pGroup1->GetSubItem(5);
				pProp->SetValue((_variant_t)Degree(hotbone->BindPoint().GetRotation()));
				pProp = pGroup1->GetSubItem(6);
				pProp->SetValue((_variant_t)hotbone->BindPoint().GetHScale());
				pProp = pGroup1->GetSubItem(7);
				pProp->SetValue((_variant_t)hotbone->BindPoint().GetVScale());
			}
			break;
		case 5:
			pGroup1 = m_MFCPGCtrl.GetProperty(0);
			pProp = pGroup1->GetSubItem(0);
			pProp->SetValue((_variant_t)hotbone->GetX());
			pProp = pGroup1->GetSubItem(1);
			pProp->SetValue((_variant_t)hotbone->GetY());
			pProp = pGroup1->GetSubItem(2);
			pProp->SetValue((_variant_t)hotbone->ControlPoint().GetRelative());
			pProp = pGroup1->GetSubItem(3);
			pProp->SetValue((_variant_t)hotbone->ControlPoint().GetAbsolute());
			pProp = pGroup1->GetSubItem(4);
			if(hotbone->ControlPoint().GetBasis()==true)
				pProp->SetValue((_variant_t)L"头结点");
			else
				pProp->SetValue((_variant_t)L"尾结点");
			pProp = pGroup1->GetSubItem(5);
			pProp->SetValue((_variant_t)Degree(hotbone->GetRotate()));
			break;
		case 6:
			if(hotjoint==0)
			{
				SetPropertyPage(0);
				return;
			}
			pGroup1 = m_MFCPGCtrl.GetProperty(0);
			pProp = pGroup1->GetSubItem(0);
			pProp->SetValue((_variant_t)hotjoint->GetRelative());
			pProp = pGroup1->GetSubItem(1);
			pProp->SetValue((_variant_t)hotjoint->GetAbsolute());
			pProp = pGroup1->GetSubItem(2);
			if(hotjoint->GetBasis()==true)
				pProp->SetValue((_variant_t)L"头结点");
			else
				pProp->SetValue((_variant_t)L"尾结点");
			pProp = pGroup1->GetSubItem(3);
			if(hotjoint->bindbone)
				pProp->SetValue((_variant_t)L"已绑定");
			else
				pProp->SetValue((_variant_t)L"无");
			pProp = pGroup1->GetSubItem(4);
			if(hotjoint->bindbone)
			{
				pProp->AllowEdit(TRUE);
				pProp->SetValue((_variant_t)Degree(hotjoint->angle));
			}
			else
			{
				pProp->AllowEdit(FALSE);
				pProp->SetValue((_variant_t)0.f);
			}
		}
	}
	else
	{
		switch(mpage)
		{
		case 0:
			{
				if(hotbone)return;
				pGroup1 = m_MFCPGCtrl.GetProperty(0);
				pProp = pGroup1->GetSubItem(0);
				pProp->SetValue((_variant_t)nowskt->GetOX());
				pProp = pGroup1->GetSubItem(1);
				pProp->SetValue((_variant_t)nowskt->GetOY());
				break;
			}
		case 1:
			{
				if(!hotbone)return;
				pGroup1 = m_MFCPGCtrl.GetProperty(0);
				pProp = pGroup1->GetSubItem(0);
				pProp->SetValue((_variant_t)Degree(hotbone->GetRotateE()));
				break;
			}
		}
	}
}

void CRightView::SetPropertyPage(int n,bool v)
{
	if(editmode)
	{
		if(v || n == mpage)return ;
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
				pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("长度"),(_variant_t)0.f,_T("骨头长度"),7));
				pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("父骨头"),(_variant_t)-1,_T("父骨头移动会带动孩子移动，输入不存在的骨头序号会清除父骨头，通常用-1表示没有父亲"),8));
				CMFCPropertyGridProperty *pProp = new CMFCPropertyGridProperty(_T("主骨头"),(_variant_t)L"否",_T("是否是主骨头"),9);
				pProp->AddOption(_T("是"));
				pProp->AddOption(_T("否"));
				pGroup1->AddSubItem(pProp);
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
			{
				CMFCPropertyGridProperty *pGroup1 = new CMFCPropertyGridProperty(_T("绑定节点"));
				CMFCPropertyGridProperty *pProp = new CMFCPropertyGridProperty(_T("X"),(_variant_t)0.f,_T("X轴坐标，只读"),0);
				pProp->AllowEdit(false);
				pGroup1->AddSubItem(pProp);
				pProp = new CMFCPropertyGridProperty(_T("Y"),(_variant_t)0.f,_T("y轴坐标，只读"),1);
				pProp->AllowEdit(false);
				pGroup1->AddSubItem(pProp);
				pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("相对位置"),(_variant_t)0.f,_T("结点在骨头上相对基准点的位置"),2));
				pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("绝对位置"),(_variant_t)0.f,_T("结点在骨头上距离基准点的距离"),3));
				pProp = new CMFCPropertyGridProperty(_T("基准点"),(_variant_t)L"头结点",_T("绑定节点坐标是根据头结点还是尾结点确定"),4);
				pProp->AddOption(L"头结点");	pProp->AddOption(L"尾结点");
				pProp->AllowEdit(false);
				pGroup1->AddSubItem(pProp);
				if(hotbone->BindPoint().part)
				{
					pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("旋转量"),(_variant_t)0.f,_T("绑定的图元相对骨头的旋转量"),5));
					pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("横向拉伸"),(_variant_t)0.f,_T("绑定的图元横向拉伸量"),6));
					pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("纵向拉伸"),(_variant_t)0.f,_T("绑定的图元纵向拉伸量"),7));
				}
				pGroup1->Expand(TRUE);
				m_MFCPGCtrl.AddProperty(pGroup1);
				break;
			}
		case 5:
			{
				CMFCPropertyGridProperty *pGroup1 = new CMFCPropertyGridProperty(_T("控制节点"));
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
				pProp = new CMFCPropertyGridProperty(_T("绑定"),(_variant_t)L"无",_T("关节是否已绑定骨头"),3);
				pProp->AllowEdit(false);
				pGroup1->AddSubItem(pProp);
				pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("相对旋转角度"),(_variant_t)0.f,_T("骨头相对绑定骨头的顺时针旋转角度"),4));
				pGroup1->Expand(TRUE);
				m_MFCPGCtrl.AddProperty(pGroup1);
				break;
			}
		}
	}
	else
	{
		if(v || n == mpage)return ;
		mpage = n;
		m_MFCPGCtrl.RemoveAll();
		m_MFCPGCtrl.SetAlphabeticMode(true);
		m_MFCPGCtrl.SetAlphabeticMode(false);
		switch (mpage)
		{
		case 0:
			{
				CMFCPropertyGridProperty *pGroup1 = new CMFCPropertyGridProperty(_T("骨骼"));
				pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("OX"),(_variant_t)0.f,_T("主骨头的X轴偏移值"),0));
				pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("OY"),(_variant_t)0.f,_T("主骨头的Y轴偏移值"),1));
				pGroup1->Expand(TRUE);
				m_MFCPGCtrl.AddProperty(pGroup1);
				break;
			}
		case 1:
			{
				CMFCPropertyGridProperty *pGroup1 = new CMFCPropertyGridProperty(_T("骨头"));
				pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("倾斜角"),(_variant_t)0.f,_T("骨头的倾斜角"),0));
				pGroup1->Expand(TRUE);
				m_MFCPGCtrl.AddProperty(pGroup1);
				break;
			}
		}
	}
}
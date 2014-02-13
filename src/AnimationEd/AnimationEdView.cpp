
// AnimationEdView.cpp : CAnimationEdView 类的实现
//

#include "stdafx.h"
#include "AnimationEd.h"

#include "AnimationEdDoc.h"
#include "AnimationEdView.h"

#include "globaldata_animall.h"
#include "globaldata_view.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

UINT overi=0,overji=0;

// CAnimationEdView

IMPLEMENT_DYNCREATE(CAnimationEdView, CView)

BEGIN_MESSAGE_MAP(CAnimationEdView, CView)
	ON_WM_DESTROY()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CAnimationEdView 构造/析构

CAnimationEdView::CAnimationEdView()
{
	// TODO: 在此处添加构造代码

}

CAnimationEdView::~CAnimationEdView()
{
}

BOOL CAnimationEdView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CAnimationEdView 绘制

void CAnimationEdView::OnDraw(CDC* /*pDC*/)
{
	CAnimationEdDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}

void CAnimationEdView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CAnimationEdView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CAnimationEdView 诊断

#ifdef _DEBUG
void CAnimationEdView::AssertValid() const
{
	CView::AssertValid();
}

void CAnimationEdView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAnimationEdDoc* CAnimationEdView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAnimationEdDoc)));
	return (CAnimationEdDoc*)m_pDocument;
}
#endif //_DEBUG

bool FrameFunc()
{
	float mx=0,my=0;
	static float lmx = 0,lmy = 0;
	static float vmx = 0,vmy = 0;
	static float rort = 0;
	hge->Input_GetMousePos(&mx,&my);
	overi = overji = -1;
	over = 0;overj = 0;

	std::map<int,hgeBone*>::iterator m1_Iter;
	if(mode == 0 || mode == 1)
	{
		std::list<hgeBone*>::iterator itor;
		hgeBone* vv;
		for(itor = nowskt->bones.begin();itor != nowskt->bones.end();itor++)
		{
			vv = *itor;
			if(vv->GetDistanceFromPoint(mx,my)<2)
			{
				overi = vv->GetID();
				over = vv;
				break;
			}
		}

		if(hge->Input_KeyDown(HGEK_LBUTTON))
		{
			float x,y;
			hgePoint dd;
			if(hotbone)
			{
				dd = hotbone->GetOtherPoint();
				x = dd.x,y = dd.y;
			}
			if(mode == 0 && hotbone && mx >= x-4 && mx <= x+4 && my >= y-4 && my <= y+4)
			{
				rort = hotbone->GetRotate() + M_PI_2;
				mode = 7;
			}
			else if(over)
				SelectBone(overi,true);
			else
				SelectBone(-1,true);
		}
		
		if(over)
		{
			for(UINT i = 0;i<over->joints.size();i++)
			{
				if(mx>over->joints[i]->GetX()-4 && mx<over->joints[i]->GetX()+4 && my>over->joints[i]->GetY()-4 && my<over->joints[i]->GetY()+4)
				{
					overji = i;
					overj = over->joints[i];
					break;
				}
			}
		}

		if(hge->Input_KeyDown(HGEK_LBUTTON) && editmode)
		{
			if(mode == 0 && over && mx >= over->GetHeadX()-4 && mx <= over->GetHeadX()+4 && my >= over->GetHeadY()-4 && my <= over->GetHeadY()+4)
			{
				mode = 4;
			}
			else if(mode == 0 && over && mx >= over->GetTailX()-4 && mx <= over->GetTailX()+4 && my >= over->GetTailY()-4 && my <= over->GetTailY()+4)
			{
				mode = 5;
			}
			else if(overj)
			{
				SelectJoint(overji+4,true);
			}
			else if(hotbone && hotbone->GetDistanceFromPoint(mx,my)<2)
			{
				mode = 6;
				vmx = mx - hotbone->GetX();
				vmy = my - hotbone->GetY();
			}
		}

		if(hge->Input_KeyDown(HGEK_RBUTTON))
		{
			mode = 0;
		}
	}
	else if(mode == 2)
	{
		if(hge->Input_KeyDown(HGEK_RBUTTON))
		{
			mode = 0;
		}
		else if(hge->Input_KeyDown(HGEK_LBUTTON))
		{
			hotbone = nowskt->GetBoneFromID(nowskt->AddBone());
			hotbone->SetHead(mx,my);
			hotbone->SetTail(mx,my);
			mode = 3;
		}
	}
	else if(mode == 3)
	{
		if(hge->Input_GetKeyState(HGEK_LBUTTON) && hotbone)
		{
			hotbone->SetTail(mx,my);
		}
		else
		{
			mode = 0;
			hotbone = 0;
			g_leftview->RefreshBoneList();
			SelectBone(nowskt->newestbi,true);
		}
	}
	else if(mode == 4)
	{
		if(hge->Input_GetKeyState(HGEK_LBUTTON) && hotbone)
		{
			hotbone->SetHead(mx,my);
		}
		else
		{
			mode = 0;
			g_rightview->RefreshProperty();
		}
	}
	else if(mode == 5)
	{
		if(hge->Input_GetKeyState(HGEK_LBUTTON) && hotbone)
		{
			hotbone->SetTail(mx,my);
		}
		else
		{
			mode = 0;
			g_rightview->RefreshProperty();
		}
	}
	else if(mode == 6)
	{
		if(hge->Input_GetKeyState(HGEK_LBUTTON) && hotbone)
		{
			if(lmx != mx || lmy !=my)
				hotbone->SetPosition(mx - vmx,my - vmy);
		}
		else
		{
			mode = 0;
			g_rightview->RefreshProperty();
		}
	}
	else if(mode ==7)
	{
		if(hge->Input_GetKeyState(HGEK_LBUTTON) && hotbone)
		{
			if(abs(hotbone->ControlPoint().GetX() - mx) > 0.01 && abs(hotbone->ControlPoint().GetY() - my) > 0.01)
			{
				hgeLine temp(hotbone->ControlPoint().GetX() ,hotbone->ControlPoint().GetY() ,mx,my);
				hotbone->SetRotate(temp.GetRotate() - M_PI_2);
			}
		}
		else
		{
			mode = 0;
			g_rightview->RefreshProperty();
		}
	}
	lmx = mx;lmy = my;

	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);

	std::list<hgeBone*>::reverse_iterator ritor;
	hgeBone* vv;
	for(ritor = nowskt->bones.rbegin();ritor != nowskt->bones.rend();ritor++)
	{
		vv = *ritor;
		hge->Gfx_RenderLine(vv->GetHeadX(),vv->GetHeadY(),vv->GetTailX(),vv->GetTailY(),0xffffffff);
		vv->bind.Render();
	}

	if(hotbone)
	{
		//画头结点
		float x = hotbone->GetHeadX(),y = hotbone->GetHeadY();
		hge->Gfx_RenderLine(x-4,y-4,x+4,y-4,0xffffffff);
		hge->Gfx_RenderLine(x-4,y-4,x-4,y+4,0xffffffff);
		hge->Gfx_RenderLine(x+4,y+4,x+4,y-4,0xffffffff);
		hge->Gfx_RenderLine(x+4,y+4,x-4,y+4,0xffffffff);
		//画尾结点
		x = hotbone->GetTailX(),y = hotbone->GetTailY();
		hge->Gfx_RenderLine(x-4,y-4,x+4,y-4,0xffffffff);
		hge->Gfx_RenderLine(x-4,y-4,x-4,y+4,0xffffffff);
		hge->Gfx_RenderLine(x+4,y+4,x+4,y-4,0xffffffff);
		hge->Gfx_RenderLine(x+4,y+4,x-4,y+4,0xffffffff);
		//画控制结点
		x = hotbone->GetX(),y = hotbone->GetY();
		hge->Gfx_RenderLine(x,y-3,x+3,y,0xffffffff);
		hge->Gfx_RenderLine(x,y-3,x-3,y,0xffffffff);
		hge->Gfx_RenderLine(x,y+3,x+3,y,0xffffffff);
		hge->Gfx_RenderLine(x,y+3,x-3,y,0xffffffff);
		for(UINT i= 0 ;i<hotbone->joints.size();i++)
		{

			x = hotbone->joints[i]->GetX(),y = hotbone->joints[i]->GetY();
			hge->Gfx_RenderLine(x,y-4,x-4,y+4,0xffffffff);
			hge->Gfx_RenderLine(x,y-4,x+4,y+4,0xffffffff);
			hge->Gfx_RenderLine(x-4,y+4,x+4,y+4,0xffffffff);
			if(hotbone->joints[i]->bindbone )
			{
				hge->Gfx_RenderLine(hotbone->joints[i]->bindbone->GetHeadX(),hotbone->joints[i]->bindbone->GetHeadY(),hotbone->joints[i]->bindbone->GetTailX(),hotbone->joints[i]->bindbone->GetTailY(),0xff0000ff);
			}
		}
		hgePoint dd = hotbone->GetOtherPoint();
		x = dd.x,y = dd.y;
		hge->Gfx_RenderLine(x,y-3,x+3,y,0xffffffff);
		hge->Gfx_RenderLine(x,y-3,x-3,y,0xffffffff);
		hge->Gfx_RenderLine(x,y+3,x+3,y,0xffffffff);
		hge->Gfx_RenderLine(x,y+3,x-3,y,0xffffffff);
	}
	if(hotjoint)
	{
		float x = hotjoint->GetX(),y = hotjoint->GetY();
		hge->Gfx_RenderLine(x,y-4,x-4,y+4,0xffff0000);
		hge->Gfx_RenderLine(x,y-4,x+4,y+4,0xffff0000);
		hge->Gfx_RenderLine(x-4,y+4,x+4,y+4,0xffff0000);
	}
	if(over)
	{
		hge->Gfx_RenderLine(over->GetHeadX(),over->GetHeadY(),over->GetTailX(),over->GetTailY(),0xffffff00);
		for(UINT i= 0 ;i<over->joints.size();i++)
		{
			float x = over->joints[i]->GetX(),y = over->joints[i]->GetY();
			hge->Gfx_RenderLine(x,y-4,x-4,y+4,0xffffffff);
			hge->Gfx_RenderLine(x,y-4,x+4,y+4,0xffffffff);
			hge->Gfx_RenderLine(x-4,y+4,x+4,y+4,0xffffffff);
		}
	}
	if(overj)
	{
		float x = overj->GetX(),y = overj->GetY();
		hge->Gfx_RenderLine(x,y-4,x-4,y+4,0xffffff00);
		hge->Gfx_RenderLine(x,y-4,x+4,y+4,0xffffff00);
		hge->Gfx_RenderLine(x-4,y+4,x+4,y+4,0xffffff00);
	}
	hge->Gfx_EndScene();
	return false;
}

// CAnimationEdView 消息处理程序

void CAnimationEdView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	// TODO: 在此添加专用代码和/或调用基类
	if ( hge!=0 )
	{
		hge->System_Shutdown();
		hge->Release();
		hge = 0;
	}

	hge = hgeCreate(HGE_VERSION);
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_TITLE, L"HGE Tutorial 01 - Minimal HGE application");
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_USESOUND, false);
	hge->System_SetState(HGE_HWNDPARENT, GetSafeHwnd());
	CRect rect;
	GetClientRect(&rect); // 获取当前客户区view大小
	hge->System_SetState(HGE_SCREENWIDTH, rect.Width());
	hge->System_SetState(HGE_SCREENHEIGHT, rect.Height());
	hge->System_SetState(HGE_SCREENBPP, 32);
	hge->System_SetState(HGE_LOGFILE, L"hge.log");
	hge->System_SetState(HGE_SHOWSPLASH, false);
	if(!hge->System_Initiate())
	{	
		// If HGE initialization failed show error message
		MessageBox(hge->System_GetErrorMessage(), L"Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		hge->Release();
		hge = 0;
	}

}

void CAnimationEdView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	if ( hge!=0 )
	{
		hge->System_Shutdown();
		hge->Release();
		hge = 0;
	}
}

void CAnimationEdView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	CRect rect;
	GetClientRect(&rect); // 获取当前客户区view大小
	//hge->System_SetState(HGE_SCREENWIDTH, rect.Width());
	//hge->System_SetState(HGE_SCREENHEIGHT, rect.Height());
	if(hge&&rect.Width()>0&&rect.Height()>0)
		::MoveWindow(hge->System_GetState(HGE_HWND),0,0,rect.Width(),rect.Height(),TRUE);
	
	// TODO: 在此处添加消息处理程序代码
}

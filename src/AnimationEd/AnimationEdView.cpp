
// AnimationEdView.cpp : CAnimationEdView 类的实现
//

#include "stdafx.h"
#include "AnimationEd.h"

#include "AnimationEdDoc.h"
#include "AnimationEdView.h"

#include "globaldata_animall.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
	// Continue execution
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);
	for(int i = 0;i<bones.size();i++)
	{
		hge->Gfx_RenderLine(bones[i]->head.x,bones[i]->head.y,bones[i]->tail.x,bones[i]->tail.y,0xffffffff);
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


// AnimationEdDoc.cpp : CAnimationEdDoc 类的实现
//

#include "stdafx.h"
#include "AnimationEd.h"

#include "AnimationEdDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAnimationEdDoc

IMPLEMENT_DYNCREATE(CAnimationEdDoc, CDocument)

BEGIN_MESSAGE_MAP(CAnimationEdDoc, CDocument)
END_MESSAGE_MAP()


// CAnimationEdDoc 构造/析构

CAnimationEdDoc::CAnimationEdDoc()
{
	// TODO: 在此添加一次性构造代码

}

CAnimationEdDoc::~CAnimationEdDoc()
{
}

BOOL CAnimationEdDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CAnimationEdDoc 序列化

void CAnimationEdDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CAnimationEdDoc 诊断

#ifdef _DEBUG
void CAnimationEdDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAnimationEdDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CAnimationEdDoc 命令

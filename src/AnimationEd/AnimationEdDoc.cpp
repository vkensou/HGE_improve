
// AnimationEdDoc.cpp : CAnimationEdDoc ���ʵ��
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


// CAnimationEdDoc ����/����

CAnimationEdDoc::CAnimationEdDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CAnimationEdDoc::~CAnimationEdDoc()
{
}

BOOL CAnimationEdDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CAnimationEdDoc ���л�

void CAnimationEdDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CAnimationEdDoc ���

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


// CAnimationEdDoc ����


// AnimationEdDoc.h : CAnimationEdDoc ��Ľӿ�
//


#pragma once


class CAnimationEdDoc : public CDocument
{
protected: // �������л�����
	CAnimationEdDoc();
	DECLARE_DYNCREATE(CAnimationEdDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CAnimationEdDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};



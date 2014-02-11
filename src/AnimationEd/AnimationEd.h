
// AnimationEd.h : AnimationEd Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include "hge.h"


// CAnimationEdApp:
// �йش����ʵ�֣������ AnimationEd.cpp
//

class CAnimationEdApp : public CWinAppEx
{
public:
	CAnimationEdApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnIdle(LONG lCount);
	afx_msg void OnNewSkeleton();
	afx_msg void OnNewAnim();
	afx_msg void OnNewBone();
	afx_msg void OnNewJoint();
	afx_msg void OnBindbone();
	afx_msg void OnReleasebind();
	afx_msg void On32783();
	afx_msg void OnDelBone();
	afx_msg void OnDelJoint();
	afx_msg void OnSaveSkeleton();
	afx_msg void OnLoadSkeleton();
};

extern CAnimationEdApp theApp;
extern HGE *hge;
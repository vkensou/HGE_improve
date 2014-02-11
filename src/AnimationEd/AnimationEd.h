
// AnimationEd.h : AnimationEd 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
#include "hge.h"


// CAnimationEdApp:
// 有关此类的实现，请参阅 AnimationEd.cpp
//

class CAnimationEdApp : public CWinAppEx
{
public:
	CAnimationEdApp();


// 重写
public:
	virtual BOOL InitInstance();

// 实现
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
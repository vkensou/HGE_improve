
// AnimationEd.h : AnimationEd Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


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

public:
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CAnimationEdApp theApp;

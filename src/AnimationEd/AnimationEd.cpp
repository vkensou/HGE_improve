
// AnimationEd.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "AnimationEd.h"
#include "MainFrm.h"

#include "AnimationEdDoc.h"
#include "AnimationEdView.h"

#include "globaldata_animall.h"
#include "globaldata_view.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAnimationEdApp

BEGIN_MESSAGE_MAP(CAnimationEdApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CAnimationEdApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	ON_COMMAND(ID_NEW_ANIM, &CAnimationEdApp::OnNewAnim)
	ON_COMMAND(ID_NEW_SKELETON, &CAnimationEdApp::OnNewSkeleton)
	ON_COMMAND(ID_NEW_BONE, &CAnimationEdApp::OnNewBone)
	ON_COMMAND(ID_NEW_JOINT, &CAnimationEdApp::OnNewJoint)
END_MESSAGE_MAP()


// CAnimationEdApp ����

CAnimationEdApp::CAnimationEdApp()
{

	m_bHiColorIcons = TRUE;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CAnimationEdApp ����

CAnimationEdApp theApp;
HGE *hge = 0;

// CAnimationEdApp ��ʼ��

BOOL CAnimationEdApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CAnimationEdDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CAnimationEdView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);



	// ������׼������DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� SDI Ӧ�ó����У���Ӧ�� ProcessShellCommand ֮����
	return TRUE;
}



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CAnimationEdApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CAnimationEdApp �Զ������/���淽��

void CAnimationEdApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CAnimationEdApp::LoadCustomState()
{
}

void CAnimationEdApp::SaveCustomState()
{
}

// CAnimationEdApp ��Ϣ�������




BOOL CAnimationEdApp::OnIdle(LONG lCount)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(hge)hge->System_Start();
	return CWinAppEx::OnIdle(lCount);
}

void CAnimationEdApp::OnNewAnim()
{
	// TODO: �ڴ���������������
}

void CAnimationEdApp::OnNewSkeleton()
{
	// TODO: �ڴ���������������
	
}

void CAnimationEdApp::OnNewBone()
{
	// TODO: �ڴ���������������
	hgeBone *nb = new hgeBone();
	nb->head.x = 100;
	nb->head.y = 100;
	nb->tail.x = 200;
	nb->tail.y = 200;

	bones.push_back(nb);
	g_leftview->RefreshBoneList();
}

void CAnimationEdApp::OnNewJoint()
{
	// TODO: �ڴ���������������
}

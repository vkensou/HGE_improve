
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
#include "animedit.h"

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
	ON_COMMAND(ID_BindBone, &CAnimationEdApp::OnBindbone)
	ON_COMMAND(ID_ReleaseBind, &CAnimationEdApp::OnReleasebind)
	ON_COMMAND(ID_32783, &CAnimationEdApp::On32783)
	ON_COMMAND(ID_DEL_BONE, &CAnimationEdApp::OnDelBone)
	ON_COMMAND(ID_DEL_JOINT, &CAnimationEdApp::OnDelJoint)
	ON_COMMAND(ID_SAVE_SKELETON, &CAnimationEdApp::OnSaveSkeleton)
	ON_COMMAND(ID_LOAD_SKELETON, &CAnimationEdApp::OnLoadSkeleton)
	ON_COMMAND(ID_CHANGEMODE, &CAnimationEdApp::OnChangemode)
	ON_COMMAND(ID_DIALOG_ANIMED, &CAnimationEdApp::OnDialogAnimed)
	ON_COMMAND(ID_ADD_ANIM, &CAnimationEdApp::OnAddAnim)
	ON_COMMAND(ID_DEL_ANIM, &CAnimationEdApp::OnDelAnim)
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

	nowskt = new hgeSkeleton;

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
	if(CWinAppEx::OnIdle(lCount))
		return TRUE;
	return TRUE;
}

void CAnimationEdApp::OnNewAnim()
{
	// TODO: �ڴ���������������
}

void CAnimationEdApp::OnNewSkeleton()
{
	// TODO: �ڴ���������������
	SelectBone(-1,true);
	g_leftview->bonelist.ResetContent();
	delete nowskt ;
	nowskt = new hgeSkeleton;
}

void CAnimationEdApp::OnNewBone()
{
	// TODO: �ڴ���������������
	//hgeBone *nb = new hgeBone(100,100,200,200);
	//bones.push_back(nb);
	if(!editmode)return;
	mode = 2;
	//int a = nowskt->AddBone();
	//g_leftview->RefreshBoneList();
	//SelectBone(a,true);
}

void CAnimationEdApp::OnNewJoint()
{
	// TODO: �ڴ���������������
	if(hotbone==0 || !editmode)return ;
	hotbone->AddJoint();
	g_leftview2->RefreshJointList();
	SelectJoint(hotbone->joints.size()+3,true);
}

void CAnimationEdApp::OnBindbone()
{
	// TODO: �ڴ���������������
	if(hotjoint==0 || !editmode)return;
	if(hotjoint->bindbone)return;
	mode = 1;
}

void CAnimationEdApp::OnReleasebind()
{
	// TODO: �ڴ���������������
	if(hotjoint==0 || !editmode)return;
	hotjoint->ReleaseBind();
}

void CAnimationEdApp::On32783()
{
	// TODO: �ڴ���������������
	g_bindshow->ShowWindow(SW_SHOW);
}

void CAnimationEdApp::OnDelBone()
{
	// TODO: �ڴ���������������
	if(hotbone)
	{
		nowskt->DelBone(hotbone);
		hotbone = 0;
		g_leftview->RefreshBoneList();
		SelectBone(-1);
	}
}

void CAnimationEdApp::OnDelJoint()
{
	// TODO: �ڴ���������������
	if(hotjoint)
	{
		hotbone->DelJoint(hotjoint);
		hotjoint = 0;
		g_leftview2->RefreshJointList();
		SelectJoint(-1);
	}
}

void CAnimationEdApp::OnSaveSkeleton()
{
	// TODO: �ڴ���������������
	CFileDialog dlgFile(FALSE, NULL, NULL, OFN_HIDEREADONLY, L"�����ļ�(*.skt)|*.skt|", NULL);

    if (dlgFile.DoModal())
	{
		CString path = dlgFile.GetPathName();
		if(path==L"")return;
		if(path.Right(4)!=L".skt")path+=L".skt";
		nowskt->Save(path.GetBuffer());
		path.ReleaseBuffer();
	}
}

void CAnimationEdApp::OnLoadSkeleton()
{
	// TODO: �ڴ���������������
	CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, L"�����ļ�(*.skt)|*.skt|", NULL);

    if (dlgFile.DoModal())
	{
		CString path = dlgFile.GetPathName();
		if(path==L"")return;
		nowskt->Load(path.GetBuffer());
		path.ReleaseBuffer();
		g_leftview->RefreshBoneList();
	}
}

void CAnimationEdApp::OnChangemode()
{
	// TODO: �ڴ���������������
	editmode = !editmode;
	if(!editmode && !nowskt->CheckReady())
		editmode = !editmode;

	g_rightview->SetPropertyPage(-1);
	SelectBone(-1);
	nowskt->SetMode(editmode);
	g_downview->RefreshData();
	mode = 0;
	nowskt->Stop();
	if(editmode)
	{
		AfxGetMainWnd()->SetWindowTextW(L"�����༭�� - ����ģʽ");
	}
	else
	{
		AfxGetMainWnd()->SetWindowTextW(L"�����༭�� - ����ģʽ");
		nowskt->SetPosition(0,0);
	}
}

void CAnimationEdApp::OnDialogAnimed()
{
	// TODO: �ڴ���������������
	if(!editmode)
	{
		CAnimEdit ae;
		
		if(ae.DoModal() == IDOK)
		{
			nowskt->SetFrameNum(ae.fnum);
			nowskt->SetFps(ae.sfps);
			g_downview->RefreshData(nowskt->GetAnimIndex());
		}
	}
}

void CAnimationEdApp::OnAddAnim()
{
	// TODO: �ڴ���������������
	g_downview->RefreshData(nowskt->AddAnim());
}

void CAnimationEdApp::OnDelAnim()
{
	// TODO: �ڴ���������������
	nowskt->DelAnim(nowskt->GetAnimIndex());
	g_downview->RefreshData();
}

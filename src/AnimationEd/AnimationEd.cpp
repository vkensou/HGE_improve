
// AnimationEd.cpp : 定义应用程序的类行为。
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
	// 基于文件的标准文档命令
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


// CAnimationEdApp 构造

CAnimationEdApp::CAnimationEdApp()
{

	m_bHiColorIcons = TRUE;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CAnimationEdApp 对象

CAnimationEdApp theApp;
HGE *hge = 0;

// CAnimationEdApp 初始化

BOOL CAnimationEdApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CAnimationEdDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CAnimationEdView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);



	// 分析标准外壳命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// 仅当具有后缀时才调用 DragAcceptFiles
	//  在 SDI 应用程序中，这应在 ProcessShellCommand 之后发生

	nowskt = new hgeSkeleton;

	return TRUE;
}



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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

// 用于运行对话框的应用程序命令
void CAnimationEdApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CAnimationEdApp 自定义加载/保存方法

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

// CAnimationEdApp 消息处理程序




BOOL CAnimationEdApp::OnIdle(LONG lCount)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(hge)hge->System_Start();
	if(CWinAppEx::OnIdle(lCount))
		return TRUE;
	return TRUE;
}

void CAnimationEdApp::OnNewAnim()
{
	// TODO: 在此添加命令处理程序代码
}

void CAnimationEdApp::OnNewSkeleton()
{
	// TODO: 在此添加命令处理程序代码
	SelectBone(-1,true);
	g_leftview->bonelist.ResetContent();
	delete nowskt ;
	nowskt = new hgeSkeleton;
}

void CAnimationEdApp::OnNewBone()
{
	// TODO: 在此添加命令处理程序代码
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
	// TODO: 在此添加命令处理程序代码
	if(hotbone==0 || !editmode)return ;
	hotbone->AddJoint();
	g_leftview2->RefreshJointList();
	SelectJoint(hotbone->joints.size()+3,true);
}

void CAnimationEdApp::OnBindbone()
{
	// TODO: 在此添加命令处理程序代码
	if(hotjoint==0 || !editmode)return;
	if(hotjoint->bindbone)return;
	mode = 1;
}

void CAnimationEdApp::OnReleasebind()
{
	// TODO: 在此添加命令处理程序代码
	if(hotjoint==0 || !editmode)return;
	hotjoint->ReleaseBind();
}

void CAnimationEdApp::On32783()
{
	// TODO: 在此添加命令处理程序代码
	g_bindshow->ShowWindow(SW_SHOW);
}

void CAnimationEdApp::OnDelBone()
{
	// TODO: 在此添加命令处理程序代码
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
	// TODO: 在此添加命令处理程序代码
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
	// TODO: 在此添加命令处理程序代码
	CFileDialog dlgFile(FALSE, NULL, NULL, OFN_HIDEREADONLY, L"骨骼文件(*.skt)|*.skt|", NULL);

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
	// TODO: 在此添加命令处理程序代码
	CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, L"骨骼文件(*.skt)|*.skt|", NULL);

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
	// TODO: 在此添加命令处理程序代码
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
		AfxGetMainWnd()->SetWindowTextW(L"动画编辑器 - 骨骼模式");
	}
	else
	{
		AfxGetMainWnd()->SetWindowTextW(L"动画编辑器 - 动画模式");
		nowskt->SetPosition(0,0);
	}
}

void CAnimationEdApp::OnDialogAnimed()
{
	// TODO: 在此添加命令处理程序代码
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
	// TODO: 在此添加命令处理程序代码
	g_downview->RefreshData(nowskt->AddAnim());
}

void CAnimationEdApp::OnDelAnim()
{
	// TODO: 在此添加命令处理程序代码
	nowskt->DelAnim(nowskt->GetAnimIndex());
	g_downview->RefreshData();
}

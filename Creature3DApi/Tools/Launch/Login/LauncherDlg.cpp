// LauncherDlg.cpp : implementation file
//
//#include <Windows.h>
#include "stdafx.h"
#include "Launcher.h"
#include "LauncherDlg.h"
#include "resource.h"
#include <sys/stat.h>
#include <fstream>
#include "SystemInfo.h"
#include <gl/GL.h>
using namespace std;
#pragma comment(lib, "Opengl32.lib") 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CWebBrowser, CHtmlView)

CWebBrowser::CWebBrowser()
: m_bContextMenuEnabled(TRUE)
{
}

CWebBrowser::~CWebBrowser()
{
}

BEGIN_MESSAGE_MAP(CWebBrowser, CHtmlView)
	ON_WM_DESTROY()
	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()


// CWebBrowser ��Ϣ�������
void CWebBrowser::OnTitleChange(LPCTSTR lpszText)
{
	// TODO: �ڴ����ר�ô����/����û���

	CHtmlView::OnTitleChange(lpszText);
}

void CWebBrowser::OnDocumentComplete(LPCTSTR lpszURL)
{
	// TODO: �ڴ����ר�ô����/����û���

	CHtmlView::OnDocumentComplete(lpszURL);
}


void CWebBrowser::OnDestroy()
{
	m_pBrowserApp.Release();

	m_wndBrowser.DestroyWindow();

	CWnd::OnDestroy();
}

int CWebBrowser::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void CWebBrowser::PostNcDestroy()
{
	//��ֹ��ɾ��
	//CHtmlView::PostNcDestroy();
}

BOOL CWebBrowser::PreTranslateMessage(MSG* pMsg)
{
	if (WM_RBUTTONUP == pMsg->message || WM_CONTEXTMENU == pMsg->message)
	{
		if (!IsContextMenuEnabled()) //�����Ҽ��˵��ͼ��̲˵���
		{
			return TRUE;
		}
	}

	return CHtmlView::PreTranslateMessage(pMsg);
}

HRESULT CWebBrowser::OnGetHostInfo(DOCHOSTUIINFO *pInfo)
{
	pInfo->dwFlags |= DOCHOSTUIFLAG_SCROLL_NO | DOCHOSTUIFLAG_NO3DBORDER;
	return S_OK;
}

#define _USER_NAME_	L"?user="
void CWebBrowser::OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags, LPCTSTR lpszTargetFrameName, CByteArray& baPostedData, LPCTSTR lpszHeaders, BOOL* pbCancel)
{
	if (wcsstr(lpszURL, _USER_NAME_))
	{
		wchar_t szBuf[256] = {0};
		wcscpy(szBuf, lpszURL);
		wchar_t * pTmp = wcsstr(szBuf, _USER_NAME_);
		if (pTmp)
		{
			pTmp += wcslen(_USER_NAME_);

			//ת���ַ���
			char szTmp[256] = {0};
			WideCharToMultiByte( CP_ACP, 0, pTmp, -1, szTmp, 255, NULL, NULL );
			CString strPath = m_strGameDir;
			//AfxMessageBox(m_strGameDir);
			strPath += L"/jxjlogin.dat";
			FILE * pFile = _wfopen(strPath, L"wb");
			if (NULL == pFile)
			{
				AfxMessageBox(L"jxjlogin.dat д��ʧ��");
				return ;
			}

			fwrite(szTmp, strlen(szTmp), 1, pFile);
			fclose(pFile);

			::Sleep(1);

			//������Ϸ
			STARTUPINFO si;
			PROCESS_INFORMATION pi;
			ZeroMemory( &si, sizeof(si) );	// ��������Ϣ�ṹ����
			si.cb = sizeof(si);
			ZeroMemory( &pi, sizeof(pi) );	// ��������Ϣ�ṹ����

			//���԰汾��·��
			strPath = m_strGameDir;
			strPath += L"/Launcher.exe";
			//AfxMessageBox(strPath);
			CreateProcess(strPath, NULL, NULL, NULL, FALSE, 0, NULL, m_strGameDir, &si, &pi);

			//�˳�����
			ExitProcess(0);
		}
	}
	else
		CHtmlView::OnBeforeNavigate2(lpszURL, nFlags, lpszTargetFrameName, baPostedData, lpszHeaders, pbCancel);
}

HRESULT CWebBrowser::OnTranslateUrl(DWORD dwTranslate,
									OLECHAR* pchURLIn, OLECHAR** ppchURLOut)
{
	//AfxMessageBox(pchURLIn);
	if( wcslen(pchURLIn) == 0 || wcsstr(pchURLIn, _USER_NAME_) ||
		wcsstr(pchURLIn, L"micro") ||
		wcsstr(pchURLIn, L"4game") )
		return S_OK;
	if(	wcsstr(pchURLIn, L"http") )
	{
		ShellExecute(NULL,L"open",pchURLIn,NULL,NULL,SW_SHOW);
	}
	return S_OK;
}
//////////////////////////////////////////////////////////////////////////

// CLauncherDlg dialog
CLauncherDlg::CLauncherDlg(CWnd* pParent /*=NULL*/)
	: CDialogSK(CLauncherDlg::IDD, pParent)
	, m_Download(this)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bQuitProcess = FALSE;
	m_uCurDownloadSize = 0;
	m_uCurDownloadFileSize = 1;
	m_bDownloadFinish = FALSE;

	m_strModule[0] = 0;

	m_btDownloadStage = 0;
}
CLauncherDlg::~CLauncherDlg()
{
	m_Download.Uninit();
}

void CLauncherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogSK::DoDataExchange(pDX);

	//DDX_Control(pDX, IDC_START_GAME, m_btnStartGame);
	DDX_Control(pDX, IDC_BUTTON_MINI, m_btnMiniDlg);
	DDX_Control(pDX, IDC_BUTTON_QUIT, m_btnQuit);
	DDX_Control(pDX, IDC_PROGRESS1, m_Process1);
	DDX_Control(pDX, IDC_BUTTON_SETTING, m_btnVideoSetting);
	DDX_Control(pDX, IDC_CHECK1, m_btnVideoLevel[0]);
	DDX_Control(pDX, IDC_CHECK2, m_btnVideoLevel[1]);
	DDX_Control(pDX, IDC_CHECK3, m_btnVideoLevel[2]);
	DDX_Control(pDX, IDC_CHECK4, m_btnVideoLevel[3]);
	DDX_Control(pDX, IDC_CHECK5, m_btnVideoLevel[4]);
	DDX_Control(pDX, IDC_BUTTON_SELECT, m_btnSelect);
	DDX_Control(pDX, IDC_BUTTON_SETTING_CANCLE, m_btnSelectCancel);
	//DDX_Control(pDX, IDC_INFO, m_staticText);
}

BEGIN_MESSAGE_MAP(CLauncherDlg, CDialogSK)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	//ON_BN_CLICKED(IDC_START_GAME, &CLauncherDlg::OnBnClickedStartGame)
	ON_BN_CLICKED(IDC_BUTTON_MINI, &CLauncherDlg::OnBnClickedButtonMini)
	ON_BN_CLICKED(IDC_BUTTON_QUIT, &CLauncherDlg::OnBnClickedButtonQuit)
	ON_BN_CLICKED(IDC_BUTTON_SETTING, &CLauncherDlg::OnBnClickedButtonVideoSetting)
	ON_BN_CLICKED(IDC_CHECK1,  &CLauncherDlg::OnBnClickedButtonLevelVeryLow)
	ON_BN_CLICKED(IDC_CHECK2, &CLauncherDlg::OnBnClickedButtonLevelLow)
	ON_BN_CLICKED(IDC_CHECK3, &CLauncherDlg::OnBnClickedButtonLevelNormal)
	ON_BN_CLICKED(IDC_CHECK4,  &CLauncherDlg::OnBnClickedButtonLevelHigh)
	ON_BN_CLICKED(IDC_CHECK5,  &CLauncherDlg::OnBnClickedButtonLevelVeryHigh)
	ON_BN_CLICKED(IDC_BUTTON_SELECT,  &CLauncherDlg::OnBnClickedButtonSelect)
	ON_BN_CLICKED(IDC_BUTTON_SETTING_CANCLE,  &CLauncherDlg::OnBnClickedButtonCancel)
	ON_WM_TIMER()
	//ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &CLauncherDlg::OnNMCustomdrawProgress1)
END_MESSAGE_MAP()

void CLauncherDlg::CreateDesktopShortCut(const wchar_t * pDir)
{
	wchar_t szBuf[255] = {0};
	wsprintf(szBuf, L"%s/Login.exe", pDir);

	HRESULT hr = CoInitialize(NULL);
	if (SUCCEEDED(hr))
	{
		IShellLink *pisl;
		hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&pisl);
		if (SUCCEEDED(hr))
		{
			IPersistFile* pIPF;

			//����������Ҫ������ݷ�ʽ��ԭʼ�ļ���ַ
			pisl->SetPath(szBuf);
			pisl->SetWorkingDirectory(pDir);
			hr = pisl->QueryInterface(IID_IPersistFile, (void**)&pIPF);
			if (SUCCEEDED(hr))
			{

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////

				//����������Ҫ������ݷ�ʽ��Ŀ���ַ
				TCHAR szDesktopPath[MAX_PATH] = {0}, szPath[MAX_PATH];
				SHGetSpecialFolderPath(NULL, szDesktopPath, CSIDL_DESKTOP, FALSE);
				wsprintf(szPath, L"%s/���Ǿ�.lnk", szDesktopPath);
				DeleteFile(szPath);

				pIPF->Save(szPath, FALSE);
				pIPF->Release();
			}
			pisl->Release();
		}
		CoUninitialize();
	}
}

// CLauncherDlg message handlers
BOOL CLauncherDlg::OnInitDialog()
{
	CDialogSK::OnInitDialog();

	//CString curDir = GetCurrentUninstallDir();
	//�����ж��������ж��
// 	if (2 == __argc)
// 	{
// 		if(GetJXJProgressExit())
// 		{
// 			if (IDYES == MessageBox(L"�Ƿ����ж�ؽ��Ǿ���", L"��ʾ", MB_YESNO))
// 			{
// 				if(UninstallGame())
// 					AfxMessageBox(L"ж�����");
// 				else
// 					AfxMessageBox(L"ж��ʧ��,���ֶ�ж��!");
// 				ExitProcess(0);
// 				return FALSE;
// 			}
// 		}
// 		else
// 		{
// 			MessageBox(L"���Ǿ������������У����ȹرճ�������ԣ�",L"��ʾ",MB_OK|MB_ICONERROR);
// 			ExitProcess(0);
// 			return FALSE;
// 		}
// 	}

	char *web = NULL;
	struct stat buf;
	if(!stat("login.ini", &buf ))
	{
		std::ifstream fin("login.ini",std::ios::in|std::ios::binary);
		if(fin)
		{
			fin.seekg(0, std::ios::end);
			int length = fin.tellg();
			web = new char[length+1];
			memset(web,0,length+1);
			fin.seekg(0, std::ios::beg);
			fin.read(web, length);
			fin.close();
		}
	}
	if(web)
	{
		m_loginurl = web;
		delete [] web;
		web = NULL;
	}
	if(m_loginurl.IsEmpty())
		m_loginurl = "http://www.quegame.com/micro/";

	CRect stRect;
	GetWindowRect(stRect);
	MoveWindow(stRect.top, stRect.left, 1035, 590);
	//MoveWindow(stRect.top, stRect.left, 1032, 536);

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// ���öԻ��򱳾���Ϣ
	EnableEasyMove();						// �����ƶ�
	SetBitmap(L"LauncherDlg.bmp");
	SetStyle (LO_RESIZE);					// ʹ�Ի����С�ʺ�λͼ��С
	SetTransparentColor(RGB(64, 64, 64));	// ����͸��ɫ
	//SetTransparentColor(RGB(0, 255, 0));	// ����͸��ɫ
	//
	SetWindowText(L"���Ǿ���װ����");
	//�����˳���ťͼƬ
	m_btnQuit.SetBitmaps(IDB_BITMAP_QUIT_1, RGB(0, 255, 0), IDB_BITMAP_QUIT_3, RGB(0, 255, 0));
	m_btnQuit.SetAlign(CButtonST::ST_ALIGN_OVERLAP, FALSE);
	m_btnQuit.SetPressedStyle(CButtonST::BTNST_PRESSED_LEFTRIGHT, FALSE);
	m_btnQuit.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 255, 255));
	m_btnQuit.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
	m_btnQuit.SizeToContent();
	m_btnQuit.DrawBorder(FALSE, FALSE);
	m_btnQuit.MoveWindow(981, 80, 25, 26);
	//m_btnQuit.MoveWindow(894, 110, 23, 23);

	//������С����ťͼƬ
	m_btnMiniDlg.SetBitmaps(IDB_BITMAP_MINI_1, RGB(0, 255, 0), IDB_BITMAP_MINI_3, RGB(0, 255, 0));
	m_btnMiniDlg.SetAlign(CButtonST::ST_ALIGN_OVERLAP, FALSE);
	m_btnMiniDlg.SetPressedStyle(CButtonST::BTNST_PRESSED_LEFTRIGHT, FALSE);
	m_btnMiniDlg.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 255, 255));
	m_btnMiniDlg.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
	m_btnMiniDlg.SizeToContent();
	m_btnMiniDlg.DrawBorder(FALSE, FALSE);
	m_btnMiniDlg.MoveWindow(951, 80, 25, 26);
	//m_btnMiniDlg.MoveWindow(842, 116, 31, 9);

	//������ʾ���ð�ť
	m_btnVideoSetting.SetBitmaps(IDB_BITMAP_SETTING_3, RGB(0, 255, 0), IDB_BITMAP_SETTING_1, RGB(0, 255, 0));
	m_btnVideoSetting.SetAlign(CButtonST::ST_ALIGN_OVERLAP, FALSE);
	m_btnVideoSetting.SetPressedStyle(CButtonST::BTNST_PRESSED_LEFTRIGHT, FALSE);
	m_btnVideoSetting.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 255, 255));
	m_btnVideoSetting.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
	m_btnVideoSetting.SizeToContent();
	m_btnVideoSetting.DrawBorder(FALSE, FALSE);
	m_btnVideoSetting.MoveWindow(829, 81, 103, 23);
	//m_btnVideoSetting.MoveWindow(22, 298, 81, 81);

	//������ʾ����ģʽ
	//99,313    267,313    435,313    603,313   771.313
	m_btnVideoLevel[0].SetBitmaps(IDB_BITMAP_QUAD_1, RGB(0, 255, 0), IDB_BITMAP_QUAD_3, RGB(0, 255, 0));
	m_btnVideoLevel[0].SetAlign(CButtonST::ST_ALIGN_OVERLAP, FALSE);
	m_btnVideoLevel[0].SetPressedStyle(CButtonST::BTNST_PRESSED_LEFTRIGHT, FALSE);
	m_btnVideoLevel[0].SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 255, 255));
	m_btnVideoLevel[0].SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
	m_btnVideoLevel[0].SizeToContent();
	m_btnVideoLevel[0].DrawBorder(FALSE, FALSE);
	m_btnVideoLevel[0].MoveWindow(101, 313, 172, 172);
	//m_btnVideoLevel[0].MoveWindow(127, 221, 138, 138);
	m_btnVideoLevel[0].ShowWindow(SW_HIDE);


	m_btnVideoLevel[1].SetBitmaps(IDB_BITMAP_QUAD_1, RGB(0, 255, 0), IDB_BITMAP_QUAD_3, RGB(0, 255, 0));
	m_btnVideoLevel[1].SetAlign(CButtonST::ST_ALIGN_OVERLAP, FALSE);
	m_btnVideoLevel[1].SetPressedStyle(CButtonST::BTNST_PRESSED_LEFTRIGHT, FALSE);
	m_btnVideoLevel[1].SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 255, 255));
	m_btnVideoLevel[1].SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
	m_btnVideoLevel[1].SizeToContent();
	m_btnVideoLevel[1].DrawBorder(FALSE, FALSE);
	m_btnVideoLevel[1].MoveWindow(269, 313, 172, 172);
	//m_btnVideoLevel[1].MoveWindow(261, 221, 138, 138);
	m_btnVideoLevel[1].ShowWindow(SW_HIDE);

	m_btnVideoLevel[2].SetBitmaps(IDB_BITMAP_QUAD_1, RGB(0, 255, 0), IDB_BITMAP_QUAD_3, RGB(0, 255, 0));
	m_btnVideoLevel[2].SetAlign(CButtonST::ST_ALIGN_OVERLAP, FALSE);
	m_btnVideoLevel[2].SetPressedStyle(CButtonST::BTNST_PRESSED_LEFTRIGHT, FALSE);
	m_btnVideoLevel[2].SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 255, 255));
	m_btnVideoLevel[2].SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
	m_btnVideoLevel[2].SizeToContent();
	m_btnVideoLevel[2].DrawBorder(FALSE, FALSE);
	m_btnVideoLevel[2].MoveWindow(437, 313, 172, 172);
	//m_btnVideoLevel[2].MoveWindow(396, 221, 138, 138);
	m_btnVideoLevel[2].ShowWindow(SW_HIDE);

	m_btnVideoLevel[3].SetBitmaps(IDB_BITMAP_QUAD_1, RGB(0, 255, 0), IDB_BITMAP_QUAD_3, RGB(0, 255, 0));
	m_btnVideoLevel[3].SetAlign(CButtonST::ST_ALIGN_OVERLAP, FALSE);
	m_btnVideoLevel[3].SetPressedStyle(CButtonST::BTNST_PRESSED_LEFTRIGHT, FALSE);
	m_btnVideoLevel[3].SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 255, 255));
	m_btnVideoLevel[3].SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
	m_btnVideoLevel[3].SizeToContent();
	m_btnVideoLevel[3].DrawBorder(FALSE, FALSE);
	m_btnVideoLevel[3].MoveWindow(605, 313, 172, 172);
	//m_btnVideoLevel[3].MoveWindow(531, 221, 138, 138);
	m_btnVideoLevel[3].ShowWindow(SW_HIDE);

	m_btnVideoLevel[4].SetBitmaps(IDB_BITMAP_QUAD_1, RGB(0, 255, 0), IDB_BITMAP_QUAD_3, RGB(0, 255, 0));
	m_btnVideoLevel[4].SetAlign(CButtonST::ST_ALIGN_OVERLAP, FALSE);
	m_btnVideoLevel[4].SetPressedStyle(CButtonST::BTNST_PRESSED_LEFTRIGHT, FALSE);
	m_btnVideoLevel[4].SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 255, 255));
	m_btnVideoLevel[4].SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
	m_btnVideoLevel[4].SizeToContent();
	m_btnVideoLevel[4].DrawBorder(FALSE, FALSE);
	m_btnVideoLevel[4].MoveWindow(773, 313, 172, 172);
	//m_btnVideoLevel[4].MoveWindow(664, 221, 138, 138);
	m_btnVideoLevel[4].ShowWindow(SW_HIDE);

	//����ģʽѡ��ť
	m_btnSelect.SetBitmaps(IDB_BITMAP_SELECT_3, RGB(0, 255, 0), IDB_BITMAP_SELECT_1, RGB(0, 255, 0));
	m_btnSelect.SetAlign(CButtonST::ST_ALIGN_OVERLAP, FALSE);
	m_btnSelect.SetPressedStyle(CButtonST::BTNST_PRESSED_LEFTRIGHT, FALSE);
	m_btnSelect.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 255, 255));
	m_btnSelect.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
	m_btnSelect.SizeToContent();
	m_btnSelect.DrawBorder(FALSE, FALSE);
	m_btnSelect.MoveWindow(370, 500, 106, 27);
	//m_btnSelect.MoveWindow(300, 381, 121, 42);
	m_btnSelect.ShowWindow(SW_HIDE);
	//����ģʽȡ����ť
	m_btnSelectCancel.SetBitmaps(IDB_BITMAP_CANCEL_3, RGB(0, 255, 0), IDB_BITMAP_CANCEL_1, RGB(0, 255, 0));
	m_btnSelectCancel.SetAlign(CButtonST::ST_ALIGN_OVERLAP, FALSE);
	m_btnSelectCancel.SetPressedStyle(CButtonST::BTNST_PRESSED_LEFTRIGHT, FALSE);
	m_btnSelectCancel.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 255, 255));
	m_btnSelectCancel.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
	m_btnSelectCancel.SizeToContent();
	m_btnSelectCancel.DrawBorder(FALSE, FALSE);
	m_btnSelectCancel.MoveWindow(568, 500, 106, 27);
	//m_btnSelectCancel.MoveWindow(514, 381, 121, 42);
	m_btnSelectCancel.ShowWindow(SW_HIDE);
	//�����ҳ
	const int nXStart = 38, nYStart = 120;
	//const int nXStart = 93, nYStart = 165;
	ModifyStyleEx( WS_EX_CLIENTEDGE, 0, 0 );	//��ֹCHtmlView������ı߿�
	m_html.Create(NULL, NULL, (WS_CHILD | WS_VISIBLE), CRect(nXStart, nYStart, nXStart + 930, nYStart + 395), this, 1201);
	//m_html.Create(NULL, NULL, (WS_CHILD | WS_VISIBLE), CRect(nXStart, nYStart, nXStart + 753, nYStart + 294), this, 1201);
	//m_html.Navigate(L"http://www.quegame.com/login/");
	//m_html.Navigate(L"http://jxj.quegame.com/download/trunk/login/tpl/index.html");
	m_htmlWait.Create(NULL, NULL, (WS_CHILD | WS_VISIBLE), CRect(nXStart, nYStart, nXStart + 930, nYStart + 395), this, 1201);
	//m_htmlWait.Create(NULL, NULL, (WS_CHILD | WS_VISIBLE), CRect(nXStart, nYStart, nXStart + 753, nYStart + 294), this, 1201);
	m_htmlWait.ShowWindow(SW_HIDE);
	m_isWait = FALSE;
	
	m_Process1.MoveWindow(72, 552, 965 - 72, 565 - 552);
	//m_Process1.MoveWindow(113, 465, 814 - 113, 478 - 465);
	m_Process1.SetRange(0, 100);
	m_Process1.ShowWindow(SW_HIDE);

	//m_staticText.MoveWindow(72+100,552,965-72,565-552);
	//m_staticText.ShowWindow(SW_HIDE);
	
	SetTimer(1, 100, NULL);

	m_Download.Init();
	DoInitCheckGame();

	return TRUE;  // return TRUE  unless you set the focus to a control
}


bool CLauncherDlg::DoInitCheckUpdate()
{
	bool bUpdate = false;
	CString strLocalPath(m_strModule);
	strLocalPath += L"/LoginExeVersionInfo.ini";
	//��ȡ���ذ汾��Ϣ
	int nlocalbgValue = GetPrivateProfileInt(L"VersionInfo", L"DlgBackVersionNumber", 0, strLocalPath);
	int nlocalexeValue = GetPrivateProfileInt(L"VersionInfo", L"LoginExeVersionNumber", 0, strLocalPath);
	//����Ini�ļ�
	bool isSucess = true;
	int tryCount = 0;
	do 
	{
		if(tryCount>=TRY_DOWNLOAD_MAXCOUNT)
		{
			MessageBox(L"�ļ�LoginExeVersionInfo.ini����ʧ�ܣ����Ժ����ԣ�");
			break;
		}
		isSucess = m_Download.DownloadFile(L"http://jxj.quegame.com/download/LoginExeVersionInfo.ini", strLocalPath, false);
		tryCount++;
		
		char *path ="d:/";
		debuglog(path,"%s:%d\n","LoginExeVersionInfo.ini",tryCount);
	} while (!isSucess);
	

	//���ȿ����Ƿ񱳾���ͼ�и��£�
	int nValue = GetPrivateProfileInt(L"VersionInfo", L"DlgBackVersionNumber", 0, strLocalPath);
	
	wstring strTmp = m_strModule;
	strTmp += L"/LauncherDlg.bmp";
	WIN32_FIND_DATA stFindFileData;
	ZeroMemory(&stFindFileData, sizeof(WIN32_FIND_DATA));
	HANDLE hFile = FindFirstFile(strTmp.c_str(), &stFindFileData);
	if (INVALID_HANDLE_VALUE == hFile || nlocalbgValue < nValue)
	{
		//���ص�¼��
		strLocalPath = m_strModule;
		strLocalPath += L"/LauncherDlg.bmp";

		isSucess = true;
		tryCount = 0;
		do 
		{
			if(tryCount>=TRY_DOWNLOAD_MAXCOUNT)
			{
				MessageBox(L"�ļ�LauncherDlg.bmp����ʧ�ܣ����Ժ����ԣ�");
				break;
			}
			isSucess = m_Download.DownloadFile(L"http://jxj.quegame.com/download/LauncherDlg.bmp", strLocalPath, false);
			tryCount++;

			char *path ="c:/";
			debuglog(path,"%s:%d\n","LauncherDlg.bmp",tryCount);
		} while (!isSucess);
	}
	::FindClose ( hFile );
	//�Ƚϰ汾
	strLocalPath = m_strModule;
	strLocalPath += L"/LoginExeVersionInfo.ini";
	nValue = GetPrivateProfileInt(L"VersionInfo", L"LoginExeVersionNumber", 0, strLocalPath);
	if (nlocalexeValue < nValue)
	{
		//if (IDYES == MessageBox(L"��¼���и��£��Ƿ���£�", L"��ʾ", MB_YESNO))
		{
			//���ص�¼��
			strLocalPath = m_strModule;
			strLocalPath += L"/TmpLogin.exe";


			isSucess = true;
			tryCount = 0;
			do 
			{
				if(tryCount>=TRY_DOWNLOAD_MAXCOUNT)
				{
					MessageBox(L"�ļ���Login.exe������ʧ�ܣ����Ժ����ԣ�");
					break;
				}
				isSucess = m_Download.DownloadFile(L"http://jxj.quegame.com/download/Login.exe", strLocalPath, false);
				tryCount++;

				char *path ="c:/";
				debuglog(path,"%s:%d\n","WebLauncher.exe",tryCount);
			} while (!isSucess);

			//ʹ�ó�����µ�¼��
			PROCESS_INFORMATION pi;
			STARTUPINFO si; //This is an [in] parameter
			ZeroMemory(&si, sizeof(si));
			si.cb = sizeof si; //Only compulsory field
			si.dwFlags = STARTF_USESHOWWINDOW;
			si.wShowWindow = SW_HIDE;
			wchar_t buf[256] = {0};
			swprintf(buf, L"%s/update.exe", m_strModule);
			
			if(CreateProcess(NULL, buf, NULL, NULL, FALSE, 0, NULL, m_strModule, &si, &pi))
			{
				//MessageBox(buf);
				//WaitForSingleObject(pi.hProcess,INFINITE);
				CloseHandle(pi.hThread);
				CloseHandle(pi.hProcess);
			}

			ExitProcess(0);
		}
	}

	//�Ƚ���Ϸ�İ汾��������ھ�ж��
	nValue = GetPrivateProfileInt(L"VersionInfo", L"VersionNumber", 0, strLocalPath);

	//��ȡ�ͻ��˰汾��Ϣ
	strLocalPath = m_strModule;
	strLocalPath += L"/jxjversion.ini";
	FILE * pFile = _wfopen(strLocalPath, L"rb");
	if (NULL == pFile)
		return bUpdate;
	fseek(pFile,0,SEEK_END);
	int nFileLen = ftell(pFile);
	fseek(pFile,0,SEEK_SET);
	char szReadBuf[256] = {0};
	if (nFileLen > 255)
		nFileLen = 255;
	fread(szReadBuf, nFileLen, 1, pFile);
	fclose(pFile);

	char * pTmp = strstr(szReadBuf, "version:");
	if (pTmp)
	{
		int nCurGameVersion = atoi(szReadBuf + strlen("version:"));
		if (nCurGameVersion < nValue)
		{
			m_htmlWait.ShowWindow(SW_NORMAL);
			m_htmlWait.Navigate(L"http://www.quegame.com/micro/waiting.php");
			m_html.ShowWindow(SW_HIDE);
			m_isWait = TRUE; 

			bUpdate = true;
			//ж����Ϸ
			if(IDOK == MessageBox(L"��⵽�����Ϸ�汾��ʱ��δ���£�Ϊȷ����Ϸ�ܹ��������У������ֶ�ж�س���"));
			{
				m_uidlg.DoModal();
			}
		}
	}

	return bUpdate;
}

#define FILE_SEPARATOR	L"/"
#define FILE_APP_NAME	L"Login.exe"
void CLauncherDlg::CreateStartMenu()
{
    TCHAR chStartupFolder[MAX_PATH];
    SHGetSpecialFolderPath(this->GetSafeHwnd(), chStartupFolder,CSIDL_PROGRAMS,FALSE);
    CString csStartupFolder = chStartupFolder;
    csStartupFolder.Append(FILE_SEPARATOR);
    csStartupFolder.Append(L"���Ǿ�");
    CreateDirectory(csStartupFolder, NULL);

    CString csInstallPath = m_strModule;
    CString csEXEFilePath;
    csEXEFilePath = csInstallPath;
    csEXEFilePath.Append(FILE_SEPARATOR);
    csEXEFilePath.Append(FILE_APP_NAME);
    CString csUnExeFilePath;
    csUnExeFilePath = csInstallPath;
    csUnExeFilePath.Append(FILE_SEPARATOR);
    csUnExeFilePath.Append(FILE_APP_NAME);
	//csUnExeFilePath.Append(L" -Uninstall");
    CString csLinkFileName = csStartupFolder;
    csLinkFileName.Append(FILE_SEPARATOR);
    csLinkFileName.Append(L"���Ǿ�.lnk");
    CString csUnlinkFileName = csStartupFolder;
    csUnlinkFileName.Append(FILE_SEPARATOR);
	csUnlinkFileName.Append(L"ж����Ϸ.lnk");

    //get icon path
    CString csExeIconPath;
    csExeIconPath = csInstallPath;
    csExeIconPath.Append(FILE_SEPARATOR);
    csExeIconPath.Append(FILE_APP_NAME);
    CString csUnExeIconPath;
    csUnExeIconPath = csInstallPath;
    csUnExeIconPath.Append(FILE_SEPARATOR);
    csUnExeIconPath.Append(FILE_APP_NAME);

    CreateShortCut(csLinkFileName, csEXEFilePath, csExeIconPath, L"");
    CreateShortCut(csUnlinkFileName, csUnExeFilePath, csUnExeIconPath, L"-Uninstall");
}

void CLauncherDlg::CreateShortCut(CString csLinkPath, CString csExePath, CString csIconPath, CString csArg)
{
	HRESULT hres;
	hres = ::CoInitialize(NULL);
	//delete old link
	CFileFind cfind;
	if(cfind.FindFile(csLinkPath))
		CFile::Remove(csLinkPath);

	IShellLink * pShellLink ;
	hres = ::CoCreateInstance( CLSID_ShellLink, NULL,CLSCTX_INPROC_SERVER, IID_IShellLink,(void **)&pShellLink);
	if( SUCCEEDED( hres))
	{
		pShellLink -> SetPath(csExePath);
		pShellLink -> SetIconLocation(csIconPath, 0); 
//		pShellLink -> SetHotkey( MAKEWORD( 'R', HOTKEYF_SHIFT | HOTKEYF_CONTROL));
		CString csWorkingDir;
		csWorkingDir = csExePath.Left(2);
		csWorkingDir.Append(FILE_SEPARATOR);

		pShellLink -> SetWorkingDirectory(csWorkingDir);
		pShellLink->SetArguments(csArg);

		IPersistFile *pPersistFile;
		hres = pShellLink -> QueryInterface( IID_IPersistFile, (void **)&pPersistFile) ;
		if( SUCCEEDED(hres))
		{
			hres = pPersistFile -> Save(csLinkPath, TRUE);
			pPersistFile -> Release();
		}
		pShellLink -> Release();
	}
	::CoUninitialize();
}

string CLauncherDlg::getCardInfo()
{
	CDC* pDC = GetDC();
	HDC hdc = pDC->m_hDC;
	PIXELFORMATDESCRIPTOR pfd = { 
		sizeof(PIXELFORMATDESCRIPTOR),
		1,                     
		PFD_DRAW_TO_WINDOW |   
		PFD_SUPPORT_OPENGL | 
		PFD_DOUBLEBUFFER,      
		PFD_TYPE_RGBA,         
		32,                    
		0, 0, 0, 0, 0, 0,      
		0,                     
		0,                     
		0,                     
		0, 0, 0, 0,            
		24,
		0,                     
		0,                     
		PFD_MAIN_PLANE,        
		0,                     
		0, 0, 0                
	};
	SetPixelFormat(hdc, ChoosePixelFormat(hdc, &pfd), &pfd);

	HGLRC hglrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, hglrc);
	string renderer = (char*) glGetString(GL_RENDERER);
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hglrc);
	ReleaseDC(pDC);
	return renderer;
}
void CLauncherDlg::vedioSetting()
{
	wstring strTmp(m_strModule);
	strTmp += L"\\GameVideoSetting.ini";
	WIN32_FIND_DATA stFindFileData;
	HANDLE hFile = FindFirstFile(strTmp.c_str(), &stFindFileData);
	const char* index ;
	string cardInfo  = getCardInfo();
	if (INVALID_HANDLE_VALUE == hFile)
	{
		int nCardLevel = 0;
		//stSysInfo.GetDisplayCardInfo(dwNum, strDiskInfo);
		if (index = strstr(cardInfo.c_str(), "GTX "))	//nvidia
		{
			//ȷ���Կ��ţ��ֳɴ���2000��С��2000��
			int nCardNumber = atoi(index + strlen("GTX "));
			if (nCardNumber > 2000)
				nCardLevel = 0;	//��
			else
			{
				int nSubNumber = nCardNumber % 100;
				if (nSubNumber > 50)
					nCardLevel = 3;	//��
				else if (nSubNumber <= 30)
					nCardLevel = 0;	//��
				else
					nCardLevel = 2;	//��
			}
		}
		else if (index = strstr(cardInfo.c_str(), "Titan"))	//nvidia
		{
			nCardLevel = 3;	//��
		}
		else if (index = strstr(cardInfo.c_str(), "Radeon HD"))	//Ati
		{
			int nCardNumber = atoi(index + strlen("Radeon HD "));
			if (nCardNumber < 5000)
				nCardLevel = 1;	//��
			else
			{
				int nSubNumber = nCardNumber % 1000;
				if (nSubNumber <= 50)
					nCardLevel = 1;	//��
				else if (nSubNumber <= 70)
					nCardLevel = 2;	//��
				else
					nCardLevel = 3;	//��
			}

		}
		else if (index = strstr(cardInfo.c_str(), "Radeon R9"))	//Ati
		{
			nCardLevel = 3;	//��
		}
		else if (index = strstr(cardInfo.c_str(), "Radeon R7"))	//Ati
		{
			int nCardNumber = atoi(index + strlen("Radeon R7 "));
			if (nCardNumber < 260)
				nCardLevel = 2;	//��
			else
			{
				nCardLevel = 3;	//��
			}
		}
		else
			nCardLevel = 0;	//��

		//д�����ļ�
		CString strInfo;
		strInfo.Format(L"%d", nCardLevel);
		WritePrivateProfileString(L"GameVideoSetting", L"SettingValue", strInfo, strTmp.c_str());
		WritePrivateProfileString(L"GameVideoSetting", L"SettingUpdate", L"1", strTmp.c_str());
	}
	::FindClose ( hFile );
}
void CLauncherDlg::DoInitCheckGame()
{
	//�������г���Launcher.exe�Ƿ���ڣ���������ڣ���ǿ������
	BOOL bCheckReg4Game = CheckReg4Game();
	BOOL bCanRunGame = CanRunGame();

	//���ע������Ƿ�������
	BOOL bRunUpdate = FALSE;
	if (bCanRunGame)
	{
		m_html.m_strGameDir = m_strModule;

		bool bUpdate = DoInitCheckUpdate();
		if ( ! bUpdate)
		{
			//m_html.Navigate(L"http://www.quegame.com/micro/");
			m_html.Navigate(m_loginurl.GetString());
			//m_html.Navigate(L"http://www.quegame.com/micronew/");
			m_htmlWait.ShowWindow(SW_HIDE);
			m_html.ShowWindow(SW_NORMAL);
			m_isWait = FALSE;
		}
		else
			bRunUpdate = TRUE;
	}
	else
		bRunUpdate = TRUE;

	if (bRunUpdate)
	{
		m_htmlWait.ShowWindow(SW_NORMAL);
		m_htmlWait.Navigate(L"http://www.quegame.com/micro/waiting.php");
		m_html.ShowWindow(SW_HIDE);
		m_isWait = TRUE;

		CSystemInfo stSysInfo;
		CString chProcessorName, chProcessorType;DWORD dwNum = 50;
		//stSysInfo.GetCpuInfo(chProcessorName, chProcessorType, dwNum, dwMaxClockSpeed);
		enum { eBufferSize = 50, };
		CString strDiskInfo[eBufferSize];
		unsigned __int64 iDiskFreeSize[eBufferSize];
		wchar_t disk[eBufferSize];
		ZeroMemory(iDiskFreeSize, eBufferSize * sizeof(unsigned _int64));
		stSysInfo.GetDiskInfo(dwNum, strDiskInfo, iDiskFreeSize,disk);

		//C�̺�D�̱Ƚϴ�С
		wchar_t szBuf[255] = {0};
		const wchar_t * pTmp = NULL;
		wchar_t cDisk = disk[0];//L'C';
		wcscpy_s(szBuf, 255, strDiskInfo[1]); 
		pTmp = wcsstr(szBuf, L"���ش���(");
		unsigned __int64 uTmpValue = 5 * 1024 * 1024;
		uTmpValue *= 1024;
		if (pTmp && iDiskFreeSize[0] < uTmpValue)	//���C��ʣ��С��5G��װ��D�̣��Ժ󲻱Ƚϴ�С��
		{
			cDisk = disk[1];//L'D';
		}
		swprintf_s(m_strModule, L"%c:\\Jiangxingjue", cDisk);
		swprintf_s(m_Download.m_strModule, L"%c:\\Jiangxingjue", cDisk);

		m_html.m_strGameDir = m_strModule;

		CreateDirectory(m_strModule, NULL);
		//�������û�������ļ�����ȷ���Կ���֮�����������ļ�
		vedioSetting();
		
		

		//����ѹ����ʱĿ¼�Ķ����ƶ�����ϷĿ¼
		//�жϵ�ǰ�ļ�����Ŀ¼�Ƿ�����ʱ�ļ���
		//�������ʱ�ļ��������ļ������򲻸���

		//strTmp = m_strModule;
		//strTmp += L"\\Login.exe";
		//hFile = FindFirstFile(strTmp.c_str(), &stFindFileData);

		GetModuleFileName(NULL, szBuf, 255); //�õ���ǰģ��·��
		wchar_t * pcurLast = NULL, * pcurTmp = wcsstr(szBuf, L"\\");
		while (pcurTmp)
		{
			pcurLast = pcurTmp;
			pcurTmp = wcsstr(pcurLast + 1, L"\\");
		}
		if (pcurLast)
			pcurLast[0] = 0;
		CString strTmpPath;
		strTmpPath.Format(L"%s",szBuf);

		if (strTmpPath.Compare(m_strModule)!=0)
		{
			strTmpPath.Format(L"%s\\Login.exe", szBuf);
			CopyBatchFile2DirPath(strTmpPath, m_strModule);
			strTmpPath.Format(L"%s\\login.ini", szBuf);
			CopyBatchFile2DirPath(strTmpPath, m_strModule);
			//strTmpPath.Format(L"%s\\mfc90u.dll", szBuf);
			//CopyBatchFile2DirPath(strTmpPath, m_strModule);
			//strTmpPath.Format(L"%s\\mfcm90u.dll", szBuf);
			//CopyBatchFile2DirPath(strTmpPath, m_strModule);
			strTmpPath.Format(L"%s\\LauncherDlg.bmp", szBuf);
			CopyBatchFile2DirPath(strTmpPath, m_strModule);
			strTmpPath.Format(L"%s\\Uninstall.list", szBuf);
			CopyBatchFile2DirPath(strTmpPath, m_strModule);
			strTmpPath.Format(L"%s\\LoginExeVersionInfo.ini", szBuf);
			CopyBatchFile2DirPath(strTmpPath, m_strModule);
			strTmpPath.Format(L"%s\\JXJClient.7z", szBuf);
			CopyBatchFile2DirPath(strTmpPath, m_strModule);
			strTmpPath.Format(L"%s\\7zr.exe", szBuf);
			CopyBatchFile2DirPath(strTmpPath, m_strModule);
			
		}

		//strTmp = m_strModule;
		//strTmp += L"/JXJClient.7z";
		//hFile = FindFirstFile(strTmp.c_str(), &stFindFileData);
		//if (INVALID_HANDLE_VALUE == hFile)
		//{
			//���ע����еļ�ֵ��Ч�������ļ�
			/*CString strHttpFile("http://jxj.quegame.com/download/JXJClient.7z");
			wstring strTmp = m_strModule;
			strTmp += L"/JXJClient.7z";
			m_Download.StartDownload(strHttpFile, strTmp.c_str());

			m_Process1.ShowWindow(SW_SHOW);
			m_Process1.setText(CString(L"�ļ�������...."));*/
		//}
		//else
		//{
		//	::FindClose ( hFile );
		//}

		//��ѹ
		//Decompress();
		m_Download.m_bStartCompress = TRUE;

		CreateStartMenu();
		CreateDesktopShortCut(m_strModule);
	}else
	{
		vedioSetting();
	}
}

void CLauncherDlg::CopyBatchFile2DirPath(CString strFilePath, CString strDirPath)
{
	//����Ŀ¼
	CreateDirectory(strDirPath, NULL);

	//�ƶ��ļ�
	CString strFileName, strMove2FilePath;
	if (GetFileName(strFilePath, strFileName))
	{
		strMove2FilePath.Format(L"%s/%s", strDirPath, strFileName);
		CopyFile(strFilePath, strMove2FilePath, FALSE);
	}
}

BOOL CLauncherDlg::GetFileName(CString strPath, CString & strFileName)
{
	const wchar_t * pLast = NULL, * pTmp = wcsstr(strPath, L"\\");
	while (pTmp)
	{
		pLast = pTmp;
		pTmp = wcsstr(pLast + 1, L"\\");
		if (NULL == pTmp)
			pTmp = wcsstr(pLast + 1, L"/");
	}
	if (pLast)
		strFileName = pLast + 1;
	return TRUE;
}

BOOL CLauncherDlg::CanRunGame()
{
	wstring strTmp(m_strModule);
	strTmp += L"/Launcher.exe";
	//AfxMessageBox(strTmp.c_str());
	WIN32_FIND_DATA stFindFileData;
	HANDLE hFile = FindFirstFile(strTmp.c_str(), &stFindFileData);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		//AfxMessageBox(L"false1");
		::FindClose ( hFile );
		return FALSE;
	}
	::FindClose ( hFile );
	return TRUE;
}

void CLauncherDlg::RunGame()
{
	// ����������Ϣ
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory( &si, sizeof(si) );	// ��������Ϣ�ṹ����
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );	// ��������Ϣ�ṹ����

	wstring strTmp(m_strModule);
	strTmp += L"/Launcher.exe";

	//���԰汾��·��
	CreateProcess(strTmp.c_str(), NULL, NULL, NULL, FALSE, 0, NULL, m_strModule, &si, &pi);
}

void CLauncherDlg::RunSetup()
{
	//// ����������Ϣ
	//STARTUPINFO si;
	//PROCESS_INFORMATION pi;
	//ZeroMemory( &si, sizeof(si) );	// ��������Ϣ�ṹ����
	//si.cb = sizeof(si);
	//ZeroMemory( &pi, sizeof(pi) );	// ��������Ϣ�ṹ����

	//wstring strTmp(m_strModule);
	//strTmp += L"/JXJGame.exe";

	////���԰汾��·��
	//CreateProcess(strTmp.c_str(), NULL, NULL, NULL, FALSE, 0, NULL, m_strModule, &si, &pi);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CLauncherDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogSK::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags the minimized window.
HCURSOR CLauncherDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLauncherDlg::OnBnClickedStartGame()
{
	//// ����������Ϣ
	//STARTUPINFO si;
	//PROCESS_INFORMATION pi;
	//ZeroMemory( &si, sizeof(si) );	// ��������Ϣ�ṹ����
	//si.cb = sizeof(si);
	//ZeroMemory( &pi, sizeof(pi) );	// ��������Ϣ�ṹ����

	////���԰汾��·��
	//CreateProcess(L"../Game.exe", NULL, NULL, NULL, FALSE, 0, NULL, L"../", &si, &pi);

	//�˳�����
	//OnOK();
}

void CLauncherDlg::OnBnClickedButtonMini()
{
	ShowWindow(SW_MINIMIZE);
}

void CLauncherDlg::OnBnClickedButtonQuit()
{
	CDialogSK::OnCancel();
}

void CLauncherDlg::OnBnClickedButtonVideoSetting()
{
	m_html.ShowWindow(SW_HIDE);
	m_htmlWait.ShowWindow(SW_HIDE);

	m_btnSelect.ShowWindow(SW_SHOW);
	m_btnSelectCancel.ShowWindow(SW_SHOW);

	wstring strTmp(m_strModule);
	strTmp += L"/GameVideoSetting.ini";
	int selectId = GetPrivateProfileInt(L"GameVideoSetting", L"SettingValue",2,strTmp.c_str());
	if(selectId>4) selectId = 4;
	
	for (int i = 0;i<5;i++)
	{
		m_btnVideoLevel[i].ShowWindow(SW_SHOW);
		if(i == selectId)
			m_btnVideoLevel[i].SetCheck(1);
		else
			m_btnVideoLevel[i].SetCheck(0);
	}
}
void CLauncherDlg::OnBnClickedButtonLevelVeryLow()
{
	for (int i = 1;i<5;i++)
	{
		m_btnVideoLevel[i].SetCheck(0);
	}
	m_btnVideoLevel[0].SetCheck(1);
}
void CLauncherDlg::OnBnClickedButtonLevelLow()
{
	for (int i = 0;i<5;i++)
	{
		if(i == 1) continue; 
		m_btnVideoLevel[i].SetCheck(0);
	}
	m_btnVideoLevel[1].SetCheck(1);
}
void CLauncherDlg::OnBnClickedButtonLevelNormal()
{
	for (int i = 0;i<5;i++)
	{
		if(i == 2) continue; 
		m_btnVideoLevel[i].SetCheck(0);
	}
	m_btnVideoLevel[2].SetCheck(1);
}
void CLauncherDlg::OnBnClickedButtonLevelHigh()
{
	for (int i = 0;i<5;i++)
	{
		if(i == 3) continue; 
		m_btnVideoLevel[i].SetCheck(0);
	}
	m_btnVideoLevel[3].SetCheck(1);
}
void CLauncherDlg::OnBnClickedButtonLevelVeryHigh()
{
	for (int i = 0;i<5;i++)
	{
		if(i == 4) continue; 
		m_btnVideoLevel[i].SetCheck(0);
	}
	m_btnVideoLevel[4].SetCheck(1);
}
void CLauncherDlg::OnBnClickedButtonSelect()
{
	wstring strTmp(m_strModule);
	strTmp += L"/GameVideoSetting.ini";
	int selectId = GetPrivateProfileInt(L"GameVideoSetting", L"SettingValue",2,strTmp.c_str());

	for (int i = 0;i<5;i++)
	{
		if(m_btnVideoLevel[i].GetCheck()==1)
		{
			selectId = i;
			break;
		}
	}

	CString strInfo;
	strInfo.Format(L"%d", selectId);
	WritePrivateProfileString(L"GameVideoSetting", L"SettingValue", strInfo, strTmp.c_str());
	WritePrivateProfileString(L"GameVideoSetting", L"SettingUpdate", L"1", strTmp.c_str());
	OnBnClickedButtonCancel();
}
void CLauncherDlg::OnBnClickedButtonCancel()
{
	if(m_isWait == TRUE)
	{
		m_htmlWait.ShowWindow(SW_SHOW);
	}
	else
	{
		m_html.ShowWindow(SW_SHOW);
	}
	
	

	for (int i = 0;i<5;i++)
	{
		m_btnVideoLevel[i].ShowWindow(SW_HIDE);
	}

	m_btnSelect.ShowWindow(SW_HIDE);
	m_btnSelectCancel.ShowWindow(SW_HIDE);
}
void CLauncherDlg::OnCancel()
{

}

wstring GetProgramDir()    
{     
	TCHAR exeFullPath[MAX_PATH]; 
	GetCurrentDirectory(MAX_PATH,exeFullPath);
	return exeFullPath;
	//TCHAR exeFullPath[MAX_PATH];  
	//GetModuleFileName(NULL,exeFullPath,MAX_PATH);  
	//wstring strPath = __TEXT("");         
	//strPath = (wstring)exeFullPath;    
	//int pos = strPath.find_last_of(L'\\', strPath.length());  
	//return strPath.substr(0, pos);  
}   

BOOL CLauncherDlg::CheckReg4Game()
{
	HKEY hKey;
	bool bFind = FALSE;
	//LONG lRet = RegOpenKeyEx( HKEY_CURRENT_USER, L"Software\\MozillaPlugins\\@jxj.com", 0, KEY_QUERY_VALUE, &hKey );
	LONG lRet = RegOpenKeyEx( HKEY_CURRENT_USER, L"SOFTWARE\\MozillaPlugins\\quegame.com/JXJWebPlayer", 0, KEY_QUERY_VALUE, &hKey );
	if( lRet != ERROR_SUCCESS )
	{
		RegCloseKey( hKey );
	}
	else
	{
		//char szBuf[128] = {0};
		wchar_t szBuf[255] = {0};
		DWORD dwBufLen = 127;
		lRet = RegQueryValueEx( hKey, L"Path", NULL, NULL, (LPBYTE) szBuf, &dwBufLen);
		if( lRet == ERROR_SUCCESS )
		{
			wcscpy(m_strModule, szBuf);
			wchar_t * pIndex = wcsstr(m_strModule, L"Bin");
			if (pIndex)
				pIndex[0] = 0;
			else
			{
				pIndex = wcsstr(m_strModule, L"bin");
				if (pIndex)
					pIndex[0] = 0;
			}
			bFind = TRUE;
		}
		
		RegCloseKey( hKey );
	}

	if (bFind == FALSE)
	{
		WIN32_FIND_DATA FindFileData;
		HANDLE hFind;
		wstring path = GetProgramDir();
		wstring findPath = path + L"/Launcher.exe";
		//AfxMessageBox(findPath.c_str());
		const TCHAR *FilePathBuff = findPath.c_str();
		hFind = FindFirstFile(FilePathBuff, &FindFileData);
		if (hFind != INVALID_HANDLE_VALUE)
		{
			bFind = TRUE;
			wcscpy(m_strModule, path.c_str());
		}
		::FindClose(hFind);
	}
	return bFind;
}

void CLauncherDlg::CurDownloadProc(CString &fileName,UINT uCurDownload, UINT uTotalSize)
{
	m_strCurDownFileName = fileName;
	m_uCurDownloadSize = uCurDownload;
	m_uCurDownloadFileSize = uTotalSize;
}

void CLauncherDlg::OnDownloadFinish(const CString & strHttpFile, const CString & strLocalFile)
{
	//RunSetup();

	//m_bDownloadFinish = TRUE;

	//if (0 == m_btDownloadStage)
	//{
	//	m_btDownloadStage = 1;
	//}
	//else if (2 == m_btDownloadStage)
	//{
	//	//m_bDownloadFinish = TRUE;
	//	m_Download.m_bStartCompress = TRUE;
	//}
}
void CLauncherDlg::OnDecompressFile()
{
	CString str(L"���ڰ�װ....");
	m_Process1.SetPos(0);
	m_Process1.setText(str);
}
void CLauncherDlg::OnTimer(UINT_PTR nIDEvent)
{
	/*if (1 == m_btDownloadStage)
	{
		m_btDownloadStage = 2;

		CString strHttpFile("http://jxj.quegame.com/download/7zr.exe");
		wstring strTmp(m_strModule);
		strTmp += L"/7zr.exe";
		m_Download.StartDownload(strHttpFile, strTmp.c_str());
	}*/

	//if (m_bDownloadFinish)
	//{
	//	m_bDownloadFinish = FALSE;

	//	//��ѹ
	//	wchar_t buf[256];
	//	memset(buf,0,256);
	//	swprintf(buf, L"%s/7zr.exe x -r %s/JXJClient.7z -y", m_strModule, m_strModule);
	//	PROCESS_INFORMATION pi;
	//	STARTUPINFO si; //This is an [in] parameter
	//	ZeroMemory(&si, sizeof(si));
	//	si.cb = sizeof si; //Only compulsory field
	//	si.dwFlags = STARTF_USESHOWWINDOW;
	//	si.wShowWindow = SW_HIDE;
	//	if(CreateProcess(NULL, buf, NULL, NULL, FALSE, 0, NULL, m_strModule, &si, &pi))
	//	{
	//		WaitForSingleObject(pi.hProcess,INFINITE);
	//		CloseHandle(pi.hThread);
	//		CloseHandle(pi.hProcess);

	//		//����install.cmd
	//		//wstring strTmp(m_strModule);
	//		//strTmp += L"/Install.cmd";
	//		//_wsystem(strTmp.c_str());

	//		//ÿ������ִ��
	//		swprintf(buf, L"regsvr32 /s /u %s/Bin/Creature3DX.ocx", m_strModule);
	//		if(CreateProcess(NULL, buf, NULL, NULL, FALSE, 0, NULL, m_strModule, &si, &pi))
	//		{
	//			WaitForSingleObject(pi.hProcess,INFINITE);
	//			CloseHandle(pi.hThread);
	//			CloseHandle(pi.hProcess);
	//		}
	//		else
	//			AfxMessageBox(L"regsvr32");
	//		swprintf(buf, L"%s/RegisterKeyNP.exe -del", m_strModule);
	//		if(CreateProcess(NULL, buf, NULL, NULL, FALSE, 0, NULL, m_strModule, &si, &pi))
	//		{
	//			WaitForSingleObject(pi.hProcess,INFINITE);
	//			CloseHandle(pi.hThread);
	//			CloseHandle(pi.hProcess);
	//		}
	//		else
	//			AfxMessageBox(L"RegisterKeyNP");
	//		swprintf(buf, L"regsvr32 /s %s/Bin/Creature3DX.ocx", m_strModule);
	//		if(CreateProcess(NULL, buf, NULL, NULL, FALSE, 0, NULL, m_strModule, &si, &pi))
	//		{
	//			WaitForSingleObject(pi.hProcess,INFINITE);
	//			CloseHandle(pi.hThread);
	//			CloseHandle(pi.hProcess);
	//		}
	//		else
	//			AfxMessageBox(L"regsvr32");
	//		swprintf(buf, L"%s/RegisterKeyNP.exe -reg", m_strModule);
	//		if(CreateProcess(NULL, buf, NULL, NULL, FALSE, 0, NULL, m_strModule, &si, &pi))
	//		{
	//			WaitForSingleObject(pi.hProcess,INFINITE);
	//			CloseHandle(pi.hThread);
	//			CloseHandle(pi.hProcess);
	//		}
	//		else
	//			AfxMessageBox(L"RegisterKeyNP");
	//		swprintf(buf, L"%s/Launcher.exe", m_strModule);
	//		if(CreateProcess(NULL, buf, NULL, NULL, FALSE, 0, NULL, m_strModule, &si, &pi))
	//		{
	//			WaitForSingleObject(pi.hProcess,INFINITE);
	//			CloseHandle(pi.hThread);
	//			CloseHandle(pi.hProcess);
	//		}
	//		else
	//			AfxMessageBox(L"Launcher");
	//	}
	//	else
	//		AfxMessageBox(L"��ѹʧ��");

	//	m_Download.Uninit();
	//	::Sleep(16);

	//	CDialogSK::OnCancel();

	//	//m_bQuitProcess = TRUE;


	//	////���ע������Ƿ�������
	//	//if (CheckReg4Game())
	//	//{
	//	//	//// ����������Ϣ
	//	//	//RunGame();

	//	//	m_bQuitProcess = TRUE;
	//	//}
	//}
	if (m_Download.m_bQuitProcess || m_bQuitProcess)
	{
		//m_Download.Uninit();
		//::Sleep(16);

		//CDialogSK::OnCancel();

		m_Process1.SetPos(100);
		UpdateData();

		m_html.ShowWindow(SW_NORMAL);
		//m_html.Navigate(L"http://www.quegame.com/micro/");
		m_html.Navigate(m_loginurl.GetString());
		//m_html.Navigate(L"http://www.quegame.com/micronew/");
		m_htmlWait.ShowWindow(SW_HIDE);
		m_Process1.ShowWindow(SW_HIDE);
		m_isWait = FALSE;

		KillTimer(1);
	}
	else
	{
		if (m_uCurDownloadFileSize)
		{
			m_Process1.SetPos(m_uCurDownloadSize * 100.0f / m_uCurDownloadFileSize);
			UpdateData();
		}
	}

	__super::OnTimer(nIDEvent);
}

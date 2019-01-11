
// qLoginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "qLogin.h"
#include "qLoginDlg.h"
//#include "afxdialogex.h"
#include <string>
//#include <dxgi.h>
#include <vector>
#include "SystemInfo.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <gl/GL.h>
#pragma comment(lib, "Opengl32.lib") 
//#pragma comment(lib, "dxgi.lib") 
// CqLoginDlg �Ի���

using namespace std;

CqLoginDlg::CqLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogSK(CqLoginDlg::IDD, pParent)
	, m_Download(this)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bQuitProcess = FALSE;
	m_uCurDownloadSize = 0;
	m_uCurDownloadFileSize = 1;

	m_strModule[0] = 0;

	m_btDownloadStage = 0;
	flag = false;
}

CqLoginDlg::~CqLoginDlg()
{
	m_Download.Uninit();
}

void CqLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogSK::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_Process);
	DDX_Control(pDX, IDC_STATIC1, m_Text);
	DDX_Control(pDX, IDC_BUTTON1,m_button1);
	DDX_Control(pDX, IDC_BUTTON2,m_button2);
}

BEGIN_MESSAGE_MAP(CqLoginDlg, CDialogSK)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CqLoginDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CqLoginDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CqLoginDlg ��Ϣ�������

BOOL CqLoginDlg::OnInitDialog()
{
	CDialogSK::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_Process.SetRange(0, 100);
	m_Process.ShowWindow(SW_HIDE);
	SetTimer(1, 100, NULL);

	m_Download.Init();
	DoInitCheckGame();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CqLoginDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogSK::OnPaint();
	}
}
std::string CqLoginDlg::getCardInfo()
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
void CqLoginDlg::vedioSetting()
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
//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CqLoginDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CqLoginDlg::DoInitCheckGame()
{
	//�������г���Launcher.exe�Ƿ���ڣ���������ڣ���ǿ������
	BOOL bCheckReg4Game = CheckReg4Game();
	BOOL bCanRunGame = CanRunGame();
	if (bCanRunGame)
	{
		wchar_t buf[256];
		memset(buf, 0, 256);
		wsprintf(buf, L"%s/Login.exe\0", m_strModule);
		ShellExecute(NULL, L"open", buf, NULL, NULL, SW_SHOW);
		exit(0);
	}
	else
	{
		Install();
		vedioSetting();
	}
	//	bRunUpdate = TRUE;

	//if (bRunUpdate)
	//{
	//	Install();
	//	
	//}else
	//{
	//	//MessageBox(L"��װ�ɹ�",L"Jiangxingjue");
	//	m_Process.ShowWindow(SW_HIDE);
	//	m_Text.ShowWindow(SW_HIDE);
	//	m_button1.ShowWindow(SW_SHOW);
	//	m_button2.ShowWindow(SW_SHOW);
	//	//exit(0);
	//}
	//vedioSetting();
}
void CqLoginDlg::Install()
{
	m_Process.ShowWindow(SW_SHOW);
	m_Text.ShowWindow(SW_SHOW);
	m_button1.ShowWindow(SW_HIDE);
	m_button2.ShowWindow(SW_HIDE);

	CSystemInfo stSysInfo;
	CString chProcessorName, chProcessorType;
	//stSysInfo.GetCpuInfo(chProcessorName, chProcessorType, dwNum, dwMaxClockSpeed);
	DWORD dwNum = 50;
	enum { eBufferSize = 50, };
	std::string strDiskInfo[eBufferSize];
	unsigned __int64 iDiskFreeSize[eBufferSize];
	char disk[eBufferSize];
	ZeroMemory(iDiskFreeSize, eBufferSize * sizeof(unsigned _int64));
	stSysInfo.GetDiskInfo(dwNum, strDiskInfo, iDiskFreeSize,disk);
	if (dwNum > 5)//cdefgh
		dwNum = 5;
	////C�̺�D�̱Ƚϴ�С
	//const wchar_t * pTmp = NULL;
	//wchar_t cDisk = disk[0];//L'C';
	//wcscpy_s(szBuf, 255, strDiskInfo[1]); 
	//pTmp = wcsstr(szBuf, L"���ش���(");
	//unsigned __int64 uTmpValue = 5 * 1024 * 1024;
	//uTmpValue *= 1024;
	//if (pTmp && iDiskFreeSize[0] < uTmpValue)	//���C��ʣ��С��5G��װ��D�̣��Ժ󲻱Ƚϴ�С��
	//{
	//	cDisk = disk[1];//L'D';
	//}
	//��װ��ʣ��ռ�����Ӳ����
	const char * pTmp = NULL;
	char cDisk = disk[0];//L'C';
	unsigned __int64 maxDiskFreeSize = 0;
	for (int i = 0; i < dwNum; i++)
	{
		if (iDiskFreeSize[i] >= maxDiskFreeSize)
		{
			maxDiskFreeSize = iDiskFreeSize[i];
			cDisk = disk[i];
		}
	}
	swprintf_s(m_strModule, L"%c:\\Jiangxingjue", cDisk);
	swprintf_s(m_Download.m_strModule, L"%c:\\Jiangxingjue", cDisk);

	CreateDirectory(m_strModule, NULL);

	//����ѹ����ʱĿ¼�Ķ����ƶ�����ϷĿ¼
	//�жϵ�ǰ�ļ�����Ŀ¼�Ƿ�����ʱ�ļ���
	//�������ʱ�ļ��������ļ������򲻸���
	wchar_t szBuf[255] = { 0 };
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
		strTmpPath.Format(L"%s\\JXJClient.7z", szBuf);
		CopyBatchFile2DirPath(strTmpPath, m_strModule);
		strTmpPath.Format(L"%s\\Uninstall.list", szBuf);
		CopyBatchFile2DirPath(strTmpPath, m_strModule);
		strTmpPath.Format(L"%s\\7zr.exe", szBuf);
		CopyBatchFile2DirPath(strTmpPath, m_strModule);
		strTmpPath.Format(L"%s\\web.ini", szBuf);
		CopyBatchFile2DirPath(strTmpPath, m_strModule);
		//΢��
		strTmpPath.Format(L"%s\\Login.exe", szBuf);
		CopyBatchFile2DirPath(strTmpPath, m_strModule);
		strTmpPath.Format(L"%s\\login.ini", szBuf);
		CopyBatchFile2DirPath(strTmpPath, m_strModule);
		strTmpPath.Format(L"%s\\LauncherDlg.bmp", szBuf);
		CopyBatchFile2DirPath(strTmpPath, m_strModule);
		strTmpPath.Format(L"%s\\LoginExeVersionInfo.ini", szBuf);
		CopyBatchFile2DirPath(strTmpPath, m_strModule);
		CreateStartMenu();
	}
	//AfxMessageBox(L"1111111");
	wstring strTmp = m_strModule;
	strTmp += L"/JXJClient.7z";
	WIN32_FIND_DATA stFindFileData;
	ZeroMemory(&stFindFileData, sizeof(WIN32_FIND_DATA));
	HANDLE hFile = FindFirstFile(strTmp.c_str(), &stFindFileData);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		//���ע����еļ�ֵ��Ч�������ļ�
		CString strHttpFile("http://jxj.quegame.com/download/JXJClient.7z");
		strTmp = m_strModule;
		strTmp += L"/JXJClient.7z";
		m_Download.StartDownload(strHttpFile, strTmp.c_str());
	}
	else
		m_Download.m_bStartCompress = TRUE;

	CString str(L"�ļ���ȡ��...");
	m_Text.SetWindowTextW(str);
	//}
	//else
	//{
	::FindClose ( hFile );
	//}
}
#define FILE_SEPARATOR	L"/"
#define FILE_APP_NAME	L"Login.exe"
void CqLoginDlg::CreateStartMenu()
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

void CqLoginDlg::CreateShortCut(CString csLinkPath, CString csExePath, CString csIconPath, CString csArg)
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
void CqLoginDlg::CopyBatchFile2DirPath(CString strFilePath, CString strDirPath)
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

BOOL CqLoginDlg::GetFileName(CString strPath, CString & strFileName)
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

wstring GetProgramDir()    
{     
	//TCHAR exeFullPath[MAX_PATH];  
	//GetModuleFileName(NULL,exeFullPath,MAX_PATH);  
	//wstring strPath = __TEXT("");         
	//strPath = (wstring)exeFullPath;    
	//int pos = strPath.find_last_of(L'\\', strPath.length());  
	//return strPath.substr(0, pos); 
	TCHAR exeFullPath[MAX_PATH]; 
	GetCurrentDirectory(MAX_PATH,exeFullPath);
	return exeFullPath;
}   

BOOL CqLoginDlg::CheckReg4Game()
{
	HKEY hKey;
	bool bFind = FALSE;
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
		wstring findPath = path + L"\\Launcher.exe";
		const TCHAR *FilePathBuff = findPath.c_str();
		hFind = FindFirstFile(FilePathBuff, &FindFileData);
		if (hFind != INVALID_HANDLE_VALUE)
		{
			wcscpy(m_strModule, path.c_str());
			bFind = TRUE;
		}
		::FindClose(hFind);
	}
	return bFind;
}

BOOL CqLoginDlg::CanRunGame()
{
	wstring strTmp(m_strModule);
	strTmp += L"/Login.exe";
	WIN32_FIND_DATA stFindFileData;
	HANDLE hFile = FindFirstFile(strTmp.c_str(), &stFindFileData);
	if (INVALID_HANDLE_VALUE == hFile)
	{
		::FindClose ( hFile );
		return FALSE;
	}
	::FindClose ( hFile );
	return TRUE;
}
static int n = 0;
void CqLoginDlg::OnTimer(UINT_PTR nIDEvent)
{
	//if (1 == m_btDownloadStage)
	//{
	//	m_btDownloadStage = 2;

	//	/*CString strHttpFile("http://app1104925852.imgcache.qzoneapp.com/app1104925852/download/7zr.exe");
	//	wstring strTmp(m_strModule);
	//	strTmp += L"/7zr.exe";
	//	m_Download.StartDownload(strHttpFile, strTmp.c_str());*/
	//}

	
	if (m_Download.m_bQuitProcess || m_bQuitProcess)
	{
		//m_Download.Uninit();
		//::Sleep(16);

		//CDialogSK::OnCancel();

		m_Process.SetPos(100);
		UpdateData();

		KillTimer(1);
		//MessageBox(L"��װ�ɹ�",L"Jiangxingjue");
		CDialogSK::OnCancel();
	}
	else
	{
		if (m_uCurDownloadFileSize)
		{
			if (flag)
			{
				m_Process.SetPos(n * 100.0f / 300);
			}
			else
				m_Process.SetPos(m_uCurDownloadSize * 100.0f / m_uCurDownloadFileSize);
			UpdateData();
		}
			n++;
			CString str(L"�ļ���ȡ��...");
			if (n %5 == 0)
			{
				str += L"...";
			}
			m_Text.SetWindowTextW(str);
		
	}

	__super::OnTimer(nIDEvent);
}

void CqLoginDlg::CurDownloadProc(CString &fileName,UINT uCurDownload, UINT uTotalSize)
{
	m_uCurDownloadSize = uCurDownload;
	m_uCurDownloadFileSize = uTotalSize;
}

void CqLoginDlg::OnDownloadFinish(const CString & strHttpFile, const CString & strLocalFile)
{
	//RunSetup();

	//m_bDownloadFinish = TRUE;
	m_Download.m_bStartCompress = TRUE;
	
}
void CqLoginDlg::OnDecompressFile()
{
	flag = true;
	n=0;
}

void CqLoginDlg::OnGameLog()
{
	m_Download.GameLog(L"http://jxj.quegame.com/index.php/index/installsqq");
	m_bQuitProcess = TRUE;
}

void CqLoginDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	wchar_t buf[256];
	memset(buf,0,sizeof(buf));
	swprintf(buf, L"regsvr32 /s Bin/npJXJWebPlayer.dll" );
	PROCESS_INFORMATION pi;
	STARTUPINFO si; //This is an [in] parameter
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof si; //Only compulsory field
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;
	if(CreateProcess(NULL, buf, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		WaitForSingleObject(pi.hProcess,INFINITE);
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
		AfxMessageBox(L"�޸������");
	}
	else
		AfxMessageBox(L"regsvr32 failed");
	CDialogSK::OnCancel();
}


void CqLoginDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Install();
}

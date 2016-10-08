// Creature3DXCtrl.cpp : CCreature3DXCtrl ActiveX �ؼ����ʵ�֡�

#include "stdafx.h"
#include "Creature3DX.h"
#include "Creature3DXCtrl.h"
#include "Creature3DXPropPage.h"
#include "process.h"
//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif
#if defined(WIN32) && !defined(__CYGWIN__)
#include <Io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <direct.h> // for _mkdir

#define mkdir(x,y) _mkdir((x))
#define stat64 _stati64

// set up for windows so acts just like unix access().
#define F_OK 4


#else // unix

#if defined( __APPLE__ ) || defined(__CYGWIN__) || defined(__FreeBSD__)
#define stat64 stat
#endif

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#endif

// set up _S_ISDIR()
#if !defined(S_ISDIR)
#  if defined( _S_IFDIR) && !defined( __S_IFDIR)
#    define __S_IFDIR _S_IFDIR
#  endif
#  define S_ISDIR(mode)    (mode&__S_IFDIR)
#endif
#include <string>
#include <fstream>
#include <time.h>
#include <vector>
#include <fstream>
#include <stack>

IMPLEMENT_DYNCREATE(CCreature3DXCtrl, COleControl)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CCreature3DXCtrl, COleControl)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_CREATE()
	ON_WM_NCDESTROY()
END_MESSAGE_MAP()



// ����ӳ��

BEGIN_DISPATCH_MAP(CCreature3DXCtrl, COleControl)
END_DISPATCH_MAP()



// �¼�ӳ��

BEGIN_EVENT_MAP(CCreature3DXCtrl, COleControl)
END_EVENT_MAP()



// ����ҳ

// TODO: ����Ҫ��Ӹ�������ҳ�����ס���Ӽ�����
BEGIN_PROPPAGEIDS(CCreature3DXCtrl, 1)
	PROPPAGEID(CCreature3DXPropPage::guid)
END_PROPPAGEIDS(CCreature3DXCtrl)



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CCreature3DXCtrl, "CREATURE3DX.Creature3DXCtrl.1",
	0x5d2ee22e, 0xecfe, 0x440a, 0x8d, 0x48, 0x86, 0xed, 0xda, 0x43, 0x39, 0x95)



// ����� ID �Ͱ汾

IMPLEMENT_OLETYPELIB(CCreature3DXCtrl, _tlid, _wVerMajor, _wVerMinor)



// �ӿ� ID

const IID BASED_CODE IID_DCreature3DX =
		{ 0x714D2510, 0x9A0C, 0x4498, { 0xBF, 0x39, 0x33, 0xDB, 0x17, 0x79, 0xEB, 0x67 } };
const IID BASED_CODE IID_DCreature3DXEvents =
		{ 0x9666DF6A, 0x6072, 0x4696, { 0x98, 0xF0, 0x6C, 0xA9, 0x9, 0xEC, 0xDA, 0x27 } };



// �ؼ�������Ϣ

static const DWORD BASED_CODE _dwCreature3DXOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CCreature3DXCtrl, IDS_CREATURE3DX, _dwCreature3DXOleMisc)



// CCreature3DXCtrl::CCreature3DXCtrlFactory::UpdateRegistry -
// ��ӻ��Ƴ� CCreature3DXCtrl ��ϵͳע�����

BOOL CCreature3DXCtrl::CCreature3DXCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: ��֤���Ŀؼ��Ƿ���ϵ�Ԫģ���̴߳������
	// �йظ�����Ϣ����ο� MFC ����˵�� 64��
	// ������Ŀؼ������ϵ�Ԫģ�͹�����
	// �����޸����´��룬��������������
	// afxRegApartmentThreading ��Ϊ 0��

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_CREATURE3DX,
			IDB_CREATURE3DX,
			afxRegApartmentThreading,
			_dwCreature3DXOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


std::string getFilePath(const std::string& fileName)
{
	std::string::size_type slash1 = fileName.find_last_of('/');
	std::string::size_type slash2 = fileName.find_last_of('\\');
	if (slash1==std::string::npos) 
	{
		if (slash2==std::string::npos) return std::string();
		return std::string(fileName,0,slash2);
	}
	if (slash2==std::string::npos) return std::string(fileName,0,slash1);
	return std::string(fileName, 0, slash1>slash2 ?  slash1 : slash2);
}
void appendLibraryFilePaths(const std::string &path)
{
	static bool inited = false;
	if(!inited)
	{
		char newPath[1024];
		char* ptr;
		if ((ptr = getenv( "PATH" )))
		{
			sprintf(newPath,"PATH=%s;%s\0",path.c_str(),ptr);
			putenv(newPath);
		}
		else
		{
			sprintf(newPath,"PATH=%s\0",path.c_str(),ptr);
			putenv(newPath);
		}
		inited = true;
	}
}
void findFileInDir(const char* rootDir, std::vector<std::string>& fileNameVec)
{
	std::string rdir = rootDir;
	char fname[1024];
	ZeroMemory(fname, 1024);

	WIN32_FIND_DATA fd;
	ZeroMemory(&fd, sizeof(WIN32_FIND_DATA));

	HANDLE hSearch;

	char filePathName[1024];
	char tmpPath[1024];
	ZeroMemory(filePathName, 1024);
	ZeroMemory(tmpPath, 1024);

	strcpy(filePathName, rootDir);

	bool bSearchFinished = FALSE;

	if( filePathName[strlen(filePathName) -1] != '\\' )
	{
		strcat(filePathName, "\\");
	}
	strcat(filePathName, "*");
	hSearch = FindFirstFile(filePathName, &fd);

	if( (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		&& strcmp(fd.cFileName, ".") && strcmp(fd.cFileName, "..") )
	{
		strcpy(tmpPath, rootDir);
		strcat(tmpPath, fd.cFileName);
		strcat(tmpPath, "\\");
		findFileInDir(tmpPath, fileNameVec);
	}
	else if( strcmp(fd.cFileName, ".") && strcmp(fd.cFileName, "..") )
	{
		if( rootDir[strlen(rootDir) -1] != '\\' )
			sprintf(fname, "%s\\%s\0",rootDir,fd.cFileName);
		else
			sprintf(fname, "%s%s\0",rootDir,fd.cFileName);
		fileNameVec.push_back(fname);
	}

	while( !bSearchFinished )
	{
		if( FindNextFile(hSearch, &fd) )
		{
			if( (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				&& strcmp(fd.cFileName, ".") && strcmp(fd.cFileName, "..") )       
			{
				strcpy(tmpPath, rootDir);
				strcat(tmpPath, fd.cFileName);
				strcat(tmpPath, "\\");
				findFileInDir(tmpPath, fileNameVec);
			}
			else if( strcmp(fd.cFileName, ".") && strcmp(fd.cFileName, "..") )
			{
				if( rootDir[strlen(rootDir) -1] != '\\' )
					sprintf(fname, "%s\\%s\0",rootDir,fd.cFileName);
				else
					sprintf(fname, "%s%s\0",rootDir,fd.cFileName);
				fileNameVec.push_back(fname);
			}
		}
		else
		{
			if( GetLastError() == ERROR_NO_MORE_FILES )
			{
				bSearchFinished = TRUE;
			}
			else
				bSearchFinished = TRUE;
		}
	}
	FindClose(hSearch);
}
bool fileExists(const std::string& filename)
{
	return access( filename.c_str(), F_OK ) == 0;
}
std::string convertFileNameToUnixStyle(const std::string& fileName)
{
	std::string new_fileName(fileName);

	std::string::size_type slash = 0;
	while( (slash=new_fileName.find_first_of('\\',slash)) != std::string::npos)
	{
		new_fileName[slash]='/';
	}

	return new_fileName;
}
bool makeDirectory( const std::string &path )
{
	if (path.empty())
	{
		return false;
	}

	struct stat64 stbuf;
	if( stat64( path.c_str(), &stbuf ) == 0 )
	{
		if( S_ISDIR(stbuf.st_mode))
			return true;
		else
		{
			return false;
		}
	}

	std::string dir = path;
	std::stack<std::string> paths;
	while( true )
	{
		if( dir.empty() )
			break;

		if( stat64( dir.c_str(), &stbuf ) < 0 )
		{
			switch( errno )
			{
			case ENOENT:
			case ENOTDIR:
				paths.push( dir );
				break;

			default:
				return false;
			}
		}
		dir = getFilePath(std::string(dir));
	}

	while( !paths.empty() )
	{
		std::string dir = paths.top();

		if( mkdir( dir.c_str(), 0755 )< 0 )
		{
			return false;
		} 
		paths.pop();
	}
	return true;
}
bool makeDirectoryForFile( const std::string &path )
{
	return makeDirectory( getFilePath( path ));
}
bool copyFile(const std::string &srcFile, const std::string &destFile)
{
	if(fileExists(destFile))
	{
		std::string _destFile = "_"+destFile;
		makeDirectoryForFile(_destFile);
		if(fileExists(_destFile))
			DeleteFileA(_destFile.c_str());
		MoveFile(destFile.c_str(),_destFile.c_str());
	}
	if(fileExists(srcFile))
	{
		std::string src = convertFileNameToUnixStyle(srcFile);
		if(src.find("./") == 0)
		{
			src.erase(0,2);
		}
		std::string dest = convertFileNameToUnixStyle(destFile);
		if(dest.find("./") == 0)
		{
			dest.erase(0,2);
		}
		if(src.compare(dest) != 0)
		{
			makeDirectoryForFile(destFile);
			std::ofstream out(destFile.c_str(),std::ios::binary|std::ios::out);
			if(!out)
			{
				char buf[128];
				sprintf(buf,"����:�޷������ļ�[%s],��ȷ���ļ��Ƿ�����(���类ɱ������������)��\0",destFile.c_str());
				MessageBox(::GetDesktopWindow(),buf,"��������",MB_OK);
				return false;
			}
			else
			{
				std::ifstream in(srcFile.c_str(),std::ios::binary|std::ios::in);
				out << in.rdbuf();
				out.close();
				in.close();
				return true;
			}
		}
	}
	return false;
}
// CCreature3DXCtrl::CCreature3DXCtrl - ���캯��

CCreature3DXCtrl::CCreature3DXCtrl():
//m_exit(false),
m_creature3d(NULL),
m_thread(NULL),
m_needRestart(false)
//m_gameThread(NULL)
{
	SetInitialSize(1024,600);
	InitializeIIDs(&IID_DCreature3DX, &IID_DCreature3DXEvents);
	// TODO: �ڴ˳�ʼ���ؼ���ʵ�����ݡ�

	char   lpszPath[1024]; 
	memset(lpszPath,0,sizeof(char)*1024); 
	GetModuleFileName(AfxGetInstanceHandle(),lpszPath,1024);
	m_clientPath = getFilePath(lpszPath);
	appendLibraryFilePaths(m_clientPath);
	m_clientPath.erase(m_clientPath.size()-4,4);
	//appendLibraryFilePaths("D:\\CAI������\\new\\ClientCook\\bin");
}



// CCreature3DXCtrl::~CCreature3DXCtrl - ��������

CCreature3DXCtrl::~CCreature3DXCtrl()
{
	// TODO: �ڴ�����ؼ���ʵ�����ݡ�
	if(m_thread)
	{
		CloseHandle( m_thread );
		m_thread = NULL;
	}
}



// CCreature3DXCtrl::OnDraw - ��ͼ����

void CCreature3DXCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;

	////// TODO: �����Լ��Ļ�ͼ�����滻����Ĵ��롣
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
	//pdc->Ellipse(rcBounds);
	Sleep(100);
}



// CCreature3DXCtrl::DoPropExchange - �־���֧��

void CCreature3DXCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Ϊÿ���־õ��Զ������Ե��� PX_ ������
	PX_String(pPX,_T("strLoginInfo"),m_strLoginInfo);
}

// CCreature3DXCtrl::OnResetState - ���ؼ�����ΪĬ��״̬

void CCreature3DXCtrl::OnResetState()
{
	COleControl::OnResetState();  // ���� DoPropExchange ���ҵ���Ĭ��ֵ

	// TODO: �ڴ��������������ؼ�״̬��
}

unsigned __stdcall StartCreature3DThread(void* ctrl) 
{
	CCreature3DXCtrl *theCtrl = (CCreature3DXCtrl *)ctrl;
	theCtrl->StartCreature3D();
	return 0;
}
typedef __declspec(dllimport) int RUNCREATURE3D(char *);
void CCreature3DXCtrl::StartCreature3D(/*HWND hWndParent, HWND hWnd, int x, int y, int width, int height*/)
{
	SetCurrentDirectory(m_clientPath.c_str());
	//SetCurrentDirectory("D:\\CAI������\\new\\ClientCook");
	//////////�汾�ļ���������
	std::vector<std::string> fileNameVec;
	findFileInDir("jxjpkg\\bin",fileNameVec);
	if(!fileNameVec.empty())
	{
		std::string filename;
		for( std::vector<std::string>::iterator itr = fileNameVec.begin();
			itr != fileNameVec.end();
			++itr )
		{
			filename = *itr;
			filename.erase(0,7);
			if(copyFile(*itr,filename))
				DeleteFileA((*itr).c_str());
		}
	}
	//��д�ļ�
	WriteLoginInfo2File();

	if(!m_creature3d)
	{
		char buf[256];
#ifdef _DEBUG
		//sprintf(buf,"D:/CAI������/new/ClientCook%s\0","/bin/Creature3Dd.dll");
		sprintf(buf,"%s%s\0",m_clientPath.c_str(),"\\bin\\Creature3Dd.dll");
#else
		//sprintf(buf,"D:/CAI������/new/GameClient%s\0","/bin/Creature3D.dll");
		sprintf(buf,"%s%s\0",m_clientPath.c_str(),"\\bin\\Creature3D.dll");
#endif
		m_creature3d = LoadLibrary(buf);
	}

	if(m_creature3d)
	{
		RUNCREATURE3D* creature3DMain;
		creature3DMain = (RUNCREATURE3D*)GetProcAddress (m_creature3d, "main");
		if (creature3DMain)
		{
			RECT rect;
			GetWindowRect(&rect);
			int x = rect.left;
			int y = rect.top;
			int width = rect.right - rect.left;
			int height = rect.bottom - rect.top;
			char argv[255];
			sprintf(argv,"-hWndParent %d -Wnd %d -xpos %d -ypos %d -width %d -height %d -WebLogin %s\0",(int)m_hWnd,0,(int)x,(int)y,(int)width,(int)height, m_strLoginInfo.GetString());
			//MessageBox(argv,"Creature3DX");
			(*creature3DMain)(argv);
		}
		FreeLibrary(m_creature3d);
		m_creature3d = NULL;
	}
	else
		MessageBox("Load Creature3D.dll Faild","Creature3DX");

	if(m_needRestart)
	{
		m_needRestart = false;
		StartCreature3D();
	}
	//exit(0);
}
void CCreature3DXCtrl::OnNcDestroy()
{
	exitGame();
	waitClose();
	COleControl::OnNcDestroy();
}
typedef __declspec(dllimport) void EXITCREATURE3D();
void CCreature3DXCtrl::exitGame()
{
	if(m_creature3d)
	{
		EXITCREATURE3D* exitgame;
		exitgame = (EXITCREATURE3D*)GetProcAddress (m_creature3d, "ExitCreature3D");
		if (exitgame)
		{
			(*exitgame)();
		}
	}
}
void CCreature3DXCtrl::needRestart()
{
	m_needRestart = true;
}
void CCreature3DXCtrl::waitClose()
{
	MSG msg;
	while(m_creature3d)
	{
		//::Sleep(10);
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)>0)
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
	}
}
void CCreature3DXCtrl::WriteLoginInfo2File()
{
	FILE * pFile = fopen("jxjlogin.dat", "wb");
	fwrite(m_strLoginInfo.GetString(), 1, strlen(m_strLoginInfo) + 1, pFile);
	fclose(pFile);
}
// CCreature3DXCtrl ��Ϣ�������
static LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)  
{
	switch (msg) 
	{
	case WM_USER+10:
		{
			CCreature3DXCtrl *win=(CCreature3DXCtrl *)GetWindowLong(hWnd,GWL_USERDATA);
			win->needRestart();
		}
		break;
	//case WM_USER+602:
	//	{
	//		std::string sContet = (TCHAR*)((COPYDATASTRUCT*)lParam)->lpData;
	//		sContet += "&openid=" + g_openID;
	//		sContet += "&openkey=" + g_openKey;
	//		sContet += "&pf=" + g_pf;
	//		sContet += "&pfkey=" + g_pfKey;
	//		CcreActiveXCtrl *win=(CcreActiveXCtrl *)GetWindowLong(hWnd,GWL_USERDATA);
	//		win->showWeb(sContet.c_str());
	//		//g_webDlg.ShowWindow(SW_SHOW);
	//		//g_webDlg.setURL(sContet.c_str());
	//	}
	//	break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//void CCreature3DXCtrl::showWeb(LPCTSTR url)
//{
//	m_webDlg.ShowWindow(SW_SHOW);
//	m_webDlg.setURL(url);
//}
int CCreature3DXCtrl::OnCreate(LPCREATESTRUCT   lpCreateStruct)
{
	int r = COleControl::OnCreate(lpCreateStruct);
	if(!m_thread)
		m_thread = (HANDLE)_beginthreadex(NULL, 0, &StartCreature3DThread, (void*)this, 0, 0);
	SetWindowLong(m_hWnd,GWL_USERDATA,(long)this);
	SetWindowLongPtr(m_hWnd, GWLP_WNDPROC,(LPARAM)(WNDPROC)WinProc);  
	return r;
}
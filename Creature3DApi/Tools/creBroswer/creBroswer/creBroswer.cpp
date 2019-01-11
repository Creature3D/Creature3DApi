// creBroswer.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "creBroswer.h"
#include <map>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CcreBroswerApp

BEGIN_MESSAGE_MAP(CcreBroswerApp, CWinApp)
END_MESSAGE_MAP()


// CcreBroswerApp ����

CcreBroswerApp::CcreBroswerApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��

}


// Ψһ��һ�� CcreBroswerApp ����

CcreBroswerApp theApp;
typedef std::map<HWND,creWebDialog *> DialogMap;
DialogMap g_dialogMap;
extern  "C" __declspec(dllexport) HWND create(int x,int y,int width,int height)
{
	creWebDialog *dlg = new creWebDialog;
	dlg->Create(IDD_DIALOG1,NULL);
	dlg->ShowWindow(SW_HIDE);
	//g_dialog.MoveWindow(400,300,640,512);
	dlg->MoveWindow(x,y,width,height);
	HWND hwnd = dlg->GetSafeHwnd();
	g_dialogMap[hwnd] = dlg;
	return hwnd;
}
//extern  "C" __declspec(dllexport) HWND getHWND()
//{
//	return g_dialog.GetSafeHwnd();
//}
extern  "C" __declspec(dllexport) void Navigate(HWND hwnd,const char* url)
{
	DialogMap::iterator itr = g_dialogMap.find(hwnd);
	if(itr != g_dialogMap.end())
	{
		creWebDialog *dlg = g_dialogMap[hwnd];
		if(dlg)
		{
			dlg->Navigate(url);
			dlg->ShowWindow(SW_SHOW);
		}
	}
}

extern  "C" __declspec(dllexport) void release()
{
	for (DialogMap::iterator itr = g_dialogMap.begin();
		itr != g_dialogMap.end();
		++itr)
	{
		delete itr->second;
		itr->second = nullptr;
	}
	g_dialogMap.clear();
}

// CcreBroswerApp ��ʼ��

BOOL CcreBroswerApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

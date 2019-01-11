// LauncherDlg.h : header file
//

#pragma once

#include "CDialogSK.h"
#include "BtnST.h"
#include <afxhtml.h>
#include "UpdateNetEventSink.h"
#include "afxcmn.h"
#include "UninstallDlg.h"

#include "TextProgress.h"
#include <string>
using namespace std;
//#include "UninstallDlg.h"
//��ҳ�������װ
class CWebBrowser : public CHtmlView
{
	DECLARE_DYNCREATE(CWebBrowser)
	DECLARE_MESSAGE_MAP()

public:
	CWebBrowser();          
	virtual ~CWebBrowser();

	BOOL IsContextMenuEnabled() const { return m_bContextMenuEnabled; }
	void EnableContextMenu(BOOL newVal = TRUE) { m_bContextMenuEnabled = newVal; }

	virtual HRESULT OnGetHostInfo(DOCHOSTUIINFO *pInfo);	//ȥ����ı�Ե�Ĺ�����

	virtual void OnBeforeNavigate2(LPCTSTR lpszURL, DWORD nFlags,
		LPCTSTR lpszTargetFrameName, CByteArray& baPostedData,
		LPCTSTR lpszHeaders, BOOL* pbCancel);
	virtual HRESULT OnTranslateUrl(DWORD dwTranslate,
		OLECHAR* pchURLIn, OLECHAR** ppchURLOut);

	CString m_strGameDir;

protected:
	
	virtual void PostNcDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	

	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnDestroy();

protected:
	virtual void OnTitleChange(LPCTSTR lpszText);
	virtual void OnDocumentComplete(LPCTSTR lpszURL);

protected:
	BOOL m_bContextMenuEnabled;
};



// CLauncherDlg dialog
class CLauncherDlg : public CDialogSK, public CUpdateEventCallback
{
// Construction
public:
	CLauncherDlg(CWnd* pParent = NULL);	// standard constructor
	~CLauncherDlg();

// Dialog Data
	enum { IDD = IDD_LAUNCHER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	virtual void OnCancel();
	virtual void OnOK(){};
	void vedioSetting();
// Implementation
protected:
	HICON m_hIcon;
	CButtonST m_btnStartGame;	//��ʼ��Ϸ
	CButtonST m_btnQuit;		//�رճ���
	CButtonST m_btnMiniDlg;		//��С������
	CButtonST m_btnVideoSetting;//��ʾ���ð�ť
	CButtonST m_btnVideoLevel[5];			//��ʾģʽ
	CButtonST m_btnSelect;		//ѡ��ģʽ
	CButtonST m_btnSelectCancel;//ȡ��ѡ��
	CString m_loginurl;

	CWebBrowser m_html;	//������ؼ�
	CWebBrowser m_htmlWait;	//�ȴ���ʱ����ʾ��ҳ��
	BOOL m_isWait;

	CUpdateNetEventSink m_Download;	//����

	BOOL m_bDownloadFinish;	//���ؽ���
	BOOL m_bQuitProcess;	//�˳�����
	UINT m_uCurDownloadSize;		//��ǰ���صĴ�С
	UINT m_uCurDownloadFileSize;	//��ǰ���ص��ļ���С
	CString m_strCurDownFileName;
	CUninstallDlg m_uidlg;
	//CStatic m_staticText;//��̬�ı���
	virtual void CurDownloadProc(CString & fileName,UINT uCurDownload, UINT uTotalSize);	//��ǰ���ص��ֽ������ܵ��ļ���С
	virtual void OnDownloadFinish(const CString & strHttpFile, const CString & strLocalFile);	//�����ļ���ɵ�֪ͨ
	virtual void OnDecompressFile();

	BOOL CheckReg4Game();	//��ע����м���Ƿ�����Ϸ�������˵����Ϸ��ȷ��װ��

	void RunGame();	//������Ϸ
	void RunSetup();//���а�װ��Ϸ

	wchar_t m_strModule[256];	//·��

	void CreateDesktopShortCut(const wchar_t * pDir);	//���������ݷ�ʽ
	BOOL CanRunGame();	//����Launcher.exe�Ƿ���ڣ���������ڣ�˵�������°�װ����ǿ������

	BOOL GetFileName(CString strPath, CString & strFileName);	//�õ��ļ���

	void CopyBatchFile2DirPath(CString strFilePath, CString strDirPath);	//��txt���ļ����ļ��ƶ���ָ��Ŀ¼��

	void DoInitCheckGame();
	bool DoInitCheckUpdate();
	void CreateStartMenu();
	void CreateShortCut(CString csLinkPath, CString csExePath, CString csIconPath, CString csArg);
	string getCardInfo();
	byte m_btDownloadStage;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStartGame();
	afx_msg void OnBnClickedButtonMini();
	afx_msg void OnBnClickedButtonQuit();
	afx_msg void OnBnClickedButtonVideoSetting();
	afx_msg void OnBnClickedButtonLevelVeryLow();
	afx_msg void OnBnClickedButtonLevelLow();
	afx_msg void OnBnClickedButtonLevelNormal();
	afx_msg void OnBnClickedButtonLevelHigh();
	afx_msg void OnBnClickedButtonLevelVeryHigh();
	afx_msg void OnBnClickedButtonSelect();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CTextProgress m_Process1;
/*	afx_msg void OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult);*/
};

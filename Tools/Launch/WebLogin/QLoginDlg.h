
// qLoginDlg.h : ͷ�ļ�
//
#pragma once


#include "UpdateNetEventSink.h"
#include "CDialogSK.h"
#include <string>
// CqLoginDlg �Ի���
class CqLoginDlg : public CDialogSK, public CUpdateEventCallback
{
// ����
public:
	CqLoginDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CqLoginDlg();
// �Ի�������
	enum { IDD = IDD_QLOGIN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	virtual void OnCancel(){};
	virtual void OnOK(){};

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void Install();
// ʵ��
protected:
	std::string getCardInfo();
	void vedioSetting();
	HICON m_hIcon;
	CUpdateNetEventSink m_Download;
	wchar_t m_strModule[256];	//·��
	CProgressCtrl m_Process;
	CStatic m_Text;
	CButton m_button1;
	CButton m_button2;
	byte m_btDownloadStage;
	BOOL m_bQuitProcess;	//�˳�����
	UINT m_uCurDownloadSize;		//��ǰ���صĴ�С
	UINT m_uCurDownloadFileSize;	//��ǰ���ص��ļ���С
	bool flag;

	virtual void CurDownloadProc(CString & fileName,UINT uCurDownload, UINT uTotalSize);	//��ǰ���ص��ֽ������ܵ��ļ���С
	virtual void OnDownloadFinish(const CString & strHttpFile, const CString & strLocalFile);	//�����ļ���ɵ�֪ͨ
	virtual void OnDecompressFile();
	virtual void OnGameLog();
	BOOL GetFileName(CString strPath, CString & strFileName);	//�õ��ļ���
	void DoInitCheckGame();
	bool DoInitCheckUpdate();
	void CopyBatchFile2DirPath(CString strFilePath, CString strDirPath);	//��txt���ļ����ļ��ƶ���ָ��Ŀ¼��
	BOOL CanRunGame();	//����Launcher.exe�Ƿ���ڣ���������ڣ�˵�������°�װ����ǿ������
	BOOL CheckReg4Game();	//��ע����м���Ƿ�����Ϸ�������˵����Ϸ��ȷ��װ��;
	void CreateStartMenu();
	void CreateShortCut(CString csLinkPath, CString csExePath, CString csIconPath, CString csArg);
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};

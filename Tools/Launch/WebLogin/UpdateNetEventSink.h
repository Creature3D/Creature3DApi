#pragma once

class CUpdateEventCallback
{
public:
	CUpdateEventCallback(){}

	virtual void CurDownloadProc(CString & fileName,UINT uCurDownload, UINT uTotalSize){};	//��ǰ���ص��ֽ������ܵ��ļ���С

	virtual void OnDownloadFinish(const CString & strHttpFile, const CString & strLocalFile){};	//�����ļ���ɵ�֪ͨ

	virtual void OnDecompressFile(){};	//��ʼ��ѹ�ļ�

	virtual void OnGameLog(){};
};

//�����ļ�
class CUpdateNetEventSink
{
public:
	CUpdateNetEventSink(CUpdateEventCallback * pCallback);
	~CUpdateNetEventSink(void);

	bool Init();
	void Uninit();

	void StartDownload(CString strFileURLInServer, CString strFileLocalFullPath);

	void ProcDownload();	//ִ����������

	bool m_bIsDownloading;	//�Ƿ���������

	bool m_bStartCompress;	//�Ƿ�ʼ��ѹ
	BOOL m_bQuitProcess;	//�˳�����

	wchar_t m_strModule[256];	//·��

	bool DownloadFile( CString strFileURLInServer, CString strFileLocalFullPath, bool bCallBack = true);	//�����ļ�
	bool GameLog(CString strURL);
protected:
	CString m_strFileURLInServer;
	CString m_strFileLocalFullPath;

	//wchar_t m_szFileURLInServer[500];
	//wchar_t m_szFileLocalFullPath[500];

	CWinThread * m_pThread;		//�����߳�

	bool m_bInit;	//�Ƿ��ʼ����
public:
	CUpdateEventCallback * m_pCallBack;	//�¼�֪ͨ
};


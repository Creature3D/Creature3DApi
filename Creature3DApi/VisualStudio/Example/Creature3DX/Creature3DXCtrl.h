#pragma once
// Creature3DXCtrl.h : CCreature3DXCtrl ActiveX �ؼ����������
#include <string>

// CCreature3DXCtrl : �й�ʵ�ֵ���Ϣ������� Creature3DXCtrl.cpp��

class CCreature3DXCtrl : public COleControl
{
	DECLARE_DYNCREATE(CCreature3DXCtrl)

// ���캯��
public:
	CCreature3DXCtrl();

// ��д
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	void StartCreature3D();
	void needRestart();
	void waitClose();
	void exitGame();
// ʵ��
protected:
	~CCreature3DXCtrl();
	afx_msg int OnCreate(LPCREATESTRUCT   lpCreateStruct); 
	afx_msg void OnNcDestroy();
	//bool m_exit;
	HMODULE m_creature3d;
	HANDLE m_thread;
	std::string m_clientPath;
	bool m_needRestart;
	//crGameThread *m_gameThread;
	DECLARE_OLECREATE_EX(CCreature3DXCtrl)    // �๤���� guid
	DECLARE_OLETYPELIB(CCreature3DXCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CCreature3DXCtrl)     // ����ҳ ID
	DECLARE_OLECTLTYPE(CCreature3DXCtrl)		// �������ƺ�����״̬
	CString m_strLoginInfo;

	void WriteLoginInfo2File();	//����¼��Ϣд�ļ�
// ��Ϣӳ��
	DECLARE_MESSAGE_MAP()

// ����ӳ��
	DECLARE_DISPATCH_MAP()

// �¼�ӳ��
	DECLARE_EVENT_MAP()

// ���Ⱥ��¼� ID
public:
	enum {
	};
};


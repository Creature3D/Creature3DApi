#pragma once

// Creature3DXPropPage.h : CCreature3DXPropPage ����ҳ���������


// CCreature3DXPropPage : �й�ʵ�ֵ���Ϣ������� Creature3DXPropPage.cpp��

class CCreature3DXPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CCreature3DXPropPage)
	DECLARE_OLECREATE_EX(CCreature3DXPropPage)

// ���캯��
public:
	CCreature3DXPropPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_CREATURE3DX };

// ʵ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ��Ϣӳ��
protected:
	DECLARE_MESSAGE_MAP()
};


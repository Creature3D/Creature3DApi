// Creature3DXPropPage.cpp : CCreature3DXPropPage ����ҳ���ʵ�֡�

#include "stdafx.h"
#include "Creature3DX.h"
#include "Creature3DXPropPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CCreature3DXPropPage, COlePropertyPage)



// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CCreature3DXPropPage, COlePropertyPage)
END_MESSAGE_MAP()



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CCreature3DXPropPage, "CREATURE3DX.Creature3DXPropPage.1",
	0x5ddfb85, 0x9dfd, 0x4d06, 0x91, 0x3f, 0x4c, 0x19, 0x46, 0xfc, 0x6a, 0x1a)



// CCreature3DXPropPage::CCreature3DXPropPageFactory::UpdateRegistry -
// ��ӻ��Ƴ� CCreature3DXPropPage ��ϵͳע�����

BOOL CCreature3DXPropPage::CCreature3DXPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_CREATURE3DX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}



// CCreature3DXPropPage::CCreature3DXPropPage - ���캯��

CCreature3DXPropPage::CCreature3DXPropPage() :
	COlePropertyPage(IDD, IDS_CREATURE3DX_PPG_CAPTION)
{
}



// CCreature3DXPropPage::DoDataExchange - ��ҳ�����Լ��ƶ�����

void CCreature3DXPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDP_PostProcessing(pDX);
}



// CCreature3DXPropPage ��Ϣ�������

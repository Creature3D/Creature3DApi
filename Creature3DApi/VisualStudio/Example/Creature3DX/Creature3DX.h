#pragma once

// Creature3DX.h : Creature3DX.DLL ����ͷ�ļ�

#if !defined( __AFXCTL_H__ )
#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // ������


// CCreature3DXApp : �й�ʵ�ֵ���Ϣ������� Creature3DX.cpp��

class CCreature3DXApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;


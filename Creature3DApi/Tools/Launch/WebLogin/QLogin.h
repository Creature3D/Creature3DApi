
// qLogin.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CqLoginApp:
// �йش����ʵ�֣������ qLogin.cpp
//

class CqLoginApp : public CWinApp
{
public:
	CqLoginApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CqLoginApp theApp;
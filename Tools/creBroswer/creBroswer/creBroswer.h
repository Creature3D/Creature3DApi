// creBroswer.h : creBroswer DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "creWebDialog.h"

// CcreBroswerApp
// �йش���ʵ�ֵ���Ϣ������� creBroswer.cpp
//

class CcreBroswerApp : public CWinApp
{
public:
	CcreBroswerApp();
	void WriteWebBrowserRegKey(LPCTSTR lpKey, DWORD dwValue);
	char m_exeName[256];
// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

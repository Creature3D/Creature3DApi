// creWebDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "creBroswer.h"
#include "creWebDialog.h"


// creWebDialog �Ի���

IMPLEMENT_DYNCREATE(creWebDialog, CDHtmlDialog)

creWebDialog::creWebDialog(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(creWebDialog::IDD, creWebDialog::IDH, pParent)
{

}

creWebDialog::~creWebDialog()
{
}

void creWebDialog::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
}

BOOL creWebDialog::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

BEGIN_MESSAGE_MAP(creWebDialog, CDHtmlDialog)
END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(creWebDialog)
	DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
	DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
END_DHTML_EVENT_MAP()



// creWebDialog ��Ϣ�������

HRESULT creWebDialog::OnButtonOK(IHTMLElement* /*pElement*/)
{
	OnOK();
	return S_OK;
}

HRESULT creWebDialog::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	OnCancel();
	return S_OK;
}


LRESULT creWebDialog::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: �ڴ����ר�ô����/����û���
	//if(message == WM_ERASEBKGND)
	//	return TRUE;
	return CDHtmlDialog::WindowProc(message, wParam, lParam);
}

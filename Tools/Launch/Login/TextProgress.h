#pragma once
#ifndef AFX_TEXTPROGRESS1_H__INCLUDED_
#define AFX_TEXTPROGRESS1_H__INCLUDED_

#include <afxcmn.h>

class CTextProgress : public CProgressCtrl
{
	// Construction
public:
	CTextProgress();
	COLORREF m_crText;  //�ı���ɫ
	COLORREF m_crProgress; //������ɫ
	COLORREF m_crBlank;  //�հ�������ɫ

private:
	CString m_strText;
	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextProgress)
	//}}AFX_VIRTUAL

	// Implementation
public:
	virtual ~CTextProgress();

	void setText(CString & str);
	CString getText(){return m_strText;}
	// Generated message map functions
protected:
	//{{AFX_MSG(CTextProgress)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif





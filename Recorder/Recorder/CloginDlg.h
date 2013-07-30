#include "Resource.h"
#if !defined(AFX_LOGINDLG_H__181C56B7_5FF5_49BA_BA85_46B110E42CD4__INCLUDED_)
#define AFX_LOGINDLG_H__181C56B7_5FF5_49BA_BA85_46B110E42CD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CloginDlg :public CDialog
{
	public:
		CloginDlg(CWnd* pParent = NULL);
		

		// Dialog Data
		enum { IDD = IDD_LOGIN_DIALOG};
		CString	m_PassWord;
		CString	m_UserName;
	protected:
		virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
		//virtual void Verification();
		//virtual void Registration();

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnVerification();
	afx_msg void OnEmplification();
	afx_msg void OnFileExit();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGINDLG_H__181C56B7_5FF5_49BA_BA85_46B110E42CD4__INCLUDED_)
#pragma once


// UserInfoDlg dialog

class UserInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(UserInfoDlg)
public:
	UserInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~UserInfoDlg();

// Dialog Data
	enum { IDD = IDD_USERINFO_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	
	DECLARE_MESSAGE_MAP()
public:
	BOOL OldUser;
	CString username;
	CString userid;
	CString department;
	CString email;
	afx_msg void OnSubmit();
	afx_msg void OnExit();
	afx_msg void OnTypeChek();
};

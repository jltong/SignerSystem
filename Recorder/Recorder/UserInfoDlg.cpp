// UserInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Users.h"
#include "Recorder.h"
#include "UserInfoDlg.h"
#include "afxdialogex.h"


// UserInfoDlg dialog

IMPLEMENT_DYNAMIC(UserInfoDlg, CDialogEx)

UserInfoDlg::UserInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(UserInfoDlg::IDD, pParent)
	, username(_T(""))
	, userid(_T(""))
	, department(_T(""))
	, email(_T(""))
{
	OldUser = FALSE;
}

UserInfoDlg::~UserInfoDlg()
{
}

void UserInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_USERNAMEG_EDIT, username);
	DDX_Text(pDX, IDC_USERID_EDIT, userid);
	DDX_Text(pDX, IDC_DEPARTMENT_EDIT, department);
	DDX_Text(pDX, IDC_EMAIL_EDIT, email);
}


BEGIN_MESSAGE_MAP(UserInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDC_UISUBMIT_BUTTON, &UserInfoDlg::OnSubmit)
	ON_BN_CLICKED(IDC_UIEXIT_BUTTON, &UserInfoDlg::OnExit)
	ON_BN_CLICKED(IDC_TYPE_CHECK, &UserInfoDlg::OnTypeChek)
END_MESSAGE_MAP()


// UserInfoDlg message handlers


void UserInfoDlg::OnSubmit()
{

	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
	Users userinfo(username,userid,department,email);

	if(this->OldUser == TRUE&&!userinfo.isExist(username,_T("userinfo"))){
		AfxMessageBox(_T("Make sure that you are a registered user before your check to the 'OldUser' checkbox."));
		((CEdit *)GetDlgItem(IDC_USERNAMEG_EDIT))->SetWindowText(NULL);
		return;
	}
	else if(this->OldUser == TRUE && userinfo.isExist(username,_T("userinfo"))){
		AfxMessageBox(_T("Qualified User."));
		return;
	}

	if(username==""||userid==""||department==""||email==""){
		AfxMessageBox(_T("Make sure that you have filled in all the blank before your submission"));
		return;
	}
	
	
	if(userinfo.isExistId(userid,_T("userinfo"))){
		userinfo.UpdateInfo(username,userid,department,email);
		AfxMessageBox(_T("用户信息已更新"));
		return;
	}
	if(userinfo.InsertUserInfo())
		AfxMessageBox(_T("注册成功！"));
	else
		AfxMessageBox(_T("注册失败！"));
}


void UserInfoDlg::OnExit()
{
	Users user;
	if(!user.isExist(this->username,_T("userinfo"))){
		AfxMessageBox(_T("He/She is not a qualified user."));
		((CEdit *)GetDlgItem(IDC_USERNAMEG_EDIT))->SetWindowText(NULL);
		return;
	}
	CDialog::OnOK();
}


void UserInfoDlg::OnTypeChek()
{
	// TODO: Add your control notification handler code here
	if ( BST_CHECKED == IsDlgButtonChecked( IDC_TYPE_CHECK) ){
		OldUser = TRUE;
		((CWnd *)(this->GetDlgItem(IDC_USERID_EDIT)))->EnableWindow(FALSE);
		((CWnd *)(this->GetDlgItem(IDC_DEPARTMENT_EDIT)))->EnableWindow(FALSE);
		((CWnd *)(this->GetDlgItem(IDC_EMAIL_EDIT)))->EnableWindow(FALSE);
		
	}
	else{
		OldUser = FALSE;
		((CWnd *)(this->GetDlgItem(IDC_USERID_EDIT)))->EnableWindow(TRUE);
		((CWnd *)(this->GetDlgItem(IDC_DEPARTMENT_EDIT)))->EnableWindow(TRUE);
		((CWnd *)(this->GetDlgItem(IDC_EMAIL_EDIT)))->EnableWindow(TRUE);
	}
	

}

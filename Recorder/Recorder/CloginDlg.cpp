#include "stdafx.h"
#include "CloginDlg.h"
#include "Users.h"
#include "ADOConn.h"
#include "RecorderDlg.h"
#define SuperUser _T("1") 
CloginDlg::CloginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CloginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginDlg)
	m_PassWord = _T("");
	m_UserName = _T("");
	//}}AFX_DATA_INIT

}

void CloginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PASSWORD_EDIT, m_PassWord);
	DDX_Text(pDX, IDC_USRNAME_EDIT, m_UserName);
}




BEGIN_MESSAGE_MAP(CloginDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CloginDlg::OnVerification)
	ON_BN_CLICKED(IDC_LOGIN_EMPTY, &CloginDlg::OnEmplification)
	ON_COMMAND(ID_FILE_EXIT, &CloginDlg::OnFileExit)
END_MESSAGE_MAP()


void CloginDlg::OnVerification()
{
	// TODO: Add your control notification handler code here
	//将对话框中编辑框的数据读取到成员变量中
	UpdateData(TRUE);
	//检查数据有效性
	if (m_UserName == "")
	{
		AfxMessageBox(_T("请输入用户名"));
		return;
	}
	if (m_PassWord == "")
	{
		AfxMessageBox(_T("请输入密码"));
		return;
	}
	Users user;
	if(!user.isExist(m_UserName,_T("login"))){
		AfxMessageBox(_T("用户不存在"));
		return;
	} 
	user.GetInfo(m_UserName);

	if(user.getPassWord()!=m_PassWord){
		AfxMessageBox(_T("密码错误"));
		return;
	}
	else{
		CRecorderDlg dlg;
		dlg.DoModal();
	}
}




void CloginDlg::OnEmplification()
{
	// TODO: Add your control notification handler code here
	((CEdit *)GetDlgItem(IDC_USRNAME_EDIT))->SetWindowText(NULL);
	((CEdit *)GetDlgItem(IDC_PASSWORD_EDIT))->SetWindowText(NULL);
}


void CloginDlg::OnFileExit()
{
	// TODO: Add your command handler code here
	CDialog::EndDialog(0);
}

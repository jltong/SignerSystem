
// Recorder.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Recorder.h"
#include "CloginDlg.h"
#include "FirstPageDlg.h"
#include "RecorderDlg.h"
#include "CloginDlg.h"
#include "mclmcrrt.h"
#include "mclmcr.h"

#include "Training.h"
#include "TestSpeech.h"
#include "IncTrain.h"
#include "Initialize.h"
#include "mclcppclass.h"
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"mclmcr.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <odbcinst.h>
 #pragma comment(lib, "odbccp32.lib")

// CRecorderApp

BEGIN_MESSAGE_MAP(CRecorderApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CRecorderApp construction

CRecorderApp::CRecorderApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CRecorderApp object

CRecorderApp theApp;


// CRecorderApp initialization

BOOL CRecorderApp::InitInstance()
{
	

	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	
	//the Initialization for the call of external dll and lib!!!
	bool res = false,res1=false,res2=false,res3=false;
		res = mclInitializeApplication(NULL,0);
	if (!res)
	{
		AfxMessageBox(_T("初始化Application错误！"));
	}
	res = InitializeInitialize();
	res1 = TrainingInitialize();
	res2 = IncTrainInitialize();
	res3 = TestSpeechInitialize();
	if (!res||!res1||!res2||!res3)
	{
		AfxMessageBox(_T("初始化Lib错误！"));
	}

	/*
	 CString szPath; 
	 GetModuleFileName(NULL,szPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH); 
	 szPath.ReleaseBuffer(); 
 
	 int nPos; 
	 nPos=szPath.ReverseFind ('\\'); 
	 szPath=szPath.Left (nPos); 
	 nPos=szPath.ReverseFind ('\\'); 
	 szPath=szPath.Left (nPos); 
	 CString szFile = szPath + "\\SR1.accdb"; 

	 CString str;
	 str.Format(_T("DSN=%s!DBQ=%s!DEFAULTDIR=%s!!"),_T("sign_dsn"),szFile,szPath);
	 
	 int nlen = str.GetLength();
	 for (int i=0; i<nlen; i++) {
		 if (str.GetAt(i) == '!') 
			 str.SetAt(i,'\0'); 
	 } 
 
	//自动注册ODBC数据源
	 if (FALSE == SQLConfigDataSource(NULL, ODBC_ADD_DSN, _T("Microsoft Access Driver (*.mdb, *.accdb)\0"), str)) {
		AfxMessageBox(_T("SQLConfigDataSource Failed")); 
	 }

	*/

	CString sPath;
	GetModuleFileName(NULL,sPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	sPath.ReleaseBuffer();
	int nPos;
	nPos=sPath.ReverseFind ('\\');
	sPath=sPath.Left (nPos);

	CString lpszFile = sPath + "\\SR1.accdb";
	
	//AfxMessageBox(lpszFile);//
	

	CString str;
	str.Format(_T("DSN=%s? DBQ=%s? FIL=MicrosoftAccess? DEFAULTDIR=%s?? "),_T("SRDSN"),lpszFile,sPath);

	int mlen = str.GetLength();
    for (int i=0; i<mlen; i++)
	{
		if (str.GetAt(i) == '?')
			str.SetAt(i,'\0');
	}

  if (FALSE == SQLConfigDataSource(NULL,ODBC_ADD_DSN,_T("Microsoft Access Driver (*.mdb, *.accdb)\0"),str))
		AfxMessageBox(_T("SQLConfigDataSource Failed"));
  
  //seek for the folder,if not exist,create it.
	CString folderName = _T("E:\\Speechdata");
	
	if(!PathIsDirectory(folderName)){
		CreateDirectory(folderName,NULL);
	}
	folderName = _T("E:\\Speechdata\\Test");
	if(!PathIsDirectory(folderName)){
		CreateDirectory(folderName,NULL);
	}
	CFirstPageDlg cfpdlg;
	cfpdlg.DoModal();

	


	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.

	InitializeTerminate();
	TrainingTerminate();
	IncTrainTerminate();
	TestSpeechTerminate();
	res = mclTerminateApplication();
	if (!res)
	{
		AfxMessageBox(_T("结束Application错误!"));
	}
	return FALSE;
}




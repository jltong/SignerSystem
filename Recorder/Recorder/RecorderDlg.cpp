
// RecorderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "tchar.h"
#include<cstdlib>
#include<cstring>
#include<string>
#include <locale.h>
#include "Recorder.h"
#include "RecorderDlg.h"
#include "UserInfoDlg.h"
#include "CloginDlg.h"
#include "afxdialogex.h"
#include "mclmcrrt.h"
#include "mclmcr.h"
#include "Training.h"
#include "TestSpeech.h"
#include "IncTrain.h"
#include "Initialize.h"
#include "mclcppclass.h"
#include "mat.h"
#include "matrix.h"
#include "Users.h"
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"mclmcr.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	
END_MESSAGE_MAP()


// CRecorderDlg dialog




CRecorderDlg::CRecorderDlg(CWnd* pParent )
	: CDialog(CRecorderDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	guestname=_T("");
	guestid=_T("");
	wavname=_T("");
	testwavname=_T("");
	anyGuest=FALSE;
	isSelect=FALSE;

	bRecording=FALSE;
	bPlaying=FALSE;
	bReverse=FALSE;
	bPaused=FALSE;
	bEnding=FALSE;
	bTerminating=FALSE;
	Pause=FALSE;
	dwDataLength=0;
	dwRepetitions=1;
}


void CRecorderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, guestname);
	//DDX_Text(pDX, IDC_USRNAME_EDIT, m_UserName);
	
	//将对话框中编辑框的数据读取到成员变量中
	//UpdateData(TRUE);
}

BEGIN_MESSAGE_MAP(CRecorderDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_HELP_ABOUT, OnHelpAbout)

	
	
	ON_MESSAGE(MM_WIM_OPEN,OnMM_WIM_OPEN)
	ON_MESSAGE(MM_WIM_DATA,OnMM_WIM_DATA)
	ON_MESSAGE(MM_WIM_CLOSE,OnMM_WIM_CLOSE)
	ON_MESSAGE(MM_WOM_OPEN,OnMM_WOM_OPEN)
	ON_MESSAGE(MM_WOM_DONE,OnMM_WOM_DONE)
	ON_MESSAGE(MM_WOM_CLOSE,OnMM_WOM_CLOSE)
	ON_WM_DESTROY()
	
	ON_BN_CLICKED(IDC_REC_START, OnRecStart)
	ON_BN_CLICKED(IDC_REC_STOP, OnRecStop)
	ON_BN_CLICKED(IDC_PLAY_START, OnPlayStart)
	ON_BN_CLICKED(IDC_PLAY_PAUSE, OnPlayPause)
	ON_BN_CLICKED(IDC_PLAY_STOP, OnPlayStop)
	ON_BN_CLICKED(IDC_REC_SAVE, OnSaveRec)
	ON_BN_CLICKED(IDC_TRAIN,OnTrain)
	ON_BN_CLICKED(IDC_TEST,OnTest)
	ON_WM_TIMER()
	
	ON_COMMAND(ID_HELP_ABOUT, OnHelpAbout)
	ON_COMMAND(ID_BASIC_EXIT,OnExit)
	ON_BN_CLICKED(IDC_OBTAINUSERINFO_BUTTON, OnUserObtain)
	ON_BN_CLICKED(IDC_BROWSE1, &CRecorderDlg::OnTrainBrowse)
	ON_BN_CLICKED(IDC_BROWSE2, &CRecorderDlg::OnTestBrowse)
END_MESSAGE_MAP()


// CRecorderDlg message handlers

BOOL CRecorderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	//we can add custom menu here!!!

	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	HICON hlcon=AfxGetApp()->LoadIconW(IDI_S1);
	HICON hlcon1=AfxGetApp()->LoadIconW(IDI_S2);
	((CButton *)GetDlgItem(IDC_BROWSE1))->SetIcon(hlcon);
	
	((CButton *)GetDlgItem(IDC_BROWSE2))->SetIcon(hlcon1);

	// TODO: Add extra initialization here
	pWaveHdr1=reinterpret_cast<PWAVEHDR>(malloc(sizeof(WAVEHDR)));
	pWaveHdr2=reinterpret_cast<PWAVEHDR>(malloc(sizeof(WAVEHDR)));
	
	//allocate memory for save buffer
	pSaveBuffer = reinterpret_cast<PBYTE>(malloc(1));
	
	

	return TRUE;  
}

void CRecorderDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		if(nID==SC_MINIMIZE )
			ShowWindow(SW_SHOWMINIMIZED);
		else
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRecorderDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRecorderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);//difference
}
void CRecorderDlg::OnRecStart() 
{
	// TODO: Add your control notification handler code here
	//allocate buffer memory
	pBuffer1=(PBYTE)malloc(INP_BUFFER_SIZE);
	pBuffer2=(PBYTE)malloc(INP_BUFFER_SIZE);
	if (!pBuffer1 || !pBuffer2) {
		if (pBuffer1) free(pBuffer1);
		if (pBuffer2) free(pBuffer2);
		MessageBeep(MB_ICONEXCLAMATION);
		AfxMessageBox(TEXT("Memory erro!"));//TEXT()
		return ;
	}
	
	//open waveform audo for input
	
	waveform.wFormatTag=WAVE_FORMAT_PCM;
	waveform.nChannels=1;
	waveform.nSamplesPerSec=11025;
	waveform.nAvgBytesPerSec=11025;
	waveform.nBlockAlign=1;
	waveform.wBitsPerSample=8;
	waveform.cbSize=0;

	
	if (waveInOpen(&hWaveIn,WAVE_MAPPER,&waveform,(DWORD)this->m_hWnd,NULL,CALLBACK_WINDOW)) {
		free(pBuffer1);
		free(pBuffer2);
		MessageBeep(MB_ICONEXCLAMATION);
		AfxMessageBox(TEXT("Audio can not be open!"));
	}
	pWaveHdr1->lpData=(LPSTR)pBuffer1;
	pWaveHdr1->dwBufferLength=INP_BUFFER_SIZE;
	pWaveHdr1->dwBytesRecorded=0;
	pWaveHdr1->dwUser=0;
	pWaveHdr1->dwFlags=0;
	pWaveHdr1->dwLoops=1;
	pWaveHdr1->lpNext=NULL;
	pWaveHdr1->reserved=0;
	
	waveInPrepareHeader(hWaveIn,pWaveHdr1,sizeof(WAVEHDR));
	
	pWaveHdr2->lpData=(LPSTR)pBuffer2;
	pWaveHdr2->dwBufferLength=INP_BUFFER_SIZE;
	pWaveHdr2->dwBytesRecorded=0;
	pWaveHdr2->dwUser=0;
	pWaveHdr2->dwFlags=0;
	pWaveHdr2->dwLoops=1;
	pWaveHdr2->lpNext=NULL;
	pWaveHdr2->reserved=0;
	
	waveInPrepareHeader(hWaveIn,pWaveHdr2,sizeof(WAVEHDR));
	
	//////////////////////////////////////////////////////////////////////////
	pSaveBuffer = (PBYTE)realloc (pSaveBuffer, 1) ;
	// Add the buffers
	
	waveInAddBuffer (hWaveIn, pWaveHdr1, sizeof (WAVEHDR)) ;
	waveInAddBuffer (hWaveIn, pWaveHdr2, sizeof (WAVEHDR)) ;
	
	// Begin sampling
	
	bRecording = TRUE ;
	bEnding = FALSE ;
	dwDataLength = 0 ;
	waveInStart (hWaveIn) ;
}

void CRecorderDlg::OnRecStop() 
{
	// TODO: Add your control notification handler code here
	TRACE("rec stop \n");
	if(bEnding!=TRUE){
		bEnding=TRUE;
		CString sttr,strt;
		strt.Format(_T("00:00:00"));
		sttr=strt;
		count=0;
		((CWnd *)GetDlgItem(IDC_STATIC))->SetWindowText(sttr);
		((CProgressCtrl*)GetDlgItem(IDC_PROGRESS1))-> SetPos(count/10);
		waveInReset(hWaveIn);
	}

}
LRESULT CRecorderDlg::OnMM_WIM_OPEN(UINT wParam, LONG lParam) 
{
	// TODO: Add your message handler code here and/or call default
	((CWnd *)(this->GetDlgItem(IDC_REC_START)))->EnableWindow(FALSE);
	((CWnd *)(this->GetDlgItem(IDC_REC_STOP)))->EnableWindow(TRUE);
	((CWnd *)(this->GetDlgItem(IDC_REC_SAVE)))->EnableWindow(FALSE);
	((CWnd *)(this->GetDlgItem(IDC_PLAY_START)))->EnableWindow(FALSE);
	((CWnd *)(this->GetDlgItem(IDC_PLAY_PAUSE)))->EnableWindow(FALSE);
	((CWnd *)(this->GetDlgItem(IDC_PLAY_STOP)))->EnableWindow(FALSE);

	if(count!=0)
		count=0;
	SetTimer(1,100,NULL);
	bRecording=TRUE;

	return 0;

//	TRACE("MM_WIM_OPEN\n");
}
LRESULT CRecorderDlg::OnMM_WIM_DATA(UINT wParam, LONG lParam) 
{
	// TODO: Add your message handler code here and/or call default
	// Reallocate save buffer memory
	
	//////////////////////////////////////////////////////////////////////////
	
	pNewBuffer = (PBYTE)realloc (pSaveBuffer, dwDataLength +
		((PWAVEHDR) lParam)->dwBytesRecorded) ;
	
	if (pNewBuffer == NULL)
	{
		waveInClose (hWaveIn) ;
		MessageBeep (MB_ICONEXCLAMATION) ;
		AfxMessageBox(TEXT("erro memory"));
		return 0;
	}
	
	pSaveBuffer = pNewBuffer ;
	//////////////////////////////////////////////////////////////////////////
	
	CopyMemory (pSaveBuffer + dwDataLength, ((PWAVEHDR) lParam)->lpData,
		((PWAVEHDR) lParam)->dwBytesRecorded) ;
	
	dwDataLength += ((PWAVEHDR) lParam)->dwBytesRecorded ;
	
	if (bEnding)
	{
		waveInClose (hWaveIn) ;
		return 0 ;
	}

	waveInAddBuffer (hWaveIn, (PWAVEHDR) lParam, sizeof (WAVEHDR)) ;
	TRACE("done input data\n");
	return 0;

	
}

LRESULT CRecorderDlg::OnMM_WIM_CLOSE(UINT wParam, LONG lParam) 
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(1);
	TRACE("MM_WIM_CLOSE\n");
	if (0==dwDataLength) {
		return 0;
	}
	

	waveInUnprepareHeader (hWaveIn, pWaveHdr1, sizeof (WAVEHDR)) ;
	waveInUnprepareHeader (hWaveIn, pWaveHdr2, sizeof (WAVEHDR)) ;
	
	free (pBuffer1) ;
	free (pBuffer2) ;
	
	if (dwDataLength > 0)
	{
		//enable play
		((CWnd *)(this->GetDlgItem(IDC_REC_START)))->EnableWindow(TRUE);
		((CWnd *)(this->GetDlgItem(IDC_REC_STOP)))->EnableWindow(FALSE);
		((CWnd *)(this->GetDlgItem(IDC_REC_SAVE)))->EnableWindow(TRUE);
		((CWnd *)(this->GetDlgItem(IDC_PLAY_START)))->EnableWindow(TRUE);
		((CWnd *)(this->GetDlgItem(IDC_PLAY_PAUSE)))->EnableWindow(FALSE);
		((CWnd *)(this->GetDlgItem(IDC_PLAY_STOP)))->EnableWindow(FALSE);
	}
	bRecording = FALSE ;
	((CWnd *)(this->GetDlgItem(IDC_REC_START)))->EnableWindow(TRUE);
	((CWnd *)(this->GetDlgItem(IDC_REC_STOP)))->EnableWindow(FALSE);
	
	
	

	return 0;
	
}


void CRecorderDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	CDialog::OnClose();
	if (bRecording) {
		bTerminating=TRUE;
		bEnding=TRUE;
		waveInReset(hWaveIn);
		TRACE("waveInReset\n");
		Sleep(500);
		//return CWinThread::ExitInstance();
	}
	if (bPlaying) {
		bTerminating=TRUE;
		bEnding=TRUE;
		waveOutReset(hWaveOut);
		Sleep(500);
		//return CWinThread::ExitInstance();
	}
	free (pWaveHdr1) ;
	free (pWaveHdr2) ;
	free (pSaveBuffer) ;
	
	

}

void CRecorderDlg::OnPlayStart() 
{
	
	// TODO: Add your control notification handler code here
	
	if((bPlaying==FALSE)&&(bPaused==TRUE))
	{
		bPaused=FALSE;
		bPlaying=TRUE;
		Pause=FALSE;
		waveOutRestart(hWaveOut);
		
		((CWnd *)(this->GetDlgItem(IDC_REC_START)))->EnableWindow(TRUE);
		((CWnd *)(this->GetDlgItem(IDC_REC_STOP)))->EnableWindow(FALSE);
		((CWnd *)(this->GetDlgItem(IDC_PLAY_START)))->EnableWindow(FALSE);
		((CWnd *)(this->GetDlgItem(IDC_PLAY_PAUSE)))->EnableWindow(TRUE);
		((CWnd *)(this->GetDlgItem(IDC_PLAY_STOP)))->EnableWindow(TRUE);
		
		return;
	}	
	//open waveform audio for output
	waveform.wFormatTag		=	WAVE_FORMAT_PCM;
	waveform.nChannels		=	1;
	waveform.nSamplesPerSec	=11025;
	waveform.nAvgBytesPerSec=11025;
	waveform.nBlockAlign	=1;
	waveform.wBitsPerSample	=8;
	waveform.cbSize			=0;
	
	
	if (waveOutOpen(&hWaveOut,WAVE_MAPPER,&waveform,(DWORD)this->m_hWnd,NULL,CALLBACK_WINDOW)) {
		MessageBeep(MB_ICONEXCLAMATION);
		AfxMessageBox(TEXT("Audio output error"));
	}
	

	return ;
	
}

void CRecorderDlg::OnPlayPause() 
{
	// TODO: Add your control notification handler code here
	if (!bPlaying) {
		return;
	}
	if (!bPaused) {
		Pause=TRUE;
		bPaused = TRUE;
		bPlaying  = FALSE;
		waveOutPause(hWaveOut);
		
		((CWnd *)(this->GetDlgItem(IDC_REC_START)))->EnableWindow(TRUE);
		((CWnd *)(this->GetDlgItem(IDC_REC_STOP)))->EnableWindow(FALSE);
		((CWnd *)(this->GetDlgItem(IDC_PLAY_START)))->EnableWindow(TRUE);
		((CWnd *)(this->GetDlgItem(IDC_PLAY_PAUSE)))->EnableWindow(FALSE);
		((CWnd *)(this->GetDlgItem(IDC_PLAY_STOP)))->EnableWindow(TRUE);
	}
	//if(bPlaying&(!bPaused)) 
	
	return ;
	
}

void CRecorderDlg::OnPlayStop() 
{
	
	// TODO: Add your control notification handler code here
	/*
	if (!bPlaying) {
		return ;
	}
	*/
	//comment the code above which enable us stopplay when it is paused.!!
	bEnding=TRUE;
	Pause=FALSE;

	CString sttr,strt;
	strt.Format(_T("00:00:00"));
	sttr=strt;
	count=0;

	((CWnd *)GetDlgItem(IDC_STATIC))->SetWindowText(sttr);
	((CProgressCtrl*)GetDlgItem(IDC_PROGRESS1))-> SetPos(count/10);
	waveOutReset(hWaveOut);
	
	return ;

	
}


LRESULT CRecorderDlg::OnMM_WOM_OPEN(UINT wParam, LONG lParam){
	TRACE("open MM_WOM_OPEN\n");
	// Set up header
	
	pWaveHdr1->lpData          = (LPSTR)pSaveBuffer ;
	pWaveHdr1->dwBufferLength  = dwDataLength ;
	pWaveHdr1->dwBytesRecorded = 0 ;
	pWaveHdr1->dwUser          = 0 ;
	pWaveHdr1->dwFlags         = WHDR_BEGINLOOP | WHDR_ENDLOOP ;
	pWaveHdr1->dwLoops         = dwRepetitions ;
	pWaveHdr1->lpNext          = NULL ;
	pWaveHdr1->reserved        = 0 ;
	
	// Prepare and write
	
	
	waveOutPrepareHeader (hWaveOut, pWaveHdr1, sizeof (WAVEHDR)) ;
	waveOutWrite (hWaveOut, pWaveHdr1, sizeof (WAVEHDR)) ;
	
	bEnding = FALSE ;
	bPlaying = TRUE ;
	bPaused = FALSE ;
	
	((CWnd *)(this->GetDlgItem(IDC_REC_START)))->EnableWindow(TRUE);
	((CWnd *)(this->GetDlgItem(IDC_REC_STOP)))->EnableWindow(FALSE);
	((CWnd *)(this->GetDlgItem(IDC_PLAY_START)))->EnableWindow(FALSE);//
	((CWnd *)(this->GetDlgItem(IDC_PLAY_PAUSE)))->EnableWindow(TRUE);//
	((CWnd *)(this->GetDlgItem(IDC_PLAY_STOP)))->EnableWindow(TRUE);
	
	if(count!=0)
		count=0;
	SetTimer(2,100,NULL);//playtimer

	
	return 0;
}

LRESULT CRecorderDlg::OnMM_WOM_DONE(UINT wParam, LONG lParam){

	TRACE("open MM_WOM_DONE\n");
	waveOutUnprepareHeader (hWaveOut, pWaveHdr1, sizeof (WAVEHDR)) ;
	waveOutClose (hWaveOut) ;
	
	bPaused =FALSE;
	dwRepetitions = 1 ;
	bPlaying = FALSE ;	
	
	return 0;
	
}
LRESULT CRecorderDlg::OnMM_WOM_CLOSE(UINT wParam, LONG lParam){
	KillTimer(2);
	TRACE("open MM_WOM_CLOSE\n");
	bPaused = FALSE ;
	dwRepetitions = 1 ;
	
	bPlaying = FALSE ;
	//set timer to 0;
	CString sttr,strt;
	strt.Format(_T("00:00:00"));
	sttr=strt;

	((CWnd *)GetDlgItem(IDC_STATIC))->SetWindowText(sttr);
	((CWnd *)(this->GetDlgItem(IDC_REC_START)))->EnableWindow(TRUE);
	((CWnd *)(this->GetDlgItem(IDC_REC_STOP)))->EnableWindow(FALSE);
	((CWnd *)(this->GetDlgItem(IDC_PLAY_START)))->EnableWindow(TRUE);
	((CWnd *)(this->GetDlgItem(IDC_PLAY_PAUSE)))->EnableWindow(FALSE);
	((CWnd *)(this->GetDlgItem(IDC_PLAY_STOP)))->EnableWindow(FALSE);
	return 0;
	
}
void CRecorderDlg::OnSaveRec()
{
	
		if(this->guestname=="")
			this->save_test();
		else
			this->save_train();

		((CWnd *)(this->GetDlgItem(IDC_TRAIN)))->EnableWindow(TRUE);
		((CWnd *)(this->GetDlgItem(IDC_TEST)))->EnableWindow(TRUE);
} 
void CRecorderDlg::save_train()
{
	//将buffer中存储的上一次录音的结果存储到指定说话人目录下；
		CString folderName = _T("E:\\Speechdata\\");
		folderName+=this->guestname;
		if(!PathIsDirectory(folderName)){
			CreateDirectory(folderName,NULL);
		}

		CFileFind find;
		CString wavpath=_T("");
		
		wavpath+=folderName;
		wavpath+="\\*.wav";
		BOOL ret = find.FindFile(wavpath);
		int count = 0;
		while(ret){
			ret = find.FindNextFile();
			if(find.IsDots()||find.IsDirectory())   
				continue;
			count++;
		}
		CString filename;
		filename.Format(_T("%03d"),count);
		filename+=".wav";

		this->wavname = filename;

		folderName+="\\";
		folderName+=filename;
		

		//Write the head of wav file.
		//When there exists space in the filename,we can not open the file !!! solved!
		CFile m_file;
		CFileException e;

		if(!m_file.Open(folderName,CFile::modeCreate|CFile::modeReadWrite,&e)){	
			 AfxMessageBox(_T("Open Failure!"));
		}
		DWORD m_WaveHeaderSize = 38;
		DWORD m_WaveFormatSize = 18; 
		m_file.SeekToBegin();
		m_file.Write("RIFF",4);
		unsigned int Sec=(sizeof pSaveBuffer + m_WaveHeaderSize);
		m_file.Write(&Sec,sizeof(Sec));
		m_file.Write("WAVE",4);
		m_file.Write("fmt ",4);
		m_file.Write(&m_WaveFormatSize,sizeof(m_WaveFormatSize));
		m_file.Write(&waveform.wFormatTag,sizeof(waveform.wFormatTag));
		m_file.Write(&waveform.nChannels,sizeof(waveform.nChannels));
		m_file.Write(&waveform.nSamplesPerSec,sizeof(waveform.nSamplesPerSec));
		m_file.Write(&waveform.nAvgBytesPerSec,sizeof(waveform.nAvgBytesPerSec));
		m_file.Write(&waveform.nBlockAlign,sizeof(waveform.nBlockAlign));
		m_file.Write(&waveform.wBitsPerSample,sizeof(waveform.wBitsPerSample));
		m_file.Write(&waveform.cbSize,sizeof(waveform.cbSize));
		m_file.Write("data",4);
		m_file.Write(&dwDataLength,sizeof(dwDataLength));
		m_file.Write(pSaveBuffer,dwDataLength);
		m_file.Seek(dwDataLength,CFile::begin);
		m_file.Close();

		AfxMessageBox(_T("save to ")+folderName);

} 
void CRecorderDlg::OnTrain()
{
	//process in case that the recording does not yet stop when the training is cast!!

	if(this->guestname==""||this->guestid==""){
		AfxMessageBox(_T("You'd better get the username and/or wav file first."));
		return;
	}

	if(!this->isSelect){
		//save_train();
		((CWnd *)(this->GetDlgItem(IDC_TRAIN)))->EnableWindow(FALSE);
		//((CWnd *)(this->GetDlgItem(IDC_TEST)))->EnableWindow(FALSE);
	}


	((CEdit *)GetDlgItem(IDC_DISPLAY))->SetWindowText(_T("Updating"));
	((CEdit *)GetDlgItem(IDC_NAME))->SetWindowText(_T("Updating"));

	
	((CEdit *)(this->GetDlgItem(IDC_DISPLAY)))->EnableWindow(TRUE);
	((CEdit *)(this->GetDlgItem(IDC_NAME)))->EnableWindow(TRUE);


	CString display;
	//默认情况下，系统对上一次存储的录音文件进行训练；
	display.Format(_T("你即将对 %s (ID: %s) 的 %s 进行训练，是否继续"),this->guestname,this->guestid,this->wavname);
	
	if(MessageBox(display,_T("训练ing"),MB_ICONQUESTION|MB_OKCANCEL)==IDCANCEL)
		return;
	CString folderName,file1,wavpath;
	folderName = _T("E:\\Speechdata\\");
	CFileFind find;
	//检查指定的即将训练的声音文件是否存在。不存在，则直接退出。
	wavpath = folderName+this->guestname+_T("\\")+this->wavname;
	if(!find.FindFile(wavpath)){
		display.Format(_T("%s (ID: %s) 的 %s 文件不存在，请选择正确的语音路径进行训练"),this->guestname,this->guestid,this->wavname);
		AfxMessageBox(display);
	}
	find.Close();

	//检查指定路径E:\Speechdata下是否存在speakerdata.mat。不存在，则新建一个。
	
	
	file1=_T("speakerdata.mat");
	file1=folderName+file1;	//E:\\Speechdata\\speakerdata.mat
	



	
	if(!find.FindFile(file1)){
		Initial();
	}
	find.Close();
	/*
	检查指定路径E:\Speechdata下是否存在NameTable.txt
	CStdioFile myfile;
	CString file2;
	file2=folderName+_T("NameTable.txt");
	CFileFind find1;
	if(!find1.FindFile(file2)){
		myfile.Open(...);
	}
	*/


	USES_CONVERSION;// #define CString to char *
	
	CString userName,userId,sph;
	userName = this->guestname;
	userId = this->guestid;
	sph = this->wavname;
	
	
	
// 以前的版本，使用一个txt文件来记录已训练说话人的姓名表；
// 如今，用Access数据库中的一张表来替代。更方便信息存储与管理。
// 因此，删去打开txt文件的相关代码。
/*
	
	CString fileName=_T("NameTable.txt");
	folderName+=fileName;

	
	CFileException fileException;

	CFileFind find;
	if(!find.FindFile(folderName)){
		if(!myfile.Open(folderName,CFile::modeCreate|CFile::modeReadWrite,&fileException)){
			AfxMessageBox(_T("Create Failure!"));
		}
	}
	else{
		if(!myfile.Open(folderName,CFile::modeReadWrite,&fileException)){
			AfxMessageBox(_T("Open Failure!"));
		}
	}
*/
	
	
	
	//判断数据库train表中是否存在该用户
	Users trainer;
	trainer.setUserName(userName);
	trainer.setUserId(userId);
	int speakerid = trainer.isExistId(userId,_T("train"));
	
	

	//char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) ); 
	//setlocale( LC_CTYPE, "chs" );
	/*
	// 查找NameTable中是否有相同的名字信息，即,判断当前说话人是新说话人还是旧说话人；
	// 若是旧说话人，采用增量学习方法进行训练。
	int order=0;
	myfile.SeekToBegin();
	while(myfile.ReadString(testName)){
		order++;
		if(testName==Name){
			newcomer=0;
			break;
		}
	}
	
	testName.Format(_T("%s\n"),Name);
	if(newcomer){
		myfile.WriteString(testName);
	}
	myfile.Close();
	*/
	//setlocale( LC_CTYPE, old_locale ); 
	//free( old_locale );

	char* myname=W2A(userName);
	char* mysph=W2A(sph);


	try{
		mwArray SpkName(myname);
		mwArray SphName(mysph);
		mwArray trainnum(20); 

		if(speakerid==0){
			Training(SpkName,SphName,trainnum);
			trainer.InsertTrainInfo();
			((CEdit *)GetDlgItem(IDC_NAME))->SetWindowText(_T("Training"));
		}
		else{
			CString s;
			s.Format(_T("This is number %d speaker in the training database."),speakerid);
			AfxMessageBox(s);
			mwArray Speaker(speakerid);
			IncrementGMM(Speaker,SphName,trainnum);
			((CEdit *)GetDlgItem(IDC_NAME))->SetWindowText(_T("Incremental Training"));
		}

		((CEdit *)GetDlgItem(IDC_DISPLAY))->SetWindowText(_T("Training successfully!"));
		
	}
	
	catch(const mwException &e){
		 CString ex;
		 char *ssstr=(char *)e.what();
		 ssstr[strlen(e.what())]='\0';
		 ex=ssstr;
		 ((CEdit *)GetDlgItem(IDC_DISPLAY))->SetWindowText(ex);
		 CString caption=_T("warning");
		 MessageBox(ex,caption);
	}
	if(this->isSelect){
		this->guestname.Empty();
		this->guestid.Empty();
		this->wavname.Empty();
		this->isSelect = FALSE;
	}
}

void CRecorderDlg::save_test()
{
		CString folderName = _T("E:\\Speechdata\\Test\\");
		//seek for the folder .\Test,if not exist,create it.
		if(!PathIsDirectory(folderName)){
			CreateDirectory(folderName,NULL);
		}

		//set the current time as the name of the wave file during the test
		CTime current = CTime::GetCurrentTime();
		CString filename;
		int y = current.GetYear();
		int m = current.GetMonth();
		int d = current.GetDay();
		int h = current.GetHour();
		int min = current.GetMinute();
		int s = current.GetSecond();
		filename.Format(_T("%04d%02d%02d%02d%02d%02d"),y,m,d,h,min,s);
		filename+=".wav";
		this->testwavname = filename;
		folderName+=filename;

		//Write the head of wav file.
		//When there exists space in the filename,we can not open the file !!! solved!
		CFile m_file;
		CFileException e;

		if(!m_file.Open(folderName,CFile::modeCreate|CFile::modeReadWrite,&e)){	
			 AfxMessageBox(_T("Open Failure!"));
		}
		DWORD m_WaveHeaderSize = 38;
		DWORD m_WaveFormatSize = 18; 
		m_file.SeekToBegin();
		m_file.Write("RIFF",4);
		unsigned int Sec=(sizeof pSaveBuffer + m_WaveHeaderSize);
		m_file.Write(&Sec,sizeof(Sec));
		m_file.Write("WAVE",4);
		m_file.Write("fmt ",4);
		m_file.Write(&m_WaveFormatSize,sizeof(m_WaveFormatSize));
		m_file.Write(&waveform.wFormatTag,sizeof(waveform.wFormatTag));
		m_file.Write(&waveform.nChannels,sizeof(waveform.nChannels));
		m_file.Write(&waveform.nSamplesPerSec,sizeof(waveform.nSamplesPerSec));
		m_file.Write(&waveform.nAvgBytesPerSec,sizeof(waveform.nAvgBytesPerSec));
		m_file.Write(&waveform.nBlockAlign,sizeof(waveform.nBlockAlign));
		m_file.Write(&waveform.wBitsPerSample,sizeof(waveform.wBitsPerSample));
		m_file.Write(&waveform.cbSize,sizeof(waveform.cbSize));
		m_file.Write("data",4);
		m_file.Write(&dwDataLength,sizeof(dwDataLength));
		m_file.Write(pSaveBuffer,dwDataLength);
		m_file.Seek(dwDataLength,CFile::begin);
		m_file.Close();

		AfxMessageBox(_T("save to ")+folderName);
}
void CRecorderDlg::OnTest()
{

	if(!this->isSelect){
		//save_test();
		//((CWnd *)(this->GetDlgItem(IDC_TRAIN)))->EnableWindow(FALSE);
		((CWnd *)(this->GetDlgItem(IDC_TEST)))->EnableWindow(FALSE);
	}

	((CEdit *)GetDlgItem(IDC_DISPLAY))->SetWindowText(_T("Updating"));
	((CEdit *)GetDlgItem(IDC_NAME))->SetWindowText(_T("Updating"));
		
	((CEdit *)(this->GetDlgItem(IDC_DISPLAY)))->EnableWindow(TRUE);
	((CEdit *)(this->GetDlgItem(IDC_NAME)))->EnableWindow(TRUE);

	

	CString display;
	display.Format(_T("你即将对 %s 进行测试，是否继续"),this->testwavname);
	
	if(MessageBox(display,_T("测试ing"),MB_ICONQUESTION|MB_OKCANCEL)==IDCANCEL){
		//((CEdit *)(this->GetDlgItem(IDC_EDIT1)))->EnableWindow(TRUE);
		return;
	}
	//有待添加其他选项！


	USES_CONVERSION;// #define CString to char *
	
	//CStdioFile myfile;
	CString file1;
	CString folderName;
	folderName = _T("E:\\Speechdata\\");
	file1=_T("speakerdata.mat");
	//file2=_T("NameTable.txt");
	file1=folderName+file1;	//E:\\Speechdata\\speakerdata.mat
	//file2=folderName+file2;
	
	CFileFind find0;
	CFileException fileException;
	if(!find0.FindFile(file1)){
		Initial();
		/*
		if(find1.FindFile(file2)){
			myfile.Remove(file2);		
			if(!myfile.Open(file2,CFile::modeCreate,&fileException)){
				AfxMessageBox(_T("Create Failure!"));
			}	
		}
		find1.Close();
		*/
	}
	find0.Close();
	


	char* mysph=W2A(this->testwavname);
	mwArray speaker;
	mwArray sphName(mysph);

	try {
		//TestSpeech(int nargout, mwArray& pytest, const mwArray& SpeechName);
		TestSpeech(1,speaker,sphName);

		//conversion from mwArray to CString.
		mwString str=speaker.ToString();
		const char* pytest = (const char*)str;
		CString name;
		name=pytest;

		((CEdit *)GetDlgItem(IDC_NAME))->SetWindowText(name);
		((CEdit *)GetDlgItem(IDC_DISPLAY))->SetWindowText(_T("Test successfully!"));
	}
	catch(const mwException &e){
		 CString ex;
		 char *ssstr=(char *)e.what();
		 ssstr[strlen(e.what())]='\0';
		 ex=ssstr;
		 //display
		 ((CEdit *)GetDlgItem(IDC_DISPLAY))->SetWindowText(ex);
		 ((CEdit *)GetDlgItem(IDC_NAME))->SetWindowText(_T("Unknown"));
		 CString caption=_T("warning");
		 MessageBox(ex,caption);
	}

	if(this->isSelect){
		this->testwavname.Empty();
		this->isSelect = FALSE;
	}
}

void CRecorderDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnTimer(nIDEvent);
	if((nIDEvent==2)&&Pause)
		count+=0;
	else
		count+=1;
		
	CString str,str1;
	int Hour,Min,Sec;
	
	Sec=(count/10)%60;
	Min=(count/10)/60;
	Hour=(count/10)/3600;
	str1.Format(_T("%02d:%02d:%02d"),Hour,Min,Sec);
	str=str1;

	switch(nIDEvent) {
	case 1:case 2:
			((CWnd *)GetDlgItem(IDC_STATIC))->SetWindowText(str);
			((CProgressCtrl*)GetDlgItem(IDC_PROGRESS1))-> SetPos(count/10); 

	break;
	}
	return;
}

void CRecorderDlg::OnHelpAbout()
{
	// TODO: Add your command handler code here
	CAboutDlg dlg;
	dlg.DoModal();
}




void CRecorderDlg::OnExit()
{
	CDialog::EndDialog(0);
	this->GetParent()->PostMessage(WM_CLOSE,0,0);
}


void CRecorderDlg::OnUserObtain()
{
	// TODO: Add your control notification handler code here
	
	if(anyGuest == FALSE){
		UserInfoDlg dlg;
		int rtdlg=dlg.DoModal();

		if(rtdlg==IDOK&&!dlg.username.IsEmpty()){
			this->guestname = dlg.username;
			Users user;
			if (!user.GetUserInfo(this->guestname)){
				AfxMessageBox(_T("您注册的用户信息并没有正确写入，请重新注册！"));
			}
			this->guestid = user.getUserId();
			// 此处还需要添加一个文本框，用来显示userid
			//((CEdit *)(this->GetDlgItem(IDC_EDIT1)))->SetWindowText(guestid);
			((CEdit *)(this->GetDlgItem(IDC_EDIT1)))->SetWindowText(guestname);
			((CButton *)(this->GetDlgItem(IDC_OBTAINUSERINFO_BUTTON)))->SetWindowText(_T("用户登出"));
			anyGuest = TRUE;
		}
		return;
	}
	else{
		this->guestname = _T("");
		this->guestid = _T("");
		//((CEdit *)(this->GetDlgItem(IDC_EDIT1)))->SetWindowText(guestid);
		((CEdit *)(this->GetDlgItem(IDC_EDIT1)))->SetWindowText(guestname);	
		((CButton *)(this->GetDlgItem(IDC_OBTAINUSERINFO_BUTTON)))->SetWindowText(_T("获取用户信息"));
		anyGuest = FALSE;
	}
	
}


void CRecorderDlg::OnTrainBrowse()
{
	// TODO: Add your control notification handler code here
	CString lpszFilter = _T("WAV Files(*.wav)|*.wav||");
	CString lpszFileName=_T("E:\\Speechdata\\");
	CFileDialog dlg(TRUE,NULL,lpszFileName,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,lpszFilter,this);
	CString filename;
	
	if (dlg.DoModal() == IDOK ){
		this->wavname = dlg.GetFileName();
		filename = dlg.GetPathName();

		int pos = filename.ReverseFind('\\');
		filename = filename.Left(pos);
		pos = filename.ReverseFind('\\');
		this->guestname = filename.Mid(pos+1);
		Users user;
		if(!user.GetUserInfo(this->guestname)){
			AfxMessageBox(this->guestname+_T(" is not a qualified speaker!\nPlease chech it again."));
			UpdateData(TRUE);
			return;
		}
		this->guestid = user.getUserId();

		this->isSelect = TRUE;
		OnTrain();
	}
}


void CRecorderDlg::OnTestBrowse()
{
	// TODO: Add your control notification handler code here
	CString lpszFilter = _T("WAV Files(*.wav)|*.wav||");
	CString lpszFileName=_T("E:\\Speechdata\\Test\\");
	CFileDialog dlg(TRUE,NULL,lpszFileName,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,lpszFilter,this);
	CString filename;
	
	if (dlg.DoModal() == IDOK ){
		this->testwavname = dlg.GetFileName();
		
		//AfxMessageBox(this->testwavname);
		this->isSelect = TRUE;
		OnTest();

	}
}

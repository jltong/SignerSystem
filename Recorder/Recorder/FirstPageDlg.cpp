// FirstPageDlg.cpp : implementation file
//最好封装为一个录音类，便于复用
//目前可以copy RecorderDlg.cpp 代码 完成录音与测试
#include "stdafx.h"
#include "Recorder.h"
#include "FirstPageDlg.h"
#include "afxdialogex.h"
#include "CloginDlg.h"
#include "Users.h"
#include "tchar.h"
#include<cstdlib>
#include<cstring>
#include<string>
#include <locale.h>
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
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"mclmcr.lib")


CFirstPageDlg::CFirstPageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFirstPageDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	showMsg = _T("");
	ErrorCnt = 0;


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

CFirstPageDlg::~CFirstPageDlg()
{
}

void CFirstPageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFirstPageDlg, CDialog)
	ON_BN_CLICKED(IDC_FP_TRAIN, &CFirstPageDlg::OnFpTrain)
	ON_BN_CLICKED(IDC_FP_TEST, &CFirstPageDlg::OnFpTest)

	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	
	ON_MESSAGE(MM_WIM_OPEN,OnMM_WIM_OPEN)
	ON_MESSAGE(MM_WIM_DATA,OnMM_WIM_DATA)
	ON_MESSAGE(MM_WIM_CLOSE,OnMM_WIM_CLOSE)
	
	ON_WM_DESTROY()

END_MESSAGE_MAP()


// CFirstPageDlg message handlers

BOOL CFirstPageDlg::OnInitDialog()
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
	
	//set the icon and font for the button and dialog
	HICON hlcon=AfxGetApp()->LoadIconW(IDI_S3);
	HICON hlcon1=AfxGetApp()->LoadIconW(IDI_ICON_REGISTER);
	((CButton *)GetDlgItem(IDC_FP_TEST))->SetIcon(hlcon);
	
	((CButton *)GetDlgItem(IDC_FP_TRAIN))->SetIcon(hlcon1);

	CFont font,font1,font_title;
	font.CreatePointFont(200,_T("楷体"));
	font1.CreatePointFont(400,_T("楷体"));
	font_title.CreatePointFont(400,_T("Consolas"));
	//IDC_FP_TITLE
	GetDlgItem(IDC_FP_TEST)->SetFont(&font_title);
	GetDlgItem(IDC_FP_TEST)->SetFont(&font1);
	GetDlgItem(IDC_FP_TRAIN)->SetFont(&font);
	// TODO: Add extra initialization here
	pWaveHdr1=reinterpret_cast<PWAVEHDR>(malloc(sizeof(WAVEHDR)));
	pWaveHdr2=reinterpret_cast<PWAVEHDR>(malloc(sizeof(WAVEHDR)));
	
	//allocate memory for save buffer
	pSaveBuffer = reinterpret_cast<PBYTE>(malloc(1));

	return TRUE;  
}

void CFirstPageDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	
		if(nID==SC_MINIMIZE )
			ShowWindow(SW_SHOWMINIMIZED);
		else
			CDialog::OnSysCommand(nID, lParam);
	
}

void CFirstPageDlg::OnPaint()
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
HCURSOR CFirstPageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);//difference
}



LRESULT CFirstPageDlg::OnMM_WIM_OPEN(UINT wParam, LONG lParam) 
{
	// TODO: Add your message handler code here and/or call default

	bRecording=TRUE;

	return 0;

//	TRACE("MM_WIM_OPEN\n");
}
LRESULT CFirstPageDlg::OnMM_WIM_DATA(UINT wParam, LONG lParam) 
{
	// TODO: Add your message handler code here and/or call default
	// Reallocate save buffer memory
	
	//////////////////////////////////////////////////////////////////////////
	
	pNewBuffer = (PBYTE)realloc (pSaveBuffer, dwDataLength +((PWAVEHDR) lParam)->dwBytesRecorded) ;
	
	if (pNewBuffer == NULL)
	{
		waveInClose (hWaveIn) ;
		MessageBeep (MB_ICONEXCLAMATION) ;
		AfxMessageBox(_T("OnMM_WIM_DATA:memory error"));
		return 0;
	}
	
	pSaveBuffer = pNewBuffer ;
	
	CopyMemory (pSaveBuffer + dwDataLength, ((PWAVEHDR) lParam)->lpData,((PWAVEHDR) lParam)->dwBytesRecorded) ;
	
	dwDataLength += ((PWAVEHDR) lParam)->dwBytesRecorded ;
	
	if (!bRecording)
	{
		waveInClose (hWaveIn) ;
		return 0 ;
	}

	waveInAddBuffer (hWaveIn, (PWAVEHDR) lParam, sizeof (WAVEHDR)) ;
	TRACE("done input data\n");
	return 0;

	
}

LRESULT CFirstPageDlg::OnMM_WIM_CLOSE(UINT wParam, LONG lParam) 
{
	// TODO: Add your message handler code here and/or call default


	waveInUnprepareHeader (hWaveIn, pWaveHdr1, sizeof (WAVEHDR)) ;
	waveInUnprepareHeader (hWaveIn, pWaveHdr2, sizeof (WAVEHDR)) ;
	
	free (pBuffer1) ;
	free (pBuffer2) ;
	
	
	return 0;
	
}


void CFirstPageDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	CDialog::OnClose();
	if (bRecording) {
		//bTerminating=TRUE;
		//bEnding=TRUE;
		waveInReset(hWaveIn);
		TRACE("waveInReset\n");
		Sleep(500);
		//return CWinThread::ExitInstance();
	}
	
	free (pWaveHdr1) ;
	free (pWaveHdr2) ;
	free (pSaveBuffer) ;
	
	

}

//here add the record

void CFirstPageDlg::save(CString path)
{
		CFile m_file;
		CFileException e;

		if(!m_file.Open(path,CFile::modeCreate|CFile::modeReadWrite,&e)){	
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

		AfxMessageBox(_T("Test save successfully!"));
}







void CFirstPageDlg::OnFpTrain()
{
	// TODO: Add your control notification handler code here
	CloginDlg dlg;
	dlg.DoModal();
	
}


void CFirstPageDlg::OnFpTest()
{

	if(bRecording==FALSE){
		//mean that stay in the state of Stop.
		//click the button can triger the behavior of record.
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
		//fill in the structure WAVEFORMATEX
		waveform.wFormatTag=WAVE_FORMAT_PCM; //PCM pulse code modulation
		waveform.nChannels=1;
		waveform.nSamplesPerSec=11025;//sample rate =25khz
		waveform.nAvgBytesPerSec=11025;//ave data rate = 25khz
		waveform.nBlockAlign=1;
		waveform.wBitsPerSample=8; //8 bits per sample
		waveform.cbSize=0;

	
		if (waveInOpen(&hWaveIn,WAVE_MAPPER,&waveform,(DWORD)this->m_hWnd,NULL,CALLBACK_WINDOW)) {
			free(pBuffer1);
			free(pBuffer2);
			MessageBeep(MB_ICONEXCLAMATION);
			AfxMessageBox(_T("Audio can not be open!"));
		}
		//PWAVEHDR pWaveHdr1,pWaveHdr2;
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
		this->showMsg+=_T("Recording...\r\n");
		((CEdit *)GetDlgItem(IDC_FP_TESTOUT))->SetWindowText(this->showMsg);
		dwDataLength = 0 ;
		
		waveInStart (hWaveIn) ;

	}
	else{
		//bRecording == TRUE
		//Recording state,click the button will stop recording and finish the Test.
		if(bRecording){
			//bEnding=TRUE;
			waveInReset(hWaveIn);//stop the record!
		}
		bRecording = FALSE;
		CString filepath;
		filepath = _T("E:\\Speechdata\\Test");
		//find the directory
		if(!PathIsDirectory(filepath)){
			CreateDirectory(filepath,NULL);
		}
		//set the test filename
		CTime current = CTime::GetCurrentTime();
		CString filename;
		int y = current.GetYear();
		int m = current.GetMonth();
		int d = current.GetDay();
		int h = current.GetHour();
		int min = current.GetMinute();
		int s = current.GetSecond();
		filename.Format(_T("%d%d%d%d%d%d"),y,m,d,h,min,s);
		filename+=".wav";
		filepath+=_T("\\")+filename; 
		
		CFileFind find;
		if(!find.FindFile(filepath)){
			save(filepath);
		}
		find.Close();

		USES_CONVERSION;// #define CString to char *
	
		//CStdioFile myfile;
		CString file1;
		CString folderName = _T("E:\\Speechdata\\");
		file1=_T("speakerdata.mat");
		//file2=_T("NameTable.txt");
		file1=folderName+file1;	//E:\\Speechdata\\speakerdata.mat
		//file2=folderName+file2;
		

		//make sure the corresponse of the file1 and file2
		CFileFind find1;
		//CFileException fileException;
		if(!find1.FindFile(file1)){
			Initial();
			/*
			if(find2.FindFile(file2)){
				myfile.Remove(file2);		
				if(!myfile.Open(file2,CFile::modeCreate,&fileException)){
					AfxMessageBox(_T("Create Failure!"));
				}
				
			}
			find2.Close();
			*/
		}	
		find1.Close();

		char* mysph=W2A(filename);
		mwArray speaker;//store the output
		mwArray sphName(mysph);
		try {
			//TestSpeech(int nargout, mwArray& pytest, const mwArray& SpeechName);
			TestSpeech(1,speaker,sphName);

			//conversion from mwArray to CString.
			mwString str=speaker.ToString();
			const char* pytest = (const char*)str;
			CString name;
			name=pytest;
			
			CTime current = CTime::GetCurrentTime();
			CString curtime;
			int h = current.GetHour();
			int min = current.GetMinute();
			int s = current.GetSecond();
			curtime.Format(_T("%02d:%02d:%02d"),h,min,s);
			this->showMsg+=curtime+_T(":")+name+_T("\r\n");//Display the outcome of TEST
			
			((CEdit *)GetDlgItem(IDC_FP_TESTOUT))->SetWindowText(this->showMsg);
			//显示用户信息（姓名，编号，部门等）；

			Users signer;
			if(!signer.isExist(name,_T("train"))){
				AfxMessageBox(_T("Invalid users or the existence of inconformity."));
				return;
			}
			signer.GetUserInfo(name);

			CString signerinfo;
			signerinfo.Format(_T("UserName:%s\r\nUserId:%s\r\nDepartment:%s\r\nEmail:%s\r\n"),signer.getUserName(),signer.getUserId(),signer.getDep(),signer.getEmail());
			UINT inret = MessageBox(signerinfo,_T("测试ing"),MB_ICONQUESTION|MB_OKCANCEL);
			if(inret==IDCANCEL){
				ErrorCnt++;
				if(ErrorCnt == 2){
					AfxMessageBox(_T("Your stored information may have been destroyed.Please contact the Administrator to re-enrollment"));
				}
				AfxMessageBox(_T("SignIn Error: identity discrepancy.Leave %d times to try again!"),2-ErrorCnt);
				return;
			}
			else if(inret == IDOK){
				//flush the signer's signin record.
				//userid timetoarrive
				current = CTime::GetCurrentTime();
				int year = current.GetYear();
				int month = current.GetMonth();
				int day = current.GetDay();

				int hour = current.GetHour();
				int minute = current.GetMinute();
				int second = current.GetSecond();
				CString signtime,signdate;
				signdate.Format(_T("%d/%d/%d"),month,day,year);
				signtime.Format(_T("%02d:%02d:%02d"),hour,minute,second);
				signer.setDTA(signdate);
				signer.setTTA(signtime);

				if(signer.InsertSignIn())
					AfxMessageBox(_T("SignIn Success"));
				else
					AfxMessageBox(_T("SignIn Error"));
				
				this->showMsg="";
				ErrorCnt=0;
			}
			
		}
		catch(const mwException &e){
			 CString ex;
			 char *str=(char *)e.what();
			 str[strlen(e.what())]='\0';
			 ex=str;
			 //display
			 this->showMsg+=ex+_T("\r\n");
			 ((CEdit *)GetDlgItem(IDC_FP_TESTOUT))->SetWindowText(this->showMsg);
			 
			 CString caption=_T("warning");
			 MessageBox(ex,caption);
		}
	}

}


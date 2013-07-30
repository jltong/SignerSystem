
// RecorderDlg.h : header file
//

#pragma once
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

// CRecorderDlg dialog
#define  INP_BUFFER_SIZE 16384
class CRecorderDlg : public CDialog
{
// Construction
public:
	CRecorderDlg(CWnd* pParent = NULL);	// standard constructor
	CString guestname;//obtain the username of guest
	CString guestid; //obtain the userid of guest
	CString wavname;//the name of wave file for training 
	CString testwavname;//the name of wave file for testing 
	BOOL isSelect;
	BOOL anyGuest;
// Dialog Data
	enum { IDD = IDD_RECORDER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	UINT count;
	HICON  m_hIcon;
	
	
	BOOL  bRecording,bPlaying,bReverse,bPaused,bEnding,bTerminating,Pause;
	DWORD  dwDataLength,dwRepetitions;
	HWAVEIN  hWaveIn;
	HWAVEOUT hWaveOut;
	PBYTE pBuffer1,pBuffer2,pSaveBuffer,pNewBuffer;
	PWAVEHDR pWaveHdr1,pWaveHdr2;
	HMMIO hFile;
	
	WAVEFORMATEX waveform;//The WAVEFORMATEX structure specifies the data format of a wave audio stream

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRecStart();
	afx_msg void OnRecStop();
	/*the six function below all have a formal return value of 0 */
	afx_msg LRESULT OnMM_WIM_OPEN(UINT wParam,LONG lParam);
	afx_msg LRESULT OnMM_WIM_DATA(UINT wParam,LONG lParam);
	afx_msg LRESULT OnMM_WIM_CLOSE(UINT wParam,LONG lParam);
	afx_msg LRESULT OnMM_WOM_OPEN(UINT wParam,LONG lParam);
	afx_msg LRESULT OnMM_WOM_DONE(UINT wParam,LONG lParam);
	afx_msg LRESULT OnMM_WOM_CLOSE(UINT wParam,LONG lParam);

	
	afx_msg void OnDestroy();
	afx_msg void OnPlayStart();
	afx_msg void OnPlayPause();
	afx_msg void OnPlayStop();
	afx_msg void OnSaveRec();
	afx_msg void OnTrain();
	afx_msg void OnTest();
	afx_msg void OnUserObtain();
	afx_msg void save_test();
	afx_msg void save_train();
	afx_msg void OnTimer(UINT nIDEvent);


	DECLARE_MESSAGE_MAP()
public:
	//used for test,may not be in use now

	afx_msg void OnHelpAbout();
	afx_msg void OnExit();
	
	afx_msg void OnTrainBrowse();
	afx_msg void OnTestBrowse();
};

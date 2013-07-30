#pragma once
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

#define  INP_BUFFER_SIZE 16384

// CFirstPageDlg dialog

class CFirstPageDlg : public CDialog
{
//private:
	//int visitnum;
	//CString lastvisit;//record the time of the last visit
	
public:
	CFirstPageDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFirstPageDlg();
	CString showMsg;
// Dialog Data
	enum { IDD = IDD_FIRSTPAGE };

protected:
	int ErrorCnt;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	UINT count;
	HICON  m_hIcon;
	BOOL  bRecording,
		  bPlaying,
		  bReverse,
		  bPaused,
		  bEnding,
		  bTerminating,
		  Pause;
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

	/*the six function below all have a formal return value of 0 */
	afx_msg LRESULT OnMM_WIM_OPEN(UINT wParam,LONG lParam);
	afx_msg LRESULT OnMM_WIM_DATA(UINT wParam,LONG lParam);
	afx_msg LRESULT OnMM_WIM_CLOSE(UINT wParam,LONG lParam);
	afx_msg LRESULT OnMM_WOM_OPEN(UINT wParam,LONG lParam);
	afx_msg LRESULT OnMM_WOM_DONE(UINT wParam,LONG lParam);
	afx_msg LRESULT OnMM_WOM_CLOSE(UINT wParam,LONG lParam);
	
	afx_msg void OnDestroy();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFpTrain();
	afx_msg void OnFpTest();
	afx_msg void save(CString path);
	afx_msg void OnStnClickedFpTitle();
};

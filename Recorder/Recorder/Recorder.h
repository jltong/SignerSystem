
// Recorder.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CRecorderApp:
// See Recorder.cpp for the implementation of this class
//

class CRecorderApp : public CWinApp
{
public:
	CRecorderApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecordHWndApp)
	public:
		virtual BOOL InitInstance();
		

	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRecordHWndApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP() // Declare Message Map
};

extern CRecorderApp theApp;
// DemoExe.h : main header file for the DEMOEXE application
//

#if !defined(AFX_DEMOEXE_H__1344FFE2_202F_4DA8_91BA_142F87374088__INCLUDED_)
#define AFX_DEMOEXE_H__1344FFE2_202F_4DA8_91BA_142F87374088__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDemoExeApp:
// See DemoExe.cpp for the implementation of this class
//

class CDemoExeApp : public CWinApp
{
public:
	CDemoExeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoExeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDemoExeApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMOEXE_H__1344FFE2_202F_4DA8_91BA_142F87374088__INCLUDED_)

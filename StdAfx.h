// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__8D94CA87_DEC0_4AB4_8C36_4888D09B706C__INCLUDED_)
#define AFX_STDAFX_H__8D94CA87_DEC0_4AB4_8C36_4888D09B706C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <SCUU.h>

#include "IMGFUC.h"
#include "PathDialog.h"
#include "NumRec.h"
#include "NumRec_C.h"


#include <fstream.h>

#ifdef _DEBUG
	#pragma comment(lib, "ConNumRecDllD.lib")
#else
	#pragma comment(lib, "ConNumRecDll.lib")
#endif

//#define SAVE_REC_INFO_TO_TXT
#define SAVE_MRU_INIFILE
#define SAVE_SUBDIR
#define SAVE_CUR_PROCFILE
#define SAVE_TIME_INFO


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__8D94CA87_DEC0_4AB4_8C36_4888D09B706C__INCLUDED_)

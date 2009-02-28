// DemoExeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DemoExe.h"
#include "DemoExeDlg.h"
#include "IniFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoExeDlg dialog
char drive[_MAX_DRIVE];
char dir[_MAX_DIR];
char fname[_MAX_FNAME];
char ext[_MAX_EXT];

CDemoExeDlg::CDemoExeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDemoExeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDemoExeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bShowImg = FALSE;

	m_pImg = NULL;
	m_pImg = new CDIBitmap;
	m_pImg->Create(2,2);

	m_pImgSub1 = NULL;
	m_pImgSub1 = new CDIBitmap;
	m_pImgSub1->Create(2,2);

	m_pImgSub2 = NULL;
	m_pImgSub2 = new CDIBitmap;
	m_pImgSub2->Create(2,2);

	m_strRes = "Please First Load In.";

	m_bInBatchProcess = FALSE;

#ifdef SAVE_MRU_INIFILE
	m_strMRUBatchPath = "";
#endif
}

BOOL CDemoExeDlg::InitVars()
{
	m_pImg->Create(2,2);
	m_pImgSub1->Create(2,2);
	m_pImgSub2->Create(2,2);

	m_strRes = "";

	return TRUE;
}

CDemoExeDlg::~CDemoExeDlg()
{
	delete m_pImg;
	delete m_pImgSub1;
	delete m_pImgSub2;
}

void CDemoExeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemoExeDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDemoExeDlg, CDialog)
	//{{AFX_MSG_MAP(CDemoExeDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_BATCH, OnBtnBatch)
	ON_BN_CLICKED(IDC_BTN_INTERFACE, OnBtnInterface)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoExeDlg message handlers

BOOL CDemoExeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDemoExeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDemoExeDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CPaintDC dc(this);

		CRect rcShow;
		GetDlgItem(IDC_STC_PIC)->GetWindowRect( &rcShow );
		ScreenToClient( &rcShow );
		CSize szShow( rcShow.Width() , rcShow.Height() );
		m_pImg->Stretch(&dc, rcShow.TopLeft(), szShow );

		GetDlgItem(IDC_STC_SUBPIC1)->GetWindowRect( &rcShow );
		ScreenToClient( &rcShow );
		szShow = CSize( rcShow.Width() , rcShow.Height() );
		m_pImgSub1->Stretch(&dc, rcShow.TopLeft(), szShow );

		GetDlgItem(IDC_STC_SUBPIC2)->GetWindowRect( &rcShow );
		ScreenToClient( &rcShow );
		szShow = CSize( rcShow.Width() , rcShow.Height() );
		m_pImgSub2->Stretch(&dc, rcShow.TopLeft(), szShow );

		CFont fontRes;
		fontRes.CreateFont(30,0,0,0,400,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_SWISS,"Arial");
		//CFont* pOldFont = GetDlgItem(IDC_STC_STR)->GetDC()->SelectObject(&fontRes);
		//GetDlgItem(IDC_STC_STR)->GetDC()->TextOut(0,0,m_strRes);
		//GetDlgItem(IDC_STC_STR)->GetDC()->SelectObject(pOldFont);
		CFont* pOldFont = dc.SelectObject(&fontRes);
		//SetDlgItemText( IDC_STC_STR, m_strRes );
		GetDlgItem(IDC_STC_STR)->GetWindowRect( &rcShow );
		ScreenToClient( &rcShow );
		dc.TextOut(rcShow.left,rcShow.top,m_strRes);
		dc.SelectObject(pOldFont);
		

		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDemoExeDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDemoExeDlg::OnOK()
{
	// TODO: Add extra validation here
		CFileDialog dlgLoad(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		"所有图象文件(*.tif; *.jpg; *.bmp; *.tga)|*.tif; *.jpg; *.bmp; *.tga|TIFF 文件(*.tif)|*.tif|JPEG 文件(*.jpg)|*.jpg|Windows 位图(*.bmp)|*.bmp|Targa 文件(*.tga)|*.tga||");

	if( dlgLoad.DoModal() == IDOK )
	{
		InitVars();

		m_bShowImg = TRUE;
		CString newName = dlgLoad.GetPathName(); 
		CString szValue = AfxGetApp()->GetProfileString(_T("Settings"),"Image Path",NULL);
		dlgLoad.m_ofn.lpstrInitialDir = szValue;
		CString m_strImageName = dlgLoad.GetFileName();
		int nLength = newName.GetLength() - m_strImageName.GetLength() - 1;
		szValue = newName.Left(nLength);
		AfxGetApp()->WriteProfileString(_T("Settings"),"Image Path",szValue);

		CString strRes = "";
		CString strNation = "";
		if( m_pImg->Load(newName) )//把图象读入m_pImage中
		{
			BOOL bJudgeRes = FALSE;
			CRect rcSubRgn1 = CRect(0,0,0,0);
			CRect rcSubRgn2 = CRect(0,0,0,0);

			m_NumRec.SetProcFileString(newName);
			strRes = m_NumRec.RecNum( m_pImg, bJudgeRes );
			CString strNumSeg = "";
			CString strABCSeg = "";
 			m_NumRec.GetPosInfo( rcSubRgn1, rcSubRgn2, strNumSeg, strABCSeg );
			
//////////////////////////////C Interface Call////////////////////////////////////////////////////////////////////////			
//			int nImgWidth = m_pImg->GetWidth();
//			int nImgHeight = m_pImg->GetHeight();			
//			LPCONNUMINFO pInfo = new CONNUMINFO;
//			RecConNum( m_pImg->GetBitsAddress(), nImgWidth, nImgHeight, pInfo);
//			strRes.Format( "%s" , pInfo->ConNum );
//			rcSubRgn1 = CRect( pInfo->ABCRegion[0], pInfo->ABCRegion[1], pInfo->ABCRegion[2], pInfo->ABCRegion[3] );
//			rcSubRgn2 = CRect( pInfo->NumRegion[0], pInfo->NumRegion[1], pInfo->NumRegion[2], pInfo->NumRegion[3] );
// 			delete pInfo;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			if( strRes != "" && strRes != "error")
			{
				if( rcSubRgn1 != CRect(0,0,0,0) )
				{
					int w = rcSubRgn1.Width()+1;
					int h = rcSubRgn1.Height()+1;

					m_pImgSub1->Create( w, h, 24 );
					CRect rcCut = rcSubRgn1;
					GetPicRectPart( m_pImg, m_pImgSub1, rcCut );
					DrawRect( m_pImg, rcSubRgn1, 255, 0, 0 );
				}

				if( rcSubRgn2 != CRect(0,0,0,0) )
				{
					int w = rcSubRgn2.Width()+1;
					int h = rcSubRgn2.Height()+1;

					m_pImgSub2->Create( w, h, 24 );
					CRect rcCut = rcSubRgn2;
					GetPicRectPart( m_pImg, m_pImgSub2, rcCut );
					DrawRect( m_pImg, rcSubRgn2, 255, 0, 0 );
				}

				Invalidate();
			}
			else if( strRes == "error" )
			{
				strRes = "Sorry. It's expired.";
			}
			else
			{
				strRes = "Req Fur Improvement";
			}

			//GetDlgItem(IDC_STC_STR)->SetWindowText( strRes );

			m_strRes = strRes;
			
			Invalidate();

		}
		else
		{
			strRes = "Load Picture error!";
 		}


	}	
}

/*
void CDemoExeDlg::OnOK()
{
	// TODO: Add extra validation here
	InitVars();
	CFileDialog dlgLoad(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		"所有图象文件(*.tif; *.jpg; *.bmp; *.tga)|*.tif; *.jpg; *.bmp; *.tga|TIFF 文件(*.tif)|*.tif|JPEG 文件(*.jpg)|*.jpg|Windows 位图(*.bmp)|*.bmp|Targa 文件(*.tga)|*.tga||");

	if( dlgLoad.DoModal() == IDOK )
	{
		m_bShowImg = TRUE;
		CString newName = dlgLoad.GetPathName(); 
		CString szValue = AfxGetApp()->GetProfileString(_T("Settings"),"Image Path",NULL);
		dlgLoad.m_ofn.lpstrInitialDir = szValue;
		CString m_strImageName = dlgLoad.GetFileName();
		int nLength = newName.GetLength() - m_strImageName.GetLength() - 1;
		szValue = newName.Left(nLength);

		AfxGetApp()->WriteProfileString(_T("Settings"),"Image Path",szValue);

		CString strRes = "";
		CString strNation = "";
		if( m_pImg->Load(newName) )//把图象读入m_pImage中
		{
			m_NumRec.SetProcFileString(newName);
			BOOL bJudgeRes = FALSE;
			strRes = m_NumRec.RecNum( m_pImg, bJudgeRes );
			//strRes = m_NumRec.RecTopNum( m_pImg, bJudgeRes );
			if( strRes != "" && strRes != "error")
			{
				CRect rcSubRgn1;
				CRect rcSubRgn2;
				CString strSubString1;
				CString strSubString2;
				m_NumRec.GetPosInfo(rcSubRgn1,rcSubRgn2,strSubString1,strSubString2);

				if( rcSubRgn1 != CRect(0,0,0,0) )
				{
					int w = rcSubRgn1.Width()+1;
					int h = rcSubRgn1.Height()+1;

					m_pImgSub1->Create( w, h, 24 );
					DrawRect( m_pImg, rcSubRgn1, 255, 0, 0 );
					GetPicRectPart( m_pImg, m_pImgSub1, rcSubRgn1 );
					
				}

				if( rcSubRgn2 != CRect(0,0,0,0) )
				{
					int w = rcSubRgn2.Width()+1;
					int h = rcSubRgn2.Height()+1;

					m_pImgSub2->Create( w, h, 24 );
					DrawRect( m_pImg, rcSubRgn2, 255, 0, 0 );
					GetPicRectPart( m_pImg, m_pImgSub2, rcSubRgn2 );
					
				}

				//m_pImg->Save( CString(_T("Processed.jpg")) );

				Invalidate();
			}
			else if( strRes == "error" )
			{
				strRes = "Sorry. It's expired.";
			}
			else
			{
				strRes = "Sorry. The try failed.";
			}

			//GetDlgItem(IDC_STC_STR)->SetWindowText( strRes );

			m_strRes = strRes;
			

			Invalidate();

			if( bJudgeRes )
			{
				AfxMessageBox("BINGLE!");
			}
			//AfxMessageBox(strRes);
		}
		else
		{
			strRes = "Load Picture error!";
 		}
		if( strRes != "" )
		{
			//AfxMessageBox(strRes);
 		}

	}
	//Invalidate();
	
	//CDialog::OnOK();
}
//*/


void CDemoExeDlg::OnBtnBatch() 
{
	// TODO: Add your control notification handler code here
	m_bInBatchProcess = TRUE;

/////////////////////////Org Process Dirs//////////////////////////////////////////////
	CString strPicDir = _T("D:\\PrjTmp\\Container Project\\Container\\attack");
#ifdef SAVE_MRU_INIFILE
	if( !ReadIni() )
	{
		m_strMRUBatchPath = strPicDir;
		WriteIni();
	}
	else
	{
		strPicDir = m_strMRUBatchPath;
	}
#endif
///////////////////////////////////////////////////////////////////////////////////////
	CString strCaption(_T("Batch Process"));
	CString strTitle(_T("Please Select your Batch Process Directory:"));
	
	CPathDialog dlg(strCaption, strTitle, strPicDir);
	if(dlg.DoModal()==IDOK)
	{
		strPicDir = dlg.GetPathName();
#ifdef SAVE_MRU_INIFILE
		m_strMRUBatchPath = strPicDir;
		WriteIni();
#endif
	}
	else
	{
		return;
	}


	CStringList PicPathList;
	CStringList PicSubDirList;
	GetPicturePathList( strPicDir, PicPathList, PicSubDirList );

//*//Scale Try
	CString filePath;
	CString fileSubDir;
	CString strMDir = "识别结果";
	CreateDirectory( strMDir, NULL );
	strMDir += _T("\\");
	CString strBingleDir = strMDir + "\\" + "Rec\\";
	CreateDirectory( strBingleDir, NULL );
	strBingleDir += "JR\\";
	CreateDirectory( strBingleDir, NULL );
	CString strNoRecDir = strMDir + "\\" + "NoRec\\";
	CreateDirectory( strNoRecDir, NULL );
	CString strProDir = strMDir + "\\Rec\\JW\\";
	CreateDirectory( strProDir, NULL );

#ifdef SAVE_REC_INFO_TO_TXT
	fstream fBingleFile;
	fstream fNoRecFile;
	fstream fProFile;

	CString strInfoFile;
	strInfoFile.Format( "%sBingleRes.txt", strBingleDir );
	fBingleFile.open( strInfoFile, ios::out | ios::trunc );
	strInfoFile.Format( "%sNoRec.txt", strNoRecDir );
	fNoRecFile.open( strInfoFile, ios::out | ios::trunc );
	strInfoFile.Format( "%sPro.txt", strProDir );
	fProFile.open( strInfoFile, ios::out | ios::trunc );
#endif

#ifdef SAVE_TIME_INFO
	int nProcFiles = 0;
	long nTotalProcTime = 0;
	long nAverProcTime = 0;
	long nMaxProcTime = 0;
	CString strLongProcFile = "";

	fstream fProcTimeInfo;
	fProcTimeInfo.open( "tProcTime.txt", ios::out | ios::trunc );
#endif


    while( !PicPathList.IsEmpty() )
	{
	    filePath = PicPathList.RemoveHead();
		fileSubDir = PicSubDirList.RemoveHead();

		CString strRes = "";
		CString strNation = "";
		if( m_pImg->Load(filePath) )//把图象读入m_pImage中
		{
			_splitpath( filePath, drive, dir, fname, ext );

#ifdef SAVE_CUR_PROCFILE
			CString strFileName;
			strFileName.Format( "%s%s", fname, ext );
			CopyFile( filePath, strFileName, FALSE );
#endif

			
#ifdef SAVE_TIME_INFO
			long tSt = GetTickCount();
#endif
			m_NumRec.SetProcFileString(filePath);
			BOOL bJudgeRes = FALSE;
			strRes = m_NumRec.RecNum(m_pImg, bJudgeRes);
			//strRes = m_NumRec.RecTopNum(m_pImg, bJudgeRes);

/////////////////////////C Interface Call/////////////////////////////////////////
//			int nImgWidth = m_pImg->GetWidth();
//			int nImgHeight = m_pImg->GetHeight();
//			LPCONNUMINFO pInfo = new CONNUMINFO;
//			RecConNum( m_pImg->GetBitsAddress(), nImgWidth, nImgHeight, pInfo);
//			strRes.Format( "%s" , pInfo->ConNum );
// 			bJudgeRes = pInfo->bJudge;
// 			delete pInfo;
//////////////////////////////////////////////////////////////////////////////////

#ifdef SAVE_TIME_INFO
			long tEd = GetTickCount();
			int tPc = tEd - tSt;
			nProcFiles++;
			nTotalProcTime += tPc;
			if( tPc > nMaxProcTime )
			{
				nMaxProcTime = tPc;
				strLongProcFile = filePath;
			}
#endif

#ifdef SAVE_CUR_PROCFILE			
			DeleteFile( strFileName );
#endif

			CString strDesPath = "";
			CString strDesDir = "";
			if( strRes != "" )
			{
				strDesDir.Format("%sRec",strMDir);
				CreateDirectory( strDesDir, NULL );
				strDesDir += "\\";
				if( bJudgeRes )
				{
					strDesDir += "JR";
					CreateDirectory( strDesDir, NULL );
					strDesDir += "\\";
#ifdef SAVE_REC_INFO_TO_TXT
					fBingleFile << filePath << endl;
#endif
				}
				else
				{
					strDesDir += "JW";
					CreateDirectory( strDesDir, NULL );
					strDesDir += "\\";
#ifdef SAVE_REC_INFO_TO_TXT
					fProFile << filePath << endl;
#endif
				}
#ifdef SAVE_SUBDIR
				strDesDir += fileSubDir;
				//CreateDirectory(strDesDir,NULL);
				CreateIntermediateDirectory(LPCTSTR(strDesDir));
 				strDesDir += "\\";
#endif
				strDesPath.Format( "%s%s_%s%s",strDesDir,fname,strRes,ext );
			}
			else
			{
				strDesDir.Format("%sNoRec",strMDir);
				CreateDirectory( strDesDir, NULL );
				strDesDir += "\\";
#ifdef SAVE_SUBDIR
				strDesDir += fileSubDir;
				//CreateDirectory(strDesDir,NULL);
				CreateIntermediateDirectory(LPCTSTR(strDesDir));
 				strDesDir += "\\";
#endif
				strDesPath.Format( "%s%s%s",strDesDir,fname,ext );
#ifdef SAVE_REC_INFO_TO_TXT
				fNoRecFile << filePath << endl;
#endif
			}
			CopyFile( filePath, strDesPath, TRUE );
		}
	}
//*/


#ifdef SAVE_TIME_INFO
	nAverProcTime = nTotalProcTime / nProcFiles;
	fProcTimeInfo << " Average Process Time : " << nAverProcTime << "ms;" << endl;
	fProcTimeInfo << " Max Process Time : " << nMaxProcTime << "ms..." << endl;
	fProcTimeInfo << " Long Process File : \n" << strLongProcFile << endl;
	fProcTimeInfo.close();

	_splitpath( strLongProcFile, drive, dir, fname, ext );
	CString strDesPath;
	strDesPath.Format( "LongToPr_%s%s", fname, ext );
	CopyFile( strLongProcFile, strDesPath, FALSE );
#endif

#ifdef SAVE_REC_INFO_TO_TXT
	fBingleFile.close();
	fNoRecFile.close();
	fProFile.close();
#endif

	m_bInBatchProcess = FALSE;
	AfxMessageBox("Ko!");
}

void CDemoExeDlg::OnBtnInterface() 
{
	// TODO: Add your control notification handler code here
	InitVars();
	CFileDialog dlgLoad(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,
		"所有图象文件(*.tif; *.jpg; *.bmp; *.tga)|*.tif; *.jpg; *.bmp; *.tga|TIFF 文件(*.tif)|*.tif|JPEG 文件(*.jpg)|*.jpg|Windows 位图(*.bmp)|*.bmp|Targa 文件(*.tga)|*.tga||");

	if( dlgLoad.DoModal() == IDOK )
	{
		m_bShowImg = TRUE;
		CString newName = dlgLoad.GetPathName(); 
		CString szValue = AfxGetApp()->GetProfileString(_T("Settings"),"Image Path",NULL);
		dlgLoad.m_ofn.lpstrInitialDir = szValue;
		CString m_strImageName = dlgLoad.GetFileName();
		int nLength = newName.GetLength() - m_strImageName.GetLength() - 1;
		szValue = newName.Left(nLength);

		AfxGetApp()->WriteProfileString(_T("Settings"),"Image Path",szValue);

		CString strRes = "";
		CString strNation = "";
		if( m_pImg->Load(newName) )//把图象读入m_pImage中
		{
			m_NumRec.SetProcFileString(newName);

			int nPicWidth = 0;
			int nPicHeight = 0;

			nPicWidth = m_pImg->GetWidth();
			nPicHeight = m_pImg->GetHeight();

			IMAGE imgR = ImageAlloc( nPicWidth , nPicHeight );
			IMAGE imgG = ImageAlloc( nPicWidth , nPicHeight );
			IMAGE imgB = ImageAlloc( nPicWidth , nPicHeight );
			IMAGE imgGray = ImageAlloc( nPicWidth, nPicHeight );

			CRect rcPic;
			m_pImg->GetRect(rcPic);
			m_pImg->GetImage( rcPic , imgR[0] , imgG[0] , imgB[0] );

			for( int jj = 0; jj < nPicHeight; jj++ )
			{
				for( int ii = 0; ii < nPicWidth; ii++ )
				{
					imgGray[jj][ii] = (imgR[jj][ii] + imgG[jj][ii] + imgB[jj][ii]) / 3;
				}
			}

			ObjRectArray preRects;
			//m_NumRec.GetPreNumRects( imgGray, preRects );
			m_NumRec.GetPreVerNumRects( imgGray, preRects );
			DrawObjRectArray( m_pImg, preRects, 255, 0, 0 );

			Invalidate();

			ImageFree( imgGray );
			ImageFree( imgR );
			ImageFree( imgG );
			ImageFree( imgB );
		}
		else
		{
			strRes = "Load Picture error!";
 		}
	}

	CString strRes = "HDMU6016109";
 	BOOL bRec = m_NumRec.JudgeResString(strRes);

}

#ifdef SAVE_MRU_INIFILE
BOOL CDemoExeDlg::ReadIni()
{
	CIniFile iFile;
	iFile.SetName("MRU");
	if( !iFile.OpenIniFileForRead() ) return FALSE;
	CString sec1 = _T("MRU Path");
	iFile.GetItemString( sec1, "Batch Test Path", m_strMRUBatchPath);
	iFile.CloseIniFile();
	return TRUE;
}

void CDemoExeDlg::WriteIni( )
{
	CIniFile iFile;
	iFile.SetName("MRU");
	iFile.OpenIniFileForWrite();
	iFile.WriteSection( "MRU Path" );
	iFile.WriteItemString( "Batch Test Path", m_strMRUBatchPath );
	iFile.CloseIniFile();	
}
#endif



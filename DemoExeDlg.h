// DemoExeDlg.h : header file
//

#if !defined(AFX_DEMOEXEDLG_H__A415267F_77D5_4325_9A5F_9F78FE134180__INCLUDED_)
#define AFX_DEMOEXEDLG_H__A415267F_77D5_4325_9A5F_9F78FE134180__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDemoExeDlg dialog

class CDemoExeDlg : public CDialog
{
// Construction
public:
	CDemoExeDlg(CWnd* pParent = NULL);	// standard constructor
	~CDemoExeDlg();
// Dialog Data
	//{{AFX_DATA(CDemoExeDlg)
	enum { IDD = IDD_DEMOEXE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoExeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDemoExeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnBtnBatch();
	afx_msg void OnBtnInterface();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CNumRec m_NumRec;

	BOOL m_bShowImg;

	CDIBitmap *m_pImg;
	CDIBitmap *m_pImgSub1;
	CDIBitmap *m_pImgSub2;

	CString m_strRes;

	BOOL m_bInBatchProcess;

	BOOL InitVars();

#ifdef SAVE_MRU_INIFILE
	CString m_strMRUBatchPath;
	BOOL ReadIni();
	void WriteIni();
#endif

#ifdef SAVE_SUBDIR
	/*
	描述：
		创建多级目录
	参数：
		strDirectory	要创建的目录，比如 D:\Folder1\Folder2 或者 Folder1\Folder2\Folder3
	返回值：
		true	创建成功 或 目录已存在
		false	创建失败
	*/
	bool CreateIntermediateDirectory (const char *strDirectory)
	{
		if (strDirectory==NULL || strDirectory[0]==0)
		{
			return false;
		}

		bool bErrorOccur = false;
		CString csDirectory = strDirectory;
		CString csIntermediateDirectory;

		csDirectory.Replace ('/', '\\');
		while (csDirectory.Replace ("\\\\", "\\") > 0);
		csDirectory.TrimRight ('\\');

		int iLastIndex = 0;
		while (true)
		{
			iLastIndex = csDirectory.Find ('\\', iLastIndex);

			if (iLastIndex == -1)
			{
				csIntermediateDirectory = csDirectory;
			}
			else
			{
				csIntermediateDirectory = csDirectory.Left (iLastIndex);
				iLastIndex ++;
			}

			// 如果该文件夹不存在，则创建之
			HANDLE hDirectory = 
			CreateFile (
				csIntermediateDirectory,
				GENERIC_READ,
				FILE_SHARE_READ,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL | FILE_FLAG_BACKUP_SEMANTICS ,
				NULL
				);

			if (hDirectory == INVALID_HANDLE_VALUE)
			{
				BOOL bCreated = CreateDirectory (csIntermediateDirectory, NULL);
				if (!bCreated)
				{
					//logger.Log (LL_ERROR, "Create directory %s error! ErrorCode=%d",
					//	csIntermediateDirectory,
					//	GetLastError ()
					//	);
					bErrorOccur = true;
					break;
				}
			}
			else {
				CloseHandle (hDirectory);
			}

			if (iLastIndex == -1)
			{
				break;
			}
		}

		return !bErrorOccur;
	}
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMOEXEDLG_H__A415267F_77D5_4325_9A5F_9F78FE134180__INCLUDED_)

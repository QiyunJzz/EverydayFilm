// Update.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "UpdateDlg.h"
#include "DownLoadControl.h"


// CUpdateApp:
// �йش����ʵ�֣������ Update.cpp
//

class CUpdateApp : public CWinApp
{
public:
	enum enDownMode{DL_NORMAL=0,DL_FORCE,DL_CHECK};	

public:
	CUpdateApp();
	BOOL OnlyOneExe();
	void OnInitFile();
	int OnGetUpdateFile(CString strUrl);
	int OnGetRunMode();
	BOOL OnRunExe();
	BOOL GetFileExist(CString strFile);
	CString GetExeVision(CString strExe);
	BOOL CompareVision(CString strUpdate,CString strExe);
	BOOL IsUpdateNow();  
	CString GetExeModulePath();

// ��д
	public:
	virtual BOOL InitInstance();

public:
	CString m_strFile,m_strFileBuffer;
	CString m_strUrl;
	CString m_strFilePath,m_strFileName,m_strExePath;
	CString m_strFileVision;
	CDownLoadControl m_downControl;
	enDownMode  m_enDlState;

	BOOL m_bDownComplete;
// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CUpdateApp theApp;
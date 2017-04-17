// Apply.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "Header.h"
#include "ShowWnd.h"


#define MAX_TCHAR 256
// CApplyApp:
// �йش����ʵ�֣������ Apply.cpp
//

typedef struct tagCOMMANDLINE
{
public:
    tagCOMMANDLINE()
	{
		m_strClassHandle.Empty();
		m_strName.Empty();
		m_strWeb.Empty();
		m_strIconLink.Empty();
		m_strEs.Empty();
		m_szSize=CSize(0,0);
		m_bScroll=FALSE;
		m_bShield=FALSE;
		m_strAdUrl.Empty();
	};
public:
	CString     m_strClassHandle,//���;��
			    m_strName,	//������
			    m_strWeb,  //����ʲô��ҳ
				m_strIconLink,		//  ����ͼ����ҳ
				m_strEs;			//������Ϣ
	BOOL		m_bScroll;
	CSize       m_szSize;		 //�����С
	BOOL        m_bShield;
	CString     m_strAdUrl;
}CommandLine,*pCommandLine;


class CApplyApp  : public CWinApp
{
public:
	CApplyApp();

// ��д
	public:
	virtual BOOL InitInstance();
	BOOL Parse_Command();
	void Parse_String(LPCTSTR strVal);
	void StringToSize(CString strVal);
	BOOL OnlyOneExe();
	int OnGetUpdateFile(CString szURL, CString Filename);

	CString GetExeModulePath(HINSTANCE hInstance=NULL);
	BOOL JudgeDirectoryAndCreateMulDirectory(CString strPath);
	BOOL IsFileExist(CString strFile);

public:				
	CommandLine m_sCommandLine;
	CShowWnd pShowWnd;

public:
	CString m_strIcon;
	CString sURL;

	_bstr_t strURL;
// ʵ��
	DECLARE_MESSAGE_MAP()
};

extern CApplyApp theApp;
// ApplyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Apply.h"
#include "ApplyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CApplyDlg �Ի���
/////////////////////////////////////////////////////////////////////////////////////////////
////////
typedef   BOOL   (FAR   PASCAL   *   FUNCTransparent)(   
											HWND   hwnd,                       //   handle   to   the   layered   window   
											COLORREF   crKey,             //   specifies   the   color   key   
											BYTE   bAlpha,                   //   value   for   the   blend   function   
											DWORD   dwFlags                 //   action   
											);   

void CApplyDlg::SetTrans(int itrans)
{
	HMODULE   hModule   =   GetModuleHandle(_T("user32.dll"));   
    FUNCTransparent   SetLayeredWindowAttributes;   
    SetLayeredWindowAttributes= (FUNCTransparent)GetProcAddress(hModule,"SetLayeredWindowAttributes");      
     //  ���÷ֲ���չ���   
    SetWindowLong(GetSafeHwnd(),GWL_EXSTYLE,GetWindowLong(GetSafeHwnd(),GWL_EXSTYLE)|0x80000L);   
    //   70%   alpha   
    SetLayeredWindowAttributes(GetSafeHwnd(),   0,   (255   *   itrans)   /   100,   0x2); 

}



CApplyDlg::CApplyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CApplyDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//m_hIcon=(HICON)::LoadImage(0,_T("res\\Apply.ico"),IMAGE_ICON,   16,   16, LR_LOADFROMFILE );
}

void CApplyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

void CApplyDlg::NewShowWnd()
{
	//m_renderEngine.SetSkin();
	CShowWnd* pShowWnd=new CShowWnd();
	pShowWnd->CreatePlayWnd();
	pShowWnd->ShowWindow(TRUE);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////
BEGIN_MESSAGE_MAP(CApplyDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CApplyDlg ��Ϣ�������

BOOL CApplyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��


	SetTrans(0);
	//ɾ��WS_EX_APPWINDOW��չ���
	ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW);
	NewShowWnd();
	NewShowWnd();
	NewShowWnd();
	NewShowWnd();

	SetTimer(100,500,NULL);
	return TRUE;  
}



void CApplyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CApplyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CApplyDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if(nIDEvent==100)
	{
		this->ShowWindow(FALSE);
		KillTimer(100);
	
	}

	CDialog::OnTimer(nIDEvent);
}

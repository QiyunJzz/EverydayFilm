// TestApplyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestApply.h"
#include "TestApplyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

	//handle='7758'|name='����Ӧ��'|web='www.baidu.com'|icon='logo_16.ico'|iconlink='www.linkcon.com'|iconsavepath='\\apps\\200002017\\' 
	//|es='���������ܺ�'|size='800,400' "  
	// �ַ���ʽ������գ������ж���ո��tab �Լ� ��|��  
	// �������������������վ��ͼ�ꡢ ͼ�����ص�ַ��ͼ�걣��Ŀ¼�����·������������Ϣ�������С


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTestApplyDlg �Ի���




CTestApplyDlg::CTestApplyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestApplyDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestApplyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_str);
}

BEGIN_MESSAGE_MAP(CTestApplyDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CTestApplyDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTestApplyDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTestApplyDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTestApplyDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CTestApplyDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CTestApplyDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CTestApplyDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CTestApplyDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CTestApplyDlg::OnBnClickedButton9)
END_MESSAGE_MAP()


// CTestApplyDlg ��Ϣ�������

BOOL CTestApplyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	strPath=GetExeModulePath();
	strPath.Append(_T("//Apply.exe"));

	m_str.SetWindowText(_T("webFuntion=fund handle=7765 name=�Խת�� web=http://360.tuyaya.com/bd_jizhuanwan.php/ iconlink=http://www.zhidao001.com/home.gif es=�Խת�� size=540,340"));

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTestApplyDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestApplyDlg::OnPaint()
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
HCURSOR CTestApplyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


CString CTestApplyDlg::GetExeModulePath(HINSTANCE hInstance)
{
	TCHAR szFilePath[MAX_PATH + 1]; 
	AfxGetInstanceHandle();
	GetModuleFileName(hInstance, szFilePath, MAX_PATH); 
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0;//ɾ���ļ�����ֻ���·��
	CString str_url = szFilePath;
	return str_url;
}


void CTestApplyDlg::OnBnClickedButton1()
{
	strVal.Empty();

	strVal=_T("handle=7758 name=��ݲ�ѯ web=http://baidu.kuaidi100.com/ iconlink=http://www.zhidao001.com/home.gif es=��ݲ�ѯ������ǰ���� size=800,380");


	ShellExecute(NULL,_T("open"),strPath,strVal,NULL,SW_SHOWNORMAL);
}

void CTestApplyDlg::OnBnClickedButton2()
{
	strVal.Empty();

	strVal=_T("handle=7759 name=����ֱ�� web=http://topic.pptv.com/partner/baiduapp/live/main/ iconlink=http://www.zhidao001.com/home.gif es=���������ر�غܺ� size=900,493");

	ShellExecute(NULL,_T("open"),strPath,strVal,NULL,SW_SHOWNORMAL);
}

void CTestApplyDlg::OnBnClickedButton3()
{
	strVal.Empty();

	strVal=_T("handle=7760 name=�����Ƶ web=http://v.ifeng.com/app/ iconlink=http://www.zhidao001.com/home.gif es=������ӿ�������ʵ���� size=940,630");

	ShellExecute(NULL,_T("open"),strPath,strVal,NULL,SW_SHOWNORMAL);
}

void CTestApplyDlg::OnBnClickedButton4()
{
	strVal.Empty();

	strVal=_T("handle=7761 name=����Ԥ�� web=http://shenghuo.360.cn/tq/yb iconlink=http://www.zhidao001.com/home.gif es=����Ԥ�� size=400,600");

	ShellExecute(NULL,_T("open"),strPath,strVal,NULL,SW_SHOWNORMAL);
}

//////////////////////////////////////////////////////////////
///////////
void CTestApplyDlg::OnBnClickedButton5()
{
	strVal.Empty();

	
	strVal=_T("handle=7762 name=���ߵ�ͼ web=http://ditu.google.cn/maps?hl=zh-CN&tab=ll iconlink=http://www.zhidao001.com/home.gif es=���ߵ�ͼ size=1380,746");

	ShellExecute(NULL,_T("open"),strPath,strVal,NULL,SW_SHOWNORMAL);
}

void CTestApplyDlg::OnBnClickedButton6()
{
	strVal.Empty();

	
	strVal=_T("handle=7763 name=�г�ʱ�̱� web=http://lieche.58.com/app/search.html iconlink=http://www.zhidao001.com/home.gif es=�г�ʱ�̱� size=800,600");

	ShellExecute(NULL,_T("open"),strPath,strVal,NULL,SW_SHOWNORMAL);
}

void CTestApplyDlg::OnBnClickedButton7()
{
	strVal.Empty();

	
	strVal=_T("handle=7764 name=��Ʊ���� web=http://app.hexun.com/market/ iconlink=http://www.zhidao001.com/home.gif es=��Ʊ���� size=770,622");

	ShellExecute(NULL,_T("open"),strPath,strVal,NULL,SW_SHOWNORMAL);
}

void CTestApplyDlg::OnBnClickedButton8()
{
	strVal.Empty();

	
	strVal=_T("handle=7765 name=�Խת�� web=http://360.tuyaya.com/bd_jizhuanwan.php/ iconlink=http://www.zhidao001.com/home.gif es=�Խת�� size=540,340");

	ShellExecute(NULL,_T("open"),strPath,strVal,NULL,SW_SHOWNORMAL);
}

void CTestApplyDlg::OnBnClickedButton9()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString m_strValue;
	m_str.GetWindowText(m_strValue);
	ShellExecute(NULL,_T("open"),strPath,m_strValue,NULL,SW_SHOWNORMAL);
}

void CTestApplyDlg::OnStnClickedStatic1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

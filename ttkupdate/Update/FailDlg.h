#pragma once


// CFailDlg �Ի���

class CFailDlg : public CDialog
{
	DECLARE_DYNAMIC(CFailDlg)

public:
	CFailDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFailDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_DOWNLOAD_FAIL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

private:
	CSuperLink m_linkSite;
	CFont    m_Font; 

public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedBtnOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};

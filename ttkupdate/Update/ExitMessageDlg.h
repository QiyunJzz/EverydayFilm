#pragma once


// CExitMessageDlg �Ի���

class CExitMessageDlg : public CDialog
{
	DECLARE_DYNAMIC(CExitMessageDlg)

public:
	CExitMessageDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CExitMessageDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_EXITMESSAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnOk();
	afx_msg void OnBnClickedBtnCancel();
};

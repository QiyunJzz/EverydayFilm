#pragma once


// CCheckDlg �Ի���

class CCheckDlg : public CDialog
{
	DECLARE_DYNAMIC(CCheckDlg)

public:
	CCheckDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCheckDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_CHECK };


public:
	void ShowWindowEx(BOOL m_bShow=TRUE);
	void ShowProcessCtrl();


public:
	CWinThread* pCheckThread;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnCancel();
	virtual BOOL OnInitDialog();
};

#pragma once


// CIntroductionDlg �Ի���

class CIntroductionDlg : public CDialog
{
	DECLARE_DYNAMIC(CIntroductionDlg)

public:
	CIntroductionDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CIntroductionDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_INTRODUCTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedBtnNext();
	afx_msg void OnBnClickedBtnCancel();
};

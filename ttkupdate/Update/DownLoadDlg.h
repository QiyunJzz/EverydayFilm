#pragma once


// CDownLoadDlg �Ի���

class CDownLoadDlg : public CDialog
{
	DECLARE_DYNAMIC(CDownLoadDlg)

public:
	CDownLoadDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDownLoadDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_DOWNLOAD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��


private:
	CFont    m_Font; 
	CString m_strUpTip;

public:
	CProgressCtrl* GetProgressCtrlDown();
	CListBox*	GetListBoxDown();
	CButton *   GetBtnAtOnce();
	CButton *   GetBtnTryAggin();
	CStatic *   GetStaticShow();


public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedBtnNext();
	afx_msg void OnBnClickedBtnCancel();
	afx_msg void OnBnClickedBtnTryAgain();
	afx_msg void OnBnClickedBtnLookCarefully();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};

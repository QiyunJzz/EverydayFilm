#ifndef __CSOCKETCLIENT__H__
#define __CSOCKETCLIENT__H__
#pragma once
#include "afxsock.h"

#define NET_BUFFER_SIZE			2048		// Ĭ�ϻ����С


class CSocketClient :
	public CSocket
{
public:
	CSocketClient(void);
	~CSocketClient(void);

	BOOL IsConnected();  //�Ƿ�����
	CString GetDigitStrAtHead ( LPCTSTR lpszStr );		//�õ����ֱ�ͷ
	int GetResponse ( CString *pcsResponseStr=NULL, BOOL bBlock=TRUE );   //�õ���Ӧ
	BOOL GetResponse ( int nVerifyCode, CString *pcsResponseStr=NULL );
	CString GetResponseHistoryString();							//�ȵ���ʷ��Ӧ
	void ClearResponseHistoryString();							//�����ʷ��Ӧ

public:
	BOOL Connect ( LPCTSTR lpszHost, USHORT nPort );			//����
	void Disconnect();								//��������
	int Receive (char *pBuf, int nSize, BOOL bBlock=TRUE );		//��������
	BOOL GetIPAndPortByPasvString(LPCTSTR lpszPasvString, OUT CString &csIP, OUT USHORT &nPort );	//�õ�IP�Ͷ˿�
	void SetEventOfEndModule ( HANDLE hEvtEndModule );			//���ý����¼�
	BOOL Send ( char *pData, int nSize );						//��������
	BOOL SendString(LPCTSTR lpszData, ... );					//����


public:
	virtual BOOL ConnectHelper(const SOCKADDR* lpSockAddr, int nSockAddrLen);		//���Ӱ���
	BOOL PumpMessagesMy(UINT uStopFlag);	//�ҵ���Ϣ��


private:
	CString m_strResponseHistoryString;		//��ʷ��Ӧ
	HANDLE m_hEvtEndModule;					//�¼����
	BOOL m_bConnected;						//�����ж�

public:
	int m_nIndex;
};
#endif
#ifndef __DOWNLOADPUBLIC__H__
#define __DOWNLOADPUBLIC__H__
#pragma once
#include <Afxmt.h>
#include <afxtempl.h>
#include "SocketClient.h"


//ȱʡ�����Դ���
const UINT DEFAULT_RETRY_MAX	= 10; 

//�߳����� ��ʱ  ��������
#define SLEEP_RETURN_Down(x)             {if ( ::WaitForSingleObject ( m_hEvtEndModule, x ) == WAIT_OBJECT_0 ) return DownloadEnd(FALSE);}


enum
{
	NOTIFY_TYPE_GOT_REMOTE_FILENAME,				// ȡ��Զ��վ���ļ���, �������ص��ļ����ض���ʱ�ŷ��͸�֪ͨ��lpNotifyData Ϊ LPCTSTR ���͵��ļ����ַ���ָ��
	NOTIFY_TYPE_GOT_REMOTE_FILESIZE,				// ȡ��Զ��վ���ļ���С��lpNotifyData Ϊ int ���͵��ļ���С
	NOTIFY_TYPE_START_DOWNLOAD,						// ��ʼ���أ�lpNotifyData ����
	NOTIFY_TYPE_END_DOWNLOAD,						// �������أ�lpNotifyData Ϊ ENUM_DOWNLOAD_RESULT ���͵����ؽ��
	NOTIFY_TYPE_WILL_DOWNLOAD_SIZE,					// ������Ҫ���صĴ�С��lpNotifyData Ϊ int ���͵���Ҫ���صĴ�С
	NOTIFY_TYPE_THREAD_DOWNLOADED_SIZE,				// ĳ�߳������ص����ݴ�С��lpNotifyData Ϊ int ���͵������صĴ�С
};


typedef struct tagDownloadNotifyPara     //��������֪ͨ����
{
	int nIndex;
	UINT nNotityType;
	LPVOID lpNotifyData;
	LPVOID pDownloadMTR;
} DownloadNotifyPara;

typedef CArray<DownloadNotifyPara,DownloadNotifyPara&> g_ArrayDownloadNotifyPara;

// ��Ϣ֪ͨ�ص�����
typedef void (*FUNC_DownloadNotify) ( DownloadNotifyPara *pDownloadNotifyPara, WPARAM wParam );
typedef void (*FUNC_SaveDownloadInfo) ( int nIndex, int nDownloadedSize, int nSimpleSaveSize, WPARAM wParam );

// ȱʡ�˿ں�
#define DEFAULT_HTTP_PORT			80
#define DEFAULT_HTTPS_PORT			443
#define DEFAULT_FTP_PORT			21
#define DEFAULT_SOCKS_PORT			6815

typedef enum _DownloadResult   //���ؽ��
{
	ENUM_DOWNLOAD_RESULT_SUCCESS,
	ENUM_DOWNLOAD_RESULT_FAILED,
	ENUM_DOWNLOAD_RESULT_CANCEL,
} ENUM_DOWNLOAD_RESULT;


class CDownLoadPublic
{
public:
	CDownLoadPublic(void);
	~CDownLoadPublic(void);

	BOOL ThreadIsRunning();				//�߳��Ƿ�����
	CString GetDownloadObjectFileName(CString *pstrExtensionName=NULL);  //�õ����ض����ļ���
	void ClearThreadHandle();					//����߳̾��
	void ResetVar();							//��������Var
	int GetUndownloadBytes();					//�õ�δ�����ֽ�
	BOOL ThreadProcDownload();						//�߳�����
	BOOL SetSaveFileName(LPCTSTR lpszSaveFileName);		//���ñ��澶·��
	int GetWillDownloadSize();							//�õ���Ҫ�����ֽ�
	void SetWillDownloadSize(int nWillDownloadSize);		//���ý�Ҫ�����ֽ�
	int GetDownloadedSize();								//�õ����ش�С
	void SetDownloadedSize(int nDownloadedSize);			//�������ش�С
	int GetTempSaveBytes();									//�õ�Ԥ�����ֽ�
	void SetTempSaveBytes(int nTempSaveBytes);				//����Ԥ�����ֽ�
	CString GetRemoteFileName();							//�õ�Զ���ļ���
	BOOL SetDownloadUrl(LPCTSTR lpszDownloadUrl);			//��������URL
	virtual BOOL Connect();									//�Ƿ�����
	BOOL GetRemoteSiteInfo();								//�õ�Զ��վ����Ϣ

	void SetAuthorization (LPCTSTR lpszUsername, LPCTSTR lpszPassword);		//������Ȩ
	void SetReferer(LPCTSTR lpszReferer);										//���òο�
	void SetUserAgent(LPCTSTR lpszUserAgent);									//�����û�����
	void SetSaveDownloadInfoCallback(FUNC_SaveDownloadInfo Proc_SaveDownloadInfo, WPARAM wParam);  //���ñ��������Ϣ�ص�����
	virtual BOOL Download(				//����
		int nWillDownloadStartPos,
		int nWillDownloadSize,
		int nDownloadedSize
		);
	BOOL IsSupportResume() ;   //�Ƿ�֧�ָֻ�
	CString GetProtocolType() ;  //Э��
	time_t GetTimeLastModified() ;   //�õ�����޸�ʱ��
	int GetFileTotalSize() ;		//�õ��ļ��ܴ�С
	CString GetUserName() ;			//�õ��û���
	CString GetPassword() ;				//�õ�����
	CString GetDownloadUrl() ;		//�õ�URL
	BOOL IsDownloadSuccess() ;		//�����Ƿ�ɹ�
	HANDLE GetThreadHandle() ;				//�õ��߳̾��	
	int GetWillDownloadStartPos() ;	//�õ���Ҫ��ʼ����λ��
	CString GetServerName() ;				//�õ���������
	void StopDownload();											//ֹͣ����

	virtual BOOL GetRemoteSiteInfoPro();							//�õ�Զ��վ����Ϣ
	virtual BOOL DownloadOnce();									//�Ƿ���������
	CString GetRefererFromURL();									//ͨ��URL�õ��ο�
	int SaveDataToFile(char *pData, int nSize);						//�������ݵ��ļ�
	virtual BOOL RecvDataAndSaveToFile(CSocketClient &SocketClient,char* szTailData=NULL, int nTailSize=0); //�������ݺͱ��浽�ļ�
	BOOL DownloadEnd(BOOL bRes);	

	BOOL OpenFileForSave();  //Ϊ������ļ�

public:
	LPVOID m_pDownloadMTR;
	int m_nIndex;

public:
	CFile m_file;

	// ������URL
	CString		m_strDownloadUrl;
	CString		m_strSaveFileName;

	// ����������Ϣ�Ļص�����
	FUNC_SaveDownloadInfo m_funcSaveDownloadInfo;
	WPARAM m_wSaveDownloadInfo_Param;

	// �Ƿ�֧�ֶϵ�����
	BOOL		m_bSupportResume;
	HANDLE		m_hThread;

	// �ļ��Լ����ش�С
	int					m_nFileTotalSize;				// �ļ��ܵĴ�С��-1��ʾδ֪�ļ���С
	int					m_nWillDownloadStartPos;		// Ҫ�����ļ��Ŀ�ʼλ��
	int					m_nWillDownloadSize;			// ������Ҫ���صĴ�С��-1��ʾ��֪���ļ���С���������ص��������ر�����Ϊֹ
	CCriticalSection	m_csWillDownloadSize;		// ���� m_nWillDownloadSize �����Ļ�����
	int					m_nTempSaveBytes;				// �������ʱ�����е��ֽ���
	CCriticalSection	m_csTempSaveBytes;			// ���� m_nTempSaveBytes �����Ļ�����
	int					m_nDownloadedSize;				// �����ص��ֽ�����ָ��ȫд���ļ��е��ֽ�������������ʱ�����������
	CCriticalSection	m_csDownloadedSize;			// ���� m_nDownloadedSize �����Ļ�����

	// �ļ�����(Զ���ļ�����Ϣ)
	CTime		m_TimeLastModified;

	// Referer
	CString		m_strReferer;
	CString		m_strCookieFlag;

	// UserAgent
	CString		m_strUserAgent;

	// �Ƿ������֤ : Request-Header: Authorization
	CString		m_strUsername;
	CString		m_strPassword;

	// ���ع��������õı���
	CString		m_strProtocolType;	// ��ʹ�õĴ���Э�飺http��ftp��
	CString		m_strServer;
	CString		m_strObject;
	CString		m_strFileName;
	USHORT		m_nPort;

	BOOL m_bDownloadSuccess;

public:
	// ģ������¼�
	HANDLE m_hEvtEndModule;
	// ���ӷ������� Socket
	CSocketClient m_SocketClient;
};

int Base64Encode(LPCTSTR lpszEncoding, CString &strEncoded);   //����64����
int Base64Decode(LPCTSTR lpszDecoding, CString &strDecoded);	//����64����
BOOL ParseTrueURL(LPCTSTR lpszURL,CString& strServer,CString& strObject,USHORT& nPort, CString &csProtocolType);		//����URL
void Set_DownloadNotify_Callback(FUNC_DownloadNotify Proc_DownloadNotify, WPARAM wParam);				//��������֪ͨ
void SetRetryTimes(int nRetryTimes);											//��������ʱ��

#endif
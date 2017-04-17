#include "StdAfx.h"
#include "PublicFunc.h"

CString GetOneLine(CString &strIn)
{
	int nPos = strIn.Find (_T("\r\n"),0);
	if (nPos < 0) return _T("");
	CString strOneLine = strIn.Left(nPos);
	strIn = strIn.Mid(nPos+2);
	return strOneLine;
}

// �ȴ��߳��˳�
BOOL WaitForThreadEnd( HANDLE hThread, DWORD dwWaitTime/*=5000 */ )
{
	BOOL bRet = TRUE;
	if (!HANDLE_IS_VALID(hThread)) return TRUE;
	if (::WaitForSingleObject(hThread, dwWaitTime) == WAIT_TIMEOUT)
	{
		bRet = FALSE;
		::TerminateThread(hThread,0);
	}
	return bRet;
}

CString ErrorCodeFormatMessage( DWORD dwErrorCode )
{
	CString strError;
	LPVOID pv;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		dwErrorCode,
		MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),
		(LPTSTR)&pv,
		0,
		NULL);
	if(pv)
	{
		strError = (TCHAR*)pv;
		LocalFree(pv);
	}
	return strError;
}


// Ϊ�˷��� _tstrchr() �� _tstrrchr() ������ȷ�����ַ������ַ����е������ַ�����ָ�����ַ��滻��
void ReplaceChineseStrToEnglish(TCHAR *szBuf, TCHAR cReplace)
{
	if (!szBuf) return;
	for (int i = 0; szBuf[i] != _T('\0'); i++)
	{
		if (szBuf[i] < 0 && szBuf[i+1] !=_T('\0'))
		{
			szBuf[i] = cReplace;
			szBuf[i+1] = cReplace;
			i ++;
		}
	}
}

// ��׼��·�����ļ������Ѳ������ļ�������������ַ��滻��ָ�����ַ���//u �� StandardizationPathBuffer() �м��ϸú���
CString StandardizationFileForPathName( LPCTSTR lpszFileOrPathName, BOOL bIsFileName, TCHAR cReplaceChar/*='_'*/ )
{
	CString strFileOrPathName = GET_SAFE_STRING(lpszFileOrPathName);
	CString strHead, strTail;
	// ·���������һ��'\\'�������ġ��������ơ�c:\\�����ַ�Ҳ�������ġ���������ȡ���������������滻�����滻���Ժ��ٲ�����
	if (!bIsFileName)
	{
		if (strFileOrPathName.GetLength() >= 1 && (strFileOrPathName[strFileOrPathName.GetLength()-1] ==_T('\\')|| strFileOrPathName[strFileOrPathName.GetLength()-1] ==_T('/')))
		{
			strTail += strFileOrPathName[strFileOrPathName.GetLength()-1];
			strFileOrPathName = strFileOrPathName.Left ( strFileOrPathName.GetLength()-1 );
		}

		if (strFileOrPathName.GetLength() >= 2 && isalpha(strFileOrPathName[0]) && strFileOrPathName[1]==':')
		{
			strHead = strFileOrPathName.Left(2);
			strFileOrPathName = strFileOrPathName.Mid(2);
		}
		if (strFileOrPathName.GetLength() >= 1 && (strFileOrPathName[0]==_T('\\')||strFileOrPathName[0]==_T('/')))
		{
			strHead += strFileOrPathName[0];
			strFileOrPathName = strFileOrPathName.Mid(1);
		}
	}
	else
	{
		strFileOrPathName.Replace(_T("\\"),_T("_"));
		strFileOrPathName.Replace(_T("/"),_T("_"));
	}
	strFileOrPathName.Replace(_T(":"),_T("_"));
	strFileOrPathName.Replace(_T("*"),_T("_"));
	strFileOrPathName.Replace(_T("?"),_T("_"));
	strFileOrPathName.Replace(_T("\""),_T("_"));
	strFileOrPathName.Replace(_T("<"),_T("_"));
	strFileOrPathName.Replace(_T(">"),_T("_"));
	strFileOrPathName.Replace(_T("|"),_T("_"));
	strFileOrPathName.Insert(0, strHead);
	strFileOrPathName += strTail;

	return strFileOrPathName;
}


// ��׼��·�����壬��������ԡ�\����β�����Զ�����
void StandardizationPathBuffer(TCHAR *szPath, int nSize,TCHAR cFlagChar/*='\\'*/ )
{
	int nLen = _tcslen(szPath);
	if (nLen < 1) return;
	ASSERT_ADDRESS(szPath, nLen+1);
	TCHAR szTemp[4] = {0};
	szTemp[0] = cFlagChar;
	if (szPath[nLen-1] != cFlagChar)
		_tcsncat(szPath, szTemp, nSize);

	CString strPath = StandardizationFileForPathName(szPath, FALSE);
	_tcsncpy(szPath,strPath,nSize);
}

TCHAR *hxpStrrChr ( const TCHAR *str, int c )
{
	if (!str) return NULL;
	CString strString = str;
	ReplaceChineseStrToEnglish(strString.GetBuffer(strString.GetLength()), (c>=127)?(c-1):(c+1));
	strString.ReleaseBuffer();
	int nPos = strString.ReverseFind(c);
	if (nPos < 0) return NULL;
	return ((TCHAR*)str+nPos);
}

TCHAR *hxpStrChr (const TCHAR *str, int c)
{
	if (!str) return NULL;
	CString strString = str;
	ReplaceChineseStrToEnglish(strString.GetBuffer(strString.GetLength()), (c>=127)?(c-1):(c+1));
	strString.ReleaseBuffer();
	int nPos = strString.Find(c);
	if (nPos < 0) return NULL;
	return ((TCHAR*)str+nPos);
}


// �����ļ������������ļ�������չ�����磺����·��Ϊ��E:\123\456.bmp������ô szFileName ���ڡ�E:\123\456��
// szExtensionName ���ڡ�bmp��
BOOL PartFileAndExtensionName(
							   IN LPCTSTR lpszFileName,
							   OUT TCHAR *szFileName,
							   IN int nFileNameSize,
							   OUT TCHAR *szExtensionName/*=NULL*/,
							   IN int nExtensionNameSize/*=0*/ )
{
	ASSERT(lpszFileName);
	TCHAR chDirPart =_T('\\');
	if (hxpStrChr(lpszFileName,_T('/')))
		chDirPart =_T('/');

	if (szFileName)
	{
		STRNCPY(szFileName, lpszFileName, nFileNameSize);
	}
	if (szExtensionName)
	{
		memset(szExtensionName, 0, nExtensionNameSize);
	}

	TCHAR *p_Dot = hxpStrrChr (lpszFileName,_T('.'));

	if (!p_Dot)		return TRUE;

	TCHAR *p_Slash = hxpStrrChr(lpszFileName, chDirPart);
	if (szFileName)
	{
		if (p_Dot-lpszFileName >= nFileNameSize)
			return FALSE;
		//		TRACE ( "%d, %d\n", p_Dot-lpszFileName, strlen(lpszFileName) );
		if (int(p_Dot-lpszFileName) < (int)_tcslen(lpszFileName)-1)
			szFileName[p_Dot-lpszFileName] =_T('\0');
	}

	if (p_Slash > p_Dot)		return TRUE;

	if (szExtensionName)
	{
		STRNCPY (szExtensionName, p_Dot+1, nExtensionNameSize);
	}
	return TRUE;
}

// ��һ��������ȫ·����(�����ļ���)�з����·����û���ļ�������
// �ļ������磺�ӡ�E:\001\002.exe���зֵá�E:\001\����������뵽
// lsOnlyPath�У���002.exe������szOnlyFileName��
//
BOOL PartFileAndPathByFullPath (
								IN LPCTSTR lpszFilePath,			// ȫ·����(�����ļ���)
								OUT TCHAR *szOnlyFileName,			// ���ļ�����û��·����
								int nFileNameSize,
								OUT TCHAR *szOnlyPath /*=NULL*/,		// ��·����û���ļ�����
								int nPathSize/*=0*/
								)
{
	ASSERT (lpszFilePath);
	TCHAR chDirPart =_T('\\');
	if (hxpStrChr(lpszFilePath,_T('/')))
		chDirPart =_T('/');

	if (szOnlyFileName)
	{
		memset(szOnlyFileName,0,nFileNameSize);
	}
	if (szOnlyPath)
	{
		memset(szOnlyPath, 0, nPathSize);
	}

	WIN32_FILE_ATTRIBUTE_DATA FileAttrData;
	if ( GetFileAttributesEx (lpszFilePath, GetFileExInfoStandard, (LPVOID)&FileAttrData ) &&
		( FileAttrData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) == FILE_ATTRIBUTE_DIRECTORY
		&& FileAttrData.dwFileAttributes != 0xffffffff ) //	�������Ŀ¼
	{
		if (szOnlyPath)
		{
			STRNCPY(szOnlyPath, lpszFilePath, nPathSize);
			StandardizationPathBuffer(szOnlyPath, nPathSize, chDirPart);
		}
		return TRUE;
	}

	TCHAR *p = hxpStrrChr(lpszFilePath, chDirPart);
	if (!p)
	{
		STRNCPY(szOnlyFileName, lpszFilePath, nFileNameSize);
		return TRUE;
	}

	if (szOnlyFileName)
		STRNCPY(szOnlyFileName, p+1, nFileNameSize);
	if (szOnlyPath)
	{
		STRNCPY (szOnlyPath, lpszFilePath, nPathSize);
		int nLen = p-lpszFilePath+1;
		if(nPathSize-1 < nLen) return FALSE;
		szOnlyPath[nLen] =_T('\0');
	}
	return TRUE;
}

BOOL PartPathAndFileAndExtensionName (
									  IN LPCTSTR lpszFilePath,			// ȫ·����(�����ļ���)
									  OUT CString *pstrOnlyPath,			// �����·����û���ļ�����
									  OUT CString *pstrOnlyFileName,		// ������ļ�����û��·����
									  OUT CString *pstrExtensionName		// �����չ��
									  )
{
	TCHAR szOnlyPath[MAX_PATH] = {0};
	TCHAR szOnlyFileName[MAX_PATH] = {0};
	TCHAR szExtensionName[MAX_PATH] = {0};
	if (!PartFileAndPathByFullPath(lpszFilePath, szOnlyFileName, MAX_PATH, szOnlyPath, MAX_PATH))
		return FALSE;
	if (!PartFileAndExtensionName(szOnlyFileName, szOnlyFileName, MAX_PATH, szExtensionName, MAX_PATH))
		return FALSE;

	if (pstrOnlyPath) *pstrOnlyPath = szOnlyPath;
	if (pstrOnlyFileName) *pstrOnlyFileName = szOnlyFileName;
	if (pstrExtensionName) *pstrExtensionName = szExtensionName;

	return TRUE;
}

int GetMouthByShortStr ( LPCTSTR lpszShortMonth )
{
	const TCHAR* szConstMonth[] =
	{_T("jan"),_T("feb"),_T("mar"),_T("apr"),_T("may"),_T("jun"),_T("jul"),_T("aug"),_T("sep"),_T("oct"),_T("nov"),_T("dec"),_T("")};

	CString strShortMonth = GET_SAFE_STRING ( lpszShortMonth );

	for (int i = 0; i < sizeof(szConstMonth)/sizeof(szConstMonth[0]); i++)
	{
		if (strShortMonth.CompareNoCase(szConstMonth[i]) == 0)
		{
			return (i+1);
		}
	}
	return -1;
};

int CalcCharCount ( LPCTSTR lpszText, TCHAR chCalc )
{
	int nLen = STRLEN_SZ(lpszText);
	int nCount = 0;
	for (int i = 0; i < nLen; i++)
	{
		if ((BYTE)lpszText[i] == (BYTE)chCalc)
			nCount++;
	}
	return nCount;
}

#define  TIME_START_YEAR  1900
BOOL CopyBuffer_Date(int *data,SYSTEMTIME &SysTime)
{
	const int nMinDateDigitCount = 3;
	ASSERT_ADDRESS(data, nMinDateDigitCount*sizeof(int));

	/********��(1000 ~ 9999)********/
	if (data[0] < 1000 || data[0] >= 9999)
		return FALSE;
	SysTime.wYear = data[0];

	/********��(1--12)********/
	if (data[1] < 1 || data[1] > 12)
		return FALSE;
	SysTime.wMonth = data[1];

	/********��(1--31)********/
	if (data[2] < 1 && data[2] > 31)
		return FALSE;
	SysTime.wDay = data[2];

	return TRUE;
}

BOOL CopyBuffer_Time(int *pData, SYSTEMTIME &SysTime )
{
	const int nMinDateDigitCount = 3;
	ASSERT_ADDRESS(pData, nMinDateDigitCount*sizeof(int));

	/********ʱ(0--23)********/
	if (pData[0] <0 || pData[0] > 23)
		return FALSE;
	SysTime.wHour = pData[0];

	/********��(0--59)********/
	if (pData[1] < 0 || pData[1] > 59)
		return FALSE;
	SysTime.wMinute = pData[1];

	/********��********/
	if (pData[2] < 0 || pData[2] > 59)
		return FALSE;
	SysTime.wSecond = pData[2];

	return TRUE;
}

// ConvertStrToCTime() ��һ����ʾ���ڵ��ַ��������ꡢ�¡��ա�ʱ���֡����˳��
// ��"2001-08-09 18:03:30"��ת�� CTime ��ʽ.
// return :(0	-	����) (1 - ��ʱ��ʱ��) (2 -	������) (3 - ��ʱ��)

int ConvertStrToCTime(TCHAR *pchTime, CTime &cTime )
{
	int  i, j, k;
	TCHAR tmpbuf[8] = {0};
	int  nValue[6] = {0};
	SYSTEMTIME SysTime = {0};

	if ((!pchTime)) return FALSE; /* invalid parameter */

	memset((void *)nValue, 0, sizeof(nValue));
	for (i = 0, j = 0, k = 0;  ; i++)
	{
		if (pchTime[i]<_T('0')||pchTime[i]>_T('9')) /* �������ַ� */
		{
			tmpbuf[j] =_T('\0');
			if (j > 0)
			{
				nValue[k++] =_ttoi(tmpbuf);
				j = 0;
				if (k >= 6) break;
			}
			if (pchTime[i] ==_T('\0')) break;
		}
		else if (j < 7) 
			tmpbuf[j++] = pchTime[i];
	}
	if (k < 3) 
		return 0;
	if	(
		CalcCharCount(pchTime,_T('-')) < 2
		&&
		CalcCharCount(pchTime,_T('/')) < 2
		&&
		CalcCharCount(pchTime,_T(':')) < 2
		)
		return 0;

	int nRet = 0;
	// ������ʱ��
	if	(
		(k >= 6)
		&&
		CopyBuffer_Date(nValue, SysTime)
		&&
		CopyBuffer_Time(&nValue[3], SysTime)
		)
	{
		nRet = 1;
	}
	// ������
	else if	(
		(k>=3)
		&&
		CopyBuffer_Date(nValue, SysTime)
		)
	{
		nRet = 2;
	}

	// ��ʱ��
	if	(
		(k>=3)
		&&
		CopyBuffer_Time( nValue, SysTime)
		)
	{
		nRet = 3;
	}

	if (SysTime.wYear < 1971)
		SysTime.wYear = 1971;
	if (SysTime.wMonth < 1)
		SysTime.wMonth = 1;
	if (SysTime.wDay < 1)
		SysTime.wDay = 1;

	CTime tTemp (SysTime);
	cTime = tTemp;

	return nRet;
}

void MytoLower(TCHAR *pSrc)   
{   
	//assert(src);   
	TCHAR *p = pSrc;   
	while(*p !=_T('\0'))   
	{   
		if(64 < *p && *p < 91) //A��65��Z��90   
		{   
			*p = (*p+32);   
		}   
		p++;   
	} 
} 

// ����һ�����ļ�
BOOL CreateNullFile( LPCTSTR lpszFileName, int nFileSize )
{
	if (!lpszFileName) return FALSE;
	DeleteFile(lpszFileName);
	CFile file;
	BOOL bRet = TRUE;
	TRY
	{
		bRet = file.Open(lpszFileName, CFile::modeCreate|CFile::modeWrite|CFile::typeBinary);
		if (bRet && nFileSize > 0)
			file.SetLength(nFileSize);
	}
	CATCH(CFileException, e)
	{
		e->Delete();
		bRet = FALSE;
	}
	END_CATCH
	
	if (!bRet)
	{
		TRACE(_T("Create file [%s] failed. %s"), lpszFileName,ErrorCodeFormatMessage(GetLastError()));
	}
	if (HANDLE_IS_VALID(file.m_hFile))
		file.Close();
	return bRet;
}



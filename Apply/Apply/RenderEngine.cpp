#include "StdAfx.h"
#include "RenderEngine.h"

#define _CRTDBG_MAP_ALLOC 
#include<stdlib.h> 
#include<crtdbg.h> 
#include "Apply.h"

CRenderEngine m_renderEngine;
CRenderEngine::CRenderEngine(void)
{
	m_skn.Empty();
	m_Font.CreateFont(13,0,0,0,FW_NORMAL,FALSE,FALSE,FALSE,ANSI_CHARSET,3,2,1,2,_T("����"));
}

CRenderEngine::~CRenderEngine(void)
{
	RemoveAllImages();
	m_Font.DeleteObject();
}

void CRenderEngine::SetSkin(CString str)
{
	m_skn=str;	
}


void CRenderEngine::DrawIcon(CDC* pDC,UINT uId,CRect pDest)
{
	HICON hIcon;
	if(uId==0) return;

	hIcon = AfxGetApp()->LoadIcon (uId); 
	ICONINFO pIcon;
	GetIconInfo(hIcon,&pIcon);


	if (hIcon != NULL)
	{
		DrawIconEx(pDC->GetSafeHdc(),pDest.left,pDest.top+3,hIcon,pIcon.xHotspot,pIcon.yHotspot,0,NULL,DI_NORMAL);
    }
}

void CRenderEngine::DrawIcon(CDC* pDC,HICON* hIcon,CRect pDest)
{
	if(hIcon==NULL) return;

	ICONINFO pIcon;
	GetIconInfo(*hIcon,&pIcon);

	if (hIcon != NULL)
	{
		DrawIconEx(pDC->GetSafeHdc(),pDest.left,pDest.top+3,*hIcon,pIcon.xHotspot,pIcon.yHotspot,0,NULL,DI_NORMAL);
    }
}


void CRenderEngine::DrawFillRect(CDC* pDC,CRect rect,COLORREF color)
{
	CBrush bkcolor(color);
	pDC->FillRect(&rect,&bkcolor);
}

void CRenderEngine::DrawWindowText(CDC* pDC,CString str,CRect pDest,COLORREF color,CFont* mFont)
{
	if(mFont)	pDC->SelectObject(*mFont);
	else 	pDC->SelectObject(m_Font);

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(color);
	pDC->DrawText(str,str.GetLength(), pDest, DT_LEFT);
}

void CRenderEngine::DrawLine(CDC* pDC,CPoint start,CPoint end,COLORREF color,int bordersize)
{
		CPen m_Pen,*pOldPen;
		m_Pen.CreatePen(PS_SOLID,bordersize,color);
		pOldPen=pDC->SelectObject(&m_Pen);

		pDC->MoveTo(start.x,start.y);
		pDC->LineTo(end.x,end.y);   //�Ϻ�

		pDC->SelectObject(pOldPen);	
		m_Pen.DeleteObject();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////
void CRenderEngine::DrawBorder(CDC* pDC,CRect rcPaint,int bSize,COLORREF color)
{
	if(rcPaint.IsRectEmpty()||bSize<=0||pDC==NULL) return;
			
	CPen m_Pen,*pOldPen;
	m_Pen.CreatePen(PS_SOLID,bSize,color);
	pOldPen=pDC->SelectObject(&m_Pen);

	pDC->MoveTo(0,0);
	pDC->LineTo(rcPaint.Width(),0);   //�Ϻ�
	
	pDC->MoveTo(rcPaint.Width(),0);
	pDC->LineTo(rcPaint.Width(),rcPaint.Height());  //����
	
	pDC->MoveTo(rcPaint.Width(),rcPaint.Height());
	pDC->LineTo(0,rcPaint.Height());  //�º�
	
	pDC->MoveTo(0,rcPaint.Height());
	pDC->LineTo(0,0);  //����


	//�ĸ���
	pDC->MoveTo(2,0);
	pDC->LineTo(0,2);   //����

	pDC->MoveTo(0,rcPaint.Height()-3);
	pDC->LineTo(3,rcPaint.Height());   //����

	pDC->MoveTo(rcPaint.Width()-3,0);
	pDC->LineTo(rcPaint.Width(),2);   //����

	pDC->MoveTo(rcPaint.Width(),rcPaint.Height()-4);
	pDC->LineTo(rcPaint.Width()-4,rcPaint.Height());   //����	

	pDC->SelectObject(pOldPen);	
	m_Pen.DeleteObject();	
}

void CRenderEngine::DrawBorder2(CDC* pDC,CRect rcPaint,int bSize,COLORREF color)
{
	if(rcPaint.IsRectEmpty()||bSize<=0||pDC==NULL) return;
			
	CPen m_Pen,*pOldPen;
	m_Pen.CreatePen(PS_SOLID,bSize,color);
	pOldPen=pDC->SelectObject(&m_Pen);

	pDC->MoveTo(0,1);
	pDC->LineTo(rcPaint.Width(),1);   //�Ϻ�
	
	pDC->MoveTo(rcPaint.Width()-2,0);
	pDC->LineTo(rcPaint.Width()-2,rcPaint.Height());  //����
	
	pDC->MoveTo(rcPaint.Width(),rcPaint.Height()-2);
	pDC->LineTo(0,rcPaint.Height()-2);  //�º�
	
	pDC->MoveTo(1,rcPaint.Height());
	pDC->LineTo(1,0);  //����


	////�ĸ���
	//pDC->MoveTo(2,0);
	//pDC->LineTo(0,2);   //����

	//pDC->MoveTo(0,rcPaint.Height()-3);
	//pDC->LineTo(3,rcPaint.Height());   //����

	//pDC->MoveTo(rcPaint.Width()-3,0);
	//pDC->LineTo(rcPaint.Width(),2);   //����

	//pDC->MoveTo(rcPaint.Width(),rcPaint.Height()-4);
	//pDC->LineTo(rcPaint.Width()-4,rcPaint.Height());   //����	

	pDC->SelectObject(pOldPen);	
	m_Pen.DeleteObject();	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//// image
TImageInfo* CRenderEngine::GetImage(LPCTSTR bitmap)
{
    TImageInfo* data = static_cast<TImageInfo*>(m_mImageHash.Find(bitmap));
    if( !data ) return GetImage(bitmap);
    else return data;
}

TImageInfo* CRenderEngine::GetImageEx(LPCTSTR bitmap, LPCTSTR type, DWORD mask)
{
    TImageInfo* data = static_cast<TImageInfo*>(m_mImageHash.Find(bitmap));
    if( !data ) {
        if( AddImage(bitmap, type, mask) ) {
            data = static_cast<TImageInfo*>(m_mImageHash.Find(bitmap));
        }
    }

    return data;
}

TImageInfo* CRenderEngine::AddImage(LPCTSTR bitmap, LPCTSTR type, DWORD mask)
{
    TImageInfo* data = NULL;
    if( type != NULL ) {
        if( isdigit(*bitmap) ) {
            LPTSTR pstr = NULL;
            int iIndex = _tcstol(bitmap, &pstr, 10);
			data = LoadImage(iIndex, m_skn.GetBuffer(), type, mask);
        }
    }
    else {
		data = LoadImage(bitmap, m_skn.GetBuffer(), type, mask);
    }

    if( !data ) return NULL;
    if( !m_mImageHash.Insert(bitmap, data) ) {
        ::DeleteObject(data->hBitmap);
        delete data;
    }
    return data;
}

bool CRenderEngine::RemoveImage(LPCTSTR bitmap)
{
    TImageInfo* data = GetImage(bitmap);
    if( !data ) return false;

    ::DeleteObject(data->hBitmap);
    delete data;

    return m_mImageHash.Remove(bitmap);
}

void CRenderEngine::RemoveAllImages()
{
    TImageInfo* data;
    for( int i = 0; i< m_mImageHash.GetSize(); i++ ) {
        if(LPCTSTR key = m_mImageHash.GetAt(i)) {
            data = static_cast<TImageInfo*>(m_mImageHash.Find(key));
            ::DeleteObject(data->hBitmap);
            delete data;
        }
    }

    m_mImageHash.Resize(0);
}


///////////////////////////////////////////
/////////////////// Image UI

TImageInfo* CRenderEngine::LoadImage(STRINGorID bitmap, STRINGorID skn, STRINGorID type, DWORD mask)
{
    LPBYTE pData = NULL;
    DWORD dwSize = 0;
	CComQIPtr<IStorage> pStg;
	CComQIPtr<IStorage> picStg;
	HRESULT hr = NOERROR;
	USES_CONVERSION;
	if(skn.m_lpstr != NULL)
	{
		LPCOLESTR lpwFileName = T2COLE( skn.m_lpstr );	// ת��T����Ϊ���ַ�
		hr = ::StgIsStorageFile( lpwFileName );	// �Ǹ����ļ���
		if(FAILED(hr))
			return NULL;

		hr = ::StgOpenStorage(			// �򿪸����ļ�
			lpwFileName,					// �ļ�����
			NULL,
			STGM_READ | STGM_SHARE_DENY_WRITE,
			0,
			0,
			&pStg);				// �õ����洢�ӿ�ָ��

		if(FAILED(hr))
			return NULL;

		hr = pStg->OpenStorage(L"pic",NULL,STGM_READ | STGM_SHARE_EXCLUSIVE,0,0,&picStg);
		if(FAILED(hr))
		{
			return NULL;
		}
		CComQIPtr<IStream> pStream;
		hr = picStg->OpenStream( T2COLE( bitmap.m_lpstr ),NULL,STGM_READ | STGM_SHARE_EXCLUSIVE,0,&pStream);
		if(FAILED(hr))
		{
			return NULL;
		}
		ULARGE_INTEGER sz;
		LARGE_INTEGER a;
		a.QuadPart = 0;
		hr = pStream->Seek(a, STREAM_SEEK_END, &sz); 
		dwSize = sz.QuadPart;
		pData = new BYTE[dwSize]; 
		pStream->Seek(a , STREAM_SEEK_SET, NULL); 
		pStream->Read(pData , dwSize , NULL); 
	}
    else if( HIWORD(bitmap.m_lpstr) != NULL ) {
        HANDLE hFile = ::CreateFile(bitmap.m_lpstr, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, \
            FILE_ATTRIBUTE_NORMAL, NULL);
        if( hFile == INVALID_HANDLE_VALUE ) return NULL;
        dwSize = ::GetFileSize(hFile, NULL);
        if( dwSize == 0 ) return NULL;

        DWORD dwRead = 0;
        pData = new BYTE[ dwSize ];
        ::ReadFile( hFile, pData, dwSize, &dwRead, NULL );
        ::CloseHandle( hFile );

        if( dwRead != dwSize ) {
            delete[] pData;
            return NULL;
        }
    }
    else {
        HRSRC hResource = ::FindResource(NULL, bitmap.m_lpstr, type.m_lpstr);
        if( hResource == NULL ) return NULL;
        HGLOBAL hGlobal = ::LoadResource(NULL, hResource);
        if( hGlobal == NULL ) {
            FreeResource(hResource);
            return NULL;
        }

        dwSize = ::SizeofResource(NULL, hResource);
        if( dwSize == 0 ) return NULL;
        pData = new BYTE[ dwSize ];
        ::CopyMemory(pData, (LPBYTE)::LockResource(hGlobal), dwSize);
        ::FreeResource(hResource);
    }

    LPBYTE pImage = NULL;
    int x,y,n;
    pImage = stbi_load_from_memory(pData, dwSize, &x, &y, &n, 4);
    delete[] pData;
    if( !pImage ) return NULL;

    BITMAPINFO bmi;
    ZeroMemory(&bmi, sizeof(BITMAPINFO));
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = x;
    bmi.bmiHeader.biHeight = -y;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biSizeImage = x * y * 4;

    bool bAlphaChannel = false;
    LPBYTE pDest = NULL;
    HBITMAP hBitmap = ::CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void**)&pDest, NULL, 0);
    if( !hBitmap ) return NULL;

    for( int i = 0; i < x * y; i++ ) 
    {
        pDest[i*4 + 3] = pImage[i*4 + 3];
        if( pDest[i*4 + 3] < 255 )
        {
            pDest[i*4] = (BYTE)(DWORD(pImage[i*4 + 2])*pImage[i*4 + 3]/255);
            pDest[i*4 + 1] = (BYTE)(DWORD(pImage[i*4 + 1])*pImage[i*4 + 3]/255);
            pDest[i*4 + 2] = (BYTE)(DWORD(pImage[i*4])*pImage[i*4 + 3]/255); 
            bAlphaChannel = true;
        }
        else
        {
            pDest[i*4] = pImage[i*4 + 2];
            pDest[i*4 + 1] = pImage[i*4 + 1];
            pDest[i*4 + 2] = pImage[i*4]; 
        }

        if( *(DWORD*)(&pDest[i*4]) == mask ) {
            pDest[i*4] = (BYTE)0;
            pDest[i*4 + 1] = (BYTE)0;
            pDest[i*4 + 2] = (BYTE)0; 
            pDest[i*4 + 3] = (BYTE)0;
            bAlphaChannel = true;
        }
    }

    TImageInfo* data = new TImageInfo;
    data->hBitmap = hBitmap;
    data->nX = x;
    data->nY = y;
    data->alphaChannel = bAlphaChannel;
    return data;
}

bool CRenderEngine::DrawImageString(HDC hDC, const RECT& rc, const RECT& rcPaint,LPCTSTR pStrImage, LPCTSTR pStrModify)
{	
    // 1��aaa.jpg
    // 2��file='aaa.jpg' res='' restype='0' dest='0,0,0,0' source='0,0,0,0' corner='0,0,0,0' 
    // mask='#FF0000' fade='255' hole='false'
    // �ַ���ʽ������գ������ж���ո��tab��ͼƬ�����Ƿ����alphaͨ����ͼƬ����

	if(_tcscmp(pStrImage,_T(""))==0) return false;
    CString sImageName = pStrImage;
    CString sImageResType;
    RECT rcItem = rc;
    RECT rcBmpPart = {0};
    RECT rcCorner = {0};
    DWORD dwMask = 0;
    BYTE bFade = 0xFF;
    bool bHole = false;

    CString sItem;
    CString sValue;
    LPTSTR pstr = NULL;

    for( int i = 0; i < 2; ++i ) {
        if( i == 1) {
            pStrImage = pStrModify;
        }
        if( !pStrImage ) continue;

        while( *pStrImage != _T('\0') ) {
            sItem.Empty();
            sValue.Empty();
            while( *pStrImage != _T('\0') && *pStrImage != _T('=') ) {
                LPTSTR pstrTemp = ::CharNext(pStrImage);	//�����ַ�������һ���ַ��ĵ�ַ����ָ�룡
                while( pStrImage < pstrTemp) {			//�ַ����Ƚ�
                    sItem += *pStrImage++;
                }
            }
            if( *pStrImage++ != _T('=') ) break;	//�ƶ�����һ����=��
            if( *pStrImage++ != _T('\'') ) break;	//�ƶ����ؼ�������
            while( *pStrImage != _T('\0') && *pStrImage != _T('\'') ) {	//�����ڿո� �� ������
                LPTSTR pstrTemp = ::CharNext(pStrImage);
                while( pStrImage < pstrTemp) {
                    sValue += *pStrImage++;
                }
            }
            if( *pStrImage++ != _T('\'') ) break;		//�����ڽ�����
            if( !sValue.IsEmpty() ) {
                if( sItem == _T("file") || sItem == _T("res") ) {		//��ȡfile�������Ϣ
                    sImageName = sValue;
                }
                else if( sItem == _T("restype") ) {		//����
                    sImageResType = sValue;
                }
                else if( sItem == _T("dest") ) {		//��ȡ
					rcItem.left = rc.left + _tcstol(sValue.GetBuffer(), &pstr, 10);  ASSERT(pstr);		//�Զ���λ����һ����
                    rcItem.top = rc.top + _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr);    
                    rcItem.right = rc.left + _tcstol(pstr + 1, &pstr, 10);  ASSERT(pstr);    
                    rcItem.bottom = rc.top + _tcstol(pstr + 1, &pstr, 10); ASSERT(pstr);  
                }
                else if( sItem == _T("source") ) {
                    rcBmpPart.left = _tcstol(sValue.GetBuffer(), &pstr, 10);  ASSERT(pstr);    
                    rcBmpPart.top = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr);    
                    rcBmpPart.right = _tcstol(pstr + 1, &pstr, 10);  ASSERT(pstr);    
                    rcBmpPart.bottom = _tcstol(pstr + 1, &pstr, 10); ASSERT(pstr);  
                }
                else if( sItem == _T("corner") ) {
                    rcCorner.left = _tcstol(sValue.GetBuffer(), &pstr, 10);  ASSERT(pstr);    
                    rcCorner.top = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr);    
                    rcCorner.right = _tcstol(pstr + 1, &pstr, 10);  ASSERT(pstr);    
                    rcCorner.bottom = _tcstol(pstr + 1, &pstr, 10); ASSERT(pstr);
                }
                else if( sItem == _T("mask") ) {
                    if( sValue[0] == _T('#')) dwMask = _tcstoul(sValue.GetBuffer() + 1, &pstr, 16);
                    else dwMask = _tcstoul(sValue.GetBuffer(), &pstr, 16);
                }
                else if( sItem == _T("fade") ) {
                    bFade = (BYTE)_tcstoul(sValue.GetBuffer(), &pstr, 10);
                }
                else if( sItem == _T("hole") ) {
                    bHole = (_tcscmp(sValue.GetBuffer(), _T("true")) == 0);
                }
            }
            if( *pStrImage++ != _T(' ') ) break;
		}
    }

    TImageInfo* data = NULL;
    if( sImageResType.IsEmpty() ) {
       data = GetImageEx((LPCTSTR)sImageName, NULL, dwMask);
    }
    else {
        data = GetImageEx((LPCTSTR)sImageName, (LPCTSTR)sImageResType, dwMask);
    }


    if( !data ) return false;

    if( hDC == NULL ) return true;

    if( rcBmpPart.left == 0 && rcBmpPart.right == 0 && rcBmpPart.top == 0 && rcBmpPart.bottom == 0 ) {	//���û������source ��ȡԭͼλ��
        rcBmpPart.right = data->nX;
        rcBmpPart.bottom = data->nY;
    }

    RECT rcTemp;				//����Ϊ�� ��ֱ�ӷ���
    if( !::IntersectRect(&rcTemp, &rcItem, &rc) ) return true;		//intersecRect�������Ϊ�գ��򷵻ط���ֵ�����������Ϊ���򷵻�0��
    if( !::IntersectRect(&rcTemp, &rcItem, &rcPaint) ) return true;
    DrawImage(hDC, data->hBitmap, rcItem, rcPaint, rcBmpPart, rcCorner, data->alphaChannel, bFade, bHole);	//��ͼ

    return true;
}

void CRenderEngine::DrawImage(HDC hDC, HBITMAP hBitmap, const RECT& rc, const RECT& rcPaint,
                                    const RECT& rcBmpPart, const RECT& rcCorners, bool alphaChannel, 
                                    BYTE uFade, bool hole)				//��ͼ
{
    ASSERT(::GetObjectType(hDC)==OBJ_DC || ::GetObjectType(hDC)==OBJ_MEMDC); //OBJ_DC:�豸�����Ļ���   OBJ_MEMDC:���豸�����Ļ���

    typedef BOOL (WINAPI *LPALPHABLEND)(HDC, int, int, int, int,HDC, int, int, int, int, BLENDFUNCTION);
    static LPALPHABLEND lpAlphaBlend = (LPALPHABLEND) ::GetProcAddress(::GetModuleHandle(_T("msimg32.dll")), "AlphaBlend");
	//AlphaBlend �ú���������ʾ����ָ��͸���ȵ�ͼ��

   if( lpAlphaBlend == NULL ) lpAlphaBlend = AlphaBitBlt;  //ָ������ָ��
    if( hBitmap == NULL ) return;						//λͼ��������ֱ�ӷ���

    HDC hCloneDC = ::CreateCompatibleDC(hDC);			//�ú�������һ����ָ���豸���ݵ��ڴ��豸�����Ļ�����DC��
    HBITMAP hOldBitmap = (HBITMAP) ::SelectObject(hCloneDC, hBitmap);		//ѡ����
    ::SetStretchBltMode(hDC, COLORONCOLOR);				//�ú�����������ָ���豸�����е�λͼ����ģʽ��

    RECT rcTemp = {0};
    RECT rcDest = {0};
    if( lpAlphaBlend && (alphaChannel || uFade < 255) ) {			//alphaͨ���򽥱�Ч��
        BLENDFUNCTION bf = { AC_SRC_OVER, 0, uFade, AC_SRC_ALPHA };		//���ֽṹ�Ļ�Ͽ���ͨ��ָ��Դ��Ŀ��λͼ�Ļ�Ϲ���
        // middle  �м�
		if( !hole ) {			//hole=falseʱ ִ��
            rcDest.left = rc.left + rcCorners.left;		//��ͼλ�øı� �ı�Ч��
            rcDest.top = rc.top + rcCorners.top;
            rcDest.right = rc.right - rc.left - rcCorners.left - rcCorners.right;
            rcDest.bottom = rc.bottom - rc.top - rcCorners.top - rcCorners.bottom;
            rcDest.right += rcDest.left;
            rcDest.bottom += rcDest.top;
            if( ::IntersectRect(&rcTemp, &rcPaint, &rcDest) ) {		//���ڽ���������ִ��
                rcDest.right -= rcDest.left;
                rcDest.bottom -= rcDest.top;
                lpAlphaBlend(hDC, rcDest.left, rcDest.top, rcDest.right, rcDest.bottom, hCloneDC, \
                    rcBmpPart.left + rcCorners.left, rcBmpPart.top + rcCorners.top, \
                    rcBmpPart.right - rcBmpPart.left - rcCorners.left - rcCorners.right, \
                    rcBmpPart.bottom - rcBmpPart.top - rcCorners.top - rcCorners.bottom, bf);

                //if( rcTemp.left == rcDest.left && rcTemp.right == rcDest.right && \
                //    rcTemp.top == rcDest.top && rcTemp.bottom == rcDest.bottom) {
                //    lpAlphaBlend(hDC, rcTemp.left, rcTemp.top, rcTemp.right - rcTemp.left, \
                //        rcTemp.bottom - rcTemp.top, hCloneDC, rcBmpPart.left + rcCorners.left, \
                //        rcBmpPart.top + rcCorners.top, rcBmpPart.right - rcBmpPart.left - rcCorners.left - \
                //        rcCorners.right, rcBmpPart.bottom - rcBmpPart.top - rcCorners.top - rcCorners.bottom, bf);
                //}
                //else {
                //    float fScaleX = ((float)rcBmpPart.right - rcBmpPart.left - rcCorners.left - \
                //        rcCorners.right) / (rc.right - rc.left - rcCorners.left - rcCorners.right); 
                //    float fScaleY = ((float)rcBmpPart.bottom - rcBmpPart.top - rcCorners.top - \
                //        rcCorners.bottom) / (rc.bottom - rc.top - rcCorners.top - rcCorners.bottom); 
                //    lpAlphaBlend(hDC, rcTemp.left, rcTemp.top, rcTemp.right - rcTemp.left, \
                //        rcTemp.bottom - rcTemp.top, hCloneDC, rcBmpPart.left + rcCorners.left + \
                //        (rcTemp.left - rc.left - rcCorners.left) * fScaleX + 0.5, rcBmpPart.top + rcCorners.top + \
                //        (rcTemp.top - rc.top - rcCorners.top) * fScaleY + 0.5, (rcTemp.right - rcTemp.left) * fScaleX - 0.5, \
                //        (rcTemp.bottom - rcTemp.top) * fScaleY - 0.5, bf);
                //}
            }
        }

        // left-top
        if( rcCorners.left > 0 && rcCorners.top > 0 ) {  //conrner left and top ��Ϣ����
            rcDest.left = rc.left;
            rcDest.top = rc.top;
            rcDest.right = rcCorners.left;
            rcDest.bottom = rcCorners.top;
            rcDest.right += rcDest.left;
            rcDest.bottom += rcDest.top;
            if( ::IntersectRect(&rcTemp, &rcPaint, &rcDest) ) {
                rcDest.right -= rcDest.left;
                rcDest.bottom -= rcDest.top;
                lpAlphaBlend(hDC, rcDest.left, rcDest.top, rcDest.right, rcDest.bottom, hCloneDC, \
                    rcBmpPart.left, rcBmpPart.top, rcCorners.left, rcCorners.top, bf);
            }
        }
        // top
        if( rcCorners.top > 0 ) {  //corner top����
            rcDest.left = rc.left + rcCorners.left;
            rcDest.top = rc.top;
            rcDest.right = rc.right - rc.left - rcCorners.left - rcCorners.right;
            rcDest.bottom = rcCorners.top;
            rcDest.right += rcDest.left;
            rcDest.bottom += rcDest.top;
            if( ::IntersectRect(&rcTemp, &rcPaint, &rcDest) ) {
                rcDest.right -= rcDest.left;
                rcDest.bottom -= rcDest.top;
                lpAlphaBlend(hDC, rcDest.left, rcDest.top, rcDest.right, rcDest.bottom, hCloneDC, \
                    rcBmpPart.left + rcCorners.left, rcBmpPart.top, rcBmpPart.right - rcBmpPart.left - \
                    rcCorners.left - rcCorners.right, rcCorners.top, bf);
            }
        }
        // right-top			//corner right and top ����
        if( rcCorners.right > 0 && rcCorners.top > 0 ) {
            rcDest.left = rc.right - rcCorners.right;
            rcDest.top = rc.top;
            rcDest.right = rcCorners.right;
            rcDest.bottom = rcCorners.top;
            rcDest.right += rcDest.left;
            rcDest.bottom += rcDest.top;
            if( ::IntersectRect(&rcTemp, &rcPaint, &rcDest) ) {
                rcDest.right -= rcDest.left;
                rcDest.bottom -= rcDest.top;
                lpAlphaBlend(hDC, rcDest.left, rcDest.top, rcDest.right, rcDest.bottom, hCloneDC, \
                    rcBmpPart.right - rcCorners.right, rcBmpPart.top, rcCorners.right, rcCorners.top, bf);
            }
        }
        // left			//corner left ����
        if( rcCorners.left > 0 ) {
            rcDest.left = rc.left;
            rcDest.top = rc.top + rcCorners.top;
            rcDest.right = rcCorners.left;
            rcDest.bottom = rc.bottom - rc.top - rcCorners.top - rcCorners.bottom;
            rcDest.right += rcDest.left;
            rcDest.bottom += rcDest.top;
            if( ::IntersectRect(&rcTemp, &rcPaint, &rcDest) ) {
                rcDest.right -= rcDest.left;
                rcDest.bottom -= rcDest.top;
                lpAlphaBlend(hDC, rcDest.left, rcDest.top, rcDest.right, rcDest.bottom, hCloneDC, \
                    rcBmpPart.left, rcBmpPart.top + rcCorners.top, rcCorners.left, rcBmpPart.bottom - \
                    rcBmpPart.top - rcCorners.top - rcCorners.bottom, bf);
            }
        }
        // right			//corner right ����
        if( rcCorners.right > 0 ) {
            rcDest.left = rc.right - rcCorners.right;
            rcDest.top = rc.top + rcCorners.top;
            rcDest.right = rcCorners.right;
            rcDest.bottom = rc.bottom - rc.top - rcCorners.top - rcCorners.bottom;
            rcDest.right += rcDest.left;
            rcDest.bottom += rcDest.top;
            if( ::IntersectRect(&rcTemp, &rcPaint, &rcDest) ) {
                rcDest.right -= rcDest.left;
                rcDest.bottom -= rcDest.top;
                lpAlphaBlend(hDC, rcDest.left, rcDest.top, rcDest.right, rcDest.bottom, hCloneDC, \
                    rcBmpPart.right - rcCorners.right, rcBmpPart.top + rcCorners.top, rcCorners.right, \
                    rcBmpPart.bottom - rcBmpPart.top - rcCorners.top - rcCorners.bottom, bf);
            }
        }
        // left-bottom
        if( rcCorners.left > 0 && rcCorners.bottom > 0 ) {
            rcDest.left = rc.left;
            rcDest.top = rc.bottom - rcCorners.bottom;
            rcDest.right = rcCorners.left;
            rcDest.bottom = rcCorners.bottom;
            rcDest.right += rcDest.left;
            rcDest.bottom += rcDest.top;
            if( ::IntersectRect(&rcTemp, &rcPaint, &rcDest) ) {
                rcDest.right -= rcDest.left;
                rcDest.bottom -= rcDest.top;
                lpAlphaBlend(hDC, rcDest.left, rcDest.top, rcDest.right, rcDest.bottom, hCloneDC, \
                    rcBmpPart.left, rcBmpPart.bottom - rcCorners.bottom, rcCorners.left, rcCorners.bottom, bf);
            }
        }
        // bottom
        if( rcCorners.bottom > 0 ) {
            rcDest.left = rc.left + rcCorners.left;
            rcDest.top = rc.bottom - rcCorners.bottom;
            rcDest.right = rc.right - rc.left - rcCorners.left - rcCorners.right;
            rcDest.bottom = rcCorners.bottom;
            rcDest.right += rcDest.left;
            rcDest.bottom += rcDest.top;
            if( ::IntersectRect(&rcTemp, &rcPaint, &rcDest) ) {
                rcDest.right -= rcDest.left;
                rcDest.bottom -= rcDest.top;
                lpAlphaBlend(hDC, rcDest.left, rcDest.top, rcDest.right, rcDest.bottom, hCloneDC, \
                    rcBmpPart.left + rcCorners.left, rcBmpPart.bottom - rcCorners.bottom, \
                    rcBmpPart.right - rcBmpPart.left - rcCorners.left - rcCorners.right, rcCorners.bottom, bf);
            }
        }
        // right-bottom
        if( rcCorners.right > 0 && rcCorners.bottom > 0 ) {
            rcDest.left = rc.right - rcCorners.right;
            rcDest.top = rc.bottom - rcCorners.bottom;
            rcDest.right = rcCorners.right;
            rcDest.bottom = rcCorners.bottom;
            rcDest.right += rcDest.left;
            rcDest.bottom += rcDest.top;
            if( ::IntersectRect(&rcTemp, &rcPaint, &rcDest) ) {
                rcDest.right -= rcDest.left;
                rcDest.bottom -= rcDest.top;
                lpAlphaBlend(hDC, rcDest.left, rcDest.top, rcDest.right, rcDest.bottom, hCloneDC, \
                    rcBmpPart.right - rcCorners.right, rcBmpPart.bottom - rcCorners.bottom, rcCorners.right, \
                    rcCorners.bottom, bf);
            }
        }
	}
    else 
    {			//û��alphaͨ�� Ч��    bitblt ֱ����ͼ
        if (rc.right - rc.left == rcBmpPart.right - rcBmpPart.left \
            && rc.bottom - rc.top == rcBmpPart.bottom - rcBmpPart.top \
            && rcCorners.left == 0 && rcCorners.right == 0 && rcCorners.top == 0 && rcCorners.bottom == 0)
        {
            if( ::IntersectRect(&rcTemp, &rcPaint, &rc) ) {
                ::BitBlt(hDC, rcTemp.left, rcTemp.top, rcTemp.right - rcTemp.left, rcTemp.bottom - rcTemp.top, \
                    hCloneDC, rcBmpPart.left + rcTemp.left - rc.left, rcBmpPart.top + rcTemp.top - rc.top, SRCCOPY);
            }
        }
        else
        {
            // middle
            if( !hole ) {
                rcDest.left = rc.left + rcCorners.left;
                rcDest.top = rc.top + rcCorners.top;
                rcDest.right = rc.right - rc.left - rcCorners.left - rcCorners.right;
                rcDest.bottom = rc.bottom - rc.top - rcCorners.top - rcCorners.bottom;
                rcDest.right += rcDest.left;
                rcDest.bottom += rcDest.top;
                if( ::IntersectRect(&rcTemp, &rcPaint, &rcDest) ) {
                    rcDest.right -= rcDest.left;
                    rcDest.bottom -= rcDest.top;
                    ::StretchBlt(hDC, rcDest.left, rcDest.top, rcDest.right, rcDest.bottom, hCloneDC, \
                        rcBmpPart.left + rcCorners.left, rcBmpPart.top + rcCorners.top, \
                        rcBmpPart.right - rcBmpPart.left - rcCorners.left - rcCorners.right, \
                        rcBmpPart.bottom - rcBmpPart.top - rcCorners.top - rcCorners.bottom, SRCCOPY);

                    //if( rcTemp.left == rcDest.left && rcTemp.right == rcDest.right && \
                    //    rcTemp.top == rcDest.top && rcTemp.bottom == rcDest.bottom) {
                    //        ::StretchBlt(hDC, rcTemp.left, rcTemp.top, rcTemp.right - rcTemp.left, \
                    //            rcTemp.bottom - rcTemp.top, hCloneDC, rcBmpPart.left + rcCorners.left, \
                    //            rcBmpPart.top + rcCorners.top, rcBmpPart.right - rcBmpPart.left - rcCorners.left - \
                    //            rcCorners.right, rcBmpPart.bottom - rcBmpPart.top - rcCorners.top - rcCorners.bottom, SRCCOPY);
                    //}
                    //else {
                    //    float fScaleX = ((float)rcBmpPart.right - rcBmpPart.left - rcCorners.left - \
                    //        rcCorners.right) / (rc.right - rc.left -rcCorners.left - rcCorners.right); 
                    //    float fScaleY = ((float)rcBmpPart.bottom - rcBmpPart.top - rcCorners.top - \
                    //        rcCorners.bottom) / (rc.bottom - rc.top - rcCorners.top - rcCorners.bottom); 
                    //    ::StretchBlt(hDC, rcTemp.left, rcTemp.top, rcTemp.right - rcTemp.left, \
                    //        rcTemp.bottom - rcTemp.top, hCloneDC, rcBmpPart.left + rcCorners.left + \
                    //        (rcTemp.left - rc.left) * fScaleX - 0.5 / fScaleX, rcBmpPart.top + rcCorners.top + \
                    //        (rcTemp.top - rc.top) * fScaleY - 0.5 / fScaleY, (rcTemp.right - rcTemp.left - rcCorners.left - \
                    //        rcCorners.right) * fScaleX + 1 / fScaleX, (rcTemp.bottom - rcTemp.top - rcCorners.top - \
                    //        rcCorners.bottom) * fScaleY + 1 / fScaleY, SRCCOPY);
                    //}
                }
            }
            
            // left-top
            if( rcCorners.left > 0 && rcCorners.top > 0 ) {
                rcDest.left = rc.left;
                rcDest.top = rc.top;
                rcDest.right = rcCorners.left;
                rcDest.bottom = rcCorners.top;
                rcDest.right += rcDest.left;
                rcDest.bottom += rcDest.top;
                if( ::IntersectRect(&rcTemp, &rcPaint, &rcDest) ) {
                    rcDest.right -= rcDest.left;
                    rcDest.bottom -= rcDest.top;
                    ::StretchBlt(hDC, rcDest.left, rcDest.top, rcDest.right, rcDest.bottom, hCloneDC, \
                        rcBmpPart.left, rcBmpPart.top, rcCorners.left, rcCorners.top, SRCCOPY);
                }
            }
            // top
            if( rcCorners.top > 0 ) {
                rcDest.left = rc.left + rcCorners.left;
                rcDest.top = rc.top;
                rcDest.right = rc.right - rc.left - rcCorners.left - rcCorners.right;
                rcDest.bottom = rcCorners.top;
                rcDest.right += rcDest.left;
                rcDest.bottom += rcDest.top;
                if( ::IntersectRect(&rcTemp, &rcPaint, &rcDest) ) {
                    rcDest.right -= rcDest.left;
                    rcDest.bottom -= rcDest.top;
                    ::StretchBlt(hDC, rcDest.left, rcDest.top, rcDest.right, rcDest.bottom, hCloneDC, \
                        rcBmpPart.left + rcCorners.left, rcBmpPart.top, rcBmpPart.right - rcBmpPart.left - \
                        rcCorners.left - rcCorners.right, rcCorners.top, SRCCOPY);
                }
            }
            // right-top
            if( rcCorners.right > 0 && rcCorners.top > 0 ) {
                rcDest.left = rc.right - rcCorners.right;
                rcDest.top = rc.top;
                rcDest.right = rcCorners.right;
                rcDest.bottom = rcCorners.top;
                rcDest.right += rcDest.left;
                rcDest.bottom += rcDest.top;
                if( ::IntersectRect(&rcTemp, &rcPaint, &rcDest) ) {
                    rcDest.right -= rcDest.left;
                    rcDest.bottom -= rcDest.top;
                    ::StretchBlt(hDC, rcDest.left, rcDest.top, rcDest.right, rcDest.bottom, hCloneDC, \
                        rcBmpPart.right - rcCorners.right, rcBmpPart.top, rcCorners.right, rcCorners.top, SRCCOPY);
                }
            }
            // left
            if( rcCorners.left > 0 ) {
                rcDest.left = rc.left;
                rcDest.top = rc.top + rcCorners.top;
                rcDest.right = rcCorners.left;
                rcDest.bottom = rc.bottom - rc.top - rcCorners.top - rcCorners.bottom;
                rcDest.right += rcDest.left;
                rcDest.bottom += rcDest.top;
                if( ::IntersectRect(&rcTemp, &rcPaint, &rcDest) ) {
                    rcDest.right -= rcDest.left;
                    rcDest.bottom -= rcDest.top;
                    ::StretchBlt(hDC, rcDest.left, rcDest.top, rcDest.right, rcDest.bottom, hCloneDC, \
                        rcBmpPart.left, rcBmpPart.top + rcCorners.top, rcCorners.left, rcBmpPart.bottom - \
                        rcBmpPart.top - rcCorners.top - rcCorners.bottom, SRCCOPY);
                }
            }
            // right
            if( rcCorners.right > 0 ) {
                rcDest.left = rc.right - rcCorners.right;
                rcDest.top = rc.top + rcCorners.top;
                rcDest.right = rcCorners.right;
                rcDest.bottom = rc.bottom - rc.top - rcCorners.top - rcCorners.bottom;
                rcDest.right += rcDest.left;
                rcDest.bottom += rcDest.top;
                if( ::IntersectRect(&rcTemp, &rcPaint, &rcDest) ) {
                    rcDest.right -= rcDest.left;
                    rcDest.bottom -= rcDest.top;
                    ::StretchBlt(hDC, rcDest.left, rcDest.top, rcDest.right, rcDest.bottom, hCloneDC, \
                        rcBmpPart.right - rcCorners.right, rcBmpPart.top + rcCorners.top, rcCorners.right, \
                        rcBmpPart.bottom - rcBmpPart.top - rcCorners.top - rcCorners.bottom, SRCCOPY);
                }
            }
            // left-bottom
            if( rcCorners.left > 0 && rcCorners.bottom > 0 ) {
                rcDest.left = rc.left;
                rcDest.top = rc.bottom - rcCorners.bottom;
                rcDest.right = rcCorners.left;
                rcDest.bottom = rcCorners.bottom;
                rcDest.right += rcDest.left;
                rcDest.bottom += rcDest.top;
                if( ::IntersectRect(&rcTemp, &rcPaint, &rcDest) ) {
                    rcDest.right -= rcDest.left;
                    rcDest.bottom -= rcDest.top;
                    ::StretchBlt(hDC, rcDest.left, rcDest.top, rcDest.right, rcDest.bottom, hCloneDC, \
                        rcBmpPart.left, rcBmpPart.bottom - rcCorners.bottom, rcCorners.left, rcCorners.bottom, SRCCOPY);
                }
            }
            // bottom
            if( rcCorners.bottom > 0 ) {
                rcDest.left = rc.left + rcCorners.left;
                rcDest.top = rc.bottom - rcCorners.bottom;
                rcDest.right = rc.right - rc.left - rcCorners.left - rcCorners.right;
                rcDest.bottom = rcCorners.bottom;
                rcDest.right += rcDest.left;
                rcDest.bottom += rcDest.top;
                if( ::IntersectRect(&rcTemp, &rcPaint, &rcDest) ) {
                    rcDest.right -= rcDest.left;
                    rcDest.bottom -= rcDest.top;
                    ::StretchBlt(hDC, rcDest.left, rcDest.top, rcDest.right, rcDest.bottom, hCloneDC, \
                        rcBmpPart.left + rcCorners.left, rcBmpPart.bottom - rcCorners.bottom, \
                        rcBmpPart.right - rcBmpPart.left - rcCorners.left - rcCorners.right, rcCorners.bottom, SRCCOPY);
                }
            }
            // right-bottom
            if( rcCorners.right > 0 && rcCorners.bottom > 0 ) {
                rcDest.left = rc.right - rcCorners.right;
                rcDest.top = rc.bottom - rcCorners.bottom;
                rcDest.right = rcCorners.right;
                rcDest.bottom = rcCorners.bottom;
                rcDest.right += rcDest.left;
                rcDest.bottom += rcDest.top;
                if( ::IntersectRect(&rcTemp, &rcPaint, &rcDest) ) {
                    rcDest.right -= rcDest.left;
                    rcDest.bottom -= rcDest.top;
                    ::StretchBlt(hDC, rcDest.left, rcDest.top, rcDest.right, rcDest.bottom, hCloneDC, \
                        rcBmpPart.right - rcCorners.right, rcBmpPart.bottom - rcCorners.bottom, rcCorners.right, \
                        rcCorners.bottom, SRCCOPY);
                }
            }
        }
    }
    ::SelectObject(hCloneDC, hOldBitmap);
    ::DeleteDC(hCloneDC);
}
#ifndef STRINGPTRMAP_H
#define STRINGPTRMAP_H
#pragma once

typedef struct tagTFontInfo
{
    HFONT hFont;
    TEXTMETRIC tm;
} TFontInfo;

typedef struct tagTImageInfo
{
    HBITMAP hBitmap;
    int nX;
    int nY;
    bool alphaChannel;
} TImageInfo;

struct TITEM
{
    CString Key;
    LPVOID Data;
    struct TITEM* pNext;
};

class  CStringPtrMap
{
public:
    CStringPtrMap(int nSize = 83);
    ~CStringPtrMap();

    void Resize(int nSize = 83);
    LPVOID Find(LPCTSTR key) const;
    bool Insert(LPCTSTR key, LPVOID pData);
    LPVOID Set(LPCTSTR key, LPVOID pData);
    bool Remove(LPCTSTR key);
    int GetSize() const;
    LPCTSTR GetAt(int iIndex) const;
    LPCTSTR operator[] (int nIndex) const;

protected:
    TITEM** m_aT;
    int m_nBuckets;
};

class STRINGorID
{
public:
    STRINGorID(LPCTSTR lpString) : m_lpstr(lpString)
    { }
    STRINGorID(UINT nID) : m_lpstr(MAKEINTRESOURCE(nID))
    {}
    LPCTSTR m_lpstr;
};



/////////////////////////////////////////////////////////////////////////////
extern "C"
{
    extern unsigned char *stbi_load_from_memory(unsigned char const *buffer, int len, int *x, int *y, \
        int *comp, int req_comp);
};
//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
//
//
static COLORREF PixelAlpha(COLORREF clrSrc, double src_darken, COLORREF clrDest, double dest_darken)
{
    return RGB (GetRValue (clrSrc) * src_darken + GetRValue (clrDest) * dest_darken,		//GetRValue �ú�����ȡһ��RGB��ɫֵ�еĺ�ɫǿ��ֵ��
        GetGValue (clrSrc) * src_darken + GetGValue (clrDest) * dest_darken, 
        GetBValue (clrSrc) * src_darken + GetBValue (clrDest) * dest_darken);

}

static BOOL WINAPI AlphaBitBlt(HDC hDC, int nDestX, int nDestY, int dwWidth, int dwHeight, HDC hSrcDC, \
                        int nSrcX, int nSrcY, int wSrc, int hSrc, BLENDFUNCTION ftn)
{
    HDC hTempDC = ::CreateCompatibleDC(hDC);		//�ú�������һ����ָ���豸���ݵ��ڴ��豸�����Ļ�����DC����
    if (NULL == hTempDC)
        return FALSE;

    //Creates Source DIB  ����Դ��DIB
    LPBITMAPINFO lpbiSrc;  //ָ��bitmap�ṹ��Ϣ��ָ��
    // Fill in the BITMAPINFOHEADER  ���BITMAPINFOHEADER�ṹ
    lpbiSrc = (LPBITMAPINFO) new BYTE[sizeof(BITMAPINFOHEADER)];
    lpbiSrc->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    lpbiSrc->bmiHeader.biWidth = dwWidth;
    lpbiSrc->bmiHeader.biHeight = dwHeight;
    lpbiSrc->bmiHeader.biPlanes = 1;
    lpbiSrc->bmiHeader.biBitCount = 32;
    lpbiSrc->bmiHeader.biCompression = BI_RGB;
    lpbiSrc->bmiHeader.biSizeImage = dwWidth * dwHeight;
    lpbiSrc->bmiHeader.biXPelsPerMeter = 0;
    lpbiSrc->bmiHeader.biYPelsPerMeter = 0;
    lpbiSrc->bmiHeader.biClrUsed = 0;
    lpbiSrc->bmiHeader.biClrImportant = 0;

    COLORREF* pSrcBits = NULL;			//COLORREFֵ������ָ��һ��RGB��ɫ��
    HBITMAP hSrcDib = CreateDIBSection (
        hSrcDC, lpbiSrc, DIB_RGB_COLORS, (void **)&pSrcBits,
        NULL, NULL);
	//CreateDIBSection �ù���Ϊ���ṩ��һ��λͼλֵ��λ�õ�ָ�롣
	//�����ṩһ������һ���ļ�ӳ����󣬸ú�����ʹ����������λͼ�������������ϵͳ������ڴ�λͼ��
	//pSrcBits һ�������������յ���DIBλֵ��λ�õ�ָ���ָ��

    if ((NULL == hSrcDib) || (NULL == pSrcBits)) 
    {
        ::DeleteDC(hTempDC);
        return FALSE;
    }

    HBITMAP hOldTempBmp = (HBITMAP)::SelectObject (hTempDC, hSrcDib);
    ::StretchBlt(hTempDC, 0, 0, dwWidth, dwHeight, hSrcDC, nSrcX, nSrcY, wSrc, hSrc, SRCCOPY);
	//StretchBlt������Դ���ε�λͼ���Ƶ�Ŀ����Σ������ѹ��λͼ������ӦĿ����εĳߴ磬�����Ҫ�ġ�
    ::SelectObject (hTempDC, hOldTempBmp);

    //Creates Destination DIB  ����Ŀ��DIB
    LPBITMAPINFO lpbiDest;
    // Fill in the BITMAPINFOHEADER    //���BITMAPINFOHEADER��Ϣ
    lpbiDest = (LPBITMAPINFO) new BYTE[sizeof(BITMAPINFOHEADER)];
    lpbiDest->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    lpbiDest->bmiHeader.biWidth = dwWidth;
    lpbiDest->bmiHeader.biHeight = dwHeight;
    lpbiDest->bmiHeader.biPlanes = 1;
    lpbiDest->bmiHeader.biBitCount = 32;
    lpbiDest->bmiHeader.biCompression = BI_RGB;
    lpbiDest->bmiHeader.biSizeImage = dwWidth * dwHeight;
    lpbiDest->bmiHeader.biXPelsPerMeter = 0;
    lpbiDest->bmiHeader.biYPelsPerMeter = 0;
    lpbiDest->bmiHeader.biClrUsed = 0;
    lpbiDest->bmiHeader.biClrImportant = 0;

    COLORREF* pDestBits = NULL;
    HBITMAP hDestDib = CreateDIBSection (
        hDC, lpbiDest, DIB_RGB_COLORS, (void **)&pDestBits,
        NULL, NULL);

    if ((NULL == hDestDib) || (NULL == pDestBits))
    {
        delete [] lpbiSrc;
        ::DeleteObject(hSrcDib);
        ::DeleteDC(hTempDC);
        return FALSE;
    }

    ::SelectObject (hTempDC, hDestDib);
    ::BitBlt (hTempDC, 0, 0, dwWidth, dwHeight, hDC, nDestX, nDestY, SRCCOPY);  //��ͼ
    ::SelectObject (hTempDC, hOldTempBmp);

    double src_darken;
    BYTE nAlpha;
					//����PixelAlpha���� RGB��ֵ
    for (int pixel = 0; pixel < dwWidth * dwHeight; pixel++, pSrcBits++, pDestBits++)
    {
        nAlpha = LOBYTE(*pSrcBits >> 24);
        src_darken = (double) (nAlpha * ftn.SourceConstantAlpha) / 255.0 / 255.0;
        if( src_darken < 0.0 ) src_darken = 0.0;
        *pDestBits = PixelAlpha(*pSrcBits, src_darken, *pDestBits, 1.0 - src_darken);
    } //for

    ::SelectObject (hTempDC, hDestDib);
    ::BitBlt (hDC, nDestX, nDestY, dwWidth, dwHeight, hTempDC, 0, 0, SRCCOPY);
    ::SelectObject (hTempDC, hOldTempBmp);

    delete [] lpbiDest;
    ::DeleteObject(hDestDib);

    delete [] lpbiSrc;
    ::DeleteObject(hSrcDib);

    ::DeleteDC(hTempDC);
    return TRUE;
}

#endif
////////////////////////////////////////////////////////////////////////////////////////////////////
//
//

#include "Texture.h"
#include "../Core/PathManager.h"
#include "ResourcesManager.h"

CTexture::CTexture() :
	m_hMemDC(NULL),
	m_bColorKeyEnable(false),
	m_ColorKey(RGB(255, 0, 255))
{
}


CTexture::~CTexture()
{
	// ������ �����Ǿ� �ִ� ������ �ٽ� �������ش�.
	SelectObject(m_hMemDC, m_hOldBitmap);

	// Bitmap�� �����ش�.
	DeleteObject(m_hBitmap);

	// DC�� �����ش�.
	DeleteDC(m_hMemDC);
}

void CTexture::SetColorKey(unsigned char r, unsigned char g, unsigned char b)
{
	m_ColorKey = RGB(r, g, b);
	m_bColorKeyEnable = true;
}

void CTexture::SetColorKey(COLORREF colorKey)
{
	m_ColorKey = colorKey;
	m_bColorKeyEnable = true;
}

bool CTexture::LoadTexture(HINSTANCE hInst, HDC hDC, const string & strKey, const wchar_t * pFileName, const string & strPathKey)
{
	m_strFileName = pFileName;
	m_strKey = strKey;
	m_strPathKey = strPathKey;

	// �޸� DC�� ������ش�.
	m_hMemDC = CreateCompatibleDC(hDC);

	// ��ü ��θ� ������ش�.
	const wchar_t* pPath = GET_SINGLE(CPathManager)->FindPath(strPathKey);

	wstring strPath;

	if (pPath)
		strPath = pPath;

	strPath += pFileName;

	m_hBitmap = (HBITMAP)LoadImage(hInst, strPath.c_str(),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE); // 0, 0 ���� ������ �� �̹��� ���� ũ�⿡ �����ش�.

	// ������ ������� ��Ʈ�� ������ DC�� �����Ѵ�.
	// ������ �� ��ȯ�Ǵ� ���� DC�� �⺻���� �����Ǿ� �ִ�
	// ������ ��ȯ�ȴ�.
	m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

	GetObject(m_hBitmap, sizeof(m_tInfo), &m_tInfo);
	
	return true;
}

void CTexture::SaveFromPath(const char * pFileName, const string & strPayhKey)
{
}

void CTexture::Save(FILE * pFile)
{
	int iLength = m_strKey.length();

	// Key�� ���� ����
	fwrite(&iLength, 4, 1, pFile);
	fwrite(m_strKey.c_str(), 1, iLength, pFile);

	// FileName ����
	iLength = m_strFileName.length();
	fwrite(&iLength, 4, 1, pFile);
	fwrite(m_strFileName.c_str(), 2, iLength, pFile);

	// PathKey ����
	iLength = m_strPathKey.length();
	fwrite(&iLength, 4, 1, pFile);
	fwrite(m_strPathKey.c_str(), 1, iLength, pFile);

	// ColorKey
	fwrite(&m_bColorKeyEnable, 1, 1, pFile);
	fwrite(&m_ColorKey, sizeof(COLORREF), 1, pFile);
}

void CTexture::LoadFromPath(const char * pFileName, const string & strPayhKey)
{

}

void CTexture::Load(FILE * pFile)
{
	
}
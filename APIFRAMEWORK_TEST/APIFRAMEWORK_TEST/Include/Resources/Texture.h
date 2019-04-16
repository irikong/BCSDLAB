#pragma once

#include "..\Ref.h"

class CTexture :
	public CRef
{
private:
	friend class CResourcesManager;

	CTexture();
	~CTexture();

	HDC			m_hMemDC;
	HBITMAP		m_hBitmap;
	HBITMAP		m_hOldBitmap;
	BITMAP		m_tInfo;
	COLORREF	m_ColorKey;
	bool		m_bColorKeyEnable;
	wstring		m_strFileName;
	string		m_strKey;
	string		m_strPathKey;

public:
	void SetColorKey(unsigned char r, unsigned char g, unsigned char b);
	void SetColorKey(COLORREF colorKey);
	COLORREF GetColorKey() const { return m_ColorKey; }

	bool GetColorKeyEnable() const { return m_bColorKeyEnable; }
	long GetWidth() const { return m_tInfo.bmWidth; }
	long GetHeight() const { return m_tInfo.bmHeight; }

	bool LoadTexture(HINSTANCE hInst, HDC hDC, const string& strKey, const wchar_t* pFileName, const string& strPathKey = TEXTURE_PATH);
	HDC GetDC() const { return m_hMemDC; }

	void SaveFromPath(const char* pFileName, const string& strPayhKey = DATA_PATH);
	void Save(FILE* pFile);
	void LoadFromPath(const char* pFileName, const string& strPayhKey = DATA_PATH);
	void Load(FILE* pFile);
};
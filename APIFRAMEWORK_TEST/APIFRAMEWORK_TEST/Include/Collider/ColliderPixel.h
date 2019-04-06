#pragma once
#include "Collider.h"

typedef struct _tagPixel {
	unsigned char r;
	unsigned char g;
	unsigned char b;
}PIXEL, *PPIXEL;

class CColliderPixel :
	public CCollider
{
private:
	vector<PIXEL>	m_vecPixel;
	int		m_iWidth;
	int		m_iHeight;

protected:
	friend class CObj;

	CColliderPixel();
	CColliderPixel(const CColliderPixel& coll);
	~CColliderPixel();

public:
	bool SetPixelInfo(char* pFileName, const string& strPathKey = TEXTURE_PATH);
	//const vector<PIXEL>& GetPixel() const { return m_vecPixel; }
	//int GetWidth() const { return m_iWidth; }
	//int GetHeight() const { return m_iHeight; }

	virtual bool	Init();
	virtual void	Input(float fDeltaTime);
	virtual int		Update(float fDeltaTime);
	virtual int		LateUpdate(float fDeltaTime);
	virtual bool	Collision(CCollider* pDest);
	virtual void	Render(HDC hDC, float fDeltaTime);
	virtual CColliderPixel*	Clone();
};
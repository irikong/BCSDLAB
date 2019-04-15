#pragma once
#include "StaticObj.h"
class CTile :
	public CStaticObj
{
private:
	friend class CObj;
	friend class CStage;

	CTile();
	CTile(const CTile& tile);
	~CTile();

	TILE_OPTION m_eOption;
	class CTexture* m_pOptionTex;

public:
	virtual bool	Init();
	virtual void	Input(float fDeltaTime);
	virtual int		Update(float fDeltaTime);
	virtual int		LateUpdate(float fDeltaTime);
	virtual void	Collision(float fDeltaTime);
	virtual void	Render(HDC hDC, float fDeltaTime);
	virtual CTile*	Clone();

	void SetTileOption(TILE_OPTION eOption);
	TILE_OPTION GetTileOption()const { return m_eOption; }


};
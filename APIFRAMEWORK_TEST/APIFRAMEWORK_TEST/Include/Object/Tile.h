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

public:
	virtual bool	Init();
	virtual void	Input(float fDeltaTime);
	virtual int		Update(float fDeltaTime);
	virtual int		LateUpdate(float fDeltaTime);
	virtual void	Collision(float fDeltaTime);
	virtual void	Render(HDC hDC, float fDeltaTime);
	virtual CTile*	Clone();
};
#pragma once
#include "StaticObj.h"
class CStage :
	public CStaticObj
{
private:
	friend class CObj;
	friend class CScene;

	CStage();
	CStage(const CStage& stage);
	~CStage();

	vector<class CTile*> m_vecTile;

public:
	virtual bool	Init();
	virtual void	Input(float fDeltaTime);
	virtual int		Update(float fDeltaTime);
	virtual int		LateUpdate(float fDeltaTime);
	virtual void	Collision(float fDeltaTime);
	virtual void	Render(HDC hDC, float fDeltaTime);
	virtual CStage*	Clone();
};
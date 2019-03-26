#pragma once

#include "..\Game.h"

class Obj
{
protected:
	Obj();
	virtual ~Obj();

protected:
	POSITION m_tPos;
	_SIZE m_tSize;
};


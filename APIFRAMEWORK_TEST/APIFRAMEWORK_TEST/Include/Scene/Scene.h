#pragma once

#include "..\Game.h"

class Scene
{
protected:
	friend class SceneManager;
protected:
	Scene();
	virtual ~Scene() = 0;

public:
	virtual bool Init();
};


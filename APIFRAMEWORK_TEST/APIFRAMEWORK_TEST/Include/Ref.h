#pragma once

#include "Game.h"

class CRef
{
public:
	CRef();
	virtual ~CRef() = 0;

protected:
	int m_iRef;

public:
	void AddRef() {
		++m_iRef;
	}

	int Release() {
		--m_iRef;

		if (!m_iRef) {
			delete this;
			return 0;
		}

		return m_iRef;
	}
};


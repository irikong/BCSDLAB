#pragma once

#include "Game.h"

class CRef
{
public:
	CRef();
	virtual ~CRef() = 0;

protected:
	int m_iRef;
	bool m_bEnable; // ��ü ��Ȱ�� Ȱ��
	bool m_bLife; // �׾����� �������

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

	void SetEnable(bool bEnable) {
		m_bEnable = bEnable;
	}

	void Die() {
		m_bLife = false;
	}

	bool GetEnable() const {
		return m_bEnable;
	}

	bool GetLife() const {
		return m_bLife;
	}
};


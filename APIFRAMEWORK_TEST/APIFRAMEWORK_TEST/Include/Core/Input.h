#pragma once

#include "../Game.h"

typedef struct _tagKeyInfo
{
	vector<DWORD>	vecKey;
	string		strName;
	bool		bDown;
	bool		bPress;
	bool		bUp;

	_tagKeyInfo() :
		bDown(false), bPress(false), bUp(false) {}
}KEYINFO, *pKEYINFO;

class CInput
{
private:
	unordered_map<string, pKEYINFO>	m_mapKey;
	pKEYINFO	m_pCreateKey;
	HWND		m_hWnd;

	POINT			m_tMousePos;
	POINT			m_tMouseMove;
	class CMouse*	m_pMouse;

	pKEYINFO FindKey(const string& strKey) const;

public:
	bool Init(HWND hWnd);
	void Update(float fDeltaTime);
	bool KeyDown(const string& strKey) const;
	bool KeyPress(const string& strKey) const;
	bool KeyUp(const string& strKey) const;

	class CMouse* GetMouse() const { return m_pMouse; }

	// 재귀적으로 입력을 처리하는 함수 AddKey
	// AddKey의 Base function
	template <typename T>
	bool AddKey(const T& data)
	{
		const char* pTType = typeid(T).name();

		if (strcmp(pTType, "char") == 0 || strcmp(pTType, "int") == 0)
		{
			m_pCreateKey->vecKey.push_back((DWORD)data);
		}

		else
		{
			m_pCreateKey->strName = data;
			m_mapKey.insert(make_pair(m_pCreateKey->strName, m_pCreateKey));
		}
		return true;
	}

	// AddKey의 General function
	template <typename T, typename ... Types> // ... 은 variable template 문법
	bool AddKey(const T& data, const Types& ...arg)
	{
		if (!m_pCreateKey)
			m_pCreateKey = new KEYINFO;

		const char* pTType = typeid(T).name();

		if (strcmp(pTType, "char") == 0 || strcmp(pTType, "int") == 0)
		{
			m_pCreateKey->vecKey.push_back((DWORD)data);
		}

		else
		{
			m_pCreateKey->strName = data;
			m_mapKey.insert(make_pair(m_pCreateKey->strName, m_pCreateKey));
		}

		AddKey(arg...);

		if (m_pCreateKey)
			m_pCreateKey = NULL;

		return true;
	}

	DECLARE_SINGLE(CInput)
};


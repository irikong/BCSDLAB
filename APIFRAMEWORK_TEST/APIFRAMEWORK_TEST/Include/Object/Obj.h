#pragma once

#include "../Ref.h"
#include "../Scene/Layer.h"
#include "../Collider/Collider.h"
#include "../Collider/ColliderRect.h"

class CObj :
	public CRef
{
protected:
	friend class CScene;

protected:
	CObj();
	CObj(const CObj& obj);
	virtual ~CObj();

private:
	static list<CObj*> m_ObjList;

public:
	static void AddObj(CObj* pObj);
	static CObj* FindObject(const string& strTag);
	static void EraseObj(CObj* pObj);
	static void EraseObj(const string& strTag);
	static void EraseObj();


protected:
	class CScene* m_pScene;
	class CLayer* m_pLayer;

public:
	void SetScene(class CScene* pScene) { m_pScene = pScene; }

	void SetLayer(class CLayer* pLayer) { m_pLayer = pLayer; }

	class CScene* GetScene() const { return m_pScene; }

	class CLayer* GetLayer() const { return m_pLayer; }

protected:
	string m_strTag;
	POSITION m_tPos;
	_SIZE m_tSize;
	POSITION m_tPivot;
	class CTexture* m_pTexture;
	list<class CCollider*> m_ColliderList;

public:
	float GetLeft() const { return m_tPos.x - m_tSize.x * m_tPivot.x; }
	float GetRight() const { return GetLeft() + m_tSize.x; }
	float GetTop() const { return m_tPos.y - m_tSize.y * m_tPivot.y; }
	float GetBottom() const { return GetTop() + m_tSize.y; }
	POSITION GetCenter() const { return POSITION(GetLeft() + m_tSize.x / 2.f, GetTop() + m_tSize.y / 2.f); }

	string GetTag() const {
		return m_strTag;
	}

	POSITION GetPos() const {
		return m_tPos;
	}

	_SIZE GetSize() const {
		return m_tSize;
	}

	POSITION GetPivot() const { return m_tPivot; }


public:
	void SetTag(const string& strTag) {
		m_strTag = strTag;
	}

	void SetPos(const POSITION& tPos) {
		m_tPos = tPos;
	}

	void SetPos(const POINT& tPos) {
		m_tPos = tPos;
	}

	void SetPos(float x, float y) {
		m_tPos.x = x;
		m_tPos.y = y;
	}

	void SetSize(const _SIZE& tSize) {
		m_tSize = tSize;
	}

	void SetSize(float x, float y) {
		m_tSize.x = x;
		m_tSize.y = y;
	}

	void SetPivot(const _SIZE& tPivot)
	{
		m_tPivot = tPivot;
	}

	void SetPivot(float x, float y)
	{
		m_tPivot.x = x;
		m_tPivot.y = y;
	}

	void SetTexture(class CTexture* pTexture);
	void SetTexture(const string& strKey,
		const wchar_t* pFileName = NULL,
		const string& strPathKey = TEXTURE_PATH);

	virtual bool Init() = 0;
	virtual void Input(float fDeltaTime);
	virtual int	Update(float fDeltaTime);
	virtual int	LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CObj* Clone() = 0;

	template <typename T>
	static T* CreateObj(const string& strTag, class CLayer* pLayer = NULL)
	{
		T* pObj = new T;

		pObj->SetTag(strTag);

		if (!pObj->Init())
		{
			SAFE_RELEASE(pObj);
			return NULL;
		}

		if (pLayer)
		{
			pLayer->AddObject(pObj);
		}

		AddObj(pObj);

		return pObj;
	}

	public:	const list <CCollider*>* GetColliderList() const { return &m_ColliderList; }
			CCollider* GetCollider(const string& strTag);

	template <typename T>
	T* AddCollider(const string& strTag)
	{
		T* pCollider = new T;

		pCollider->SetObj(this);
		pCollider->SetTag(strTag);

		if (!pCollider->Init())
		{
			SAFE_RELEASE(pCollider);
			return NULL;
		}

		pCollider->AddRef();
		m_ColliderList.push_back(pCollider);

		return pCollider;
	}

	bool CheckCollider() { return !m_ColliderList.empty(); }

	static CObj* CreateCloneObj(const string& strPrototypeKey,
		const string& strTag, class CLayer* pLayer = NULL);
};
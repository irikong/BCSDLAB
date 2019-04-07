#pragma once
#include "../Ref.h"
class CAnimation :
	public CRef
{
private:
	friend class CObj;

	unordered_map<string, pANIMATIONCLIP>	m_mapClip;
	pANIMATIONCLIP	m_pCurClip;
	string			m_strCurClip;
	string			m_strDefaultClip;
	class CObj*		m_pObj;
	bool			m_bMotionEnd;

	CAnimation();
	CAnimation(const CAnimation& anim);
	~CAnimation();

	pANIMATIONCLIP FindClip(const string& strName);

public:
	void SetObj(class CObj* pObj) { m_pObj = pObj; }
	void SetCurrentClip(const string& strCurClip);
	void SetDefaultClip(const string& strDefaultClip);
	void ChangeClip(const string& strClip);

	// Atlas �������� �߰�
	bool AddClip(const string& strName, ANIMATION_TYPE eType,
		ANIMATION_OPTION eOption, float fAnimationLimitTime,
		int iFrameMaxX, int iFrameMaxY, int iStartX, int iStartY,
		int iLengthX, int iLengthY, float fOptionLimitTime,
		const string& strTexKey, const wchar_t* pFileName,
		const string& strPathKey = TEXTURE_PATH);

	bool Init();
	void Update(float fTime);
	CAnimation* Clone();
};
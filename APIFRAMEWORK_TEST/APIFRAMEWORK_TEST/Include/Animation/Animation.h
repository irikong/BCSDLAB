#pragma once
#include "../Ref.h"
class CAnimation :
	public CRef
{
private:
	friend class CObj;

	unordered_map<string, pANIMATIONCLIP>	m_mapClip;

	CAnimation();
	CAnimation(const CAnimation& anim);
	~CAnimation();

public:
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
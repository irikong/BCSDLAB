#pragma once

#include "Flag.h"

typedef struct _tagResolution {
	unsigned int iW;
	unsigned int iH;

	_tagResolution() : iW(0), iH(0) {}
	_tagResolution(int x, int y) : iW(x), iH(y) {}

}RESOLUTION, *PRESOLUTION;

typedef struct _tagPosition {
	float x, y;

	_tagPosition() :
		x(0.f), y(0.f)
	{

	}

	_tagPosition(float _x, float _y) :
		x(_x), y(_y)
	{

	}

	_tagPosition(const _tagPosition& pos)
	{
		x = (float)pos.x;
		y = (float)pos.y;
	}

	_tagPosition(const POINT& pt) {
		x = (float)pt.x;
		y = (float)pt.y;
	}

	void operator = (const _tagPosition& pos) {
		x = (float)pos.x;
		y = (float)pos.y;
	}

	void operator = (const POINT& pt) {
		x = (float)pt.x;
		y = (float)pt.y;
	}

	void operator = (float f[2]) {
		x = f[0];
		y = f[1];
	}

	// operator +

	_tagPosition operator + (const _tagPosition& pos) const {
		_tagPosition tPos;
		tPos.x = x + pos.x;
		tPos.y = y + pos.y;
		return tPos;
	}

	_tagPosition operator + (const POINT& pos) const {
		_tagPosition tPos;
		tPos.x = x + pos.x;
		tPos.y = y + pos.y;
		return tPos;
	}

	_tagPosition operator + (float f[2]) const {
		_tagPosition tPos;
		tPos.x = x + f[0];
		tPos.y = y + f[1];
		return tPos;
	}

	_tagPosition operator + (float f) const {
		_tagPosition tPos;
		tPos.x = x + f;
		tPos.y = y + f;
		return tPos;
	}

	void operator += (const _tagPosition& pos) {
		x += pos.x;
		y += pos.y;
	}

	// operator -

	_tagPosition operator - (const _tagPosition& pos) const {
		_tagPosition tPos;
		tPos.x = x - pos.x;
		tPos.y = y - pos.y;
		return tPos;
	}

	_tagPosition operator - (const POINT& pos) const {
		_tagPosition tPos;
		tPos.x = x - pos.x;
		tPos.y = y - pos.y;
		return tPos;
	}

	_tagPosition operator - (float f[2]) const {
		_tagPosition tPos;
		tPos.x = x - f[0];
		tPos.y = y - f[1];
		return tPos;
	}

	_tagPosition operator - (float f) const {
		_tagPosition tPos;
		tPos.x = x - f;
		tPos.y = y - f;
		return tPos;
	}

	void operator -= (const _tagPosition& pos) {
		x -= pos.x;
		y -= pos.y;
	}

	// operator *

	_tagPosition operator * (const _tagPosition& pos) const {
		_tagPosition tPos;
		tPos.x = x * pos.x;
		tPos.y = y * pos.y;
		return tPos;
	}

	_tagPosition operator * (const POINT& pos) const {
		_tagPosition tPos;
		tPos.x = x * pos.x;
		tPos.y = y * pos.y;
		return tPos;
	}

	_tagPosition operator * (float f[2]) const {
		_tagPosition tPos;
		tPos.x = x * f[0];
		tPos.y = y * f[1];
		return tPos;
	}

	_tagPosition operator * (float f) const {
		_tagPosition tPos;
		tPos.x = x * f;
		tPos.y = y * f;
		return tPos;
	}

	// operator /

	_tagPosition operator / (const _tagPosition& pos) const {
		_tagPosition tPos;
		tPos.x = x / pos.x;
		tPos.y = y / pos.y;
		return tPos;
	}

	_tagPosition operator / (const POINT& pos) const {
		_tagPosition tPos;
		tPos.x = x / pos.x;
		tPos.y = y / pos.y;
		return tPos;
	}

	_tagPosition operator / (float f[2]) const {
		_tagPosition tPos;
		tPos.x = x / f[0];
		tPos.y = y / f[1];
		return tPos;
	}

	_tagPosition operator / (float f) const {
		_tagPosition tPos;
		tPos.x = x / f;
		tPos.y = y / f;
		return tPos;
	}
}POSITION, *PPOSITION, _SIZE, *_PSIZE;

typedef struct _tagRectangle
{
	float	l;
	float	t;
	float	r;
	float	b;

	_tagRectangle() :
		l(0.f), t(0.f), r(0.f), b(0.f) { }
}RECTANGLE, *pRECTANGLE;

typedef struct _tagSphere
{
	POSITION	tCenter;
	float		fRadius;

	_tagSphere() :
		tCenter(0.f, 0.f), fRadius(0.f) { }
}SPHERE, *pSPHERE;

typedef struct _tagPixel {
	unsigned char r;
	unsigned char g;
	unsigned char b;
}PIXEL, *pPIXEL;

typedef struct _tagAnimationClip // 局聪皋捞记 府家胶 包府侩 备炼眉
{
	vector<class CTexture*>	vecTexture;
	ANIMATION_TYPE		eType;
	ANIMATION_OPTION	eOption;
	float		fAnimationTime;
	float		fAnimationLimitTime;
	float		fOptionTime;
	float		fOptionLimitTime;
	float		fAnimationFrameTime;
	int			iFrameX;
	int			iFrameY;
	int			iFrameMaxX;
	int			iFrameMaxY;
	int			iStartX;
	int			iStartY;
	int			iLengthX;
	int			iLengthY;
	_SIZE		tFrameSize;
}ANIMATIONCLIP, *pANIMATIONCLIP;
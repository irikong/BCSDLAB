#pragma once

// Scene Type
enum SCENE_CREATE {
	SC_CURRENT,
	SC_NEXT,
	SC_END
};

// Direction
enum MOVE_DIR {
	MD_BACK = -1,
	MD_NONE,
	MD_FRONT
};

// Collider Type
enum COLLLIDER_TYPE
{
	CT_RECT,
	CT_SPHERE,
	CT_LINE,
	CT_POINT,
	CT_PIXEL,
	CT_END
};

// Collision State
enum COLLISION_STATE
{
	CS_ENTER,
	CS_STAY,
	CS_LEAVE,
	CS_END
};

// Animation Type
enum ANIMATION_TYPE
{
	AT_ATLAS,
	AT_FRAME,
	AT_END
};

// Animation Option
enum ANIMATION_OPTION
{
	AO_LOOP, // 반복
	AO_ONCE_RETURN, // 모션 후 다시 디폴트로 돌아감
	AO_ONCE_DESTROY, // 모션 후 삭제
	AO_TIME_RETURN, // 일정 시간 후 디폴트로 돌아감 
	AO_TIME_DESTROY // 일정 시간 후 삭제
};

enum SCENE_CHANGE
{
	SC_NONE,
	SC_CHANGE
};
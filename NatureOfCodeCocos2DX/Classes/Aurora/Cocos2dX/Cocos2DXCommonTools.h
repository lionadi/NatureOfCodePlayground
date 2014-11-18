#ifndef NatureOfCodeCocos2DX_Cocos2DXCommonTools_h
#define NatureOfCodeCocos2DX_Cocos2DXCommonTools_h

#include "../Math/MathOperations.h"
#include "cocos2d.h"

using namespace Aurora::Math;
using namespace cocos2d;

namespace Aurora {
	namespace Cocos2DX {

			mRECT ConvertSizeTo_mRect(const Size &size);
			VECTOR2D ConvertVec2Tp_VECTOR2D(const cocos2d::Vec2 &vec2);
			cocos2d::Vec2 ConvertVECTOR2DTp_Vec2(const VECTOR2D &value);


	};
};

#endif
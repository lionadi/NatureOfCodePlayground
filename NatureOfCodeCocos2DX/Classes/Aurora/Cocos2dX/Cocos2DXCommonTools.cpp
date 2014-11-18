#include "Cocos2DXCommonTools.h"

namespace Aurora {
	namespace Cocos2DX {
		

		Aurora::Math::mRECT ConvertSizeTo_mRect(const Size &size)
		{
			return(mRECT(size.width, size.height));
		}

		Aurora::Math::VECTOR2D ConvertVec2Tp_VECTOR2D(const cocos2d::Vec2 &vec2)
		{
			return(VECTOR2D(vec2.x, vec2.y));
		}

		cocos2d::Vec2 ConvertVECTOR2DTp_Vec2(const VECTOR2D &value)
		{
			return(cocos2d::Vec2(value.X, value.Y));
		}

	};
};
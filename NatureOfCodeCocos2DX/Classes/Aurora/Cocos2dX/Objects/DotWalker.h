#ifndef NatureOfCodeCocos2DX_DotWalker_h
#define NatureOfCodeCocos2DX_DotWalker_h

#include "../../Random/RandomOperations.h"
#include "../Cocos2DXCommonTools.h"

using namespace Aurora::Random;

namespace Aurora
{
	namespace Cocos2DX
	{
		class DotWalker : virtual public DrawNode, PWalker
		{
		private:
			Size viewSize;
			Color3B mainColor;
			int colorCount;
			int colorCountLimit;
			Vec2 TargetForWalker;
			void RenderWalkerByPosition(const VECTOR2D &position);
			void CalculateColor();
		public:
			DotWalker();
			DotWalker(const Size &viewSize);
			DotWalker(const Size &viewSize, const Vec2 &position);
			DotWalker(const Vec2 &position);
			~DotWalker();

			

			void SetWalkerTarget(const Vec2 &target);

			void StepWalker();

			void Render();

		};

	};
};

#endif
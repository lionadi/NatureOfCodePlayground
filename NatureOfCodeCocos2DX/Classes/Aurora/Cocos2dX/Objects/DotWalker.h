#ifndef NatureOfCodeCocos2DX_DotWalker_h
#define NatureOfCodeCocos2DX_DotWalker_h

#include "../../Random/RandomOperations.h"
#include "../Cocos2DXCommonTools.h"

using namespace Aurora::Random;

namespace Aurora
{
	namespace Cocos2DX
	{
		class DotWalker : public IWalker, public Walker
		{
		private:
			Size viewSize;
			cocos2d::Color4F mainColor;
			int colorCount;
			int colorCountLimit;
			Vec2 TargetForWalker;
			void RenderWalkerByPosition(const VECTOR2D &position);
			void CalculateColor();
			DrawNode *dotWalkerDrawNode;
		public:
			DotWalker();
			DotWalker(const Size &viewSize);
			DotWalker(const Size &viewSize, const Vec2 &position);
			DotWalker(const Vec2 &position);
			~DotWalker();

			
			DrawNode * GetWalkerDrawNode();
			void SetWalkerDrawNodeStartPosition(const Vec2& startPosition);

			void SetWalkerTarget(const Vec2 &target);

			void StepWalker() final;

			void Render() final;

			void init() final;

			void init(const Size &areaSize);

			void init(const IWalker &value);

		};

	};
};

#endif
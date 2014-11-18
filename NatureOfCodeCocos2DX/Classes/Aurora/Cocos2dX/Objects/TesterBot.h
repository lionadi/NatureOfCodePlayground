#ifndef NatureOfCodeCocos2DX_TestBot_h
#define NatureOfCodeCocos2DX_TestBot_h

#include "../../Random/RandomOperations.h"
#include "../Cocos2DXCommonTools.h"

using namespace Aurora::Random;

namespace Aurora
{
	namespace Cocos2DX
	{
		class TestBot : public IMover, public Mover
		{
		private:
			Size viewSize;
			cocos2d::Color4F mainColor;
			int colorCount;
			int colorCountLimit;
			Vec2 TargetForWalker;
			cocos2d::DrawNode *dotMoverDrawNode;
		public:
			TestBot();
			TestBot(const Size &viewSize);
			TestBot(const Size &viewSize, const Vec2 &position, const Vec2 &velocity, const Vec2 &acceleration);
			~TestBot();


			DrawNode * GetMoverDrawNode();
			void SetMoverDrawNodeStartPosition(const Vec2& startPosition);


			void Render() final;

			void init() final;

			void init(const Size &areaSize);

			void init(const IWalker &value);

			void MoveMover() final;

		};

	};
};

#endif
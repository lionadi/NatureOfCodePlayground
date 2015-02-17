#ifndef NatureOfCodeCocos2DX_TestBot_h
#define NatureOfCodeCocos2DX_TestBot_h

#include "../../Random/RandomOperations.h"
#include "../Cocos2DXCommonTools.h"
#include "../../Physics/PhysicsOperations.h"

using namespace Aurora::Random;
using namespace Aurora::Physics;


namespace Aurora
{
	namespace Cocos2DX
	{
		class TestBot : public IMoverImplementor, private Mover, private IPhysicsForceRepresentationBase
		{
		private:
			Size viewSize;
			cocos2d::Color4F mainColor;
			int colorCount;
			int colorCountLimit;
			cocos2d::DrawNode *dotMoverDrawNode;
			Vec2 moverDrawNodeTarget;
			void init() final;

			void init(const Size &viewSize, const Vec2 &position, const Vec2 &velocity, const Vec2 &acceleration, const float &mass);

			void init(const IMoverImplementor &value);
		public:
			TestBot();
			TestBot(const Size &viewSize);
			TestBot(const Size &viewSize, const Vec2 &position, const Vec2 &velocity, const Vec2 &acceleration, const float &mass);
			TestBot(const Size &viewSize, const Vec2 &position, const Vec2 &velocity, const Vec2 &acceleration, const cocos2d::Color4F &color);
			virtual ~TestBot();


			DrawNode * GetMoverDrawNode();
			void SetMoverDrawNodeStartPosition(const Vec2& startPosition);


			void Render() final;

			

			void MoveMover() final;

			void SetMoverTarget(const Vec2 &target);

			std::shared_ptr<Aurora::Physics::Force> AccessObjectPhysics() const final;

			

			//void SetColor(const cocos2d::Color4F &value);

			//void SetMoverTarget(const VECTOR2D &target) override {};

		};
		namespace AliasDeclarations
		{
			using VectorTestBots = std::vector < std::shared_ptr<Aurora::Cocos2DX::TestBot> > ;
		};

	};
};

#endif
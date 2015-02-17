#ifndef NatureOfCodeCocos2DX_DotWalker_h
#define NatureOfCodeCocos2DX_DotWalker_h

#include "../../Random/RandomOperations.h"
#include "../Cocos2DXCommonTools.h"
#include "../../Physics/PhysicsOperations.h"

using namespace Aurora::Random;
using namespace Aurora::Physics;

namespace Aurora
{
	namespace Cocos2DX
	{
		class DotWalker : public IWalkerImplementor, private Walker, private IPhysicsForceRepresentationBase
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
			void init() final;

			void init(const Size &areaSize);

			void init(const IWalkerImplementor &value);
		public:
			DotWalker();
			DotWalker(const Size &viewSize);
			DotWalker(const Size &viewSize, const Vec2 &position);
			DotWalker(const Vec2 &position);
			virtual ~DotWalker();

			
			DrawNode * GetWalkerDrawNode();
			void SetWalkerDrawNodeStartPosition(const Vec2& startPosition);

			void SetWalkerTarget(const Vec2 &target);

			void StepWalker() final;

			void Render() final;

			void SetWalkerRandomNumberMode(RandomNumberMode randomNumberMode) final;

			std::shared_ptr<Physics::Force> AccessObjectPhysics() const final;


		};

	};
};

#endif
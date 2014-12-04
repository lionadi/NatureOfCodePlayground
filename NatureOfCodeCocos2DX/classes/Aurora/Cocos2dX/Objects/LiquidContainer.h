#ifndef NatureOfCodeCocos2DX_LiquidContainer_h
#define NatureOfCodeCocos2DX_LiquidContainer_h

#include "../../Random/RandomOperations.h"
#include "../../Physics/PhysicsOperations.h"
#include "../Cocos2DXCommonTools.h"


using namespace Aurora::Physics;

namespace Aurora
{
	namespace Cocos2DX
	{
		class LiquidContainer : public Aurora::Physics::Liquid, public Aurora::Physics::ILiquid
		{
		private:
			virtual void init();
			void init(const Size &areaSize, float coefficientDrag);


			cocos2d::Color4F mainColor;
			cocos2d::DrawNode *objectDrawNode;
		public:

			LiquidContainer();
			LiquidContainer(const Size &viewSize);
			LiquidContainer(const Size &viewSize, float coefficientDrag);
			virtual ~LiquidContainer();


			DrawNode * GetDrawNode();

			virtual void Render() final;



		};
	};
};

#endif
#ifndef NatureOfCodeCocos2DX_OscillatorBot_h
#define NatureOfCodeCocos2DX_OscillatorBot_h

#include "../../Random/RandomOperations.h"
#include "../Cocos2DXCommonTools.h"
#include "../../Physics/PhysicsOperations.h"

using namespace Aurora::Random;
using namespace Aurora::Physics;


namespace Aurora
{
	namespace Cocos2DX
	{
		class OscillatorBot : public IOscillatorImplementor, private Oscillator, private IPhysicsForceRepresentationBase
		{
		private:
			Size viewSize;
			cocos2d::Color4F mainColor;
			int colorCount;
			int colorCountLimit;
			cocos2d::DrawNode *dotMoverDrawNode;
			Vec2 moverDrawNodeTarget;
		public:
			OscillatorBot();
			OscillatorBot(const Size &viewSize);
			virtual ~OscillatorBot();

			virtual void Render() override;

			virtual std::shared_ptr<Physics::Force> AccessObjectPhysics() const final;

			virtual void init() override;

			DrawNode * GetMoverDrawNode();
			void SetMoverDrawNodeStartPosition(const Vec2& startPosition);

		};

		namespace AliasDeclarations
		{
			using OscillatorBots = std::vector < std::shared_ptr<Aurora::Cocos2DX::OscillatorBot> >;
		};
	}
}

#endif
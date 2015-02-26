#include "OscillatorBot.h"

using namespace cocos2d;

namespace Aurora
{
	namespace Cocos2DX
	{


		void OscillatorBot::Render()
		{
			if (this->dotMoverDrawNode == nullptr)
				return;

			this->mainColor = cocos2d::Color4F(RandomNumberGenerator::GetRandomPositiveFloat(1), RandomNumberGenerator::GetRandomPositiveFloat(1), RandomNumberGenerator::GetRandomPositiveFloat(1), 0.5f);
			this->mainColor = cocos2d::Color4F::BLUE;

			this->dotMoverDrawNode->drawDot(Vec2(0, 0), this->ObjectPhysics()->Mass(), this->mainColor);

			IOscillatorImplementor::Render();
			DelayTime *delayAction = DelayTime::create(0.0001f);

			auto updateAngularMomentum = CallFunc::create(
			[&]() { 
				this->DoCalculations();
				Point origin = Director::getInstance()->getVisibleOrigin();
				this->dotMoverDrawNode->setPosition(ConvertVECTOR2DTp_Vec2(this->ObjectPhysics()->Position()) + origin);
				} 
			);

			Sequence *actionSequence = Sequence::create(updateAngularMomentum, delayAction, NULL);

			this->dotMoverDrawNode->runAction(RepeatForever::create(actionSequence));
		}


		std::shared_ptr<Physics::Force> OscillatorBot::AccessObjectPhysics() const
		{
			return this->ObjectPhysics();
		}

		void OscillatorBot::init()
		{
			this->dotMoverDrawNode = DrawNode::create();
			this->ObjectPhysics()->Mass(10);
			VECTOR2D zero = VECTOR2D(this->viewSize.width / 2, this->viewSize.height / 2);
			this->StartPosition(zero);
			this->ObjectPhysics()->Position(zero);
			this->ObjectPhysics()->AreaSize(ConvertSizeTo_mRect(this->viewSize));
			this->ImplementorObjectPhysics(this->ObjectPhysics());
			this->dotMoverDrawNode->setAnchorPoint(Vec2(0, 0));
			//(viewSize, position, velocity, acceleration, mass);
		}

		DrawNode * OscillatorBot::GetMoverDrawNode()
		{
			return(this->dotMoverDrawNode);
		}

		void OscillatorBot::SetMoverDrawNodeStartPosition(const Vec2& startPosition)
		{
			this->dotMoverDrawNode->setPosition(startPosition);
		}

		OscillatorBot::OscillatorBot(const Size &viewSize) : Oscillator(ConvertSizeTo_mRect(viewSize)), IOscillatorImplementor(), IPhysicsForceRepresentationBase()
		{
			this->SetConstrainsRange(ConvertSizeTo_mRect(viewSize));
			this->viewSize = viewSize;
			this->init();
			this->Render();
		}

		OscillatorBot::OscillatorBot() : Oscillator(), IOscillatorImplementor(), IPhysicsForceRepresentationBase()
		{

		}

		OscillatorBot::~OscillatorBot()
		{
			IOscillatorImplementor::~IOscillatorImplementor();
			Oscillator::~Oscillator();
			IPhysicsForceRepresentationBase::~IPhysicsForceRepresentationBase();
		}

	}
}
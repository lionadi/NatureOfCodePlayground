#include "TesterBot.h"
using namespace cocos2d;



Aurora::Cocos2DX::TestBot::TestBot() : Mover()
{
	this->init();
}

Aurora::Cocos2DX::TestBot::TestBot(const Size &viewSize) : Mover(ConvertSizeTo_mRect(viewSize))
{
	this->init(viewSize, Vec2::ZERO, Vec2::ZERO, Vec2::ZERO, 1);
}

Aurora::Cocos2DX::TestBot::TestBot(const Size &viewSize, const Vec2 &position, const Vec2 &velocity, const Vec2 &acceleration, const cocos2d::Color4F &color)
{
	this->init(viewSize, position, velocity, acceleration, 1);
	this->mainColor = color;
	this->dotMoverDrawNode->setAnchorPoint(Vec2(0, 0));
	this->Render();
}

Aurora::Cocos2DX::TestBot::TestBot(const Size &viewSize, const Vec2 &position, const Vec2 &velocity, const Vec2 &acceleration, const float &mass) 
{
	this->init(viewSize, position, velocity, acceleration, mass);
	this->dotMoverDrawNode->setAnchorPoint(Vec2(0, 0));
	this->Render();
}

Aurora::Cocos2DX::TestBot::~TestBot()
{
	IMoverImplementor::~IMoverImplementor();
	Mover::~Mover();
}

DrawNode * Aurora::Cocos2DX::TestBot::GetMoverDrawNode()
{
	return(this->dotMoverDrawNode);
}

void Aurora::Cocos2DX::TestBot::SetMoverDrawNodeStartPosition(const Vec2& startPosition)
{
	this->dotMoverDrawNode->setPosition(startPosition);
}

void Aurora::Cocos2DX::TestBot::Render()
{
	if (this->dotMoverDrawNode == nullptr)
		return;
	
	this->mainColor = cocos2d::Color4F(RandomNumberGenerator::GetRandomPositiveFloat(1), RandomNumberGenerator::GetRandomPositiveFloat(1), RandomNumberGenerator::GetRandomPositiveFloat(1), 0.5f);
	this->mainColor = cocos2d::Color4F::BLUE;
	this->SetVelocityRange(5, 0);

	//this->dotMoverDrawNode->drawDot(Vec2(0,0), this->GetMoverMass(), this->mainColor);

	Vec2 *vecs = new Vec2[4];
	Point origin = Director::getInstance()->getVisibleOrigin();
	vecs[0].x = 0;
	vecs[0].y = 0;
	vecs[1].x = 0;
	vecs[1].y = 10;
	vecs[2].x = 10;
	vecs[2].y = 10;
	vecs[3].x = 10;
	vecs[3].y = 0;
	//vecs[0] += 0;
	//vecs[1] += 0;
	//vecs[2] += 0;
	//vecs[3] += 0;
	/*auto polygonData = ConvertVECTOR2DListTp_Vec2(this->LiquidArea());
	for (auto &singlePoly : polygonData)
	{
		singlePoly += origin;
	}*/

	this->dotMoverDrawNode->drawPolygon(&vecs[0], 4, this->mainColor, 1, this->mainColor);


	IMoverImplementor::Render();
	DelayTime *delayAction = DelayTime::create(0.0001f);
	//std::function<void(DotWalker&)> makeWalkerStep = &DotWalker::StepWalker;
	// perform the selector call
	CallFunc *callSelectorAction = CallFunc::create(
		std::bind(&TestBot::MoveMover, this));

	/*auto updateAngularMomentum = CallFunc::create(
		[&]() { this->ObjectPhysics()->UpdateAngular(); } );*/

	//auto rotateBy = RotateBy::create(0.01f, this->ObjectPhysics()->AngularAcceleration());
	//Sequence *actionSequence = Sequence::create(callSelectorAction, updateAngularMomentum, rotateBy, delayAction, NULL);
	Sequence *actionSequence = Sequence::create(callSelectorAction, delayAction, NULL);

	this->dotMoverDrawNode->runAction(RepeatForever::create(actionSequence));
}

void Aurora::Cocos2DX::TestBot::SetMoverTarget(const Vec2 &target)
{
	Point origin = Director::getInstance()->getVisibleOrigin();
	this->SetTarget(ConvertVec2Tp_VECTOR2D(target - origin));
	this->moverDrawNodeTarget = this->dotMoverDrawNode->convertToNodeSpace(target);
}

void Aurora::Cocos2DX::TestBot::MoveMover()
{
	//this->SetPosition(ConvertVec2Tp_VECTOR2D(this->dotMoverDrawNode->getPosition()));
	this->DoCalculations();
	this->Accelerate();
	Point origin = Director::getInstance()->getVisibleOrigin();
	this->dotMoverDrawNode->setPosition(ConvertVECTOR2DTp_Vec2(this->GetCurentPosition()) + origin);
	//auto angle = this->ObjectPhysics()->Angle();
	//this->dotMoverDrawNode->setRotation(angle);
	
}

void Aurora::Cocos2DX::TestBot::init()
{
	this->dotMoverDrawNode = DrawNode::create();
	this->ImplementorObjectPhysics(this->ObjectPhysics());
}

void Aurora::Cocos2DX::TestBot::init(const Size &viewSize, const Vec2 &position, const Vec2 &velocity, const Vec2 &acceleration, const float &mass)
{
	//Mover::Mover(ConvertVec2Tp_VECTOR2D(position), ConvertVec2Tp_VECTOR2D(velocity), ConvertVec2Tp_VECTOR2D(acceleration), ConvertSizeTo_mRect(viewSize), mass);
	this->ObjectPhysics()->Position(ConvertVec2Tp_VECTOR2D(position));
	//this->ObjectPhysics()->Acceleration(ConvertVec2Tp_VECTOR2D(acceleration));
	//this->ObjectPhysics()->Velocity(ConvertVec2Tp_VECTOR2D(velocity));
	this->ObjectPhysics()->Mass(mass);
	this->ObjectPhysics()->AreaSize(ConvertSizeTo_mRect(viewSize));
	//this->ObjectPhysics()->AngularAcceleration(0.1f);
	this->SetConstrainsRange(ConvertSizeTo_mRect(viewSize));
	this->viewSize = viewSize;
	this->dotMoverDrawNode = DrawNode::create();
	this->ImplementorObjectPhysics(this->ObjectPhysics());
}

void Aurora::Cocos2DX::TestBot::init(const IMoverImplementor &value)
{

}

std::shared_ptr<Aurora::Physics::Force> Aurora::Cocos2DX::TestBot::AccessObjectPhysics() const
{
	return this->ObjectPhysics();
}

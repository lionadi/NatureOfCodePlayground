#include "TesterBot.h"
using namespace cocos2d;



Aurora::Cocos2DX::TestBot::TestBot() : Mover()
{
	this->init();
}

Aurora::Cocos2DX::TestBot::TestBot(const Size &viewSize) : Mover(ConvertSizeTo_mRect(viewSize))
{
	this->init(viewSize);
}

Aurora::Cocos2DX::TestBot::TestBot(const Size &viewSize, const Vec2 &position, const Vec2 &velocity, const Vec2 &acceleration) : Mover(ConvertVec2Tp_VECTOR2D(position), ConvertVec2Tp_VECTOR2D(velocity), ConvertVec2Tp_VECTOR2D(acceleration), ConvertSizeTo_mRect(viewSize))
{

	this->init(viewSize);
	//Vec2 t3 = this->dotMoverDrawNode->getParent()->convertToNodeSpace(position);
	this->dotMoverDrawNode->setAnchorPoint(Vec2(0,0));
	this->Render();
}

Aurora::Cocos2DX::TestBot::~TestBot()
{
	IMover::~IMover();
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
	
	this->mainColor = cocos2d::Color4F::MAGENTA;
	this->SetVelocityRange(5, 0);

	//this->dotMoverDrawNode->drawDot(ConvertVECTOR2DTp_Vec2(this->GetCurentPosition()), 10, this->mainColor);
	this->dotMoverDrawNode->drawDot(Vec2(0,0), 10, this->mainColor);
	/*this->dotMoverDrawNode->drawDot(Vec2(0, visibleSize.height / 2), 10, cocos2d::Color4F::BLUE);
	this->dotMoverDrawNode->drawDot(Vec2(600, 200), 10, cocos2d::Color4F::GREEN);
	
	
	this->dotMoverDrawNode->drawDot(Vec2(10, 10), 10, cocos2d::Color4F::ORANGE);
	this->dotMoverDrawNode->drawDot(Vec2(visibleSize.width / 2, visibleSize.height/2), 10, cocos2d::Color4F::MAGENTA);
	this->dotMoverDrawNode->drawDot(Vec2(winSize.width/2, winSize.height/2), 10, cocos2d::Color4F::RED);*/

	IMover::Render();
	DelayTime *delayAction = DelayTime::create(0.0001f);
	//std::function<void(DotWalker&)> makeWalkerStep = &DotWalker::StepWalker;
	// perform the selector call
	CallFunc *callSelectorAction = CallFunc::create(
		std::bind(&TestBot::MoveMover, this));

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
	Vec2 t = this->dotMoverDrawNode->getParent()->convertToNodeSpace(ConvertVECTOR2DTp_Vec2(this->GetCurentPosition()));
	Vec2 t2 = this->dotMoverDrawNode->getParent()->convertToWorldSpace(ConvertVECTOR2DTp_Vec2(this->GetCurentPosition()));
	Vec2 tt = ConvertVECTOR2DTp_Vec2(this->GetCurentPosition()) + origin;
	this->dotMoverDrawNode->setPosition(tt);
	Vec2 t3 = this->dotMoverDrawNode->convertToWorldSpace(ConvertVECTOR2DTp_Vec2(this->GetCurentPosition()));
	
	Vec2 t5 = this->dotMoverDrawNode->convertToNodeSpace(ConvertVECTOR2DTp_Vec2(this->GetCurentPosition()));
}

void Aurora::Cocos2DX::TestBot::init()
{
	this->dotMoverDrawNode = DrawNode::create();
	
}

void Aurora::Cocos2DX::TestBot::init(const Size &areaSize)
{
	this->viewSize = areaSize;
	this->dotMoverDrawNode = DrawNode::create();
}

void Aurora::Cocos2DX::TestBot::init(const IWalker &value)
{

}

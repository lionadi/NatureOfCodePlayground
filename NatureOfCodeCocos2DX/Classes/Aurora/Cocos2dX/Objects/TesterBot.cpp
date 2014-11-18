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
	this->dotMoverDrawNode->setPosition(position);
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
	
	this->mainColor = cocos2d::Color4F::YELLOW;
	this->dotMoverDrawNode->drawDot(this->dotMoverDrawNode->getPosition(), 10, this->mainColor);

	IMover::Render();
	DelayTime *delayAction = DelayTime::create(0.0001f);
	//std::function<void(DotWalker&)> makeWalkerStep = &DotWalker::StepWalker;
	// perform the selector call
	CallFunc *callSelectorAction = CallFunc::create(
		std::bind(&TestBot::MoveMover, this));

	Sequence *actionSequence = Sequence::create(callSelectorAction, delayAction, NULL);

	this->dotMoverDrawNode->runAction(RepeatForever::create(actionSequence));
}

void Aurora::Cocos2DX::TestBot::MoveMover()
{
	this->DoCalculations();
	this->dotMoverDrawNode->setPosition(ConvertVECTOR2DTp_Vec2(this->GetCurentPosition()));
}

void Aurora::Cocos2DX::TestBot::init()
{
	this->dotMoverDrawNode = DrawNode::create();
	this->SetVelocityRange(10, 0);
	this->Render();
}

void Aurora::Cocos2DX::TestBot::init(const Size &areaSize)
{
	this->viewSize = areaSize;
	this->dotMoverDrawNode = DrawNode::create();
	this->SetVelocityRange(10, 0);
	this->Render();
}

void Aurora::Cocos2DX::TestBot::init(const IWalker &value)
{

}

#include "MainMenuScene.h"
#include "GameScene.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(GameScreen::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScreen::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScreen::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(GameScreen::onTouchCancelled, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	isTouching = false;
	glClearColor(1.0, 1.0, 1.0, 1.0);
	this->setColor(cocos2d::Color3B::WHITE);
	//this->testBots = std::make_unique<AliasDeclarations::VectorTestBots>();

	for (int x = 0; x < 7; ++x)
	{
		this->oscillatorBots.push_back(std::make_shared<OscillatorBot>(visibleSize));
		// For random generated objects
		//this->testBots.push_back(std::make_shared<TestBot>(visibleSize, Vec2(RandomNumberGenerator::GetRandomPositiveFloat(visibleSize.width / 3), RandomNumberGenerator::GetRandomPositiveFloat(visibleSize.height /3)), Vec2::ZERO, Vec2(RandomNumberGenerator::GetRandomFloat(2), RandomNumberGenerator::GetRandomFloat(2)), RandomNumberGenerator::GetRandomPositiveFloat(15)));

		// Single object
		//this->testBots.push_back(std::make_shared<TestBot>(visibleSize, Vec2(visibleSize.width / 2, visibleSize.height / 2), Vec2::ZERO, Vec2::ZERO));
	}

	this->water = std::make_shared<LiquidContainer>(visibleSize, 0.3f);
	this->walker = std::make_shared<DotWalker>(visibleSize, Vec2((visibleSize.width / 2), (visibleSize.height / 2)));
	this->testBot = std::make_shared<TestBot>(visibleSize, Vec2(visibleSize.width / 2, visibleSize.height / 2), Vec2::ZERO, Vec2::ZERO, 40);
	this->walker->SetWalkerRandomNumberMode(RandomNumberMode::Perlin);
	//this->testBot->SetRandomNumberMode(RandomNumberMode::Perlin);
	this->walker->SetWalkerDrawNodeStartPosition(Vec2(origin.x, origin.y));
	//this->testBot->SetMoverDrawNodeStartPosition(Vec2(origin.x, origin.y));
	//this->addChild(this->walker->GetWalkerDrawNode());
	this->addChild(this->testBot->GetMoverDrawNode());
	for (auto testBotTemp : this->testBots)
	{
		
		this->addChild(testBotTemp->GetMoverDrawNode());
		//testBotTemp->SetRandomNumberMode(RandomNumberMode::Perlin);
	}

	for (auto oscillatorBotTemp : this->oscillatorBots)
	{

		this->addChild(oscillatorBotTemp->GetMoverDrawNode());
		//testBotTemp->SetRandomNumberMode(RandomNumberMode::Perlin);
	}

	//this->addChild(this->water->GetDrawNode());
	/*Size cS = this->getContentSize();
	Vec2 cp = this->getPosition();*/
	this->scheduleUpdate();
    
    return true;
}

void MainMenu::update(float dt)
{
	/*for (auto testBotTemp : this->testBots)
	{
		if (this->water->IsInside(testBotTemp->GetCurentPosition()))
		{
			std::shared_ptr<Aurora::Physics::Force> ff = testBotTemp->ObjectPhysics();
			VECTOR2D dragForce = FrictionCalculations::SimplifiedDragForceCalculations(testBotTemp->ObjectPhysics()->Velocity(), this->water->CoefficientDrag());
			testBotTemp->ObjectPhysics()->ApplyForce(dragForce);
		}
	}*/
	/*for (auto testBotTemp : this->testBots)
	{
		VECTOR2D gravAttraction = CommonCalculations::GravitationalAttractionCalculations(1, this->testBot->ObjectPhysics()->Position(), this->testBot->ObjectPhysics()->Mass(), testBotTemp->ObjectPhysics()->Position(), testBotTemp->ObjectPhysics()->Mass(), 5, 25);
		testBotTemp->ObjectPhysics()->ApplyForce(gravAttraction);
	}*/
	//for (auto i = 0; i < this->testBots.size(); i++) {
	//	for (auto j = 0; j < this->testBots.size(); j++) {
	//		//Don’t attract yourself!
	//			if (i != j) {
	//				VECTOR2D gravAttraction = CommonCalculations::GravitationalAttractionCalculations(0.4f, this->testBots[j]->AccessObjectPhysics()->Position(), this->testBots[j]->AccessObjectPhysics()->Mass(), this->testBots[i]->AccessObjectPhysics()->Position(), this->testBots[i]->AccessObjectPhysics()->Mass(), 5, 25);
	//					//movers[j].attract(movers[i]);
	//				this->testBots[i]->AccessObjectPhysics()->ApplyForce(gravAttraction);

	//			}
	//	}
	//}

	// Graviational Pull exmaple
	//for (auto i = 0; i < this->testBots.size(); i++) {
	//	
	//		//Don’t attract yourself!
	//			
	//				//VECTOR2D gravAttraction = CommonCalculations::GravitationalAttractionCalculations(0.4f, this->testBots[j]->AccessObjectPhysics()->Position(), this->testBots[j]->AccessObjectPhysics()->Mass(), this->testBots[i]->AccessObjectPhysics()->Position(), this->testBots[i]->AccessObjectPhysics()->Mass(), 5, 25);
	//					//movers[j].attract(movers[i]);
	//				auto distance = this->testBot->AccessObjectPhysics()->Position() - this->testBots[i]->AccessObjectPhysics()->Position();
	//				auto distanceMagnitude = distance.Magnitude();

	//				auto x = 10 * cos(this->testBots[i]->AccessObjectPhysics()->Angle());
	//				auto y = 10 * sin(this->testBots[i]->AccessObjectPhysics()->Angle());
	//				this->testBots[i]->AccessObjectPhysics()->Angle(this->testBots[i]->AccessObjectPhysics()->Angle() + 0.01f);
	//				CCLOG("TestBot anguler Pos X: %f", x);
	//				CCLOG("TestBot anguler Pos Y: %f", y);
	//				this->testBots[i]->AccessObjectPhysics()->Position(VECTOR2D(x, y));
	//					
	//			}
	
	// Single X axis oscillation
	/*
	auto distance = this->testBot->AccessObjectPhysics()->Position() - this->testBot->AccessObjectPhysics()->Position();
	auto distanceMagnitude = distance.Magnitude();

	auto frames = Director::getInstance()->getFrameRate();
	if (frameCount < frames)
		frameCount++;
	else
		frameCount = 0;
	mPOLAR2D polar;
	polar.r = 100;
	polar.theta = PI2 * Aurora::Engine::EngineCommonCalculations::CalculateDeltaTime(frameCount,frames != 0 ? frames : 60);

		float x = 0;
		float y = 0;
		MathOperations::POLAR2DToFloatXY(&x, &y, polar);
	this->testBot->AccessObjectPhysics()->Angle(this->testBot->AccessObjectPhysics()->Angle() + 0.01f);
	CCLOG("TestBot anguler Pos X: %f", x);
	CCLOG("TestBot anguler Pos Y: %f", y);
	auto origin = Director::getInstance()->getVisibleOrigin();
	this->testBot->AccessObjectPhysics()->Position(VECTOR2D(x, (Director::getInstance()->getVisibleSize().height / 2)) + ConvertVec2Tp_VECTOR2D(origin));
	*/
}

void MainMenu::GoToGameScene(cocos2d::Ref *pSender)
{
    auto scene = GameScreen::createScene();
    
    Director::getInstance()->replaceScene(scene);
}

bool MainMenu::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event)
{
	isTouching = true;
	//touchPosition = touch->getLocation()
	CCPoint touchLocation = touch->getLocationInView();
	// Convert to visible + origin size area
	touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
	//this->testBot->SetMoverTarget(touchLocation);
	for (auto testBotTemp : this->testBots)
	{
		testBotTemp->SetMoverTarget(touchLocation);
	}
	return(isTouching);
}

void MainMenu::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event * event)
{
	onTouchBegan(touch, event);
}

void MainMenu::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event * event)
{
	isTouching = false;
}

void MainMenu::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event * event)
{
	onTouchEnded(touch, event);
}

MainMenu::~MainMenu()
{
	Layer::~Layer();
	
}

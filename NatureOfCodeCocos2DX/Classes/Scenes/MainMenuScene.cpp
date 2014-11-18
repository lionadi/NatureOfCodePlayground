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

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(GameScreen::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScreen::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScreen::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(GameScreen::onTouchCancelled, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	isTouching = false;

	this->walker = std::make_shared<DotWalker>(visibleSize, Vec2((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
	this->testBot = std::make_shared<TestBot>(visibleSize, Vec2((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y), Vec2::ZERO, Vec2(1,0));
	this->walker->SetRandomNumberMode(RandomNumberMode::Perlin);
	this->walker->SetWalkerDrawNodeStartPosition(Vec2(origin.x, origin.y));
	this->testBot->SetMoverDrawNodeStartPosition(Vec2(origin.x, origin.y));
	//this->addChild(this->walker->GetWalkerDrawNode());
	this->addChild(this->testBot->GetMoverDrawNode());

	
    
    return true;
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
	this->walker->SetWalkerTarget(touch->getLocation());
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

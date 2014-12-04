#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"
#include "../Aurora/Aurora.h"

using namespace Aurora::Cocos2DX;

class MainMenu : public cocos2d::Layer
{
public:

	~MainMenu();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
	bool isTouching;
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	std::shared_ptr<DotWalker> walker;
	std::shared_ptr<TestBot> testBot;
	std::shared_ptr<LiquidContainer> water;
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu);
	AliasDeclarations::VectorTestBots testBots;
	void update(float dt) override;

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event * event);
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event * event);
	void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event * event);

    void GoToGameScene(Ref *pSender);
};

#endif // __MAINMENU_SCENE_H__

#include "Help.h"
#include"GameMainLayer.h"
#include "GameStart.h"

USING_NS_CC;

Scene* Help::createScene()
{
	// 'scene' is an autorelease Ref
	auto scene = Scene::create();

	// 'layer' is an autorelease Ref
	auto layer = Help::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool Help::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite *bg = Sprite::create("help/help-back.png");
    bg->setPosition(Vec2(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height /2));
    this->addChild(bg);

	//Ok°´Å¥
	auto okMenuItem  = MenuItemImage::create(
		"help/ok-down.png",
		"help/ok-up.png",
		CC_CALLBACK_1(Help::menuOkItemCallback, this));
	okMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(900, 610)));

	Menu* mn = Menu::create(okMenuItem, NULL);
	mn->setPosition(Vec2::ZERO);
	this->addChild(mn);

	return true;
}

void Help::menuOkItemCallback(Ref* pSender)
{
	this->removeAllChildrenWithCleanup(true);
	Scene* GSscene  = GameStart:: createScene();
	GSscene = TransitionShrinkGrow::create(0.8, GSscene);
	Director::getInstance()->replaceScene(GSscene);
}
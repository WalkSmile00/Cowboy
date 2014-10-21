#include "GameSetting.h"
#include"GameMainLayer.h"
#include "GameStart.h"


USING_NS_CC;

Scene* GameSetting::createScene()
{
	// 'scene' is an autorelease Ref
	auto scene = Scene::create();

	// 'layer' is an autorelease Ref
	auto layer = GameSetting::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool GameSetting::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	Sprite *bg = Sprite::create("menu/setting-back.png");
    bg->setPosition(Vec2(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height /2));
    this->addChild(bg);

	//ÒôÐ§
	auto soundOnMenuItem = MenuItemImage::create(
		"menu/on.png",
		"menu/on.png");
	auto soundOffMenuItem = MenuItemImage::create(
		"menu/off.png",
		"menu/off.png");

	auto soundToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(GameSetting::menuSoundToggleCallback, this), 
		soundOnMenuItem,
		soundOffMenuItem, 
		NULL);
	soundToggleMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(900, 260)));

	//ÒôÀÖ
	auto musicOnMenuItem  = MenuItemImage::create(
		"menu/on.png",
		"menu/on.png");
	auto musicOffMenuItem  = MenuItemImage::create(
		"menu/off.png",
		"menu/off.png");
	auto musicToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(GameSetting::menuMusicToggleCallback, this),
		musicOnMenuItem,
		musicOffMenuItem,
		NULL );
	musicToggleMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(900, 420)));

	//Ok°´Å¥

	auto okMenuItem  = MenuItemImage::create(
		"menu/ok-down.png",
		"menu/ok-up.png",
		CC_CALLBACK_1(GameSetting::menuOkItemCallback, this));
	okMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(650, 610)));

	Menu* mn = Menu::create(soundToggleMenuItem, musicToggleMenuItem,okMenuItem, NULL);
	mn->setPosition(Vec2::ZERO);
	this->addChild(mn);



	return true;
}


void GameSetting::menuSoundToggleCallback(Ref* pSender)
{

}


void GameSetting::menuMusicToggleCallback(Ref* pSender)
{

}

void GameSetting::menuOkItemCallback(Ref* pSender)
{
	this->removeAllChildrenWithCleanup(true);
	Scene* GSscene  = GameStart:: createScene();
	GSscene = TransitionProgressRadialCCW::create(0.5,GSscene);
	Director::getInstance()->replaceScene(GSscene);
}
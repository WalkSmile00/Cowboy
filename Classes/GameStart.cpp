#include "GameStart.h"
#include"GameMainLayer.h"
#include "GameSetting.h"
#include "Help.h"

USING_NS_CC;

Scene* GameStart::createScene()
{
	// 'scene' is an autorelease Ref
	auto scene = Scene::create();

	// 'layer' is an autorelease Ref
	auto layer = GameStart::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool GameStart::init()
{
	if ( !Layer::init() )
	{
		return false;
	}


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite *bg = Sprite::create("menu/background.png");

    bg->setPosition(Vec2(origin.x + visibleSize.width/2,

                             origin.y + visibleSize.height /2));

    this->addChild(bg);

	//¿ªÊ¼¾«Áé

    Sprite *startSpriteNormal = Sprite::create("menu/start-up.png");
    Sprite *startSpriteSelected = Sprite::create("menu/start-down.png");

	MenuItemSprite *startMenuItem = MenuItemSprite::create(startSpriteNormal, 
													startSpriteSelected,
												   CC_CALLBACK_1(GameStart::menuItemStartCallback, this));

	startMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(700, 170)));    

	//Ìí¼Ó±³¾°ÒôÀÖ
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/start_background.wav",true);

	// ÉèÖÃÍ¼Æ¬²Ëµ¥
    MenuItemImage *settingMenuItem = MenuItemImage::create(
                             "menu/setting-up.png",
                             "menu/setting-down.png",	
							 CC_CALLBACK_1(GameStart::menuItemSettingCallback, this)); 

	settingMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(480, 440)));	

	// °ïÖúÍ¼Æ¬²Ëµ¥
    MenuItemImage *helpMenuItem = MenuItemImage::create(
                             "menu/help-up.png",
                             "menu/help-down.png",
							 CC_CALLBACK_1(GameStart::menuItemHelpCallback, this));	

	helpMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(860, 570)));

	Menu* mu = Menu::create(startMenuItem, settingMenuItem, helpMenuItem, NULL);	
	mu->setPosition(Vec2::ZERO);
	this->addChild(mu);

    return true;
}

void GameStart::menuItemHelpCallback(Ref* pSender)
{
	this->removeAllChildrenWithCleanup(true);
    Scene* Helpscene  = Help:: createScene();
	Helpscene = TransitionJumpZoom ::create(1,Helpscene);
	Director::getInstance()->replaceScene(Helpscene);
}

void GameStart::menuItemStartCallback(Ref* pSender)
{
	this->removeAllChildrenWithCleanup(true);
    Scene* GMscene  = GameMainLayer:: createScene();
	GMscene = TransitionProgressHorizontal ::create(1,GMscene);
	Director::getInstance()->replaceScene(GMscene);
}

void GameStart::menuItemSettingCallback(Ref* pSender)
{
	this->removeAllChildrenWithCleanup(true);
    Scene* GSscene  = GameSetting:: createScene();
	GSscene = TransitionProgressRadialCW::create(0.5,GSscene);
	Director::getInstance()->replaceScene(GSscene);
}

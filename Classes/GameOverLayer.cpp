#include"GameOverLayer.h"
#include "GameMainLayer.h"
#include"LayerStatus.h"
#include"Score.h"
#include<string>
#include<iostream>
#include<sstream>
using namespace std;

USING_NS_CC;

Scene* GameOverLayer::createScene()
{
	// 'scene' is an autorelease Ref
	auto scene = Scene::create();

	// 'layer' is an autorelease Ref
	auto layer = GameOverLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool GameOverLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto background = Sprite::create("background.png");
	background->setAnchorPoint(Vec2::ZERO);
    this->addChild(background,0);   

	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("SpirteSheet.plist");
	//添加背景山精灵
	auto mountain1 = Sprite::createWithSpriteFrameName("mountain1.png");
	mountain1->setAnchorPoint(Vec2::ZERO);
	mountain1->setPosition(Vec2(-200,80));
	this->addChild(mountain1);
	//设置字体
	TTFConfig ttfConfig("fonts/Marker Felt.ttf",
		70,
		GlyphCollection::DYNAMIC);
	ttfConfig.outlineSize = 4;

	_label = Label::createWithTTF(ttfConfig, "Game Over !");
	_label->setPosition(Vec2(origin.x + visibleSize.width/2,
		origin.y + visibleSize.height / 3 * 2.1));
	_label->enableShadow(Color4B(255,255,255,128), Size(4, -4));
	_label->setColor(Color3B::RED);
	this->addChild(_label, 1);
	_label->retain();//保证_label和对象有同样的生命周期

	//设置字体
	TTFConfig ttfConfig2("fonts/Marker Felt.ttf",
		50,
		GlyphCollection::DYNAMIC);
	ttfConfig.outlineSize = 4;
	string str = "Your Score is : ";
	int i = Score::sharedScore()->getScore();
	ostringstream oss;
	oss << i;
	str += oss.str();
	auto s_label = Label::createWithTTF(ttfConfig2, str);
	s_label->setPosition(Vec2(origin.x + visibleSize.width/2,
		origin.y + visibleSize.height / 3 * 1.2));
	s_label->enableShadow(Color4B(255,255,255,128), Size(4, -4));
	s_label->setColor(Color3B::BLUE);
	this->addChild(s_label, 1);

	/*
	//重新开始精灵

    Sprite *startSpriteNormal = Sprite::create("menu/restart-up.png");
	startSpriteNormal->setScale(0.7);
    Sprite *startSpriteSelected = Sprite::create("menu/restart-down.png");
	startSpriteSelected->setScale(0.7);

	MenuItemSprite *startMenuItem = MenuItemSprite::create(startSpriteNormal, 
													startSpriteSelected,
												   CC_CALLBACK_1(GameOverLayer::menuItemRestartCallback, this));

	startMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(650, 300)));    

	//返回按钮

	auto backMenuItem  = MenuItemImage::create(
		"menu/back-up.png",
		"menu/back-down.png",
		CC_CALLBACK_1(GameOverLayer::menuBackItemCallback, this));
	backMenuItem->setScale(0.9);
	backMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(580, 510)));

	Menu* mn = Menu::create(startMenuItem,backMenuItem, NULL);
	mn->setPosition(Vec2::ZERO);
	this->addChild(mn);
	*/
	
}

GameOverLayer::~GameOverLayer()
{
	if (_label){
		_label->release();
	}
}
/*
void GameOverLayer::menuItemRestartCallback(Ref* pSender)
{
	this->removeAllChildrenWithCleanup(true);
	//设置场景状态为emrunning
	LayerStatus::sharedLayerStatus()->setLayerStatus(emended);
	Scene* HWscene  = GameMainLayer:: createScene();
	Director::getInstance()->replaceScene(HWscene);
}

void GameOverLayer::menuBackItemCallback(Ref* pSender)
{

}

*/
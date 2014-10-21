#include "GameMainLayer.h"
#include "SimpleAudioEngine.h"
#include "GameOverLayer.h"
#include "cocostudio/CocoStudio.h"
#include "LayerStatus.h"
#include "Hero.h"
#include "Monster.h"
#include "Score.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;
using namespace cocostudio;

Scene * GameMainLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = GameMainLayer::create();
	scene->addChild(layer);
	return scene;
}

bool GameMainLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	//初始化场景
	if(LayerStatus::sharedLayerStatus()->getLayerStatus() == emended)
	{
		this->removeAll();
	}

	//设置场景状态为emrunning
	LayerStatus::sharedLayerStatus()->setLayerStatus(emrunning);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("background.png");
	background->setAnchorPoint(Vec2::ZERO);
    this->addChild(background,0);   

	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("SpirteSheet.plist");
	//添加背景山精灵
	auto mountain1 = Sprite::create("mountain1.png");
	mountain1->setAnchorPoint(Vec2::ZERO);
	mountain1->setPosition(Vec2(-200,80));
	this->addChild(mountain1);
	
	//添加人物精灵
	Sprite * sprite = Sprite::create();
	Size spriteSize = sprite->getContentSize();
	auto m_hero = Hero::create();
	m_hero->bindSprite(sprite);
	m_hero->setScale(0.5);
	m_hero->setAnchorPoint(Vec2(1,1));
	m_hero->setPosition(Vec2(150,150));
	this->addChild(m_hero,1);

	ArmatureDataManager::getInstance()->addArmatureFileInfo("HeroAni/HeroAni.ExportJson");
	auto heroAni = Armature::create("HeroAni");
	heroAni->getAnimation()->play("Hero_Ride");
	heroAni->setAnchorPoint(Vec2(0.5,0.5));

	m_hero->addChild(heroAni);

	//设置Score
	TTFConfig ttfConfig("fonts/Marker Felt.ttf",
		40,
		GlyphCollection::DYNAMIC);
	ttfConfig.outlineSize = 4;
	score_label = Label::createWithTTF(ttfConfig, "Score : ");
	score_label->setPosition(Vec2(origin.x + visibleSize.width / 10 * 8.5,
		origin.y + visibleSize.height /20 * 19));
	score_label->enableShadow(Color4B(255,255,255,128), Size(4, -4));
	score_label->setColor(Color3B::GRAY);
	this->addChild(score_label, 1);

	//每隔一秒时间添加怪物，通过改变这个时间可以改变怪物出现的快慢
	this->schedule(schedule_selector(GameMainLayer::addMonster),1.0);
	
	//添加背景音乐
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/background.wav",true);

	//定时更新分数
	this->schedule(schedule_selector(GameMainLayer::createScore));

	//开启屏幕触摸
	this->setTouchEnabled(true);
	m_hero->fire();
	return true;
}
/*
void GameMainLayer::onEnter()
{

}

void GameMainLayer::onExit()
{

}
*/
//添加怪物
void GameMainLayer::addMonster(float tm)
{
	Monster * monster = Monster::create();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//设置怪物出现在屏幕的最左边
	int x = visibleSize.width;
	//怪物的y坐标是我们通过getRandomNumber函数随机获得的数值
	//我们希望的怪物y坐标是不低于怪物自己的半身高，不高于它的头部，记住怪物的锚点在中心位置
	int y = getRandomNumber(monster->getContentSize().height/2,visibleSize.height);
	monster->setPosition(Vec2(x,y));

	this->addChild(monster);
}

//start和end代表希望获得的随机数范围
int GameMainLayer::getRandomNumber(int start,int end)
{
	return CCRANDOM_0_1()*(end-start)+start;
}

void GameMainLayer::createScore(float delta)
{
	
	string str = "Score : ";
	int i = Score::sharedScore()->getScore();
	ostringstream oss;
	oss << i;
	str += oss.str();
	score_label->setString(str);
}

void GameMainLayer::removeAll()
{
	this->removeAllChildrenWithCleanup(false);
}

GameMainLayer::~GameMainLayer()
{
	this->removeAll();
}

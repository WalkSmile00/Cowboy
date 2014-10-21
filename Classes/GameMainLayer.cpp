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
	//��ʼ������
	if(LayerStatus::sharedLayerStatus()->getLayerStatus() == emended)
	{
		this->removeAll();
	}

	//���ó���״̬Ϊemrunning
	LayerStatus::sharedLayerStatus()->setLayerStatus(emrunning);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("background.png");
	background->setAnchorPoint(Vec2::ZERO);
    this->addChild(background,0);   

	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("SpirteSheet.plist");
	//��ӱ���ɽ����
	auto mountain1 = Sprite::create("mountain1.png");
	mountain1->setAnchorPoint(Vec2::ZERO);
	mountain1->setPosition(Vec2(-200,80));
	this->addChild(mountain1);
	
	//������ﾫ��
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

	//����Score
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

	//ÿ��һ��ʱ����ӹ��ͨ���ı����ʱ����Ըı������ֵĿ���
	this->schedule(schedule_selector(GameMainLayer::addMonster),1.0);
	
	//��ӱ�������
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/background.wav",true);

	//��ʱ���·���
	this->schedule(schedule_selector(GameMainLayer::createScore));

	//������Ļ����
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
//��ӹ���
void GameMainLayer::addMonster(float tm)
{
	Monster * monster = Monster::create();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//���ù����������Ļ�������
	int x = visibleSize.width;
	//�����y����������ͨ��getRandomNumber���������õ���ֵ
	//����ϣ���Ĺ���y�����ǲ����ڹ����Լ��İ���ߣ�����������ͷ������ס�����ê��������λ��
	int y = getRandomNumber(monster->getContentSize().height/2,visibleSize.height);
	monster->setPosition(Vec2(x,y));

	this->addChild(monster);
}

//start��end����ϣ����õ��������Χ
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

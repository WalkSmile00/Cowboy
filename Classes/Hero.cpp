#include "Hero.h"
#include "Bullet.h"
#include "BulletManager.h"

bool Hero::init()
{
	bool bRet = false;
	do
	{
                //首先初始化父类的init函数
		CC_BREAK_IF(!Sprite::init());
		//为成员变量赋值，否则的话指针指向的是空
		m_sprite = Sprite::create();

		bRet = true;
	}
	while(0);

	return bRet;
}

void Hero::bindSprite(Sprite * sprite)
{
	m_sprite = sprite;
	this->addChild(m_sprite);
}

void Hero::fire()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto dispatcher = Director::getInstance()->getEventDispatcher(); 
	auto m_myListener = EventListenerTouchOneByOne::create();			//创建一个触摸监听    
	m_myListener->setSwallowTouches(false);							//设置是否想下传递触摸  
	dispatcher->removeEventListener(m_myListener);
	m_myListener->onTouchBegan = [=](Touch* touch,Event* event)
	{ 
			// 获取触摸点坐标
			auto loc = Director::getInstance()->convertToGL(touch->getStartLocationInView()); 
			if(loc.x <=140)
			{
				return false;
			}
			//添加子弹
			Bullet * bullet = Bullet::create();
			//将子弹的开始位置设置为玩家所在的坐标位置
			bullet->setPosition(this->getPosition());
			//将子弹添加到主场景中
			this->getParent()->addChild(bullet);

			//__Array* array = __Array::create();
			//Array *array = Array::create();
			//array->addObject(bullet);
			//log("%d",array->count());
			BulletManager::sharedBulletManager()->getBulletArray()->addObject(bullet);
			//log("%d",BulletManager::sharedBulletManager()->getBulletArray()->count());
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("music/bullet.mp3");
			double dx = loc.x -140;
			double dy = loc.y - 130;
			double d = sqrt(dx * dx + dy * dy);//sqtr:求平方根

			double D = sqrt(visibleSize.width * visibleSize.width + visibleSize.height * visibleSize.height);

			double ratio = D / d;
			double endx = ratio * dx + 140;
			double endy = ratio * dy + 130;

			MoveTo* move = MoveTo::create(D / 500,Vec2(endx,endy));
			Sequence* actions = Sequence::create(move,NULL);
			bullet->runAction(actions);
	};
	//dispatcher->addEventListenerWithSceneGraphPriority(m_myListener,fightScene);
	dispatcher->addEventListenerWithFixedPriority(m_myListener,-1);
	//m_myListener->release();

}
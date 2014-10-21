#include "Monster.h"
#include "BulletManager.h"
#include "Score.h"
#include"GameOverLayer.h"
#include"GameMainLayer.h"
#include"LayerStatus.h"

bool Monster::init()
{
	setStatus(emnormal);
	bool bRet = false;
	do
	{
		//初始化父类的时候调用initWithFile()方法里边传入一个图片资源，当创建怪物的时候就是这个图片了
		CC_BREAK_IF(!Sprite::initWithFile("target1.png"));

		//获得屏幕的尺寸
		m_winSize = Director::getInstance()->getWinSize();

		//每隔一帧就调用move函数和update函数
		this->schedule(schedule_selector(Monster::move));
		this->scheduleUpdate();

		bRet = true;
	}
	while(0);

	return bRet;
}

void Monster::update(float tm)
{
	//判断怪物是否超出了边界
	if(this->isOut())
	{
		//将怪物从父节点上移除
		this->removeFromParentAndCleanup(true);
		//设置场景状态为emended
		LayerStatus::sharedLayerStatus()->setLayerStatus(emended);
		//切换场景
		Scene* GOscene  = GameOverLayer:: createScene();
		Director::getInstance()->replaceScene(GOscene);	
	}
	
	//Object * obj;
	Ref* obj = nullptr;
	//以下的语句将取出CCArray中的每个元素，取出来的时候事CCObject，所以要转化为我们要的类型
	
	CCARRAY_FOREACH(BulletManager::sharedBulletManager()->getBulletArray(),obj)
	{
		Sprite * bullet = (Sprite *)obj;
		//boundingBox()函数将返回一个CCRect的对象，它的intersectsRect方法用来判断与另一个CCRect有没有相交
		if ( getStatus() == emnormal ) 
		{
			if(this->boundingBox().intersectsRect(bullet->boundingBox()))
			{
				//如果子弹和怪物相交就将子弹从数组中移除出去
				int m = Score::sharedScore()->getScore();
				m += 100;
				Score::sharedScore()->setScore(m);

				setStatus(embeattacked);
				BulletManager::sharedBulletManager()->getBulletArray()->removeObject(bullet);
				//如果子弹和怪物相交就将怪物和子弹从主场景中移除
				this->removeFromParentAndCleanup(true);
				bullet->removeFromParentAndCleanup(true);
			}
		}
		
	}
	
}

//判断怪物是否超出了边界
bool Monster::isOut()
{
	Point point = this->getPosition();
	//当怪物完全出了屏幕的时候就移除掉
	if(point.x == 200)
	{
		return true;
	}
	return false;
}

void Monster::move(float tm)
{
	//设置怪物的坐标，使怪物一直向左走，每帧移动的单位是一个像素
	this->setPosition(ccpAdd(this->getPosition(),Vec2(-3,0)));
}

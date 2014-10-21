#include "Bullet.h"
#include "BulletManager.h"

bool Bullet::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Sprite::initWithFile("bullet.png"));

		m_winSize = Director::getInstance()->getWinSize();

		this->scheduleUpdate();

		bRet = true;
	}
	while(0);

	return bRet;
}

//判断子弹是否出界
void Bullet::update(float tm)
{
	if(this->isOut())
	{
		//出界就从父节点中移除
		this->removeFromParentAndCleanup(true);
		//出界就从数组中移除出去
		BulletManager::sharedBulletManager()->getBulletArray()->removeObject(this);
	}
}

bool Bullet::isOut()
{
	Point point = this->getPosition();
	//子弹可能从各个方向发射，所以进行如下的判断
	if(point.x > m_winSize.width || point.y > m_winSize.height)
	{
		return true;
	}
	return false;
}
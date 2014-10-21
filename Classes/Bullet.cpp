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

//�ж��ӵ��Ƿ����
void Bullet::update(float tm)
{
	if(this->isOut())
	{
		//����ʹӸ��ڵ����Ƴ�
		this->removeFromParentAndCleanup(true);
		//����ʹ��������Ƴ���ȥ
		BulletManager::sharedBulletManager()->getBulletArray()->removeObject(this);
	}
}

bool Bullet::isOut()
{
	Point point = this->getPosition();
	//�ӵ����ܴӸ��������䣬���Խ������µ��ж�
	if(point.x > m_winSize.width || point.y > m_winSize.height)
	{
		return true;
	}
	return false;
}
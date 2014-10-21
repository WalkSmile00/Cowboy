#include "Hero.h"
#include "Bullet.h"
#include "BulletManager.h"

bool Hero::init()
{
	bool bRet = false;
	do
	{
                //���ȳ�ʼ�������init����
		CC_BREAK_IF(!Sprite::init());
		//Ϊ��Ա������ֵ������Ļ�ָ��ָ����ǿ�
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
	auto m_myListener = EventListenerTouchOneByOne::create();			//����һ����������    
	m_myListener->setSwallowTouches(false);							//�����Ƿ����´��ݴ���  
	dispatcher->removeEventListener(m_myListener);
	m_myListener->onTouchBegan = [=](Touch* touch,Event* event)
	{ 
			// ��ȡ����������
			auto loc = Director::getInstance()->convertToGL(touch->getStartLocationInView()); 
			if(loc.x <=140)
			{
				return false;
			}
			//����ӵ�
			Bullet * bullet = Bullet::create();
			//���ӵ��Ŀ�ʼλ������Ϊ������ڵ�����λ��
			bullet->setPosition(this->getPosition());
			//���ӵ���ӵ���������
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
			double d = sqrt(dx * dx + dy * dy);//sqtr:��ƽ����

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
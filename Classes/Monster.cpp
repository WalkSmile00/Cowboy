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
		//��ʼ�������ʱ�����initWithFile()������ߴ���һ��ͼƬ��Դ�������������ʱ��������ͼƬ��
		CC_BREAK_IF(!Sprite::initWithFile("target1.png"));

		//�����Ļ�ĳߴ�
		m_winSize = Director::getInstance()->getWinSize();

		//ÿ��һ֡�͵���move������update����
		this->schedule(schedule_selector(Monster::move));
		this->scheduleUpdate();

		bRet = true;
	}
	while(0);

	return bRet;
}

void Monster::update(float tm)
{
	//�жϹ����Ƿ񳬳��˱߽�
	if(this->isOut())
	{
		//������Ӹ��ڵ����Ƴ�
		this->removeFromParentAndCleanup(true);
		//���ó���״̬Ϊemended
		LayerStatus::sharedLayerStatus()->setLayerStatus(emended);
		//�л�����
		Scene* GOscene  = GameOverLayer:: createScene();
		Director::getInstance()->replaceScene(GOscene);	
	}
	
	//Object * obj;
	Ref* obj = nullptr;
	//���µ���佫ȡ��CCArray�е�ÿ��Ԫ�أ�ȡ������ʱ����CCObject������Ҫת��Ϊ����Ҫ������
	
	CCARRAY_FOREACH(BulletManager::sharedBulletManager()->getBulletArray(),obj)
	{
		Sprite * bullet = (Sprite *)obj;
		//boundingBox()����������һ��CCRect�Ķ�������intersectsRect���������ж�����һ��CCRect��û���ཻ
		if ( getStatus() == emnormal ) 
		{
			if(this->boundingBox().intersectsRect(bullet->boundingBox()))
			{
				//����ӵ��͹����ཻ�ͽ��ӵ����������Ƴ���ȥ
				int m = Score::sharedScore()->getScore();
				m += 100;
				Score::sharedScore()->setScore(m);

				setStatus(embeattacked);
				BulletManager::sharedBulletManager()->getBulletArray()->removeObject(bullet);
				//����ӵ��͹����ཻ�ͽ�������ӵ������������Ƴ�
				this->removeFromParentAndCleanup(true);
				bullet->removeFromParentAndCleanup(true);
			}
		}
		
	}
	
}

//�жϹ����Ƿ񳬳��˱߽�
bool Monster::isOut()
{
	Point point = this->getPosition();
	//��������ȫ������Ļ��ʱ����Ƴ���
	if(point.x == 200)
	{
		return true;
	}
	return false;
}

void Monster::move(float tm)
{
	//���ù�������꣬ʹ����һֱ�����ߣ�ÿ֡�ƶ��ĵ�λ��һ������
	this->setPosition(ccpAdd(this->getPosition(),Vec2(-3,0)));
}

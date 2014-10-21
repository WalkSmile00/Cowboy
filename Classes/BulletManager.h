#ifndef _BULLET_MANAGER_H_
#define _BULLET_MANAGER_H_
#include "cocos2d.h"

using namespace cocos2d;
//���õ������ģʽ
class BulletManager
{
public:
	
	static BulletManager * sharedBulletManager();
	~BulletManager();
	//��ô洢�ӵ�������
	__Array * getBulletArray()
	{
		return m_bulletArray;
	};
	
private:
	//�洢�ӵ�������
	__Array * m_bulletArray;

private:
	bool init();
	BulletManager()
	{
		init();
	};
};
#endif
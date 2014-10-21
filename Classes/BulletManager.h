#ifndef _BULLET_MANAGER_H_
#define _BULLET_MANAGER_H_
#include "cocos2d.h"

using namespace cocos2d;
//采用单例设计模式
class BulletManager
{
public:
	
	static BulletManager * sharedBulletManager();
	~BulletManager();
	//获得存储子弹的数组
	__Array * getBulletArray()
	{
		return m_bulletArray;
	};
	
private:
	//存储子弹的数组
	__Array * m_bulletArray;

private:
	bool init();
	BulletManager()
	{
		init();
	};
};
#endif
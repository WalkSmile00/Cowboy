#include "BulletManager.h"

BulletManager * BulletManager::sharedBulletManager()
{
	static BulletManager bulletManager;
	
	return &bulletManager;
}

bool BulletManager::init()
{
	bool bRet = false;
	do
	{
		this->m_bulletArray = __Array::create();
		this->m_bulletArray->retain();
		bRet = true;
	}
	while(0);

	return bRet;
}

BulletManager::~BulletManager()
{
	//delete this->m_bulletArray;
	this->m_bulletArray->release();
	//delete this->m_bulletManager;
}
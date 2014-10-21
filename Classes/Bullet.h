#ifndef _BULLET_H_
#define _BULLET_H_
#include "cocos2d.h"

using namespace cocos2d;

class Bullet : public Sprite
{
public:
	bool init();
	CREATE_FUNC(Bullet);
	bool isOut();
	void update(float tm);
private:
	Size m_winSize;
};

#endif
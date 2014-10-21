#ifndef _HERO_H
#define _HERO_H
#include "cocos2d.h"

using namespace cocos2d;

class Hero : public Sprite
{
public:
	virtual bool init();
	//以下的宏产生的create方法里边是不能传递参数的
	CREATE_FUNC(Hero);
	//通过这种方法来绑定一个精灵，这是将玩家单独分装为一个类的时候的一种方法
	void bindSprite(Sprite * sprite);

	void fire();

private:
	Sprite * m_sprite;
};

#endif

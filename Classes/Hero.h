#ifndef _HERO_H
#define _HERO_H
#include "cocos2d.h"

using namespace cocos2d;

class Hero : public Sprite
{
public:
	virtual bool init();
	//���µĺ������create��������ǲ��ܴ��ݲ�����
	CREATE_FUNC(Hero);
	//ͨ�����ַ�������һ�����飬���ǽ���ҵ�����װΪһ�����ʱ���һ�ַ���
	void bindSprite(Sprite * sprite);

	void fire();

private:
	Sprite * m_sprite;
};

#endif

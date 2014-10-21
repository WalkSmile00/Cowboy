#ifndef _MONSTER_H_
#define _MONSTER_H_
#include "cocos2d.h"

using namespace cocos2d;

class Monster : public Sprite
{
public:
	enum EM_MonsterStatus 
	{
		emnormal,
		embeattacked
	};
	enum EM_LayerStatus 
	{
		emrunning,
		emended
	};
	bool init();
	CREATE_FUNC(Monster);
	void move(float tm);
	void update(float tm);
	bool isOut();

	inline void setStatus( const int nStatus )
	{
		m_nStatus = nStatus;
	}

	inline int getStatus()
	{
		return m_nStatus;
	}

private:
	Size m_winSize;

	int m_nStatus;
};

#endif
#include "Score.h"

Score * Score::sharedScore()
{
	static Score score;	
	return &score;
}

bool Score::init()
{
	bool bRet = false;
	do
	{
		this->m_score = 0;
		bRet = true;
	}
	while(0);
	return bRet;
}

Score::~Score()
{	
}
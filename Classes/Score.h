#ifndef _SCORE_H_
#define _SCORE_H_
#include "cocos2d.h"

using namespace cocos2d;
//采用单例设计模式
class Score
{
public:
	static Score * sharedScore();
	~Score();
	//获得存储分数
	int  getScore()
	{
		return m_score;
	};
	void setScore( const int n_score)
	{
		m_score = n_score;
	};
private:
	//存储分数
	int  m_score;
private:
	bool init();
	Score()
	{
		init();
	};
};
#endif
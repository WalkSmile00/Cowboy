#ifndef _SCORE_H_
#define _SCORE_H_
#include "cocos2d.h"

using namespace cocos2d;
//���õ������ģʽ
class Score
{
public:
	static Score * sharedScore();
	~Score();
	//��ô洢����
	int  getScore()
	{
		return m_score;
	};
	void setScore( const int n_score)
	{
		m_score = n_score;
	};
private:
	//�洢����
	int  m_score;
private:
	bool init();
	Score()
	{
		init();
	};
};
#endif
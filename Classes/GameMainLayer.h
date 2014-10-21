#ifndef _GAME_MAIN_LAYER_H
#define _GAEM_MAIN_LAYER_H
#include "cocos2d.h"

using namespace cocos2d;

class GameMainLayer : public Layer
{
public:
	enum EM_LayerStatus 
	{
		emrunning,
		emended
	};

	bool init();
	static Scene * createScene();
	CREATE_FUNC(GameMainLayer);
	void addMonster(float tm);
	int getRandomNumber(int start,int end);
	void createScore(float delta);
	void removeAll();
	~GameMainLayer();


private:
	Size m_winSize;
	Label *score_label;
	
};

#endif

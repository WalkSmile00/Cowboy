#include"cocos2d.h"

class GameOverLayer:public cocos2d::Layer
{
public:
	enum EM_LayerStatus 
	{
		emrunning,
		emended
	};
	cocos2d::Label* _label;
	bool init();
	~GameOverLayer();
	static cocos2d::Scene* createScene();
	void menuItemRestartCallback(cocos2d::Ref* pSender);
	void menuBackItemCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(GameOverLayer);
};
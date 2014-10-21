#ifndef _LAYER_STATUS_H_
#define _LAYER_STATUS_H_
#include "cocos2d.h"

using namespace cocos2d;
//采用单例设计模式
class LayerStatus
{
public:
	enum EM_LayerStatus 
	{
		emrunning,
		emended
	};
	static LayerStatus * sharedLayerStatus();
	~LayerStatus();
	//获得场景状态
	void setLayerStatus( const int nStatus )
	{
		L_Status = nStatus;
	}

	int getLayerStatus()
	{
		return L_Status;
	}
private:
	//存储子弹的数组
	int L_Status;
private:
	bool init();
	LayerStatus()
	{
		init();
	};
};
#endif
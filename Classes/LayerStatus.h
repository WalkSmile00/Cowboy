#ifndef _LAYER_STATUS_H_
#define _LAYER_STATUS_H_
#include "cocos2d.h"

using namespace cocos2d;
//���õ������ģʽ
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
	//��ó���״̬
	void setLayerStatus( const int nStatus )
	{
		L_Status = nStatus;
	}

	int getLayerStatus()
	{
		return L_Status;
	}
private:
	//�洢�ӵ�������
	int L_Status;
private:
	bool init();
	LayerStatus()
	{
		init();
	};
};
#endif
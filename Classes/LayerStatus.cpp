#include "LayerStatus.h"

LayerStatus * LayerStatus::sharedLayerStatus()
{
	static LayerStatus layerStatus;
	
	return &layerStatus;
}

bool LayerStatus::init()
{
	bool bRet = false;
	do
	{
		this->L_Status = emended;

		bRet = true;
	}
	while(0);

	return bRet;
}

LayerStatus::~LayerStatus()
{
	
}
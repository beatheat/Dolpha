#pragma once

#include<cocos2d.h>

USING_NS_CC;

class DeathLayer : public Layer
{
public:
	static cocos2d::Layer* createLayer();

	virtual bool init();


	CREATE_FUNC(DeathLayer);
public:
	Sprite *bg;
};



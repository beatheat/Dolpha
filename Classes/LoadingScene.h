#pragma once

#include<cocos2d.h>
#include<string>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#pragma execution_character_set("utf-8")
#endif



USING_NS_CC;
using namespace std;


class BulletManager;
class GameScene;

class LoadingScene : public Scene
{
public:
	static cocos2d::Scene* createScene(const char *filename,int num);

	virtual bool init();

	CREATE_FUNC(LoadingScene);
public:
	string filename;
	bool isload;

	Sprite *cactus;

	Scene *gamescene;
	BulletManager *data;

	int scene_num;
};



#pragma once

#include<cocos2d.h>

#include<vector>
#include<map>

#include"MemoryPool.h"
#include"Particle.h"

#include<ui\UIButton.h>


class Joystick;
class Movject;
class Random;
class Player;
class BulletManager;


class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene(BulletManager *bulletmanager, int scene_num);

	virtual bool init();

	//void Release();
	//void menuCloseCallback(cocos2d::Ref* pSender);
	~GameScene();

	CREATE_FUNC(GameScene);

public:
	bool is_paused = false;
	cocos2d::ui::Button* menu_button;
private:

	Joystick *joystick;
	
	cocos2d::Layer *pause_layer;

	Player *player;
	BulletManager *bullet_manager;

	Random *random;
	MemoryPool *bg_pool;
	std::vector<Movject*> bg_tokens;

	cocos2d::Label *label;
	
	int scene_num;
	int frame;
	
};

typedef std::vector<Movject*> BulletList;

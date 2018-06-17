#pragma once

#include<cocos2d.h>
#include<vector>
#include<string>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#pragma execution_character_set("utf-8")
#endif


USING_NS_CC;

class BulletManager;
class AnimationSprite;
class SwipeGesture;

class SelectData
{
public:
	std::string map;
	Sprite *thumbnail;
	Sprite *imgframe;
	Color3B color;
	Label *name;
	Label *text;
	Label *level;
	Label *page;

	float thumbnail_y;
private:
	float saved_x;
public:
	void SetVisible(bool visible)
	{
		thumbnail->setVisible(visible);
		name->setVisible(visible);
		text->setVisible(visible);
		imgframe->setVisible(visible);
		level->setVisible(visible);
		page->setVisible(visible);
	}
	void SetSwipePosition(float x)
	{
		thumbnail->setPosition(Vec2(saved_x + x, thumbnail->getPosition().y));
		name->setPosition(Vec2(saved_x + x, name->getPosition().y));
		text->setPosition(Vec2(saved_x + x, text->getPosition().y));
		imgframe->setPosition(Vec2(saved_x + x, imgframe->getPosition().y));
		level->setPosition(Vec2(saved_x - 135 + x, level->getPosition().y));
		page->setPosition(Vec2(saved_x + x, page->getPosition().y));
	}

	void MoveOwnPosition()
	{
		thumbnail->runAction(MoveTo::create(0.2f, Vec2(saved_x, thumbnail_y)));
		name->runAction(MoveTo::create(0.2f, Vec2(saved_x, name->getPosition().y)));
		text->runAction(MoveTo::create(0.2f, Vec2(saved_x, text->getPosition().y)));
		imgframe->runAction(MoveTo::create(0.2f, Vec2(saved_x, imgframe->getPosition().y)));
		level->runAction(MoveTo::create(0.2f, Vec2(saved_x-135, level->getPosition().y)));
		page->runAction(MoveTo::create(0.2f, Vec2(saved_x, page->getPosition().y)));
	}

	void SetPosition(float x)
	{
		saved_x = x;
		thumbnail->setPosition(Vec2(x, thumbnail_y));
		name->setPosition(Vec2(x, name->getPosition().y));
		text->setPosition(Vec2(x, text->getPosition().y));
		imgframe->setPosition(Vec2(x, imgframe->getPosition().y));
		level->setPosition(Vec2(x-135, level->getPosition().y));
		page->setPosition(Vec2(x , page->getPosition().y));
	}

	void SetSavePosition(float x)
	{
		saved_x = x;
	}
};

class MenuScene : public Scene
{
public:
	static cocos2d::Scene* createScene(int select);

	virtual bool init();

	~MenuScene();

	//void menuCloseCallback(cocos2d::Ref* pSender);

public:
	Size winsize;

	Label *start;
	AnimationSprite *bg, *bg2;
	AnimationSprite *bg_star, *bg2_star;
	Sprite *aurora;

	SwipeGesture *swipe;
	bool selecting;

	int select_num;

	int frame;

	std::vector<SelectData*> select_data;

public:
	void LoadJson();
};



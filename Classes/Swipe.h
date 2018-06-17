#pragma once

#include"cocos2d.h"

#include<vector>

USING_NS_CC;

using namespace std;

enum Swipe {
	 RIGHT, UP, LEFT, DOWN
};

class SwipeGesture : public cocos2d::Layer
{
public:
	static Layer* createLayer();

	virtual bool init();

	CREATE_FUNC(SwipeGesture);
private:
	Vec2 init_pos, current_pos;

	Vec2 swipe_vec;
	Vec2 last_vec;
	Swipe dir;

	bool is_start;
	bool is_end;
	bool is_swiping;
public:
	Vec2 GetSwipeVector();
	Vec2 GetLastSwipeVector();
	Swipe GetDirection();

	bool isStart();
	bool isEnd();
	bool isSwiping();

	void update(float dt);

	bool onTouchBegan(Touch* t, Event *e);
	void onTouchMoved(Touch* t, Event *e);
	void onTouchEnded(Touch* t, Event *e);
	void onTouchCancelled(Touch* t, Event *e);
};



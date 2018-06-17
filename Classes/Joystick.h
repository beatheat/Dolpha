#pragma once

#include"cocos2d.h"

#include<vector>

USING_NS_CC;

using namespace std;

class Joystick : public cocos2d::Layer
{
public:
	static Layer* createLayer();

	virtual bool init();

	CREATE_FUNC(Joystick);

	EventListenerTouchAllAtOnce *listener;
	Sprite *jsBorder, *jsPoint;
	Sprite *actionButton1, *actionButton2;

	bool isTouched = false;
	bool isCenter = false;

	float moveAngle = 0;
	float radAngle = 0;

	float jsX = 0, jsY = 0;
	float jsOriginX = 0, jsOriginY = 0;

	int joystickId = -1;
	int button1Id = -1, button2Id = -1;

	bool isPressedA = false;
	bool isPressedB = false;

	bool isClickedA = false;
	bool isClickedB = false;

	bool isClickedA_f = false;
	bool isClickedB_f = false;

	bool isLeavedA = false;
	bool isLeavedB = false;

public:
	void SetJoystickCenter();
	int GetNWayDirection(int n);

	void update();

	void onTouchesBegan(vector<Touch*> t, Event *e);
	void onTouchesMoved(vector<Touch*> t, Event *e);
	void onTouchesEnded(vector<Touch*> t, Event *e);
};



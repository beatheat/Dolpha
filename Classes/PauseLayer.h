#pragma once

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#pragma execution_character_set("utf-8")
#endif


#include<cocos2d.h>
#include<ui\UIButton.h>
#include<ui\UISlider.h>

class PauseLayer : public cocos2d::Layer
{
public:
	static cocos2d::Layer* createLayer();

	virtual bool init();

	CREATE_FUNC(PauseLayer);
public:
	cocos2d::Sprite *panel;

	cocos2d::ui::Button *btn_resume;
	cocos2d::ui::Button *btn_exit;

	cocos2d::Label *lb_resume;
	cocos2d::Label *lb_exit;

	cocos2d::ui::Slider *sl_bg;
	cocos2d::ui::Slider *sl_se;

	cocos2d::Label *lb_bg;
	cocos2d::Label *lb_se;

	bool do_fade;
	float alpha;

	int scene_num;

	void update(float dt);
	void Init();

};



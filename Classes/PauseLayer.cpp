#include "PauseLayer.h"

#include"GameScene.h"
#include"MenuScene.h"

#include"Volumer.h"


USING_NS_CC;
//using namespace cocos2d::ui;

Layer* PauseLayer::createLayer()
{
	return PauseLayer::create();
}

bool PauseLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto filter = Sprite::create("bg.png");
	filter->setPosition(Director::getInstance()->getWinSize().width / 2,
		Director::getInstance()->getWinSize().height / 2);
	filter->setScale(2.f, 2.f);
	filter->setOpacity(190);
	filter->setLocalZOrder(23);
	this->addChild(filter);

	panel = Sprite::create("panel.png");
	panel->getTexture()->setAliasTexParameters();
	panel->setPosition(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2);
	panel->setScale(4.f, 4.f);
	panel->setOpacity(0);
	panel->setLocalZOrder(23);
	this->addChild(panel);

	float button_y = Director::getInstance()->getWinSize().height / 2 + panel->getBoundingBox().size.height / 2 - 125;

	btn_resume = ui::Button::create("panel_button.png", "panel_button_pressed.png");
	btn_resume->setScale(4.f, 4.f);
	btn_resume->setLocalZOrder(23);
	btn_resume->setOpacity(0);
	btn_resume->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, button_y));
	btn_resume->addTouchEventListener([&](Ref *sender, ui::Widget::TouchEventType type) {
		static bool out = false;
		if (type == ui::Widget::TouchEventType::BEGAN)
		{
			lb_resume->setColor(Color3B(67, 136, 143));
			lb_resume->runAction(MoveBy::create(0, Vec2(3, -3)));
			Volumer::GetInstance()->PlaySE("se/button.ogg");
		}
		else if (type == ui::Widget::TouchEventType::MOVED)
		{
			auto btn = static_cast<ui::Button*>(sender);
			Vec2 pos = btn->getTouchMovePosition();
			Size size = btn->getBoundingBox().size;
			if (!out && (
				pos.x > btn->getPosition().x + size.width / 2 || pos.x < btn->getPosition().x - size.width / 2 ||
				pos.y > btn->getPosition().y + size.height / 2 || pos.y < btn->getPosition().y - size.height / 2)) {
				lb_resume->setColor(Color3B(172, 229, 235));
				lb_resume->runAction(MoveBy::create(0, Vec2(-3, 3)));
				out = true;
			}
		}
		else if(type == ui::Widget::TouchEventType::ENDED || type== ui::Widget::TouchEventType::CANCELED)
		{
			lb_resume->setColor(Color3B(172, 229, 235));
			if(!out)
				lb_resume->runAction(MoveBy::create(0, Vec2(-3, 3)));
			out = false;
		}
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			this->setVisible(false);
			static_cast<GameScene*>(_parent)->is_paused = false;
			static_cast<GameScene*>(_parent)->menu_button->setEnabled(true);
		}
	});
	this->addChild(btn_resume);

	lb_resume = Label::createWithBMFont("fonts/gulim13.fnt", "계속하기");
	lb_resume->setScale(3.f, 3.f);
	lb_resume->getFontAtlas()->setAliasTexParameters();
	lb_resume->setLocalZOrder(23);
	lb_resume->setOpacity(0);
	lb_resume->setColor(Color3B(172, 229, 235));
	lb_resume->setPosition(Director::getInstance()->getWinSize().width / 2, button_y);
	this->addChild(lb_resume);

	button_y -= 40 + btn_resume->getBoundingBox().size.height / 2;

	btn_exit = ui::Button::create("panel_button.png", "panel_button_pressed.png");
	btn_exit->setScale(4.f, 4.f);
	btn_exit->setLocalZOrder(23);
	btn_exit->setOpacity(0);
	btn_exit->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, button_y));
	btn_exit->addTouchEventListener([&](Ref *sender, ui::Widget::TouchEventType type) {
		static bool out = false;
		if (type == ui::Widget::TouchEventType::BEGAN)
		{
			lb_exit->setColor(Color3B(67, 136, 143));
			lb_exit->runAction(MoveBy::create(0, Vec2(3, -3)));
			Volumer::GetInstance()->PlaySE("se/button.ogg");
		}
		else if (type == ui::Widget::TouchEventType::MOVED)
		{
			auto btn = static_cast<ui::Button*>(sender);
			Vec2 pos = btn->getTouchMovePosition();
			Size size = btn->getBoundingBox().size;
			if (!out && (
				pos.x > btn->getPosition().x + size.width / 2 || pos.x < btn->getPosition().x - size.width / 2 ||
				pos.y > btn->getPosition().y + size.height / 2 || pos.y < btn->getPosition().y - size.height / 2)) {
				lb_exit->setColor(Color3B(172, 229, 235));
				lb_exit->runAction(MoveBy::create(0, Vec2(-3, 3)));
				out = true;
			}
		}
		else if (type == ui::Widget::TouchEventType::ENDED || type == ui::Widget::TouchEventType::CANCELED)
		{
			lb_exit->setColor(Color3B(172, 229, 235));
			if (!out)
				lb_exit->runAction(MoveBy::create(0, Vec2(-3, 3)));
			out = false;
		}
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			auto scene = MenuScene::createScene(scene_num);
			auto fade = TransitionFade::create(0.6f, scene);
			Director::getInstance()->replaceScene(fade);
			Volumer::GetInstance()->PauseBG("bgm/ingame.mp3");
			//AudioEngine::end
		}
	});
	this->addChild(btn_exit);

	lb_exit = Label::createWithBMFont("fonts/gulim13.fnt", "그만하기");
	lb_exit->setScale(3.f, 3.f);
	lb_exit->getFontAtlas()->setAliasTexParameters();
	lb_exit->setLocalZOrder(23);
	lb_exit->setOpacity(0);
	lb_exit->setColor(Color3B(172, 229, 235));
	lb_exit->setPosition(Director::getInstance()->getWinSize().width / 2, button_y);
	this->addChild(lb_exit);

	button_y -= 50 + btn_exit->getBoundingBox().size.height / 2;

	sl_se = ui::Slider::create();
	sl_se->loadBarTexture("slider.png");
	sl_se->loadSlidBallTextures("sliderball.png");
	sl_se->loadProgressBarTexture("slideprogress.png");
	sl_se->setPercent(Volumer::GetInstance()->GetVolumeSE() * 100);
	sl_se->setLocalZOrder(23);
	sl_se->setOpacity(0);
	sl_se->setScale(4.f, 4.f);
	sl_se->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2 + 30, button_y));
	sl_se->addEventListener([&](Ref *ref,ui::Slider::EventType type){
		if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED) {
			ui::Slider* slider = static_cast<ui::Slider*>(ref);
			float per = slider->getPercent() / 100.f;
			Volumer::GetInstance()->SetVolumeSE(per);
		}
		if (type == ui::Slider::EventType::ON_SLIDEBALL_UP)
		{
			Volumer::GetInstance()->PlaySE("se/ddiyong.ogg");
		}
	});
	this->addChild(sl_se);

	lb_se = Label::createWithBMFont("fonts/gulim13.fnt", "효과음");
	lb_se->setScale(3.f, 3.f);
	lb_se->getFontAtlas()->setAliasTexParameters();
	lb_se->setLocalZOrder(23);
	lb_se->setOpacity(0);
	lb_se->setColor(Color3B(172, 229, 235));
	lb_se->setPosition(Director::getInstance()->getWinSize().width / 2 - 110, button_y);
	this->addChild(lb_se);

	button_y -= 50 + sl_se->getBoundingBox().size.height / 2;

	sl_bg = ui::Slider::create();
	sl_bg->loadBarTexture("slider.png");
	sl_bg->loadSlidBallTextures("sliderball.png");
	sl_bg->loadProgressBarTexture("slideprogress.png");
	sl_bg->setPercent(Volumer::GetInstance()->GetVolumeBG() * 100);
	sl_bg->setLocalZOrder(23);
	sl_bg->setOpacity(0);
	sl_bg->setScale(4.f, 4.f);
	sl_bg->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2 + 30, button_y));
	sl_bg->addEventListener([&](Ref *ref, ui::Slider::EventType type) {
		if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED) {
			ui::Slider* slider = static_cast<ui::Slider*>(ref);
			float per = slider->getPercent() / 100.f;
			Volumer::GetInstance()->SetVolumeBG(per);
		}
		//if (type == Slider::EventType::ON_SLIDEBALL_UP)
		//{
		//	Volumer::GetInstance()->PlayBG("se/ddiyong.ogg");
		//}
	});
	this->addChild(sl_bg);

	lb_bg = Label::createWithBMFont("fonts/gulim13.fnt", "배경음");
	lb_bg->setScale(3.f, 3.f);
	lb_bg->getFontAtlas()->setAliasTexParameters();
	lb_bg->setLocalZOrder(23);
	lb_bg->setOpacity(0);
	lb_bg->setColor(Color3B(172, 229, 235));
	lb_bg->setPosition(Director::getInstance()->getWinSize().width / 2 - 110, button_y);
	this->addChild(lb_bg);

	return true;
}

void PauseLayer::Init()
{
	panel->setOpacity(0);

	btn_resume->setOpacity(0);
	btn_exit->setOpacity(0);

	lb_resume->setOpacity(0);
	lb_exit->setOpacity(0);

	sl_se->setOpacity(0);
	lb_se->setOpacity(0);

	sl_bg->setOpacity(0);
	lb_bg->setOpacity(0);

	//this->schedule(CC_CALLBACK_1(PauseLayer::Fade, this), "fade");
	this->scheduleUpdate();
}

void PauseLayer::update(float dt)
{
	panel->setOpacity(alpha);

	btn_resume->setOpacity(alpha);
	btn_exit->setOpacity(alpha);

	lb_resume->setOpacity(alpha);
	lb_exit->setOpacity(alpha);

	sl_se->setOpacity(alpha);
	lb_se->setOpacity(alpha);

	sl_bg->setOpacity(alpha);
	lb_bg->setOpacity(alpha);

	alpha += 9;
	if (alpha > 255) {
		do_fade = false;
		alpha = 0;
		this->unscheduleUpdate();
	}
}
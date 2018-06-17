#include"DeathLayer.h"


Layer* DeathLayer::createLayer()
{
	return DeathLayer::create();
}


bool DeathLayer::init()
{

	if (!Layer::init()) {
		return false;
	}

	this->setLocalZOrder(30);

	bg = Sprite::create("bg.png");
	bg->setPosition(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2);
	bg->setOpacity(0);
	bg->setScale(2.f, 2.f);
	this->addChild(bg);

	this->schedule([&](float dt) {
		bg->setOpacity(bg->getOpacity() + 3);
		if (bg->getOpacity() >= 220)
			this->unschedule("death");
	}, 0, CC_REPEAT_FOREVER, 1.8f, "death");



	return true;
}
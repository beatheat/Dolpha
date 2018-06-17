#include"Joystick.h"

#define JOYSMARGIN_X 30
#define JOYSMARGIN_Y 15

Layer* Joystick::createLayer()
{
	return Joystick::create();
}

bool Joystick::init()
{
	if (!Layer::init())
	{
		return false;
	}

	radAngle = moveAngle = 0;

	auto jsPanel = Sprite::create("joyPanel6.png");
	jsPanel->setScale(2.f*2, 2.5f*2);
	jsPanel->setPosition(jsPanel->getBoundingBox().size.width / 2.0f,
	jsPanel->getBoundingBox().size.height / 2.0f);
	//jsPanel->setOpacity(200);
	jsPanel->setLocalZOrder(15);
	this->addChild(jsPanel);

	jsBorder = Sprite::create("joyBack.png");
	jsBorder->setScale(2.5f, 2.5f);
	jsOriginX = (jsBorder->getBoundingBox().size.width / 2.0f) + JOYSMARGIN_X;
	jsOriginY = (jsBorder->getBoundingBox().size.height / 2.0f) + JOYSMARGIN_Y;
	jsBorder->setPosition(jsOriginX, jsOriginY);
	jsBorder->setLocalZOrder(20);
	jsBorder->setOpacity(90);
	this->addChild(jsBorder);

	jsPoint = Sprite::create("button-red.png");
	jsPoint->setScale(2.8, 2.8f);
	jsPoint->setPosition(jsOriginX, jsOriginY);
	jsPoint->setLocalZOrder(21);
	this->addChild(jsPoint);


	actionButton1 = Sprite::create("button.png");
	actionButton1->setPosition(this->getContentSize().width - actionButton1->getContentSize().width / 2.0f - 130, actionButton1->getContentSize().height / 2.0f + 50);
	actionButton1->setLocalZOrder(15);
	actionButton1->setScale(2.5f, 2.5f);
	this->addChild(actionButton1);

	actionButton2 = Sprite::create("button.png");
	actionButton2->setPosition(this->getContentSize().width - actionButton2->getContentSize().width / 2.0f - 60, actionButton2->getContentSize().height / 2.0f + 120);
	actionButton2->setLocalZOrder(15);
	actionButton2->setScale(2.5f, 2.5f);
	this->addChild(actionButton2);

	listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(Joystick::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(Joystick::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(Joystick::onTouchesEnded, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void Joystick::update()
{
	isClickedA = isClickedB = false;
	isLeavedA = isLeavedB = false;
}

int Joystick::GetNWayDirection(int n)
{
	int interval = 360 / n;
	float moveAngle = this->moveAngle > 0 ? this->moveAngle : 360 + this->moveAngle;
	float start = 90 - interval / 2.0f;
	while (start - interval > 0) start -= interval;

	return ((int)(moveAngle + start)%360 / interval) % 8 * interval;
}

void Joystick::SetJoystickCenter()
{
	jsPoint->setPosition(jsOriginX, jsOriginY);
}


void Joystick::onTouchesBegan(vector<Touch*> touches, Event *e)
{
	for (const auto &t : touches) {
		if (!isTouched) {

			int x1 = t->getLocation().x;
			int y1 = t->getLocation().y;
			if ((t->getLocation().x - jsOriginX) * (t->getLocation().x - jsOriginX) +
				(t->getLocation().y - jsOriginY) * (t->getLocation().y - jsOriginY) <
				(jsBorder->getBoundingBox().size.width / 2.0f) * (jsBorder->getBoundingBox().size.width / 2.0f))
			{
				isTouched = true;
				isCenter = false;
				joystickId = t->getID();

				if ((t->getLocation().x - jsOriginX) * (t->getLocation().x - jsOriginX) +
					(t->getLocation().y - jsOriginY) * (t->getLocation().y - jsOriginY) <
					(jsBorder->getBoundingBox().size.width / 10.0f) * (jsBorder->getBoundingBox().size.width / 10.0f)) {
					isCenter = true;
				}
				else
				{
					jsPoint->setVisible(true);
					jsX = t->getLocation().x;
					jsY = t->getLocation().y;
					jsPoint->setPosition(jsX, jsY);

					radAngle = atan2(jsY - jsBorder->getPositionY(), jsX - jsBorder->getPositionX());
					moveAngle = CC_RADIANS_TO_DEGREES(radAngle);
				}
			}
		}
		if ((t->getLocation().x - actionButton1->getPositionX()) * (t->getLocation().x - actionButton1->getPositionX()) +
			(t->getLocation().y - actionButton1->getPositionY()) * (t->getLocation().y - actionButton1->getPositionY()) <
			(actionButton1->getBoundingBox().size.width / 2.0f * 3.0f/2.0f) * (actionButton1->getBoundingBox().size.width / 2.0f * 3.0f / 2.0f) && !isClickedA_f)
		{
			isPressedA = true;
			isClickedA = true;
			isClickedA_f = true;
			button1Id = t->getID();
			//Device::vibrate(0.05);
		}

		if ((t->getLocation().x - actionButton2->getPositionX()) * (t->getLocation().x - actionButton2->getPositionX()) +
			(t->getLocation().y - actionButton2->getPositionY()) * (t->getLocation().y - actionButton2->getPositionY()) <
			(actionButton2->getBoundingBox().size.width / 2.0f * 3.0f / 2.0f) * (actionButton2->getBoundingBox().size.width / 2.0f * 3.0f / 2.0f) && !isClickedB_f)
		{
			isPressedB = true;
			isClickedB = true;
			isClickedB_f = true;
			button2Id = t->getID();
			//Device::vibrate(0.05);
		}
	}
}

void Joystick::onTouchesMoved(vector<Touch*> touches, Event *e)
{
	for (const auto &t : touches) {
		if (isTouched &&
			(t->getLocation().x - jsOriginX) * (t->getLocation().x - jsOriginX) +
			(t->getLocation().y - jsOriginY) * (t->getLocation().y - jsOriginY) >
			(jsBorder->getBoundingBox().size.width / 10.0f) * (jsBorder->getBoundingBox().size.width / 10.0f)
			)
		{
			if (t->getID() == joystickId) {
				isCenter = false;

				jsX = t->getLocation().x;
				jsY = t->getLocation().y;


				radAngle = atan2(jsY - jsBorder->getPositionY(), jsX - jsBorder->getPositionX());
				moveAngle = CC_RADIANS_TO_DEGREES(radAngle);

				if ((t->getLocation().x - jsOriginX) * (t->getLocation().x - jsOriginX) +
					(t->getLocation().y - jsOriginY) * (t->getLocation().y - jsOriginY) >=
					(jsBorder->getBoundingBox().size.width / 2.0f) * (jsBorder->getBoundingBox().size.width / 2.0f))
				{
					jsPoint->setPosition(jsOriginX + cos(radAngle) * (jsBorder->getBoundingBox().size.width / 2.0f)
						, jsOriginY + sin(radAngle) * (jsBorder->getBoundingBox().size.width / 2.0f));
				}
				else
					jsPoint->setPosition(jsX, jsY);

			}
		}
	}
}


void Joystick::onTouchesEnded(vector<Touch*> touches, Event *e)
{
	for (const auto &t : touches) {
		if (isTouched) {
			if (t->getID() == joystickId) {
				isTouched = false;
				jsPoint->setPosition(jsOriginX, jsOriginY);
				moveAngle = radAngle = 0;
			}
		}
		if (isClickedA_f) {
			if (t->getID() == button1Id) {
				isPressedA = false;
				isClickedA = false;
				isClickedA_f = false;
				isLeavedA = true;
			}
		}
		if (isClickedB_f) {
			if (t->getID() == button2Id) {
				isPressedB = false;
				isClickedB = false;
				isClickedB_f = false;
				isLeavedB = true;
			}
		}
	}
}


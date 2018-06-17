#include"Swipe.h"

Layer* SwipeGesture::createLayer()
{
	return SwipeGesture::create();
}

bool SwipeGesture::init()
{
	if (!Layer::init())
	{
		return false;
	}

	swipe_vec = Vec2(0, 0);
	last_vec = Vec2(0, 0);

	is_start = false;
	is_end = false;
	is_swiping = false;

	auto listener = EventListenerTouchOneByOne::create();
	//listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(SwipeGesture::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(SwipeGesture::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(SwipeGesture::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(SwipeGesture::onTouchCancelled, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);

	this->scheduleUpdate();
	
	return true;
}

void SwipeGesture::update(float dt)
{
	if (is_swiping)
		swipe_vec = init_pos - current_pos;
	else
		swipe_vec = Vec2(0, 0);
}

Vec2 SwipeGesture::GetSwipeVector()
{
	return swipe_vec;
}

Vec2 SwipeGesture::GetLastSwipeVector()
{
	return last_vec;
}

Swipe SwipeGesture::GetDirection()
{
	int angle = CC_RADIANS_TO_DEGREES(swipe_vec.getAngle());
	if (angle < -45) angle += 360;
	angle += 45;
	return static_cast<Swipe>(angle / 90);
}

bool SwipeGesture::onTouchBegan(Touch* t, Event *e)
{
	init_pos = Vec2(t->getLocation());
	current_pos = Vec2(t->getLocation());
	is_start = true;
	is_end = false;
	is_swiping = true;
	return true;
}

void SwipeGesture::onTouchMoved(Touch* t, Event *e)
{
	current_pos = Vec2(t->getLocation());
	is_start = false;
}

void SwipeGesture::onTouchEnded(Touch* t, Event *e)
{
	last_vec = init_pos - current_pos;
	is_end = true;
	is_swiping = false;
}

void SwipeGesture::onTouchCancelled(Touch *t, Event *e)
{
	onTouchEnded(t, e);
}

bool SwipeGesture::isStart()
{
	return is_start ? !(is_start = false) : false;
}

bool SwipeGesture::isEnd()
{
	return is_end ? !(is_end = false) : false;
}

bool SwipeGesture::isSwiping()
{
	return is_swiping;
}
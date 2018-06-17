#include"Player.h"

#include"Joystick.h"
#include"Func.h"
#include"Particle.h"
#include"MotionBlur.h"
#include"Movject.h"
#include"Bullet.h"
#include"Func.h"

#include"Volumer.h"

Player::Player(const char *filename, Size size, Node *parent) : filename(filename), size(size), parent(parent)
{
	sprite = Sprite::create(filename);
	sprite->getTexture()->setAliasTexParameters();
	sprite->setTextureRect(Rect(0, 6, 24, 24));
	sprite->setScale(2.0f, 2.0f);
	sprite->setLocalZOrder(5);
	sprite->setPosition(Director::getInstance()->getWinSize().width / 2,
		Director::getInstance()->getWinSize().height / 2);

	auto blur = MotionBlur::getInstance()->GetBlurShader();
	auto gp = GLProgramState::create(blur);

	sprite->setGLProgram(blur);
	sprite->setGLProgramState(gp);

	parent->addChild(sprite);

	redbean = Sprite::create("bullet_normal.png");
	//redbean->getTexture()->setAliasTexParameters();
	redbean->setPosition(sprite->getPosition().x,sprite->getPosition().y-4);
	redbean->setLocalZOrder(25);
	redbean->setScale(1.5f, 1.5f);
	redbean->setVisible(false);
	redbean->setTextureRect(Rect(0, 0, 7.5f, 7.5f));

	parent->addChild(redbean);


	particles1 = new ParticleManager("whiteBox.png", 268, 272, 1.5f, 1.6f, 1.8, 2.5, 0, 0, 30, 35, parent);
	particles1->SetColor(Color4B(220, 234, 20, 255), Color4B(255, 0, 0, 150));		   
	particles2 = new ParticleManager("whiteBox.png", 268, 272, 1.5f, 1.6f, 1.8, 2.5, 0, 0, 30, 35, parent);
	particles2->SetColor(Color4B(220, 234, 20, 255), Color4B(255, 0, 0, 150));

	Vec2 pos = sprite->getPosition();
	pos_particle1 = Vec2(2, - sprite->getContentSize().height / 2.0f + 1);
	pos_particle2 = Vec2(-2, - sprite->getContentSize().height / 2.0f + 1);

	slow = 1.0f;
	speed = 1.0f;
	is_moveback = false;

	hypermove = false;
	hypertick = 0;
	reboundtick = 30;
	blurvec = Vec2(0, 0);

	dead = false;
	//====================================

	keys = { false,false,false,false,false };
	auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyPressed = [&](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) keys.up = true;
		if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) keys.down = true;
		if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) keys.right = true;
		if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) keys.left = true;
		if (keyCode == EventKeyboard::KeyCode::KEY_Z && !keys.z)
		{
			//Jan::pressed = true;
			//player->runAction(MoveBy::create(1.0 / 6.0, Point(0, 150)));
		}
	};
	keylistener->onKeyReleased = [&](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) keys.up = false;
		if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) keys.down = false;
		if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) keys.right = false;
		if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) keys.left = false;
	};
	parent->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keylistener, parent);
}

bool Player::Move(Joystick *joystick,BulletList *bullets)
{
	Vec2 loc = sprite->getPosition();

	if (keys.up)    sprite->setPosition(loc.x, loc.y + 5);
	if (keys.down)  sprite->setPosition(loc.x, loc.y - 5);
	if (keys.left)  sprite->setPosition(loc.x - 5, loc.y);
	if (keys.right) sprite->setPosition(loc.x + 5, loc.y);

	//================================

	Vec2 pos = sprite->getPosition();

	if (!dead)
	{

		is_moveback = false;

		pos_prev = pos;
		sprite->setTextureRect(Rect(0, 6, 24, 24));
		blurvec = Vec2(0, 0);

		if (hypermove)
		{
			Sprite *afterimage = Sprite::create(filename);
			afterimage->setPosition(pos);
			afterimage->setScale(2.0f, 2.0f);
			if (hyperdir / 45 == 2 || hyperdir / 45 == 6)
				afterimage->setTextureRect(Rect(0, 6, 24, 24));
			else
				afterimage->setTextureRect(Rect(24 * 2, 6, 24, 24));
			afterimage->setOpacity(200);
			parent->addChild(afterimage);
			jansang.push_back(afterimage);

			pos.x += Math::Cos(hyperdir) * 9;
			pos.y += Math::Sin(hyperdir) * 9;

			if (hyperdir / 45 == 2 || hyperdir / 45 == 6)
				sprite->setTextureRect(Rect(0, 6, 24, 24));
			else
				sprite->setTextureRect(Rect(24 * 2, 6, 24, 24));

			blurvec = -Vec2((pos.x - pos_prev.x) / size.width / 6.f, (pos.y - pos_prev.y) / size.height / 3.f);
			if (blurvec.x > 0) blurvec.x = -blurvec.x;


			hypertick++;

			if (hypertick > 15)
			{

				hypertick = 0;
				reboundtick = 0;
				hypermove = false;

			}
		}
		else
		{
			reboundtick++;
			if (joystick->isTouched && !joystick->isCenter)
			{
				int move = joystick->GetNWayDirection(8) / 45;

				if (move <= 4) // upside
				{
					is_moveback = false;
					speed = 4.5f;
				}
				else //downside
				{
					is_moveback = true;
					speed = 3.5f;
					if (move == 6) // down
						speed = 3;
				}

				if (move == 2 || move == 6)
				{
					sprite->setTextureRect(Rect(0, 6, 24, 24));
					sprite->setFlippedX(false);
				}
				else
				{

					sprite->setTextureRect(Rect(24 * 2, 6, 24, 24));
					sprite->setFlippedX(move <= 2 || move == 7);
				}
				//speed = 9;
				pos.x += Math::Cos(move * 45) * speed * slow;
				pos.y += Math::Sin(move * 45) * speed * slow;

			}
		}

		if (pos.x < size.width / 4)
			pos.x = size.width / 4;
		if (pos.x > Director::getInstance()->getWinSize().width - size.width / 4)
			pos.x = Director::getInstance()->getWinSize().width - size.width / 4;
		if (pos.y < size.height / 2 + 200)
			pos.y = size.height / 2 + 200;
		if (pos.y > Director::getInstance()->getWinSize().height - size.height / 2)
			pos.y = Director::getInstance()->getWinSize().height - size.height / 2;

		//충돌판정==========

		float r1 = redbean->getBoundingBox().size.width / 2;
		for (auto i = bullets->begin(); i != bullets->end(); i++)
		{
			auto bullet = *i;
			Vec2 dpos = bullet->GetSprite()->getPosition() - pos;
			float length = Math::FastSqrt(dpos.dot(dpos));
			float r2 = bullet->GetSprite()->getBoundingBox().size.width / 2;
			//죽는 판정 -- 사망애니메이션 넣자/ 사망 씬넣자
			//if (length < r1 + r2) {
			//	particles1->SetDirection(0, 360);
			//	particles1->SetAngle(0, 360);
			//	particles1->SetScale(2.f, 3.f);
			//	particles1->SetSpeed(0, 2);
			//	particles1->SetLife(60, 120);
			//	particles1->SetColor(Color4B::BLUE, Color4B(50,100,200,220));
			//	particles1->DrawBurst(pos.x, pos.y, 40);

			//	particles2->SetDirection(0, 360);
			//	particles2->SetAngle (0, 360);
			//	particles2->SetScale(2.f, 3.f);
			//	particles2->SetSpeed(0, 2);
			//	particles2->SetLife(60, 120);
			//	particles2->SetColor(Color4B::RED, Color4B(50, 100, 200, 220));
			//	particles2->DrawBurst(pos.x, pos.y, 40);

			//	redbean->setVisible(false);
			//	sprite->setVisible(false);
			//	for (auto i = jansang.begin(); i != jansang.end();) {
			//		(*i)->removeFromParent();
			//		i = jansang.erase(i);
			//	}
			//	dead = true;
			//	break;
			//}
		}

		//================
		sprite->getGLProgramState()->setUniformVec2("u_stepSize", blurvec);
		sprite->setPosition(pos.x, pos.y);
		redbean->setPosition(pos.x, pos.y - 4);

		if (!is_moveback || joystick->isPressedA)
		{
			particles1->SetSpeed(1.8, 2.5);
			particles2->SetSpeed(1.8, 2.5);
		}
		else
		{
			particles1->SetSpeed(3.0, 4.0);
			particles2->SetSpeed(3.0, 4.0);
		}

		if (joystick->isClickedA)
		{
			slow = 0.4f;
			particles1->SetLife(10, 15);
			particles2->SetLife(10, 15);
			redbean->setVisible(true);
		}
		if (joystick->isLeavedA)
		{
			slow = 1.0f;
			particles1->SetLife(25, 30);
			particles2->SetLife(25, 30);
			redbean->setVisible(false);
		}

		if (joystick->isClickedB && !hypermove && reboundtick >= 30)
		{
			hypermove = true;
			hyperdir = !joystick->isTouched ? 90 : joystick->GetNWayDirection(8);
			Volumer::GetInstance()->PlaySE("se/move2.ogg");
		}

		for (auto i = jansang.begin(); i != jansang.end();)
		{
			int opacity = (*i)->getOpacity();
			(*i)->setOpacity(opacity -= 18);
			if (opacity <= 0) {
				(*i)->removeFromParent();
				i = jansang.erase(i);
			}
			else
				i++;
		}


		particles1->Draw(pos.x + pos_particle1.x, pos.y + pos_particle1.y);
		particles2->Draw(pos.x + pos_particle2.x, pos.y + pos_particle2.y);
	}
	particles1->Move();
	particles2->Move();

	return !dead;
}

Sprite* Player::GetSprite()
{
	return sprite;
}
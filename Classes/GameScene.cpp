#include"GameScene.h"

#include"Joystick.h"

#include"Func.h"
#include"Movject.h"
#include"Random.h"
#include"Player.h"
#include"Bullet.h"
#include"PauseLayer.h"
#include"DeathLayer.h"

#include"Volumer.h"


USING_NS_CC;
//using namespace cocos2d::ui;



Scene* GameScene::createScene(BulletManager *bulletmanger, int scene_num)
{
	GameScene *gamescene = GameScene::create();
	gamescene->bullet_manager = bulletmanger;
	gamescene->bullet_manager->SetParent(gamescene);
	static_cast<PauseLayer*>(gamescene->pause_layer)->scene_num = scene_num;
	return gamescene;
}

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto background = Sprite::create("bg.png");
	background->setScale(2.0f, 2.0f);
	float winsize = (float)Director::getInstance()->getWinSize().height;
	float bgsize = (float)background->getContentSize().height*2;
	float bgcenter = (bgsize / 2.0f - (bgsize - winsize) / 2.0f) / bgsize;
	background->setAnchorPoint(Vec2(0.5, bgcenter));
	background->setPosition(Vec2(Director::getInstance()->getWinSize().width/2,
		Director::getInstance()->getWinSize().height/2));
	this->addChild(background);

	joystick = static_cast<Joystick*>(Joystick::createLayer());
	joystick->setLocalZOrder(20);
	this->addChild(joystick);

	pause_layer= PauseLayer::createLayer();
	pause_layer->setLocalZOrder(30);
	pause_layer->setVisible(false);
	this->addChild(pause_layer);

	menu_button = ui::Button::create("menu.png","menu_pressed.png");
	menu_button->setScale(3.f, 3.f);	
	menu_button->setPosition(Vec2(Director::getInstance()->getWinSize().width
		- menu_button->getBoundingBox().size.width + 10,
		Director::getInstance()->getWinSize().height
		- menu_button->getBoundingBox().size.height + 10));
	menu_button->setLocalZOrder(20);
	menu_button->addTouchEventListener([&](Ref *sender, ui::Widget::TouchEventType type)->void
	{
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			Volumer::GetInstance()->PlaySE("se/menu.ogg");

			menu_button->setEnabled(false);
			pause_layer->setVisible(true);
			static_cast<PauseLayer*>(pause_layer)->Init();
			is_paused = true;
		}
	});
	this->addChild(menu_button);

	player = new Player("plane_tr2.png",Size(24,24), this);

	bg_pool = new MemoryPool(sizeof(Movject), 80);
	random = new Random;

	this->schedule([&](float dt) {
		if (!is_paused)
		{
			int range = random->NextInt(8) + 3;
			for (int i = 0; i < range; i++) {
				auto spr = Sprite::create("white_star.png");
				spr->setColor(Color3B(74, 123, 223));
				float size = (float)random->NextInt(30000) / 10000.0f + 1.0f;
				float speed = size * 3;
				spr->setScale(size, size);
				spr->setRotation(random->NextInt(360));
				if (bg_pool->GetSize() > bg_tokens.size())
					bg_tokens.push_back(new(bg_pool) Movject(
						spr, random->NextInt(Director::getInstance()->getWinSize().width),
						Director::getInstance()->getWinSize().height + 10, -90, speed, this, bg_pool));
			}
		}
	}, 0.3, "backgroundMove");

	label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
	label->setPosition(300, 235);
	
	this->addChild(label);

	frame = 5200;

	this->schedule([&](float dt) {
		if (!is_paused)
		{
			

			if (!player->Move(joystick, bullet_manager->GetBullets()) && menu_button->isEnabled()) {
				joystick->getEventDispatcher()->setEnabled(false);
				joystick->SetJoystickCenter();
				menu_button->setEnabled(false);
				auto deathlayer = DeathLayer::create();
				this->addChild(deathlayer);
			}
			joystick->update();

			bullet_manager->Move(frame++, player->GetSprite());

			//label->setString(toString(bg_tokens.size()));

			//background delete
			for (auto iter = bg_tokens.begin(); iter != bg_tokens.end();)
			{
				(*iter)->Move();
				Vec2 pos = (*iter)->GetSprite()->getPosition();
				if (pos.y < 160) {
					Movject::operator delete(*iter, bg_pool);
					iter = bg_tokens.erase(iter);
				}
				else
					iter++;
			}
		}
	}, "mainloop");


	auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyReleased = [&](EventKeyboard::KeyCode keycode, Event *event) {
		if (!is_paused && keycode == EventKeyboard::KeyCode::KEY_BACK) {
			Volumer::GetInstance()->PlaySE("se/menu.ogg");

			menu_button->setEnabled(false);
			pause_layer->setVisible(true);
			static_cast<PauseLayer*>(pause_layer)->Init();
			is_paused = true;
		}

	};

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keylistener, this);
	
	Volumer::GetInstance()->PlayBG("bgm/ingame.mp3", true);

	return true;
}



 
GameScene::~GameScene()
{
	delete bullet_manager;
	delete random;
	delete bg_pool;
}
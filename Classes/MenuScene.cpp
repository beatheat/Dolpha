#include"MenuScene.h"

#include"LoadingScene.h"
#include"AnimationSprite.h"
#include"Swipe.h"
#include"Func.h"
#include"json\document.h"
#include"json\rapidjson.h"
#include"Volumer.h"


using namespace rapidjson;


Scene* MenuScene::createScene(int select)
{
	auto scene = new (std::nothrow) MenuScene;
	if(scene)
		scene->select_num = select;
	if (scene && scene->init())
	{
		scene->autorelease();
		return scene;
	}
	else {
		delete scene;
		scene = nullptr;
		return scene;
	}
}

bool MenuScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	winsize = Director::getInstance()->getWinSize();

	selecting = false;

	LoadJson();
	//select_num = 0;
	select_data[select_num]->SetPosition(winsize.width * 0.5f);
	select_data[select_num]->SetVisible(true);

	if (select_num < select_data.size() - 1)
	{
		select_data[select_num + 1]->SetPosition(winsize.width * 1.5f);
		select_data[select_num + 1]->SetVisible(true);
	}

	if (select_num > 0)
	{
		select_data[select_num - 1]->SetPosition(winsize.width * (-0.5f));
		select_data[select_num - 1]->SetVisible(true);
	}

	bg = AnimationSprite::create("json/star.json");
	bg->setPosition(winsize.width / 2, winsize.height / 2);
	bg->setScale(2.f, 2.f);
	bg->playAnimation("star-small");
	this->addChild(bg);

	bg_star = AnimationSprite::create("json/star.json");
	bg_star->setPosition(winsize.width / 2, winsize.height / 2);
	bg_star->setScale(2.f, 2.f);
	bg_star->playAnimation("star-big");
	this->addChild(bg_star);


	bg2 = AnimationSprite::create("json/star.json");
	bg2->setPosition(winsize.width * 1.5f, winsize.height / 2);
	bg2->setScale(2.f, 2.f);
	bg2->playAnimation("star-small");
	this->addChild(bg2);

	bg2_star = AnimationSprite::create("json/star.json");
	bg2_star->setPosition(winsize.width * 1.5f, winsize.height / 2);
	bg2_star->setScale(2.f, 2.f);
	bg2_star->playAnimation("star-big");
	this->addChild(bg2_star);

	aurora = Sprite::create("bg_aurora.png");
	aurora->setPosition(winsize.width / 2, winsize.height / 2);
	aurora->setScale(2.f, 2.f);
	aurora->setColor(select_data[select_num]->color);
	this->addChild(aurora);

	swipe = static_cast<SwipeGesture*>(SwipeGesture::createLayer());
	this->addChild(swipe);


	auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyReleased = [&](EventKeyboard::KeyCode keycode, Event *event) {
		if (keycode == EventKeyboard::KeyCode::KEY_BACK) {
			Director::getInstance()->end();
			//Director::
		}
	};

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keylistener, this);

	auto touchlistener = EventListenerTouchOneByOne::create();
	touchlistener->onTouchBegan = [&](Touch *t, Event *e)->bool {
		Vec2 pos = t->getLocation();
		Vec2 tpos = select_data[select_num]->imgframe->getPosition();
		Size tsize = select_data[select_num]->imgframe->getBoundingBox().size;
		if (pos.x > tpos.x - tsize.width / 2  && pos.x < tpos.x + tsize.width / 2 &&
			pos.y > tpos.y - tsize.height / 2  && pos.y < tpos.y + tsize.height / 2 ) {
			select_data[select_num]->imgframe->setScale(1.7f);
			select_data[select_num]->thumbnail->setScale(8.f * 1.7f / 2.0f);
			selecting = true;
		}
		return true;
	};
	touchlistener->onTouchEnded = [&](Touch *t, Event *e) {
		Vec2 pos = t->getLocation();
		Vec2 tpos = select_data[select_num]->imgframe->getPosition();
		Size tsize = select_data[select_num]->imgframe->getBoundingBox().size;
		if (pos.x > tpos.x - tsize.width / 2 && pos.x < tpos.x + tsize.width / 2 &&
			pos.y > tpos.y - tsize.height / 2 && pos.y < tpos.y + tsize.height / 2) {
			auto scene = LoadingScene::createScene(select_data[select_num]->map.c_str(), select_num);
			auto fade = TransitionFade::create(0.6f, scene);
			Volumer::GetInstance()->PlaySE("se/start.ogg");
			Director::getInstance()->replaceScene(fade);
		}
		select_data[select_num]->imgframe->setScale(2.0f);
		select_data[select_num]->thumbnail->setScale(8.f);
		selecting = false;
	};

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchlistener, this);

	frame = 0;

	this->schedule([&](float dt) {
		Vec2 bg_pos = bg->getPosition();
		Vec2 star_pos = bg_star->getPosition();
		Vec2 bg2_pos = bg2->getPosition();
		Vec2 star2_pos = bg2_star->getPosition();
		bg->setPosition(bg_pos.x - 0.3f, bg_pos.y);
		bg_star->setPosition(star_pos.x - 0.46f, star_pos.y);
		bg2->setPosition(bg2_pos.x - 0.3f, bg_pos.y);
		bg2_star->setPosition(star2_pos.x - 0.46f, star2_pos.y);
		if (bg_pos.x <= -winsize.width / 2) {
			bg->setPosition(winsize.width * 1.5f, winsize.height / 2);
		}

		if (star_pos.x <= -winsize.width / 2) {
			bg_star->setPosition(winsize.width * 1.5f, winsize.height / 2);
		}

		if (bg2_pos.x <= -winsize.width / 2) {
			bg2->setPosition(winsize.width * 1.5f, winsize.height / 2);
		}

		if (star2_pos.x <= -winsize.width / 2) {
			bg2_star->setPosition(winsize.width * 1.5f, winsize.height / 2);
		}

		select_data[select_num]->thumbnail->setPosition(select_data[select_num]->thumbnail->getPosition().x,
			select_data[select_num]->thumbnail->getPosition().y + 8.f / 50.f * (float)((frame / 60) % 2 == 0 ? 1 : -1));

		if (!selecting && swipe->isSwiping())
		{
			select_data[select_num]->SetSwipePosition(-swipe->GetSwipeVector().x);

			if (select_num > 0) {
				select_data[select_num - 1]->SetSwipePosition(-swipe->GetSwipeVector().x);

				select_data[select_num - 1]->thumbnail->setPosition(select_data[select_num - 1]->thumbnail->getPosition().x,
					select_data[select_num - 1]->thumbnail->getPosition().y + 8.f / 50.f * (float)((frame / 60) % 2 == 0 ? 1 : -1));
			}
			if (select_num < select_data.size() - 1) {
				select_data[select_num + 1]->SetSwipePosition(-swipe->GetSwipeVector().x);

				select_data[select_num + 1]->thumbnail->setPosition(select_data[select_num + 1]->thumbnail->getPosition().x,
					select_data[select_num + 1]->thumbnail->getPosition().y + 8.f / 50.f * (float)((frame / 60) % 2 == 0 ? 1 : -1));
			}

			Color3B color_cur = select_data[select_num]->color;
			Color3B color_obj = color_cur;
			float len = abs(swipe->GetSwipeVector().x);
			if (swipe->GetSwipeVector().x < 0 && select_num > 0) {
				color_obj = select_data[select_num - 1]->color;
			}
			else if (swipe->GetSwipeVector().x > 0 && select_num < select_data.size() - 1) {
				color_obj = select_data[select_num + 1]->color;
			}
			color_obj = Color3B(color_cur.r + (color_obj.r - color_cur.r) / winsize.width * len,
				color_cur.g + (color_obj.g - color_cur.g) / winsize.width *len,
				color_cur.b + (color_obj.b - color_cur.b) / winsize.width *len);
			aurora->setColor(color_obj);
		}

		if (swipe->isEnd())
		{
			if (swipe->GetLastSwipeVector().x < -Director::getInstance()->getWinSize().width * 1.f/5.f && select_num > 0) {
				if (select_num < select_data.size() - 1) {
					select_data[select_num + 1]->SetVisible(false);
				}
				select_num--;
				select_data[select_num]->SetSavePosition(Director::getInstance()->getWinSize().width / 2);
				select_data[select_num + 1]->SetSavePosition(Director::getInstance()->getWinSize().width * 1.5f);
				if (select_num  > 0) {
					select_data[select_num - 1]->SetPosition(Director::getInstance()->getWinSize().width * -0.5f);
					select_data[select_num - 1]->SetSavePosition(Director::getInstance()->getWinSize().width * -0.5f);
					select_data[select_num - 1]->SetVisible(true);

				}
			}
			else if (swipe->GetLastSwipeVector().x > Director::getInstance()->getWinSize().width * 1.f / 5.f && select_num < select_data.size() - 1) {
				if (select_num > 0) {
					select_data[select_num - 1]->SetVisible(false);

				}
				select_num++;
				select_data[select_num]->SetSavePosition(Director::getInstance()->getWinSize().width / 2);
				select_data[select_num - 1]->SetSavePosition(Director::getInstance()->getWinSize().width * -0.5f);
				if (select_num  < select_data.size() - 1) {
					select_data[select_num + 1]->SetPosition(Director::getInstance()->getWinSize().width * 1.5f);
					select_data[select_num + 1]->SetSavePosition(Director::getInstance()->getWinSize().width * 1.5f);
					select_data[select_num + 1]->SetVisible(true);

				}
			}

			aurora->runAction(TintTo::create(0.2f, select_data[select_num]->color));

			select_data[select_num]->MoveOwnPosition();
			if (select_num  > 0) {
				select_data[select_num - 1]->MoveOwnPosition();
			}
			if (select_num  < select_data.size() - 1) {
				select_data[select_num + 1]->MoveOwnPosition();
			}
		}
		frame++;
	},"menuloop");

	return true;
}


void MenuScene::LoadJson()
{
	string file = FileUtils::getInstance()->getStringFromFile("json/maps.json");
	Document doc;
	doc.Parse(file.c_str());
	int num = 1;
	for (auto i = doc.Begin(); i != doc.End(); i++)
	{
		SelectData *sel = new SelectData;

		sel->map = (*i)["map"].GetString();
		
		sel->color = Color3B((*i)["color"].GetArray()[0].GetInt(), (*i)["color"].GetArray()[1].GetInt(), (*i)["color"].GetArray()[2].GetInt());

		sel->imgframe = Sprite::create("select_frame.png");
		sel->imgframe->setScale(2.f, 2.f);
		sel->imgframe->setLocalZOrder(2);
		sel->imgframe->setPosition(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2 + 190);
		sel->imgframe->setVisible(false);
		this->addChild(sel->imgframe);

		sel->thumbnail = Sprite::create((*i)["thumbnail"].GetString());	
		sel->thumbnail->setPosition(winsize.width / 2, winsize.height / 2 + 190);
		sel->thumbnail_y = winsize.height / 2 + 190;
		sel->thumbnail->setLocalZOrder(2);
		sel->thumbnail->getTexture()->setAliasTexParameters();
		sel->thumbnail->setScale(8.f, 8.f);
		sel->thumbnail->setVisible(false);


		this->addChild(sel->thumbnail);

		sel->name = Label::createWithBMFont("fonts/gulim13.fnt", (*i)["name"].GetString());
		sel->name->setScale(4.5f, 4.5f);
		sel->name->setLocalZOrder(2);
		sel->name->getFontAtlas()->setAliasTexParameters();
		sel->name->setPosition(winsize.width / 2, winsize.height / 2);
		sel->name->setVisible(false);
		this->addChild(sel->name);

		sel->text = Label::createWithBMFont("fonts/gulim13.fnt", (*i)["text"].GetString());
		sel->text->setMaxLineWidth(130);
		sel->text->setLineHeight(17);
		sel->text->setScale(3.f, 3.f);
		sel->text->setLocalZOrder(2);
		sel->text->getFontAtlas()->setAliasTexParameters();
		sel->text->setAnchorPoint(Vec2(0.5f, 1));
		sel->text->setPosition(winsize.width / 2, winsize.height / 2 - 120);
		sel->text->setVisible(false);
		this->addChild(sel->text);

		sel->level = Label::createWithBMFont("fonts/gulim13b_lv.fnt", (*i)["level"].GetString(),TextHAlignment::LEFT);
		sel->level->setMaxLineWidth(130);
		sel->level->setScale(3.2f, 3.2f);
		sel->level->setLocalZOrder(2);
		sel->level->getFontAtlas()->setAliasTexParameters();
		sel->level->setPosition(winsize.width / 2 - 135, winsize.height / 2 - 70);
		sel->level->setVisible(false);
		this->addChild(sel->level);

		sel->page = Label::createWithBMFont("fonts/gulim13.fnt", toString(num) + "/" + toString(doc.GetArray().Size()));
		sel->page->setLocalZOrder(2);
		sel->page->setScale(2.5f, 2.5f);
		sel->page->getFontAtlas()->setAliasTexParameters();
		sel->page->setPosition(winsize.width / 2, 50);
		sel->page->setVisible(false);
		this->addChild(sel->page);


		num++;

		//1.설정창 뒤로가기 시작버튼 사운드 추가 사망모션 인게임메뉴창
		// 240 

		select_data.push_back(sel);
	}
}


MenuScene::~MenuScene()
{
	for (auto i = select_data.begin(); i != select_data.end();)
	{
		delete *i;
		i = select_data.erase(i);
	}
}
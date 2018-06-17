#include"LoadingScene.h"

#include"Bullet.h"
#include"GameScene.h"
#include"Func.h"
#include"Random.h"

Scene* LoadingScene::createScene(const char *filename, int num)
{
	auto loadingscene = LoadingScene::create();
	loadingscene->filename = filename;
	loadingscene->scene_num = num;
	return loadingscene;
}

bool LoadingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	

	cactus = Sprite::create("eyecatch.png");
	cactus->setScale(3.f, 3.f);
	cactus->setPosition(Director::getInstance()->getWinSize().width - cactus->getBoundingBox().size.width / 2 -  20 ,
		cactus->getBoundingBox().size.height / 2 + 28);
	this->addChild(cactus);


	Random rand;
	string tip = FileUtils::getInstance()->getStringFromFile("res/tips.txt");
	auto vtips = StringSplit(tip, '\n');
	tip = "-TIPS-\n" + vtips[rand.NextInt(vtips.size())];

	auto tips = Label::createWithBMFont("fonts/gulim13.fnt",tip,TextHAlignment::CENTER,120);
	tips->setLineHeight(18);
	tips->setScale(3.f, 3.f);
	tips->getFontAtlas()->setAliasTexParameters();
	tips->setPosition(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2);
	this->addChild(tips);

	this->scheduleOnce([&](float dt) {
		Director::getInstance()->getScheduler()->performFunctionInCocosThread([&]() {
			data = new BulletManager(filename, 900);
			isload = true;
			gamescene = GameScene::createScene(data, scene_num);
			gamescene->retain();
		});
	}, 1, "thread");

	this->schedule([&](float dt) {
		cactus->setRotation3D(Vec3(0, cactus->getRotation3D().y + 7, 0));
		if (isload) {
			auto fade = TransitionFade::create(0.6f, gamescene);
			Director::getInstance()->replaceScene(fade);
			gamescene->release();
			isload = false;
		}
			
	},"loading");


	return true;
}
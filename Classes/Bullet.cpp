#include"Bullet.h"

#include"Func.h"
#include"Movject.h"
#include"MemoryPool.h"

using namespace std;

BulletManager::BulletManager(string filename, int pool_size)
{
	string path = CCFileUtils::getInstance()->fullPathForFilename("script/" + filename + ".shoot");
	string stage_data = CCFileUtils::getInstance()->getStringFromFile(path);
	vector<string> line_data;

	//Split by \n
	line_data.push_back("");
	for (int i = 0, li = 0; i < stage_data.size(); i++)
	{
		if (stage_data[i] == '\n') continue;
		if (stage_data[i] == '\r') {
			line_data.push_back("");
			li++;
			continue;
		}
		line_data[li] += stage_data[i];
	}
	line_data.pop_back();

	for (int i = 0; i < line_data.size(); i++)
	{
		auto splits = StringSplit(line_data[i], ' ');
		BulletData data;
		data.pos.x = atof(splits[0].c_str());
		data.pos.y = atof(splits[1].c_str());
		if (data.pos.y > 50000) {
			float dist = 90000 - data.pos.y;
			data.pos.y = Director::getInstance()->getWinSize().height - dist;
		}
		else if (data.pos.y > 10000) {
			float dist = 45000 - data.pos.y;
			data.pos.y = Director::getInstance()->getWinSize().height/2 - dist;
		}

		data.speed = atof(splits[2].c_str());
		data.dir = atof(splits[3].c_str());
		data.acc = atof(splits[4].c_str());
		data.acc_dir = atof(splits[5].c_str());

		data.color = atoi(splits[6].c_str());
		data.bullet_type = atoi(splits[7].c_str());
		data.life = atoi(splits[8].c_str());
		data.tag = atoi(splits[9].c_str());
		data.frame = atoi(splits[10].c_str());
		bullet_data.push_back(data);
	}

	path = CCFileUtils::getInstance()->fullPathForFilename("script/" + filename + ".mani");
	stage_data = CCFileUtils::getInstance()->getStringFromFile(path);

	line_data.clear();

	line_data.push_back("");
	for (int i = 0, li = 0; i < stage_data.size(); i++)
	{
		if (stage_data[i] == '\n') continue;
		if (stage_data[i] == '\r') {
			line_data.push_back("");
			li++;
			continue;
		}
		line_data[li] += stage_data[i];
	}
	line_data.pop_back();

	for (int i = 0; i < line_data.size(); i++)
	{
		auto splits = StringSplit(line_data[i], ' ');
		BulletData data;

		data.type = (BulletData::Type)atoi(splits[0].c_str());
		data.pos.x = atof(splits[1].c_str());
		data.pos.y = atof(splits[2].c_str());
		if (data.pos.y > 80000) {
			float dist = 90000 - data.pos.y;
			data.pos.y = Director::getInstance()->getWinSize().height - dist;
		}
		else if (data.pos.y > 10000) {
			float dist = 45000 - data.pos.y;
			data.pos.y = Director::getInstance()->getWinSize().height / 2 - dist;
		}

		data.speed = atof(splits[3].c_str());
		data.dir = atof(splits[4].c_str());
		data.acc = atof(splits[5].c_str());
		data.acc_dir = atof(splits[6].c_str());

		data.color = atoi(splits[7].c_str());
		data.tag = atoi(splits[8].c_str());
		data.frame = atoi(splits[9].c_str());

		manipulate_data.push_back(data);

	}
	pool = new MemoryPool(sizeof(Movject), pool_size);

	id_generator = 1;
}

BulletManager::BulletManager(string filename,int pool_size, Node *parent) : parent(parent)
{
	BulletManager(filename, pool_size);
}

void BulletManager::Move(int frame, Sprite *player)
{
	if (!once) {
		once = true;
		label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
		label->setPosition(200, 350);
		parent->addChild(label);
	}
	label->setString(toString(bullets.size()));

	//for debug
	if (bullet_data.size() > 0 && bullet_data.front().frame < frame)
	{
		for (auto i = bullet_data.begin(); i != bullet_data.end(); ) {
			if (i->frame < frame)
				i = bullet_data.erase(i);
			else
				break;
		}
	}
	if (manipulate_data.size() > 0 && manipulate_data.front().frame < frame)
	{
		for (auto i = manipulate_data.begin(); i != manipulate_data.end(); ) {
			if (i->frame < frame)
				i = manipulate_data.erase(i);
			else
				break;
		}
	}

	while(bullet_data.size() > 0 && bullet_data.front().frame == frame)
	{
		if (frame == 4950) {
				int a = 1;
		}
		BulletData data = bullet_data.front();
		bullet_data.pop_front();

		//image이름
		Sprite *sprite = Sprite::create("bullet_normal.png");
		//sprite->getTexture()->setAliasTexParameters();
		sprite->setScale(3.0f, 3.0f);
		sprite->setLocalZOrder(10);
		sprite->setTextureRect(Rect(data.color * 7.5, data.bullet_type * 7.5, 7.5, 7.5));

		if (data.dir == TO_PLAYER)
			data.dir = CC_RADIANS_TO_DEGREES((player->getPosition() - data.pos).getAngle());
		if (data.acc_dir == TO_PLAYER) 
			data.acc_dir = CC_RADIANS_TO_DEGREES((player->getPosition() - data.pos).getAngle());
		auto bullet = new(pool) Movject(sprite, data.pos.x, data.pos.y, data.dir, data.speed, data.acc_dir, data.acc, parent, pool, id_generator++, data.tag);
		bullet->SetLife(data.life);
		bullets.push_back(bullet);
		
		auto bullet_list = bullets_bytag.find(data.tag);
		if (bullet_list == bullets_bytag.end()) {
			bullets_bytag.insert(make_pair(data.tag, new map<int, Movject*>));
			bullet_list = bullets_bytag.find(data.tag);
		}
		bullet_list->second->insert(make_pair(bullet->GetId(), bullet));
	}


	while (manipulate_data.size() > 0 && manipulate_data.front().frame == frame)
	{
		BulletData data = manipulate_data.front();
		manipulate_data.pop_front();


		auto bullet_list = bullets_bytag.find(data.tag)->second;
		for (auto i = bullet_list->begin(); i != bullet_list->end(); i++)
		{
			auto bullet = i->second;

			if (data.type == BulletData::Type::MANIPULATE)
			{
				if (data.pos.x != SAME && data.pos.y != SAME)
					bullet->SetPosition(data.pos.x, data.pos.y);
				if (data.speed != SAME && data.dir != SAME)
					bullet->SetSpeedAndDir(data.speed, data.dir);
				else if (data.speed != SAME && data.dir == SAME)
					bullet->SetSpeed(data.speed);
				else if (data.dir != SAME && data.speed == SAME)
					bullet->SetDirection(data.dir);
				else if (data.dir == TO_PLAYER)
					bullet->SetDirection(CC_RADIANS_TO_DEGREES((player->getPosition() - data.pos).getAngle()));
				if (data.acc != SAME && data.acc_dir != SAME)
					bullet->SetAcc(data.acc, data.acc_dir);
				else if (data.acc != SAME && data.acc_dir == SAME)
					bullet->SetAcceleration(data.acc);
				else if (data.acc == SAME && data.acc_dir != SAME)
					bullet->SetAccDirection(data.acc_dir);
				else if (data.acc_dir == TO_PLAYER)
					bullet->SetAccDirection(CC_RADIANS_TO_DEGREES((player->getPosition() - data.pos).getAngle()));
			}
			else if (data.type == BulletData::Type::CSTART)
			{
				bullet->SetCentripetal(data.pos, data.speed, data.dir);
			}
			else if (data.type == BulletData::Type::CSTARTA)
			{
				bullet->SetCentripetalWithASpeed(data.pos, data.speed, data.dir);
			}
			else if (data.type == BulletData::Type::CEND)
			{
				bullet->SetCentripetal(Vec2(-1, -1), 0, 0);
			}
			else if (data.type == BulletData::Type::CMOVE)
			{
				bullet->SetMoveCircle(data.speed, data.dir);
				if (!(data.acc == SAME || data.acc_dir == SAME))
					bullet->SetMoveCircleAcc(data.acc, data.acc_dir);
			}

			//bullet->SetCentripetal(Vec2(240, 480),5,Movject::CLOCK);

			//bullets_bytag 에서도 삭제

			//if (data.color != SAME)
			//	(*i)->GetSprite()->setColor()
		}
	}

	for (auto i = bullets.begin(); i != bullets.end();)
	{
		(*i)->Move();
		if ((*i)->GetSprite()->getPosition().x < -5 || (*i)->GetSprite()->getPosition().x > Director::getInstance()->getWinSize().width + 5 ||
			(*i)->GetSprite()->getPosition().y <  155 || (*i)->GetSprite()->getPosition().y > Director::getInstance()->getWinSize().height + 5)
		{
			if ((*i)->GetTag() == 39) {
				int  a = 1;
			}
			if ((*i)->GetDLife() == false)
			{
				(*i)->SetLife((*i)->GetLife() - 1);
				(*i)->SetDLife(true);
			}
		}
		else
			(*i)->SetDLife(false);

		if ((*i)->GetLife() <= 0)
		{
			bullets_bytag[(*i)->GetTag()]->erase((*i)->GetId());
			Movject::operator delete(*i, pool);
			i = bullets.erase(i);
		}
		else 
			i++;
	}

	//밖으로 나가면 삭제
}

void BulletManager::SetParent(Node *parent)
{
	this->parent = parent;
}

std::vector<Movject*>* BulletManager::GetBullets()
{
	return &bullets;
}

BulletManager::~BulletManager()
{
	for (auto i = bullets.begin(); i != bullets.end(); i++)
		Movject::operator delete(*i, pool);
	for (auto i = bullets_bytag.begin(); i != bullets_bytag.end(); i++)
		delete i->second;
	delete pool;
}


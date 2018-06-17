#pragma once

#include<cocos2d.h>
#include<vector>
#include<map>
#include<string>



USING_NS_CC;

#define SAME 10000
#define TO_PLAYER 10001

class Movject;
class MemoryPool;

class BulletData
{
public:
	enum Type{
		MANIPULATE, CSTART , CEND, CMOVE , CSTARTA
	};
public:
	BulletData& operator=(const BulletData& other)
	{
		if (this != &other) {
			this->pos = other.pos;
			this->speed = other.speed;
			this->dir = other.dir;
			this->acc = other.acc;
			this->acc_dir = other.acc_dir;
			this->bullet_type = other.bullet_type;
			this->color = other.color;
			this->tag = other.tag;
			this->frame = other.frame;
		}
		return *this;
	}

	Vec2 pos;
	//Vec2 move;
	//Vec2 acc;
	float speed;
	float dir;
	float acc;
	float acc_dir;


	int color;
	int bullet_type;
	int tag;
	int frame;
	int life;

	Type type;
};

class BulletManager
{
public:
	BulletManager(std::string filename, int pool_size);
	BulletManager(std::string filename, int pool_size, Node *parent);
	~BulletManager();

	void Move(int frame, Sprite *player);
	void SetParent(Node *parent);

	std::vector<Movject*>* GetBullets();

private:
	Node *parent;
	MemoryPool *pool;

	std::deque<BulletData> bullet_data;
	std::deque<BulletData> manipulate_data;

	std::vector<Movject*> bullets;

	// tag && id
	std::map<int, std::map<int, Movject*>*> bullets_bytag;
	//
	Label *label;
	bool once = false;

	int id_generator;
};

typedef std::vector<Movject*> BulletList;
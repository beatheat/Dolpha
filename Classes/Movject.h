#pragma once

#include "cocos2d.h"

#include"MemNode.h"

USING_NS_CC;

class MemoryPool;

class Movject : public MemNode
{
public:
	Movject(Sprite *sprite, float x, float y, float dir, float speed, Node *parent, MemoryPool *pool,int id=-1, int tag=0);
	Movject(Sprite *sprite, float x, float y, Vec2 dirv, Node *parent, MemoryPool *pool,int id=-1, int tag=0);
	Movject(Sprite *sprite, float x, float y, float dir, float speed, float acc_dir, float acc, Node *parent, MemoryPool *pool,int id=-1 ,int tag=0);
	Movject(Sprite *sprite, float x, float y, Vec2 dirv, Vec2 accv, Node *parent, MemoryPool *pool,int id=-1, int tag=0);

	~Movject();

	void Set(float x, float y, Vec2 dirv, Vec2 accv);

	//center Vec2(-1,-1) to disable
	void SetCentripetal(Vec2 center,float speed, int dir);
	void SetCentripetalWithASpeed(Vec2 center, float aspeed, int dir);
	void SetMoveCircle(float speed, float dir);
	void SetMoveCircleAcc(float speed, float dir);

	void SetSpeedAndDir(float speed, float dir);
	void SetPosition(float x, float y);
	void SetDirection(float dir);
	void SetSpeed(float speed);
	void SetVector(Vec2 vec);
	void SetAccVector(Vec2 acc);
	void SetAcceleration(float acc);

	void SetAccDirection(float acc_dir);
	void SetAcc(float acc, float acc_dir);

	float GetSpeed() { return vec.getLength(); };
	float GetDirection() { return CC_RADIANS_TO_DEGREES(vec.getAngle()); };
	float GetAcc() { return acc.getLength(); };
	float GetAccDir() { return CC_RADIANS_TO_DEGREES(acc.getAngle()); };


	Sprite* GetSprite() { return sprite; };
	int GetTag() { return tag; };
	int GetId() { return id; };

	void SetLife(int life) { this->life = life; };
	int GetLife() { return life; };

	void SetDLife(bool dlife) { this->dlife = dlife; };
	bool GetDLife() { return dlife; };

	void Move();

	void* operator new (size_t n, MemoryPool *pool);
	void operator delete(void *p);
	void operator delete(void *p, MemoryPool *pool);

protected:
	Sprite *sprite;
	Node *parent;

	Vec2 vec;
	Vec2 acc;

	bool oncircle;
	Vec2 oncirclevec;
	float oncircleacc;
	Vec2 circlecenter;

	//
	Vec2 movecircle;
	Vec2 acccircle;

	int tag;
	int id;
	int life;
	bool dlife;
};


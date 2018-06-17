#pragma once

#include<vector>
#include<string>
#include<cocos2d.h>

#include"MemNode.h"
#include"MemoryPool.h"
#include"Random.h"

using namespace std;

USING_NS_CC;

class Random;

class Particle : public MemNode
{
public:
	float speed;
	int life;
	float dir;

	Color4B interval_color;

	Sprite *sprite;

	void* operator new (size_t n, MemoryPool *pool) { return pool->New(n); };
	void operator delete(void *p) { ::operator delete(p); };
	void operator delete(void *p, MemoryPool *pool) {
		//static_cast<Particle*>(p)->~Particle();
		static_cast<Particle*>(p)->sprite->removeFromParent();
		static_cast<MemNode*>(p)->~MemNode();
		return pool->Delete(p);
	};

	Particle(MemoryPool *pool) : MemNode(pool) {};
};

class ParticleManager
{
public:
	ParticleManager(const char *filename, float min_dir, float max_dir, float min_scale, float max_scale, float min_speed, float max_speed,
		float min_angle, float max_angle, float min_life, float max_life, Node *parent);
	~ParticleManager();

	void SetColor(Color4B start, Color4B end);
	void SetLife(float min_life, float max_life);
	void SetAngle(float min_angle, float max_angle);
	void SetDirection(float min_dir, float max_dir);
	void SetSpeed(float min_speed, float max_speed);
	void SetScale(float min_scale, float max_scale);
	void SetVisible(bool visible);

	void DrawBurst(float x, float y, int num);
	void Draw(float x, float y);
	void Move();

private:
	MemoryPool *pool;
	vector<Particle*> particles;
	Random random;

	Node *parent;
	
	string filename;

	float min_dir, max_dir;
	float min_scale, max_scale;
	float min_speed, max_speed;
	float min_angle, max_angle;
	float min_life, max_life;

	Color4B start_color, end_color;
	bool visible;
};
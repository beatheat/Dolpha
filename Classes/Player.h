#pragma once

#include"cocos2d.h"
#include<vector>
#include<string>
#include<map>

USING_NS_CC;
using namespace std;

class Joystick;
class ParticleManager;
class Movject;

typedef std::vector<Movject*> BulletList;

typedef struct _Key {
	bool up, down, left, right, z;
}Key;


class Player
{
public:
	Player(const char *filename, Size size, Node *parent);

	bool Move(Joystick *joystick, BulletList *bullets);
	Sprite* GetSprite();

private:
	string filename;

	Sprite *sprite;
	Sprite *redbean;
	vector<Sprite*> jansang;
	Vec2 pos_prev;
	Node *parent;

	ParticleManager *particles1, *particles2;

	Size size;

	Key keys;

	bool is_moveback;
	float speed, slow;

	bool hypermove;
	int hyperdir;
	int hypertick;
	int reboundtick;
	Vec2 blurvec;

	Vec2 pos_particle1, pos_particle2;

	bool dead;
};
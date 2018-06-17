#include "Movject.h"

#include"Func.h"
#include"MemoryPool.h"


Movject::Movject(Sprite *sprite, float x, float y, float dir, float speed, Node *parent, MemoryPool *pool,int id, int tag)
	: MemNode(pool), sprite(sprite), acc(Vec2(0,0)), oncircle(false), tag(tag), id(id), life(1), dlife(false)
{
	sprite->setPosition(x, y);
	this->parent = parent;
	parent->addChild(sprite);
	this->vec.x = Math::Cos(dir) * speed;
	this->vec.y = Math::Sin(dir) * speed;
}

Movject::Movject(Sprite *sprite, float x, float y, Vec2 dirv, Node *parent, MemoryPool *pool,int id, int tag)
	: MemNode(pool), sprite(sprite), vec(dirv), acc(Vec2(0,0)), oncircle(false), tag(tag), id(id), life(1), dlife(false)
{
	sprite->setPosition(x, y);
	this->parent = parent;
	parent->addChild(sprite);
}

Movject::Movject(Sprite *sprite, float x, float y, float dir, float speed, float acc_dir, float acc, Node *parent, MemoryPool *pool,int id, int tag)
	: MemNode(pool), sprite(sprite), oncircle(false), tag(tag), id(id), life(1), dlife(false)
{
	sprite->setPosition(x, y);
	this->parent = parent;
	parent->addChild(sprite);

	this->vec.x = Math::Cos(dir) * speed;
	this->vec.y = Math::Sin(dir) * speed;
	this->acc.x = Math::Cos(acc_dir) * acc;
	this->acc.y = Math::Sin(acc_dir) * acc;
}

Movject::Movject(Sprite *sprite, float x, float y, Vec2 dirv, Vec2 accv, Node *parent, MemoryPool *pool,int id, int tag)
	: MemNode(pool), sprite(sprite), vec(dirv), acc(accv), oncircle(false), tag(tag), id(id), life(1), dlife(false)
{
	sprite->setPosition(x, y);
	this->parent = parent;
	parent->addChild(sprite);
}

Movject::~Movject()
{
	parent->removeChild(sprite);
}


void Movject::SetPosition(float x, float y)
{
	this->sprite->setPosition(x, y);
}

void Movject::SetSpeedAndDir(float speed, float dir)
{
	vec.x = speed * Math::Cos(dir);
	vec.y = speed * Math::Sin(dir);
}

void Movject::SetDirection(float dir)
{
	float size = vec.getLength();
	vec.x = size * Math::Cos(dir);
	vec.y = size * Math::Sin(dir);
}

void Movject::SetSpeed(float speed)
{
	this->vec.normalize();
	this->vec *= speed;
}

void Movject::SetVector(Vec2 vec)
{
	this->vec = vec;
}

void Movject::SetAccVector(Vec2 acc)
{
	this->acc = acc;
}

void Movject::SetAcc(float acc, float acc_dir)
{
	this->acc.x = acc * Math::Cos(acc_dir);
	this->acc.y = acc * Math::Sin(acc_dir);
}

//0일때 조심!!
void Movject::SetAcceleration(float acc)
{
	//if (this->acc == Vec2::ZERO)
	//	this->acc = Vec2(1, 0);
	this->acc.normalize();
	this->acc *= acc;
}

void Movject::SetAccDirection(float acc_dir)
{
	//if (this->acc == Vec2::ZERO)
	//	this->acc = Vec2(0, 1);
	float size = this->acc.getLength();
	this->acc.x = size * Math::Cos(acc_dir);
	this->acc.y = size * Math::Sin(acc_dir);
}

void Movject::Set(float x, float y, Vec2 dirv, Vec2 accv)
{
	this->sprite->setPosition(x, y);
	this->vec = dirv;
	this->acc = accv;
}

void Movject::SetCentripetal(Vec2 center,float speed, int dir)
{
	oncircle = true;
	if (center == Vec2(-1, -1)) oncircle = false;
	circlecenter = center;
	oncirclevec = (circlecenter - sprite->getPosition());
	oncirclevec = dir * Vec2(-oncirclevec.y, oncirclevec.x).getNormalized() * speed;
	//oncircleacc = oncirclevec.getLength()*oncirclevec.getLength() / (circlecenter - sprite->getPosition()).getLength();
	oncircleacc = speed*speed / (circlecenter - sprite->getPosition()).getLength();

	movecircle = acccircle = Vec2(0, 0);
}

void Movject::SetCentripetalWithASpeed(Vec2 center, float aspeed, int dir)
{
	oncircle = true;
	if (center == Vec2(-1, -1)) oncircle = false;
	circlecenter = center;
	oncirclevec = (circlecenter - sprite->getPosition());
	aspeed = oncirclevec.getLength() * M_PI * 2 * aspeed / 360.f;
	oncirclevec = dir * Vec2(-oncirclevec.y, oncirclevec.x).getNormalized() * aspeed;
	//oncircleacc = oncirclevec.getLength()*oncirclevec.getLength() / (circlecenter - sprite->getPosition()).getLength();
	oncircleacc = aspeed*aspeed / (circlecenter - sprite->getPosition()).getLength();

	movecircle = acccircle = Vec2(0, 0);
}


void Movject::SetMoveCircle(float speed, float dir)
{
	movecircle.x = speed * Math::Cos(dir);
	movecircle.y = speed * Math::Sin(dir);
}

void Movject::SetMoveCircleAcc(float speed, float dir)
{
	acccircle.x = speed * Math::Cos(dir);
	acccircle.y = speed * Math::Sin(dir);
}

void Movject::Move()
{
	Vec2 pos = sprite->getPosition();

	if (oncircle) {
		movecircle += acccircle;
		circlecenter += movecircle;
		pos += movecircle;

		oncirclevec += (circlecenter - pos).getNormalized() * oncircleacc;
		pos += oncirclevec;
	}
	vec += acc;
	pos += vec;
	sprite->setPosition(pos);
	
}


void* Movject::operator new (size_t n, MemoryPool *pool) { return pool->New(n); };
void Movject::operator delete(void *p) { ::operator delete(p); };
void Movject::operator delete(void *p, MemoryPool *pool) {
	static_cast<Movject*>(p)->~Movject();
	static_cast<MemNode*>(p)->~MemNode();
	return pool->Delete(p);
};
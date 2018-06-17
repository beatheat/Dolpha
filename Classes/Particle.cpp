#include"Particle.h"

#include"Func.h"

ParticleManager::ParticleManager(const char *filename, float min_dir, float max_dir,
	float min_scale, float max_scale, float min_speed, float max_speed,
	float min_angle, float max_angle, float min_life, float max_life, Node *parent) :
	filename(filename), min_dir(min_dir), max_dir(max_dir), min_scale(min_scale), max_scale(max_scale),
	min_speed(min_speed), max_speed(max_speed), min_angle(min_angle), max_angle(max_angle),
	min_life(min_life), max_life(max_life), parent(parent),
	start_color(255,255,255,255), end_color(255,255,255,255), visible(true)
{
	pool = new MemoryPool(sizeof(Particle), 500);
};

ParticleManager::~ParticleManager()
{
	for (auto i = particles.begin(); i != particles.end();)
	{
		Particle *p = *i;
		if (p->life <= 0)
		{
			Particle::operator delete(*i, pool);
			i = particles.erase(i);
		}
		else
			i++;
	}
	delete pool;
}

void ParticleManager::Draw(float x,float y)
{
	if (visible)
	{
		Particle *particle = new(pool) Particle(pool);
		particle->sprite = Sprite::create(filename);

		particle->dir =
			static_cast<float>(random.NextInt(static_cast<int>((max_dir - min_dir) * 10))) / 10.0f + min_dir;
		particle->speed =
			static_cast<float>(random.NextInt(static_cast<int>((max_speed - min_speed) * 10))) / 10.0f + min_speed;
		particle->life =
			static_cast<float>(random.NextInt(static_cast<int>((max_life - min_life) * 10))) / 10.0f + min_life;

		particle->sprite->setScale(
			static_cast<float>(random.NextInt(static_cast<int>((max_scale - min_scale) * 10))) / 10.0f + min_scale);
		particle->sprite->setRotation(
			static_cast<float>(random.NextInt(static_cast<int>((max_angle - min_angle) * 10))) / 10.0f + min_angle);

		particle->sprite->setColor(Color3B(start_color));
		particle->sprite->setOpacity(start_color.a);
		particle->interval_color = Color4B((end_color.r - start_color.r) / particle->life,
			(end_color.g - start_color.g) / particle->life, (end_color.b - start_color.b) / particle->life,
			(end_color.a - start_color.a) / particle->life);

		particle->sprite->setPosition(x, y);

		parent->addChild(particle->sprite);

		particles.push_back(particle);
	}
}

void ParticleManager::DrawBurst(float x, float y, int num)
{
	for (int i = 0; i < num; i++)Draw(x, y);
}

void ParticleManager::Move()
{
	for (auto i = particles.begin(); i != particles.end();)
	{
		Particle *p = *i;
		Vec2 pos = p->sprite->getPosition();
		p->sprite->setPosition(pos.x + Math::Cos(p->dir)*p->speed, pos.y + Math::Sin(p->dir)*p->speed);
		Color3B color = p->sprite->getColor();
		Color4B interval = p->interval_color;
		p->sprite->setColor(Color3B(color.r + interval.r, color.g + interval.g, color.b + interval.b));
		p->sprite->setOpacity(p->sprite->getOpacity() + interval.a);
		p->life--;
		if (p->life <= 0)
		{
			Particle::operator delete(*i, pool);
			i = particles.erase(i);
		}
		else
			i++;
	}
}

void ParticleManager::SetColor(Color4B start, Color4B end)
{
	this->start_color = start;
	this->end_color = end;
}

void ParticleManager::SetLife(float min_life, float max_life)
{
	this->min_life = min_life;
	this->max_life = max_life;
}

void ParticleManager::SetDirection(float min_dir, float max_dir)
{
	this->min_dir = min_dir;
	this->max_dir = max_dir;
}

void ParticleManager::SetSpeed(float min_speed, float max_speed)
{
	this->min_speed = min_speed;
	this->max_speed = max_speed;
}

void ParticleManager::SetAngle(float min_angle, float max_angle)
{
	this->min_angle = min_angle;
	this->max_angle = max_angle;
}

void ParticleManager::SetScale(float min_scale, float max_scale)
{
	this->min_scale = min_scale;
	this->max_scale = max_scale;
}

//수정필요
void ParticleManager::SetVisible(bool visible)
{
	this->visible = visible;
	for (auto i = particles.begin(); i != particles.end();) {
		Particle::operator delete(*i, pool);
		i = particles.erase(i);
	}
}
#include "AnimationSprite.h"

#include "json/rapidjson.h"
#include "json/document.h"

USING_NS_CC;
using namespace std;
using namespace rapidjson;

AnimationSprite * AnimationSprite::create(const std::string &json) {
	AnimationSprite *ret = new (std::nothrow) AnimationSprite();
	if (ret && ret->initWithData(json)) {
		ret->autorelease();
		return ret;
	} else {
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

bool AnimationSprite::initWithData(const std::string &json) {
	auto file = FileUtils::getInstance()->getStringFromFile(json);

	Document doc;
	doc.Parse(file.c_str());

	this->initWithFile(doc["sprite"].GetString());
	this->setContentSize(Size(doc["width"].GetInt(), doc["height"].GetInt()));
	this->setTextureRect(Rect(Vec2::ZERO, this->getContentSize()));

	for (auto &i : doc["animation"].GetArray()) {
		auto name = i["name"].GetString();
		int x = i["x"].GetInt(), y = i["y"].GetInt(), len = i["length"].GetInt();
		bool repeat = i["repeat"].GetBool();

		vector<int> speeds;
		for (auto &j : i["speed"].GetArray()) {
			speeds.push_back(j.GetInt());
		}

		_animations[name] = AnimationData(x, y, len, speeds, repeat);
	}

	return true;
}

void AnimationSprite::playAnimation(const string &name) {
	_currentAnimationName = name;

	_tick = 0;
	_index = 0;

	this->continueAnimation();
}

void AnimationSprite::stopAnimation() {
	this->unscheduleUpdate();
	_tick = 0;
	_index = 0;
	_isPause = false;
	_currentAnimationName = "";
}

void AnimationSprite::pauseAnimation() {
	if (!_isPause) {
		this->unscheduleUpdate();
		_isPause = true;
	}
}

void AnimationSprite::continueAnimation() {
	this->scheduleUpdate();
	_isPause = false;
}

void AnimationSprite::update(float dt) {
	auto anim = _animations[_currentAnimationName];

	_tick += 1 * 60.0f * dt;
	if (_tick >= anim._speeds[_index]) {
		this->setTextureRect(Rect(Vec2(anim._x + this->getContentSize().width * _index, anim._y), this->getContentSize()));
		_tick = 0;
		_index += 1;

		/// 애니메이션이 끝났을 때
		if (_index >= anim._length) {
			/// 반복하지 않는 애니메이션인 경우
			if (!anim._repeat) {
				this->stopAnimation();
				return;
			}
			_index = 0;
		}
	}
}
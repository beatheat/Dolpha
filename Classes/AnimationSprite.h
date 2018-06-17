#ifndef _ANIMATION_SPRITE_H_
#define _ANIMATION_SPRITE_H_

#include "cocos2d.h"

class AnimationSprite;

class AnimationData {
public:
	AnimationData() {}

	AnimationData(int x, int y, int len, const std::vector<int> &speeds, bool repeat) : 
		_x(x), _y(y), _length(len), _speeds(speeds), _repeat(repeat) {}

	friend class AnimationSprite;

private:
	int _x, _y, _length;
	bool _repeat;
	std::vector<int> _speeds;

};

class AnimationSprite : public cocos2d::Sprite {
public:
	static AnimationSprite * create(const std::string &json);

	virtual bool initWithData(const std::string &json);

	void playAnimation(const std::string &name);
	void stopAnimation();
	void pauseAnimation();
	void continueAnimation();

	std::string getCurrentAnimationName() const { return _currentAnimationName; }

	void update(float dt) override;

protected:
	std::map<std::string, AnimationData> _animations;

	float _tick = 0;
	int _index = 0;

	std::string _currentAnimationName = "";
	bool _isPause = false;

};

#endif
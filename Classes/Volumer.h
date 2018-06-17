#pragma once


#include<map>
#include<cocos2d.h>
#include<AudioEngine.h>

using namespace std;

USING_NS_CC;

using namespace experimental;

class Volumer
{
public:
	static Volumer* GetInstance();

	void Load();

	void PlaySE(const char *name, bool loop = false);
	void PlayBG(const char *name, bool loop = false);

	void StopSE(const char *name);
	void StopBG(const char *name);

	void PauseSE(const char *name);
	void PauseBG(const char *name);

	void SetVolumeSE(float volume);
	void SetVolumeBG(float volume);

	float GetVolumeSE();
	float GetVolumeBG();
private:
	static Volumer *volumer;

	float se_volume = 1.f, bg_volume = 1.f;

	map<const char*, int> se_ids;
	map<const char*, int> bg_ids;
};
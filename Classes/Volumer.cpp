#include"Volumer.h"

Volumer* Volumer::volumer = nullptr;

Volumer *Volumer::GetInstance()
{
	if (volumer == nullptr)
	{
		volumer = new Volumer();
	}
	return volumer;
}

void Volumer::Load()
{
	AudioEngine::preload("se/move.ogg");
	AudioEngine::preload("se/mainstart.ogg");
	AudioEngine::preload("se/start.ogg");
	AudioEngine::preload("se/menu.ogg");
	AudioEngine::preload("se/button.ogg");

	AudioEngine::preload("bgm/ingame.mp3");
}

void Volumer::PlaySE(const char* name, bool loop)
{

	int id = AudioEngine::play2d(name, loop);
	AudioEngine::setVolume(id, se_volume);
	if (se_ids.find(name) == se_ids.end())
		se_ids.insert(make_pair(name, id));
	else
		se_ids.find(name)->second = id;

}

void Volumer::PlayBG(const char* name, bool loop)
{

	int id = AudioEngine::play2d(name, loop);
	AudioEngine::setVolume(id, bg_volume);
	if (bg_ids.find(name) == bg_ids.end())
		bg_ids.insert(make_pair(name, id));
	else
		bg_ids.find(name)->second = id;
}


void Volumer::StopSE(const char *name)
{
	AudioEngine::stop(se_ids.find(name)->second);
}

void Volumer::StopBG(const char *name)
{
	AudioEngine::stop(bg_ids.find(name)->second);
}

void Volumer::PauseSE(const char *name)
{
	AudioEngine::pause(se_ids.find(name)->second);
}

void Volumer::PauseBG(const char *name)
{
	AudioEngine::pause(bg_ids.find(name)->second);
}


void Volumer::SetVolumeSE(float volume)
{
	this->se_volume = volume;
	for (auto i = se_ids.begin(); i != se_ids.end(); i++) {
		AudioEngine::setVolume(i->second, volume);
	}
}

void Volumer::SetVolumeBG(float volume)
{
	this->bg_volume = volume;
	for (auto i = bg_ids.begin(); i != bg_ids.end(); i++) {
		AudioEngine::setVolume(i->second, volume);
	}
}

float Volumer::GetVolumeSE()
{
	return se_volume;
}

float Volumer::GetVolumeBG()
{
	return bg_volume;
}
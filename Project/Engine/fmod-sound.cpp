#include "fmod-sound.h"

SoundManager* SoundManager::instance = nullptr;
SoundManager* SoundManager::sharedManager()
{
	if (instance == nullptr)
	{
		instance = new SoundManager;
	}
	return instance;
}

void SoundManager::init()
{
	//currentVolume = 100;
	result = System_Create(&pFmod);
	ErrorCheck(result);
	result = pFmod->init(100, FMOD_LOOP_NORMAL, NULL);
	ErrorCheck(result);
}

void SoundManager::loading(std::string path, bool repeat, int index)
{
	if (repeat == true)
	{
		result = pFmod->createSound(path.c_str(), FMOD_LOOP_NORMAL, NULL, &music[index]);
	}
	else
	{
		result = pFmod->createSound(path.c_str(), FMOD_DEFAULT, NULL, &music[index]);
	}
}

void SoundManager::play(int type, bool /*repeat*/)
{
	pFmod->update();
	result = pFmod->playSound(music[type], nullptr, false, &ch[type]);
	result = ch[type]->setVolume(static_cast<float>(currentVolume / 100.f));
}

void SoundManager::stop(int type)
{
	ch[type]->stop();
}

void SoundManager::ErrorCheck(FMOD_RESULT res)
{
	if (res != FMOD_OK)
	{
		exit(-1);
	}
}

void SoundManager::release()
{
	if (instance != nullptr)
	{
		delete instance;
	}
}

void SoundManager::volumeUp()
{
	if (currentVolume < 100)
		currentVolume += 10;
	for (int s = 0; s < static_cast<int>(game_sounds::Count); ++s)
		result = ch[s]->setVolume(static_cast<float>(currentVolume / 100.f));
}

void SoundManager::volumeDown()
{
	if (currentVolume > 0)
		currentVolume -= 10;
	for (int s = 0; s < static_cast<int>(game_sounds::Count); ++s)
		result = ch[s]->setVolume(static_cast<float>(currentVolume / 100.f));
}
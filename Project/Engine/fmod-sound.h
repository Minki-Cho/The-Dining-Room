#pragma once
const int MAX_SOUND_TRACK = 36;

#include <string>
#include <iostream>
#include <fmod.hpp>
#include "../Game/Sound_lists.h"
using namespace FMOD;

class SoundManager 
{
public:
	static SoundManager* instance;
	static SoundManager* sharedManager();
	void init();
	void loading(std::string path, bool repeat,int index);
	void play(int type, bool repeat);
	void stop(int type);
	void ErrorCheck(FMOD_RESULT r);
	void release();
	void volumeUp();
	void volumeDown();
	int getCurrentVolume() { return currentVolume; };
private:
	System* pFmod;
	Channel* ch[MAX_SOUND_TRACK];
	Sound* music[MAX_SOUND_TRACK];
	FMOD_RESULT result;

	int currentVolume{ 50 };
};
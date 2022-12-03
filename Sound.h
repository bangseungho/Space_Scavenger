#pragma once
#include "Object.h"
#include <fmod.hpp>
class Sound : public Object
{
public:
	static FMOD_SYSTEM* SOUND_SYSTEM;
	static FMOD_CHANNEL* MUSIC_CHANNER;

	static float musicVelum;
public:
	Sound();
	~Sound();

public:
	void Update();

public:
	void Load(string _FileName);
	void Play();
	void Stop();
	void RepetPlay();

public:
	FMOD_SOUND* sound;

private:
	const char* fileName;
	bool isLoop;
};


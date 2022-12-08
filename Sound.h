#pragma once
#include "Object.h"
#include <fmod.hpp>

class Sound
{
public:
	static FMOD_SYSTEM* SOUND_SYSTEM;
	FMOD_CHANNEL* MUSIC_CHANNER;

	static float musicVolum;
public:
	Sound();
	~Sound();

public:
	void Update();

public:
	void Load(string _FileName, bool _IsLoop);
	void Play();
	void Stop();
	void SetVolum(float _Volum);

public:
	FMOD_SOUND* sound;

private:
	string fileName;
	bool isLoop;
};

#pragma once
#include "Object.h"
#include <fmod.hpp>

class Sound : public Object
{
public:
	static FMOD_SYSTEM* SOUND_SYSTEM;

	static float musicVolum;
public:
	Sound();
	~Sound();

public:
	void Update();

public:
	void Load(string _FileName) { Load(_FileName, false); };
	void Load(string _FileName, bool _IsLoop);
	void Play();
	void RepeatPlay();
	void Stop();
	void SetVolum(float _Volum);

public:
	FMOD_CHANNEL* MUSIC_CHANNER;
	FMOD_SOUND* sound;

private:
	bool isLoop;
	string fileName;
};

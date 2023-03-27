#pragma once
#include "Object.h"
#include <fmod.hpp>

struct Channel {
	FMOD_CHANNEL* channel;
	float volum;
};

class Sound : public Object
{
public:
	static FMOD_SYSTEM* SOUND_SYSTEM;
	static Channel MUSIC;
	static Channel EFFECT;

	static void SetVolum();
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

public:
	FMOD_SOUND* sound;
	string channelType;

private:
	bool isLoop;
	string fileName;
};

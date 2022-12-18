#include "Sound.h"

FMOD_SYSTEM* Sound::SOUND_SYSTEM = nullptr;
Channel Sound::MUSIC;
Channel Sound::EFFECT;

void Sound::SetVolum()
{
	FMOD_Channel_SetPaused(MUSIC.channel, 1);
	FMOD_Channel_SetVolume(MUSIC.channel, MUSIC.volum);
	FMOD_Channel_SetVolume(EFFECT.channel, EFFECT.volum);
	FMOD_Channel_SetPaused(MUSIC.channel, 0);
}

Sound::Sound()
{
	SetActive(false);
	if (SOUND_SYSTEM == nullptr)
	{
		SetActive(true);
		FMOD_System_Create(&SOUND_SYSTEM);
		FMOD_System_Init(SOUND_SYSTEM, 10, FMOD_INIT_NORMAL, NULL);
		FMOD_Channel_SetVolume(MUSIC.channel, MUSIC.volum);
		FMOD_Channel_SetVolume(EFFECT.channel, EFFECT.volum);
	}

	channelType = "Music";
}

Sound::~Sound()
{
	FMOD_Sound_Release(sound);
}

void Sound::Update()
{
	FMOD_System_Update(SOUND_SYSTEM);
}

void Sound::Load(string _FileName, bool _IsLoop)
{
	fileName = _FileName;
	isLoop = _IsLoop;

	if (isLoop) FMOD_System_CreateSound(SOUND_SYSTEM, fileName.c_str(), FMOD_LOOP_NORMAL, 0, &sound);
	else FMOD_System_CreateSound(SOUND_SYSTEM, fileName.c_str(), FMOD_DEFAULT, 0, &sound);
}

void Sound::Play()
{
	if (isLoop)
	{
		isLoop = false;
		FMOD_System_CreateSound(SOUND_SYSTEM, fileName.c_str(), FMOD_DEFAULT, 0, &sound);
	}
	
	if(channelType == "Music")
		FMOD_System_PlaySound(SOUND_SYSTEM, sound, 0, false, &MUSIC.channel);
	else if (channelType == "Effect")
		FMOD_System_PlaySound(SOUND_SYSTEM, sound, 0, false, &EFFECT.channel);
}

void Sound::RepeatPlay()
{
	if (!isLoop)
	{
		isLoop = true;
		FMOD_System_CreateSound(SOUND_SYSTEM, fileName.c_str(), FMOD_LOOP_NORMAL, 0, &sound);
	}

	if (channelType == "Music")
		FMOD_System_PlaySound(SOUND_SYSTEM, sound, 0, false, &MUSIC.channel);
	else if (channelType == "Effect")
		FMOD_System_PlaySound(SOUND_SYSTEM, sound, 0, false, &EFFECT.channel);
}

void Sound::Stop()
{
	if (channelType == "Music") FMOD_Channel_Stop(MUSIC.channel);
	else if (channelType == "Effect") FMOD_Channel_Stop(EFFECT.channel);
}

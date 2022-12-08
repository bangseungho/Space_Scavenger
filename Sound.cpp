#include "Sound.h"

FMOD_SYSTEM* Sound::SOUND_SYSTEM = nullptr;
float Sound::musicVolum = 1;

Sound::Sound()
{
	if (SOUND_SYSTEM == nullptr)
	{
		FMOD_System_Create(&SOUND_SYSTEM);
		FMOD_System_Init(SOUND_SYSTEM, 10, FMOD_INIT_NORMAL, NULL);
	}
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
}

void Sound::Play()
{
	FMOD_Channel_Stop(MUSIC_CHANNER);

	if (false == isLoop)
	{
		FMOD_System_CreateSound(SOUND_SYSTEM, fileName.c_str(), FMOD_DEFAULT, 0, &sound);
		FMOD_Channel_SetVolume(MUSIC_CHANNER, musicVolum);
		FMOD_System_PlaySound(SOUND_SYSTEM, sound, 0, false, &MUSIC_CHANNER);
	}
	else if (true == isLoop)
	{
		FMOD_System_CreateSound(SOUND_SYSTEM, fileName.c_str(), FMOD_LOOP_NORMAL, 0, &sound);
		FMOD_Channel_SetVolume(MUSIC_CHANNER, musicVolum);
		FMOD_System_PlaySound(SOUND_SYSTEM, sound, 0, false, &MUSIC_CHANNER);
	}
}

void Sound::Stop()
{
	FMOD_Channel_Stop(MUSIC_CHANNER);
}

void Sound::SetVolum(float _Volum)
{
	musicVolum += _Volum;

	if (musicVolum < 0) musicVolum = 0; // Min Volum
	if (musicVolum > 2) musicVolum = 2; // Max Volum

	FMOD_Channel_SetVolume(MUSIC_CHANNER , musicVolum);
}

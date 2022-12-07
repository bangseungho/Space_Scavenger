//#include "Sound.h"
//
//FMOD_SYSTEM* Sound::SOUND_SYSTEM = nullptr;
//FMOD_CHANNEL* Sound::MUSIC_CHANNER;
//float Sound::musicVelum = 1;
//
//Sound::Sound()
//{
//	if (SOUND_SYSTEM == nullptr)
//	{
//		FMOD_System_Create(&SOUND_SYSTEM, FMOD_VERSION);
//		FMOD_System_Init(SOUND_SYSTEM, 3, FMOD_INIT_NORMAL, NULL);
//	}
//}
//
//Sound::~Sound()
//{
//	FMOD_Sound_Release(sound);
//}
//
//void Sound::Update()
//{
//	FMOD_System_Update(SOUND_SYSTEM);
//}
//
//void Sound::Load(string _FileName)
//{
//	fileName = _FileName.c_str();
//	try
//	{
//		FMOD_System_CreateSound(SOUND_SYSTEM, fileName, FMOD_DEFAULT, NULL, &sound);
//	}
//	catch (const std::exception&)
//	{
//		cout << fileName << " 이 존재하지 않습니다." << endl;
//		exit(1);
//	}
//}
//
//void Sound::Play()
//{
//	if (isLoop)
//	{
//		FMOD_System_CreateSound(SOUND_SYSTEM, fileName, FMOD_DEFAULT, NULL, &sound);
//	}
//	FMOD_Channel_SetVolume(MUSIC_CHANNER, musicVelum);
//	FMOD_System_PlaySound(SOUND_SYSTEM, sound, NULL, 0, &MUSIC_CHANNER);
//}
//
//void Sound::RepetPlay()
//{
//	if (!isLoop)
//	{
//		FMOD_System_CreateSound(SOUND_SYSTEM, fileName, FMOD_LOOP_NORMAL, NULL, &sound);
//	}
//	FMOD_Channel_SetVolume(MUSIC_CHANNER, musicVelum);
//	FMOD_System_PlaySound(SOUND_SYSTEM, sound, NULL, 0, &MUSIC_CHANNER);
//}

#include "SoundManager.h"

SoundManager* SoundManager::Instace = nullptr;

SoundManager::SoundManager()
{
	if (Instace == nullptr)
		Instace = this;

	bar_Music = new SoundBar;
	bar_Effect = new SoundBar;

	bar_Music->type = "Music";
	bar_Effect->type = "Effect";

	bar_Music->transform.local->position.y = 50;
	bar_Effect->transform.local->position.y = -50;
	bacground.transform.local->position.x = 30;

	SetActive(false);
}

SoundManager::~SoundManager()
{
}

void SoundManager::Enable()
{
	bacground.SetActive(true);
	bar_Music->SetActive(true);
	bar_Effect->SetActive(true);
}

void SoundManager::Disable()
{
	bacground.SetActive(false);
	bar_Music->SetActive(false);
	bar_Effect->SetActive(false);
}

void SoundManager::Init()
{
	for (const auto& world : transform.world)
	{
		bacground.transform.world.push_back(world);
		bar_Music->transform.world.push_back(world);
		bar_Effect->transform.world.push_back(world);
	}
	bacground.transform.world.push_back(transform.local);
	bar_Music->transform.world.push_back(transform.local);
	bar_Effect->transform.world.push_back(transform.local);
}

SoundBar::SoundBar()
{
	name = "SoundBar";
	font.lineType = 1;
}

SoundBar::~SoundBar()
{
}

void SoundBar::Enable()
{
	font.SetActive(true);
	bar.SetActive(true);
	plus_Button.SetActive(true);
	minus_Button.SetActive(true);
}

void SoundBar::Disable()
{
	font.SetActive(false);
	bar.SetActive(false);
	plus_Button.SetActive(false);
	minus_Button.SetActive(false);
}

void SoundBar::Init()
{
	for (const auto& world : transform.world)
	{
		font.transform.world.push_back(world);
		bar.transform.world.push_back(world);
		plus_Button.transform.world.push_back(world);
		minus_Button.transform.world.push_back(world);
	}

	font.transform.world.push_back(transform.local);
	bar.transform.world.push_back(transform.local);
	plus_Button.transform.world.push_back(transform.local);
	minus_Button.transform.world.push_back(transform.local);
}

void SoundBar::Update()
{
	if (plus_Button.transform.local->position.x == 0)
	{
		plus_Button.transform.local->position.x = (bar.size->width + plus_Button.size->width) / 2.0f;
		minus_Button.transform.local->position.x = -(bar.size->width + plus_Button.size->width) / 2.0f;
		font.transform.local->position.y = bar.size->height / 2.0f;
		font.text = type;
	}

	if (plus_Button.isClick) bar.amount += 0.1f;
	else if (minus_Button.isClick) bar.amount -= 0.1f;

	if (type == "Music") Sound::MUSIC.volum = bar.amount;
	if (type == "Effect") Sound::EFFECT.volum = bar.amount;

	Sound::SetVolum();
}

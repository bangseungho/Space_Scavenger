#include "BulletNum.h"

int FullBullet::totalNum = 12;
int FullBullet::rad = 53;

BulletNum::BulletNum(string path)
{
	name = "BulletNum";

	ui_Icon.image_file = path + "BulletNum.png";
	ui_Empty.image_file = path + "Empty_BulletNum.png";
	ui_Reload.image_file = path + "Reload.png";
	ui_LowGun.image_file = path + "Gun.png";

	for (int i = 0; i < FullBullet::totalNum; ++i) {
		float r = 360 * i / FullBullet::totalNum;
		ui_Full.push_back(new FullBullet);
		ui_Full[i]->image_file = path + "Full_BulletNum.png";
		ui_Full[i]->transform.local->rotation.z -= r;
		ui_Full[i]->transform.local->position.x = FullBullet::rad * sin(radians(r));
		ui_Full[i]->transform.local->position.y = FullBullet::rad * cos(radians(r));
		ui_Full[i]->color.SetColor(Color(1.0f, 0.5 - i * 0.07f, 0.0f, 1.0f));
	}

	font.lineType = 1;
	font.transform.local->position.y -= 80;
	font.transform.local->position.x += 7;

	transform.local->position.y = -330;
	transform.local->position.x = 510;
}

BulletNum::~BulletNum()
{

}

void BulletNum::Enable()
{
	ui_Icon.SetActive(true);
	ui_Empty.SetActive(true);
	ui_LowGun.SetActive(true);
	for (auto& fb : ui_Full) {
		fb->SetActive(true);
	}
	font.SetActive(true);
}

void BulletNum::Disable()
{
	ui_Icon.SetActive(false);
	ui_Empty.SetActive(false);
	ui_Reload.SetActive(false);
	ui_LowGun.SetActive(false);
	for (auto& fb : ui_Full) {
		fb->SetActive(false);
	}
	font.SetActive(false);
}

void BulletNum::Init()
{
	for (const auto& world : transform.world)
	{
		ui_Icon.transform.world.push_back(world);
		ui_Empty.transform.world.push_back(world);
		ui_Reload.transform.world.push_back(world);
		ui_LowGun.transform.world.push_back(world);
		for (auto& fb : ui_Full) fb->transform.world.push_back(world);
		font.transform.world.push_back(world);
	}
	ui_Icon.transform.world.push_back(transform.local);
	ui_Empty.transform.world.push_back(transform.local);
	ui_Reload.transform.world.push_back(transform.local);
	ui_LowGun.transform.world.push_back(transform.local);
	for (auto& fb : ui_Full) fb->transform.world.push_back(transform.local);
	font.transform.world.push_back(transform.local);
}

void BulletNum::Update()
{
	ui_Icon.color = color;
	ui_Empty.color = color;
	ui_LowGun.color = color;

	static int negativeNum;
	if (ui_Reload.ActiveSelf()) {
		if (ui_Reload.color.A >= 1.0)
			negativeNum = -1;
		else if (ui_Reload.color.A <= 0.0)
			negativeNum = 1;
		ui_Reload.color.A += 0.01 * negativeNum;
	}

	int toDrawBulletNum = FullBullet::totalNum * ratioRemainBullet / 100.0;

	for (int i = 0; i < toDrawBulletNum; ++i) {
		ui_Full[i]->SetActive(true);
	}
	for (int i = toDrawBulletNum; i < FullBullet::totalNum; ++i) {
		ui_Full[i]->SetActive(false);
	}
}

void BulletNum::GetBulletInfo(const int& _BulletNum, const int& _RemainBullet)
{
	string remainBullet{ to_string(_BulletNum) + " / "};
	remainBullet += to_string(_RemainBullet);

	if (_RemainBullet == 0) {
		Disable();
		ui_Reload.SetActive(true);
		ui_LowGun.SetActive(true);
		font.SetActive(true);
	}
	else {
		ui_LowGun.SetActive(true);
		ui_Reload.SetActive(false);
		ui_Icon.SetActive(true);
		ui_Empty.SetActive(true);
	}

	font.text = remainBullet;
	ratioRemainBullet = static_cast<float>(_RemainBullet) * 100 / _BulletNum;
}
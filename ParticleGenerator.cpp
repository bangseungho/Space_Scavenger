#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(int _Amount)
{
	int temp = 0;

	for (int i = 0; i < _Amount; ++i)
		particles.push_back(new Particle{});

	SetActive(false);
}

ParticleGenerator::~ParticleGenerator()
{
}

void ParticleGenerator::Enable()
{
	for (auto& p : particles)
		p->SetActive(true);
	timer.OnTimer(1);
}

void ParticleGenerator::Disable()
{
	for (auto& p : particles)
		p->SetActive(false);
}

void ParticleGenerator::Init()
{
}

void ParticleGenerator::Update()
{
	if (timer.CheckTimer())
		SetActive(false);
}

void ParticleGenerator::ExplodeParticles(const Transform& _TargetPos)
{
	SetActive(true);
	for (auto& p : particles) {
		p->transform.local->position = _TargetPos.model * vec4(0, 0, 0, 1);
	}
}

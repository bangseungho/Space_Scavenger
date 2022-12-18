#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(int _Amount) : amount{ _Amount }
{
	int temp = 0;

	for (int i = 0; i < amount; ++i) {
		particles.push_back(new Particle{});
		particles[i]->distancePitch = 36 * i;
		if (i % 10 == 0) {
			temp += 360.0 / amount * 4;
		}
		particles[i]->distanceYaw = temp;
	}

	startPoint = vec3(0.0f);
	start = false;
}

ParticleGenerator::~ParticleGenerator()
{
}

void ParticleGenerator::Init()
{
}

void ParticleGenerator::Update()
{
	if (start) SpreadParticles();
}

void ParticleGenerator::ExplodeParticles(const Transform& _TargetPos)
{
	start = true;
	for (auto& p : particles) {
		p->SetActive(true);
		p->transform.local->position = _TargetPos.local->position;
		startPoint = _TargetPos.local->position;
	}
}

void ParticleGenerator::SpreadParticles()
{
	for (auto& p : particles) {
		p->transform.local->position.x = startPoint.x + p->distance * sin(p->distancePitch / 360.0 * PI * 2) * cos(p->distanceYaw / 360.0 * PI * 2);
		p->transform.local->position.y = startPoint.y + p->distance * sin(p->distancePitch / 360.0 * PI * 2) * sin(p->distanceYaw / 360.0 * PI * 2);
		p->transform.local->position.z = startPoint.z + p->distance * cos(p->distancePitch / 360.0 * PI * 2);
		
		p->color.A -= 0.03;
		if (p->color.A < 0) {
			toSpawnParticleNum++;
			p->SetActive(false);
		}
	}
}

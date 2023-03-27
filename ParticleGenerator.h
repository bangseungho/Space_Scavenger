#pragma once
#include "Particle.h"
#include "Object.h"

class ParticleGenerator : public Object
{
public:
	ParticleGenerator(int _Amount);
	~ParticleGenerator();

public:
	void Enable();
	void Disable();
	void Init();
	void Update();

public:
	void ExplodeParticles(const Transform& _TargetPos);

private:
	Timer timer;
	vector<Particle*> particles;
	int toSpawnParticleNum;

};


#pragma once
#include "Particle.h"
#include "Object.h"

class ParticleGenerator : public Object
{
public:
	ParticleGenerator(int _Amount);
	~ParticleGenerator();

public:
	void Init();
	void Update();

public:
	void ExplodeParticles(const Transform& _TargetPos);
	void SpreadParticles();

public:
	int amount;
	bool start;

public:
	vec3 startPoint;

private:
	vector<Particle*> particles;
	int toSpawnParticleNum;

};


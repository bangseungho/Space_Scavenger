#include "Transform.h"

Transform::Transform()
{
	local = new TransformBlock;
	worldModel = mat4(1);
	localModel = mat4(1);
	model = mat4(1);
}

Transform::~Transform()
{
}


void Transform::SetScale()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> randomPos(-1, 1);

	vec3 randomSacle = { (float)randomPos(gen), (float)randomPos(gen),  (float)randomPos(gen) };

	randomSacle = randomSacle + local->scale;

	randomSacle.x = (randomSacle.x <= 0) ? 1 : randomSacle.x;
	randomSacle.y = (randomSacle.y <= 0) ? 1 : randomSacle.y;

	local->scale = randomSacle;
}

void Transform::SetRandomRotate()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> randomPos(0, 360);

	local->rotation = { (float)randomPos(gen), 0 , 0};
}

void Transform::Info()
{
	cout << local->pivot << " : local Pivot" << endl;
	cout << local->position << " : local Position" << endl;
	cout << local->rotation << " : local Rotation" << endl;
	cout << local->scale << " : local Scale" << endl;
}

void Transform::LookAt(float speed)
{
	vec3 pos = model * vec4(0, 0, 0, 1);
	vec3 dir = translate(model, vec3(0, 0, -1)) * vec4(0, 0, 0, 1);
	vec3 norm = normalize(dir - pos);

	local->position += norm * FrameTime::oneFrame * speed;
}

// 목표하는 Target에 Speed 만큼 전진
void Transform::LookAtTarget(const Transform& _Target, const float _Speed)
{
	vec3 myPos = model * vec4(0, 0, 0, 1);
	vec3 targetPos = _Target.model * vec4(0, 0, 0, 1);
	vec3 dir = normalize(targetPos - myPos);

	local->position += dir * FrameTime::oneFrame * _Speed;
}
TransformBlock::TransformBlock()
{
	pivot = vec3(0);
	position = vec3(0);
	rotation = vec3(0);
	scale = vec3(1);
}

TransformBlock::~TransformBlock()
{
}

void TransformBlock::ReSet()
{
	pivot = vec3(0);
	position = vec3(0);
	rotation = vec3(0);
	scale = vec3(1);
}
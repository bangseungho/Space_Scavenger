#include "Transform.h"

Transform::Transform()
{
	localPivot = vec3(0);
	localPosition = vec3(0);
	localRotation = vec3(0);
	localScale = vec3(1);

	localModel = new mat4(1);
	worldModel = new mat4(1);
	model = new mat4(1);
}

Transform::~Transform()
{
}

void Transform::Update()
{

}

void Transform::SetScale()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> randomPos(-1, 1);

	vec3 randomSacle = { (float)randomPos(gen), (float)randomPos(gen),  (float)randomPos(gen) };

	randomSacle = randomSacle + localScale;

	randomSacle.x = (randomSacle.x <= 0) ? 1 : randomSacle.x;
	randomSacle.y = (randomSacle.y <= 0) ? 1 : randomSacle.y;

	localScale = randomSacle;
}

void Transform::SetRandomRotate()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> randomPos(0, 360);

	localRotation = { (float)randomPos(gen), 0 , 0};
}

void Transform::Info()
{
	cout << localPivot << " : localPivot" << endl;
	cout << localPosition << " : localPosition" << endl;
	cout << localRotation << " : localRotation" << endl;
	cout << localScale << " : localScale" << endl;
}

void Transform::ReSet()
{
	localPosition = vec3(0, 0, 0);
	localScale = vec3(1, 1, 1);
	localRotation = vec3(0, 0, 0);
	localPivot = vec3(0, 0, 0);
}


void Transform::LookAt(float speed)
{
	vec3 pos = *model * vec4(0, 0, 0, 1);
	vec3 dir = translate(*model, vec3(0, 0, -1)) * vec4(0, 0, 0, 1);
	vec3 norm = normalize(dir - pos);

	localPosition += norm * FrameTime::oneFrame * speed;
}

// 목표하는 Target에 Speed 만큼 전진
void Transform::LookAtTarget(const Transform& _Target, const float _Speed)
{
	vec3 myPos = *model * vec4(0, 0, 0, 1);
	vec3 targetPos = *_Target.model * vec4(0, 0, 0, 1);
	vec3 dir = normalize(targetPos - myPos);

	localPosition += dir * FrameTime::oneFrame * _Speed;
}
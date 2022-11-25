#pragma once
#include "Transform.h"

class Camera {
public:
 	static Camera* mainCamera;

	static unsigned int viewPosLocation;

public:
	Camera();
	~Camera();

public:
	void Draw();
	void ProcessInput(int specialKey);

	void Info();
public:
	void LookAtView(float speed);

public:
	string name;
	Transform transform;
	Transform* target_Pos;

	bool isProjection;
	bool isProjection_XY;
	bool isProjection_XZ;
	bool isPitch;
	vec3 velocity; // 이동방향
	vec3 cameraPos; //--- 카메라 위치
	vec3 realCameraPos;	// 실제 카메라 위치
	vec3 cameraFront = vec3(0, 0, -1);
	vec3 cameraDirection; //--- 카메라 바라보는 방향
	vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);
	// 문제를 풀기 위한 임시 변수들
	float yRotate;
	float speed;
};
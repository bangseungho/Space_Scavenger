#include "Camera.h"

Camera* Camera::mainCamera = nullptr;

unsigned int Camera::viewLocation;
unsigned int Camera::projectionLocation;
unsigned int Camera::viewPosLocation;


Camera::Camera()
{
	name = "Null";

	yRotate = 0;

	isProjection = false;
	isProjection_XY = false;
	isProjection_XZ = false;
	isPitch = false;

	velocity = vec3(0);
	cameraPos = vec3(0);
	realCameraPos = vec3(0);
	cameraDirection = vec3(0);
}

Camera::~Camera()
{
}

void Camera::Draw()
{
	view = mat4(1.0f);
	projection = mat4(1.0f);
	float size = 2.0f;
	if (isProjection_XY)	// 직각 투영
	{
		projection = ortho(-size, size, -size, size, -size, size);
	}
	else if (isProjection_XZ)
	{
		projection = ortho(-size, size, -size, size, -size, size);
		projection = rotate(projection, radians(90.0f), vec3(1, 0, 0));
	}
	else if(isProjection)
	{
		view = lookAt(cameraPos, vec3(0), cameraUp);

		projection = perspective(radians(45.0f), static_cast<float>(aspect_ratio), 0.1f, 50.0f);

		for (auto& world : transform.world)
		{
			projection = translate(projection, world->position);
			projection = rotate(projection, radians(world->rotation.x), vec3(1.0, 0.0, 0.0));
			projection = rotate(projection, radians(world->rotation.y), vec3(0.0, 1.0, 0.0));
			projection = rotate(projection, radians(world->rotation.z), vec3(0.0, 0.0, 1.0));
		}
		projection = translate(projection, transform.local->position);
		projection = rotate(projection, radians(transform.local->rotation.x), vec3(1.0, 0.0, 0.0));
		projection = rotate(projection, radians(transform.local->rotation.y), vec3(0.0, 1.0, 0.0));
		projection = rotate(projection, radians(transform.local->rotation.z), vec3(0.0, 0.0, 1.0));
	}
	else if (isPitch)
	{
		vec3 pos = translate(transform.model, cameraPos) * vec4(0, 0, 0, 1);
		pos = translate(target_Pos->model, pos) * vec4(0, 0, 0, 1);
		vec3 dir = translate(target_Pos->model, cameraDirection) * vec4(0, 0, 0, 1);
		mat4 worldModel = mat4(1.0);
		mat4 localModel = mat4(1.0);

		for (auto& world : target_Pos->world)
		{
			localModel = rotate(localModel, radians(world->rotation.y), vec3(0, 1.0, 0));	// y축으로 자전 해주고 싶어 처음에 추가
			localModel = rotate(localModel, radians(world->rotation.x), vec3(1.0, 0, 0));
			localModel = rotate(localModel, radians(world->rotation.z), vec3(0, 0, 1.0));
		}

		worldModel = rotate(worldModel, radians(target_Pos->local->rotation.y), vec3(0, 1.0, 0));
		worldModel = rotate(worldModel, radians(target_Pos->local->rotation.x), vec3(1.0, 0, 0));
		worldModel = rotate(worldModel, radians(target_Pos->local->rotation.z), vec3(0, 0, 1.0));

		mat4 model = localModel * worldModel;

		vec3 up = translate(model, cameraUp) * vec4(0, 0, 0, 1);
		up = normalize(up);

		view = lookAt(pos, dir, up);

		projection = perspective(radians(45.0f), static_cast<float>(aspect_ratio), 0.1f, 100000.0f);
	}

	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, value_ptr(view));
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, value_ptr(projection));
	glUniform3f(viewPosLocation, cameraPos.x, cameraPos.y, cameraPos.z);
}

mat4& Camera::SetMatrix()
{
	mat4 localModel = mat4(1.0);
	mat4 worldModel = mat4(1.0);

	for (auto& world : transform.world)
	{
		//worldModel = translate(worldModel, world->pivot);
		worldModel = translate(worldModel, world->position);
		worldModel = rotate(worldModel, radians(world->rotation.y), vec3(0, 1.0, 0));
		worldModel = rotate(worldModel, radians(world->rotation.x), vec3(1.0, 0, 0));
		worldModel = rotate(worldModel, radians(world->rotation.z), vec3(0, 0, 1.0));
		worldModel = scale(worldModel, world->scale);
	}

	localModel = translate(localModel, transform.local->pivot);
	localModel = translate(localModel, transform.local->position);
	localModel = rotate(localModel, radians(transform.local->rotation.y), vec3(0, 1.0, 0));
	localModel = rotate(localModel, radians(transform.local->rotation.x), vec3(1.0, 0, 0));
	localModel = rotate(localModel, radians(transform.local->rotation.z), vec3(0, 0, 1.0));
	localModel = scale(localModel, transform.local->scale);

	transform.localModel = localModel;
	transform.worldModel = worldModel;
	transform.model = worldModel * localModel;

	return transform.model;
}
void Camera::Info()
{
	cout << "Camera : " << name << endl;
}

void Camera::LookAtView(float speed)
{
	vec3 diff = normalize(cameraPos - cameraDirection) * speed * FrameTime::oneFrame * vec3(10) / target_Pos->local->scale;

	cameraPos += diff;
	
	//diff *= target_Pos->worldScale * target_Pos->localScale;
	//realCameraPos += diff;
}

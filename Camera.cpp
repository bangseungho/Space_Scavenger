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
	mat4 view = mat4(1.0f);
	mat4 projection = mat4(1.0f);
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

		projection = translate(projection, transform.localPosition);
		projection = rotate(projection, radians(transform.localRotation.x), vec3(1.0, 0.0, 0.0));
		projection = rotate(projection, radians(transform.localRotation.y), vec3(0.0, 1.0, 0.0));
		projection = rotate(projection, radians(transform.localRotation.z), vec3(0.0, 0.0, 1.0));

		projection = translate(projection, transform.worldPosition);
		projection = rotate(projection, radians(transform.worldRotation.x), vec3(1.0, 0.0, 0.0));
		projection = rotate(projection, radians(transform.worldRotation.y), vec3(0.0, 1.0, 0.0));
		projection = rotate(projection, radians(transform.worldRotation.z), vec3(0.0, 0.0, 1.0));
	}
	else if (isPitch)
	{
		vec3 pos = translate(target_Pos->model, cameraPos) * vec4(0, 0, 0, 1);
		vec3 dir = translate(target_Pos->model, cameraDirection) * vec4(0, 0, 0, 1);
		mat4 worldModel = mat4(1.0);
		mat4 localModel = mat4(1.0);

		localModel = rotate(localModel, radians(target_Pos->localRotation.y), vec3(0, 1.0, 0));	// y축으로 자전 해주고 싶어 처음에 추가
		localModel = rotate(localModel, radians(target_Pos->localRotation.x), vec3(1.0, 0, 0));
		localModel = rotate(localModel, radians(target_Pos->localRotation.z), vec3(0, 0, 1.0));
														  
		worldModel = rotate(worldModel, radians(target_Pos->worldRotation.y), vec3(0, 1.0, 0));
		worldModel = rotate(worldModel, radians(target_Pos->worldRotation.x), vec3(1.0, 0, 0));
		worldModel = rotate(worldModel, radians(target_Pos->worldRotation.z), vec3(0, 0, 1.0));

		mat4 model = localModel * worldModel;

		vec3 up = translate(model, cameraUp) * vec4(0, 0, 0, 1);
		up = normalize(up);

		view = lookAt(pos, dir, up);

		projection = perspective(radians(45.0f), static_cast<float>(aspect_ratio), 0.1f, 50.0f);
	}

	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);
	glUniform3f(viewPosLocation, cameraPos.x, cameraPos.y, cameraPos.z);
}
void Camera::ProcessInput(int specialKey)
{
	//float cameraSpeed = speed * FrameTime::oneFrame;
	//switch (specialKey)
	//{
	//case GLUT_KEY_LEFT:
	//	cameraPos -= glm::normalize(glm::cross(cameraDirection, cameraUp)) * cameraSpeed;
	//	break;
	//case GLUT_KEY_RIGHT:
	//	cameraPos += glm::normalize(glm::cross(cameraDirection, cameraUp)) * cameraSpeed;
	//	break;
	//case GLUT_KEY_UP:
	//	cameraPos += cameraSpeed * cameraDirection;
	//	break;
	//case GLUT_KEY_DOWN:
	//	cameraPos -= cameraSpeed * cameraDirection;
	//	break;
	//}
}


void Camera::Info()
{
	cout << "Camera : " << name << endl;
}

void Camera::LookAtView(float speed)
{
	vec3 diff = normalize(cameraPos - cameraDirection) * speed * FrameTime::oneFrame * vec3(100);

	cameraPos += diff;
	
	//diff *= target_Pos->worldScale * target_Pos->localScale;
	//realCameraPos += diff;
}

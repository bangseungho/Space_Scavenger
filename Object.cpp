#include "Object.h"

//list<Object*> Object::allObject;	//main.cpp 에서 전역변수로 Object 호출시 static 부분 무시함 (이유는 모름)
int Object::ID_Count = 0;
unsigned char Object::key;
int Object::specialKey;

int Object::modelLocation;
int Object::vColorLocation;

Object::Object(): transform(), color()
{
	id = ID_Count++;
	name = "UnName";
	isActive = true;

	worldPivotSpeed = vec3(0);
	worldSpeed = localSpeed = vec3(0);
	worldRotateSpeed = localRotateSpeed = vec3(0);

	allObject.push_back(this);
}

Object::~Object()
{
}

void Object::Update()
{
}

void Object::Init()
{
	glUseProgram(s_program);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VAO_Dot);
	glGenBuffers(1, &VAO_Index);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VAO_Dot);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * block.vertices.size(), &block.vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VAO_Index); //--- GL_ELEMENT_ARRAY_BUFFER 버퍼 유형으로 바인딩
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vec3) * block.faceIndex, block.face, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);
	glEnableVertexAttribArray(0);
}

void Object::ObjcetDraw()
{
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(transform.model));
	glUniform4f(vColorLocation, color.R, color.G, color.B, color.A);

	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, block.faceIndex * 3, GL_UNSIGNED_SHORT, 0);
}


void Object::Collision()
{

}

void Object::Info()
{
	cout << name << " : " << id << endl;
}

mat4& Object::SetMatrix()
{
	mat4 worldModel = mat4(1.0);
	mat4 localModel = mat4(1.0);

	localModel = translate(localModel, transform.localPosition);
	localModel = rotate(localModel, radians(transform.localRotation.x), vec3(1.0, 0, 0));
	localModel = rotate(localModel, radians(transform.localRotation.y), vec3(0, 1.0, 0));	// y축으로 자전 해주고 싶어 처음에 추가
	localModel = rotate(localModel, radians(transform.localRotation.z), vec3(0, 0, 1.0));
	localModel = translate(localModel, transform.localPivot);
	localModel = scale(localModel, transform.localScale);

	worldModel = translate(worldModel, transform.worldPosition);
	worldModel = rotate(worldModel, radians(transform.worldRotation.x), vec3(1.0, 0, 0));
	worldModel = rotate(worldModel, radians(transform.worldRotation.y), vec3(0, 1.0, 0));
	worldModel = rotate(worldModel, radians(transform.worldRotation.z), vec3(0, 0, 1.0));
	worldModel = translate(worldModel, transform.worldPivot);
	worldModel = scale(worldModel, transform.worldScale);

	transform.model = localModel * worldModel;

	return transform.model;
}
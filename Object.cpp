#include "Object.h"

//list<Object*> Object::allObject;	//main.cpp 에서 전역변수로 Object 호출시 static 부분 무시함 (이유는 모름)
int Object::ID_Count = 0;
unsigned char Object::key;
int Object::specialKey;

unsigned int Object::modelLocation;
unsigned int Object::vColorLocation;

unsigned int Object::objectColorLocation;

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
	delete block;
	allObject.erase(remove(allObject.begin(), allObject.end(), this), allObject.end());
}

void Object::Update()
{
}

void Object::Init()
{
	glUseProgram(s_program);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VAO_VERTICES);
	glGenBuffers(1, &VAO_VERTICES_INDEX);

	glGenBuffers(1, &VAO_VERTICES_UVS);
	glGenBuffers(1, &VAO_UV_INDICES);

	glGenBuffers(1, &VAO_VERTICES_NORMALS);
	glGenBuffers(1, &VAO_NORMAL_INDICES);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VAO_VERTICES_UVS);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * block->vertices_uvs->size(), &block->vertices_uvs[0][0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VAO_UV_INDICES);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vec3) * block->uvIndices->size(), &block->uvIndices[0][0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vec2), (void*)0); //--- 텍스쳐

	glBindBuffer(GL_ARRAY_BUFFER, VAO_VERTICES_NORMALS);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * block->vertices_normals->size(), &block->vertices_normals[0][0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VAO_NORMAL_INDICES);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vec3) * block->normalIndices->size(), &block->normalIndices[0][0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vec3) , (void*)0); //--- 노말 속성

	glBindBuffer(GL_ARRAY_BUFFER, VAO_VERTICES);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * block->vertices->size(), &block->vertices[0][0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VAO_VERTICES_INDEX); //--- GL_ELEMENT_ARRAY_BUFFER 버퍼 유형으로 바인딩
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vec3) * block->vertexIndices->size(), &block->vertexIndices[0][0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0); // 정점
}

void Object::ObjectDraw()
{
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(transform.model));
	glUniform4f(vColorLocation, color.R, color.G, color.B, color.A);

	glBindVertexArray(VAO);

	//glPointSize(5.0f);
	//glDrawArrays(GL_POINTS, 0, block.vertices->size());
	glDrawElements(GL_TRIANGLES, block->vertexIndices->size() * 3, GL_UNSIGNED_SHORT, 0);
	
}


void Object::Collision()
{

}

void Object::SetActive(bool value)
{
	if (this->isActive == false && value == true)
		this->Enable();
	else if (this->isActive == true && value == false)
		this->Disable();

	this->isActive = value;
}

void Object::Info()
{
	cout << id << " : " << name << endl;
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
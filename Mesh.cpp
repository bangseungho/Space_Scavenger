#include "Mesh.h"

Shader* Mesh::objectShader = nullptr;
unsigned int Mesh::vertexLocation;
unsigned int Mesh::uvLoaction;
unsigned int Mesh::normalLocation;

unsigned int Mesh::modelLocation;
unsigned int Mesh::vColorLocation;

unsigned int Mesh::KaLocation;
unsigned int Mesh::KdLocation;
unsigned int Mesh::KsLocation;
unsigned int Mesh::dLocation;

unsigned int Mesh::lightTypeIndexLocation;

Mesh::Mesh(Object* obj) : object(obj)
{
	if (objectShader == nullptr)
	{
		objectShader = Shader::allProgram.find("Object")->second;
		vertexLocation = glGetAttribLocation(objectShader->program, "vPos");
		uvLoaction = glGetAttribLocation(objectShader->program, "vUV");
		normalLocation = glGetAttribLocation(objectShader->program, "vNormal");

		modelLocation = glGetUniformLocation(objectShader->program, "modelTransform");
		vColorLocation = glGetUniformLocation(objectShader->program, "vColor");

		KaLocation = glGetUniformLocation(objectShader->program, "Ka");
		KdLocation = glGetUniformLocation(objectShader->program, "Kd");
		KsLocation = glGetUniformLocation(objectShader->program, "Ks");
		dLocation = glGetUniformLocation(objectShader->program, "d");

		lightTypeIndexLocation = glGetUniformLocation(objectShader->program, "lightTypeIndex");
	}

	lightTypeIndex = 0;

	isDraw = true;
}

Mesh::~Mesh()
{
}

void Mesh::MeshInit()
{
	int num = obj->vBlock.groupCount;
	VAO = new GLuint[num];
	VBO = new GLuint[1];
	EBO = new GLuint[num];

	glGenVertexArrays(num, VAO);
	glGenBuffers(1, VBO);
	glGenBuffers(num, EBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * obj->vBlock.vertices_normals.size(), &obj->vBlock.vertices_normals[0], GL_STATIC_DRAW);
	for (int i = 0; i < num; i++)
	{
		glBindVertexArray(VAO[i]);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vec3) * obj->vBlock.normalIndices[i].size(), &obj->vBlock.normalIndices[i][0], GL_STATIC_DRAW);
		glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0); //--- 노말 속성
		glEnableVertexAttribArray(normalLocation);
	}

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * obj->vBlock.vertices.size(), &obj->vBlock.vertices[0], GL_STATIC_DRAW);
	for (int i = 0; i < num; i++)
	{
		glBindVertexArray(VAO[i]);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[i]); //--- GL_ELEMENT_ARRAY_BUFFER 버퍼 유형으로 바인딩
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vec3) * obj->vBlock.vertexIndices[i].size(), &obj->vBlock.vertexIndices[i][0], GL_STATIC_DRAW);
		glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0); // 정점
		glEnableVertexAttribArray(vertexLocation);
	}

	//for (int i = 0; i < num; i++)
	//{
	//	glBindVertexArray(VAO[i]);

	//	//if (obj->isOnMTL)
	//	//{
	//	//	MaterialBlock mBlock = obj->mBlock.find(obj->vBlock.usemtlName[i])->second;
	//	//	glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
	//	//	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3), &mBlock.Kd, GL_STATIC_DRAW);
	//	//	glEnableVertexAttribArray(KdLocation);
	//	//	glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
	//	//	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3), &mBlock.Ks, GL_STATIC_DRAW);
	//	//	glEnableVertexAttribArray(KsLocation);
	//	//	glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
	//	//	glBufferData(GL_ARRAY_BUFFER, sizeof(float), &mBlock.d, GL_STATIC_DRAW);
	//	//	glEnableVertexAttribArray(dLocation);
	//	//}

	//	//glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
	//	//glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * obj->vBlock.vertices_uvs.size(), &obj->vBlock.vertices_uvs[0], GL_STATIC_DRAW);
	//	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[i]);
	//	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vec3) * obj->vBlock.uvIndices[i].size(), &obj->vBlock.uvIndices[i][0], GL_STATIC_DRAW);
	//	//glVertexAttribPointer(uvLoaction, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0); //--- 텍스쳐
	//	//glEnableVertexAttribArray(uvLoaction);

	//	glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
	//	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * obj->vBlock.vertices_normals.size(), &obj->vBlock.vertices_normals[0], GL_STATIC_DRAW);
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[i]);
	//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vec3) * obj->vBlock.normalIndices[i].size(), &obj->vBlock.normalIndices[i][0], GL_STATIC_DRAW);
	//	glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0); //--- 노말 속성
	//	glEnableVertexAttribArray(normalLocation);

	//	glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
	//	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * obj->vBlock.vertices.size(), &obj->vBlock.vertices[0], GL_STATIC_DRAW);
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[i]); //--- GL_ELEMENT_ARRAY_BUFFER 버퍼 유형으로 바인딩
	//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vec3) * obj->vBlock.vertexIndices[i].size(), &obj->vBlock.vertexIndices[i][0], GL_STATIC_DRAW);
	//	glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0); // 정점
	//	glEnableVertexAttribArray(vertexLocation);
	//}
	
}

void Mesh::Draw()
{
	glUniform1i(lightTypeIndexLocation, lightTypeIndex);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(object->transform.model));
	glUniform4f(vColorLocation, color.R, color.G, color.B, color.A);

	for (int i = 0; i < obj->vBlock.groupCount; i++)
	{
		if (obj->isOnMTL)
		{
			MaterialBlock mBlock;
			if (obj->vBlock.usemtlName[i] == "NULL")
			{
				mBlock.Ka = vec3(1);
				mBlock.Kd = vec3(1);
				mBlock.Ks = vec3(1);
				mBlock.d = 1.5f;
			}
			else  mBlock = obj->mBlock.find(obj->vBlock.usemtlName[i])->second;
			glUniform3f(KaLocation, mBlock.Ka.x, mBlock.Ka.y, mBlock.Ka.z);
			glUniform3f(KdLocation, mBlock.Kd.x, mBlock.Kd.y, mBlock.Kd.z);
			glUniform3f(KsLocation, mBlock.Ks.x, mBlock.Ks.y, mBlock.Ks.z);
			glUniform1f(dLocation, mBlock.d);
		}

		glBindVertexArray(VAO[i]);

		glDrawElements(GL_TRIANGLES, obj->vBlock.vertexIndices[i].size() * 3, GL_UNSIGNED_SHORT, 0);
	}
	
}
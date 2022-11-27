#include "Mesh.h"

unsigned int Mesh::modelLocation;
unsigned int Mesh::vColorLocation;

Mesh::Mesh(Object* obj) : object(obj)
{
	allMesh.push_back(this);
	isDraw = true;
}

Mesh::~Mesh()
{
	allMesh.erase(remove(allMesh.begin(), allMesh.end(), this), allMesh.end());
}

void Mesh::MeshInit()
{
	glUseProgram(s_program);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VAO_VERTICES);
	glGenBuffers(1, &VAO_VERTICES_INDEX);

	glGenBuffers(1, &VAO_VERTICES_UVS);
	glGenBuffers(1, &VAO_UV_INDICES);

	glGenBuffers(1, &VAO_VERTICES_NORMALS);
	glGenBuffers(1, &VAO_NORMAL_INDICES);

	//glGenBuffers(1, &UBO_MATERIAL_BLOCK);
	glBindVertexArray(VAO);


	//glBindBuffer(GL_UNIFORM_BUFFER, UBO_MATERIAL_BLOCK);
	//glBufferData(GL_UNIFORM_BUFFER, sizeof(vec3) * 3 + sizeof(float), NULL, GL_STATIC_DRAW); // 152 바이트 메모리 할당
	//glUniformBlockBinding(s_program, meterialBlockLoaction, UBO_MATERIAL_BLOCK);
	//glBindBufferBase(GL_UNIFORM_BUFFER, 0, buffer_b);

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
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0); //--- 노말 속성

	glBindBuffer(GL_ARRAY_BUFFER, VAO_VERTICES);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * block->vertices->size(), &block->vertices[0][0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VAO_VERTICES_INDEX); //--- GL_ELEMENT_ARRAY_BUFFER 버퍼 유형으로 바인딩
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vec3) * block->vertexIndices->size(), &block->vertexIndices[0][0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0); // 정점
}

void Mesh::Draw()
{
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(object->transform.model));
	glUniform4f(vColorLocation, color.R, color.G, color.B, color.A);

	glBindVertexArray(VAO);

	//glPointSize(5.0f);
	//glDrawArrays(GL_POINTS, 0, block.vertices->size());
	glDrawElements(GL_TRIANGLES, block->vertexIndices->size() * 3, GL_UNSIGNED_SHORT, 0);
}
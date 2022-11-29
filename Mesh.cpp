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

	GLint uvLoaction = glGetAttribLocation(s_program, "vUV");
	GLint normalLocation = glGetAttribLocation(s_program, "vNormal");
	GLint vertexLocation = glGetAttribLocation(s_program, "vPos");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * block->vertices_uvs.size(), &block->vertices_uvs[0], GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vec3) * block->uvIndices.size(), &block->uvIndices[0], GL_STATIC_DRAW);
	//glVertexAttribPointer(uvLoaction, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0); //--- 텍스쳐
	//glEnableVertexAttribArray(uvLoaction);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * block->vertices_normals.size(), &block->vertices_normals[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vec3) * block->normalIndices.size(), &block->normalIndices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0); //--- 노말 속성
	glEnableVertexAttribArray(normalLocation);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * block->vertices.size(), &block->vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //--- GL_ELEMENT_ARRAY_BUFFER 버퍼 유형으로 바인딩
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vec3) * block->vertexIndices.size(), &block->vertexIndices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0); // 정점
	glEnableVertexAttribArray(vertexLocation);
}

void Mesh::Draw()
{
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(object->transform.model));
	glUniform4f(vColorLocation, color.R, color.G, color.B, color.A);

	glBindVertexArray(VAO);

	//glPointSize(5.0f);
	//glDrawArrays(GL_POINTS, 0, block.vertices->size());
	glDrawElements(GL_TRIANGLES, block->vertexIndices.size() * 3, GL_UNSIGNED_SHORT, 0);
}
#include "Mesh.h"

unsigned int Mesh::vertexLocation;
unsigned int Mesh::uvLoaction;
unsigned int Mesh::normalLocation;

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
	//glUseProgram(s_program);

	//GLint uvLoaction = glGetAttribLocation(s_program, "vUV");
	//GLint normalLocation = glGetAttribLocation(s_program, "vNormal");
	//GLint vertexLocation = glGetAttribLocation(s_program, "vPos");

	int num = obj->vBlock.groupCount;
	VAO = new GLuint[num];
	VBO = new GLuint[num];
	EBO = new GLuint[num];

	glGenVertexArrays(num, VAO);
	glGenBuffers(num, VBO);
	glGenBuffers(num, EBO);

	for (int i = 0; i < num; i++)
	{
		glBindVertexArray(VAO[i]);

		//glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * obj->vBlock.vertices_uvs.size(), &obj->vBlock.vertices_uvs[0], GL_STATIC_DRAW);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[i]);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vec3) * obj->vBlock.uvIndices[i].size(), &obj->vBlock.uvIndices[i][0], GL_STATIC_DRAW);
		//glVertexAttribPointer(uvLoaction, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0); //--- 텍스쳐
		//glEnableVertexAttribArray(uvLoaction);

		glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * obj->vBlock.vertices_normals.size(), &obj->vBlock.vertices_normals[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vec3) * obj->vBlock.normalIndices[i].size(), &obj->vBlock.normalIndices[i][0], GL_STATIC_DRAW);
		glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0); //--- 노말 속성
		glEnableVertexAttribArray(normalLocation);

		glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * obj->vBlock.vertices.size(), &obj->vBlock.vertices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[i]); //--- GL_ELEMENT_ARRAY_BUFFER 버퍼 유형으로 바인딩
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vec3) * obj->vBlock.vertexIndices[i].size(), &obj->vBlock.vertexIndices[i][0], GL_STATIC_DRAW);
		glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0); // 정점
		glEnableVertexAttribArray(vertexLocation);
	}
	
}

void Mesh::Draw()
{
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(object->transform.model));
	glUniform4f(vColorLocation, color.R, color.G, color.B, color.A);

	for (int i = 0; i < obj->vBlock.groupCount; i++)
	{
		glBindVertexArray(VAO[i]);

		//glPointSize(5.0f);
		//glDrawArrays(GL_POINTS, 0, block.vertices->size());
		glDrawElements(GL_TRIANGLES, obj->vBlock.vertexIndices[i].size() * 3, GL_UNSIGNED_SHORT, 0);
	}
	
}
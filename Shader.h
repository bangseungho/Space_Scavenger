#pragma once
#include <iostream>
#include <map>
#include <string>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/ext.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

using namespace std;
using namespace glm;

#pragma warning(disable:4996)

class Shader
{
public:
	static map<string, GLuint*> allProgram;
public:
	Shader(string _Name);
	~Shader();
public:
	void CreatVertexShader(string shaderFileName);
	void CreatFragmentShader(string shaderFileName);
	void CreatProgram();

private:
	char* FileToBuffer(const char* file);

public:
	GLuint program;

private:
	string name;
	GLuint vertexShader;
	GLuint fragmentShader;
};


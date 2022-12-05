#pragma once
#include "FrameTime.h"
#include "Random.h"
#include "Shader.h"
#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

// 모델 사용에 따른 정의
#ifndef _MAX
#define _MAX
#endif


extern char default_Cube[];

//extern GLuint s_program;
//extern GLuint vertexShader; //--- 버텍스 세이더 객체
//extern GLuint fragmentShader; //--- 프래그먼트 세이더 객체
//
//extern GLuint gui_s_program;
//extern GLuint gui_vertexShader;
//extern GLuint gui_fragmentShader;

extern int windowSize_W;
extern int windowSize_H;
extern double aspect_ratio;

extern bool isFullScreen;

extern int Time_Duration;

extern float PI;

typedef struct Vector2 {
	GLfloat x;
	GLfloat y;
}Vector2;

typedef struct Vector3 {
	GLfloat x;
	GLfloat y;
	GLfloat z;
}Vector3;

typedef struct Position2 {
	int x;
	int y;
}Position2;

typedef struct Face {
	unsigned short a;
	unsigned short b;
	unsigned short c;
}Face;

//typedef struct MaterialBlock {
//	char name[32];
//	int illum;
//	char map_Kd[32];
//	float Ni;
//	vec3 Kd;
//	vec3 Ka;
//	vec3 Tf;
//	unsigned int texture;
//}MaterialBlock;
//
//typedef struct VertexBlock {
//	vector<Face>* vertexIndices, *uvIndices, *normalIndices;
//	vector<vec3> vertices;
//	vector<vec2> vertices_uvs;
//	vector<vec3> vertices_normals;
//	vec3 max, min;
//	int groupCount;
//
//	MaterialBlock material;
//}VertexBlock;

Face operator- (const Face my, int other);

ostream& operator<< (ostream& outputStream, const vec3& my);
ostream& operator<< (ostream& outputStream, const Face& my);
bool operator== (const vec3 my, const float other);

extern vec2 StartMouse;

//char* filetobuf(const char* file);
//void make_vertexShaders();
//void make_fragmentShaders();
//void InitShader();
void FrameTimer(int value);
//void ReadObj(char* fileName, VertexBlock& block);
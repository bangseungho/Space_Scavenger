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

extern int windowSize_W;
extern int windowSize_H;
extern double aspect_ratio;

extern bool isFullScreen;

extern vec2 StartMouse;
extern vec2 mouse_Pos;

typedef struct Face {
	unsigned short a;
	unsigned short b;
	unsigned short c;
}Face;


Face operator- (const Face my, int other);

ostream& operator<< (ostream& outputStream, const vec3& my);
ostream& operator<< (ostream& outputStream, const Face& my);
bool operator== (const vec3 my, const float other);

extern vec2 StartMouse;

void FrameTimer(int value);
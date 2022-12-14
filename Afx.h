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
#include <locale>
#include <codecvt>

// 모델 사용에 따른 정의
#ifndef _MAX
#define _MAX
#endif

extern double windowSize_W;
extern double windowSize_H;
extern double aspect_ratio;

extern bool isFullScreen;

extern vec2 StartMouse;
extern vec2 mouse_Pos;
extern int button;
extern int state;

typedef struct Face {
	unsigned short a;
	unsigned short b;
	unsigned short c;
}Face;


Face operator- (const Face my, int other);

ostream& operator<< (ostream& outputStream, const vec2& my);
ostream& operator<< (ostream& outputStream, const vec3& my);
ostream& operator<< (ostream& outputStream, const Face& my);
bool operator== (const vec3 my, const float other);

extern vec2 StartMouse;

void FrameTimer(int value);
#include "Afx.h"

double windowSize_W = 1600;
double windowSize_H = 900;

double aspect_ratio = windowSize_W / windowSize_H;

bool isFullScreen = false;
bool isOnTimer = false;

vec2 StartMouse;
vec2 mouse_Pos;
int button;
int state;

#pragma region VectorFuntion

Face operator-(const Face my, int other)
{
	Face result;
	result.a = my.a - other;
	result.b = my.b - other;
	result.c = my.c - other;
	return result;
}

ostream& operator<< (ostream& outputStream, const vec2& my)
{
	cout << my.x << ", " << my.y;
	return outputStream;
}


ostream& operator<< (ostream& outputStream, const vec3& my)
{
	cout << my.x << ", " << my.y << ", " << my.z;
	return outputStream;
}

ostream& operator<< (ostream& outputStream, const Face& my)
{
	cout << my.a << ", " << my.b << ", " << my.c;
	return outputStream;
}

bool operator== (const vec3 my, const float other)
{
	if (my.x != other) return false;
	if (my.y != other)return false;
	if (my.z != other)return false;

	return true;
}

#pragma endregion

void FrameTimer(int value)
{
	glutPostRedisplay();
}

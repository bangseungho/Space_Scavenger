#pragma once
#include "Afx.h"

class Color {
public:
	Color();
	Color(float r, float g, float b, float a);
	~Color();

public:
	void SetRandomColor();
	void SetColor(Color color);
	void SetColor(GLclampf i[]);
	void BlinkAlpha();

private:

public:
	GLclampf R;
	GLclampf G;
	GLclampf B;
	GLclampf A;

private:

};
#pragma once
#include "Render.h"
class Font : public Object
{
public:
	void Init();

public:
	int size;
	string fileName;
private:
	HDC hDC;              // Private GDI Device Context
	HGLRC hRC;            // Permanent Rendering Context
	HWND hWnd;            // Holds Our Window Handle
	HINSTANCE hInstance;
	GLuint base;
};
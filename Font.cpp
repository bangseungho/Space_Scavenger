#include "Font.h"

Font::Font(string _Name) : Mesh(this)
{
	name = "Font";
	text = "";

	Render::fontRender->AddObject(this, _Name);
}

Font::~Font()
{
}

void Font::Draw()
{
	vec2 pos = transform.model * vec4(0, 0, 0, 1);

	glColor4f(color.R, color.G, color.B, color.A);
	glRasterPos2f(pos.x, pos.y);

	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text.c_str());
}

#include "Color.h"

Color::Color()
{
	R = G = B = 1;
	A = 1;
}

Color::Color(float r,float g, float b, float a)
{
	R = r;
	G = g;
	B = b;
	A = a;
}

Color::~Color()
{
}

void Color::SetRandomColor()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<GLclampf> randomcolor(0.0f, 1.0f);

	R = randomcolor(gen);
	G = randomcolor(gen);
	B = randomcolor(gen);
}

void Color::SetColor(Color color)
{
	R = color.R;
	G = color.G;
	B = color.B;
	A = color.A;
}

void Color::SetColor(GLclampf i[])
{
	R = i[0];
	G = i[1];
	B = i[2];
	A = i[3];
}

void Color::BlinkAlpha()
{


}

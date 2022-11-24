#include "Vector_AFX.h"

double Vec3Dot(const vec3 a, const vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z)/ length(b);
}
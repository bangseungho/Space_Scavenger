#include "Resource.h"


Resource::Resource()
{
	collider.tag = "Resource";
	collider.object = this;

	amount = 0;
	moveDirection = vec3(0);
}

Resource::~Resource()
{
}
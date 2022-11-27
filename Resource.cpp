#include "Resource.h"


Resource::Resource() : Mesh(this)
{
	collider.tag = "Resource";
	collider.object = this;

	amount = 0;
	velocity = vec3(0);
}

Resource::~Resource()
{
}
#include "Saturn.h"

OBJ* Saturn::_Obj = nullptr;

Saturn::Saturn()
{
	if (_Obj == nullptr)
	{
		_Obj = new OBJ;
		_Obj->ReadObj("Obj/Planet/", "Saturn.obj");
	}
	obj = _Obj;
	name = "Saturn";
}
Saturn::~Saturn()
{

}
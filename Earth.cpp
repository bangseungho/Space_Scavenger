#include "Earth.h"

OBJ* Earth::_Obj = nullptr;

Earth::Earth()
{
	if (_Obj == nullptr)
	{
		_Obj = new OBJ;
		_Obj->ReadObj("Obj/Planet/", "Earth.obj");
	}
	obj = _Obj;

	name = "Earth";
}

Earth::~Earth()
{

}
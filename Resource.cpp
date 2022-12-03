#include "Resource.h"

libxl::Book* Resource::book = nullptr;
libxl::Sheet* Resource::sheet = nullptr;

Resource::Resource() : Mesh(this)
{
	if (book == nullptr)
	{
		book = xlCreateXMLBook();
		book->load(L"Data/PlayerData.xlsx");
		sheet = book->getSheet(0);
	}

	SetActive(false);

	collider.tag = "Resource";
	collider.object = this;

	amount = 0;
	velocity = vec3(0);

	Render::meshtRender->AddObject(this, "Resource");
}

Resource::~Resource()
{
}

void Resource::Init()
{
	
}
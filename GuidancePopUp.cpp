#include "Guidance.h"

GuidacnePopUp::GuidacnePopUp(Guidance* _Guidance) : guidance(_Guidance)
{
	ResourceData* data = ResourceData::Instance;
	int count = data->sheet->readNum(1, 0);
	for (int i = 0; i < count; i++)
	{
		wstring wNmae = data->sheet->readStr(i + 5, 2);
		string name;
		name.assign(wNmae.begin(), wNmae.end());
		resourceToggles[name].name += name;
	}
}

GuidacnePopUp::~GuidacnePopUp()
{
}

void GuidacnePopUp::Enable()
{
	for (auto& toggle : resourceToggles)
		toggle.second.SetActive(true);
}

void GuidacnePopUp::Disable()
{
	for (auto& toggle : resourceToggles)
		toggle.second.SetActive(false);
}
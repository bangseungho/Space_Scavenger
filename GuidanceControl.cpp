#include "Guidance.h"

GuidanceControl::GuidanceControl(Guidance* _Guidance) : guidance(_Guidance)	
{
	ResourceData* data = ResourceData::Instance;
	int count = data->sheet->readNum(1, 0);
	for (int i = 0; i < count; i++)
	{
		wstring wNmae = data->sheet->readStr(i + 2, 1);
		string name;

		static std::locale loc(""); 
		auto& facet = use_facet<codecvt<wchar_t, char, mbstate_t>>(loc);
		name = wstring_convert<remove_reference<decltype(facet)>::type, wchar_t>(&facet).to_bytes(wNmae);

		Toggle* toggle = new Toggle;
		toggle->name += name;
		toggle->transform.local->scale *= 3;
		toggle->transform.local->position = vec3(100 * i - 300, 100, 0);

		resourceToggles[name] = toggle;
	}
}

GuidanceControl::~GuidanceControl()
{
}

void GuidanceControl::Enable()
{
	background.SetActive(true);
	for (auto& toggle : resourceToggles)
		toggle.second->SetActive(true);
}

void GuidanceControl::Disable()
{
	background.SetActive(false);
	for (auto& toggle : resourceToggles)
		toggle.second->SetActive(false);
}

void GuidanceControl::Update()
{
	for (auto& toggle : resourceToggles)
	{
		guidance->resourceType[toggle.first] = toggle.second->isToggle;
	}
}

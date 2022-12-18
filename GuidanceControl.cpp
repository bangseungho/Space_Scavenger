#include "Guidance.h"

GuidanceControl::GuidanceControl(Guidance* _Guidance) : guidance(_Guidance)	
{
	ResourceData* data = ResourceData::Instance;
	int count = data->sheet->readNum(1, 0);
	for (int i = 0; i < count; i++)
	{
		string path = "UI/Resource/" + data->resourceTypes[i] + "_";
		Toggle* toggle = new Toggle(path);
		toggle->name += data->resourceTypes[i];
		toggle->transform.local->position = vec3(100 * i - 300, 100, 0);

		resourceToggles[data->resourceTypes[i]] = toggle;
	}

	SetActive(false);
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

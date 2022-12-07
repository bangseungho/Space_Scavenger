#pragma once
#include "Equipment.h"
#include "Resource.h"

// todo 
// event 함수를 통해 collide에 걸린 자원이 drag를 킬 수 있게 해야함

class Guidance : public Equipment
{
public:
	Guidance();
	~Guidance();

public:
	void Update();

public:
	void SerchResource();	// 주변에 Resource가 있는지 확인
public:
	map<string, bool> resourceType;	// 가져올 자원 리스트		(추후 설정된 자원만 끓고 오게 변경)

public:
	float serchDistnace;	// 찾을 자원의 최대 범위
};


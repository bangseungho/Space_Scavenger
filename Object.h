#pragma once
#include "Transform.h"

class Object {
public:
	static int ID_Count;
	static list<Object*> allObject;
	static vector<Object*> initObject;

	static unsigned char key;
	static unsigned char keyUp;
	static int specialKey;
	static int specialKeyUp;

	static unsigned int meterialBlockLoaction;

public:
	Object();
	~Object();

public:
	virtual void Enable() {};
	virtual void Disable() {};
	virtual void Init();
	virtual void Update();
	virtual void OnCollision() {};
	virtual void MyTimer();
	virtual mat4& SetMatrix();

public:
	bool ActiveSelf() { return isActive; };
	void SetActive(bool value);

	void Info();

public:
	int id;
	string name;
	Transform transform;

private:
	bool isActive;
	
};
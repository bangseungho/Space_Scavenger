#pragma once

#include "Transform.h"
#include "Camera.h"

class Object {
public:
	static int ID_Count;
	static list<Object*> allObject;

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
	virtual void Update();
	virtual void Init();
	virtual void OnCollision() {};
	virtual void MyTimer();

public:
	bool ActiveSelf() { return isActive; };
	void SetActive(bool value);
	void Info();
public:
	virtual mat4& SetMatrix();

public:
	int id;
	string name;
	Transform transform;
	bool isDraw = true;

private:
	bool isActive;
	
};
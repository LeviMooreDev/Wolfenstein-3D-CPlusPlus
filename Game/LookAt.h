#pragma once
#include "Component.h"
#include "GameObject.h"

class LookAt : public Component
{
private:
	GameObject * target;

public:
	LookAt(GameObject * target);
	~LookAt();

	void Update(Scene * scene);

	string GetName() { return "LookAt"; };
};


#pragma once
#include "Component.h"

class Health : public Component
{
private:
	GameObject * player;

public:
	Health(GameObject * player);
	~Health();

	void Hit(GameObject * other);

	string GetName() { return "Health"; };
};


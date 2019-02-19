#pragma once
#include "Component.h"

class Gold : public Component
{
private:
	GameObject * player;

public:
	Gold(GameObject * player);
	~Gold();

	void Hit(GameObject * other);

	string GetName() { return "Gold"; };
};


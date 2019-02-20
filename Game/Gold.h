#pragma once
#include "Component.h"
#define GoldComponentName "Gold"

//responsible for picking up gold on the floor
class Gold : public Component
{
public:
	//called when something hits the gold. in our case, the player is the only thing that moves so other have to be the player
	void Hit(GameObject * other);

	//returns the component name
	string GetName() { return GoldComponentName; };
};


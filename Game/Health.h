#pragma once
#include "Component.h"
#define HealthComponentName "Health"

//responsible for picking up health packs on the floor
class Health : public Component
{
public:
	//called when something hits the health pack. in our case, the player is the only thing that moves so other have to be the player
	void Hit(GameObject * other);

	//returns the component name
	string GetName() { return HealthComponentName; };
};


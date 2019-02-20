#pragma once
#include "Component.h"
#include "GameObject.h"
#define LookAtComponentName "Look At"

//responsible for making the game object face the target at all times
class LookAt : public Component
{
private:
	//the target we want to look at
	GameObject * target;

public:
	//target: the target we want to look at
	LookAt(GameObject * target);

	//called by the engine every frame
	void Update(Scene * scene);

	//returns the component name
	string GetName() { return LookAtComponentName; };
};


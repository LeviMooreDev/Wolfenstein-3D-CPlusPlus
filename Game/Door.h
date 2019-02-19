#pragma once
#include "Component.h"
#include "Scene.h"
#include "Vector3.h"
#include "Collider.h"
#include "GameObject.h"

class Door : public Component
{
private:
	bool needSetup = true;
	Vector3 openPosition;
	float speed = 4;
	bool open = false;
	Collider * collider;
	GameObject * player;

public:
	Door(GameObject * player, Collider * collider);
	~Door();

	void Update(Scene * scene);
};


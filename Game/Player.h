#pragma once
#include "Component.h"
#include "Transform.h"

class Player : public Component
{
private:
	float walkSpeed = 10;
	float lookSpeed = 30;
	Vector3 v;

public:
	Player();
	~Player();

	void OnWallHit(GameObject * other);

	void Update(Scene * scene);
	string GetName() { return "Player"; };
};


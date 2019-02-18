#pragma once
#include "Component.h"
#include "Scene.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Animation.h"

class Enemy : public Component
{
private:
	GameObject * player;
	MeshRenderer * meshRenderer;
	Vector3 lookDir = Vector3::Forward();
	float angleToPlayer;
	bool rightSideOfPlayer;
	bool dead;
	int hp = 2;

	Animation deadAnimation;

public:
	Enemy();
	Enemy(GameObject * player, MeshRenderer * meshRenderer);
	~Enemy();

	void Update(Scene * scene);
	void Idle();
	void Dead();
	void Hit();
};


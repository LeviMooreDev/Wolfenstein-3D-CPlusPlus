#pragma once
#include "Component.h"
#include "Scene.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Animation.h"

class Enemy : public Component
{
private:
	enum State
	{
		Idle,
		Hit,
		Fire,
		Dead
	};
	State state;

	GameObject * player;
	MeshRenderer * meshRenderer;
	float angleToPlayer;
	bool rightSideOfPlayer;
	float hitEffectEndTime;
	bool callHitFun;
	float nextFireTime;
	float fireDelay = 1;

	Animation deadAnimation;
	Animation fireAnimation;

public:
	int hp = 3;
	Vector3 lookDir = Vector3::Forward();
	bool ignorePlayer;

	//only use for GetName()
	Enemy();
	Enemy(GameObject * player, MeshRenderer * meshRenderer);
	~Enemy();

	void Update(Scene * scene);
	void IdleState();
	void HitState();
	void FireState();
	void DeadState();
	void HitByPlayer();

	string GetName() { return "Enemy"; };
};


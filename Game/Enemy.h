#pragma once
#include "Component.h"
#include "Scene.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Animation.h"
#define EnemyComponentName "Enemy"

//responsible for the enemy AI
class Enemy : public Component
{
private:
	//the states an enemy can be in
	enum State
	{
		Idle,
		TakenDamage,
		Fire,
		Dead
	};
	//the current state the enemy is in
	State state;

	//the player game object
	GameObject * player;
	//the mesh renderer component on the same game object the enemy component is on
	MeshRenderer * meshRenderer;

	//angle to the player. 0 is front, 180 is behind. 90 can be to either side.
	float angleToPlayer;
	//true if the player is on the right side of the enemy
	bool rightSideOfPlayer;
	//the time when the taken damage effect stops
	float takenDamageEffectEndTime;
	//true if the enemy needs to call the hit method on the player next time it uses the fire animation frame
	bool callHitPlayerFun;
	//next time the enemy can try to shoot the player
	float nextFireTime;
	//the minimum fire delay between fire attempts at the player. a random amount 0-1 is added.
	float minimumFireDelay = 1;

	//animation object used to control the dead animation
	Animation deadAnimation;
	//animation object used to control the fire animation
	Animation fireAnimation;

public:
	//the health of the enemy. hits needed to kill it.
	int hp = 3;
	//the direction the enemy is looking. we don't use transform.rotation because this is overwritten by the LookAt component
	Vector3 lookDirection = Vector3::Forward();
	//true if the guard should ignore the player
	bool ignorePlayer;

	//player: the player game object
	//meshRenderer: the mesh renderer component on the same game object the enemy component is on
	Enemy(GameObject * player, MeshRenderer * meshRenderer);

	//called by the engine every frame
	void Update(Scene * scene);

	//called by Update() when the enemy is in an idle state
	void IdleState();
	//called by Update() when the enemy is in a taken damage state
	void TakenDamageState();
	//called by Update() when the enemy is in a fire state
	void FireState();
	//called by Update() when the enemy is in a dead state
	void DeadState();

	//make the enemy take 1 in damage
	void HitByPlayer();

	//returns the enemy component name
	string GetName() { return EnemyComponentName; };
};


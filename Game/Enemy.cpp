#include "Enemy.h"
#include "MeshRenderer.h"
#include "Debug.h"
#include "MeshRenderer.h"
#include "Textures.h"
#include "Collider.h"
#include "Time.h"
#include "Audio.h"
#include "Player.h"
#include "Raycast.h"

Enemy::Enemy(GameObject * player, MeshRenderer * meshRenderer)
{
	//add random delay to minimum fire delay and set next fire time
	minimumFireDelay += static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	nextFireTime = Time::GetTimeSinceStart() + minimumFireDelay;

	//setup animation objects
	deadAnimation.loop = false;
	deadAnimation.waitTime = 0.14f;
	deadAnimation.frames = 4;

	fireAnimation.loop = false;
	fireAnimation.waitTime = 0.14f;
	fireAnimation.frames = 4;

	(*this).player = player;
	(*this).meshRenderer = meshRenderer;
}


void Enemy::Update(Scene * scene)
{
	//fint direction and angle to player
	Vector3 directionToPlayer = Vector3(player->transform.position.x, 0, player->transform.position.z) - Vector3(gameObject->transform.position.x, 0, gameObject->transform.position.z);
	angleToPlayer = directionToPlayer.Angle(lookDirection);
	rightSideOfPlayer = !(lookDirection.Rotate(Vector3::Up(), 90).Angle(directionToPlayer) > 90.0f);

	//call the right state method
	switch (state)
	{
	case Enemy::Idle:
		IdleState();
		break;
	case Enemy::TakenDamage:
		TakenDamageState();
		break;
	case Enemy::Fire:
		FireState();
		break;
	case Enemy::Dead:
		DeadState();
		break;
	}
}

void Enemy::IdleState()
{
	//if we don't want to ignore the player and are close enough
	if (!ignorePlayer && gameObject->GetDistanceToCamera() < 20)
	{
		//if we are ready to try firing at the player
		if (Time::GetTimeSinceStart() > nextFireTime)
		{
			//reset fire time
			nextFireTime = Time::GetTimeSinceStart() + minimumFireDelay;

			//send a ray toward the player and if we hit look at the player and change state to fire
			Vector3 point;
			GameObject * hit = Raycast::Send(gameObject->transform.position, player->transform.position - gameObject->transform.position, point, gameObject);
			if (hit != nullptr)
			{
				lookDirection = (hit->transform.position - gameObject->transform.position).Normalized();

				if (hit->tag == "Player")
				{
					fireAnimation.Reset();
					callHitPlayerFun = true;
					state = State::Fire;
					return;
				}
			}
		}
	}

	//the frame in the idle animation texture we want to show
	float frameIndex = 0;

	//find the right frame based on the angle the player is looking at the enemy from
	angleToPlayer += (45.0f / 2.0f);
	if (angleToPlayer < 45.0f && angleToPlayer > 0)
	{
		frameIndex = 0;
	}
	if (angleToPlayer < 90.0f && angleToPlayer > 45.0f)
	{
		if (rightSideOfPlayer)
			frameIndex = 1;
		else
			frameIndex = 7;
	}
	if (angleToPlayer < 135.0f && angleToPlayer > 90.0f)
	{
		if (rightSideOfPlayer)
			frameIndex = 2;
		else
			frameIndex = 6;
	}
	if (angleToPlayer < 180.0f && angleToPlayer > 135.0f)
	{
		if (rightSideOfPlayer)
			frameIndex = 3;
		else
			frameIndex = 5;
	}
	if (angleToPlayer < 225 && angleToPlayer > 180.0f)
	{
		frameIndex = 4;
	}

	//find the area of the texture we want to show
	float dirStep = 1.0f / 8.0f;
	float startX = frameIndex * dirStep;
	float endX = startX + dirStep;

	//update enemy texture
	meshRenderer->SetTexture("guard idle", new float[8]{ startX, 0, endX, 0, endX, 1, startX, 1, }, true);
}
void Enemy::TakenDamageState()
{
	//if we are done showing the taken damage effect return to idle, else set the enemy texture to guard hit
	if (Time::GetTimeSinceStart() > takenDamageEffectEndTime)
	{
		state = State::Idle;
		return;
	}
	meshRenderer->SetTexture("guard hit", new float[8]{ 0, 0, 1, 0, 1, 1, 0, 1, }, true);
}
void Enemy::FireState()
{
	//update the fire animation object
	fireAnimation.UpdateTime(Time::GetDeltaTime());

	//if we have reached the end of the fire animation return to idle
	int index = fireAnimation.GetIndex();
	if (index == fireAnimation.frames)
	{
		state = State::Idle;
	}
	//else update the enemy texture
	else
	{
		float dirStep = 1.0f / (fireAnimation.frames);
		float startX = fireAnimation.GetIndex() * dirStep;
		float endX = startX + dirStep;
		meshRenderer->SetTexture("guard fire", new float[8]{ startX, 0, endX, 0, endX, 1, startX, 1, }, true);

		//if we are at the animation frame where the gun fires and we have not yet call Hit() on the player, call Hit()
		if (callHitPlayerFun && index == fireAnimation.frames - 1)
		{
			callHitPlayerFun = false;
			Audio::Play("pistol");
			((Player*)player->GetComponent(PlayerComponentName))->Hit();
		}
	}
}
void Enemy::DeadState()
{
	//update the dead animation object
	deadAnimation.UpdateTime(Time::GetDeltaTime());

	//update the enemy texture
	float dirStep = 1.0f / (deadAnimation.frames + 1);
	float startX = deadAnimation.GetIndex() * dirStep;
	float endX = startX + dirStep;
	meshRenderer->SetTexture("guard dead", new float[8]{ startX, 0, endX, 0, endX, 1, startX, 1, }, true);
}

void Enemy::HitByPlayer()
{
	hp--;
	
	//if the enemy dead
	if (hp == 0)
	{
		//play a random dead sound
		string sounds[2] = { "enemy death 1", "enemy death 2" };
		Audio::PlayRandom(sounds, 2);

		//give the player a pistol
		((Player*)player->GetComponent(PlayerComponentName))->GivePistol();

		//disable the collider component on the enemy
		gameObject->GetComponent(ColliderComponentName)->enabled = false;

		//reset the dead animation and change state to dead
		deadAnimation.Reset();
		state = State::Dead;
	}
	else
	{
		Audio::Play("enemy hit");

		//look at the player
		lookDirection = (player->transform.position - gameObject->transform.position).Normalized();
		
		//set the taken damage effect end time and change state to taken damage
		takenDamageEffectEndTime = Time::GetTimeSinceStart() + .15f;
		state = State::TakenDamage;
	}
}

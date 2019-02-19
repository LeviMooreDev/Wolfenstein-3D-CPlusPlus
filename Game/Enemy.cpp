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

Enemy::Enemy(){}
Enemy::Enemy(GameObject * player, MeshRenderer * meshRenderer)
{
	fireDelay += static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

	nextFireTime = Time::GetTimeSinceStart() + fireDelay;

	deadAnimation.loop = false;
	deadAnimation.waitTime = 0.14f;
	deadAnimation.maxIndex = 4;

	fireAnimation.loop = false;
	fireAnimation.waitTime = 0.14f;
	fireAnimation.maxIndex = 4;

	(*this).player = player;
	(*this).meshRenderer = meshRenderer;
}

Enemy::~Enemy()
{
}

void Enemy::Update(Scene * scene)
{
	//direction to player
	Vector3 directionToPlayer = Vector3(player->transform.position.x, 0, player->transform.position.z) - Vector3(gameObject->transform.position.x, 0, gameObject->transform.position.z);
	
	//angle to player
	angleToPlayer = directionToPlayer.Angle(lookDir);

	//on the right side of the player
	rightSideOfPlayer = !(lookDir.Rotate(Vector3::Up(), 90).Angle(directionToPlayer) > 90.0f);

	switch (state)
	{
	case Enemy::Idle:
		IdleState();
		break;
	case Enemy::Hit:
		HitState();
		break;
	case Enemy::Fire:
		FireState();
		break;
	case Enemy::Dead:
		DeadState();
		break;
	default:
		break;
	}
}

void Enemy::IdleState()
{
	if (!ignorePlayer && gameObject->GetDistanceToCamera() < 20)
	{
		if (Time::GetTimeSinceStart() > nextFireTime)
		{
			nextFireTime = Time::GetTimeSinceStart() + fireDelay;

			Vector3 point;
			GameObject * hit = Raycast::Send(gameObject->transform.position, player->transform.position - gameObject->transform.position, point, gameObject);
			if (hit != nullptr)
			{
				lookDir = (hit->transform.position - gameObject->transform.position).Normalized();

				if (hit->tag == "Player")
				{
					fireAnimation.Reset();
					callHitFun = true;
					state = State::Fire;
					return;
				}
			}
		}
	}

	string textureName = "guard idle";
	float dirIndex = 0;

	angleToPlayer += (45.0f / 2.0f);
	if (angleToPlayer < 45.0f && angleToPlayer > 0)
	{
		dirIndex = 0;
	}
	if (angleToPlayer < 90.0f && angleToPlayer > 45.0f)
	{
		if (rightSideOfPlayer)
			dirIndex = 1;
		else
			dirIndex = 7;
	}
	if (angleToPlayer < 135.0f && angleToPlayer > 90.0f)
	{
		if (rightSideOfPlayer)
			dirIndex = 2;
		else
			dirIndex = 6;
	}
	if (angleToPlayer < 180.0f && angleToPlayer > 135.0f)
	{
		if (rightSideOfPlayer)
			dirIndex = 3;
		else
			dirIndex = 5;
	}
	if (angleToPlayer < 225 && angleToPlayer > 180.0f)
	{
		dirIndex = 4;
	}

	float dirStep = 1.0f / 8.0f;
	float startX = dirIndex * dirStep;
	float endX = startX + dirStep;
	meshRenderer->SetTexture(textureName, new float[8]{ startX, 0, endX, 0, endX, 1, startX, 1, }, true);
}
void Enemy::HitState()
{
	if (Time::GetTimeSinceStart() > hitEffectEndTime)
	{
		state = State::Idle;
		return;
	}
	meshRenderer->SetTexture("guard hit", new float[8]{ 0, 0, 1, 0, 1, 1, 0, 1, }, true);
}
void Enemy::FireState()
{
	fireAnimation.UpdateTime(Time::GetDeltaTime());

	int index = fireAnimation.GetIndex();
	if (index == fireAnimation.maxIndex)
	{
		state = State::Idle;
	}
	else
	{
		float dirStep = 1.0f / (fireAnimation.maxIndex);
		float startX = fireAnimation.GetIndex() * dirStep;
		float endX = startX + dirStep;
		meshRenderer->SetTexture("guard fire", new float[8]{ startX, 0, endX, 0, endX, 1, startX, 1, }, true);

		if (callHitFun && index == fireAnimation.maxIndex - 1)
		{
			callHitFun = false;
			Audio::Play("pistol");
			((Player*)player->GetComponent(Player().GetName()))->Hit();
		}
	}
}
void Enemy::DeadState()
{
	deadAnimation.UpdateTime(Time::GetDeltaTime());

	float dirStep = 1.0f / (deadAnimation.maxIndex + 1);
	float startX = deadAnimation.GetIndex() * dirStep;
	float endX = startX + dirStep;
	meshRenderer->SetTexture("guard dead", new float[8]{ startX, 0, endX, 0, endX, 1, startX, 1, }, true);
}

void Enemy::HitByPlayer()
{
	hp--;
	if (hp == 0)
	{
		string sounds[2] = { "enemy death 1", "enemy death 2" };
		Audio::PlayRandom(sounds, 2);

		gameObject->GetComponent(Collider().GetName())->enabled = false;
		deadAnimation.Reset();
		state = State::Dead;

		((Player*)player->GetComponent(Player().GetName()))->GivePistol();
	}
	else
	{
		Audio::Play("enemy hit");
		lookDir = (player->transform.position - gameObject->transform.position).Normalized();
		hitEffectEndTime = Time::GetTimeSinceStart() + .15f;
		state = State::Hit;
	}
}

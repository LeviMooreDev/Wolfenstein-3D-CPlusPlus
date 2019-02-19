#include "Enemy.h"
#include "MeshRenderer.h"
#include "Debug.h"
#include "MeshRenderer.h"
#include "Textures.h"
#include "Collider.h"
#include "Time.h"
#include "Audio.h"
#include "Player.h"

Enemy::Enemy()
{
}
Enemy::Enemy(GameObject * player, MeshRenderer * meshRenderer)
{
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

	if (dead)
		Dead();
	else
		Idle();
}

void Enemy::Idle()
{
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
void Enemy::Dead()
{
	deadAnimation.UpdateTime(Time::GetDeltaTime());

	float dirStep = 1.0f / (deadAnimation.maxIndex + 1);
	float startX = deadAnimation.GetIndex() * dirStep;
	float endX = startX + dirStep;
	meshRenderer->SetTexture("guard dead", new float[8]{ startX, 0, endX, 0, endX, 1, startX, 1, }, true);
}

void Enemy::Hit()
{
	hp--;
	if (hp == 0)
	{
		string sounds[2] = { "enemy death 1", "enemy death 2" };
		Audio::PlayRandom(sounds, 2);

		gameObject->GetComponent(Collider().GetName())->enabled = false;
		deadAnimation.Reset();
		deadAnimation.loop = false;
		deadAnimation.waitTime = 0.14f;
		deadAnimation.maxIndex = 4;
		dead = true;

		((Player*)player->GetComponent(Player().GetName()))->GivePistol();
	}
	else
	{
		Audio::Play("enemy hit");
	}
}

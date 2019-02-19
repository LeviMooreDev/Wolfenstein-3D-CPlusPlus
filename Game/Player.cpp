#include "Player.h"
#include "Input.h"
#include "Transform.h"
#include "GameObject.h"
#include "Time.h"
#include "Collider.h"
#include "Debug.h"
#include "Raycast.h"
#include "Enemy.h"
#include "Audio.h"
#include "UINumber.h"
#include "Game.h"

Player::Player()
{
}
Player::Player(UIImage * handImage, UIImage * hudWeapon, UINumber * hudGold, UINumber * hudHealth)
{
	(*this).handImage = handImage;
	(*this).hudWeapon = hudWeapon;
	(*this).hudGold = hudGold;
	(*this).hudHealth = hudHealth;

	pistolAnimation.maxIndex = 4;
	pistolAnimation.loop = false;
	pistolAnimation.waitTime = 0.08f;
	pistolAnimation.run = false;

	knifeAnimation.maxIndex = 4;
	knifeAnimation.loop = false;
	knifeAnimation.waitTime = 0.08f;
	knifeAnimation.run = false;
}
Player::~Player()
{
}

void Player::Update(Scene * scene)
{
	Move();
	Weapon();
	Hud();
}
void Player::Move()
{
	gameObject->transform.rotation += Vector3::Up() * Input::MouseMoveDirection().x * lookSpeed * Time::GetDeltaTime();

	if (Input::KeyHold(Input::Keys::W))
	{
		gameObject->transform.position += gameObject->transform.Forward() * walkSpeed * Time::GetDeltaTime();
	}
	if (Input::KeyHold(Input::Keys::S))
	{
		gameObject->transform.position += gameObject->transform.Back() * walkSpeed * Time::GetDeltaTime();
	}
	if (Input::KeyHold(Input::Keys::A))
	{
		gameObject->transform.position += gameObject->transform.Left() * walkSpeed * Time::GetDeltaTime();
	}
	if (Input::KeyHold(Input::Keys::D))
	{
		gameObject->transform.position += gameObject->transform.Right() * walkSpeed * Time::GetDeltaTime();
	}
}
void Player::Weapon()
{
	pistolAnimation.UpdateTime(Time::GetDeltaTime());
	knifeAnimation.UpdateTime(Time::GetDeltaTime());

	float dirStep = 1.0f / 5.0f;
	float startX = (hasPistol ? pistolAnimation.GetIndex() : knifeAnimation.GetIndex()) * dirStep;
	float endX = startX + dirStep;

	if (hasPistol)
		handImage->SetTexture("pistol animation", new float[8]{ startX, 0, startX, 1, endX, 1, endX, 0, });
	else
		handImage->SetTexture("knife animation", new float[8]{ startX, 0, startX, 1, endX, 1, endX, 0, });

	if (Input::KeyDown(Input::Keys::SPACE))
	{
		if (hasPistol)
			Audio::Play("pistol");
		else
			Audio::Play("knife");

		pistolAnimation.Reset();
		pistolAnimation.run = true;
		knifeAnimation.Reset();
		knifeAnimation.run = true;

		Vector3 point;
		GameObject * hit = Raycast::Send(gameObject->transform.position, gameObject->transform.Forward(), point, gameObject);
		if (hit != nullptr)
		{
			if (hit->tag == "Enemy")
			{
				if (hasPistol)
				{
					((Enemy *)(hit->GetComponent(Enemy().GetName())))->HitByPlayer();
				}
				else if(gameObject->transform.position.Distance(hit->transform.position) < 2)
				{
					((Enemy *)(hit->GetComponent(Enemy().GetName())))->HitByPlayer();
				}
			}
		}
	}
}
void Player::Hud()
{
	if (hasPistol)
	{
		hudWeapon->SetTexture("hud pistol", new float[8]{ 0, 0, 0, 1, 1, 1, 1, 0, });
	}
	else
	{
		hudWeapon->SetTexture("hud knife", new float[8]{ 0, 0, 0, 1, 1, 1, 1, 0, });
	}
}

void Player::AddHealth(int amount)
{
	health += amount;
	if (health > 100)
		health = 100;

	hudHealth->number = health;
}
void Player::AddGold(int amount)
{
	gold += amount;
	hudGold->number = gold;
}

void Player::GivePistol()
{
	hasPistol = true;
}

void Player::Hit()
{
	health -= 8;
	if (health < 0)
		health = 0;
	hudHealth->number = health;

	if (health == 0)
	{
		Audio::Play("player dead");
		Game::LoseGame();
		//dead
	}
	else
	{
		string sounds[2] = { "player hit 1", "player hit 2" };
		Audio::PlayRandom(sounds, 2);
	}
}

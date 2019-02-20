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

Player::Player(UIImage * handImage, UIImage * hudWeapon, UINumber * hudGold, UINumber * hudHealth)
{
	(*this).handImage = handImage;
	(*this).hudWeapon = hudWeapon;
	(*this).hudGold = hudGold;
	(*this).hudHealth = hudHealth;

	//setup animation objects
	pistolAnimation.frames = 4;
	pistolAnimation.loop = false;
	pistolAnimation.waitTime = 0.08f;
	pistolAnimation.run = false;

	knifeAnimation.frames = 4;
	knifeAnimation.loop = false;
	knifeAnimation.waitTime = 0.08f;
	knifeAnimation.run = false;

	//set next time we can attack
	nextAttackTime = Time::GetTimeSinceStart() + attackDelay;
}

void Player::Update(Scene * scene)
{
	UpdateMovement();
	UpdateWeapon();
	UpdateHandTexture();

	//if the player presses 0, decrease the mouse sensitivity
	if (Input::KeyHold(Input::Keys::N9))
	{
		if (lookSpeed > 1)
			lookSpeed -= 5 * Time::GetDeltaTime();
	}
	//if the player presses 9, increase the mouse sensitivity
	if (Input::KeyHold(Input::Keys::N0))
	{
		lookSpeed += 5 * Time::GetDeltaTime();
	}
}
void Player::UpdateMovement()
{
	//rotate player based on mouse movement
	gameObject->transform.rotation += Vector3::Up() * Input::MouseMoveDirection().x * lookSpeed * Time::GetDeltaTime();

	//the direction we want to move
	Vector3 moveDirection;

	//add to move direction relative to self
	if (Input::KeyHold(Input::Keys::W))
		moveDirection += gameObject->transform.Forward();
	if (Input::KeyHold(Input::Keys::S))
		moveDirection += gameObject->transform.Back();
	if (Input::KeyHold(Input::Keys::A))
		moveDirection += gameObject->transform.Left();
	if (Input::KeyHold(Input::Keys::D))
		moveDirection += gameObject->transform.Right();

	//normalize move direction to avoid moving faster if both x and y is 1 or -1
	moveDirection.Normalize();

	//move
	gameObject->transform.position += moveDirection * walkSpeed * Time::GetDeltaTime();
}
void Player::UpdateWeapon()
{
	//update animation objects
	pistolAnimation.UpdateTime(Time::GetDeltaTime());
	knifeAnimation.UpdateTime(Time::GetDeltaTime());

	//find the area of the texture we want to show
	float dirStep = 1.0f / 5.0f;
	float startX = (hasPistol ? pistolAnimation.GetIndex() : knifeAnimation.GetIndex()) * dirStep;
	float endX = startX + dirStep;

	//update hand texture
	if (hasPistol)
		handImage->SetTexture("pistol animation", new float[8]{ startX, 0, startX, 1, endX, 1, endX, 0, });
	else
		handImage->SetTexture("knife animation", new float[8]{ startX, 0, startX, 1, endX, 1, endX, 0, });

	//if the player presses space or left mouse
	if (Input::KeyDown(Input::Keys::SPACE) || Input::MouseLeftClick())
	{
		//if we can't attack yet return, else set next attack time
		if (Time::GetTimeSinceStart() < nextAttackTime)
			return;
		nextAttackTime = Time::GetTimeSinceStart() + attackDelay;

		//play attack sound
		if (hasPistol)
			Audio::Play("pistol");
		else
			Audio::Play("knife");

		//reset animation objects
		pistolAnimation.Reset();
		pistolAnimation.run = true;
		knifeAnimation.Reset();
		knifeAnimation.run = true;

		//send ray out in front of the player
		//if we hit an enemy call their HitByPlayer() method
		Vector3 point;
		GameObject * hit = Raycast::Send(gameObject->transform.position, gameObject->transform.Forward(), point, gameObject);
		if (hit != nullptr)
		{
			if (hit->tag == "Enemy")
			{
				if (hasPistol)
				{
					((Enemy *)(hit->GetComponent(EnemyComponentName)))->HitByPlayer();
				}
				else if(gameObject->transform.position.Distance(hit->transform.position) < 2)
				{
					((Enemy *)(hit->GetComponent(EnemyComponentName)))->HitByPlayer();
				}
			}
		}
	}
}
void Player::UpdateHandTexture()
{
	if (hasPistol)
		hudWeapon->SetTexture("hud pistol", new float[8]{ 0, 0, 0, 1, 1, 1, 1, 0, });
	else
		hudWeapon->SetTexture("hud knife", new float[8]{ 0, 0, 0, 1, 1, 1, 1, 0, });
}

bool Player::AddHealth()
{
	//if we are at max health stop and return false
	if (health >= 100)
		return false;

	//limit health to 100
	health += 10;
	if (health >= 100)
		health = 100;

	//update ui
	hudHealth->number = health;

	return true;
}
void Player::AddGold()
{
	//add gold and update ui
	gold += 300;
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

	//update ui
	hudHealth->number = health;

	//if we are dead play dead sound and show lose game scene
	if (health == 0)
	{
		Audio::Play("player dead");
		Game::LoseGame();
	}
	//if we are still alive play a player hit sound
	else
	{
		string sounds[2] = { "player hit 1", "player hit 2" };
		Audio::PlayRandom(sounds, 2);
	}
}

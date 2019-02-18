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

Player::Player()
{
}
Player::~Player()
{
}

void Player::OnWallHit(GameObject * other)
{


}

void Player::Update(Scene * scene)
{
	if (Input::KeyDown(Input::Keys::SPACE))
	{
		Audio::Play("pistol");

		Vector3 point;
		GameObject * hit = Raycast::Send(gameObject->transform.position, gameObject->transform.Forward(), point, gameObject);
		if (hit != nullptr)
		{
			if (hit->tag == "Enemy")
			{
				((Enemy *)(hit->GetComponent(Enemy().GetName())))->Hit();
			}
		}
	}

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
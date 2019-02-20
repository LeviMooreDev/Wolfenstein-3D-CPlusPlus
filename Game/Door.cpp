#include "Door.h"
#include "Scene.h"
#include "Input.h"
#include "Time.h"
#include "Collider.h"
#include "GameObject.h"
#include "Audio.h"

Door::Door(GameObject * player, Collider * collider)
{
	(*this).collider = collider;
	(*this).player = player;
}

void Door::Update(Scene * scene)
{
	//if the door needs setup set the open position to the right of the current(closed) position
	if (needSetup)
	{
		needSetup = false;
		openPosition = gameObject->transform.position + gameObject->transform.Right() * 3;
	}

	//when the player presses E, check if the player is close enough to use the door
	//if yes, mark the door as open and disable the collider
	if (Input::KeyDown(Input::Keys::E))
	{
		Vector3 d = gameObject->transform.position;
		d.y = 0;
		Vector3 p = player->transform.position;
		p.y = 0;

		if (d.Distance(p) < 2)
		{
			open = true;
			collider->enabled = false;
			Audio::Play("door");
		}
	}

	//if the door is open move it to the open position
	if (open)
	{
		gameObject->transform.position.MoveTowards(openPosition, speed * Time::GetDeltaTime());
	}
}

#include "Door.h"
#include "Scene.h"
#include "Input.h"
#include "Time.h"
#include "Collider.h"
#include "GameObject.h"
#include "Audio.h"
#include "Debug.h"

Door::Door(GameObject * player, Collider * collider)
{
	(*this).collider = collider;
	(*this).player = player;
}
Door::~Door()
{
}

void Door::Update(Scene * scene)
{
	if (needSetup)
	{
		needSetup = false;
		openPosition = gameObject->transform.position + gameObject->transform.Right() * 3;
	}

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
	if (open)
	{
		gameObject->transform.position.MoveTowards(openPosition, speed * Time::GetDeltaTime());
	}
}

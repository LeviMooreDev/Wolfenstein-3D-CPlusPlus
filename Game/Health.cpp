#include "Health.h"
#include "Audio.h"
#include "GameObject.h"
#include "Player.h"

Health::Health(GameObject * player)
{
}
Health::~Health()
{
}

void Health::Hit(GameObject * other)
{
	if (((Player*)other->GetComponent(Player().GetName()))->AddHealth(10))
	{
		gameObject->enabled = false;
		Audio::Play("health");
	}
}

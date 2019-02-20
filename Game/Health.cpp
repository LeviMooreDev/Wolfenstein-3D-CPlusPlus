#include "Health.h"
#include "Audio.h"
#include "GameObject.h"
#include "Player.h"

void Health::Hit(GameObject * other)
{
	if (((Player*)other->GetComponent(PlayerComponentName))->AddHealth())
	{
		gameObject->enabled = false;
		Audio::Play("health");
	}
}

#include "Gold.h"
#include "Audio.h"
#include "GameObject.h"
#include "Player.h"

void Gold::Hit(GameObject * other)
{
	((Player*)other->GetComponent(PlayerComponentName))->AddGold();
	gameObject->enabled = false;
	Audio::Play("pickup");
}

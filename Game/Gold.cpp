#include "Gold.h"
#include "Audio.h"
#include "GameObject.h"
#include "Player.h"

Gold::Gold(GameObject * player)
{
}
Gold::~Gold()
{
}

void Gold::Hit(GameObject * other)
{
	((Player*)other->GetComponent(Player().GetName()))->AddGold(300);
	gameObject->enabled = false;
	Audio::Play("pickup");
}

#pragma once
#include "Component.h"
#include "Scene.h"
#include "GameObject.h"
#define EndGameLeverComponentName "End Game Lever"

//responsible for ending the game when the player use the lever at the end of the level
class EndGameLever : public Component
{
private:
	//the player
	GameObject * player;

public:
	//player: the player game object
	EndGameLever(GameObject * player);

	//called by the engine every frame
	void Update(Scene * scene);

	//returns the component name
	string GetName() { return EndGameLeverComponentName; };
};
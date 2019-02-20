#pragma once
#include "Component.h"
#include "Scene.h"
#include "Vector3.h"
#include "Collider.h"
#include "GameObject.h"
#define DoorComponentName "Door"

//responsible for opening doors when the player use them
class Door : public Component
{
private:
	//does the door need to be setup
	bool needSetup = true;
	//the position when open
	Vector3 openPosition;
	//the speed the door moves with
	float speed = 4;
	//is the door open
	bool open = false;
	//the collider component on the game object the door component is on
	Collider * collider;
	//the player game object
	GameObject * player;

public:
	//player: the player game object
	//collider: the collider component on the same game object the door component is on
	Door(GameObject * player, Collider * collider);
	
	//called by the engine every frame
	void Update(Scene * scene);

	//returns the component name
	string GetName() { return DoorComponentName; };
};


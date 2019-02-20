#pragma once
#include "Component.h"
#include "Transform.h"
#include "UIImage.h"
#include "Animation.h"
#include "UINumber.h"
#define PlayerComponentName "Player"

//responsible for controlling the player
class Player : public Component
{
private:
	//player health
	int health = 100;
	//player gold
	int gold = 0;
	//walk speed
	float walkSpeed = 10;
	//look speed
	float lookSpeed = 10;
	//true if we has picked up a pistol
	bool hasPistol = false;
	//next time we can attack
	float nextAttackTime;
	//the delay between attack
	float attackDelay = 0.2f;

	//the ui image showing player hands
	UIImage * handImage;
	//the ui image showing what weapon we have equipped
	UIImage * hudWeapon;
	//the ui number showing how much gold we have
	UINumber * hudGold;
	//the ui number showing how much health we have
	UINumber * hudHealth;

	//animation object used to update the knife animation
	Animation knifeAnimation;
	//animation object used to update the pistol animation
	Animation pistolAnimation;

public:
	//handImage: the ui image showing our hands
	//hudWeapon: the ui image showing what weapon we have equipped
	//hudGold: the ui number showing how much gold we have
	//hudHealth: the ui number showing how much health we have
	Player(UIImage * handImage, UIImage * hudWeapon, UINumber * hudGold, UINumber * hudHealth);

	//called by the engine every frame
	void Update(Scene * scene);
	//move the player
	void UpdateMovement();
	//use the weapon
	void UpdateWeapon();
	//update hand texture
	void UpdateHandTexture();

	//add 10 health to the player
	//return: true if the player was able to get more health
	bool AddHealth();
	//add 300 gold to the player
	void AddGold();
	//give the player a pistol
	void GivePistol();

	//damage the player
	void Hit();

	//returns the component name
	string GetName() { return PlayerComponentName; };
};


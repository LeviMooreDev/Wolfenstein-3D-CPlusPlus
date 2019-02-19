#pragma once
#include "Component.h"
#include "Transform.h"
#include "UIImage.h"
#include "Animation.h"
#include "UINumber.h"

class Player : public Component
{
private:
	int health = 100;
	int gold = 0;
	float walkSpeed = 10;
	float lookSpeed = 25;
	bool hasPistol;
	UIImage * handImage;
	UIImage * hudWeapon;
	UINumber * hudGold;
	UINumber * hudHealth;
	Animation pistolAnimation;
	Animation knifeAnimation;

public:
	Player();
	Player(UIImage * handImage, UIImage * hudWeapon, UINumber * hudGold, UINumber * hudHealth);
	~Player();

	void Update(Scene * scene);
	void Move();
	void Weapon();
	void Hud();

	void AddHealth(int amount);
	void AddGold(int amount);
	void GivePistol();

	string GetName() { return "Player"; };
};


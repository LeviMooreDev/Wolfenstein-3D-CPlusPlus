#pragma once
#include "Component.h"
#include "Scene.h"
#include "GameObject.h"

class EndGame : public Component
{
private:
	GameObject * player;

public:
	EndGame(GameObject * player);
	~EndGame();

	void Update(Scene * scene);
};
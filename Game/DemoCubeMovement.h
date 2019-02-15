#pragma once
#include "Component.h"

class DemoCubeMovement : public Component
{
private:
	float targetScale = 1;
	bool moveCube = false;

public:
	DemoCubeMovement();
	~DemoCubeMovement();

	void Update(Scene * scene);
};


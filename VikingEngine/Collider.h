#pragma once
#include "DLLHelper.h"
#include "Component.h"
#include "Vector3.h"
#include "Scene.h"
#include <iostream>
#include <functional>

class Collider : public Component
{
private:
	float colors[72]
	{
		0, 255, 0,   0, 255, 0,   0, 255, 0,   0, 255, 0,
		0, 255, 0,   0, 255, 0,   0, 255, 0,   0, 255, 0,
		0, 255, 0,   0, 255, 0,   0, 255, 0,   0, 255, 0,
		0, 255, 0,   0, 255, 0,   0, 255, 0,   0, 255, 0,
		0, 255, 0,   0, 255, 0,   0, 255, 0,   0, 255, 0,
		0, 255, 0,   0, 255, 0,   0, 255, 0,   0, 255, 0,
	};
	float vertices[72] =
	{
		-.5, .5, -.5,   -.5, .5,  .5,  -.5, -.5, .5,  -.5, -.5, -.5, //left
		 .5, -.5, -.5,    .5, -.5, .5,   .5, .5,  .5,   .5, .5, -.5, //right
		 .5, .5, -.5,   -.5, .5, -.5,  -.5, -.5, -.5,   .5, -.5, -.5, //forward
		 .5, -.5,  .5,   -.5, -.5, .5,  -.5, .5,  .5,   .5, .5, .5, //back
		 .5,  .5,  .5,   -.5,  .5, .5,  -.5, .5, -.5,   .5, .5, -.5, //up
		 .5,-.5, -.5,   -.5,-.5, -.5,  -.5, -.5, .5,   .5, -.5,  .5 //down
	};

	Vector3 lastPosition;
	Vector3 lastCenter;
	Vector3 lastSize;

	std::function<void(GameObject *)> onHit = nullptr;
	std::function<void(GameObject *)> onTrigger = nullptr;

	void Update(Scene * scene);
	void Draw2(Scene * scene);

public:
	DLLEXTERN static bool showWireframe;
	bool solid = true;
	Vector3 size = Vector3::One();
	Vector3 center;

	DLLEXTERN Collider();
	DLLEXTERN ~Collider();
	DLLEXTERN void ListenForHit(std::function<void(GameObject *)> onHit);
	DLLEXTERN void ListenForTrigger(std::function<void(GameObject *)> onHit);
	DLLEXTERN Vector3 Min();
	DLLEXTERN Vector3 Max();

	string GetName() { return "Collider"; };
};
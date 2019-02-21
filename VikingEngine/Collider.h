#pragma once
#include "DLLHelper.h"
#include "Component.h"
#include "Vector3.h"
#include "Scene.h"
#include <iostream>
#include <functional>
#define ColliderComponentName "Collider"

//responsible for making a game object behave in a way that simulates physics
class Collider : public Component
{
private:
	//vertices used when showing wireframe
	float wireframeVertices[72] =
	{
		-.5, .5, -.5,   -.5, .5,  .5,  -.5, -.5, .5,  -.5, -.5, -.5, //left
		 .5, -.5, -.5,    .5, -.5, .5,   .5, .5,  .5,   .5, .5, -.5, //right
		 .5, .5, -.5,   -.5, .5, -.5,  -.5, -.5, -.5,   .5, -.5, -.5, //forward
		 .5, -.5,  .5,   -.5, -.5, .5,  -.5, .5,  .5,   .5, .5, .5, //back
		 .5,  .5,  .5,   -.5,  .5, .5,  -.5, .5, -.5,   .5, .5, -.5, //up
		 .5,-.5, -.5,   -.5,-.5, -.5,  -.5, -.5, .5,   .5, -.5,  .5 //down
	};
	//colors used when showing wireframe
	float colors[72]
	{
		0, 255, 0,   0, 255, 0,   0, 255, 0,   0, 255, 0,
		0, 255, 0,   0, 255, 0,   0, 255, 0,   0, 255, 0,
		0, 255, 0,   0, 255, 0,   0, 255, 0,   0, 255, 0,
		0, 255, 0,   0, 255, 0,   0, 255, 0,   0, 255, 0,
		0, 255, 0,   0, 255, 0,   0, 255, 0,   0, 255, 0,
		0, 255, 0,   0, 255, 0,   0, 255, 0,   0, 255, 0,
	};

	//last valid game object position
	Vector3 lastValidPosition;
	//last last center value
	Vector3 lastCenterOffset;
	//last last size value
	Vector3 lastSize;

	//function to call when we hit solid game object
	std::function<void(GameObject *)> onHit = nullptr;
	//function to call when we hit not solid game object
	std::function<void(GameObject *)> onTrigger = nullptr;

	//called every frame
	void Update(Scene * scene);
	//called every frame when the second draw group is called
	void Draw2(Scene * scene);

public:
	//true if we want to show the collision boxes with wireframes
	DLLEXTERN static bool showWireframe;
	//true if the game object can not go through other game objects with a collider
	bool solid = true;
	//size of the collider
	Vector3 size = Vector3::One();
	//center of the collider. center offset is added to the position of the game object.
	Vector3 centerOffset;

	DLLEXTERN Collider() {};

	//add a method to be called with the game object hits another game object that is solid
	DLLEXTERN void ListenForHit(std::function<void(GameObject *)> onHit);
	//add a method to be called with the game object hits another game object that is not solid
	DLLEXTERN void ListenForTrigger(std::function<void(GameObject *)> onHit);

	//returns the minimum z, y and z value of the collider
	DLLEXTERN Vector3 Min();
	//returns the maximum x, y and z value of the collider
	DLLEXTERN Vector3 Max();

	//returns the component name
	string GetName() { return ColliderComponentName; };
};
#pragma once
#include "DLLHelper.h"
#include "Component.h"
#include "Transform.h"
#include <unordered_map>
#include <iostream>
#include "Camera.h"

typedef std::basic_string<char> string;

//we create an empty scene class because we need it as a parameter, but if we include it we end up in an endless loop of including
class Scene;

class GameObject
{
private:
	//id of the next game object that is created.
	static int nextId;
	//id of the game object. is unique and automatically assigned.
	int id;
	//true if the game object has a collider
	bool hasColliders = false;
	//distance to the active camera
	float distanceToCamera;

	//the reason we split components up into different lists are so it is easier to update and raw them in the correct order

	//list of camera components the game object has on it
	std::unordered_map<string, Component *> componentsCamera;
	//list of physics components the game object has on it
	std::unordered_map<string, Component *> componentsPhysics;
	//list of normal components the game object has on it
	std::unordered_map<string, Component *> componentsNormal;

public:
	//if false the game object and its components will not be updated or drawn
	bool enabled = true;
	//true if the distance to the active camera is important
	//we use this to make sorting of game objects more efficient
	bool distanceToCameraIsImportant;

	//game object tag. use to quickly identify type of game object
	string tag = "NO TAG";

	//the game objects transform
	Transform transform;

	DLLEXTERN GameObject();
	DLLEXTERN ~GameObject();

	//returns the distance to the active camera
	DLLEXTERN float GetDistanceToCamera();

	//update the game object
	void UpdateSelf(Scene * scene);
	//update physics components
	void UpdatePhysicsComponents(Scene * scene);
	//update normal components
	void UpdateNormalComponents(Scene * scene);
	//update camera components
	void DrawCameraComponents(Scene * scene);
	//call components draw1 method
	void Draw1(Scene * scene);
	//call components draw2 method
	void Draw2(Scene * scene);

	//returns true if the game object has a collider on it
	bool HasColliders();

	//add component to game object
	//com: the component you want to add
	DLLEXTERN Component * AddComponent(Component * component);

	//returns a component from game object
	//com: name of the component you want to get
	DLLEXTERN Component * GetComponent(string name);

	//remove component from game object
	//com: name of the component you want to remove
	DLLEXTERN void RemoveComponent(Component * component);

	//returns game object id
	DLLEXTERN int GetId() const;
};
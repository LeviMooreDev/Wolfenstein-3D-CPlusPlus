#pragma once
#include "DLLHelper.h"
#include "GameObject.h"
#include "Camera.h"
#include <iostream>
#include <unordered_set> 
#include <iterator> 
#include "UIBase.h"

//responsible for keeping track of what things to render and together with engine making sure things are called in the right order
class Scene
{
private:
	//list of game objects in the scene
	std::vector<GameObject *> gameObjects;
	//list of ui elements in the scene
	std::unordered_set<UIBase *> uiElements;

	//amount of game objects in the scene last frame
	//we use this to make sorting of game objects more efficient
	int lastGameObjectCount;

public:
	//the active camera
	Camera * activeCamera;

	DLLEXTERN Scene() {};
	DLLEXTERN ~Scene();

	//called by engine when game objects needs to be updated
	void Update();
	//called by engine when game objects needs to be drawn
	void Draw();
	//called by engine when ui elements needs to be drawn
	void UI();

	//sorts game objects based on how close they are to the active camera
	void SortGameObjectsByDistanceToCamera();

	//add game object to scene.
	//gameObject: the game object you want to add
	DLLEXTERN GameObject * AddGameObject(GameObject * gameObject);

	//remove game object from scene.
	//gameObject: the game object you want to remove
	DLLEXTERN void RemoveGameObject(GameObject * gameObject);

	//returns all game objects in the scene
	DLLEXTERN std::vector<GameObject*>* GetAllGameObjects();

	//add ui element to scene.
	//element: the ui element you want to add

	DLLEXTERN UIBase * AddUIElement(UIBase * element);
	//remove ui element from scene.
	//element: the ui element you want to remove
	DLLEXTERN void RemoveUIElement(UIBase * element);
};
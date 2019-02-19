#pragma once
#include "DLLHelper.h"
#include "GameObject.h"
#include "Camera.h"
#include <iostream>
#include <unordered_set> 
#include <iterator> 
#include "UIBase.h"

class Scene
{
private:
	//list of game objects in the scene
	std::vector<GameObject *> * gameObjects = new std::vector<GameObject *>();
	std::unordered_set<UIBase *> * uiElements = new std::unordered_set<UIBase *>();

	int lastGameObjectCount;
public:
	Camera * activeCamera;

	DLLEXTERN Scene();
	DLLEXTERN ~Scene();

	void Update();
	void Draw();
	void UI();

	void SortGameObjectsByDistanceToCamera();

	//returns true if the scene is empty
	DLLEXTERN bool IsEmpty();

	//add game object to scene. You can not add the same object twice.
	DLLEXTERN GameObject * AddGameObject(GameObject * go);
	//remove game object from scene.
	DLLEXTERN void RemoveGameObject(GameObject * go);
	//returns all game objects in the scene
	DLLEXTERN std::vector<GameObject*>* GetAllGameObjects();

	//add ui element to scene.
	DLLEXTERN UIBase * AddUIElement(UIBase * element);
	//remove ui element from scene.
	DLLEXTERN void RemoveUIElement(UIBase * element);
	//returns all ui elements in the scene
	DLLEXTERN std::unordered_set<UIBase*>* GetUIElements();
};
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
	std::vector<GameObject *> gameObjects;
	std::unordered_set<UIBase *> uiElements;

	int lastGameObjectCount;
public:
	Camera * activeCamera;

	DLLEXTERN Scene();
	DLLEXTERN ~Scene();

	void Update();
	void Draw();
	void UI();

	void SortGameObjectsByDistanceToCamera();

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
};
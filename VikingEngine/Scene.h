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
	/* WHY use unordered_set?
	we search our game objects a lot and unordered_set is fast at that.
	with unordered_set the element is used as the key. This means that we don't need to know the index to remove a game object.
	we use unordered_set instead of set because it does not matter what order the elements are in.
	*/
	//list of game objects in the scene
	std::unordered_set<GameObject *> * gameObjects;
	std::unordered_set<UIBase *> * uiElements;

public:
	Camera * activeCamera;

	DLLEXTERN Scene();
	DLLEXTERN ~Scene();

	void Update();
	void Draw();
	void UI();

	//returns true if the scene is empty
	DLLEXTERN bool IsEmpty();

	//add game object to scene. You can not add the same object twice.
	DLLEXTERN GameObject * AddGameObject(GameObject * go);
	//remove game object from scene.
	DLLEXTERN void RemoveGameObject(GameObject * go);
	//returns all game objects in the scene
	DLLEXTERN std::unordered_set<GameObject*>* GetAllGameObjects();

	//add ui element to scene.
	DLLEXTERN UIBase * AddUIElement(UIBase * element);
	//remove ui element from scene.
	DLLEXTERN void RemoveUIElement(UIBase * element);
	//returns all ui elements in the scene
	DLLEXTERN std::unordered_set<UIBase*>* GetUIElements();
};
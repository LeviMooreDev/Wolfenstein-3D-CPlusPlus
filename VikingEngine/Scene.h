#pragma once
#include "DLLHelper.h"
#include "GameObject.h"

#include <iostream>
#include <unordered_set> 
#include <iterator> 

class DLLEXTERN Scene
{
private:
	/* WHY use unordered_set?
	we search our game objects a lot and unordered_set is fast at that.
	with unordered_set the element is used as the key. This means that we don't need to know the index to remove a game object.
	we use unordered_set instead of set because it does not matter what order the elements are in.
	*/
	//list of game objects in the scene
	std::unordered_set<GameObject> gameObjects;

public:
	Scene();
	~Scene();

	//add game object to scene. You can not add the same object twice.
	GameObject AddGameObject(GameObject go);

	//remove game object from scene.
	void RemoveGameObject(GameObject go);

	//remove all game objects from scene.
	void ClearGameObjects();

	//count game objects in scene.
	int GetGameObjectCount();

	//returns true if the scene is empty
	bool IsEmpty();
};


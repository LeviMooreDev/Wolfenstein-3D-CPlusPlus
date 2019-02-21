#include "Scene.h"
#include <GL/freeglut.h>
#include <GLFW\glfw3.h>
#include "Debug.h"
#include <exception>
#include "Engine.h"
#include <algorithm>
#include "Input.h"
#include <algorithm>
#include <iostream>
#include "GameObject.h"

Scene::~Scene()
{
	//free up memory used by game objects
	for (auto gameObject = gameObjects.begin(); gameObject != gameObjects.end(); gameObject++)
		delete *gameObject;
	gameObjects.clear();

	//free up memory used by ui elements
	for (auto uiElement = uiElements.begin(); uiElement != uiElements.end(); uiElement++)
		delete *uiElement;
	uiElements.clear();
}

void Scene::Update()
{
	//loop all game objects in the scene
	std::vector<GameObject *>::iterator go = gameObjects.begin();
	
	//update the game object (no components)
	while (go != gameObjects.end())
	{
		if ((*go)->enabled)
			(*go)->UpdateSelf(this);
		go++;
	}

	//update normal components
	go = gameObjects.begin();
	while (go != gameObjects.end())
	{
		if ((*go)->enabled)
			(*go)->UpdateNormalComponents(this);
		go++;
	}

	//update physics components
	go = gameObjects.begin();
	while (go != gameObjects.end())
	{
		if ((*go)->enabled)
			(*go)->UpdatePhysicsComponents(this);
		go++;
	}
}
void Scene::Draw()
{
	//update camera components
	std::vector<GameObject *>::iterator go = gameObjects.begin();
	while (go != gameObjects.end())
	{
		if ((*go)->enabled)
			(*go)->DrawCameraComponents(this);
		go++;
	}

	//sort game objects by distance to active camera
	SortGameObjectsByDistanceToCamera();

	//call draw1 on all game objects
	go = gameObjects.begin();
	while (go != gameObjects.end())
	{
		if ((*go)->enabled)
			(*go)->Draw1(this);
		go++;
	}

	//call draw2 on all game objects
	go = gameObjects.begin();
	while (go != gameObjects.end())
	{
		if ((*go)->enabled)
			(*go)->Draw2(this);
		go++;
	}
}

void Scene::UI()
{
	//set camera and matrix to "2d" so ui element position and size is not in world space but screen space
	glMatrixMode(GL_PROJECTION_MATRIX);
	glOrtho(0, Engine::I()->GetWindowSize().x, 0, Engine::I()->GetWindowSize().y, -1, 1);
	glMatrixMode(GL_MODELVIEW_MATRIX);
	glDisable(GL_DEPTH_TEST);
	
	//loop ui elements and draw them
	std::unordered_set<UIBase *>::iterator uiElement = uiElements.begin();
	while (uiElement != uiElements.end())
	{
		if ((*uiElement)->enabled)
			(*uiElement)->Draw();
		uiElement++;
	}

	glEnable(GL_DEPTH_TEST);
}

void Scene::SortGameObjectsByDistanceToCamera()
{
	//if we have less than 2 game objects no need to sort them(it)
	if (gameObjects.size() < 2)
		return;

	//if the amount of game objects have not changed since last frame no need to sort them so the one where distance to the camera is important is first.
	if (lastGameObjectCount != gameObjects.size())
	{
		lastGameObjectCount = gameObjects.size();
		
		//we use bubble sort to order the game objects where distance to the camera is important first.
		//we use some extra resources doing this once in awhile, so when we sort the important game objects every frame we can stop as soon as we reach a none important game object
		//by doing it this way we avoid having to sort all the game objects including the ones that does not need sorting every frame

		bool swapp = true;
		while (swapp)
		{
			swapp = false;
			std::vector<GameObject *>::iterator go = gameObjects.begin();
			while (go != gameObjects.end() - 1)
			{
				if (!(*go)->distanceToCameraIsImportant && (*(go + 1))->distanceToCameraIsImportant)
				{
					std::iter_swap(go, go + 1);
					swapp = true;
				}

				go++;
			}
		}
	}

	//we use bubble sort to order the game objects by their distance to the active camera
	bool swapp = true;
	while (swapp)
	{
		swapp = false;

		std::vector<GameObject *>::iterator go = gameObjects.begin();
		while (go != gameObjects.end() - 1)
		{
			//if we have reached a game object where distance to the camera is not important we know that we have been through all the important game objects os we stop here
			if (!(*go)->distanceToCameraIsImportant)
				break;

			if ((*go)->GetDistanceToCamera() < (*(go + 1))->GetDistanceToCamera())
			{
				std::iter_swap(go, go + 1);
				swapp = true;
			}

			go++;
		}
	}

	return;
}

GameObject * Scene::AddGameObject(GameObject * gameObject)
{
	gameObjects.push_back(gameObject);
	return gameObject;
}
void Scene::RemoveGameObject(GameObject * gameObject)
{
	gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), gameObject), gameObjects.end());
}
std::vector<GameObject *> * Scene::GetAllGameObjects()
{
	return &gameObjects;
}

UIBase * Scene::AddUIElement(UIBase * element)
{
	if (uiElements.count(element) != 0)
	{
		Debug::Error("Trying to add same ui element to a scene twice. ID: " + std::to_string(element->GetId()));
		return element;
	}

	uiElements.insert(element);
	return element;
}

void Scene::RemoveUIElement(UIBase * element)
{
	if (uiElements.count(element) != 1)
	{
		Debug::Error("Trying to remove ui element that is not in the scene. ID: " + std::to_string(element->GetId()));
		return;
	}

	uiElements.erase(element);
}
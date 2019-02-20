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

Scene::Scene()
{
}
Scene::~Scene()
{
	for (auto gameObject = gameObjects.begin(); gameObject != gameObjects.end(); gameObject++)
		delete *gameObject;
	gameObjects.clear();

	for (auto uiElement = uiElements.begin(); uiElement != uiElements.end(); uiElement++)
		delete *uiElement;
	uiElements.clear();
}

void Scene::Update()
{
	std::vector<GameObject *>::iterator go = gameObjects.begin();
	
	while (go != gameObjects.end())
	{
		if ((*go)->enabled)
			(*go)->UpdateSelf(this);
		go++;
	}

	go = gameObjects.begin();
	while (go != gameObjects.end())
	{
		if ((*go)->enabled)
			(*go)->UpdateNormalComponents(this);
		go++;
	}

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
	//draw camera
	std::vector<GameObject *>::iterator go = gameObjects.begin();
	while (go != gameObjects.end())
	{
		if ((*go)->enabled)
			(*go)->DrawCameraComponents(this);
		go++;
	}

	SortGameObjectsByDistanceToCamera();
	//draw 1
	go = gameObjects.begin();
	while (go != gameObjects.end())
	{
		if ((*go)->enabled)
			(*go)->Draw1(this);
		go++;
	}

	//draw 2
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
	glMatrixMode(GL_PROJECTION_MATRIX);
	glOrtho(0, Engine::I()->GetWindowSize().x, 0, Engine::I()->GetWindowSize().y, -1, 1);
	glMatrixMode(GL_MODELVIEW_MATRIX);
	glDisable(GL_DEPTH_TEST);

	std::unordered_set<UIBase *>::iterator uiElement = uiElements.begin();
	while (uiElement != uiElements.end())
	{
		if ((*uiElement)->enabled)
			(*uiElement)->Update();
		uiElement++;
	}

	uiElement = uiElements.begin();
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
	if (gameObjects.size() < 2)
		return;

	if (lastGameObjectCount != gameObjects.size())
	{
		lastGameObjectCount = gameObjects.size();
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

	bool swapp = true;
	while (swapp)
	{
		swapp = false;

		std::vector<GameObject *>::iterator go = gameObjects.begin();
		while (go != gameObjects.end() - 1)
		{
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

	endLoop:
	return;
}

GameObject * Scene::AddGameObject(GameObject *go)
{
	gameObjects.push_back(go);
	return go;
}
void Scene::RemoveGameObject(GameObject * go)
{
	gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), go), gameObjects.end());
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
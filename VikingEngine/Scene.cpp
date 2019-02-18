#include "Scene.h"
#include <GL/freeglut.h>
#include <GLFW\glfw3.h>
#include "Debug.h"
#include <exception>
#include "Engine.h"

Scene::Scene()
{
	gameObjects = new std::unordered_set<GameObject *>();
	uiElements = new std::unordered_set<UIBase *>();
}
Scene::~Scene()
{
	delete gameObjects;
	delete uiElements;
}

void Scene::Update()
{
	std::unordered_set<GameObject *>::iterator go = gameObjects->begin();
	while (go != gameObjects->end())
	{
		if ((*go)->enabled)
			(*go)->UpdatePhysicsComponents(this);
		go++;
	}

	go = gameObjects->begin();
	while (go != gameObjects->end())
	{
		if ((*go)->enabled)
			(*go)->UpdateCameraComponents(this);
		go++;
	}

	go = gameObjects->begin();
	while (go != gameObjects->end())
	{
		if ((*go)->enabled)
			(*go)->UpdateNormalComponents(this);
		go++;
	}
}
void Scene::Draw()
{
	//draw camera
	std::unordered_set<GameObject *>::iterator go = gameObjects->begin();
	while (go != gameObjects->end())
	{
		if ((*go)->enabled)
			(*go)->DrawCameraComponents(this);
		go++;
	}

	//draw 1
	go = gameObjects->begin();
	while (go != gameObjects->end())
	{
		if ((*go)->enabled)
			(*go)->Draw1(this);
		go++;
	}

	//draw 2
	go = gameObjects->begin();
	while (go != gameObjects->end())
	{
		if ((*go)->enabled)
			(*go)->Draw2(this);
		go++;
	}
}

void Scene::UI()
{
	//glMatrixMode(GL_PROJECTION_MATRIX);
	glOrtho(0, Engine::I()->GetWindowSize().x, 0, Engine::I()->GetWindowSize().y, -1, 1);
	//glMatrixMode(GL_MODELVIEW_MATRIX);

	std::unordered_set<UIBase *>::iterator uiElement = uiElements->begin();
	while (uiElement != uiElements->end())
	{
		if ((*uiElement)->enabled)
			(*uiElement)->Update();
		uiElement++;
	}

	uiElement = uiElements->begin();
	while (uiElement != uiElements->end())
	{
		if ((*uiElement)->enabled)
			(*uiElement)->Draw();
		uiElement++;
	}
}

GameObject * Scene::AddGameObject(GameObject *go)
{
	if (gameObjects->count(go) != 0)
	{
		Debug::Error("Trying to add same game object to a scene twice. ID: " + std::to_string(go->GetId()) + " Name: " + go->name);
		return go;
	}

	gameObjects->insert(go);
	return go;
}
void Scene::RemoveGameObject(GameObject * go)
{
	if (gameObjects->count(go) != 1)
	{
		Debug::Error("Trying to remove game object that is not in the scene. ID: " + std::to_string(go->GetId()) + " Name: " + go->name);
		return;
	}

	gameObjects->erase(go);
}
std::unordered_set<GameObject *> * Scene::GetAllGameObjects()
{
	return gameObjects;
}

UIBase * Scene::AddUIElement(UIBase * element)
{
	if (uiElements->count(element) != 0)
	{
		Debug::Error("Trying to add same ui element to a scene twice. ID: " + std::to_string(element->GetId()));
		return element;
	}

	uiElements->insert(element);
	return element;
}

void Scene::RemoveUIElement(UIBase * element)
{
	if (uiElements->count(element) != 1)
	{
		Debug::Error("Trying to remove ui element that is not in the scene. ID: " + std::to_string(element->GetId()));
		return;
	}

	uiElements->erase(element);
}

std::unordered_set<UIBase*>* Scene::GetUIElements()
{
	return uiElements;
}

bool Scene::IsEmpty()
{
	return gameObjects->empty();
}

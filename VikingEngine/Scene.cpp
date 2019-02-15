#include "Scene.h"
#include <GL/freeglut.h>
#include <GLFW\glfw3.h>
#include "Debug.h"
#include <exception>

Scene::Scene()
{
	gameObjects = new std::unordered_set<GameObject *>();
}
Scene::~Scene()
{
	delete gameObjects;
}

void Scene::UpdateGameObjects()
{
	std::unordered_set<GameObject *>::iterator go = gameObjects->begin();
	while (go != gameObjects->end())
	{
		(*go)->UpdateComponents(this);

		go++;
	}
}
void Scene::DrawCamera()
{
	if (activeCamera != nullptr)
		activeCamera->DrawViewport();
}
void Scene::DrawGameObjects()
{
	std::unordered_set<GameObject *>::iterator go = gameObjects->begin();
	while (go != gameObjects->end())
	{
		(*go)->DrawComponents(this);

		go++;
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
void Scene::ClearGameObjects()
{
	gameObjects->clear();
}
int Scene::GetGameObjectCount()
{
	return gameObjects->size();
}

bool Scene::IsEmpty()
{
	return gameObjects->empty();
}

#include "GameObject.h"
#include "Debug.h"
#include <typeinfo>
#include "Component.h"
#include "Scene.h"
#include "Engine.h"

int GameObject::nextId = 0;

GameObject::GameObject()
{
	id = nextId;
	GameObject::nextId++;
}
GameObject::~GameObject()
{
	std::unordered_map<string, Component *>::iterator com = componentsCamera.begin();
	while (com != componentsCamera.end())
	{
		delete com->second;
		com++;
	}
	componentsCamera.clear();

	com = componentsPhysics.begin();
	while (com != componentsPhysics.end())
	{
		delete com->second;
		com++;
	}
	componentsPhysics.clear();

	com = componentsNormal.begin();
	while (com != componentsNormal.end())
	{
		delete com->second;
		com++;
	}
	componentsNormal.clear();
}

float GameObject::GetDistanceToCamera()
{
	return distanceToCamera;
}

void GameObject::UpdateSelf(Scene * scene)
{
	if (scene->activeCamera != nullptr)
		distanceToCamera = transform.position.Distance(scene->activeCamera->GetParentGameObject()->transform.position);
}
void GameObject::UpdatePhysicsComponents(Scene * scene)
{
	std::unordered_map<string, Component *>::iterator com = componentsPhysics.begin();
	while (com != componentsPhysics.end())
	{
		if (com->second->enabled)
			com->second->V_Update(scene);
		com++;
	}
}
void GameObject::UpdateNormalComponents(Scene * scene)
{
	std::unordered_map<string, Component *>::iterator com = componentsNormal.begin();
	while (com != componentsNormal.end())
	{
		if (com->second->enabled)
			com->second->V_Update(scene);
		com++;
	}
}
void GameObject::DrawCameraComponents(Scene * scene)
{
	std::unordered_map<string, Component *>::iterator com = componentsCamera.begin();
	while (com != componentsCamera.end())
	{
		if (com->second->enabled)
			com->second->V_Draw1(scene);
		com++;
	}
}
void GameObject::Draw1(Scene * scene)
{
	std::unordered_map<string, Component *>::iterator com = componentsNormal.begin();
	while (com != componentsNormal.end())
	{
		if (com->second->enabled)
			com->second->V_Draw1(scene);
		com++;
	}

	com = componentsPhysics.begin();
	while (com != componentsPhysics.end())
	{
		if (com->second->enabled)
			com->second->V_Draw1(scene);
		com++;
	}
}
void GameObject::Draw2(Scene * scene)
{
	std::unordered_map<string, Component *>::iterator com = componentsNormal.begin();
	while (com != componentsNormal.end())
	{
		if (com->second->enabled)
			com->second->V_Draw2(scene);
		com++;
	}

	com = componentsPhysics.begin();
	while (com != componentsPhysics.end())
	{
		if (com->second->enabled)
			com->second->V_Draw2(scene);
		com++;
	}
}

bool GameObject::HasColliders()
{
	return hasColliders;
}

Component * GameObject::AddComponent(Component * com)
{
	if (com->GetName() == "Camera")
	{
		if (componentsCamera.count(com->GetName()) != 0)
		{
			Debug::Error("Trying to add same component to a game object twice. Game Object ID: " + std::to_string(GetId()) + ". Component: " + com->GetName());
			return com;
		}
		componentsCamera.insert(std::pair<string, Component *>(com->GetName(), com));
	}
	else if (com->GetName() == "Collider")
	{
		if (componentsPhysics.count(com->GetName()) != 0)
		{
			Debug::Error("Trying to add same component to a game object twice. Game Object ID: " + std::to_string(GetId()) + ". Component: " + com->GetName());
			return com;
		}
		componentsPhysics.insert(std::pair<string, Component *>(com->GetName(), com));
		hasColliders = true;
	}
	else
	{
		if (componentsNormal.count(com->GetName()) != 0)
		{
			Debug::Error("Trying to add same component to a game object twice. Game Object ID: " + std::to_string(GetId()) + ". Component: " + com->GetName());
			return com;
		}
		componentsNormal.insert(std::pair<string, Component *>(com->GetName(), com));
	}
	com->SetParentGameObject(this);
	return com;
}
Component * GameObject::GetComponent(string name)
{
	if (name == "Camera")
	{
		if (componentsCamera.count(name) != 1)
		{
			Debug::Error("Trying to get component that is not on the game object. Game Object ID: " + std::to_string(GetId()) + ". Component: " + name);
			return nullptr;
		}
		return componentsCamera.find(name)->second;
	}
	else if (name == "Collider")
	{
		if (componentsPhysics.count(name) != 1)
		{
			Debug::Error("Trying to get component that is not on the game object. Game Object ID: " + std::to_string(GetId()) + ". Component: " + name);
			return nullptr;
		}
		return componentsPhysics.find(name)->second;
	}
	else
	{
		if (componentsNormal.count(name) != 1)
		{
			Debug::Error("Trying to get component that is not on the game object. Game Object ID: " + std::to_string(GetId()) + ". Component: " + name);
			return nullptr;
		}
		return componentsNormal.find(name)->second;
	}
}
void GameObject::RemoveComponent(Component * com)
{
	if (com->GetName() == "Camera")
	{
		if (componentsCamera.count(com->GetName()) != 1)
		{
			Debug::Error("Trying to remove component that is not on the game object. Game Object ID: " + std::to_string(GetId()) + ". Component: " + com->GetName());
			return;
		}
		componentsCamera.erase(com->GetName());
	}
	else if (com->GetName() == "Collider")
	{
		if (componentsPhysics.count(com->GetName()) != 1)
		{
			Debug::Error("Trying to remove component that is not on the game object. Game Object ID: " + std::to_string(GetId()) + ". Component: " + com->GetName());
			return;
		}
		componentsPhysics.erase(com->GetName());
		hasColliders = !componentsNormal.empty();
	}
	else
	{
		if (componentsNormal.count(com->GetName()) != 1)
		{
			Debug::Error("Trying to remove component that is not on the game object. Game Object ID: " + std::to_string(GetId()) + ". Component: " + com->GetName());
			return;
		}
		componentsNormal.erase(com->GetName());
	}
	com->RemoveParentGameObject();
}

int GameObject::GetId() const
{
	return id;
}
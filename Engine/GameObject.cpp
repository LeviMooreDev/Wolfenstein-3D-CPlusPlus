#include "GameObject.h"
#include "Debug.h"
#include "Component.h"
#include "Scene.h"
#include "Engine.h"
#include "Collider.h"

//declare static field
int GameObject::nextId = 0;

GameObject::GameObject()
{
	//assign id and incress next id
	id = nextId;
	GameObject::nextId++;
}
GameObject::~GameObject()
{
	//free up memory used by the components on the game object

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
	//if there is an active camera find the distance to it
	if (scene->activeCamera != nullptr)
		distanceToCamera = transform.position.Distance(scene->activeCamera->gameObject->transform.position);
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

Component * GameObject::AddComponent(Component * component)
{
	//if we are adding a camera component
	if (component->GetName() == CameraComponentName)
	{
		//check if we already have a component of this type on the game object
		if (componentsCamera.count(component->GetName()) != 0)
		{
			Debug::Error("Trying to add same component to a game object twice. Game Object ID: " + std::to_string(GetId()) + ". Component: " + component->GetName());
			return component;
		}

		//add the component
		componentsCamera.insert(std::pair<string, Component *>(component->GetName(), component));
	}

	//if we are adding a collider component
	else if (component->GetName() == ColliderComponentName)
	{
		//check if we already have a component of this type on the game object
		if (componentsPhysics.count(component->GetName()) != 0)
		{
			Debug::Error("Trying to add same component to a game object twice. Game Object ID: " + std::to_string(GetId()) + ". Component: " + component->GetName());
			return component;
		}

		//add the component and set hasColliders to ture
		componentsPhysics.insert(std::pair<string, Component *>(component->GetName(), component));
		hasColliders = true;
	}

	//if we are adding a component that is not a camera or collider (normal)
	else
	{
		//check if we already have a component of this type on the game object
		if (componentsNormal.count(component->GetName()) != 0)
		{
			Debug::Error("Trying to add same component to a game object twice. Game Object ID: " + std::to_string(GetId()) + ". Component: " + component->GetName());
			return component;
		}

		//add the component
		componentsNormal.insert(std::pair<string, Component *>(component->GetName(), component));
	}

	//set the game object the components is on to this game object
	component->gameObject = this;

	return component;
}
Component * GameObject::GetComponent(string name)
{
	//if the component we want to get is a camera component
	if (name == CameraComponentName)
	{
		//check if we have a component of this type on the game object
		if (componentsCamera.count(name) != 1)
		{
			Debug::Error("Trying to get component that is not on the game object. Game Object ID: " + std::to_string(GetId()) + ". Component: " + name);
			return nullptr;
		}

		//return the component
		return componentsCamera.find(name)->second;
	}

	//if the component we want to get is a collider component
	else if (name == ColliderComponentName)
	{
		//check if we have a component of this type on the game object
		if (componentsPhysics.count(name) != 1)
		{
			Debug::Error("Trying to get component that is not on the game object. Game Object ID: " + std::to_string(GetId()) + ". Component: " + name);
			return nullptr;
		}

		//return the component
		return componentsPhysics.find(name)->second;
	}

	//if the component we want to get is not a camera or collider (normal)
	else
	{
		//check if we have a component of this type on the game object
		if (componentsNormal.count(name) != 1)
		{
			Debug::Error("Trying to get component that is not on the game object. Game Object ID: " + std::to_string(GetId()) + ". Component: " + name);
			return nullptr;
		}

		//return the component
		return componentsNormal.find(name)->second;
	}
}
void GameObject::RemoveComponent(Component * component)
{
	//if we want to remove a camera component
	if (component->GetName() == CameraComponentName)
	{
		//check if we have a component of this type on the game object
		if (componentsCamera.count(component->GetName()) != 1)
		{
			Debug::Error("Trying to remove component that is not on the game object. Game Object ID: " + std::to_string(GetId()) + ". Component: " + component->GetName());
			return;
		}

		//remove the component
		componentsCamera.erase(component->GetName());
	}

	//if we want to remove a collider component
	else if (component->GetName() == ColliderComponentName)
	{
		//check if we have a component of this type on the game object
		if (componentsPhysics.count(component->GetName()) != 1)
		{
			Debug::Error("Trying to remove component that is not on the game object. Game Object ID: " + std::to_string(GetId()) + ". Component: " + component->GetName());
			return;
		}

		//remove the component
		componentsPhysics.erase(component->GetName());

		//if we have no colliders on the game object set hasColliders to false
		hasColliders = !componentsPhysics.empty();
	}

	//if we want to remove a component that is not a camera or collider (normal)
	else
	{
		//check if we have a component of this type on the game object
		if (componentsNormal.count(component->GetName()) != 1)
		{
			Debug::Error("Trying to remove component that is not on the game object. Game Object ID: " + std::to_string(GetId()) + ". Component: " + component->GetName());
			return;
		}

		//remove the component
		componentsNormal.erase(component->GetName());
	}
	component->gameObject = nullptr;
}

int GameObject::GetId() const
{
	return id;
}
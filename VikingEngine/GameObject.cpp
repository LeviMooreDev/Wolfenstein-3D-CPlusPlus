#include "GameObject.h"
#include "Debug.h"
#include <typeinfo>
#include "Component.h"

int GameObject::nextId = 0;

GameObject::GameObject()
{
	id = nextId;
	nextId++;

	components = new std::unordered_map<string, Component *>();
}


GameObject::~GameObject()
{
	delete components;
}

void GameObject::UpdateComponents()
{
	std::unordered_map<string, Component *>::iterator com = components->begin();
	while (com != components->end())
	{
		if(com->second->enabled)
			com->second->Update(this);

		com++;
	}
}

Component * GameObject::AddComponent(Component * com)
{
	if (components->count(com->GetName()) != 0)
	{
		Debug::Error("Trying to add same component to a game object twice. Game Object ID: " + std::to_string(GetId()) + ". Game Object Name: " + name + ". Component: " + com->GetName());
		return com;
	}

	components->insert(std::pair<string, Component *>(com->GetName(), com));
	return com;
}

Component * GameObject::GetComponent(string name)
{
	if (components->count(name) != 1)
	{
		Debug::Error("Trying to get component that is not on the game object. Game Object ID: " + std::to_string(GetId()) + ". Game Object Name: " + name + ". Component: " + name);
		return nullptr;
	}

	return components->find(name)->second;
}

void GameObject::RemoveComponent(Component * com)
{
	if (components->count(com->GetName()) != 1)
	{
		Debug::Error("Trying to remove component that is not on the game object. Game Object ID: " + std::to_string(GetId()) + ". Game Object Name: " + name + ". Component: " + com->GetName());
		return;
	}

	components->erase(com->GetName());
}

int GameObject::GetId() const
{
	return id;
}

bool GameObject::operator==(const GameObject & other) const
{
	return id == other.id;
}

bool GameObject::operator<(const GameObject & other) const
{
	return id < other.id;
}

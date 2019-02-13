#include "GameObject.h"
#include "Debug.h"
#include <typeinfo>
#include "Component.h"

int GameObject::nextId = 0;

GameObject::GameObject()
{
	id = nextId;
	nextId++;

	components = new std::unordered_set<Component *>();
}


GameObject::~GameObject()
{
	delete components;
}

void GameObject::UpdateComponents()
{
	std::unordered_set<Component *>::iterator com = components->begin();
	while (com != components->end())
	{
		if((*com)->enabled)
			(*com)->Update(this);

		com++;
	}
}

Component * GameObject::AddComponent(Component * com)
{
	if (components->count(com) != 0)
	{
		Debug::Error("Trying to add same component to a game object twice. Game Object ID: " + std::to_string(GetId()) + ". Game Object Name: " + name + ". Component: " + com->GetName());
		return com;
	}

	components->insert(com);
	return com;
}

void GameObject::RemoveComponent(Component * com)
{
	if (components->count(com) != 1)
	{
		Debug::Error("Trying to remove component that is not on the game object. Game Object ID: " + std::to_string(GetId()) + ". Game Object Name: " + name + ". Component: " + com->GetName());
		return;
	}

	components->erase(com);
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

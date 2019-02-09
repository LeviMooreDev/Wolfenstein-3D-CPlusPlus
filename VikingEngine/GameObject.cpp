#include "GameObject.h"

int GameObject::nextId = 0;

GameObject::GameObject()
{
	id = nextId;
	nextId++;
}


GameObject::~GameObject()
{
}

int GameObject::GetId() const
{
	return id;
}

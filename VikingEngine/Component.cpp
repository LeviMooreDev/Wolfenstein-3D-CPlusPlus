#include "Component.h"
#include "GameObject.h"

void Component::SetParentGameObject(GameObject * gameObject)
{
	(*this).gameObject = gameObject;
}

GameObject * Component::GetParentGameObject()
{
	return gameObject;
}

void Component::RemoveParentGameObject()
{
	gameObject = nullptr;
}

void Component::V_Update(Scene * scene)
{
	Update(scene);
}

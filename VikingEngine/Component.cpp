#include "Component.h"
#include "GameObject.h"

void Component::SetParentGameObject(GameObject * gameObject)
{
	(*this).gameObject = gameObject;
}

void Component::RemoveParentGameObject()
{
	gameObject = nullptr;
}

void Component::V_Update(Scene * scene)
{
	if(enabled)
		Update(scene);
}

void Component::V_Draw(Scene * scene)
{
	if (enabled)
		Draw(scene);
}

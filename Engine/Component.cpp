#include "Component.h"
#include "GameObject.h"

void Component::V_Update(Scene * scene)
{
	Update(scene);
}

void Component::V_Draw1(Scene * scene)
{
	Draw1(scene);
}
void Component::V_Draw2(Scene * scene)
{
	Draw2(scene);
}
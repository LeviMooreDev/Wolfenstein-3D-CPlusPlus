#include "LookAt.h"
#include "GameObject.h"

LookAt::LookAt(GameObject * target)
{
	(*this).target = target;
}

void LookAt::Update(Scene * scene)
{
	//find the distance in the x and z axis
	float distanceX = gameObject->transform.position.x - target->transform.position.x;
	float distanceZ = gameObject->transform.position.z - target->transform.position.z;

	//update the y rotation
	gameObject->transform.rotation.x = 0;
	gameObject->transform.rotation.y = -atan2(distanceX, distanceZ) * 180 / 3.14159265358979323846;
	gameObject->transform.rotation.z = 0;
}
#include "Transform.h"
#include "Vector3.h"
#include "Debug.h"

Transform::Transform()
{
	position = Vector3(0, 0, 0);
	scale = Vector3(1, 1, 1);
	rotation = Vector3(0, 0, 0);
}
Transform::~Transform()
{

}

Vector3 Transform::Up()
{
	return Vector3(0, 1, 0).Rotate(Vector3::Right(), rotation.x).Rotate(Vector3::Up(), rotation.y).Rotate(Vector3::Forward(), rotation.z);
}

Vector3 Transform::Down()
{
	return Vector3(0, -1, 0).Rotate(Vector3::Right(), rotation.x).Rotate(Vector3::Up(), rotation.y).Rotate(Vector3::Forward(), rotation.z);
}

Vector3 Transform::Right()
{
	return Vector3(1, 0, 0).Rotate(Vector3::Right(), rotation.x).Rotate(Vector3::Up(), rotation.y).Rotate(Vector3::Forward(), rotation.z);
}

Vector3 Transform::Left()
{
	return Vector3(-1, 0, 0).Rotate(Vector3::Right(), rotation.x).Rotate(Vector3::Up(), rotation.y).Rotate(Vector3::Forward(), rotation.z);
}

Vector3 Transform::Forward()
{
	//Vector3 rotatedX = Vector3(0, 0, 1).Rotate(Vector3::Right(), rotation.x);
	//Vector3 rotatedY = rotatedX.Rotate(Vector3::Up(), rotation.y);
	//Vector3 rotatedZ = rotatedY.Rotate(Vector3::Forward(), rotation.z);
	//Vector3 rotated = rotatedZ;

	return Vector3(0, 0, 1).Rotate(Vector3::Right(), rotation.x).Rotate(Vector3::Up(), rotation.y).Rotate(Vector3::Forward(), rotation.z);
}

Vector3 Transform::Back()
{
	return Vector3(0, 0, -1).Rotate(Vector3::Right(), rotation.x).Rotate(Vector3::Up(), rotation.y).Rotate(Vector3::Forward(), rotation.z);
}

